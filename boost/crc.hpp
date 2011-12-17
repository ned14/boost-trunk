//  Boost CRC library crc.hpp header file  -----------------------------------//

//  Copyright 2001, 2004, 2011 Daryle Walker.  Use, modification, and
//  distribution are subject to the Boost Software License, Version 1.0.  (See
//  accompanying file LICENSE_1_0.txt or a copy at
//  <http://www.boost.org/LICENSE_1_0.txt>.)

//  See <http://www.boost.org/libs/crc/> for the library's home page.

#ifndef BOOST_CRC_HPP
#define BOOST_CRC_HPP

#include <boost/array.hpp>           // for boost::array
#include <boost/config.hpp>          // for BOOST_STATIC_CONSTANT, etc.
#include <boost/cstdint.hpp>         // for UINTMAX_C
#include <boost/integer.hpp>         // for boost::uint_t
#include <boost/mpl/integral_c.hpp>  // for boost::mpl::integral_c

#include <climits>  // for CHAR_BIT, etc.
#include <cstddef>  // for std::size_t

#include <boost/limits.hpp>  // for std::numeric_limits


// The type of CRC parameters that can go in a template should be related
// on the CRC's bit count.  This macro expresses that type in a compact
// form, but also allows an alternate type for compilers that don't support
// dependent types (in template value-parameters).
#if !(defined(BOOST_NO_DEPENDENT_TYPES_IN_TEMPLATE_VALUE_PARAMETERS) || (defined(BOOST_MSVC) && (BOOST_MSVC <= 1300)))
#define BOOST_CRC_PARM_TYPE  typename ::boost::uint_t<Bits>::fast
#else
#define BOOST_CRC_PARM_TYPE  unsigned long
#endif

// Some compilers [MS VC++ 6] cannot correctly set up several versions of a
// function template unless every template argument can be unambiguously
// deduced from the function arguments.  (The bug is hidden if only one version
// is needed.)  Since all of the CRC function templates have this problem, the
// workaround is to make up a dummy function argument that encodes the template
// arguments.  Calls to such template functions need all their template
// arguments explicitly specified.  At least one compiler that needs this
// workaround also needs the default value for the dummy argument to be
// specified in the definition.
#if defined(__GNUC__) || !defined(BOOST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS)
#define BOOST_CRC_DUMMY_PARM_TYPE
#define BOOST_CRC_DUMMY_INIT
#define BOOST_ACRC_DUMMY_PARM_TYPE
#define BOOST_ACRC_DUMMY_INIT
#else
namespace boost { namespace detail {
    template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
     BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
     bool ReflectIn, bool ReflectRem >
    struct dummy_crc_argument  { };
} }
#define BOOST_CRC_DUMMY_PARM_TYPE   , detail::dummy_crc_argument<Bits, \
 TruncPoly, InitRem, FinalXor, ReflectIn, ReflectRem> *p_
#define BOOST_CRC_DUMMY_INIT        BOOST_CRC_DUMMY_PARM_TYPE = 0
#define BOOST_ACRC_DUMMY_PARM_TYPE  , detail::dummy_crc_argument<Bits, \
 TruncPoly, 0, 0, false, false> *p_
#define BOOST_ACRC_DUMMY_INIT       BOOST_ACRC_DUMMY_PARM_TYPE = 0
#endif


namespace boost
{


//  Forward declarations  ----------------------------------------------------//

template < std::size_t Bits >
    class crc_basic;

template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly = 0u,
           BOOST_CRC_PARM_TYPE InitRem = 0u,
           BOOST_CRC_PARM_TYPE FinalXor = 0u, bool ReflectIn = false,
           bool ReflectRem = false >
    class crc_optimal;

template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
    typename uint_t<Bits>::fast  crc( void const *buffer,
     std::size_t byte_count
     BOOST_CRC_DUMMY_PARM_TYPE );

template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly >
    typename uint_t<Bits>::fast  augmented_crc( void const *buffer,
     std::size_t byte_count, typename uint_t<Bits>::fast initial_remainder
     BOOST_ACRC_DUMMY_PARM_TYPE );

template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly >
    typename uint_t<Bits>::fast  augmented_crc( void const *buffer,
     std::size_t byte_count
     BOOST_ACRC_DUMMY_PARM_TYPE );

typedef crc_optimal<16, 0x8005, 0, 0, true, true>         crc_16_type;
typedef crc_optimal<16, 0x1021, 0xFFFF, 0, false, false>  crc_ccitt_type;
typedef crc_optimal<16, 0x8408, 0, 0, true, true>         crc_xmodem_type;

typedef crc_optimal<32, 0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, true, true>
  crc_32_type;


//  Forward declarations for implementation detail stuff  --------------------//
//  (Just for the stuff that will be needed for the next two sections)

namespace detail
{
    template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly, bool Reflect >
        struct crc_table_t;

    template < std::size_t Bits, bool DoReflect >
        class crc_helper;

    #ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template < std::size_t Bits >
        class crc_helper< Bits, false >;
    #endif

}  // namespace detail


//  Simple cyclic redundancy code (CRC) class declaration  -------------------//

template < std::size_t Bits >
class crc_basic
{
public:
    // Type
    typedef typename boost::uint_t<Bits>::fast  value_type;

    // Constant for the template parameter
    BOOST_STATIC_CONSTANT( std::size_t, bit_count = Bits );

    // Constructor
    explicit  crc_basic( value_type truncated_polynominal,
               value_type initial_remainder = 0, value_type final_xor_value = 0,
               bool reflect_input = false, bool reflect_remainder = false );

    // Internal Operations
    value_type  get_truncated_polynominal() const;
    value_type  get_initial_remainder() const;
    value_type  get_final_xor_value() const;
    bool        get_reflect_input() const;
    bool        get_reflect_remainder() const;

    value_type  get_interim_remainder() const;
    void        reset( value_type new_rem );
    void        reset();

    // External Operations
    void  process_bit( bool bit );
    void  process_bits( unsigned char bits, std::size_t bit_count );
    void  process_byte( unsigned char byte );
    void  process_block( void const *bytes_begin, void const *bytes_end );
    void  process_bytes( void const *buffer, std::size_t byte_count );

    value_type  checksum() const;

private:
    // Member data
    value_type  rem_;
    value_type  poly_, init_, final_;  // non-const to allow assignability
    bool        rft_in_, rft_out_;     // non-const to allow assignability

};  // boost::crc_basic


//  Optimized cyclic redundancy code (CRC) class declaration  ----------------//

template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
class crc_optimal
{
public:
    // Type
    typedef typename boost::uint_t<Bits>::fast  value_type;

    // Constants for the template parameters
    BOOST_STATIC_CONSTANT( std::size_t, bit_count = Bits );
    BOOST_STATIC_CONSTANT( value_type, truncated_polynominal = TruncPoly );
    BOOST_STATIC_CONSTANT( value_type, initial_remainder = InitRem );
    BOOST_STATIC_CONSTANT( value_type, final_xor_value = FinalXor );
    BOOST_STATIC_CONSTANT( bool, reflect_input = ReflectIn );
    BOOST_STATIC_CONSTANT( bool, reflect_remainder = ReflectRem );

    // Constructor
    explicit  crc_optimal( value_type init_rem = InitRem );

    // Internal Operations
    value_type  get_truncated_polynominal() const;
    value_type  get_initial_remainder() const;
    value_type  get_final_xor_value() const;
    bool        get_reflect_input() const;
    bool        get_reflect_remainder() const;

    value_type  get_interim_remainder() const;
    void        reset( value_type new_rem = InitRem );

    // External Operations
    void  process_byte( unsigned char byte );
    void  process_block( void const *bytes_begin, void const *bytes_end );
    void  process_bytes( void const *buffer, std::size_t byte_count );

    value_type  checksum() const;

    // Operators
    void        operator ()( unsigned char byte );
    value_type  operator ()() const;

private:
    // The implementation of output reflection depends on both reflect states.
    BOOST_STATIC_CONSTANT( bool, reflect_output = (ReflectRem != ReflectIn) );

    #ifndef __BORLANDC__
    #define BOOST_CRC_REF_OUT_VAL  reflect_output
    #else
    typedef crc_optimal  self_type;
    #define BOOST_CRC_REF_OUT_VAL  (self_type::reflect_output)
    #endif

    // More implementation types
    typedef detail::crc_table_t<Bits, TruncPoly, ReflectIn>  crc_table_type;
    typedef detail::crc_helper<Bits, ReflectIn>              helper_type;
    typedef detail::crc_helper<Bits, BOOST_CRC_REF_OUT_VAL>  reflect_out_type;

    #undef BOOST_CRC_REF_OUT_VAL

    // Member data
    value_type  rem_;

};  // boost::crc_optimal


//  Implementation detail stuff  ---------------------------------------------//

namespace detail
{
    // Single-bit mask constant, MPL-style
    // (Template parameter is the 0-based index of the bit, i.e. 2**index.)
    template < int BitIndex >
    struct high_bit_mask_c
        : boost::mpl::integral_c<typename boost::uint_t< BitIndex + 1 >::fast,
           ( UINTMAX_C(1) << BitIndex )>
    {};

    // Lowest-bits mask constant, MPL-style
    // (Template parameter is the number of low bits set, i.e. 2**count - 1.)
    template < int BitCount >
    struct low_bits_mask_c
        : boost::mpl::integral_c<typename boost::uint_t< BitCount >::fast, (
           BitCount ? (( (( UINTMAX_C(1) << (BitCount - 1) ) - 1u) << 1 ) |
           UINTMAX_C( 1 )) : 0u )>
    {};

    // Bit-reflection functions
    template < typename Unsigned >
    Unsigned  reflect_unsigned( Unsigned x, int word_length
     = std::numeric_limits<Unsigned>::digits )
    {
        for ( Unsigned  l = 1u, h = l << (word_length - 1) ; h > l ; h >>= 1, l
         <<= 1 )
        {
            Unsigned const  m = h | l, t = x & m;

            if ( (t == h) || (t == l) )
                x ^= m;
        }

        return x;
    }

    unsigned char  reflect_byte_slowly( unsigned char x )
    { return reflect_unsigned(x); }

    boost::array< unsigned char, (UINTMAX_C( 1 ) << CHAR_BIT) >
    make_byte_reflection_table()
    {
        boost::array<unsigned char, ( UINTMAX_C(1) << CHAR_BIT )>  result;

        for ( boost::uint_t<CHAR_BIT + 1>::fast  i = 0u ; i <= UCHAR_MAX ; ++i )
            result[ i ] = reflect_byte_slowly( i );

        return result;
    }

    unsigned char  reflect_byte( unsigned char x )
    {
        static  boost::array<unsigned char, ( UINTMAX_C(1) << CHAR_BIT )> const
          table = make_byte_reflection_table();

        return table[ x ];
    }

    template < typename Unsigned >
    Unsigned  reflect_optionally( Unsigned x, bool reflect, int word_length
     = std::numeric_limits<Unsigned>::digits )
    { return reflect ? reflect_unsigned(x, word_length) : x; }

    unsigned char  reflect_byte_optionally( unsigned char x, bool reflect )
    { return reflect ? reflect_byte(x) : x; }

    // Encapsulate the core CRC computation routines
    template < int Bits, typename Register >
    bool  crc_modulo_update( Register &remainder, bool new_dividend_bit,
     Register truncated_divisor )
    {
        // compare the new bit with the remainder's highest
        remainder ^= new_dividend_bit ? high_bit_mask_c<Bits - 1>::value : 0u;

        // perform modulo-2 division
        bool const  quotient = remainder & high_bit_mask_c<Bits - 1>::value;

        remainder <<= 1;
        remainder ^= quotient ? truncated_divisor : 0u;
        return quotient;
    }

    template < int Bits, typename Register, typename Word >
    void  crc_modulo_word_update( Register &remainder, Word new_dividend_bits,
     Register truncated_divisor, int word_length, bool reflect )
    {
        // The natural reading order for division is highest digit/bit first.
        // The "reflect" parameter switches this.  However, building a bit mask
        // for the lowest bit is the easiest....
        new_dividend_bits = reflect_optionally( new_dividend_bits, not reflect,
         word_length );

        // Perform modulo-2 division
        for ( int  i = word_length ; i ; --i, new_dividend_bits >>= 1 )
            crc_modulo_update<Bits>( remainder, new_dividend_bits & 1u,
             truncated_divisor );

        // Note that the quotient isn't stored, since you usually won't need it,
        // and calculating it slows you down.  If you want it, just do this loop
        // manually.  Start with Word: Quotient := 0, then for each step do:
        //   Quotient <- (Quotient << 1) | crc_modulo_update(...)
    }


    // CRC table generator
    template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly, bool Reflect >
    struct crc_table_t
    {
        BOOST_STATIC_CONSTANT( std::size_t, byte_combos = (1ul << CHAR_BIT) );

        typedef typename boost::uint_t<Bits>::fast  value_type;
#if defined(__BORLANDC__) && defined(_M_IX86) && (__BORLANDC__ == 0x560)
        // for some reason Borland's command line compiler (version 0x560)
        // chokes over this unless we do the calculation for it:
        typedef value_type                   table_type[ 0x100 ];
#elif defined(__GNUC__)
        // old versions of GCC (before 4.0.2) choke on using byte_combos
        // as a constant expression when compiling with -pedantic.
        typedef value_type                   table_type[1ul << CHAR_BIT];
#else
        typedef value_type                   table_type[ byte_combos ];
#endif

        static  void  init_table();

        static  table_type  table_;

    };  // boost::detail::crc_table_t

    // CRC table generator static data member definition
    // (Some compilers [Borland C++] require the initializer to be present.)
    template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly, bool Reflect >
    typename crc_table_t<Bits, TruncPoly, Reflect>::table_type
    crc_table_t<Bits, TruncPoly, Reflect>::table_
     = { 0 };

    // Populate CRC lookup table
    template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly, bool Reflect >
    void
    crc_table_t<Bits, TruncPoly, Reflect>::init_table
    (
    )
    {
        // compute table only on the first run
        static  bool  did_init = false;
        if ( did_init )  return;

        // Loop over every possible dividend value
        for ( boost::uint_t<CHAR_BIT + 1>::fast  dividend = 0u ; dividend <=
         UCHAR_MAX ; ++dividend )
        {
            value_type  remainder = 0u;

            crc_modulo_word_update<Bits>( remainder, dividend, TruncPoly,
             CHAR_BIT, false );

            table_[ reflect_byte_optionally(dividend, Reflect) ]
             = reflect_optionally( remainder, Reflect, Bits );
        }

        did_init = true;
    }

    #ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    // Align the msb of the remainder to a byte
    template < std::size_t Bits, bool RightShift >
    class remainder
    {
    public:
        typedef typename uint_t<Bits>::fast  value_type;

        static unsigned char align_msb( value_type rem )
            { return rem >> (Bits - CHAR_BIT); }
    };

    // Specialization for the case that the remainder has less
    // bits than a byte: align the remainder msb to the byte msb
    template < std::size_t Bits >
    class remainder< Bits, false >
    {
    public:
        typedef typename uint_t<Bits>::fast  value_type;

        static unsigned char align_msb( value_type rem )
            { return rem << (CHAR_BIT - Bits); }
    };
    #endif

    // CRC helper routines
    template < std::size_t Bits, bool DoReflect >
    class crc_helper
    {
    public:
        // Type
        typedef typename uint_t<Bits>::fast  value_type;

    #ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        // Possibly reflect a remainder
        static  value_type  reflect( value_type x )
            { return reflect_unsigned(x, Bits); }

        // Compare a byte to the remainder's highest byte
        static  unsigned char  index( value_type rem, unsigned char x )
            { return x ^ rem; }

        // Shift out the remainder's highest byte
        static  value_type  shift( value_type rem )
            { return rem >> CHAR_BIT; }
    #else
        // Possibly reflect a remainder
        static  value_type  reflect( value_type x )
            { return DoReflect ? reflect_unsigned(x, Bits) : x; }

        // Compare a byte to the remainder's highest byte
        static  unsigned char  index( value_type rem, unsigned char x )
            { return x ^ ( DoReflect ? rem :
                                ((Bits>CHAR_BIT)?( rem >> (Bits - CHAR_BIT) ) :
                                    ( rem << (CHAR_BIT - Bits) ))); }

        // Shift out the remainder's highest byte
        static  value_type  shift( value_type rem )
            { return DoReflect ? rem >> CHAR_BIT : rem << CHAR_BIT; }
    #endif

    };  // boost::detail::crc_helper

    #ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template < std::size_t Bits >
    class crc_helper<Bits, false>
    {
    public:
        // Type
        typedef typename uint_t<Bits>::fast  value_type;

        // Possibly reflect a remainder
        static  value_type  reflect( value_type x )
            { return x; }

        // Compare a byte to the remainder's highest byte
        static  unsigned char  index( value_type rem, unsigned char x )
            { return x ^ remainder<Bits,(Bits>CHAR_BIT)>::align_msb( rem ); }

        // Shift out the remainder's highest byte
        static  value_type  shift( value_type rem )
            { return rem << CHAR_BIT; }

    };  // boost::detail::crc_helper
    #endif


}  // namespace detail


//  Simple CRC class function definitions  -----------------------------------//

template < std::size_t Bits >
inline
crc_basic<Bits>::crc_basic
(
    typename crc_basic<Bits>::value_type  truncated_polynominal,
    typename crc_basic<Bits>::value_type  initial_remainder,      // = 0
    typename crc_basic<Bits>::value_type  final_xor_value,        // = 0
    bool                                  reflect_input,          // = false
    bool                                  reflect_remainder       // = false
)
    : rem_( initial_remainder ), poly_( truncated_polynominal )
    , init_( initial_remainder ), final_( final_xor_value )
    , rft_in_( reflect_input ), rft_out_( reflect_remainder )
{
}

template < std::size_t Bits >
inline
typename crc_basic<Bits>::value_type
crc_basic<Bits>::get_truncated_polynominal
(
) const
{
    return poly_;
}

template < std::size_t Bits >
inline
typename crc_basic<Bits>::value_type
crc_basic<Bits>::get_initial_remainder
(
) const
{
    return init_;
}

template < std::size_t Bits >
inline
typename crc_basic<Bits>::value_type
crc_basic<Bits>::get_final_xor_value
(
) const
{
    return final_;
}

template < std::size_t Bits >
inline
bool
crc_basic<Bits>::get_reflect_input
(
) const
{
    return rft_in_;
}

template < std::size_t Bits >
inline
bool
crc_basic<Bits>::get_reflect_remainder
(
) const
{
    return rft_out_;
}

template < std::size_t Bits >
inline
typename crc_basic<Bits>::value_type
crc_basic<Bits>::get_interim_remainder
(
) const
{
    return rem_ & detail::low_bits_mask_c<Bits>::value;
}

template < std::size_t Bits >
inline
void
crc_basic<Bits>::reset
(
    typename crc_basic<Bits>::value_type  new_rem
)
{
    rem_ = new_rem;
}

template < std::size_t Bits >
inline
void
crc_basic<Bits>::reset
(
)
{
    this->reset( this->get_initial_remainder() );
}

template < std::size_t Bits >
inline
void
crc_basic<Bits>::process_bit
(
    bool  bit
)
{
    detail::crc_modulo_update<Bits>( rem_, bit, poly_ );
}

template < std::size_t Bits >
void
crc_basic<Bits>::process_bits
(
    unsigned char  bits,
    std::size_t    bit_count
)
{
    // ignore the bits above the ones we want
    bits <<= CHAR_BIT - bit_count;

    // compute the CRC for each bit, starting with the upper ones
    unsigned char const  high_bit_mask = 1u << ( CHAR_BIT - 1u );
    for ( std::size_t i = bit_count ; i > 0u ; --i, bits <<= 1u )
    {
        process_bit( static_cast<bool>(bits & high_bit_mask) );
    }
}

template < std::size_t Bits >
inline
void
crc_basic<Bits>::process_byte
(
    unsigned char  byte
)
{
    process_bits( (rft_in_ ? detail::reflect_byte( byte ) : byte), CHAR_BIT );
}

template < std::size_t Bits >
void
crc_basic<Bits>::process_block
(
    void const *  bytes_begin,
    void const *  bytes_end
)
{
    for ( unsigned char const * p
     = static_cast<unsigned char const *>(bytes_begin) ; p < bytes_end ; ++p )
    {
        process_byte( *p );
    }
}

template < std::size_t Bits >
inline
void
crc_basic<Bits>::process_bytes
(
    void const *  buffer,
    std::size_t   byte_count
)
{
    unsigned char const * const  b = static_cast<unsigned char const *>(
     buffer );

    process_block( b, b + byte_count );
}

template < std::size_t Bits >
inline
typename crc_basic<Bits>::value_type
crc_basic<Bits>::checksum
(
) const
{
    return ( (rft_out_ ? detail::reflect_unsigned( rem_, Bits ) :
     rem_) ^ final_ ) & detail::low_bits_mask_c<Bits>::value;
}


//  Optimized CRC class function definitions  --------------------------------//

// Macro to compact code
#define BOOST_CRC_OPTIMAL_NAME  crc_optimal<Bits, TruncPoly, InitRem, \
 FinalXor, ReflectIn, ReflectRem>

template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
BOOST_CRC_OPTIMAL_NAME::crc_optimal
(
    typename BOOST_CRC_OPTIMAL_NAME::value_type  init_rem  // = InitRem
)
    : rem_( helper_type::reflect(init_rem) )
{
    crc_table_type::init_table();
}

template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
typename BOOST_CRC_OPTIMAL_NAME::value_type
BOOST_CRC_OPTIMAL_NAME::get_truncated_polynominal
(
) const
{
    return TruncPoly;
}

template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
typename BOOST_CRC_OPTIMAL_NAME::value_type
BOOST_CRC_OPTIMAL_NAME::get_initial_remainder
(
) const
{
    return InitRem;
}

template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
typename BOOST_CRC_OPTIMAL_NAME::value_type
BOOST_CRC_OPTIMAL_NAME::get_final_xor_value
(
) const
{
    return FinalXor;
}

template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
bool
BOOST_CRC_OPTIMAL_NAME::get_reflect_input
(
) const
{
    return ReflectIn;
}

template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
bool
BOOST_CRC_OPTIMAL_NAME::get_reflect_remainder
(
) const
{
    return ReflectRem;
}

template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
typename BOOST_CRC_OPTIMAL_NAME::value_type
BOOST_CRC_OPTIMAL_NAME::get_interim_remainder
(
) const
{
    // Interim remainder should be _un_-reflected, so we have to undo it.
    return helper_type::reflect( rem_ ) & detail::low_bits_mask_c<Bits>::value;
}

template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
void
BOOST_CRC_OPTIMAL_NAME::reset
(
    typename BOOST_CRC_OPTIMAL_NAME::value_type  new_rem  // = InitRem
)
{
    rem_ = helper_type::reflect( new_rem );
}

template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
void
BOOST_CRC_OPTIMAL_NAME::process_byte
(
    unsigned char  byte
)
{
    process_bytes( &byte, sizeof(byte) );
}

template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
void
BOOST_CRC_OPTIMAL_NAME::process_block
(
    void const *  bytes_begin,
    void const *  bytes_end
)
{
    // Recompute the CRC for each byte passed
    for ( unsigned char const * p
     = static_cast<unsigned char const *>(bytes_begin) ; p < bytes_end ; ++p )
    {
        // Compare the new byte with the remainder's higher bits to
        // get the new bits, shift out the remainder's current higher
        // bits, and update the remainder with the polynominal division
        // of the new bits.
        unsigned char const  byte_index = helper_type::index( rem_, *p );
        rem_ = helper_type::shift( rem_ );
        rem_ ^= crc_table_type::table_[ byte_index ];
    }
}

template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
void
BOOST_CRC_OPTIMAL_NAME::process_bytes
(
    void const *   buffer,
    std::size_t  byte_count
)
{
    unsigned char const * const  b = static_cast<unsigned char const *>(
     buffer );
    process_block( b, b + byte_count );
}

template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
typename BOOST_CRC_OPTIMAL_NAME::value_type
BOOST_CRC_OPTIMAL_NAME::checksum
(
) const
{
    return ( reflect_out_type::reflect(rem_) ^ get_final_xor_value() )
     & detail::low_bits_mask_c<Bits>::value;
}

template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
void
BOOST_CRC_OPTIMAL_NAME::operator ()
(
    unsigned char  byte
)
{
    process_byte( byte );
}

template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
typename BOOST_CRC_OPTIMAL_NAME::value_type
BOOST_CRC_OPTIMAL_NAME::operator ()
(
) const
{
    return checksum();
}


//  CRC computation function definition  -------------------------------------//

template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly,
           BOOST_CRC_PARM_TYPE InitRem, BOOST_CRC_PARM_TYPE FinalXor,
           bool ReflectIn, bool ReflectRem >
inline
typename uint_t<Bits>::fast
crc
(
    void const *  buffer,
    std::size_t   byte_count
    BOOST_CRC_DUMMY_INIT
)
{
    BOOST_CRC_OPTIMAL_NAME  computer;
    computer.process_bytes( buffer, byte_count );
    return computer.checksum();
}


//  Augmented-message CRC computation function definitions  ------------------//

template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly >
typename uint_t<Bits>::fast
augmented_crc
(
    void const *                 buffer,
    std::size_t                  byte_count,
    typename uint_t<Bits>::fast  initial_remainder
    BOOST_ACRC_DUMMY_INIT
)
{
    typedef unsigned char                                byte_type;
    typedef detail::crc_table_t<Bits, TruncPoly, false>  crc_table_type;

    typename uint_t<Bits>::fast  rem = initial_remainder;
    byte_type const * const      b = static_cast<byte_type const *>( buffer );
    byte_type const * const      e = b + byte_count;

    crc_table_type::init_table();
    for ( byte_type const * p = b ; p < e ; ++p )
    {
        // Use the current top byte as the table index to the next
        // "partial product."  Shift out that top byte, shifting in
        // the next augmented-message byte.  Complete the division.
        byte_type const  byte_index = rem >> ( Bits - CHAR_BIT );
        rem <<= CHAR_BIT;
        rem |= *p;
        rem ^= crc_table_type::table_[ byte_index ];
    }

    return rem & detail::low_bits_mask_c<Bits>::value;
}

template < std::size_t Bits, BOOST_CRC_PARM_TYPE TruncPoly >
inline
typename uint_t<Bits>::fast
augmented_crc
(
    void const *  buffer,
    std::size_t   byte_count
    BOOST_ACRC_DUMMY_INIT
)
{
   // The last function argument has its type specified so the other version of
   // augmented_crc will be called.  If the cast wasn't in place, and the
   // BOOST_ACRC_DUMMY_INIT added a third argument (for a workaround), the "0"
   // would match as that third argument, leading to infinite recursion.
   return augmented_crc<Bits, TruncPoly>( buffer, byte_count,
    static_cast<typename uint_t<Bits>::fast>(0) );
}


}  // namespace boost


// Undo header-private macros
#undef BOOST_CRC_OPTIMAL_NAME
#undef BOOST_ACRC_DUMMY_INIT
#undef BOOST_ACRC_DUMMY_PARM_TYPE
#undef BOOST_CRC_DUMMY_INIT
#undef BOOST_CRC_DUMMY_PARM_TYPE
#undef BOOST_CRC_PARM_TYPE


#endif  // BOOST_CRC_HPP


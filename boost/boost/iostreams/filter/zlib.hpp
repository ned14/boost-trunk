// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_ZLIB_HPP_INCLUDED
#define BOOST_IOSTREAMS_ZLIB_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              

#include <cassert>                            
#include <ios>                // failure.
#include <memory>             // allocator, bad_alloc.
#include <new>          
#include <boost/config.hpp>   // MSVC, STATIC_CONSTANT, DEDUCED_TYPENAME
#include <boost/iostreams/constants.hpp>  // buffer size.
#include <boost/iostreams/detail/config/auto_link.hpp>
#include <boost/iostreams/detail/config/dyn_link.hpp>
#include <boost/iostreams/detail/config/zlib.hpp>
#include <boost/iostreams/filter/symmetric_filter_adapter.hpp>                
#include <boost/iostreams/pipable.hpp>                
#include <boost/type_traits/is_same.hpp>      

// Must come last.
#ifdef BOOST_MSVC
# pragma warning(push)
# pragma warning(disable:4251 4231 4660)         // Dependencies not exported.
#endif
#include <boost/config/abi_prefix.hpp>           

namespace boost { namespace iostreams {

namespace zlib {
                    // Typedefs

typedef unsigned uint;
typedef unsigned char byte;
typedef unsigned long ulong;
typedef void* alloc_func(void*, zlib::uint, zlib::uint);
typedef void free_func(void*, void*);

                    // Compression levels

BOOST_IOSTREAMS_DECL extern const int no_compression;
BOOST_IOSTREAMS_DECL extern const int best_speed;
BOOST_IOSTREAMS_DECL extern const int best_compression;
BOOST_IOSTREAMS_DECL extern const int default_compression;

                    // Compression methods

BOOST_IOSTREAMS_DECL extern const int deflated;

                    // Compression strategies

BOOST_IOSTREAMS_DECL extern const int default_strategy;
BOOST_IOSTREAMS_DECL extern const int filtered;
BOOST_IOSTREAMS_DECL extern const int huffman_only;

                    // Status codes

BOOST_IOSTREAMS_DECL extern const int okay;
BOOST_IOSTREAMS_DECL extern const int stream_end;
BOOST_IOSTREAMS_DECL extern const int stream_error;
BOOST_IOSTREAMS_DECL extern const int version_error;
BOOST_IOSTREAMS_DECL extern const int data_error;
BOOST_IOSTREAMS_DECL extern const int mem_error;
BOOST_IOSTREAMS_DECL extern const int buf_error;

                    // Flush codes

BOOST_IOSTREAMS_DECL extern const int finish;
BOOST_IOSTREAMS_DECL extern const int no_flush;

                    // Code for current OS

//BOOST_IOSTREAMS_DECL extern const int os_code;

                    // Null pointer constant.

const int null                               = 0;

                    // Default values

const int default_window_bits                = 15;
const int default_mem_level                  = 8;
const bool default_crc                       = false;
const bool default_noheader                  = false;

} // End namespace zlib. 

//
// Class name: zlib_params.
// Description: Encapsulates the parameters passed to deflateInit2
//      and inflateInit2 to customize compression and decompression.
//
struct zlib_params {

    // Non-explicit constructor.
    zlib_params( int level           = zlib::default_compression,
                 int method          = zlib::deflated,
                 int window_bits     = zlib::default_window_bits, 
                 int mem_level       = zlib::default_mem_level, 
                 int strategy        = zlib::default_strategy,
                 bool noheader       = zlib::default_noheader,
                 bool calculate_crc  = zlib::default_crc )
        : level(level), method(method), window_bits(window_bits),
          mem_level(mem_level), strategy(strategy),  
          noheader(noheader), calculate_crc(zlib::default_crc)
        { }
    int level;
    int method;
    int window_bits;
    int mem_level;
    int strategy;
    bool noheader;
    bool calculate_crc;
};

//
// Class name: zlib_error.
// Description: Subclass of std::ios::failure thrown to indicate
//     zlib errors other than out-of-memory conditions.
//
class BOOST_IOSTREAMS_DECL zlib_error : public std::ios_base::failure {
public:
    zlib_error(int error);
    int error() const { return error_; }
    static void check(int error);
private:
    int error_;
};

namespace detail {

template<typename Alloc>
struct zlib_allocator_traits {
#ifndef BOOST_NO_STD_ALLOCATOR
    typedef typename Alloc::template rebind<char>::other type;
#else
    typedef std::allocator<char> type;
#endif
};

template< typename Alloc,
          typename Base = // VC6 workaround (C2516)
              BOOST_DEDUCED_TYPENAME zlib_allocator_traits<Alloc>::type >
struct zlib_allocator : private Base {
private:
    typedef typename Base::size_type size_type;
public:
    BOOST_STATIC_CONSTANT(bool, custom = 
        (!is_same<std::allocator<char>, Base>::value));
    typedef typename zlib_allocator_traits<Alloc>::type allocator_type;
    static void* alloc(void* self, zlib::uint items, zlib::uint size);
    static void free(void* self, void* address);
};

class BOOST_IOSTREAMS_DECL zlib_base { 
public:
    typedef char char_type;
protected:
    zlib_base();
    ~zlib_base();
    void* stream() { return stream_; }
    template<typename Alloc> 
    void init( const zlib_params& p, 
               bool compress,
               zlib_allocator<Alloc>& alloc )
        {
            bool custom = zlib_allocator<Alloc>::custom;
            do_init( p, compress,
                     custom ? zlib_allocator<Alloc>::alloc : 0,
                     custom ? zlib_allocator<Alloc>::free : 0,
                     &alloc );
        }
    void before( const char*& src_begin, const char* src_end,
                 char*& dest_begin, char* dest_end );
    void after( const char*& src_begin, char*& dest_begin, 
                bool compress );
    int deflate(int flush);
    int inflate(int flush);
    void reset(bool compress);
public:
    zlib::ulong crc() const { return crc_; }
    int total_in() const { return total_in_; }
    int total_out() const { return total_out_; }
private:
    void do_init( const zlib_params& p, bool compress, zlib::alloc_func, 
                  zlib::free_func, void* derived );
    void*        stream_;         // Actual type: z_stream*.
    bool         calculate_crc_;
    zlib::ulong  crc_;
    int          total_in_;
    int          total_out_;
};

//
// Template name: zlib_compressor_impl
// Description: Model of C-Style Filte implementing compression by
//      delegating to the zlib function deflate.
//
template<typename Alloc = std::allocator<char> >
class zlib_compressor_impl : public zlib_base, public zlib_allocator<Alloc> { 
public: 
    zlib_compressor_impl(const zlib_params& = zlib::default_compression);
    bool filter( const char*& src_begin, const char* src_end,
                 char*& dest_begin, char* dest_end, bool flush );
    void close();
};

//
// Template name: zlib_compressor
// Description: Model of C-Style Filte implementing decompression by
//      delegating to the zlib function inflate.
//
template<typename Alloc = std::allocator<char> >
class zlib_decompressor_impl : public zlib_base, public zlib_allocator<Alloc> {
public:
    zlib_decompressor_impl(const zlib_params&);
    zlib_decompressor_impl(int window_bits = zlib::default_window_bits);
    bool filter( const char*& begin_in, const char* end_in,
                 char*& begin_out, char* end_out, bool flush );
    void close();
};

} // End namespace detail.

//
// Template name: zlib_compressor
// Description: Model of InputFilter and OutputFilter implementing
//      compression using zlib.
//
template<typename Alloc = std::allocator<char> >
struct basic_zlib_compressor 
    : symmetric_filter_adapter<detail::zlib_compressor_impl<Alloc>, Alloc> 
{
private:
    typedef detail::zlib_compressor_impl<Alloc>         impl_type;
    typedef symmetric_filter_adapter<impl_type, Alloc>  base_type;
public:
    typedef typename base_type::char_type               char_type;
    typedef typename base_type::io_category             io_category;
    basic_zlib_compressor( const zlib_params& = zlib::default_compression, 
                           std::streamsize buffer_size = default_buffer_size );
                           // Note: use large buffer.
    zlib::ulong crc() { return this->filter().crc(); }
    int total_in() {  return this->filter().total_in(); }
};
BOOST_IOSTREAMS_PIPABLE(basic_zlib_compressor, 1)

typedef basic_zlib_compressor<> zlib_compressor;

//
// Template name: zlib_decompressor
// Description: Model of InputFilter and OutputFilter implementing
//      decompression using zlib.
//
template<typename Alloc = std::allocator<char> >
struct basic_zlib_decompressor 
    : symmetric_filter_adapter<detail::zlib_decompressor_impl<Alloc>, Alloc> 
{
private:
    typedef detail::zlib_decompressor_impl<Alloc>       impl_type;
    typedef symmetric_filter_adapter<impl_type, Alloc>  base_type;
public:
    typedef typename base_type::char_type               char_type;
    typedef typename base_type::io_category             io_category;
    basic_zlib_decompressor( int window_bits = zlib::default_window_bits,
                             std::streamsize buffer_size = 
                                 default_buffer_size );
    basic_zlib_decompressor( const zlib_params& p,
                             std::streamsize buffer_size = 
                                 default_buffer_size );
                                 // Note: use large buffer.
    zlib::ulong crc() { return this->filter().crc(); }
    int total_out() {  return this->filter().total_out(); }
};
BOOST_IOSTREAMS_PIPABLE(basic_zlib_decompressor, 1)

typedef basic_zlib_decompressor<> zlib_decompressor;

//----------------------------------------------------------------------------//

//------------------Implementation of zlib_allocator--------------------------//

namespace detail {

template<typename Alloc>
void* zlib_allocator<Alloc>::alloc(void* self, zlib::uint items, zlib::uint size)
{ 
    size_type len = items * size;
    char* ptr = 
        static_cast<allocator_type*>(self)->allocate(len + sizeof(size_type)); 
    *reinterpret_cast<size_type*>(ptr) = len;
    return ptr + sizeof(size_type);
}

template<typename Alloc>
void zlib_allocator<Alloc>::free(void* self, void* address)
{ 
    char* ptr = reinterpret_cast<char*>(address) - sizeof(size_type);
    size_type len = *reinterpret_cast<size_type*>(ptr) + sizeof(size_type);
    static_cast<allocator_type*>(self)->deallocate(ptr, len); 
}

//------------------Implementation of zlib_compressor_impl--------------------//

template<typename Alloc>
zlib_compressor_impl<Alloc>::zlib_compressor_impl(const zlib_params& p)
{ init(p, true, static_cast<zlib_allocator<Alloc>&>(*this)); }

template<typename Alloc>
bool zlib_compressor_impl<Alloc>::filter
    ( const char*& src_begin, const char* src_end,
      char*& dest_begin, char* dest_end, bool flush )
{
    before(src_begin, src_end, dest_begin, dest_end);
    int result = deflate(flush ? zlib::finish : zlib::no_flush);
    after(src_begin, dest_begin, true);
    zlib_error::check(result);
    return result != zlib::stream_end; 
}

template<typename Alloc>
void zlib_compressor_impl<Alloc>::close() { reset(true); }

//------------------Implementation of zlib_decompressor_impl------------------//

template<typename Alloc>
zlib_decompressor_impl<Alloc>::zlib_decompressor_impl(const zlib_params& p)
{ init(p, false, static_cast<zlib_allocator<Alloc>&>(*this)); }

template<typename Alloc>
zlib_decompressor_impl<Alloc>::zlib_decompressor_impl(int window_bits)
{ 
    zlib_params p;
    p.window_bits = window_bits;
    init(p, false, static_cast<zlib_allocator<Alloc>&>(*this)); 
}

template<typename Alloc>
bool zlib_decompressor_impl<Alloc>::filter
    ( const char*& src_begin, const char* src_end,
      char*& dest_begin, char* dest_end, bool flush )
{
    before(src_begin, src_end, dest_begin, dest_end);
    int result = inflate(zlib::no_flush);
    after(src_begin, dest_begin, false);
    zlib_error::check(result);
    return result != zlib::stream_end; 
}

template<typename Alloc>
void zlib_decompressor_impl<Alloc>::close() { reset(false); }

} // End namespace detail.

//------------------Implementation of zlib_decompressor-----------------------//

template<typename Alloc>
basic_zlib_compressor<Alloc>::basic_zlib_compressor
    (const zlib_params& p, std::streamsize buffer_size) 
    : base_type(new impl_type(p), buffer_size) { }

//------------------Implementation of zlib_decompressor-----------------------//

template<typename Alloc>
basic_zlib_decompressor<Alloc>::basic_zlib_decompressor
    (int window_bits, std::streamsize buffer_size) 
    : base_type(new impl_type(window_bits), buffer_size) { }

template<typename Alloc>
basic_zlib_decompressor<Alloc>::basic_zlib_decompressor
    (const zlib_params& p, std::streamsize buffer_size) 
    : base_type(new impl_type(p), buffer_size) { }

//----------------------------------------------------------------------------//

} } // End namespaces iostreams, boost.

#include <boost/config/abi_suffix.hpp> // Pops abi_suffix.hpp pragmas.
#ifdef BOOST_MSVC
# pragma warning(pop)
#endif

#endif // #ifndef BOOST_IOSTREAMS_ZLIB_HPP_INCLUDED

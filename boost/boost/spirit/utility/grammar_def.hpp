/*=============================================================================
    Copyright (c) 2003 Hartmut Kaiser
    Copyright (c) 2003 Joel de Guzman
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_GRAMMAR_DEF_HPP)
#define BOOST_SPIRIT_GRAMMAR_DEF_HPP

#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/enum.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/repeat_from_to.hpp>
#include <boost/fusion/sequence/container/vector.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/spirit/core/assert.hpp>
#include <boost/spirit/utility/grammar_def_fwd.hpp>

///////////////////////////////////////////////////////////////////////////////
//
//  Spirit predefined maximum grammar start parser limit. This limit defines
//  the maximum number of of possible different parsers exposed from a
//  particular grammar. This number defaults to 3.
//  The actual maximum is rounded up in multiples of 3. Thus, if this value
//  is 4, the actual limit is 6. The ultimate maximum limit in this
//  implementation is 15.
//
//  It should NOT be greater than PHOENIX_LIMIT!
//
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_SPIRIT_GRAMMAR_STARTRULE_TYPE_LIMIT)
#define BOOST_SPIRIT_GRAMMAR_STARTRULE_TYPE_LIMIT PHOENIX_LIMIT
#endif

///////////////////////////////////////////////////////////////////////////////
//
// ensure BOOST_SPIRIT_GRAMMAR_STARTRULE_TYPE_LIMIT <= PHOENIX_LIMIT and
//
///////////////////////////////////////////////////////////////////////////////
BOOST_STATIC_ASSERT(BOOST_SPIRIT_GRAMMAR_STARTRULE_TYPE_LIMIT <= PHOENIX_LIMIT);

namespace boost { namespace fusion 
{    
    struct void_;
}}

namespace boost { namespace phoenix 
{    
    typedef fusion::void_ void_;
}}

//////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

struct same {};

///////////////////////////////////////////////////////////////////////////////
namespace impl {

    ///////////////////////////////////////////////////////////////////////////
    //
    //  The make_const_pointer meta function allows to generate a T const*
    //  needed to store the pointer to a given start parser from a grammar.
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename T0, typename T = T0>
    struct make_const_pointer {

    private:
        // T0 shouldn't be of type 'same'
        BOOST_STATIC_ASSERT((!boost::is_same<T0, same>::value));

        typedef typename boost::mpl::if_c<
                    boost::is_same<T, same>::value,
                    T0 const *,
                    T const *
                >::type
            ptr_type;

    public:
        // If the type in question is phoenix::void_, then the returned type
        // is still phoenix::void_, otherwise a constant pointer type to the
        // inspected type is returned.
        typedef typename boost::mpl::if_c<
                    boost::is_same<T, phoenix::void_>::value,
                    phoenix::void_,
                    ptr_type
                >::type
            type;
    };

    ///////////////////////////////////////////////////////////////////////////
    template <int N, typename ElementT>
    struct assign_zero_to_tuple_member {

        template <typename TupleT>
        static void do_(TupleT &t) { fusion::at_c<N>(t) = 0; }
    };

    template <int N>
    struct assign_zero_to_tuple_member<N, phoenix::void_> {

        template <typename TupleT>
        static void do_(TupleT& /*t*/) {}
    };

    struct phoenix_nil_type {

        typedef phoenix::void_ type;
    };

    template <int N>
    struct init_tuple_member {

        template <typename TupleT>
        static void
        do_(TupleT &t)
        {
            typedef typename boost::mpl::eval_if_c<
                        (N < fusion::result_of::size<TupleT>::value),
                        fusion::result_of::value_at_c<TupleT, N>,
                        phoenix_nil_type
                    >::type
                element_type;

            assign_zero_to_tuple_member<N, element_type>::do_(t);
        }
    };

///////////////////////////////////////////////////////////////////////////////
}   // namespace impl

///////////////////////////////////////////////////////////////////////////////
//
//  grammar_def class
//
//      This class may be used as a base class for the embedded definition
//      class inside the grammar<> derived user grammar.
//      It exposes the two functions needed for start rule access:
//
//          rule<> const &start() const;
//
//      and
//
//          template <int N>
//          rule<> const *get_start_parser() const;
//
//      Additionally it exposes a set o 'start_parsers' functions, which are to
//      be called by the user to define the parsers to use as start parsers
//      of the given grammar.
//
///////////////////////////////////////////////////////////////////////////////
template <
    typename T,
    BOOST_PP_ENUM_PARAMS(
        BOOST_PP_DEC(BOOST_SPIRIT_GRAMMAR_STARTRULE_TYPE_LIMIT), typename T)
>
class grammar_def {

private:
    ///////////////////////////////////////////////////////////////////////////
    //
    //  This generates the full tuple type from the given template parameters
    //  T, T0, ...
    //
    //      typedef phoenix::tuple<
    //              typename impl::make_const_pointer<T>::type,
    //              typename impl::make_const_pointer<T, T0>::type,
    //              ...
    //          > tuple_t;
    //
    ///////////////////////////////////////////////////////////////////////////
    #define BOOST_SPIRIT_GRAMMARDEF_TUPLE_PARAM(z, N, _) \
        typename impl::make_const_pointer<T, BOOST_PP_CAT(T, N)>::type \
        /**/

    typedef fusion::vector<
            typename impl::make_const_pointer<T>::type,
            BOOST_PP_ENUM(
                BOOST_PP_DEC(BOOST_SPIRIT_GRAMMAR_STARTRULE_TYPE_LIMIT),
                BOOST_SPIRIT_GRAMMARDEF_TUPLE_PARAM,
                _
            )
        > tuple_t;

    #undef BOOST_SPIRIT_GRAMMARDEF_TUPLE_PARAM
    ///////////////////////////////////////////////////////////////////////////

protected:
    ///////////////////////////////////////////////////////////////////////////
    //
    //  This generates a sequence of 'start_parsers' functions with increasing
    //  number of arguments, which allow to initialize the tuple members with
    //  the pointers to the start parsers of the grammar:
    //
    //      template <typename TC0, ...>
    //      void start_parsers (TC0 const &t0, ...)
    //      {
    //          fusion::at_c<0>(t) = &t0;
    //          ...
    //      }
    //
    //      where a TC0 const* must be convertible to a T0 const*
    //
    ///////////////////////////////////////////////////////////////////////////
    #define BOOST_SPIRIT_GRAMMARDEF_ENUM_PARAMS(z, N, _) \
        BOOST_PP_CAT(TC, N) const &BOOST_PP_CAT(t, N) \
        /**/
    #define BOOST_SPIRIT_GRAMMARDEF_ENUM_ASSIGN(z, N, _) \
        fusion::at_c<N>(t) = &BOOST_PP_CAT(t, N); \
        /**/
    #define BOOST_SPIRIT_GRAMMARDEF_ENUM_START(z, N, _) \
        template <BOOST_PP_ENUM_PARAMS_Z(z, BOOST_PP_INC(N), typename TC)> \
        void \
        start_parsers(BOOST_PP_ENUM_ ## z(BOOST_PP_INC(N), \
            BOOST_SPIRIT_GRAMMARDEF_ENUM_PARAMS, _) ) \
        { \
            BOOST_PP_REPEAT_ ## z(BOOST_PP_INC(N), \
                BOOST_SPIRIT_GRAMMARDEF_ENUM_ASSIGN, _) \
        } \
        /**/

    BOOST_PP_REPEAT(
        BOOST_SPIRIT_GRAMMAR_STARTRULE_TYPE_LIMIT,
        BOOST_SPIRIT_GRAMMARDEF_ENUM_START, _)

    #undef BOOST_SPIRIT_GRAMMARDEF_ENUM_START
    #undef BOOST_SPIRIT_GRAMMARDEF_ENUM_ASSIGN
    #undef BOOST_SPIRIT_GRAMMARDEF_ENUM_PARAMS
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    //
    //  This generates some initialization code, which allows to initialize all
    //  used tuple members to 0 (zero):
    //
    //      t[_1] = 0;
    //      impl::init_tuple_member<1>::do_(t);
    //      ...
    //
    ///////////////////////////////////////////////////////////////////////////
    #define BOOST_SPIRIT_GRAMMARDEF_ENUM_INIT(z, N, _) \
        impl::init_tuple_member<N>::do_(t); \
        /**/

    grammar_def()
    {
        fusion::at_c<0>(t) = 0;
        BOOST_PP_REPEAT_FROM_TO(
            1, BOOST_SPIRIT_GRAMMAR_STARTRULE_TYPE_LIMIT,
            BOOST_SPIRIT_GRAMMARDEF_ENUM_INIT, _)
    }

    #undef BOOST_SPIRIT_GRAMMARDEF_ENUM_INIT
    ///////////////////////////////////////////////////////////////////////////

public:
    T const &
    start() const
    {
    //  If the following assertion is fired, you have probably forgot to call
    //  the start_parser() function from inside the constructor of your
    //  embedded definition class to initialize the start parsers to be exposed
    //  from your grammar.
        BOOST_SPIRIT_ASSERT(0 != fusion::at_c<0>(t));
        return *fusion::at_c<0>(t);
    }

    template <int N>
    typename fusion::result_of::at_c<tuple_t const, N>::type
    get_start_parser() const
    {
    //  If the following expression yields a compiler error, you have probably
    //  tried to access a start rule, which isn't exposed as such from your
    //  grammar.
        BOOST_STATIC_ASSERT(N > 0 && N < fusion::result_of::size<tuple_t>::value);

    //  If the following assertion is fired, you have probably forgot to call
    //  the start_parser() function from inside the constructor of your
    //  embedded definition class to initialize the start parsers to be exposed
    //  from your grammar.
    //  Another reason may be, that there is a count mismatch between
    //  the number of template parameters to the grammar_def<> class and the
    //  number of parameters used while calling start_parsers().
        BOOST_SPIRIT_ASSERT(0 != fusion::at_c<N>(t));

        return fusion::at_c<N>(t);
    }

private:
    tuple_t t;
};

#undef BOOST_SPIRIT_GRAMMAR_STARTRULE_TYPE_LIMIT

}} // namespace boost::spirit

#endif // BOOST_SPIRIT_GRAMMAR_DEF_HPP

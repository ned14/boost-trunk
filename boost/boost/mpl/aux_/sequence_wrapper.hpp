
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_AUX_SEQUENCE_WRAPPER_HPP_INCLUDED
#define BOOST_MPL_AUX_SEQUENCE_WRAPPER_HPP_INCLUDED

// Copyright (c) Aleksey Gurtovoy 2000-2004
//
// Use, modification and distribution are subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy 
// at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#   include <boost/mpl/aux_/config/ctps.hpp>
#   include <boost/mpl/aux_/config/nttp.hpp>

#   include <boost/preprocessor/arithmetic/sub.hpp>
#   include <boost/preprocessor/tuple/elem.hpp>
#   include <boost/preprocessor/enum_params_with_a_default.hpp>
#   include <boost/preprocessor/enum_params.hpp>
#   include <boost/preprocessor/enum.hpp>
#   include <boost/preprocessor/repeat.hpp>
#   include <boost/preprocessor/comma_if.hpp>
#   include <boost/preprocessor/iterate.hpp>

namespace boost { namespace mpl {

#   define AUX778076_SEQUENCE_PARAMS(param) \
    BOOST_PP_ENUM_PARAMS( \
          AUX778076_SEQUENCE_LIMIT \
        , param \
        ) \
    /**/

#   define AUX778076_SEQUENCE_DEFAULT_PARAMS(param, value) \
     BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT( \
          AUX778076_SEQUENCE_LIMIT \
        , param \
        , value \
        ) \
    /**/

#   define AUX778076_SEQUENCE_N_PARAMS(n, param) \
    BOOST_PP_ENUM_PARAMS(n, param) \
    /**/

#   define AUX778076_SEQUENCE_N_PARTIAL_SPEC_PARAMS(n, param, def) \
    BOOST_PP_ENUM_PARAMS(n, param) \
    BOOST_PP_COMMA_IF(n) \
    BOOST_PP_ENUM( \
          BOOST_PP_SUB_D(1,AUX778076_SEQUENCE_LIMIT,n) \
        , BOOST_PP_TUPLE_ELEM_3_2 \
        , def \
        ) \
    /**/

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
// forward declaration
template<
      AUX778076_SEQUENCE_DEFAULT_PARAMS(typename T, na)
    >
struct AUX778076_SEQUENCE_NAME;
#else
namespace aux {
template< BOOST_MPL_AUX_NTTP_DECL(int, N) > 
struct BOOST_PP_CAT(AUX778076_SEQUENCE_NAME,_chooser);
}
#endif

#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, AUX778076_SEQUENCE_LIMIT, <boost/mpl/aux_/sequence_wrapper.hpp>))
#include BOOST_PP_ITERATE()

// real C++ version is already taken care of
#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

namespace aux {
// ???_count_args
#define AUX778076_COUNT_ARGS_PREFIX AUX778076_SEQUENCE_NAME
#define AUX778076_COUNT_ARGS_DEFAULT na
#define AUX778076_COUNT_ARGS_ARITY AUX778076_SEQUENCE_LIMIT
#define AUX778076_COUNT_ARGS_USE_STANDARD_PP_PRIMITIVES
#include <boost/mpl/aux_/count_args.hpp>

template<
      AUX778076_SEQUENCE_PARAMS(typename T)
    >
struct BOOST_PP_CAT(AUX778076_SEQUENCE_NAME,_impl)
{
    typedef aux::BOOST_PP_CAT(AUX778076_SEQUENCE_NAME,_count_args)<
          AUX778076_SEQUENCE_PARAMS(T)
        > arg_num_;
    
    typedef typename aux::BOOST_PP_CAT(AUX778076_SEQUENCE_NAME,_chooser)< arg_num_::value >
        ::template result_< AUX778076_SEQUENCE_PARAMS(T) >::type type;
};

} // namespace aux

template<
      AUX778076_SEQUENCE_DEFAULT_PARAMS(typename T, na)
    >
struct AUX778076_SEQUENCE_NAME
    : aux::BOOST_PP_CAT(AUX778076_SEQUENCE_NAME,_impl)< AUX778076_SEQUENCE_PARAMS(T) >::type
{
    typedef typename aux::BOOST_PP_CAT(AUX778076_SEQUENCE_NAME,_impl)<
          AUX778076_SEQUENCE_PARAMS(T)
        >::type type;
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#   undef AUX778076_SEQUENCE_N_PARTIAL_SPEC_PARAMS
#   undef AUX778076_SEQUENCE_N_PARAMS
#   undef AUX778076_SEQUENCE_DEFAULT_PARAMS
#   undef AUX778076_SEQUENCE_PARAMS
#   undef AUX778076_SEQUENCE_NAME
#   undef AUX778076_SEQUENCE_LIMIT

}}

#endif // BOOST_MPL_AUX_SEQUENCE_WRAPPER_HPP_INCLUDED

///// iteration

#else
#define i_ BOOST_PP_FRAME_ITERATION(1)

#   if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

#if i_ == AUX778076_SEQUENCE_LIMIT

//: primary template (not a specialization!)
template<
      AUX778076_SEQUENCE_N_PARAMS(i_, typename T)
    >
struct AUX778076_SEQUENCE_NAME
    : BOOST_PP_CAT(AUX778076_SEQUENCE_NAME,i_)< AUX778076_SEQUENCE_N_PARAMS(i_, T) >
{
    typedef BOOST_PP_CAT(AUX778076_SEQUENCE_NAME,i_)< AUX778076_SEQUENCE_N_PARAMS(i_, T) > type;
};

#else

template<
      AUX778076_SEQUENCE_N_PARAMS(i_, typename T)
    >
struct AUX778076_SEQUENCE_NAME< AUX778076_SEQUENCE_N_PARTIAL_SPEC_PARAMS(i_, T, na) >
    : BOOST_PP_CAT(AUX778076_SEQUENCE_NAME,i_)< AUX778076_SEQUENCE_N_PARAMS(i_, T) >
{
    typedef BOOST_PP_CAT(AUX778076_SEQUENCE_NAME,i_)< AUX778076_SEQUENCE_N_PARAMS(i_, T) > type;
};

#endif // i_ == AUX778076_SEQUENCE_LIMIT

#   else

namespace aux {

template<>
struct BOOST_PP_CAT(AUX778076_SEQUENCE_NAME,_chooser)<i_>
{
    template<
          AUX778076_SEQUENCE_PARAMS(typename T)
        >
    struct result_
    {
        typedef BOOST_PP_CAT(AUX778076_SEQUENCE_NAME,i_)<
              AUX778076_SEQUENCE_N_PARAMS(i_, T)
            > type;
    };
};

} // namespace aux

#   endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#undef i_
#endif // BOOST_PP_IS_ITERATING

//-----------------------------------------------------------------------------
// boost mpl/arithmetic/aux_/op.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MPL_ARITHMETIC_AUX_OP_HPP_INCLUDED
#define BOOST_MPL_ARITHMETIC_AUX_OP_HPP_INCLUDED

#include "boost/mpl/integral_c.hpp"
#include "boost/mpl/limits/arity.hpp"
#include "boost/mpl/aux_/typeof.hpp"
#include "boost/mpl/aux_/lambda_spec.hpp"
#include "boost/mpl/aux_/preprocessor/params.hpp"
#include "boost/mpl/aux_/preprocessor/default_params.hpp"
#include "boost/mpl/aux_/preprocessor/enum.hpp"
#include "boost/mpl/aux_/preprocessor/project1st.hpp"
#include "boost/config.hpp"

#define BOOST_MPL_AUX_ARITHMETIC_OP_2(name, op) \
template< \
      typename T0 \
    , typename T1 \
    > \
struct name##2 \
{ \
    typedef typename \
        BOOST_MPL_AUX_TYPEOF(T0::value op T1::value) value_type; \
    BOOST_STATIC_CONSTANT(value_type, value = (T0::value op T1::value)); \
    typedef integral_c< value_type,value > type; \
}; \
\
BOOST_MPL_AUX_LAMBDA_SPEC(2, name##2) \
/**/

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

#   define BOOST_MPL_AUX_ARITHMETIC_OP_N(name, E, N) \
template< \
      typename T0 \
    , typename T1 \
    , BOOST_MPL_PP_DEFAULT_PARAMS(2, N, typename T, E) \
    > \
struct name \
{ \
 private: \
    typedef name##2<T0,T1> subexpr_; \
    typedef name< subexpr_, BOOST_MPL_PP_PARAMS(2, N, T) > res_; \
 public: \
    typedef typename res_::value_type value_type; \
    BOOST_STATIC_CONSTANT(value_type, value = res_::value); \
    typedef integral_c< value_type,value > type; \
}; \
\
template< typename T0 > \
struct name< \
      T0, BOOST_MPL_PP_ENUM(1, N, BOOST_MPL_PP_PROJECT2ND, E) \
    > \
{ \
    typedef typename T0::value_type value_type; \
    BOOST_STATIC_CONSTANT(value_type, value = T0::value); \
    typedef T0 type; \
}; \
/**/

#elif defined(BOOST_MSVC) && (BOOST_MSVC <= 1300)

#   define BOOST_MPL_AUX_ARITHMETIC_OP_N(name, E, N) \
template< \
      typename T0 \
    , typename T1 \
    > \
struct name \
    : name##2<T0,T1> \
{ \
}; \

#else // #if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

#   define BOOST_MPL_AUX_ARITHMETIC_OP_N(name, E, N) \
namespace aux { \
template< \
      typename T1 \
    , BOOST_MPL_PP_DEFAULT_PARAMS(2, N, typename T, E) \
    > \
struct name##_impl \
{ \
    template< typename T0 > struct result_ \
    { \
    private: \
        typedef name##2<T0,T1> subexpr_; \
        typedef typename name##_impl< BOOST_MPL_PP_PARAMS(2, N, T) > \
            ::template result_<subexpr_> res_; \
    public: \
        typedef typename res_::value_type value_type; \
        BOOST_STATIC_CONSTANT(value_type, value = res_::value); \
        typedef integral_c< value_type,value > type; \
    }; \
}; \
\
template<> \
struct name##_impl< \
      BOOST_MPL_PP_ENUM(1, N, BOOST_MPL_PP_PROJECT2ND, E) \
    > \
{ \
    template< typename T0 > struct result_ \
    { \
        typedef typename T0::value_type value_type; \
        BOOST_STATIC_CONSTANT(value_type, value = T0::value); \
        typedef T0 type; \
    }; \
}; \
}\
\
template< \
      typename T0 \
    , typename T1 \
    , BOOST_MPL_PP_DEFAULT_PARAMS(2, N, typename T, E) \
    > \
struct name \
    : aux::name##_impl<T1, BOOST_MPL_PP_PARAMS(2, N, T)> \
        ::template result_<T0> \
{ \
}; \
/**/

#endif // #if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

#define BOOST_MPL_AUX_ARITHMETIC_OP(name, op, E) \
namespace boost { namespace mpl { \
    BOOST_MPL_AUX_ARITHMETIC_OP_2(name, op) \
    BOOST_MPL_AUX_ARITHMETIC_OP_N( \
          name \
        , E \
        , BOOST_MPL_METAFUNCTION_MAX_ARITY \
        ) \
}} \
/**/

#endif // BOOST_MPL_ARITHMETIC_AUX_OP_HPP_INCLUDED

//-----------------------------------------------------------------------------
// boost mpl/labmda.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MPL_LAMBDA_HPP_INCLUDED
#define BOOST_MPL_LAMBDA_HPP_INCLUDED

#include "boost/mpl/lambda_fwd.hpp"
#include "boost/mpl/bind.hpp"
#include "boost/mpl/protect.hpp"
#include "boost/mpl/make_fun.hpp"
#include "boost/mpl/limits/arity.hpp"
#include "boost/mpl/aux_/arity.hpp"
#include "boost/mpl/aux_/preprocessor/params.hpp"
#include "boost/mpl/aux_/preprocessor/enum.hpp"
#include "boost/mpl/aux_/preprocessor/project1st.hpp"
#include "boost/mpl/aux_/config/lambda_support.hpp"

#include "boost/preprocessor/comma_if.hpp"
#include "boost/preprocessor/repeat.hpp"
#include "boost/preprocessor/if.hpp"
#include "boost/preprocessor/inc.hpp"
#include "boost/preprocessor/cat.hpp"

namespace boost {
namespace mpl {

template< typename T >
struct lambda
{
    typedef T type;
};

#if !defined(BOOST_MPL_NO_LAMDBA_SUPPORT)

// local macros, #undef-ined at the end of the header

#define AUX_LAMBDA_PARAMS(i, param) \
    BOOST_MPL_PP_PARAMS(1, BOOST_PP_INC(i), param) \
/**/

#define AUX_LAMBDA_PLACEHOLDERS(i) \
    BOOST_MPL_PP_ENUM(0, i, BOOST_MPL_PP_PROJECT2ND, _) \
/**/

#define AUX_LAMBDA_BIND_PARAMS(param) \
    BOOST_MPL_PP_PARAMS( \
          1 \
        , BOOST_PP_INC(BOOST_MPL_METAFUNCTION_MAX_ARITY) \
        , param \
        ) \
/**/

#define AUX_LAMBDA_BIND_N_PARAMS(i, param) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_MPL_PP_PARAMS(1, BOOST_PP_INC(i), param) \
/**/

// AUX_LAMBDA_N_PLACEHOLDERS_SPEC
#if defined(BOOST_MPL_LAMBDA_PLACEHOLDERS_PARTIAL_SPEC)
#   define AUX_LAMBDA_N_PLACEHOLDERS_SPEC(i) \
template< \
      template< AUX_LAMBDA_PARAMS(i, typename P) > class F \
    > \
struct lambda< F<AUX_LAMBDA_PLACEHOLDERS(i)> > \
{ \
    typedef F<AUX_LAMBDA_PLACEHOLDERS(i)> type; \
}; \
/**/
#else
#   define AUX_LAMBDA_N_PLACEHOLDERS_SPEC(unused) /**/
#endif

#define AUX_LAMBDA_INVOCATION(i, T) \
    BOOST_PP_COMMA_IF(i) \
    typename lambda< BOOST_PP_CAT(T, BOOST_PP_INC(i)) >::type \
/**/

#define AUX_LAMBDA_0_SPEC(unused)

#define AUX_LAMBDA_N_SPEC(i) \
template< \
      template< AUX_LAMBDA_PARAMS(i, typename P) > class F \
    , AUX_LAMBDA_PARAMS(i, typename T) \
    > \
struct lambda< F<AUX_LAMBDA_PARAMS(i, T)> > \
{ \
    typedef bind##i< \
          typename make_f##i<F>::type \
        , BOOST_PP_REPEAT(i, AUX_LAMBDA_INVOCATION, T) \
        > type; \
}; \
\
AUX_LAMBDA_N_PLACEHOLDERS_SPEC(i) \
/**/

#define AUX_LAMBDA_ON_BIND_SPEC(i) \
template< \
      typename F AUX_LAMBDA_BIND_N_PARAMS(i, typename T) \
    > \
struct lambda< bind##i<F AUX_LAMBDA_BIND_N_PARAMS(i, T)> > \
{ \
    typedef bind##i<F AUX_LAMBDA_BIND_N_PARAMS(i, T)> type; \
}; \
/**/

#define AUX_LAMBDA_SPEC(i, unused) \
    BOOST_PP_IF( \
          i \
        , AUX_LAMBDA_N_SPEC \
        , AUX_LAMBDA_0_SPEC \
        )(i) \
    AUX_LAMBDA_ON_BIND_SPEC(i) \
/**/

// lambda<#-ary class template>
BOOST_PP_REPEAT_2ND(
      BOOST_PP_INC(BOOST_MPL_METAFUNCTION_MAX_ARITY)
    , AUX_LAMBDA_SPEC
    , unused
    )

// special case for 'protect'
template< typename T >
struct lambda< protect<T> >
{
    typedef protect<T> type;
};

// specializations for main 'bind', 'bind1st' and 'bind2nd' forms
template<
      typename F
    , AUX_LAMBDA_BIND_PARAMS(typename T)
    >
struct lambda< bind<F, AUX_LAMBDA_BIND_PARAMS(T)> >
{
    typedef bind<F, AUX_LAMBDA_BIND_PARAMS(T)> type;
};

template<
      typename F
    , typename T
    >
struct lambda< bind1st<F,T> >
{
    typedef bind1st<F,T> type;
};

template<
      typename F
    , typename T
    >
struct lambda< bind2nd<F,T> >
{
    typedef bind2nd<F,T> type;
};

#if defined(__MWERKS__) && (__MWERKS__ <= 0x3000)
namespace aux {

template< typename T, long N > 
struct arity< lambda<T>, N >
{
    BOOST_STATIC_CONSTANT(long
        , value = BOOST_MPL_METAFUNCTION_MAX_ARITY
        );
};

} // namespace aux
#endif

#undef AUX_LAMBDA_SPEC
#undef AUX_LAMBDA_N_SPEC
#undef AUX_LAMBDA_0_SPEC
#undef AUX_LAMBDA_INVOCATION
#undef AUX_LAMBDA_N_PLACEHOLDERS_SPEC
#undef AUX_LAMBDA_BIND_N_PARAMS
#undef AUX_LAMBDA_BIND_PARAMS
#undef AUX_LAMBDA_PLACEHOLDERS
#undef AUX_LAMBDA_PARAMS

#endif // #if !defined(BOOST_MPL_NO_LAMDBA_SUPPORT)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_LAMBDA_HPP_INCLUDED

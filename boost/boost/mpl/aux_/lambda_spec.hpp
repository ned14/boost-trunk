//-----------------------------------------------------------------------------
// boost mpl/aux_/lambda_spec.hpp header file
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

#ifndef BOOST_MPL_AUX_LAMBDA_SPEC_HPP_INCLUDED
#define BOOST_MPL_AUX_LAMBDA_SPEC_HPP_INCLUDED

#include "boost/mpl/placeholder.hpp"
#include "boost/mpl/lambda_fwd.hpp"
#include "boost/mpl/limits/arity.hpp"
#include "boost/mpl/aux_/arity.hpp"
#include "boost/mpl/aux_/preprocessor/params.hpp"
#include "boost/mpl/aux_/preprocessor/enum.hpp"
#include "boost/mpl/aux_/preprocessor/project1st.hpp"
#include "boost/mpl/aux_/preprocessor/def_params_tail.hpp"
#include "boost/mpl/aux_/config/lambda_support.hpp"
#include "boost/mpl/aux_/config/dtp.hpp"
#include "boost/config.hpp"

#define BOOST_MPL_AUX_LAMBDA_SPEC_PLACEHOLDERS(i) \
    BOOST_MPL_PP_ENUM(0, i, BOOST_MPL_PP_PROJECT2ND, _) \
/**/

#if defined(BOOST_NO_DEFAULT_TEMPLATE_PARAMETERS_IN_NESTED_TEMPLATES)
#   define BOOST_MPL_AUX_LAMBDA_ARITY_SPEC(i, name) \
namespace aux { \
template< long N > \
struct arity< \
      name<BOOST_MPL_AUX_LAMBDA_SPEC_PLACEHOLDERS(i)> \
    , N \
    > \
{ \
    BOOST_STATIC_CONSTANT(long \
        , value = BOOST_MPL_METAFUNCTION_MAX_ARITY \
        ); \
}; \
} \
/**/
#else
#   define BOOST_MPL_AUX_LAMBDA_ARITY_SPEC(i, name) /**/
#endif

#if !defined(BOOST_MPL_LAMBDA_PLACEHOLDERS_PARTIAL_SPEC)
#   define BOOST_MPL_AUX_LAMBDA_TEMPLATE_SPEC(i, name) \
template<> struct lambda< \
      name<BOOST_MPL_AUX_LAMBDA_SPEC_PLACEHOLDERS(i)> \
    > \
{ \
    typedef name<BOOST_MPL_AUX_LAMBDA_SPEC_PLACEHOLDERS(i)> type; \
}; \
/**/
#else
#   define BOOST_MPL_AUX_LAMBDA_TEMPLATE_SPEC(i, name) /**/
#endif

#define BOOST_MPL_AUX_LAMBDA_SPEC(i, name) \
template<> \
struct name<BOOST_MPL_AUX_LAMBDA_SPEC_PLACEHOLDERS(i)> \
{ \
    template< \
          BOOST_MPL_PP_PARAMS(0, i, typename T) \
        BOOST_MPL_AUX_DEF_PARAMS_TAIL(i, typename T) \
        > \
    struct apply \
        : name<BOOST_MPL_PP_PARAMS(0, i, T)> \
    { \
    }; \
}; \
\
BOOST_MPL_AUX_LAMBDA_ARITY_SPEC(i, name) \
BOOST_MPL_AUX_LAMBDA_TEMPLATE_SPEC(i, name) \
/**/

#endif // BOOST_MPL_AUX_LAMBDA_SPEC_HPP_INCLUDED


#ifndef BOOST_MPL_AUX_NA_SPEC_HPP_INCLUDED
#define BOOST_MPL_AUX_NA_SPEC_HPP_INCLUDED

// Copyright (c) Aleksey Gurtovoy 2001-2004
//
// Use, modification and distribution are subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy 
// at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/lambda_fwd.hpp>
#include <boost/mpl/int_fwd.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/preprocessor/params.hpp>
#include <boost/mpl/aux_/preprocessor/enum.hpp>
#include <boost/mpl/aux_/preprocessor/def_params_tail.hpp>
#include <boost/mpl/aux_/arity.hpp>
#include <boost/mpl/aux_/template_arity_fwd.hpp>
#include <boost/mpl/aux_/lambda_arity_param.hpp>
#include <boost/mpl/aux_/algorithm_namespace.hpp>
#include <boost/mpl/aux_/config/dtp.hpp>
#include <boost/mpl/aux_/config/nttp.hpp>
#include <boost/mpl/aux_/config/ttp.hpp>
#include <boost/mpl/aux_/config/lambda.hpp>
#include <boost/mpl/aux_/config/overload_resolution.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>


#define BOOST_MPL_AUX_NA_PARAMS(i) \
    BOOST_MPL_PP_ENUM(i, na) \
/**/

#if defined(BOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
#   define BOOST_MPL_AUX_NA_SPEC_ARITY(i, name) \
namespace aux { \
template< BOOST_MPL_AUX_NTTP_DECL(int, N) > \
struct arity< \
      name< BOOST_MPL_AUX_NA_PARAMS(i) > \
    , N \
    > \
{ \
    BOOST_STATIC_CONSTANT(int \
        , value = BOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        ); \
}; \
} \
/**/
#else
#   define BOOST_MPL_AUX_NA_SPEC_ARITY(i, name) /**/
#endif

#define BOOST_MPL_AUX_NA_SPEC_MAIN(i, name) \
template<> \
struct name< BOOST_MPL_AUX_NA_PARAMS(i) > \
{ \
    template< \
          BOOST_MPL_PP_PARAMS(i, typename T) \
        BOOST_MPL_PP_NESTED_DEF_PARAMS_TAIL(i, typename T, na) \
        > \
    struct apply \
        : name< BOOST_MPL_PP_PARAMS(i, T) > \
    { \
    }; \
}; \
/**/

#if defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)
#   define BOOST_MPL_AUX_NA_SPEC_LAMBDA(i, name) \
template<> \
struct lambda< \
      name< BOOST_MPL_AUX_NA_PARAMS(i) > \
    , na \
    , true \
    > \
{ \
    typedef name< BOOST_MPL_AUX_NA_PARAMS(i) > type; \
}; \
/**/
#else
#   define BOOST_MPL_AUX_NA_SPEC_LAMBDA(i, name) \
template<> \
struct lambda< \
      name< BOOST_MPL_AUX_NA_PARAMS(i) > \
    , na \
    BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(int_<-1>) \
    > \
{ \
    typedef name< BOOST_MPL_AUX_NA_PARAMS(i) > type; \
}; \
/**/
#endif

#if defined(BOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING) \ 
    || defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT) \
        && defined(BOOST_MPL_CFG_BROKEN_OVERLOAD_RESOLUTION)
#   define BOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(i, j, name) \
namespace aux { \
template< BOOST_MPL_PP_PARAMS(j, typename T) > \
struct template_arity< \
      name< BOOST_MPL_PP_PARAMS(j, T) > \
    > \
{ \
    BOOST_STATIC_CONSTANT(int, value = j); \
}; \
\
template<> \
struct template_arity< \
      name< BOOST_MPL_PP_ENUM(i, na) > \
    > \
{ \
    BOOST_STATIC_CONSTANT(int, value = -1); \
}; \
} \
/**/
#else
#   define BOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(i, j, name) /**/
#endif


#define BOOST_MPL_AUX_NA_PARAM(param) param = na

#define BOOST_MPL_AUX_NA_SPEC(i, name) \
BOOST_MPL_AUX_NA_SPEC_MAIN(i, name) \
BOOST_MPL_AUX_NA_SPEC_LAMBDA(i, name) \
BOOST_MPL_AUX_NA_SPEC_ARITY(i, name) \
BOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(i, i, name) \
/**/

#define BOOST_MPL_AUX_NA_SPEC2(i, j, name) \
BOOST_MPL_AUX_NA_SPEC_MAIN(i, name) \
BOOST_MPL_AUX_NA_SPEC_LAMBDA(i, name) \
BOOST_MPL_AUX_NA_SPEC_ARITY(i, name) \
BOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(i, j, name) \
/**/

#define BOOST_MPL_AUX_NA_ALGORITHM_SPEC(i, name) \
BOOST_MPL_AUX_AGLORITHM_NAMESPACE_BEGIN \
BOOST_MPL_AUX_NA_SPEC_MAIN(i, name) \
BOOST_MPL_AUX_AGLORITHM_NAMESPACE_END \
BOOST_MPL_AUX_NA_SPEC_LAMBDA(i, BOOST_MPL_AUX_AGLORITHM_NAMESPACE_PREFIX name) \
BOOST_MPL_AUX_NA_SPEC_ARITY(i, BOOST_MPL_AUX_AGLORITHM_NAMESPACE_PREFIX name) \
BOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(i, i, BOOST_MPL_AUX_AGLORITHM_NAMESPACE_PREFIX name) \
/**/

#endif // BOOST_MPL_AUX_NA_SPEC_HPP_INCLUDED

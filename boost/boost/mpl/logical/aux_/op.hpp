//-----------------------------------------------------------------------------
// boost mpl/logical/aux_/op.hpp header file
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

#ifndef BOOST_MPL_LOGICAL_AUX_OP_HPP_INCLUDED
#define BOOST_MPL_LOGICAL_AUX_OP_HPP_INCLUDED

#include "boost/mpl/limits/arity.hpp"
#include "boost/mpl/aux_/lambda_spec.hpp"
#include "boost/mpl/aux_/preprocessor/default_params.hpp"
#include "boost/mpl/aux_/preprocessor/enum.hpp"
#include "boost/mpl/aux_/preprocessor/project1st.hpp"
#include "boost/config.hpp"

#define BOOST_MPL_AUX_LOGICAL_OP_2(name) \
    BOOST_MPL_AUX_LAMBDA_SPEC(2, name##2 ) \
/**/

#define BOOST_MPL_AUX_LOGICAL_OP_N(name, E, N) \
template< \
      typename T0 \
    , typename T1 \
    , BOOST_MPL_PP_DEFAULT_PARAMS(2, N, typename T, E) \
    > \
struct name \
{ \
 private: \
     typedef typename name##2< \
          T0 \
        , name<BOOST_MPL_PP_PARAMS(1, N, T)> \
        >::type type_; \
 public: \
    typedef type_ type; \
    BOOST_STATIC_CONSTANT(bool, value = type::value); \
}; \
\
template<> \
struct name< \
      BOOST_MPL_PP_ENUM(0, N, BOOST_MPL_PP_PROJECT2ND, E) \
    > \
{ \
    typedef E type; \
    BOOST_STATIC_CONSTANT(bool, value = E::value); \
}; \
/**/

#define BOOST_MPL_AUX_LOGICAL_OP(name, E) \
namespace boost { namespace mpl { \
    BOOST_MPL_AUX_LOGICAL_OP_2(name) \
    BOOST_MPL_AUX_LOGICAL_OP_N( \
          name \
        , E \
        , BOOST_MPL_METAFUNCTION_MAX_ARITY \
        ) \
}} \
/**/

#endif // BOOST_MPL_LOGICAL_AUX_OP_HPP_INCLUDED

//-----------------------------------------------------------------------------
// boost mpl/aux_/count_if_not.hpp header file
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

#ifndef BOOST_MPL_AUX_COUNT_IF_NOT_HPP_INCLUDED
#define BOOST_MPL_AUX_COUNT_IF_NOT_HPP_INCLUDED

#include "boost/mpl/aux_/preprocessor/default_params.hpp"

#include "boost/preprocessor/repeat.hpp"
#include "boost/preprocessor/expr_if.hpp"
#include "boost/type_traits/same_traits.hpp"

#define BOOST_MPL_AUX_COUNT_PARAM(i, param) \
    BOOST_PP_EXPR_IF(i, +) \
    !::boost::is_same<T, param##i>::value \
/**/

#define BOOST_MPL_AUX_COUNT_IF_NOT(prefix, n) \
namespace aux { \
template< \
      typename T \
    , BOOST_MPL_PP_DEFAULT_PARAMS(0, n, typename U, T) \
    > \
struct prefix##_count_if_not \
{ \
    BOOST_STATIC_CONSTANT(long, value = BOOST_PP_REPEAT( \
          n \
        , BOOST_MPL_AUX_COUNT_PARAM \
        , U \
        )); \
}; \
} \
/**/

#endif // BOOST_MPL_AUX_COUNT_IF_NOT_HPP_INCLUDED

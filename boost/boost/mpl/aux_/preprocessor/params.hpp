//-----------------------------------------------------------------------------
// boost mpl/aux_/preprocessor/params.hpp header file
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

#ifndef BOOST_AUX_PREPROCESSOR_PARAMS_HPP_INCLUDED
#define BOOST_AUX_PREPROCESSOR_PARAMS_HPP_INCLUDED

#include "boost/preprocessor/arithmetic/add.hpp"
#include "boost/preprocessor/arithmetic/sub.hpp"
#include "boost/preprocessor/comma_if.hpp"
#include "boost/preprocessor/repeat.hpp"
#include "boost/preprocessor/tuple/elem.hpp"
#include "boost/preprocessor/cat.hpp"

// BOOST_MPL_PP_PARAMS(0, 0, T): <nothing>
// BOOST_MPL_PP_PARAMS(0, 1, T): T0
// BOOST_MPL_PP_PARAMS(0, 2, T): T0, T1
// BOOST_MPL_PP_PARAMS(1, n, T): T1, T2, .., Tn-1

#define BOOST_MPL_PP_AUX_PARAM_FUNC(i, op) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_PP_CAT( \
          BOOST_PP_TUPLE_ELEM(2, 1, op) \
        , BOOST_PP_ADD(BOOST_PP_TUPLE_ELEM(2, 0, op), i) \
        ) \
/**/

#define BOOST_MPL_PP_PARAMS(i, j, param) \
    BOOST_PP_REPEAT( \
          BOOST_PP_SUB(j, i) \
        , BOOST_MPL_PP_AUX_PARAM_FUNC \
        , (i, param) \
        ) \
/**/

#endif // BOOST_AUX_PREPROCESSOR_PARAMS_HPP_INCLUDED

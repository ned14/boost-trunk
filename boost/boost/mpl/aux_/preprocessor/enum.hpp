//-----------------------------------------------------------------------------
// boost mpl/aux_/preprocessor/enum.hpp header file
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

#ifndef BOOST_AUX_PREPROCESSOR_ENUM_HPP_INCLUDED
#define BOOST_AUX_PREPROCESSOR_ENUM_HPP_INCLUDED

#include "boost/preprocessor/arithmetic/add.hpp"
#include "boost/preprocessor/arithmetic/sub.hpp"
#include "boost/preprocessor/comma_if.hpp"
#include "boost/preprocessor/repeat.hpp"
#include "boost/preprocessor/tuple/elem.hpp"
#include "boost/preprocessor/cat.hpp"

// BOOST_MPL_PP_ENUM(0, 0, F, int): <nothing>
// BOOST_MPL_PP_ENUM(0, 1, F, int): F(0, int)
// BOOST_MPL_PP_ENUM(0, 2, F, int): F(0, int), F(1, int)
// BOOST_MPL_PP_ENUM(1, n, F, int): F(1, int), F(2, int), .., F(n-1, int)

#define BOOST_MPL_PP_AUX_ENUM_FUNC(i, ofp) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_PP_TUPLE_ELEM(3, 1, ofp)( \
          BOOST_PP_ADD(BOOST_PP_TUPLE_ELEM(3, 0, ofp), i) \
        , BOOST_PP_TUPLE_ELEM(3, 2, ofp) \
        ) \
/**/

#define BOOST_MPL_PP_ENUM(i, j, f, param) \
    BOOST_PP_REPEAT( \
          BOOST_PP_SUB(j, i) \
        , BOOST_MPL_PP_AUX_ENUM_FUNC \
        , (i, f, param) \
        ) \
/**/

#endif // BOOST_AUX_PREPROCESSOR_ENUM_HPP_INCLUDED

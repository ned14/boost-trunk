//-----------------------------------------------------------------------------
// boost mpl/aux_/preprocessor/def_params_tail.hpp header file
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

#ifndef BOOST_AUX_PREPROCESSOR_DEF_PARAMS_TAIL_HPP_INCLUDED
#define BOOST_AUX_PREPROCESSOR_DEF_PARAMS_TAIL_HPP_INCLUDED

#include "boost/mpl/limits/arity.hpp"
#include "boost/mpl/aux_/none.hpp"

#include "boost/preprocessor/arithmetic/add.hpp"
#include "boost/preprocessor/arithmetic/sub.hpp"
#include "boost/preprocessor/tuple/elem.hpp"
#include "boost/preprocessor/repeat.hpp"
#include "boost/preprocessor/cat.hpp"

// BOOST_MPL_AUX_DEF_PARAMS_TAIL(1, T): , T1 = aux::none, .., Tn = aux::none
// BOOST_MPL_AUX_DEF_PARAMS_TAIL(2, T): , T2 = aux::none, .., Tn = aux::none
// BOOST_MPL_AUX_DEF_PARAMS_TAIL(n, T): <nothing>

#define BOOST_MPL_PP_AUX_TAIL_PARAM_FUNC(i, op) \
    , BOOST_PP_CAT( \
          BOOST_PP_TUPLE_ELEM(2, 1, op) \
        , BOOST_PP_ADD(BOOST_PP_TUPLE_ELEM(2, 0, op), i) \
        ) = aux::none \
/**/

#define BOOST_MPL_AUX_DEF_PARAMS_TAIL(i, param) \
    BOOST_PP_REPEAT( \
          BOOST_PP_SUB(BOOST_MPL_METAFUNCTION_MAX_ARITY, i) \
        , BOOST_MPL_PP_AUX_TAIL_PARAM_FUNC \
        , (i, param) \
        ) \
/**/

#endif // BOOST_AUX_PREPROCESSOR_DEF_PARAMS_TAIL_HPP_INCLUDED

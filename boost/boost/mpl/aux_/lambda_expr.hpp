
#ifndef BOOST_MPL_AUX_LAMBDA_EXPR_HPP_INCLUDED
#define BOOST_MPL_AUX_LAMBDA_EXPR_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/lambda.hpp>

#if defined(BOOST_MPL_CFG_NO_LAMBDA_HEURISTIC)
#   define BOOST_MPL_AUX_IS_LAMBDA_EXPR(value) /**/
#else
#   define BOOST_MPL_AUX_IS_LAMBDA_EXPR(value) \
    typedef value is_le; \
    /**/
#endif

#endif // BOOST_MPL_AUX_LAMBDA_EXPR_HPP_INCLUDED

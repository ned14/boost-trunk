
#ifndef BOOST_MPL_AND_HPP_INCLUDED
#define BOOST_MPL_AND_HPP_INCLUDED

// Copyright (c) Aleksey Gurtovoy 2000-2003
//
// Use, modification and distribution are subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy 
// at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
 && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   include <boost/mpl/bool.hpp>
#   include <boost/mpl/aux_/nested_type_wknd.hpp>
#   include <boost/mpl/aux_/na_spec.hpp>
#   include <boost/mpl/aux_/lambda_support.hpp>

#   define BOOST_MPL_PREPROCESSED_HEADER and.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   define AUX_LOGICAL_OP_NAME and_
#   define AUX_LOGICAL_OP_VALUE1 false
#   define AUX_LOGICAL_OP_VALUE2 true
#   include <boost/mpl/aux_/logical_op.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_AND_HPP_INCLUDED

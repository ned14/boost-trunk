
#ifndef BOOST_MPL_AUX_ALGORITHM_NAMESPACE_HPP_INCLUDED
#define BOOST_MPL_AUX_ALGORITHM_NAMESPACE_HPP_INCLUDED

// Copyright (c) Aleksey Gurtovoy 2002-2004
//
// Use, modification and distribution are subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy 
// at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/gcc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, >= 0x0300) \
    && BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, BOOST_TESTED_AT(0x0302))

#   define BOOST_MPL_AUX_AGLORITHM_NAMESPACE_PREFIX algo_::
#   define BOOST_MPL_AUX_AGLORITHM_NAMESPACE_BEGIN namespace algo_ {
#   define BOOST_MPL_AUX_AGLORITHM_NAMESPACE_END } using namespace algo_;

#else

#   define BOOST_MPL_AUX_AGLORITHM_NAMESPACE_PREFIX /**/
#   define BOOST_MPL_AUX_AGLORITHM_NAMESPACE_BEGIN /**/
#   define BOOST_MPL_AUX_AGLORITHM_NAMESPACE_END /**/

#endif

#endif // BOOST_MPL_AUX_ALGORITHM_NAMESPACE_HPP_INCLUDED

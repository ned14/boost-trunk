//-----------------------------------------------------------------------------
// boost mpl/aux_/prior.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_PRIOR_HPP_INCLUDED
#define BOOST_MPL_AUX_PRIOR_HPP_INCLUDED

#if defined(BOOST_MPL_USE_NEXT_INTERNALLY)

#   if !defined(BOOST_MPL_PREPROCESSING_MODE)
#       include "boost/mpl/prior.hpp"
#   endif

#   define BOOST_MPL_AUX_PRIOR(x) prior<x>::type

#else

#   define BOOST_MPL_AUX_PRIOR(x) x::prior

#endif

#endif // BOOST_MPL_AUX_PRIOR_HPP_INCLUDED

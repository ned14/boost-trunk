
#ifndef BOOST_MPL_NEXT_PRIOR_HPP_INCLUDED
#define BOOST_MPL_NEXT_PRIOR_HPP_INCLUDED

// Copyright (c) Aleksey Gurtovoy 2000-2004
//
// Use, modification and distribution are subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy 
// at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/eti.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct next
{
    typedef typename T::next type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,next,(T))
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct prior
{
    typedef typename T::prior type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,prior,(T))
};


#if defined(BOOST_MPL_CFG_MSVC_ETI_BUG)
template<> struct next<int>
{
    typedef int type;
};

template<> struct prior<int>
{
    typedef int type;
};
#endif

BOOST_MPL_AUX_NA_SPEC(1, next)
BOOST_MPL_AUX_NA_SPEC(1, prior)

}}

#endif // BOOST_MPL_NEXT_PRIOR_HPP_INCLUDED


#ifndef BOOST_MPL_APPLY_IF_HPP_INCLUDED
#define BOOST_MPL_APPLY_IF_HPP_INCLUDED

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

#include <boost/mpl/if.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(C)
    , typename BOOST_MPL_AUX_NA_PARAM(F1)
    , typename BOOST_MPL_AUX_NA_PARAM(F2)
    >
struct apply_if
    : apply0< typename if_<C,F1,F2>::type >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,apply_if,(C,F1,F2))
};

// (almost) copy & paste in order to save one more 
// recursively nested template instantiation to user
template<
      bool C
    , typename F1
    , typename F2
    >
struct apply_if_c
    : apply0< typename if_c<C,F1,F2>::type >
{
};

BOOST_MPL_AUX_NA_SPEC(3, apply_if)
 
}}

#endif // BOOST_MPL_APPLY_IF_HPP_INCLUDED

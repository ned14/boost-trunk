
#ifndef BOOST_MPL_ITERATOR_CATEGORY_HPP_INCLUDED
#define BOOST_MPL_ITERATOR_CATEGORY_HPP_INCLUDED

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

namespace boost { 
namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Iterator)
    >
struct iterator_category
{
    typedef typename Iterator::category type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,iterator_category,(Iterator))
};

#if defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG)
template<> struct iterator_category<int>
{
    typedef int type;
};
#endif
/*
template<
      typename BOOST_MPL_AUX_NA_PARAM(Iterator)
    >
struct is_forward
    : true_
{
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(Iterator)
    >
struct is_bidirectional
    : greater_equal<
          typename Iterator::category
        , bidirectional_iterator_tag
        >
{
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(Iterator)
    >
struct is_random_access
    : greater_equal<
          typename Iterator::category
        , random_access_iterator_tag
        >
{
};
*/
BOOST_MPL_AUX_NA_SPEC(1, iterator_category)

}}

#endif // BOOST_MPL_ITERATOR_CATEGORY_HPP_INCLUDED

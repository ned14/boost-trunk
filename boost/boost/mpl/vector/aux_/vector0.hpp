
#ifndef BOOST_MPL_VECTOR_AUX_VECTOR0_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_VECTOR0_HPP_INCLUDED

// Copyright (c) 2000-04 Aleksey Gurtovoy
//
// Use, modification and distribution are subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy 
// at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/long.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>

#include <boost/mpl/vector/aux_/iterator.hpp>
#include <boost/mpl/vector/aux_/tag.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

namespace boost { 
namespace mpl {


template< int dummy_ = 0 > struct vector0;
template<> struct vector0<0>
{
#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
    typedef aux::vector_tag tag;
    typedef long_<32768>    lower_bound_;
    typedef lower_bound_    upper_bound_;
    typedef long_<0>        size;

    static void_ item_(...);
#else
    typedef aux::vector_tag<0> tag;
    typedef vector0 type;
    typedef void_ item0;
    
    typedef v_iter<vector0,0> begin;
    typedef v_iter<vector0,0> end;
#endif
};

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_VECTOR_AUX_VECTOR0_HPP_INCLUDED

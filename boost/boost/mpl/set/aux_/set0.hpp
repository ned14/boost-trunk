
#ifndef BOOST_MPL_SET_AUX_SET0_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_SET0_HPP_INCLUDED

// Copyright (c) Aleksey Gurtovoy 2003-2004
// Copyright (c) David Abrahams 2003-2004
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
#include <boost/mpl/void_fwd.hpp>
#include <boost/mpl/set/aux_/tag.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

namespace boost {
namespace mpl {

template< int dummy_ = 0 > struct set0
{
    typedef aux::set_tag    tag;
    typedef void_           last_masked_;
    typedef void_           item_type_;
    typedef item_type_      type;
    typedef long_<0>        size;
    
    BOOST_STATIC_CONSTANT(long, order = 0);
};

}}

#endif // BOOST_MPL_SET_AUX_SET0_HPP_INCLUDED


#ifndef BOOST_MPL_SET_AUX_HAS_MAP_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_HAS_MAP_IMPL_HPP_INCLUDED

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

#include "boost/mpl/has_key_fwd.hpp"
#include "boost/mpl/map/aux_/tag.hpp"
#include "boost/mpl/map/aux_/at_impl.hpp"
#include "boost/mpl/void.hpp"

namespace boost {
namespace mpl {

template<>
struct has_key_impl< aux::map_tag >
{
    template< typename Map, typename Key > struct apply
        : is_not_void_< 
              typename at_impl<aux::map_tag>
                ::apply<Map,Key>::type
            >
    {
    };
};

}}

#endif // BOOST_MPL_SET_AUX_HAS_MAP_IMPL_HPP_INCLUDED

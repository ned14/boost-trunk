
#ifndef BOOST_MPL_MAP_AUX_INSERT_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_INSERT_IMPL_HPP_INCLUDED

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

#include <boost/mpl/insert_fwd.hpp>
#include <boost/mpl/map/aux_/contains_impl.hpp>
#include <boost/mpl/map/aux_/item.hpp>
#include <boost/mpl/map/aux_/tag.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
template<>
struct insert_impl< aux::map_tag >
{
    template< 
          typename Map
        , typename Pair
        , typename unused_ 
        > 
    struct apply
        : if_< 
              contains_impl<aux::map_tag>::apply<Map,Pair>
            , Map
            , m_item<
                  typename Pair::first
                , typename Pair::second
                , Map
                >
            >
    {
    };
};
#endif

}}

#endif // BOOST_MPL_MAP_AUX_INSERT_IMPL_HPP_INCLUDED

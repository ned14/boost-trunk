
#ifndef BOOST_MPL_SET_AUX_AT_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_AT_IMPL_HPP_INCLUDED

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

#include "boost/mpl/at_fwd.hpp"
#include "boost/mpl/long.hpp"
#include "boost/mpl/map/aux_/tag.hpp"
#include "boost/mpl/aux_/order_impl.hpp"
#include "boost/mpl/aux_/type_wrapper.hpp"
#include "boost/mpl/aux_/ptr_to_ref.hpp"
#include "boost/mpl/aux_/static_cast.hpp"
#include "boost/mpl/aux_/config/typeof.hpp"

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template< typename Map, typename Key >
struct m_at
{
    typedef aux::type_wrapper<Key> key_;
    typedef __typeof__( aux::ptr_to_ref(BOOST_MPL_AUX_STATIC_CAST(Map*, 0)) 
        | BOOST_MPL_AUX_STATIC_CAST(key_*, 0) ) type;
};

template<>
struct at_impl< aux::map_tag >
{
    template< typename Map, typename Key > struct apply
        : aux::wrapped_type< typename m_at<
              Map
            , Key
            >::type >
    {
    };
};

// agurt 31/jan/04: two-step implementation for the sake of GCC 3.x
template< typename Map, long order > 
struct item_by_order_impl
{
    typedef __typeof__( aux::ptr_to_ref(BOOST_MPL_AUX_STATIC_CAST(Map*, 0)) 
        || long_<order>() ) type;
};

template< typename Map, long order >
struct item_by_order
    : aux::wrapped_type<
          typename item_by_order_impl<Map,order>::type
        >
{
};

#else // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

template< typename Map, long n > struct m_at
{
    typedef void_ type;
};

template< typename Map>
struct m_at<Map,1>
{
    typedef typename Map::type1 type;
};

template< typename Map>
struct m_at<Map,2>
{
    typedef typename Map::type2 type;
};

template<>
struct at_impl< aux::map_tag >
{
    template< typename Map, typename Key > struct apply
        : m_at<
              Map
            , x_order_impl<Map,Key>::value
            >
    {
    };
};

#endif

}}

#endif // BOOST_MPL_SET_AUX_AT_IMPL_HPP_INCLUDED

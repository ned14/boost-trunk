
#ifndef BOOST_MPL_LIST_AUX_PUSH_FRONT_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_PUSH_FRONT_HPP_INCLUDED

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

#include <boost/mpl/push_front_fwd.hpp>
#include <boost/mpl/aux_/next.hpp>
#include <boost/mpl/list/aux_/node.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct push_front_impl< aux::list_tag >
{
    template< typename List, typename T > struct apply
    {
        typedef list_node<
              typename BOOST_MPL_AUX_NEXT(List::size)
            , T
            , typename List::type
            > type;
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_PUSH_FRONT_HPP_INCLUDED


#ifndef BOOST_MPL_LIST_AUX_BEGIN_END_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_BEGIN_END_HPP_INCLUDED

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

#include <boost/mpl/begin_end_fwd.hpp>
#include <boost/mpl/list/aux_/iterator.hpp>
#include <boost/mpl/list/aux_/tag.hpp>
#include <boost/mpl/list/aux_/node.hpp>

namespace boost { namespace mpl {

template<>
struct begin_impl< aux::list_tag >
{
    template< typename List > struct apply
    {
        typedef list_iterator<typename List::type> type;
    };
};

template<>
struct end_impl< aux::list_tag >
{
    template< typename > struct apply
    {
        typedef list_iterator<null_node> type;
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_BEGIN_END_HPP_INCLUDED

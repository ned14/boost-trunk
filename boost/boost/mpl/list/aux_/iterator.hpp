
#ifndef BOOST_MPL_LIST_AUX_ITERATOR_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_ITERATOR_HPP_INCLUDED

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

#include <boost/mpl/iterator_tag.hpp>
#include <boost/mpl/list/aux_/node.hpp>
#include <boost/mpl/aux_/lambda_spec.hpp>

namespace boost { namespace mpl {

template< typename Node >
struct list_iterator
{
    typedef forward_iterator_tag category;
    typedef typename Node::item type;
    typedef list_iterator<typename Node::next> next;
};

template<>
struct list_iterator<null_node>
{
    typedef forward_iterator_tag category;
};

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(1,list_iterator)

}}

#endif // BOOST_MPL_LIST_AUX_ITERATOR_HPP_INCLUDED

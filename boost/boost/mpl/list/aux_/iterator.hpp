//-----------------------------------------------------------------------------
// boost mpl/list/aux_/iterator.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MPL_LIST_AUX_ITERATOR_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_ITERATOR_HPP_INCLUDED

#include "boost/mpl/aux_/none.hpp"
#include "boost/mpl/iterator_category.hpp"
#include "boost/mpl/lambda_fwd.hpp"
#include "boost/mpl/aux_/config/lambda_support.hpp"

namespace boost {
namespace mpl {

template< typename Node >
struct list_iterator
{
    typedef forward_iterator_tag category;
    typedef typename Node::item type;
    typedef list_iterator<typename Node::next> next;
};

template<>
struct list_iterator<aux::none>
{
    typedef forward_iterator_tag category;
};

#if !defined(BOOST_MPL_NO_LAMDBA_SUPPORT)
template< typename Node >
struct lambda< list_iterator<Node> >
{
    typedef list_iterator<Node> type;
};
#endif

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_LIST_AUX_ITERATOR_HPP_INCLUDED

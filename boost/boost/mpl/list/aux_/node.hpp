//-----------------------------------------------------------------------------
// boost mpl/list/aux_/node.hpp header file
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

#ifndef BOOST_MPL_LIST_AUX_NODE_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_NODE_HPP_INCLUDED

#include "boost/mpl/list/aux_/tag.hpp"
#include "boost/mpl/aux_/none.hpp"
#include "boost/config.hpp"

namespace boost {
namespace mpl {

template<
      typename T
    , typename Next
    >
struct list_node
{
    typedef aux::list_tag tag;
    typedef list_node type;
    typedef T item;
    typedef Next next;
};

struct null_node
{
    typedef aux::list_tag tag;
    typedef null_node type;

// to make VC 7.0 happy
#if defined(BOOST_MSVC) && (BOOST_MSVC == 1300)
    typedef aux::none item;
    typedef null_node next;
#endif
};

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_LIST_AUX_NODE_HPP_INCLUDED

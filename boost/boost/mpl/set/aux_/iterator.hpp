
#ifndef BOOST_MPL_SET_AUX_ITERATOR_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_ITERATOR_HPP_INCLUDED

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

#include "boost/mpl/set/aux_/set0.hpp"
#include "boost/mpl/has_key.hpp"
#include "boost/mpl/iterator_tag.hpp"
#include "boost/mpl/next.hpp"
#include "boost/mpl/apply_if.hpp"
#include "boost/mpl/if.hpp"
#include "boost/mpl/identity.hpp"
#include "boost/mpl/aux_/config/ctps.hpp"

namespace boost { namespace mpl {

// used by 's_iter_impl'
template< typename Set, typename Tail > struct s_iter;

template< typename Set, typename Tail > struct s_iter_impl
{
    typedef Tail                tail_;
    typedef fwd_iter_tag_       category;
    typedef typename Tail::item type;

#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    typedef typename apply_if< 
          has_key< Set,typename Tail::next_::item >
        , identity< s_iter<Set,typename Tail::next_> >
        , next< s_iter<Set,typename Tail::next_> >
        >::type next;        
#endif
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< typename Set, typename Tail > 
struct next< s_iter<Set,Tail> >
    : apply_if< 
          has_key< Set,typename Tail::next_::item >
        , identity< s_iter<Set,typename Tail::next_> >
        , next< s_iter<Set,typename Tail::next_> >
        >
{
};

template< typename Set > 
struct next< s_iter<Set,set0<> > >
{
    typedef s_iter<Set,set0<> > type;
};

template< typename Set, typename Tail > struct s_iter
    : s_iter_impl<Set,Tail>
{
};

template< typename Set > struct s_iter<Set, set0<> >
{
    typedef fwd_iter_tag_  category;
};

#else

template< typename Set >
struct s_end_iter
{
    typedef fwd_iter_tag_       category;
    typedef s_iter<Set,set0<> > next;
};

template< typename Set, typename Tail > struct s_iter
    : if_< 
          is_same< Tail,set0<> >
        , s_end_iter<Set>
        , s_iter_impl<Set,Tail>
        >::type
{
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

}}

#endif // BOOST_MPL_SET_AUX_ITERATOR_HPP_INCLUDED

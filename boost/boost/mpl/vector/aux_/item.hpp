
#ifndef BOOST_MPL_VECTOR_AUX_ITEM_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_ITEM_HPP_INCLUDED

// Copyright (c) 2000-04 Aleksey Gurtovoy
//
// Use, modification and distribution are subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy 
// at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include "boost/mpl/long.hpp"
#include "boost/mpl/void.hpp"
#include "boost/mpl/aux_/type_wrapper.hpp"
#include "boost/mpl/aux_/config/typeof.hpp"
#include "boost/mpl/aux_/config/ctps.hpp"

namespace boost {
namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template< 
      typename T
    , typename Base
    , int at_front = 0
    >
struct v_item
    : Base
{
    typedef typename Base::upper_bound_ index_;
    typedef typename index_::next       upper_bound_;
    typedef typename Base::size::next   size;
    typedef Base base;

    using Base::item_;
    static aux::type_wrapper<T> item_(index_);
};

template<
      typename T
    , typename Base
    >
struct v_item<T,Base,1>
    : Base
{
    typedef typename Base::lower_bound_::prior  index_;
    typedef index_                              lower_bound_;
    typedef typename Base::size::next           size;
    typedef Base base;

    using Base::item_;
    static aux::type_wrapper<T> item_(index_);
};

// "erasure" item
template< 
      typename Base
    , int at_front
    >
struct v_mask
    : Base
{
    typedef typename Base::upper_bound_::prior  index_;
    typedef index_                              upper_bound_;
    typedef typename Base::size::prior          size;
    typedef Base base;

    using Base::item_;
    static void_ item_(index_);
};

template< 
      typename Base
    >
struct v_mask<Base,1>
    : Base
{
    typedef typename Base::lower_bound_  index_;
    typedef typename index_::next        lower_bound_;
    typedef typename Base::size::prior   size;
    typedef Base base;

    using Base::item_;
    static void_ item_(index_);
};

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_VECTOR_AUX_ITEM_HPP_INCLUDED

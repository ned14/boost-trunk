
#ifndef BOOST_MPL_SET_AUX_ITEM_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_ITEM_HPP_INCLUDED

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

#include "boost/mpl/long.hpp"
#include "boost/mpl/void_fwd.hpp"
#include "boost/mpl/next.hpp"
#include "boost/mpl/prior.hpp"
#include "boost/mpl/set/aux_/set0.hpp"
#include "boost/mpl/aux_/yes_no.hpp"
#include "boost/mpl/aux_/type_wrapper.hpp"
#include "boost/mpl/aux_/config/gcc.hpp"
#include "boost/mpl/aux_/config/static_constant.hpp"
#include "boost/mpl/aux_/config/workaround.hpp"

// agurt, 03/may/03: use specialization in place of conventional overloading
// to supress a warning on GCC 3.x; breaks 2.95.x!
#if BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, > 0x0295) \
    && BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, BOOST_TESTED_AT(0x0302))
#   define BOOST_MPL_CFG_USE_OPERATORS_SPECIALIZATION
#endif

namespace boost {
namespace mpl {

aux::no_tag operator/(set0<> const&, void*);
aux::no_tag operator%(set0<> const&, void*);

#if defined(BOOST_MPL_CFG_USE_OPERATORS_SPECIALIZATION)

template< typename T, typename Base > struct s_item;
template< typename T, typename Base > struct s_mask;
template< typename T, typename Base > struct s_unmask;

template< typename T, typename Base >
typename s_item<T,Base>::order_tag
operator/(s_item<T,Base> const&, aux::type_wrapper<T>*);

template< typename T, typename Base >
aux::yes_tag operator%(s_item<T,Base> const&, aux::type_wrapper<T>*);

template< typename T, typename Base >
aux::yes_tag operator%(s_unmask<T,Base> const&, aux::type_wrapper<T>*);

template< typename T, typename Base >
aux::no_tag operator%(s_mask<T,Base> const&, aux::type_wrapper<T>*);

#endif // BOOST_MPL_CFG_USE_OPERATORS_SPECIALIZATION


#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x561))
namespace aux {
template< long n_ > struct order_tag_
{
    typedef char (&type)[n_];    
};
}
#endif

template< typename T, typename Base >
struct s_item
    : Base
{
    typedef void_   last_masked_;
    typedef Base    next_;
    typedef T       item;
    typedef Base    base;
    
    typedef typename next< typename Base::size >::type  size;
    
    BOOST_STATIC_CONSTANT(long, order = Base::order + 1);

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x561))
    typedef typename aux::order_tag_<(Base::order + 1)>::type order_tag;
#else
    typedef char (&order_tag)[order];
#endif

#if defined(BOOST_MPL_CFG_USE_OPERATORS_SPECIALIZATION)
    friend order_tag    operator/<>(s_item const&, aux::type_wrapper<T>*);
    friend aux::yes_tag operator%<>(s_item const&, aux::type_wrapper<T>*);
#else
    friend order_tag    operator/(s_item const&, aux::type_wrapper<T>*);
    friend aux::yes_tag operator%(s_item const&, aux::type_wrapper<T>*);
#endif
};


template< typename T, typename Base >
struct s_mask
    : Base
{
    typedef T       last_masked_;
    typedef Base    base;
    typedef typename prior< typename Base::size >::type  size;
#if defined(BOOST_MPL_CFG_USE_OPERATORS_SPECIALIZATION)
    friend aux::no_tag operator%<>(s_mask const&, aux::type_wrapper<T>*);
#else
    friend aux::no_tag operator%(s_mask const&, aux::type_wrapper<T>*);
#endif
};


template< typename T, typename Base >
struct s_unmask
    : Base
{
    typedef void_   last_masked_;
    typedef Base    base;
    typedef typename next< typename Base::size >::type  size;
#if defined(BOOST_MPL_CFG_USE_OPERATORS_SPECIALIZATION)
    friend aux::yes_tag operator%<>(s_unmask const&, aux::type_wrapper<T>*);
#else
    friend aux::yes_tag operator%(s_unmask const&, aux::type_wrapper<T>*);
#endif
};

}}

#endif // BOOST_MPL_SET_AUX_ITEM_HPP_INCLUDED

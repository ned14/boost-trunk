
#ifndef BOOST_MPL_AUX_NA_HPP_INCLUDED
#define BOOST_MPL_AUX_NA_HPP_INCLUDED

// Copyright (c) Aleksey Gurtovoy 2001-2004
//
// Use, modification and distribution are subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy 
// at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include "boost/mpl/bool.hpp"
#include "boost/mpl/aux_/config/msvc.hpp"
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

// n.a. == not available
struct na;

template< typename T >
struct is_na
    : false_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using false_::value;
#endif
};

template<>
struct is_na<na>
    : true_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using true_::value;
#endif
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
template< typename T, typename U > struct if_na
{
    typedef T type;
};

template< typename U > struct if_na<na,U>
{
    typedef U type;
};
#else
template< typename T > struct if_na_impl
{
    template< typename U > struct apply
    {
        typedef T type;
    };
};

template<> struct if_na_impl<na>
{
    template< typename U > struct apply
    {
        typedef U type;
    };
};

template< typename T, typename U > struct if_na
    : if_na_impl<T>::template apply<U>
{
};
#endif

}}

#endif // BOOST_MPL_AUX_NA_HPP_INCLUDED

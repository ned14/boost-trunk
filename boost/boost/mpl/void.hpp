
#ifndef BOOST_MPL_VOID_HPP_INCLUDED
#define BOOST_MPL_VOID_HPP_INCLUDED

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

#include "boost/mpl/void_fwd.hpp"
#include "boost/mpl/bool.hpp"
#include "boost/mpl/aux_/config/msvc.hpp"
#include "boost/mpl/aux_/config/ctps.hpp"
#include "boost/mpl/aux_/config/workaround.hpp"

// should be the last include
#include "boost/type_traits/detail/bool_trait_def.hpp"

namespace boost {
namespace mpl {

//  [JDG Feb-4-2003] made void_ a complete type to allow it to be
//  instantiated so that it can be passed in as an object that can be
//  used to select an overloaded function. Possible use includes signaling
//  a zero arity functor evaluation call.
struct void_ { typedef void_ type; };

BOOST_TT_AUX_BOOL_TRAIT_DEF1( is_void_, T, false )
BOOST_TT_AUX_BOOL_TRAIT_SPEC1( is_void_, void_, true )

BOOST_TT_AUX_BOOL_TRAIT_DEF1( is_not_void_, T, true )
BOOST_TT_AUX_BOOL_TRAIT_SPEC1( is_not_void_, void_, false )

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< typename T, typename U > struct if_void_
{
    typedef T type;
};

template< typename U > struct if_void_<void_,U>
{
    typedef U type;
};

#else

template< typename T > struct if_void_impl
{
    template< typename U > struct apply
    {
        typedef T type;
    };
};

template<> struct if_void_impl<void_>
{
    template< typename U > struct apply
    {
        typedef U type;
    };
};

template< typename T, typename U > struct if_void_
    : if_void_impl<T>::template apply<U>
{
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

}}

#include "boost/type_traits/detail/bool_trait_undef.hpp"

#endif // BOOST_MPL_VOID_HPP_INCLUDED

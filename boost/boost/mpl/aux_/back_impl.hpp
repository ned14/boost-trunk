
#ifndef BOOST_MPL_AUX_BACK_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_BACK_IMPL_HPP_INCLUDED

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

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/aux_/deref_wknd.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/mpl/aux_/config/eti.hpp>

namespace boost {
namespace mpl {

// default implementation, requires at least bi-directional iterators;
// conrete sequences might override it by specializing either the 
// 'back_impl' or the primary 'back' template

template< typename Tag >
struct back_impl
{
    template< typename Sequence > struct apply
    {
        typedef typename end<Sequence>::type iter_;
#if defined(BOOST_MPL_CFG_MSVC_ETI_BUG)
        typedef typename prior<iter_>::type last_;
#else
        typedef typename iter_::prior last_;
#endif
        typedef typename BOOST_MPL_AUX_DEREF_WNKD(last_) type;
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1, back_impl)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_AUX_BACK_IMPL_HPP_INCLUDED

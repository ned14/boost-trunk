
#ifndef BOOST_MPL_O1_SIZE_IMPL_HPP_INCLUDED
#define BOOST_MPL_O1_SIZE_IMPL_HPP_INCLUDED

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

#include "boost/mpl/O1_size_fwd.hpp"
#include "boost/mpl/integral_c.hpp"
#include "boost/mpl/if.hpp"
#include "boost/mpl/aux_/has_size.hpp"

namespace boost {
namespace mpl {

// default implementation - returns 'Sequence::size' if sequence has a 'size'
// member, and -1 otherwise; conrete sequences might override it by specializing 
// either the 'O1_size_impl' or the primary 'O1_size' template

#if 0//!defined(BOOST_MSVC) || BOOST_MSVC > 1300
namespace aux {

template< typename Sequence >
struct O1_size_impl
    : Sequence::size
{
};

} // namespace aux

template< typename Tag >
struct O1_size_impl
{
    template< typename Sequence > struct apply
        : if_c<
              ::boost::mpl::aux::has_size<Sequence>::value
            , aux::O1_size_impl<Sequence>
            , integral_c<long,-1>
            >::type
    {
    };
};
#else

template< typename Tag >
struct O1_size_impl
{
    template< typename Sequence > struct apply
        : integral_c<long,-1>
        {
        };
};

#endif // BOOST_MSVC > 1300


} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_O1_SIZE_IMPL_HPP_INCLUDED

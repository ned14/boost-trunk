//-----------------------------------------------------------------------------
// boost mpl/aux_/push_back_impl.hpp header file
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

#ifndef BOOST_MPL_AUX_PUSH_BACK_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_PUSH_BACK_IMPL_HPP_INCLUDED

#include "boost/mpl/push_back_fwd.hpp"
#include "boost/mpl/aux_/traits_lambda_spec.hpp"

namespace boost {
namespace mpl {

// no default implementation; the definition is needed to make happy the deficient
// compilers

template< typename Tag >
struct push_back_traits
{
    template< typename Sequence, typename T > struct algorithm;
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2,push_back_traits)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_AUX_PUSH_BACK_IMPL_HPP_INCLUDED

//-----------------------------------------------------------------------------
// boost mpl/prior.hpp header file
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

#ifndef BOOST_MPL_PRIOR_HPP_INCLUDED
#define BOOST_MPL_PRIOR_HPP_INCLUDED

#include "boost/mpl/aux_/lambda_spec.hpp"
#include "boost/config.hpp"

namespace boost {
namespace mpl {

template<
      typename T
    >
struct prior
{
    typedef typename T::prior type;
};

#if defined(BOOST_MSVC) && (BOOST_MSVC < 1300)
// workaround of MSVC early template instantiation bug
template<>
struct prior<int>
{
    typedef prior<int> type;
};
#endif

BOOST_MPL_AUX_LAMBDA_SPEC(1, prior)

} // namespace mpl
} // namespace boost

#endif // #ifndef BOOST_MPL_PRIOR_HPP_INCLUDED

//-----------------------------------------------------------------------------
// boost mpl/next.hpp header file
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

#ifndef BOOST_MPL_NEXT_HPP_INCLUDED
#define BOOST_MPL_NEXT_HPP_INCLUDED

#include "boost/mpl/aux_/lambda_spec.hpp"
#include "boost/config.hpp"

namespace boost {
namespace mpl {

template<
      typename T
    >
struct next
{
    typedef typename T::next type;
};

#if defined(BOOST_MSVC) && (BOOST_MSVC < 1300)
// workaround of MSVC 6.5 early template instantiation bug
template<>
struct next<int>
{
    typedef next<int> type;
};
#endif

BOOST_MPL_AUX_LAMBDA_SPEC(1, next)

} // namespace mpl
} // namespace boost

#endif // #ifndef BOOST_MPL_NEXT_HPP_INCLUDED

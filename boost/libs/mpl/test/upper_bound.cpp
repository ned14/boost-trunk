//-----------------------------------------------------------------------------
// boost mpl/test/upper_bound.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#include "boost/mpl/upper_bound.hpp"
#include "boost/mpl/range_c.hpp"
#include "boost/mpl/comparison/less.hpp"
#include "boost/mpl/int_c.hpp"
#include "boost/mpl/distance.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

#define N 100

int main()
{
    using namespace mpl::placeholder;
    typedef mpl::range_c<int,0,N+1> numbers;
    typedef mpl::upper_bound< numbers,mpl::int_c<N-1>,mpl::less<_,_> >::type iter;

    typedef mpl::begin<numbers>::type first;
    BOOST_STATIC_ASSERT((mpl::distance<first,iter>::value == N));
    return 0;
}

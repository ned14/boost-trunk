//-----------------------------------------------------------------------------
// boost mpl/test/copy.cpp source file
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

#include "boost/mpl/copy.hpp"
#include "boost/mpl/vector/vector20_c.hpp"
#include "boost/mpl/range_c.hpp"
#include "boost/mpl/push_back.hpp"
#include "boost/mpl/size.hpp"
#include "boost/mpl/equal.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

int main()
{
    typedef mpl::vector10_c<int,0,1,2,3,4,5,6,7,8,9> numbers;
    typedef mpl::copy<
          mpl::range_c<int,10,20>
        , mpl::push_back<_,_>
        , numbers
        >::type result;

    BOOST_STATIC_ASSERT(mpl::size<result>::value == 20);
    BOOST_STATIC_ASSERT((mpl::equal< result,mpl::range_c<int,0,20> >::type::value));

    return 0;
}

//-----------------------------------------------------------------------------
// boost mpl/test/advance.cpp source file
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

#include "boost/mpl/advance.hpp"
#include "boost/mpl/list.hpp"
#include "boost/mpl/assert_is_same.hpp"

namespace mpl = boost::mpl;

int main()
{
    typedef mpl::list<char,short,int,long> list;
    typedef mpl::begin<list>::type first;
    typedef mpl::advance_c<first,4>::type last;
    typedef mpl::advance_c<first,0>::type itor;

    BOOST_MPL_ASSERT_IS_SAME(last, mpl::end<list>::type);
    BOOST_MPL_ASSERT_IS_SAME(itor, first);
        
    return 0;
}

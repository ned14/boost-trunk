//-----------------------------------------------------------------------------
// boost mpl/test/count.cpp source file
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

#include "boost/mpl/count.hpp"
#include "boost/mpl/list.hpp"
//#include "boost/mpl/value_list.hpp"
#include "boost/mpl/int_c.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

int main()
{
    typedef mpl::list<int,char,long,short,char,long,double,long> types;
//    typedef mpl::value_list<1,0,5,1,7,5,0,5> values;

    BOOST_STATIC_ASSERT((mpl::count<types,int>::value == 1));
    BOOST_STATIC_ASSERT((mpl::count<types,double>::value == 1));
    BOOST_STATIC_ASSERT((mpl::count<types,char>::value == 2));
    BOOST_STATIC_ASSERT((mpl::count<types,long>::value == 3));
    BOOST_STATIC_ASSERT((mpl::count<types,unsigned>::value == 0));
    
//    BOOST_STATIC_ASSERT((mpl::count< values, mpl::int_c<1> >::value == 2));
//    BOOST_STATIC_ASSERT((mpl::count< values, mpl::int_c<0> >::value == 2));
//    BOOST_STATIC_ASSERT((mpl::count< values, mpl::int_c<5> >::value == 3));
//    BOOST_STATIC_ASSERT((mpl::count< values, mpl::int_c<7> >::value == 1));
//    BOOST_STATIC_ASSERT((mpl::count< values, mpl::int_c<8> >::value == 0));
    
    return 0;
}


// Copyright (c) Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License,Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/front.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/list_c.hpp>
#include <boost/mpl/aux_/test.hpp>

MPL_TEST_CASE()
{
    typedef list<long>::type types1;
    typedef list<int,long>::type types2;
    typedef list<char,int,long>::type types3;

    MPL_ASSERT_SAME(2,( front<types1>::type, long ));
    MPL_ASSERT_SAME(2,( front<types2>::type, int ));
    MPL_ASSERT_SAME(2,( front<types3>::type, char ));

    typedef list_c<int,1>::type values1;
    typedef list_c<int,2,1>::type values2;
    typedef list_c<int,3,2,1>::type values3;

    MPL_ASSERT_EQUAL(2,( front<values1>::type::value, 1 ));
    MPL_ASSERT_EQUAL(2,( front<values2>::type::value, 2 ));
    MPL_ASSERT_EQUAL(2,( front<values3>::type::value, 3 ));
}

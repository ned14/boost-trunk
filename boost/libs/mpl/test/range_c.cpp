
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

#include <boost/mpl/range_c.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/aux_/test.hpp>

MPL_TEST_CASE()
{
    typedef range_c<int,0,0> range0;
    typedef range_c<int,0,1> range1;
    typedef range_c<int,0,10> range10;

    MPL_ASSERT_EQUAL(2,( size<range0>::value, 0 ));
    MPL_ASSERT_EQUAL(2,( size<range1>::value, 1 ));
    MPL_ASSERT_EQUAL(2,( size<range10>::value, 10 ));

    MPL_ASSERT( empty<range0>::value );
    MPL_ASSERT( !empty<range1>::value );
    MPL_ASSERT( !empty<range10>::value );

    MPL_ASSERT_SAME(2,( begin<range0>::type, end<range0>::type ));
    MPL_ASSERT_NOT_SAME(2,( begin<range1>::type, end<range1>::type ));
    MPL_ASSERT_NOT_SAME(2,( begin<range10>::type, end<range10>::type ));

    MPL_ASSERT_EQUAL(2,( front<range1>::type::value, 0 ));
    MPL_ASSERT_EQUAL(2,( back<range1>::type::value, 0 ));
    MPL_ASSERT_EQUAL(2,( front<range10>::type::value, 0 ));
    MPL_ASSERT_EQUAL(2,( back<range10>::type::value, 9 ));
}


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

#include <boost/mpl/back.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/aux_/test.hpp>

MPL_TEST_CASE()
{
    typedef range_c<int,0,1> range1;
    typedef range_c<int,0,10> range2;
    typedef range_c<int,-10,0> range3;
    
    MPL_ASSERT_EQUAL(2,( back<range1>::type::value, 0 ));
    MPL_ASSERT_EQUAL(2,( back<range2>::type::value, 9 ));
    MPL_ASSERT_EQUAL(2,( back<range3>::type::value, -1) );
}

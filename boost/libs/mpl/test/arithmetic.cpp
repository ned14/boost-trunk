
// Copyright (c) Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/arithmetic.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/aux_/test.hpp>

MPL_TEST_CASE()
{
    typedef int_<0> _0;
    typedef int_<1> _1;
    typedef int_<3> _3;
    typedef int_<10> _10;

    MPL_ASSERT_EQUAL(3,(plus<_0,_10>::value, 10));
    MPL_ASSERT_EQUAL(3,(plus<_10,_0>::value, 10));

    MPL_ASSERT_EQUAL(3,(minus<_0,_10>::value, -10));
    MPL_ASSERT_EQUAL(3,(minus<_10,_0>::value, 10));

    MPL_ASSERT_EQUAL(3,(multiplies<_1,_10>::value, 10));
    MPL_ASSERT_EQUAL(3,(multiplies<_10,_1>::value, 10));

    MPL_ASSERT_EQUAL(3,(divides<_10,_1>::value, 10));
    MPL_ASSERT_EQUAL(3,(divides<_10,_1>::value, 10));

    MPL_ASSERT_EQUAL(3,(modulus<_10,_1>::value, 0));
    MPL_ASSERT_EQUAL(3,(modulus<_10,_3>::value, 1));

    MPL_ASSERT_EQUAL(4,(minus<_10,_1,_10>::value, -1));
    MPL_ASSERT_EQUAL(4,(plus<_10,_1,_10>::value, 21));
    MPL_ASSERT_EQUAL(4,(divides<_10,_1,_10>::value, 1));
    MPL_ASSERT_EQUAL(4,(divides<_10,_1,_10>::value, 1));
    
    MPL_ASSERT_EQUAL(2,(negate<_10>::value, -10));
}

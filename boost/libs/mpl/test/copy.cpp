
// Copyright (c) Aleksey Gurtovoy 2000-2004
// Copyright (c) David Abrahams 2003-2004
//
// Use, modification and distribution are subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy 
// at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/copy.hpp>
#include <boost/mpl/vector/vector20_c.hpp>
#include <boost/mpl/vector/vector0.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/front_inserter.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/equal.hpp>

#include <boost/mpl/aux_/test/test.hpp>


MPL_TEST_CASE()
{
    typedef vector10_c<int,9,8,7,6,5,4,3,2,1,0> answer;
    typedef copy<
          range_c<int,0,10>
        , front_inserter< vector0<> >
        >::type result;

    MPL_ASSERT_EQUAL(2,( size<result>::value, 10 ));
    MPL_ASSERT(( equal< result,answer >::value ));
}

MPL_TEST_CASE()
{
    typedef vector10_c<int,10,11,12,13,14,15,16,17,18,19> numbers;
    typedef reverse_copy<
          range_c<int,0,10>
        , front_inserter<numbers>
        >::type result;

    MPL_ASSERT_EQUAL(2,( size<result>::value, 20 ));
    MPL_ASSERT(( equal< result,range_c<int,0,20> >::value ));
}

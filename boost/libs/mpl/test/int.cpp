
// Copyright (c) Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License,Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/int.hpp>
#include <boost/mpl/aux_/test.hpp>
#include <boost/preprocessor/repeat.hpp>

#include <cassert>

#define INT_C_TEST(unused1, i, unused2) \
    { MPL_ASSERT_SAME(2,(int_<i>::value_type, int)); } \
    { MPL_ASSERT_SAME(2,(int_<i>::type, int_<i>)); } \
    { MPL_ASSERT_SAME(2,(int_<i>::next, int_<i+1>)); } \
    { MPL_ASSERT_SAME(2,(int_<i>::prior, int_<i-1>)); } \
    { MPL_ASSERT_EQUAL(2,(int_<i>::value, i)); } \
    assert(int_<i>() == i); \
/**/

MPL_TEST_CASE()
{
    BOOST_PP_REPEAT(10, INT_C_TEST, unused)
}


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

#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/test.hpp>

#include <cassert>

#define BOOL_C_TEST(c) \
    { MPL_ASSERT_SAME(2,( bool_<c>::value_type, bool )); } \
    { MPL_ASSERT_SAME(2,( bool_<c>, c##_ )); } \
    { MPL_ASSERT_SAME(2,( bool_<c>::type, bool_<c> )); } \
    { MPL_ASSERT_EQUAL(2,( bool_<c>::value, c )); } \
    assert(bool_<c>() == c); \
/**/

MPL_TEST_CASE()
{
    BOOL_C_TEST(true)
    BOOL_C_TEST(false)
}

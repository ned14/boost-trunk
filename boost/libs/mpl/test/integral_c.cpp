
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

#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/aux_/test.hpp>
#include <boost/preprocessor/repeat.hpp>

#include <cassert>


#define INTEGRAL_C_TEST(z, i, T) \
    { \
        typedef integral_c<T,i> c##i; \
        typedef integral_c<T,i+1> next_c##i; \
        typedef integral_c<T,i-1> prior_c##i; \
        { MPL_ASSERT_SAME(2,(c##i::value_type, T)); } \
        { MPL_ASSERT_SAME(2,(c##i::type, c##i)); } \
        { MPL_ASSERT_SAME(2,(c##i::next, next_c##i)); } \
        { MPL_ASSERT_SAME(2,(c##i::prior, prior_c##i)); } \
        { MPL_ASSERT_EQUAL(2,(c##i::value, i)); } \
        assert(c##i() == i); \
    } \
/**/

MPL_TEST_CASE()
{
    BOOST_PP_REPEAT(10, INTEGRAL_C_TEST, char)
    BOOST_PP_REPEAT(10, INTEGRAL_C_TEST, short)
    BOOST_PP_REPEAT(10, INTEGRAL_C_TEST, int)
}

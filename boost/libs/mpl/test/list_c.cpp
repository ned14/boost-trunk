
// Copyright (c) Aleksey Gurtovoy 2000-2004
//
// Use, modification and distribution are subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy 
// at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/list_c.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/size.hpp>
#include <boost/static_assert.hpp>

#include <boost/mpl/aux_/test/test.hpp>


#if !BOOST_WORKAROUND(BOOST_MSVC,<= 1200)
MPL_TEST_CASE()
{
    typedef list_c<bool,true>::type list1;
    typedef list_c<bool,false>::type list2;

    MPL_ASSERT_EQUAL(2,( front<list1>::type::value, true ));
    MPL_ASSERT_EQUAL(2,( front<list2>::type::value, false ));
}
#endif

MPL_TEST_CASE()
{
    typedef list_c<int,-1>::type list1;
    typedef list_c<int,0,1>::type list2;
    typedef list_c<int,1,2,3>::type list3;

    MPL_ASSERT_EQUAL(2,( size<list1>::value, 1 ));
    MPL_ASSERT_EQUAL(2,( size<list2>::value, 2 ));
    MPL_ASSERT_EQUAL(2,( size<list3>::value, 3 ));
    MPL_ASSERT_EQUAL(2,( front<list1>::type::value, -1 ));
    MPL_ASSERT_EQUAL(2,( front<list2>::type::value, 0 ));
    MPL_ASSERT_EQUAL(2,( front<list3>::type::value, 1 ));
}

MPL_TEST_CASE()
{
    typedef list_c<unsigned,0>::type list1;
    typedef list_c<unsigned,1,2>::type list2;

    MPL_ASSERT_EQUAL(2,( size<list1>::value, 1 ));
    MPL_ASSERT_EQUAL(2,( size<list2>::value, 2 ));
    MPL_ASSERT_EQUAL(2,( front<list1>::type::value, 0 ));
    MPL_ASSERT_EQUAL(2,( front<list2>::type::value, 1 ));
}


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

#include <boost/mpl/list.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/empty.hpp>

#include <boost/mpl/aux_/test/test.hpp>


MPL_TEST_CASE()
{
    typedef list0<> l0;
    typedef list1<char> l1;
    typedef list2<char,long> l2;
    typedef list9<char,char,char,char,char,char,char,char,char> l9;

    MPL_ASSERT_EQUAL(2,( size<l0>::value, 0 ));
    MPL_ASSERT_EQUAL(2,( size<l1>::value, 1 ));
    MPL_ASSERT_EQUAL(2,( size<l2>::value, 2 ));
    MPL_ASSERT_EQUAL(2,( size<l9>::value, 9 ));

    MPL_ASSERT( empty<l0>::value );
    MPL_ASSERT( !empty<l1>::value );
    MPL_ASSERT( !empty<l2>::value );
    MPL_ASSERT( !empty<l9>::value );

    MPL_ASSERT_SAME(2,( front<l1>::type,char ));
    MPL_ASSERT_SAME(2,( front<l2>::type,char ));
    MPL_ASSERT_SAME(2,( front<l9>::type,char ));
}

MPL_TEST_CASE()
{
    typedef list0<> l0;

    typedef push_front<l0,char>::type l1;
    MPL_ASSERT_SAME(2,( front<l1>::type,char ));

    typedef push_front<l1,long>::type l2;
    MPL_ASSERT_SAME(2,( front<l2>::type,long ));
}

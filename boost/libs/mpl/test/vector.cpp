
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

#include <boost/mpl/vector.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/pop_back.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/empty.hpp>

#include <boost/mpl/aux_/test/test.hpp>


MPL_TEST_CASE()
{
    typedef vector0<> v0;
    typedef vector1<char> v1;
    typedef vector2<char,long> v2;
    typedef vector9<char,char,char,char,char,char,char,char,int> v9;

    MPL_ASSERT_EQUAL(2,( size<v0>::value, 0 ));
    MPL_ASSERT_EQUAL(2,( size<v1>::value, 1 ));
    MPL_ASSERT_EQUAL(2,( size<v2>::value, 2 ));
    MPL_ASSERT_EQUAL(2,( size<v9>::value, 9 ));

    MPL_ASSERT( empty<v0>::value );
    MPL_ASSERT( !empty<v1>::value );
    MPL_ASSERT( !empty<v2>::value );
    MPL_ASSERT( !empty<v9>::value );

    MPL_ASSERT_SAME(2,( front<v1>::type,char ));
    MPL_ASSERT_SAME(2,( back<v1>::type,char ));
    MPL_ASSERT_SAME(2,( front<v2>::type,char ));
    MPL_ASSERT_SAME(2,( back<v2>::type,long ));
    MPL_ASSERT_SAME(2,( front<v9>::type,char ));
    MPL_ASSERT_SAME(2,( back<v9>::type,int ));
}

MPL_TEST_CASE()
{
    typedef vector0<> v0;

    typedef push_back<v0,int>::type v1;
    MPL_ASSERT_SAME(2,( back<v1>::type,int ));

    typedef push_front<v1,char>::type v2;
    MPL_ASSERT_SAME(2,( back<v2>::type,int ));
    MPL_ASSERT_SAME(2,( front<v2>::type,char ));

    typedef push_back<v2,long>::type v3;
    MPL_ASSERT_SAME(2,( back<v3>::type,long ));
}

MPL_TEST_CASE()
{
    typedef vector<> v0;
    typedef vector<char> v1;
    typedef vector<char,long> v2;
    typedef vector<char,char,char,char,char,char,char,char,int> v9;

    MPL_ASSERT_EQUAL(2,( size<v0>::value, 0 ));
    MPL_ASSERT_EQUAL(2,( size<v1>::value, 1 ));
    MPL_ASSERT_EQUAL(2,( size<v2>::value, 2 ));
    MPL_ASSERT_EQUAL(2,( size<v9>::value, 9 ));
}

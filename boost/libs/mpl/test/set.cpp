
// Copyright (c) Aleksey Gurtovoy 2003-2004
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

#include <boost/mpl/set.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/order.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/begin_end.hpp>

#include <boost/mpl/aux_/test/test.hpp>


MPL_TEST_CASE()
{
    typedef s_mask<char,s_item<int,s_item<char, set0<> > > > s;

    MPL_ASSERT_EQUAL(2,( size<s>::value, 1 ));
    MPL_ASSERT(( !empty<s>::value ));
    
    MPL_ASSERT_SAME(2,( clear<s>::type, set0<> ));
    MPL_ASSERT_SAME(3,( at<s,int>::type, int ));
    MPL_ASSERT_SAME(3,( at<s,char>::type, void_ ));

    MPL_ASSERT(( !has_key<s,char>::value ));
    MPL_ASSERT(( has_key<s,int>::value ));
    MPL_ASSERT_EQUAL(3,( order<s,int>::value, 2 ));
    MPL_ASSERT_SAME(3,( order<s,char>::type, void_ ));
    
    typedef begin<s>::type first;
    typedef end<s>::type last;

    MPL_ASSERT_SAME(2,( first::type, int ));
    MPL_ASSERT_SAME(2,( next<first>::type, last ));

    typedef s_unmask<char,s> s2;

    MPL_ASSERT_EQUAL(2,( size<s2>::value, 2 ));
    MPL_ASSERT(( !empty<s2>::value ));
    MPL_ASSERT_SAME(2,( clear<s2>::type, set0<> ));
    MPL_ASSERT_SAME(3,( at<s2,int>::type, int ));
    MPL_ASSERT_SAME(3,( at<s2,char>::type, char ));

    MPL_ASSERT(( has_key<s2,char>::value ));
    MPL_ASSERT(( !has_key<s2,long>::value ));
    MPL_ASSERT_EQUAL(3,( order<s2,int>::value, 2 ));
    MPL_ASSERT_EQUAL(3,( order<s2,char>::value, 1 ));

    typedef begin<s2>::type first2;
    typedef end<s2>::type last2;

    MPL_ASSERT_SAME(2,( first2::type, int ));
    typedef next<first2>::type iter;
    MPL_ASSERT_SAME(2,( iter::type, char ));
    MPL_ASSERT_SAME(2,( next<iter>::type, last2 ));

    typedef insert<s2,int>::type s2_1;
    MPL_ASSERT_SAME(2,( s2, s2_1 ));

    typedef insert<s2,long>::type s3;
    MPL_ASSERT_EQUAL(2,( size<s3>::value, 3 ));
    MPL_ASSERT(( has_key<s3,long>::value ));
    MPL_ASSERT(( has_key<s3,int>::value ));
    MPL_ASSERT(( has_key<s3,char>::value ));

    typedef insert<s,char>::type s1;
    MPL_ASSERT_EQUAL(2,( size<s1>::value, 2 ));
    MPL_ASSERT_SAME(3,( at<s1,int>::type, int ));
    MPL_ASSERT_SAME(3,( at<s1,char>::type, char ));
    MPL_ASSERT_NOT_SAME(2,( s1, s2 ));

    typedef erase<s1,char>::type s_1;
    MPL_ASSERT_SAME(2,( s, s_1 ));
    MPL_ASSERT_EQUAL(2,( size<s_1>::value, 1 ));
    MPL_ASSERT_SAME(3,( at<s_1,char>::type, void_ ));
    MPL_ASSERT_SAME(3,( at<s_1,int>::type, int ));
    
}

MPL_TEST_CASE()
{
    typedef set0<> s;
    
    MPL_ASSERT(( size<s>::value == 0 ));
    MPL_ASSERT(( empty<s>::value ));
    MPL_ASSERT_SAME(2,( clear<s>::type, set0<> ));
    MPL_ASSERT_SAME(3,( at<s,char>::type, void_ ));

    MPL_ASSERT(( !has_key<s,char>::value ));
    MPL_ASSERT(( !has_key<s,int>::value ));
    MPL_ASSERT(( !has_key<s,UDT>::value ));
    MPL_ASSERT(( !has_key<s,incomplete>::value ));

    MPL_ASSERT(( !has_key<s,char const>::value ));
    MPL_ASSERT(( !has_key<s,int const>::value ));
    MPL_ASSERT(( !has_key<s,UDT const>::value ));
    MPL_ASSERT(( !has_key<s,incomplete const>::value ));

    MPL_ASSERT(( !has_key<s,int*>::value ));
    MPL_ASSERT(( !has_key<s,UDT*>::value ));
    MPL_ASSERT(( !has_key<s,incomplete*>::value ));

    MPL_ASSERT(( !has_key<s,int&>::value ));
    MPL_ASSERT(( !has_key<s,UDT&>::value ));
    MPL_ASSERT(( !has_key<s,incomplete&>::value ));

    typedef insert<s,char>::type s1;
    MPL_ASSERT_EQUAL(2,( size<s1>::value, 1 ));
    MPL_ASSERT_SAME(3,( at<s1,char>::type, char ));

    typedef erase<s,char>::type s0_1;
    MPL_ASSERT_EQUAL(2,( size<s0_1>::value, 0 ));
    MPL_ASSERT_SAME(3,( at<s0_1,char>::type, void_ ));
}

MPL_TEST_CASE()
{
    typedef set<
          char,int const,long*,UDT* const,incomplete,abstract
        , incomplete volatile&,abstract const&
        > s;
    
    MPL_ASSERT(( size<s>::value == 8 ));
    MPL_ASSERT(( !empty<s>::value ));
    MPL_ASSERT_SAME(2,( clear<s>::type, set0<> ));
    MPL_ASSERT_SAME(3,( at<s,bool>::type, void_ ));

    MPL_ASSERT(( has_key<s,char>::value ));
    MPL_ASSERT(( has_key<s,int const>::value ));
    MPL_ASSERT(( has_key<s,long*>::value ));
    MPL_ASSERT(( has_key<s,UDT* const>::value ));
    MPL_ASSERT(( has_key<s,incomplete>::value ));
    MPL_ASSERT(( has_key<s,abstract>::value ));
    MPL_ASSERT(( has_key<s,incomplete volatile&>::value ));
    MPL_ASSERT(( has_key<s,abstract const&>::value ));

    MPL_ASSERT(( !has_key<s,char const>::value ));
    MPL_ASSERT(( !has_key<s,int>::value ));
    MPL_ASSERT(( !has_key<s,long* const>::value ));
    MPL_ASSERT(( !has_key<s,UDT*>::value ));
    MPL_ASSERT(( !has_key<s,incomplete const>::value ));
    MPL_ASSERT(( !has_key<s,abstract volatile>::value ));
    MPL_ASSERT(( !has_key<s,incomplete&>::value ));
    MPL_ASSERT(( !has_key<s,abstract&>::value ));
}


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

#include <boost/mpl/set/set0.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/order.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/begin_end.hpp>

//#include <boost/mpl/aux_/test.hpp>

using namespace boost::mpl;
using namespace boost;
/*
CTT_test_case( false_positives, (S)(T) )
    {
    CTT_assert(( !has_key<S,T>::type::value )); // notation test
    CTT_assert(( !has_key<S,T>::value ));

    CTT_assert_same(3, (BOOST_MSVC_TYPENAME order<S,T>::type, void_));
    }

CTT_test_case( empty_set, (T) )
    {
    typedef set0<> s;
    
    CTT_for_each( 
          (T) CTT_basic_modifiers(T)
        , false_positives
        , (s)(_1)
        );
    }

CTT_test_case( one_element_set, (T) )
    {
    typedef s_item<T, set0<> > s;

    CTT_for_each( 
          CTT_basic_modifiers(T)
        , false_positives
        , (s)(_1)
        );
    
    CTT_assert(( has_key<s,T>::type::value )); // notation test
    CTT_assert(( has_key<s,T>::value ));
    
    CTT_assert_equal(3, (order<s,T>::type::value, 1)); // notation test
    CTT_assert_equal(3, (order<s,T>::value, 1));
    }

CTT_test_case( insertion, (T) )
    {
    typedef s_item<T, set0<> > s1;
    typedef typename insert< set0<>,T >::type s2;

    CTT_assert_same(2, (s1, s2));
    }


CTT_test_case( erasure, (T) )
{
    typedef s_mask<char,s_item<int,s_item<char, set0<> > > > s;

    CTT_TEST_ASSERT(( !has_key<s,char>::type::value ));
    CTT_TEST_ASSERT(( has_key<s,int>::type::value ));
    CTT_TEST_ASSERT(( order<s,int>::type::value == 1 ));
    CTT_TEST_ASSERT(( is_same< order<s,char>::type,void_ >::value ));
    
    typedef begin<s>::type first;
    typedef end<s>::type last;

    CTT_TEST_ASSERT(( is_same<first::type,int>::value ));
    CTT_TEST_ASSERT(( is_same<first::next,last>::value ));

}
*/

#define MPL_TEST_CASE( test_name ) void test_name()
#define MPL_TEST_ASSERT( expr ) BOOST_STATIC_ASSERT( expr )


MPL_TEST_CASE( has_key_test2 )
{
    typedef s_mask<char,s_item<int,s_item<char, set0<> > > > s;

    MPL_TEST_ASSERT(( size<s>::type::value == 1 ));
    MPL_TEST_ASSERT(( !empty<s>::type::value ));
    MPL_TEST_ASSERT(( is_same< clear<s>::type,set0<> >::value ));
    MPL_TEST_ASSERT(( is_same< at<s,int>::type,int >::value ));
    MPL_TEST_ASSERT(( is_same< at<s,char>::type,void_ >::value ));

    MPL_TEST_ASSERT(( !has_key<s,char>::type::value ));
    MPL_TEST_ASSERT(( has_key<s,int>::type::value ));
    MPL_TEST_ASSERT(( order<s,int>::type::value == 1 ));
    MPL_TEST_ASSERT(( is_same< order<s,char>::type,void_ >::value ));
    
    typedef begin<s>::type first;
    typedef end<s>::type last;

    MPL_TEST_ASSERT(( is_same<first::type,int>::value ));
    MPL_TEST_ASSERT(( is_same< next<first>::type,last >::value ));

    typedef s_unmask<char,s> s2;

    MPL_TEST_ASSERT(( size<s2>::type::value == 2 ));
    MPL_TEST_ASSERT(( !empty<s2>::type::value ));
    MPL_TEST_ASSERT(( is_same< clear<s2>::type,set0<> >::value ));
    MPL_TEST_ASSERT(( is_same< at<s2,int>::type,int >::value ));
    MPL_TEST_ASSERT(( is_same< at<s2,char>::type,char >::value ));

    MPL_TEST_ASSERT(( has_key<s2,char>::type::value ));
    MPL_TEST_ASSERT(( !has_key<s2,long>::type::value ));
    MPL_TEST_ASSERT(( order<s2,int>::type::value == 1 ));
    //MPL_TEST_ASSERT(( order<s2,char>::type::value == 2 ));

    typedef begin<s2>::type first2;
    typedef end<s2>::type last2;

    MPL_TEST_ASSERT(( is_same<first2::type,int>::value ));
    typedef next<first2>::type iter;
    MPL_TEST_ASSERT(( is_same<iter::type,char>::value ));
    MPL_TEST_ASSERT(( is_same< next<iter>::type,last2 >::value ));

    typedef insert<s2,int>::type s2_1;
    MPL_TEST_ASSERT(( is_same<s2,s2_1>::value ));

    typedef insert<s2,long>::type s3;
    MPL_TEST_ASSERT(( size<s3>::type::value == 3 ));
    MPL_TEST_ASSERT(( has_key<s3,long>::type::value ));
    MPL_TEST_ASSERT(( has_key<s3,int>::type::value ));
    MPL_TEST_ASSERT(( has_key<s3,char>::type::value ));

    typedef insert<s,char>::type s1;
    MPL_TEST_ASSERT(( size<s1>::type::value == 2 ));
    MPL_TEST_ASSERT(( is_same< at<s1,int>::type,int >::value ));
    MPL_TEST_ASSERT(( is_same< at<s1,char>::type,char >::value ));
    MPL_TEST_ASSERT(( !is_same< s1,s2 >::value ));

    typedef erase<s1,char>::type s_1;
    MPL_TEST_ASSERT(( is_same<s,s_1>::value ));
    MPL_TEST_ASSERT(( size<s_1>::type::value == 1 ));
    MPL_TEST_ASSERT(( is_same< at<s_1,char>::type,void_ >::value ));
    MPL_TEST_ASSERT(( is_same< at<s_1,int>::type,int >::value ));
    
}

struct UDT {};
struct incomplete;


MPL_TEST_CASE( empty_set_test )
{
    typedef set0<> s;
    
    MPL_TEST_ASSERT(( size<s>::type::value == 0 ));
    MPL_TEST_ASSERT(( empty<s>::type::value ));
    MPL_TEST_ASSERT(( is_same< clear<s>::type,set0<> >::value ));
    MPL_TEST_ASSERT(( is_same< at<s,char>::type,void_ >::value ));

    MPL_TEST_ASSERT(( !has_key<s,char>::type::value ));
    MPL_TEST_ASSERT(( !has_key<s,int>::type::value ));
    MPL_TEST_ASSERT(( !has_key<s,UDT>::type::value ));
    MPL_TEST_ASSERT(( !has_key<s,incomplete>::type::value ));

    MPL_TEST_ASSERT(( !has_key<s,char const>::type::value ));
    MPL_TEST_ASSERT(( !has_key<s,int const>::type::value ));
    MPL_TEST_ASSERT(( !has_key<s,UDT const>::type::value ));
    MPL_TEST_ASSERT(( !has_key<s,incomplete const>::type::value ));

    MPL_TEST_ASSERT(( !has_key<s,int*>::type::value ));
    MPL_TEST_ASSERT(( !has_key<s,UDT*>::type::value ));
    MPL_TEST_ASSERT(( !has_key<s,incomplete*>::type::value ));

    MPL_TEST_ASSERT(( !has_key<s,int&>::type::value ));
    MPL_TEST_ASSERT(( !has_key<s,UDT&>::type::value ));
    MPL_TEST_ASSERT(( !has_key<s,incomplete&>::type::value ));

    typedef insert<s,char>::type s1;
    MPL_TEST_ASSERT(( size<s1>::type::value == 1 ));
    MPL_TEST_ASSERT(( is_same< at<s1,char>::type,char >::value ));

    typedef erase<s,char>::type s0_1;
    MPL_TEST_ASSERT(( size<s0_1>::type::value == 0 ));
    MPL_TEST_ASSERT(( is_same< at<s0_1,char>::type,void_ >::value ));

}


int main()
{
//    CTT_for_each( CTT_basic_types(), empty_set, (_1));
//    CTT_for_each( CTT_basic_types(), one_element_set, (_1));
//    CTT_for_each( CTT_basic_types(), insertion, (_1));

    return 0;
}

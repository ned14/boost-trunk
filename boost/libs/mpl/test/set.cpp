
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

#include "boost/mpl/set/set0.hpp"
#include "boost/mpl/insert.hpp"
#include "boost/mpl/has_key.hpp"
#include "boost/mpl/order.hpp"
#include "boost/mpl/begin_end.hpp"

//#include "boost/mpl/aux_/test.hpp"

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

    MPL_TEST_ASSERT(( !has_key<s,char>::type::value ));
    MPL_TEST_ASSERT(( has_key<s,int>::type::value ));
//    MPL_TEST_ASSERT(( order<s,int>::type::value == 2 ));
    MPL_TEST_ASSERT(( is_same< order<s,char>::type,void_ >::value ));
    
    typedef begin<s>::type first;
    typedef end<s>::type last;

    MPL_TEST_ASSERT(( is_same<first::type,int>::value ));
    MPL_TEST_ASSERT(( is_same< next<first>::type,last >::value ));

    typedef s_unmask<char,s> s2;

    MPL_TEST_ASSERT(( has_key<s2,char>::type::value ));

    typedef begin<s2>::type first2;
    typedef end<s2>::type last2;

    MPL_TEST_ASSERT(( is_same<first2::type,int>::value ));
    typedef next<first2>::type iter;
    MPL_TEST_ASSERT(( is_same<iter::type,char>::value ));
    MPL_TEST_ASSERT(( is_same< next<iter>::type,last2 >::value ));
}

struct UDT {};
struct incomplete;


MPL_TEST_CASE( empty_set_test )
{
    typedef set0<> s;
    
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

}


int main()
{
//    CTT_for_each( CTT_basic_types(), empty_set, (_1));
//    CTT_for_each( CTT_basic_types(), one_element_set, (_1));
//    CTT_for_each( CTT_basic_types(), insertion, (_1));

    return 0;
}

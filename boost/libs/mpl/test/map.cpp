
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

#include "boost/mpl/map/map0.hpp"
#include "boost/mpl/insert.hpp"
#include "boost/mpl/erase.hpp"
#include "boost/mpl/contains.hpp"
#include "boost/mpl/at.hpp"
#include "boost/mpl/clear.hpp"
#include "boost/mpl/has_key.hpp"
#include "boost/mpl/order.hpp"
#include "boost/mpl/size.hpp"
#include "boost/mpl/empty.hpp"
#include "boost/mpl/begin_end.hpp"
#include "boost/mpl/print.hpp"

//#include "boost/mpl/aux_/test.hpp"

using namespace boost::mpl;
using namespace boost;

#define MPL_TEST_CASE( test_name ) void test_name()
#define MPL_TEST_ASSERT( expr ) BOOST_STATIC_ASSERT( expr )


MPL_TEST_CASE( map_test2 )
{
#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
    typedef   m_mask<char
            , m_item<int,unsigned
            , m_item<char,unsigned char
            , map0<> > > > m;
#else
    typedef   m_mask<char
            , m_item2<int,unsigned
            , m_item1<char,unsigned char
            , map0<> > > > m;
#endif

    MPL_TEST_ASSERT(( size<m>::type::value == 1 ));
    MPL_TEST_ASSERT(( !empty<m>::type::value ));
    MPL_TEST_ASSERT(( is_same< clear<m>::type,map0<> >::value ));
    MPL_TEST_ASSERT(( is_same< at<m,int>::type,unsigned>::value ));
    MPL_TEST_ASSERT(( is_same< at<m,char>::type,void_ >::value ));
    MPL_TEST_ASSERT(( contains< m,pair<int,unsigned> >::value ));
    MPL_TEST_ASSERT(( !contains< m,pair<int,int> >::value ));
    MPL_TEST_ASSERT(( !contains< m,pair<char,unsigned char> >::value ));

    MPL_TEST_ASSERT(( !has_key<m,char>::type::value ));
    MPL_TEST_ASSERT(( has_key<m,int>::type::value ));
    MPL_TEST_ASSERT(( order<m,int>::type::value == 3 ));
    MPL_TEST_ASSERT(( is_same< item_by_order<m,3>::type,pair<int,unsigned> >::value ));
    MPL_TEST_ASSERT(( is_same< order<m,char>::type,void_ >::value ));

    typedef begin<m>::type first;
    typedef end<m>::type last;

    MPL_TEST_ASSERT(( is_same< first::type,pair<int,unsigned> >::value ));
    MPL_TEST_ASSERT(( is_same< next<first>::type,last >::value ));

    typedef m_item<char,long,m> m2;

    MPL_TEST_ASSERT(( size<m2>::type::value == 2 ));
    MPL_TEST_ASSERT(( !empty<m2>::type::value ));
    MPL_TEST_ASSERT(( is_same< clear<m2>::type,map0<> >::value ));
    MPL_TEST_ASSERT(( is_same< at<m2,int>::type,unsigned >::value ));
    MPL_TEST_ASSERT(( is_same< at<m2,char>::type,long >::value ));

    MPL_TEST_ASSERT(( contains< m2,pair<int,unsigned> >::value ));
    MPL_TEST_ASSERT(( !contains< m2,pair<int,int> >::value ));
    MPL_TEST_ASSERT(( !contains< m2,pair<char,unsigned char> >::value ));
    MPL_TEST_ASSERT(( contains< m2,pair<char,long> >::value ));

    MPL_TEST_ASSERT(( has_key<m2,char>::type::value ));
    MPL_TEST_ASSERT(( !has_key<m2,long>::type::value ));
    MPL_TEST_ASSERT(( order<m2,int>::type::value == 3 ));
    MPL_TEST_ASSERT(( order<m2,char>::type::value == 4 ));

    typedef begin<m2>::type first2;
    typedef end<m2>::type last2;

    MPL_TEST_ASSERT(( is_same<first2::type,pair<int,unsigned> >::value ));
    typedef next<first2>::type iter;
    MPL_TEST_ASSERT(( is_same<iter::type,pair<char,long> >::value ));
    MPL_TEST_ASSERT(( is_same< next<iter>::type,last2 >::value ));

    typedef insert<m2,pair<int,unsigned> >::type s2_1;
    MPL_TEST_ASSERT(( is_same<m2,s2_1>::value ));

    typedef insert<m2,pair<long,unsigned> >::type m3;
    MPL_TEST_ASSERT(( size<m3>::type::value == 3 ));
    MPL_TEST_ASSERT(( has_key<m3,long>::type::value ));
    MPL_TEST_ASSERT(( has_key<m3,int>::type::value ));
    MPL_TEST_ASSERT(( has_key<m3,char>::type::value ));
    MPL_TEST_ASSERT(( contains< m3,pair<long,unsigned> >::value ));
    MPL_TEST_ASSERT(( contains< m3,pair<int,unsigned> >::value ));

    typedef insert<m,pair<char,long> >::type m1;
    MPL_TEST_ASSERT(( size<m1>::type::value == 2 ));
    MPL_TEST_ASSERT(( is_same< at<m1,int>::type,unsigned >::value ));
    MPL_TEST_ASSERT(( is_same< at<m1,char>::type,long >::value ));

    MPL_TEST_ASSERT(( contains< m1,pair<int,unsigned> >::value ));
    MPL_TEST_ASSERT(( !contains< m1,pair<int,int> >::value ));
    MPL_TEST_ASSERT(( !contains< m1,pair<char,unsigned char> >::value ));
    MPL_TEST_ASSERT(( contains< m1,pair<char,long> >::value ));

    MPL_TEST_ASSERT(( is_same< m1,m2 >::value ));

    typedef erase<m1,char>::type m_1;
    MPL_TEST_ASSERT(( is_same<m,m_1>::value ));
    MPL_TEST_ASSERT(( size<m_1>::type::value == 1 ));
    MPL_TEST_ASSERT(( is_same< at<m_1,char>::type,void_ >::value ));
    MPL_TEST_ASSERT(( is_same< at<m_1,int>::type,unsigned >::value ));

    typedef erase<m3,char>::type m2_1;
    MPL_TEST_ASSERT(( size<m2_1>::type::value == 2 ));
    MPL_TEST_ASSERT(( is_same< at<m2_1,char>::type,void_ >::value ));
    MPL_TEST_ASSERT(( is_same< at<m2_1,int>::type,unsigned >::value ));
    MPL_TEST_ASSERT(( is_same< at<m2_1,long>::type,unsigned >::value ));
  
}

struct UDT {};
struct incomplete;


MPL_TEST_CASE( empty_map_test )
{
    typedef map0<> m;
    
    MPL_TEST_ASSERT(( size<m>::type::value == 0 ));
    MPL_TEST_ASSERT(( empty<m>::type::value ));
    
    MPL_TEST_ASSERT(( is_same< clear<m>::type,map0<> >::value ));
    MPL_TEST_ASSERT(( is_same< at<m,char>::type,void_ >::value ));

    MPL_TEST_ASSERT(( !has_key<m,char>::type::value ));
    MPL_TEST_ASSERT(( !has_key<m,int>::type::value ));
    MPL_TEST_ASSERT(( !has_key<m,UDT>::type::value ));
    MPL_TEST_ASSERT(( !has_key<m,incomplete>::type::value ));

    MPL_TEST_ASSERT(( !has_key<m,char const>::type::value ));
    MPL_TEST_ASSERT(( !has_key<m,int const>::type::value ));
    MPL_TEST_ASSERT(( !has_key<m,UDT const>::type::value ));
    MPL_TEST_ASSERT(( !has_key<m,incomplete const>::type::value ));

    MPL_TEST_ASSERT(( !has_key<m,int*>::type::value ));
    MPL_TEST_ASSERT(( !has_key<m,UDT*>::type::value ));
    MPL_TEST_ASSERT(( !has_key<m,incomplete*>::type::value ));

    MPL_TEST_ASSERT(( !has_key<m,int&>::type::value ));
    MPL_TEST_ASSERT(( !has_key<m,UDT&>::type::value ));
    MPL_TEST_ASSERT(( !has_key<m,incomplete&>::type::value ));

    typedef insert<m,pair<char,int> >::type m1;
    MPL_TEST_ASSERT(( size<m1>::type::value == 1 ));
    MPL_TEST_ASSERT(( is_same< at<m1,char>::type,int >::value ));

    typedef erase<m,char>::type m0_1;
    MPL_TEST_ASSERT(( size<m0_1>::type::value == 0 ));
    MPL_TEST_ASSERT(( is_same< at<m0_1,char>::type,void_ >::value ));
}


int main()
{
    return 0;
}


// Copyright (c) Aleksey Gurtovoy 2000-2004
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

#include "boost/mpl/copy_if.hpp"
#include "boost/mpl/list/list10_c.hpp"
#include "boost/mpl/list/list10.hpp"
#include "boost/mpl/front_inserter.hpp"
#include "boost/mpl/less.hpp"
#include "boost/mpl/int.hpp"
#include "boost/mpl/equal.hpp"
#include "boost/mpl/size.hpp"
#include "boost/type_traits/is_float.hpp"
#include "boost/static_assert.hpp"

using namespace boost;
using namespace mpl;

#define MPL_TEST_CASE( test_name ) void test_name()
#define MPL_TEST_ASSERT( expr ) BOOST_STATIC_ASSERT( expr )

MPL_TEST_CASE( copy_if_test )
{
    typedef list10_c<int,0,1,2,3,4,5,6,7,8,9>::type numbers;
    typedef list5_c<int,4,3,2,1,0>::type answer;
    typedef copy_if<
          numbers
        , less<_,int_<5> >
        , front_inserter< list0_c<int> >
        >::type result;

    MPL_TEST_ASSERT( size<result>::value == 5 );
    MPL_TEST_ASSERT(( equal<result,answer>::value ));
}

MPL_TEST_CASE( reverse_copy_if_test )
{
    typedef list8<int,float,long,float,char,long,double,double>::type types;
    typedef list4<float,float,double,double>::type float_types;
    typedef reverse_copy_if<
          types
        , is_float<_>
        , front_inserter< list0<> >
        >::type result;

    MPL_TEST_ASSERT( mpl::size<result>::value == 4 );
    MPL_TEST_ASSERT(( mpl::equal<result,result>::value ));
}

int main()
{
    return 0;
}

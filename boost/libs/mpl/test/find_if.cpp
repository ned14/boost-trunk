
// Copyright (c) Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License,Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/find_if.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/aux_/test.hpp>

#include <boost/type_traits/is_float.hpp>
#include <boost/type_traits/is_same.hpp>


MPL_TEST_CASE()
{
    typedef list9<int,char,long,short,char,long,double,float,char>::type types;

    typedef find_if< types, boost::is_float<_> >::type iter1;
    typedef find_if< types, boost::is_same<_,long> >::type iter2;
    typedef find_if< types, boost::is_same<_,void> >::type iter3;

    MPL_ASSERT_SAME(2,( iter1::type, double ));
    MPL_ASSERT_SAME(2,( iter2::type, long ));
    MPL_ASSERT_SAME(2,( iter3, end<types>::type ));

    typedef begin<types>::type first;
    MPL_ASSERT_EQUAL(3,( distance<first,iter1>::value, 6 ));
    MPL_ASSERT_EQUAL(3,( distance<first,iter2>::value, 2 ));
}


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

#include <boost/mpl/erase.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/list_c.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/aux_/test.hpp>

MPL_TEST_CASE()
{
    typedef list<int,char,long,short,char,long,double,long> types;
    typedef list_c<int,1,0,5,1,7,5,0,5> values;

    typedef find<types,short>::type types_iter;
    typedef find< values, integral_c<int,7> >::type values_iter;

    typedef erase<types, types_iter>::type result_types;
    typedef erase<values, values_iter>::type result_values;

    MPL_ASSERT_EQUAL(2,( size<result_types>::value, 7 ));
    MPL_ASSERT_EQUAL(2,( size<result_values>::value, 7 ));

    typedef find<result_types,short>::type result_types_iter;
    typedef find<result_values, integral_c<int,7> >::type result_values_iter;

    MPL_ASSERT_SAME(2,( result_types_iter, end<result_types>::type ));
    MPL_ASSERT_SAME(2,( result_values_iter, end<result_values>::type ));
}

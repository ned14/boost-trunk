
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

#include <boost/mpl/push_front.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/list/list10.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/front.hpp>

#include <boost/mpl/aux_/test/test.hpp>

MPL_TEST_CASE( push_front_test )
{
    typedef push_front<list0<>,long>::type res1;
    typedef push_front<list1<long>,int>::type res2;
    typedef push_front<list2<int,long>,char>::type res3;
    
    MPL_ASSERT_EQUAL(2,( size<res1>::value, 1 ));
    MPL_ASSERT_EQUAL(2,( size<res2>::value, 2 ));
    MPL_ASSERT_EQUAL(2,( size<res3>::value, 3 ));
    
    MPL_ASSERT_SAME(2,( front<res1>::type, long ));
    MPL_ASSERT_SAME(2,( front<res2>::type, int ));
    MPL_ASSERT_SAME(2,( front<res3>::type, char ));
    
    MPL_ASSERT( has_push_front< list0<> >::value );
    MPL_ASSERT( has_push_front< list1<long> >::value );

    MPL_ASSERT( !has_push_back< list0<> >::value );
}

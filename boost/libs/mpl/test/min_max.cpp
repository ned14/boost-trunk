
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

#include <boost/mpl/min_max.hpp>
#include <boost/mpl/int.hpp>

#include <boost/mpl/aux_/test/test.hpp>


MPL_TEST_CASE( min_max_test )
{
    MPL_ASSERT_SAME(3,( mpl::min< int_<5>,int_<7> >::type,int_<5> ));
    MPL_ASSERT_SAME(3,( mpl::max< int_<5>,int_<7> >::type,int_<7> ));

    MPL_ASSERT_SAME(3,( mpl::min< int_<-5>,int_<-7> >::type,int_<-7> ));
    MPL_ASSERT_SAME(3,( mpl::max< int_<-5>,int_<-7> >::type,int_<-5> ));
}

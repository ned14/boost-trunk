
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

#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/test.hpp>

MPL_TEST_CASE()
{
    typedef if_<true_,char,long>::type t1;
    typedef if_c<true,char,long>::type t2;
    MPL_ASSERT_SAME(2,( t1, char ));
    MPL_ASSERT_SAME(2,( t2, char ));

    typedef if_<false_,char,long>::type t3;
    typedef if_c<false,char,long>::type t4;
    MPL_ASSERT_SAME(2,( t3, long ));
    MPL_ASSERT_SAME(2,( t4, long ));
}

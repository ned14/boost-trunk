//-----------------------------------------------------------------------------
// boost mpl/test/apply_if.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#include <boost/mpl/apply_if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/aux_/test.hpp>

MPL_TEST_CASE()
{
    typedef apply_if<
          true_
        , identity<char>
        , identity<long>
        >::type t1;

    typedef apply_if_c<
          true
        , identity<char>
        , identity<long>
        >::type t2;

    MPL_ASSERT_SAME(2,(t1, char));
    MPL_ASSERT_SAME(2,(t2, char));

    typedef apply_if<
          false_
        , identity<char>
        , identity<long>
         >::type t3;

    typedef apply_if_c<
          false
        , identity<char>
        , identity<long>
        >::type t4;

    MPL_ASSERT_SAME(2,(t3, long));
    MPL_ASSERT_SAME(2,(t4, long));
}

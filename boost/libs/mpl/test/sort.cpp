//-----------------------------------------------------------------------------
// libs mpl/test/sort.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002-2003
// Eric Friedman
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#include <boost/mpl/sort.hpp>

#include <boost/static_assert.hpp>
#include <boost/mpl/list_c.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/at.hpp>

#include <boost/mpl/aux_/test.hpp>

MPL_TEST_CASE()
{
    typedef list_c<int, 3, 4, 0, -5, 8, -1, 7>::type numbers;
    typedef list_c<int, -5, -1, 0, 3, 4, 7, 8>::type manual_result;

    typedef sort< numbers >::type result;

    MPL_ASSERT((equal< result,manual_result,equal_to<_1,_2> >::value));
}

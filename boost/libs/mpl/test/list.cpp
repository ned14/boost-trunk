//-----------------------------------------------------------------------------
// boost mpl/test/list.cpp source file
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

#include "boost/mpl/list.hpp"

namespace mpl = boost::mpl;

int main()
{
    typedef mpl::list0 list0;
    typedef mpl::list1<int> list1;
    typedef mpl::list2<int,long> list2;
    typedef mpl::list14<
          void
        , char
        , signed char
        , unsigned char
        , signed short
        , unsigned short
        , signed int
        , unsigned int
        , signed long
        , unsigned long
        , float
        , double
        , long double
        , void
        > list14;

    return 0;
}

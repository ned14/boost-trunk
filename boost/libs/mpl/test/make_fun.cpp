//-----------------------------------------------------------------------------
// boost mpl/test/make_fun.cpp source file
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

#include "boost/mpl/make_fun.hpp"
#include "boost/mpl/assert_is_same.hpp"

namespace mpl = boost::mpl;

template<typename> struct f1;
template<typename T1, typename T2, typename T3, typename T4, typename T5> struct f5;

int main()
{
    typedef mpl::make_f1<f1>::type fc1;
    typedef mpl::make_f5<f5>::type fc5;

    return 0;
}

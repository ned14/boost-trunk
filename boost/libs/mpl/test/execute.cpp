//-----------------------------------------------------------------------------
// boost mpl/test/apply.cpp source file
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

#include "boost/mpl/execute.hpp"
#include <cassert>

namespace mpl = boost::mpl;

struct her
{
    template< typename U > struct apply
    {
        typedef U type;        
    };
};

struct my
{
    template< typename U > struct apply
    {
        typedef U type;        
        apply(int& i)
        {
            i = 10;
        }
    };
};

int main()
{
    int i = 0;
    long l = 0;

    mpl::execute< her::apply<float> >();
    mpl::execute< her::apply<float> >(i);
    mpl::execute< her::apply<float> >(l);
    
    mpl::execute< my::apply<float> >(i);
//    mpl::execute< my::apply<float> >(l);
    
    assert(i == 10);
    
    return 0;
}

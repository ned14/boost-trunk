//-----------------------------------------------------------------------------
// boost mpl/test/fold.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002
// Aleksey Gurtovoy, David Abrahams
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#include "boost/mpl/fold.hpp"
#include "boost/mpl/list.hpp"
#include "boost/mpl/assert_is_same.hpp"

#include "boost/preprocessor/cat.hpp"
#include "boost/preprocessor/inc.hpp"

namespace mpl = boost::mpl;

template< int > struct item {};


#define N 75
#define PUSH_FRONT(i, unused) \
    typedef boost::mpl::push_front<l##i,item<i> >::type BOOST_PP_CAT(l,BOOST_PP_INC(i)); \
/**/

int main()
{
    using namespace mpl::placeholder;
    
    typedef mpl::list0 l0;
    BOOST_PP_REPEAT(N, PUSH_FRONT, unused);
    
    typedef mpl::fold<
          BOOST_PP_CAT(l,N)
        , void
        , mpl::project1st<_,_>
        >::type res;
    
    BOOST_MPL_ASSERT_IS_SAME(res, void);
    return 0;
}

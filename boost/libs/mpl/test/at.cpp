//-----------------------------------------------------------------------------
// boost mpl/test/at.cpp source file
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

#include "boost/mpl/at.hpp"
#include "boost/mpl/list.hpp"
//#include "boost/mpl/value_list.hpp"
#include "boost/type_traits/same_traits.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

int main()
{
    typedef mpl::list< 
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
        > types;

    BOOST_STATIC_ASSERT((boost::is_same< mpl::at_c<0, types>::type, void >::value));
    BOOST_STATIC_ASSERT((boost::is_same< mpl::at_c<1, types>::type, char >::value));
    BOOST_STATIC_ASSERT((boost::is_same< mpl::at_c<2, types>::type, signed char >::value));
    BOOST_STATIC_ASSERT((boost::is_same< mpl::at_c<3, types>::type, unsigned char >::value));
    BOOST_STATIC_ASSERT((boost::is_same< mpl::at_c<4, types>::type, signed short >::value));
    BOOST_STATIC_ASSERT((boost::is_same< mpl::at_c<5, types>::type, unsigned short >::value));
    BOOST_STATIC_ASSERT((boost::is_same< mpl::at_c<6, types>::type, signed int >::value));
    BOOST_STATIC_ASSERT((boost::is_same< mpl::at_c<7, types>::type, unsigned int >::value));
    BOOST_STATIC_ASSERT((boost::is_same< mpl::at_c<8, types>::type, signed long >::value));
    BOOST_STATIC_ASSERT((boost::is_same< mpl::at_c<9, types>::type, unsigned long >::value));
    BOOST_STATIC_ASSERT((boost::is_same< mpl::at_c<10, types>::type, float >::value));
    BOOST_STATIC_ASSERT((boost::is_same< mpl::at_c<11, types>::type, double >::value));
    BOOST_STATIC_ASSERT((boost::is_same< mpl::at_c<12, types>::type, long double >::value));

//    typedef mpl::value_list<0,1,2,3,4,5,6,7,8,9,10,11,12,13,14> values;
/*
    BOOST_STATIC_ASSERT((mpl::at_c<0, values>::value == 0));
    BOOST_STATIC_ASSERT((mpl::at_c<1, values>::value == 1));
    BOOST_STATIC_ASSERT((mpl::at_c<2, values>::value == 2));
    BOOST_STATIC_ASSERT((mpl::at_c<3, values>::value == 3));
    BOOST_STATIC_ASSERT((mpl::at_c<4, values>::value == 4));
    BOOST_STATIC_ASSERT((mpl::at_c<5, values>::value == 5));
    BOOST_STATIC_ASSERT((mpl::at_c<6, values>::value == 6));
    BOOST_STATIC_ASSERT((mpl::at_c<7, values>::value == 7));
    BOOST_STATIC_ASSERT((mpl::at_c<8, values>::value == 8));
    BOOST_STATIC_ASSERT((mpl::at_c<9, values>::value == 9));
    BOOST_STATIC_ASSERT((mpl::at_c<10, values>::value == 10));
    BOOST_STATIC_ASSERT((mpl::at_c<11, values>::value == 11));
    BOOST_STATIC_ASSERT((mpl::at_c<12, values>::value == 12));
    BOOST_STATIC_ASSERT((mpl::at_c<13, values>::value == 13));
    BOOST_STATIC_ASSERT((mpl::at_c<14, values>::value == 14));
*/
    return 0;
}

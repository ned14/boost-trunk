//-----------------------------------------------------------------------------
// boost mpl/test/arithmetic.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#include "boost/mpl/arithmetic.hpp"
#include "boost/mpl/int_c.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

int main()
{
    typedef mpl::int_c<0> _0;
    typedef mpl::int_c<1> _1;
    typedef mpl::int_c<3> _3;
    typedef mpl::int_c<10> _10;

    BOOST_STATIC_ASSERT((mpl::plus2<_0,_10>::value == 10));
    BOOST_STATIC_ASSERT((mpl::plus<_10,_0>::value == 10));

    BOOST_STATIC_ASSERT((mpl::minus2<_0,_10>::value == -10));
    BOOST_STATIC_ASSERT((mpl::minus<_10,_0>::value == 10));

    BOOST_STATIC_ASSERT((mpl::mutliplies2<_1,_10>::value == 10));
    BOOST_STATIC_ASSERT((mpl::mutliplies<_10,_1>::value == 10));

    BOOST_STATIC_ASSERT((mpl::divides2<_10,_1>::value == 10));
    BOOST_STATIC_ASSERT((mpl::divides<_10,_1>::value == 10));

    BOOST_STATIC_ASSERT((mpl::modulus2<_10,_1>::value == 0));
    BOOST_STATIC_ASSERT((mpl::modulus<_10,_3>::value == 1));

#if !defined(BOOST_MSVC) || (BOOST_MSVC > 1300)
    BOOST_STATIC_ASSERT((mpl::minus<_10,_1,_10>::value == -1));
    BOOST_STATIC_ASSERT((mpl::plus<_10,_1,_10>::value == 21));
    BOOST_STATIC_ASSERT((mpl::divides<_10,_1,_10>::value == 1));
    BOOST_STATIC_ASSERT((mpl::divides<_10,_1,_10>::value == 1));
    BOOST_STATIC_ASSERT((mpl::modulus<_10,_3,_1>::value == 0));
#endif

    BOOST_STATIC_ASSERT((mpl::negate<_10>::value == -10));

    return 0;
}


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

#include "boost/mpl/vector/vector10.hpp"
#include "boost/mpl/push_back.hpp"
#include "boost/mpl/pop_back.hpp"
#include "boost/mpl/push_front.hpp"
#include "boost/mpl/pop_front.hpp"
#include "boost/mpl/size.hpp"
#include "boost/mpl/empty.hpp"

#include "boost/type_traits/is_same.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

int main()
{
    typedef mpl::vector0<> v0;
    typedef mpl::vector1<char> v1;
    typedef mpl::vector2<char,long> v2;
    typedef mpl::vector9<char,char,char,char,char,char,char,char,char> v9;

    BOOST_STATIC_ASSERT( mpl::size<v0>::value == 0 );
    BOOST_STATIC_ASSERT( mpl::size<v1>::value == 1 );
    BOOST_STATIC_ASSERT( mpl::size<v2>::value == 2 );
    BOOST_STATIC_ASSERT( mpl::size<v9>::value == 9 );

    BOOST_STATIC_ASSERT( mpl::empty<v0>::value );
    BOOST_STATIC_ASSERT( !mpl::empty<v1>::value );
    BOOST_STATIC_ASSERT( !mpl::empty<v2>::value );
    BOOST_STATIC_ASSERT( !mpl::empty<v9>::value );

//    using boost::is_same;
//    BOOST_STATIC_ASSERT(( is_same< , int >::value ));

    return 0;
}

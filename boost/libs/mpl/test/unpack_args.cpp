
// Copyright (c) Aleksey Gurtovoy 2002-2004
//
// Use, modification and distribution are subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy 
// at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/vector/vector10.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/lambda.hpp>
#define BOOST_MPL_NO_PREPROCESSED_HEADERS
#include <boost/mpl/unpack_args.hpp>

#include <boost/mpl/aux_/test/test.hpp>


MPL_TEST_CASE( unpack_args_test )
{
    MPL_ASSERT(( apply1< unpack_args< lambda< is_same<_1,_2> >::type >, vector2<int,int> >::type::value ));
}

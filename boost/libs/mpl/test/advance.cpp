
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


#include <boost/mpl/vector/vector10_c.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/begin_end.hpp>

#include <boost/mpl/aux_/test/test.hpp>


MPL_TEST_CASE()
{
    typedef vector10_c<int,0,1,2,3,4,5,6,7,8,9> numbers;
    typedef begin<numbers>::type first;
    typedef end<numbers>::type last;

    typedef advance_c<first,10>::type iter1;
    typedef advance_c<last,-10>::type iter2;

    MPL_ASSERT_SAME(2,( iter1, last ));
    MPL_ASSERT_SAME(2,( iter2, first ));
}

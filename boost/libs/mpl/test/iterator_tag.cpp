
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

#include <boost/mpl/iterator_tag.hpp>
#include <boost/mpl/less.hpp>

#include <boost/mpl/aux_/test/test.hpp>


MPL_TEST_CASE( iterator_tag_test )
{
    MPL_ASSERT(( less<forward_iterator_tag,bidirectional_iterator_tag>::value ));
    MPL_ASSERT(( less<bidirectional_iterator_tag,random_access_iterator_tag>::value ));
}

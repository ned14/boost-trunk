
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

#include <boost/mpl/assert.hpp>

BOOST_MPL_ASSERT_MSG( true, GLOBAL_SCOPE_ERROR );
BOOST_MPL_ASSERT_MSG( true, ANOTHER_GLOBAL_SCOPE_ERROR );

namespace my {
BOOST_MPL_ASSERT_MSG( true, NAMESPACE_SCOPE_ERROR );
BOOST_MPL_ASSERT_MSG( true, ANOTHER_NAMESPACE_SCOPE_ERROR );
}

struct her
{
    BOOST_MPL_ASSERT_MSG( true, CLASS_SCOPE_ERROR );
    BOOST_MPL_ASSERT_MSG( true, ANOTHER_CLASS_SCOPE_ERROR );
};


int main()
{
    BOOST_MPL_ASSERT_MSG( true, FUNCTION_SCOPE_ERROR );
    BOOST_MPL_ASSERT_MSG( true, ANOTHER_FUNCTION_SCOPE_ERROR );
    return 0;
}


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

// global scope
BOOST_MPL_MESSAGE( false, GLOBAL_SCOPE_ERROR );

namespace my {
// namespace scope
BOOST_MPL_MESSAGE( false, NAMESPACE_SCOPE_ERROR );
}

struct her
{
    // class/template scope
    BOOST_MPL_MESSAGE( false, CLASS_SCOPE_ERROR );
};


int main()
{
    // function scope
    BOOST_MPL_MESSAGE( false, FUNCTION_SCOPE_ERROR );
    return 0;
}

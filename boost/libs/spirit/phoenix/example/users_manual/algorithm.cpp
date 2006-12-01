/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#include <iostream>
#include <boost/spirit/phoenix/core.hpp>
#include <boost/spirit/phoenix/algorithm.hpp>

using namespace boost::phoenix;

int
main()
{
    int array[] = {1, 2, 3};
    int output[3];
    copy(arg1, arg2)(array, output);
    return 0;
}

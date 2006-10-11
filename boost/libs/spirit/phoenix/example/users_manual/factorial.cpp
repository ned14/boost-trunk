/*=============================================================================
    Copyright (c) 2001-2003 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#include <vector>
#include <algorithm>
#include <iostream>
#include <boost/spirit/phoenix/core.hpp>
#include <boost/spirit/phoenix/function.hpp>

using namespace boost::phoenix;
using namespace std;

struct factorial_impl
{
    template <typename Arg>
    struct result
    {
        typedef Arg type;
    };

    template <typename Arg>
    Arg operator()(Arg n) const
    {
        return (n <= 0) ? 1 : n * this->operator()(n-1);
    }
};

function<factorial_impl> factorial;

int
main()
{
    int i = 4;
    cout << factorial(arg1)(i) << endl;
    return 0;
}

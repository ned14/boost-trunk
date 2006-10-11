/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#include <boost/detail/lightweight_test.hpp>
#include <boost/spirit/phoenix/core/argument.hpp>
#include <boost/spirit/phoenix/core/reference.hpp>
#include <boost/spirit/phoenix/operator/self.hpp>
#include <boost/spirit/phoenix/operator/if_else.hpp>

using namespace boost::phoenix;
using namespace std;

int
main()
{
    {
        int x = 0;
        int y = 0;
        bool c = false;

        BOOST_TEST(if_else(arg1, 1234, 5678)(c) == 5678);
        BOOST_TEST(if_else(arg1, 1234, 'x')(c) == 'x');

        int& r = if_else(arg1, ref(x), ref(y))(c); // should be an lvalue
        BOOST_TEST(&y == &r);

        (if_else(arg1, ref(x), ref(y)) = 986754321)(c);
        BOOST_TEST(y == 986754321);
    }

    return boost::report_errors();
}

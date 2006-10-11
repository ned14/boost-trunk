/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#include <boost/detail/lightweight_test.hpp>
#include <boost/spirit/phoenix/core/value.hpp>
#include <boost/spirit/phoenix/operator/comparison.hpp>

using namespace boost::phoenix;
using namespace std;

int
main()
{
    {
        BOOST_TEST(!(val(123) == 456)());
        BOOST_TEST((val(123) != 456)());
        BOOST_TEST(!(val(123) > 456)());
        BOOST_TEST((val(123) < 456)());
        BOOST_TEST(!(val(123) > 456)());
        BOOST_TEST((val(123) <= 123)());
        BOOST_TEST((val(123) >= 123)());
    }

    return boost::report_errors();
}

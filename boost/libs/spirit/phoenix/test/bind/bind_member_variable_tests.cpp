/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#include <iostream>
#include <cmath>
#include <boost/noncopyable.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <boost/spirit/phoenix/core.hpp>
#include <boost/spirit/phoenix/operator.hpp>
#include <boost/spirit/phoenix/bind.hpp>

using namespace boost::phoenix;
using namespace std;
namespace phx = boost::phoenix;

namespace test
{
    struct x : boost::noncopyable // test non-copyable (hold this by reference)
    {
        int m;
    };
}

int
main()
{
    test::x x_;
    bind(&test::x::m, x_)() = 123;
    bind(&test::x::m, arg1)(x_) = 123;
    BOOST_TEST(x_.m == 123);

    return boost::report_errors();
}

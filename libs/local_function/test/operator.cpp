
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#include <boost/config.hpp>
#ifndef BOOST_NO_VARIADIC_MACROS

#include <boost/local_function.hpp>
#define BOOST_TEST_MODULE TestOperator
#include <boost/test/unit_test.hpp>

//[operator
struct point {
    int x;
    int y;
};

BOOST_AUTO_TEST_CASE(test_operator) {
    bool BOOST_LOCAL_FUNCTION(const point& p, const point& q) {
        return p.x == q.x && p.y == q.y;
    } BOOST_LOCAL_FUNCTION_NAME(equal) // OK: not using `operator...`.

    point a; a.x = 1; a.y = 2;
    point b = a;
    BOOST_CHECK(equal(a, b));
}
//]

#else

int main(void) { return 0; } // Trivial test.

#endif


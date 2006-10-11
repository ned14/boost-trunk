/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <boost/spirit/phoenix/core/argument.hpp>
#include <boost/spirit/phoenix/object/new.hpp>
#include <boost/spirit/phoenix/object/construct.hpp>
#include <boost/spirit/phoenix/object/delete.hpp>
#include <boost/spirit/phoenix/operator.hpp>

using namespace boost::phoenix;
using namespace std;

int n = 0;

struct X
{
    X(int, int, int) { cout << "new X(int, int, int)" << endl; ++n; }
    X() { cout << "new X" << endl; ++n; }
    ~X() { cout << "delete X" << endl; --n; }
};

int
main()
{
    {
        vector<X*> v(10);

        for_each(v.begin(), v.end(), arg1 = new_<X>());
        for_each(v.begin(), v.end(), delete_(arg1));

        for_each(v.begin(), v.end(), arg1 = new_<X>(1, 2, 3));
        for_each(v.begin(), v.end(), delete_(arg1));
    }

    {
        using boost::shared_ptr;
        vector<shared_ptr<X> > v(10);
        for_each(v.begin(), v.end(),
            arg1 = construct<shared_ptr<X> >(new_<X>())
        );
    }

    BOOST_TEST(n == 0);
    return boost::report_errors();
}

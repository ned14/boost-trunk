/*=============================================================================
    Spirit v1.6.2
    Copyright (c) 2003 Vaclav Vesely
    http://spirit.sourceforge.net/

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at 
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
// chset<>::operator~(range<>) bug
// operator&(chset<>, range<>) bug
// operator&(range<>, chset<>) bug
#include <boost/limits.hpp>
#include <boost/test/included/unit_test_framework.hpp>
#include <boost/spirit/utility/chset.hpp>

using namespace std;
using namespace boost;
using namespace unit_test_framework;
using namespace spirit;

//-----------------------------------------------------------------------------

void bug_000004_test()
{
    const char min = (numeric_limits<char>::min)();
    const char max = (numeric_limits<char>::max)();

    {
        chset<> set(~range<>(min, max));
        BOOST_CHECK(set.test(min) == false);
        BOOST_CHECK(set.test(min) == false);
    }

    {
        chset<> set(chset<>(anychar_p) & range<>(min, max));
        BOOST_CHECK(set.test(min) == true);
        BOOST_CHECK(set.test(min) == true);
    }

    {
        chset<> set(range<>(min, max) & chset<>(anychar_p));
        BOOST_CHECK(set.test(min) == true);
        BOOST_CHECK(set.test(min) == true);
    }
}

//-----------------------------------------------------------------------------

test_suite* init_unit_test_suite(int argc, char* argv[])
{
    test_suite* test = BOOST_TEST_SUITE("bug_000004 test");

    test->add(BOOST_TEST_CASE(&bug_000004_test));

    return test;
}

//-----------------------------------------------------------------------------

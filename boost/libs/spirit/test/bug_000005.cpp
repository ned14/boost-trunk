/*=============================================================================
    Spirit v1.6.2
    Copyright (c) 2003 Vaclav Vesely
    http://spirit.sourceforge.net/

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at 
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
// Most trailing space bug
// http://article.gmane.org/gmane.comp.parsers.spirit.general/4029

#include <boost/test/included/unit_test_framework.hpp>
#include <boost/spirit/core.hpp>

using namespace std;
using namespace boost;
using namespace unit_test_framework;
using namespace spirit;

//-----------------------------------------------------------------------------

void bug_000005_test()
{
    BOOST_CHECK(
        parse("   aaaaaaaaa     ", *ch_p('a'), space_p).full
    );

    BOOST_CHECK(
        parse("   aaaaaaaaa     ", lexeme_d[*ch_p('a')], space_p).full
    );

    BOOST_CHECK(
        parse("   aaaaaaaaa     ", *ch_p('a'), ch_p(' ')).full
    );

    BOOST_CHECK(
        parse("   aaaaaaaaa     ", lexeme_d[*ch_p('a')], ch_p(' ')).full
    );
}

//-----------------------------------------------------------------------------

test_suite* init_unit_test_suite(int argc, char* argv[])
{
    test_suite* test = BOOST_TEST_SUITE("bug_000005 test");

    test->add(BOOST_TEST_CASE(&bug_000005_test));

    return test;
}

//-----------------------------------------------------------------------------

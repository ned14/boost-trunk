// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#include <boost/iostreams/filter/test.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>
#include "detail/filters.hpp"

using namespace boost::iostreams;
using namespace boost::iostreams::test;
using boost::unit_test::test_suite;

const char* lower = 
    "in addition to providing an abstract framework the "
    "library provides a number of concrete filters, sources "
    "and sinks which serve as example applications of the "
    "library but are also useful in their own right. these "
    "include components for accessing memory-mapped files, "
    "for file access via operating system file descriptors, "
    "for code conversion, for text filtering with regular "
    "expressions, for line-ending conversion and for "
    "compression and decompression in the zlib, gzip and "
    "bzip2 formats.";

const char* upper = 
    "IN ADDITION TO PROVIDING AN ABSTRACT FRAMEWORK THE "
    "LIBRARY PROVIDES A NUMBER OF CONCRETE FILTERS, SOURCES "
    "AND SINKS WHICH SERVE AS EXAMPLE APPLICATIONS OF THE "
    "LIBRARY BUT ARE ALSO USEFUL IN THEIR OWN RIGHT. THESE "
    "INCLUDE COMPONENTS FOR ACCESSING MEMORY-MAPPED FILES, "
    "FOR FILE ACCESS VIA OPERATING SYSTEM FILE DESCRIPTORS, "
    "FOR CODE CONVERSION, FOR TEXT FILTERING WITH REGULAR "
    "EXPRESSIONS, FOR LINE-ENDING CONVERSION AND FOR "
    "COMPRESSION AND DECOMPRESSION IN THE ZLIB, GZIP AND "
    "BZIP2 FORMATS.";

void filter_test()
{
    BOOST_CHECK(test_input_filter(toupper_filter(), lower, upper));
    BOOST_CHECK(test_input_filter(toupper_multichar_filter(), lower, upper));
    BOOST_CHECK(test_output_filter(tolower_filter(), upper, lower));
    BOOST_CHECK(test_output_filter(tolower_multichar_filter(), upper, lower));
    BOOST_CHECK(test_filter_pair(tolower_filter(), toupper_filter(), upper));
    BOOST_CHECK(
        test_filter_pair( tolower_multichar_filter(), 
                          toupper_multichar_filter(), upper )
    );
}

test_suite* init_unit_test_suite(int, char* []) 
{
    test_suite* test = BOOST_TEST_SUITE("filter test");
    test->add(BOOST_TEST_CASE(&filter_test));
    return test;
}

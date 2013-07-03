///////////////////////////////////////////////////////////////
//  Copyright 2011 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_

#include "setup.hpp"
#include "table_type.hpp"
#define TEST_UDT

#include <boost/math/special_functions/math_fwd.hpp>
#include "libs/math/test/test_expint.hpp"

void expected_results()
{
   //
   // Define the max and mean errors expected for
   // various compilers and platforms.
   //
   add_expected_result(
      ".*",                          // compiler
      ".*",                          // stdlib
      ".*",                          // platform
      ".*gmp_float<18>.*",             // test type(s)
      ".*",                          // test data group
      ".*", 2500, 1500);             // test function
   add_expected_result(
      ".*",                          // compiler
      ".*",                          // stdlib
      ".*",                          // platform
      ".*mpfr_float_backend<18>.*",  // test type(s)
      ".*",                          // test data group
      ".*", 1000, 500);              // test function
   add_expected_result(
      ".*",                          // compiler
      ".*",                          // stdlib
      ".*",                          // platform
      ".*gmp_float.*",               // test type(s)
      ".*",                          // test data group
      ".*", 250, 100);               // test function
#ifdef BOOST_INTEL
   add_expected_result(
      ".*",                          // compiler
      ".*",                          // stdlib
      ".*",                          // platform
      "float128",               // test type(s)
      ".*",                          // test data group
      ".*", 4500, 1000);               // test function
#endif
   add_expected_result(
      ".*",                          // compiler
      ".*",                          // stdlib
      ".*",                          // platform
      ".*",                          // test type(s)
      ".*",                          // test data group
      ".*", 250, 50);                // test function
   //
   // Finish off by printing out the compiler/stdlib/platform names,
   // we do this to make it easier to mark up expected error rates.
   //
   std::cout << "Tests run with " << BOOST_COMPILER << ", "
      << BOOST_STDLIB << ", " << BOOST_PLATFORM << std::endl;
}

template <class T>
void test(T t, const char* p)
{
   test_expint(t, p);
}

BOOST_AUTO_TEST_CASE( test_main )
{
   using namespace boost::multiprecision;
   expected_results();
   //
   // Test at:
   // 18 decimal digits: tests 80-bit long double approximations
   // 30 decimal digits: tests 128-bit long double approximations
   // 35 decimal digits: tests arbitrary precision code
   //
   ALL_TESTS
}


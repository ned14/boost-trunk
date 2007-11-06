//  Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Basic sanity check that header <boost/math/special_functions/sign.hpp>
// #includes all the files that it needs to.
//
#include <boost/math/special_functions/sign.hpp>
//
// Note this header includes no other headers, this is
// important if this test is to be meaningful:
//
#include "test_compile_result.hpp"

void check()
{
   check_result<int>(boost::math::sign<float>(f));
   check_result<int>(boost::math::sign<double>(d));
   check_result<int>(boost::math::sign<long double>(l));

   check_result<int>(boost::math::signbit<float>(f));
   check_result<int>(boost::math::signbit<double>(d));
   check_result<int>(boost::math::signbit<long double>(l));

   check_result<float>(boost::math::copysign<float>(f, f));
   check_result<double>(boost::math::copysign<double>(d, d));
   check_result<long double>(boost::math::copysign<long double>(l, l));
}

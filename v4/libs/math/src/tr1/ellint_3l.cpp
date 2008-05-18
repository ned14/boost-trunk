//  Copyright John Maddock 2008.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#define BOOST_MATH_TR1_SOURCE
#include <boost/math/tr1.hpp>
#include <boost/math/special_functions/ellint_3.hpp>
#include "c_policy.hpp"

extern "C" long double BOOST_MATH_TR1_DECL ellint_3l(long double k, long double nu, long double phi)
{
   return c_policies::ellint_3(k, nu, phi);
}

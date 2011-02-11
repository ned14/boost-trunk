/* test_ranlux48.cpp
 *
 * Copyright Steven Watanabe 2011
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * $Id$
 *
 */

#include <boost/random/ranlux.hpp>
#include <boost/cstdint.hpp>

#define BOOST_RANDOM_URNG boost::random::ranlux48
// validation from the C++0x draft (n3090)
#define BOOST_RANDOM_VALIDATION_VALUE UINT64_C(249142670248501)

#include "test_generator.ipp"

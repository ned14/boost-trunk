/* Boost test/integer.cpp
 * test int extension
 *
 * Copyright Guillaume Melquiond 2003
 * Permission to use, copy, modify, sell, and distribute this software
 * is hereby granted without fee provided that the above copyright notice
 * appears in all copies and that both that copyright notice and this
 * permission notice appear in supporting documentation.
 *
 * None of the above authors make any representation about the suitability
 * of this software for any purpose. It is provided "as is" without express
 * or implied warranty.
 *
 * $Id$
 */

#include <boost/numeric/interval.hpp>
#include <boost/numeric/interval/ext/integer.hpp>

typedef boost::numeric::interval<float> I;

int main() {
  I x, y;
  x = 4 - (2 * y + 1) / 3;
  return 0;
}

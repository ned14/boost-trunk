//  test tools - test failure reported by BOOST_TEST  ------------------------//

//  (C) Copyright Beman Dawes 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  Revision History
//    7 Nov 00  Initial boost version (Beman Dawes)

#define BOOST_INCLUDE_MAIN  // for testing, include rather than link
#include <boost/test/test_tools.hpp>

int test_main( int, char *[] )  // note the name
{
  int v = 1;
  BOOST_TEST( v == 2 );
  BOOST_TEST( 2 == v );
  return 0;
}

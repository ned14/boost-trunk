//  boost test_main example program  ----------------------------------------//

#define BOOST_INCLUDE_MAIN  // for testing, include rather than link
#include <boost/test/test_tools.hpp>

int add( int i, int j ) { return i+j; }

int test_main( int, char *[] )  // note the name!
{
  // six ways to detect and report the same error:
  BOOST_TEST( add(2,2) == 4 );           // #1 continues on error
  BOOST_CRITICAL_TEST( add(2,2) == 4 );  // #2 throws on error
  if ( add(2,2) != 4 )
    BOOST_ERROR( "Ouch...");             // #3 continues on error
  if ( add(2,2) != 4 )
    BOOST_CRITICAL_ERROR( "Ouch..." );   // #4 throws on error
  if ( add(2,2) != 4 ) throw "Oops...";  // #5 throws on error
  return add(2,2) == 4 ? 0 : 1;          // #6 returns error code
}

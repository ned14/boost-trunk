//  libs/filesystem/test/convenience_test.cpp  -------------------------------//

//  (C) Copyright Beman Dawes, 2002
//  (C) Copyright Vladimir Prus, 2002
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org/libs/filesystem for documentation.

#include <boost/filesystem/convenience.hpp>
namespace fs = boost::filesystem;
using fs::path;

#include <boost/test/minimal.hpp>

int test_main( int, char*[] )
{

//  create_directories() tests  ----------------------------------------------//

  fs::create_directories( "" );  // should be harmless
  fs::create_directories( "/" ); // ditto
  fs::remove_all( "xx/yy/zz" );  // make sure slate is blank

  fs::create_directories( "xx" );
  BOOST_TEST( fs::exists( "xx" ) );
  BOOST_TEST( fs::is_directory( "xx" ) );

  fs::create_directories( "xx/ww/zz" );
  BOOST_TEST( fs::exists( "xx" ) );
  BOOST_TEST( fs::exists( "xx/ww" ) );
  BOOST_TEST( fs::exists( "xx/ww/zz" ) );
  BOOST_TEST( fs::is_directory( "xx" ) );
  BOOST_TEST( fs::is_directory( "xx/ww" ) );
  BOOST_TEST( fs::is_directory( "xx/ww/zz" ) );
  
// extension() tests ----------------------------------------------------------//

  BOOST_TEST( fs::extension("a/b") == "" );
  BOOST_TEST( fs::extension("a/b.txt") == ".txt" );
  BOOST_TEST( fs::extension("a/b.") == "." );
  BOOST_TEST( fs::extension("a.b.c") == ".c" );
  BOOST_TEST( fs::extension("a.b.c.") == "." );
  BOOST_TEST( fs::extension("") == "" );
  BOOST_TEST( fs::extension("a/") == "" );
  
// basename() tests ----------------------------------------------------------//

  BOOST_TEST( fs::basename("b") == "b" );
  BOOST_TEST( fs::basename("a/b.txt") == "b" );
  BOOST_TEST( fs::basename("a/b.") == "b" ); 
  BOOST_TEST( fs::basename("a.b.c") == "a.b" );
  BOOST_TEST( fs::basename("a.b.c.") == "a.b.c" );
  BOOST_TEST( fs::basename("") == "" );
  
// change_extension tests ---------------------------------------------------//

  BOOST_TEST( fs::change_extension("a.txt", ".tex").string() == "a.tex" );
  BOOST_TEST( fs::change_extension("a.", ".tex").string() == "a.tex" );
  BOOST_TEST( fs::change_extension("a", ".txt").string() == "a.txt" );
  BOOST_TEST( fs::change_extension("a.b.txt", ".tex").string() == "a.b.tex" );  
  // see the rationale in html docs for explanation why this works
  BOOST_TEST( fs::change_extension("", ".png").string() == ".png" );

  return 0;
}

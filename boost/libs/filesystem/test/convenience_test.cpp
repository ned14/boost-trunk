//  libs/filesystem/test/convenience_test.cpp  -------------------------------//

//  Copyright Beman Dawes, 2002
//  Copyright Vladimir Prus, 2002
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/filesystem

#include <boost/filesystem/convenience.hpp>
#include <boost/filesystem/exception.hpp>
namespace fs = boost::filesystem;
using fs::path;

#include <boost/test/minimal.hpp>
#include <boost/bind.hpp>
#include <fstream>
#include <iostream>

namespace
{
  template< typename F >
    bool throws_fs_error( F func, fs::error_code ec =
      ::boost::filesystem::no_error ) // VC++ 7.1 build 2292 won't accept fs::
  {
    try { func(); }

    catch ( const fs::filesystem_error & ex )
    {
      if ( ec == fs::no_error || ec == ex.error() ) return true;
      std::cout << "filesystem_error::error() reports " << ex.error()
        << ", should be " << ec
        << "\n native_error() is " << ex.native_error()
        << std::endl;
    }
    return false;
  }
}
int test_main( int, char*[] )
{
  path::default_name_check( fs::no_check ); // names below not valid on all O/S's
                                            // but they must be tested anyhow

 //  create_directories() tests  ----------------------------------------------//

  BOOST_CHECK( !fs::create_directories( "" ) );  // should be harmless
  BOOST_CHECK( !fs::create_directories( "/" ) ); // ditto

  fs::remove_all( "xx" );  // make sure slate is blank
  BOOST_CHECK( !fs::exists( "xx" ) ); // reality check

  BOOST_CHECK( fs::create_directories( "xx" ) );
  BOOST_CHECK( fs::exists( "xx" ) );
  BOOST_CHECK( fs::is_directory( "xx" ) );

  BOOST_CHECK( fs::create_directories( "xx/ww/zz" ) );
  BOOST_CHECK( fs::exists( "xx" ) );
  BOOST_CHECK( fs::exists( "xx/ww" ) );
  BOOST_CHECK( fs::exists( "xx/ww/zz" ) );
  BOOST_CHECK( fs::is_directory( "xx" ) );
  BOOST_CHECK( fs::is_directory( "xx/ww" ) );
  BOOST_CHECK( fs::is_directory( "xx/ww/zz" ) );

  path is_a_file( "xx/uu" );
  {
    std::ofstream f( is_a_file.native_file_string().c_str() );
    BOOST_CHECK( !!f );
  }
  BOOST_CHECK(
    throws_fs_error( boost::bind( fs::create_directories, is_a_file ) ) );
  BOOST_CHECK(
    throws_fs_error( boost::bind( fs::create_directories, is_a_file / "aa" ) ) );
  
// extension() tests ----------------------------------------------------------//

  BOOST_CHECK( fs::extension("a/b") == "" );
  BOOST_CHECK( fs::extension("a/b.txt") == ".txt" );
  BOOST_CHECK( fs::extension("a/b.") == "." );
  BOOST_CHECK( fs::extension("a.b.c") == ".c" );
  BOOST_CHECK( fs::extension("a.b.c.") == "." );
  BOOST_CHECK( fs::extension("") == "" );
  BOOST_CHECK( fs::extension("a/") == "" );
  
// basename() tests ----------------------------------------------------------//

  BOOST_CHECK( fs::basename("b") == "b" );
  BOOST_CHECK( fs::basename("a/b.txt") == "b" );
  BOOST_CHECK( fs::basename("a/b.") == "b" ); 
  BOOST_CHECK( fs::basename("a.b.c") == "a.b" );
  BOOST_CHECK( fs::basename("a.b.c.") == "a.b.c" );
  BOOST_CHECK( fs::basename("") == "" );
  
// change_extension tests ---------------------------------------------------//

  BOOST_CHECK( fs::change_extension("a.txt", ".tex").string() == "a.tex" );
  BOOST_CHECK( fs::change_extension("a.", ".tex").string() == "a.tex" );
  BOOST_CHECK( fs::change_extension("a", ".txt").string() == "a.txt" );
  BOOST_CHECK( fs::change_extension("a.b.txt", ".tex").string() == "a.b.tex" );  
  // see the rationale in html docs for explanation why this works
  BOOST_CHECK( fs::change_extension("", ".png").string() == ".png" );

  return 0;
}

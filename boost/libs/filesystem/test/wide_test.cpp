//  Boost wide_test.cpp  -----------------------------------------------------//

//  Copyright Beman Dawes 2005

//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/filesystem

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include "../src/utf8_codecvt_facet.hpp"
#include <boost/scoped_array.hpp>
#include <boost/test/minimal.hpp>

namespace fs = boost::filesystem;

#include <iostream>
#include <iomanip>
#include <string>
#include <cerrno>

#include "lpath.hpp"

namespace
{
  template< class Path >
  void create_file( const Path & ph, const std::string & contents )
  {
    // TODO: why missing symbol error on Darwin
    fs::ofstream f( ph );
//  std::ofstream f( ph.external_file_string().c_str() );
    if ( !f )
      throw fs::basic_filesystem_error<Path>( "wide_test create_file",
        ph, errno );
    if ( !contents.empty() ) f << contents;
  }

  template< class Path >
  void test( const Path & dir, const Path & file, const Path & dot )
  {
    fs::remove( dir / file );
    fs::remove( dir );
    BOOST_CHECK( !fs::exists( dir / file ) );
    BOOST_CHECK( !fs::exists( dir ) );
    BOOST_CHECK( fs::create_directory( dir ) );
    BOOST_CHECK( fs::exists( dir ) );
    BOOST_CHECK( fs::is_directory( dir ) );
    BOOST_CHECK( fs::is_empty( dir ) );
    create_file( dir / file, "wide_test file contests" );
    BOOST_CHECK( fs::exists( dir / file ) );
    BOOST_CHECK( !fs::is_directory( dir / file ) );
    BOOST_CHECK( !fs::is_empty( dir / file ) );
    BOOST_CHECK( fs::file_size( dir / file ) == 23 || fs::file_size( dir / file ) == 24 );
    BOOST_CHECK( fs::equivalent( dir / file, dot / dir / file ) );
    BOOST_CHECK( fs::last_write_time( dir / file ) );
    typedef fs::basic_directory_iterator<Path> it_t;
    int count(0);
    for ( it_t it( dir ); it != it_t(); ++it )
    {
      BOOST_CHECK( *it == dir / file );
      BOOST_CHECK( !fs::is_empty( *it ) );
      ++count;
    }
    BOOST_CHECK( count == 1 );
  }

  // test boost::detail::utf8_codecvt_facet; even though it is not used by
  // Boost.Filesystem on Windows, early detection of problems is worthwhile.
  std::string to_external( const std::wstring & src )
  {
    boost::detail::utf8_codecvt_facet convertor;
    std::size_t work_size( convertor.max_length() * (src.size()+1) );
    boost::scoped_array<char> work( new char[ work_size ] );
    std::mbstate_t state;
    const wchar_t * from_next;
    char * to_next;
    if ( convertor.out( 
      state, src.c_str(), src.c_str()+src.size(), from_next, work.get(),
      work.get()+work_size, to_next ) != std::codecvt_base::ok )
      boost::throw_exception( "to_external conversion error" );
    *to_next = '\0';
    return std::string( work.get() );
  }


} // unnamed namespace

//  test_main  ---------------------------------------------------------------//

int test_main( int argc, char * argv[] )
{
  std::string s( to_external( L"\x2780" ) );
  for (std::size_t i = 0; i < s.size(); ++i )
    std::cout << std::hex << int( static_cast<unsigned char>(s[i]) ) << " ";
  std::cout << std::dec << std::endl;
  BOOST_CHECK( to_external( L"\x2780" ).size() == 3 );
  BOOST_CHECK( to_external( L"\x2780" ) == "\xE2\x9E\x80" );

  test( fs::path( "foo" ), fs::path( "bar" ), fs::path( "." ) );
  test( fs::wpath( L"\x2780" ), fs::wpath( L"\x2781" ), fs::wpath( L"." ) );

  const long dir[] = { 'm', 'o', 'o', 0 };
  const long file[] = { 'f', 'a', 'r', 0 };
  const long dot[] = { '.', 0 };
  test( ::user::lpath( dir ), ::user::lpath( file ), ::user::lpath( dot ) );

  return 0;
}

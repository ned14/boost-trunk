
//  (C) Copyright Boost.org 1999. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

// Test file for macro BOOST_NO_STD_WSTREAMBUF
// This file should not compile, if it does then
// BOOST_NO_STD_WSTREAMBUF need not be defined.
// see boost_no_std_wstreambuf.cxx for more details

// Do not edit this file, it was generated automatically by
// ../tools/generate from boost_no_std_wstreambuf.cxx on
// Wed Jul 17 12:54:32  2002

// Must not have BOOST_ASSERT_CONFIG set; it defeats
// the objective of this file:
#ifdef BOOST_ASSERT_CONFIG
#  undef BOOST_ASSERT_CONFIG
#endif

#include <boost/config.hpp>
#include <boost/test/cpp_main.cpp>
#include "test.hpp"

#ifdef BOOST_NO_STD_WSTREAMBUF
#include "boost_no_std_wstreambuf.cxx"
#else
#error "this file should not compile"
#endif

int cpp_main( int, char *[] )
{
   return boost_no_std_wstreambuf::test();
}  
   

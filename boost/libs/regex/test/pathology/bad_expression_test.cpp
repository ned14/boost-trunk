/*
 *
 * Copyright (c) 1998-2002
 * Dr John Maddock
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Dr John Maddock makes no representations
 * about the suitability of this software for any purpose.
 * It is provided "as is" without express or implied warranty.
 *
 */

 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE:        recursion_test.cpp
  *   VERSION:     see <boost/version.hpp>
  *   DESCRIPTION: Test for indefinite recursion and/or stack overrun.
  */

#include <string>
#include <boost/regex.hpp>
#include <boost/test/test_tools.hpp>

int test_main( int , char* [] )
{
   std::string bad_text(1024, ' ');
   std::string good_text(200, ' ');
   good_text.append("xyz");

   boost::smatch what;

   boost::regex e1("(.+)+xyz");

   BOOST_CHECK(boost::regex_search(good_text, what, e1));
   BOOST_CHECK_THROW(boost::regex_search(bad_text, what, e1), std::runtime_error);
   BOOST_CHECK(boost::regex_search(good_text, what, e1));

   BOOST_CHECK(boost::regex_match(good_text, what, e1));
   BOOST_CHECK_THROW(boost::regex_match(bad_text, what, e1), std::runtime_error);
   BOOST_CHECK(boost::regex_match(good_text, what, e1));

   boost::regex e2("abc|[[:space:]]+(xyz)?[[:space:]]+xyz");

   BOOST_CHECK(boost::regex_search(good_text, what, e2));
   BOOST_CHECK_THROW(boost::regex_search(bad_text, what, e2), std::runtime_error);
   BOOST_CHECK(boost::regex_search(good_text, what, e2));

   return 0;
}

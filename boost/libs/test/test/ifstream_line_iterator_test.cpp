//  (C) Copyright Gennadiy Rozental 2001-2006.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.
//
//  File        : $RCSfile$
//
//  Version     : $Revision$
//
//  Description : ifstream_line_iterator unit test
// *****************************************************************************

// Boost.Test
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include <boost/test/utils/iterator/ifstream_line_iterator.hpp>

namespace ut = boost::unit_test;

static ut::ifstream_line_iterator eoi;

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE( test_default_delimeter )
{
    ut::ifstream_line_iterator it( ut::framework::master_test_suite().argc <= 1
                                        ? "./test_files/ifstream_line_iterator.tst1"
                                        : ut::framework::master_test_suite().argv[1] );

    BOOST_CHECK( it != eoi ); 

    BOOST_CHECK_EQUAL( *it, "acv ffg" ); 
    ++it;

    BOOST_CHECK_EQUAL( *it, "" ); 
    ++it;

    BOOST_CHECK_EQUAL( *it, " " ); 
    ++it;

    BOOST_CHECK_EQUAL( *it, "1" ); 
    ++it;

    BOOST_CHECK( it == eoi ); 
}

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE( test_custom_delimeter )
{
    ut::ifstream_line_iterator it( ut::framework::master_test_suite().argc <= 2 
                                        ? "./test_files/ifstream_line_iterator.tst2"
                                        : ut::framework::master_test_suite().argv[2], '}' );

    BOOST_CHECK( it != eoi ); 

    BOOST_CHECK_EQUAL( *it, "{ abc d " ); 
    ++it;

    BOOST_CHECK_EQUAL( *it, "\n{ d \n dsfg\n" ); 
    ++it;

    BOOST_CHECK_EQUAL( *it, "\n" ); 
    ++it;

    BOOST_CHECK( it == eoi ); 
}


//____________________________________________________________________________//

// *****************************************************************************
// History :
//
// $Log$
// Revision 1.9  2006/03/19 11:49:04  rogeeff
// *** empty log message ***
//
// Revision 1.8  2005/12/14 06:01:02  rogeeff
// *** empty log message ***
//
// Revision 1.7  2005/06/11 07:20:45  rogeeff
// portability fix
//
// Revision 1.6  2005/05/11 05:07:57  rogeeff
// licence update
//
// Revision 1.5  2005/03/22 07:14:44  rogeeff
// no message
//
// *****************************************************************************

// EOF

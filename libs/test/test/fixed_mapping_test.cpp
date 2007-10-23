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
//  Description : basic_cstring unit test
// *****************************************************************************

// Boost.Test
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include <boost/test/utils/basic_cstring/basic_cstring.hpp>
#include <boost/test/utils/basic_cstring/compare.hpp>
#include <boost/test/utils/fixed_mapping.hpp>

namespace utf = boost::unit_test;
namespace tt  = boost::test_tools;
using utf::const_string;

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE( test_default_compare )
{
    utf::fixed_mapping<const_string,int> test_mapping( 
        "Key1", 1,
        "Key2", 2,
        "QWE" , 3,
        "ASD" , 4,
        "aws" , 5,
        "dfg" , 6,
        "dgt" , 7,
        "ght" , 8,

        0
        );

    BOOST_CHECK_EQUAL( test_mapping[ "Key1" ], 1 );
    BOOST_CHECK_EQUAL( test_mapping[ "Key2" ], 2 );
    BOOST_CHECK_EQUAL( test_mapping[ "QWE" ] , 3 );
    BOOST_CHECK_EQUAL( test_mapping[ "ASD" ] , 4 );
    BOOST_CHECK_EQUAL( test_mapping[ "aws" ] , 5 );
    BOOST_CHECK_EQUAL( test_mapping[ "dfg" ] , 6 );
    BOOST_CHECK_EQUAL( test_mapping[ "dgt" ] , 7 );
    BOOST_CHECK_EQUAL( test_mapping[ "ght" ] , 8 );
    BOOST_CHECK_EQUAL( test_mapping[ "bla" ] , 0 );
}

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE( test_custom_compare )
{
    utf::fixed_mapping<const_string,int,utf::case_ins_less<char const> > test_mapping( 
        "Key1", 1,
        "Key2", 2,
        "QWE" , 3,
        "ASD" , 4,

        0
    );

    BOOST_CHECK_EQUAL( test_mapping[ "Key1" ], 1 );
    BOOST_CHECK_EQUAL( test_mapping[ "Key2" ], 2 );
    BOOST_CHECK_EQUAL( test_mapping[ "QWE" ] , 3 );
    BOOST_CHECK_EQUAL( test_mapping[ "ASD" ] , 4 );
    BOOST_CHECK_EQUAL( test_mapping[ "kEy1" ], 1 );
    BOOST_CHECK_EQUAL( test_mapping[ "key2" ], 2 );
    BOOST_CHECK_EQUAL( test_mapping[ "qwE" ] , 3 );
    BOOST_CHECK_EQUAL( test_mapping[ "aSd" ] , 4 );
    BOOST_CHECK_EQUAL( test_mapping[ "bla" ] , 0 );
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
// Revision 1.7  2005/05/11 05:07:56  rogeeff
// licence update
//
// Revision 1.6  2005/02/20 08:28:34  rogeeff
// This a major update for Boost.Test framework. See release docs for complete list of fixes/updates
//
// Revision 1.5  2005/01/30 03:35:55  rogeeff
// no message
//
// Revision 1.3  2005/01/18 08:30:09  rogeeff
// unit_test_log rework:
//    eliminated need for ::instance()
//    eliminated need for << end and ...END macro
//    straitend interface between log and formatters
//    change compiler like formatter name
//    minimized unit_test_log interface and reworked to use explicit calls
//
// *****************************************************************************

// EOF

//  (C) Copyright Gennadiy Rozental 2001-2005.
//  (C) Copyright Beman Dawes 1995-2001.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.
//
//  File        : $RCSfile$
//
//  Version     : $$Revision$
//
//  Description : implements main function for Test Execution Monitor.
// ***************************************************************************

#ifndef BOOST_TEST_MAIN_IPP_012205GER
#define BOOST_TEST_MAIN_IPP_012205GER

// Boost.Test
#include <boost/test/unit_test.hpp>         // for unit test framework
#include <boost/test/unit_test_result.hpp>
#include <boost/test/detail/unit_test_parameters.hpp>
#include <boost/test/detail/unit_test_monitor.hpp>
#include <boost/test/unit_test_log.hpp>

// Boost
#include <boost/scoped_ptr.hpp>

// STL
#include <iostream>                         // for cout, cerr

int test_main( int argc, char* argv[] );    // prototype for user's test_main()

namespace {
    int      argc_;
    char**   argv_;
    int      test_main_result;

    void call_test_main()
    {
        test_main_result = test_main( argc_, argv_ );

        // translate a test_main non-success return into a test error
        BOOST_CHECK( test_main_result == 0 || test_main_result == boost::exit_success );
    }
}

// ************************************************************************** //
// **************                   test main                  ************** //
// ************************************************************************** //

int BOOST_TEST_CALL_DECL main( int argc, char* argv[] ) {
    using namespace boost::unit_test;

    // set the log level
    unit_test_log.set_threshold_level_by_name( retrieve_framework_parameter( LOG_LEVEL, &argc, argv ) );

    // set the report level
    const_string reportlevel = retrieve_framework_parameter( REPORT_LEVEL, &argc, argv );

    // set the log/report format
    const_string output_format = retrieve_framework_parameter( OUTPUT_FORMAT, &argc, argv );

    if( output_format.empty() ) {
        unit_test_log.set_format( retrieve_framework_parameter( LOG_FORMAT, &argc, argv ) );
        unit_test_result::set_report_format( retrieve_framework_parameter( REPORT_FORMAT, &argc, argv ) );
    }
    else {
        unit_test_log.set_format( output_format );
        unit_test_result::set_report_format( output_format );
    }

    // set the result code flag
    bool no_result_code = retrieve_framework_parameter( NO_RESULT_CODE, &argc, argv ) == "no";

    // set catch_system_error switch
    ut_detail::unit_test_monitor::catch_system_errors( retrieve_framework_parameter( CATCH_SYS_ERRORS, &argc, argv ) != "no" );

    //  set up the test
    argc_ = argc;
    argv_ = argv;
    boost::scoped_ptr<test_case> test_main_tc( BOOST_TEST_CASE( &call_test_main ) );

    // start testing
    unit_test_log.start( retrieve_framework_parameter( BUILD_INFO, &argc, argv ) == "yes" );
    test_main_tc->run();
    unit_test_log.finish( 1 );

    // report results
    unit_test_result::instance().report( reportlevel, std::cout );

    // return code
    return no_result_code
            ? boost::exit_success
            : ( test_main_result != 0 && test_main_result != boost::exit_success
                   ? test_main_result
                   : unit_test_result::instance().result_code()
              );
}

// ***************************************************************************
//  Revision History :
//
//  $Log$
//  Revision 1.5  2005/02/01 06:40:07  rogeeff
//  copyright update
//  old log entries removed
//  minor stilistic changes
//  depricated tools removed
//
//  Revision 1.4  2005/01/31 07:50:06  rogeeff
//  cdecl portability fix
//
//  Revision 1.3  2005/01/31 06:01:54  rogeeff
//  BOOST_TEST_CALL_DECL correctness fixes
//
//  Revision 1.2  2005/01/30 01:58:33  rogeeff
//  include log explecetly
//
//  Revision 1.1  2005/01/22 19:22:12  rogeeff
//  implementation moved into headers section to eliminate dependency of included/minimal component on src directory
//
//  Revision 1.20  2005/01/19 16:34:06  vawjr
//  Changed the \r\r\n back to \r\n on windows so we don't get errors when compiling
//  on VC++8.0.  I don't know why Microsoft thinks it's a good idea to call this an error,
//  but they do.  I also don't know why people insist on checking out files on Windows and
//  copying them to a unix system to check them in (which will cause exactly this problem)
//
//  Revision 1.19  2005/01/18 08:30:08  rogeeff
//  unit_test_log rework:
//     eliminated need for ::instance()
//     eliminated need for << end and ...END macro
//     straitend interface between log and formatters
//     change compiler like formatter name
//     minimized unit_test_log interface and reworked to use explicit calls
//
// ***************************************************************************

#endif // BOOST_TEST_MAIN_IPP_012205GER

//  (C) Copyright Gennadiy Rozental 2001-2003.
//  Use, modification, and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.
//
//  File        : $RCSfile$
//
//  Version     : $Revision$
//
//  Description : tests all Test Tools but output_test_stream
// ***************************************************************************

// Boost.Test
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_result.hpp>
using namespace boost::unit_test_framework;
using boost::test_toolbox::extended_predicate_value;

// BOOST
#include <boost/compose.hpp>

// STL
#include <iostream>
#include <iomanip>
#include <list>
#include <typeinfo>
#include <cassert>

//____________________________________________________________________________//

#define CHECK_TOOL_USAGE( tool_usage, check )               \
{                                                           \
    boost::test_toolbox::output_test_stream output;         \
                                                            \
    unit_test_log::instance().set_log_stream( output );     \
    { unit_test_result_saver saver;                         \
      tool_usage;                                           \
    }                                                       \
    unit_test_log::instance().set_log_stream( std::cout );  \
    BOOST_CHECK( check );                                   \
}

//____________________________________________________________________________//

#define CHECK_CRITICAL_TOOL_USAGE( tool_usage, nothrow_check, throw_check ) \
{                                                                           \
    boost::test_toolbox::output_test_stream output;                         \
                                                                            \
    unit_test_log::instance().set_log_stream( output );                     \
    try {                                                                   \
        {   unit_test_result_saver saver;                                   \
            tool_usage;                                                     \
        }                                                                   \
        unit_test_log::instance().set_log_stream( std::cout );              \
        BOOST_CHECK( nothrow_check );                                       \
    } catch( boost::test_toolbox::detail::test_tool_failed const&) {        \
        unit_test_log::instance().set_log_stream( std::cout );              \
        BOOST_CHECK( throw_check );                                         \
    }                                                                       \
}

//____________________________________________________________________________//

char
set_unix_slash( char in )
{
    return in == '\\' ? '/' : in;
}

static std::string const&
normalize_file_name( char const* f )
{
    static std::string buffer;

    buffer = f;

    std::transform( buffer.begin(), buffer.end(), buffer.begin(), &set_unix_slash );

    return buffer;
}

#if defined(__BORLANDC__) || defined(__IBMCPP__)

#define CHECK_PATTERN( msg, shift ) \
    (boost::wrap_stringstream().ref() << normalize_file_name( __FILE__ ) << "(" << (__LINE__-shift) << "): " << msg).str()

#else

#define CHECK_PATTERN( msg, shift ) \
    (boost::wrap_stringstream().ref() << normalize_file_name( __FILE__ ) << "(" << __LINE__ << "): " << msg).str()

#endif
//____________________________________________________________________________//

class bool_convertible
{
    struct Tester {};
public:
    operator Tester*() { return static_cast<Tester*>( 0 ) + 1; }
};

void
test_BOOST_CHECK()
{
#define TEST_CASE_NAME << '\"' << "test_BOOST_CHECK" << '\"' <<

    unit_test_log::instance().set_log_threshold_level( log_all_errors );

    CHECK_TOOL_USAGE(
        BOOST_CHECK( true ),
        output.is_empty()
    );

    bool_convertible bc;

    CHECK_TOOL_USAGE(
        BOOST_CHECK( bc ),
        output.is_empty()
    );

    CHECK_TOOL_USAGE(
        BOOST_CHECK( false ),
        output.is_equal( CHECK_PATTERN( "error in " TEST_CASE_NAME ": test false failed\n", 2 ) )
    );

    CHECK_TOOL_USAGE(
        BOOST_CHECK( 1==2 ),
        output.is_equal( CHECK_PATTERN( "error in " TEST_CASE_NAME ": test 1==2 failed\n", 2 ) )
    );

    int i=2;

    CHECK_TOOL_USAGE(
        BOOST_CHECK( i==1 ),
        output.is_equal( CHECK_PATTERN( "error in " TEST_CASE_NAME ": test i==1 failed\n", 2 ) )
    );

    unit_test_log::instance().set_log_threshold_level( log_successful_tests );
    CHECK_TOOL_USAGE(
        BOOST_CHECK( i==2 ),
        output.is_equal( CHECK_PATTERN( "info: test i==2 passed\n", 2 ) )
    );
    unit_test_log::instance().set_log_threshold_level( log_all_errors );
}

//____________________________________________________________________________//

void
test_BOOST_REQUIRE()
{
#undef  TEST_CASE_NAME
#define TEST_CASE_NAME << '\"' << "test_BOOST_REQUIRE" << '\"' <<

    unit_test_log::instance().set_log_threshold_level( log_all_errors );

    CHECK_CRITICAL_TOOL_USAGE(
        BOOST_REQUIRE( true ),
        true, false
    );

    CHECK_CRITICAL_TOOL_USAGE(
        BOOST_REQUIRE( false ),
        false, true
    );

    int j = 3;

    CHECK_CRITICAL_TOOL_USAGE(
        BOOST_REQUIRE( j > 5 ),
        false, output.is_equal( CHECK_PATTERN( "fatal error in " TEST_CASE_NAME ": test j > 5 failed\n", 2 ) )
    );

    unit_test_log::instance().set_log_threshold_level( log_successful_tests );
    CHECK_CRITICAL_TOOL_USAGE(
        BOOST_REQUIRE( j < 5 ),
        output.is_equal( CHECK_PATTERN( "info: test j < 5 passed\n", 1 ) ) , false
    );
    unit_test_log::instance().set_log_threshold_level( log_all_errors );
}

//____________________________________________________________________________//

struct A {
    friend std::ostream& operator<<( std::ostream& str, A const& a ) { str << "struct A"; return str;}
};

void
test_BOOST_MESSAGE()
{
#undef  TEST_CASE_NAME
#define TEST_CASE_NAME << '\"' << "test_BOOST_REQUIRE" << '\"' <<

    unit_test_log::instance().set_log_threshold_level( log_messages );

    CHECK_TOOL_USAGE(
        BOOST_MESSAGE( "still testing" ),
        output.is_equal( "still testing\n" )
    );

    CHECK_TOOL_USAGE(
        BOOST_MESSAGE( "1+1=" << 2 ),
        output.is_equal( "1+1=2\n" )
    );

    int i = 2;
    CHECK_TOOL_USAGE(
        BOOST_MESSAGE( i << "+" << i << "=" << (i+i) ),
        output.is_equal( "2+2=4\n" )
    );

    A a = A();
    CHECK_TOOL_USAGE(
        BOOST_MESSAGE( a ),
        output.is_equal( "struct A\n" )
    );

    CHECK_TOOL_USAGE(
        BOOST_MESSAGE( std::hex << std::showbase << 20 ),
        output.is_equal( "0x14\n" )
    );

    CHECK_TOOL_USAGE(
        BOOST_MESSAGE( std::setw( 4 ) << 20 ),
        output.is_equal( "  20\n" )
        );
}

//____________________________________________________________________________//

void
test_BOOST_WARN()
{
#undef  TEST_CASE_NAME
#define TEST_CASE_NAME << '\"' << "test_BOOST_WARN" << '\"' <<

    unit_test_log::instance().set_log_threshold_level( log_warnings );

    CHECK_TOOL_USAGE(
        BOOST_WARN( sizeof(int) == sizeof(short) ),
        output.is_equal( CHECK_PATTERN( "warning in " TEST_CASE_NAME
                                        ": condition sizeof(int) == sizeof(short) is not satisfied\n", 3 ) )
    );
}

//____________________________________________________________________________//

class bad_func_container : public test_case
{
public:
    bad_func_container() : test_case( "test_BOOST_CHECKPOINT", true, 1 ) {}
    void do_run() {
        throw "some error";
    }
} bad;

void
test_BOOST_CHECKPOINT()
{
#undef  TEST_CASE_NAME
#define TEST_CASE_NAME << '\"' << "test_BOOST_CHECKPOINT" << '\"' <<

    unit_test_log::instance().set_log_threshold_level( log_all_errors );

    BOOST_CHECKPOINT( "Going to do a silly things" );

    CHECK_TOOL_USAGE(
        bad.run(),
        output.is_equal(
            (boost::wrap_stringstream().ref()
                << "Exception in " TEST_CASE_NAME ": C string: some error\n"
                << normalize_file_name( __FILE__ ) << "(" << 266 << "): "
                << "last checkpoint: Going to do a silly things\n").str()
        )
    );
}

//____________________________________________________________________________//

void
test_BOOST_WARN_MESSAGE()
{
#undef  TEST_CASE_NAME
#define TEST_CASE_NAME << '\"' << "test_BOOST_WARN_MESSAGE" << '\"' <<

    unit_test_log::instance().set_log_threshold_level( log_warnings );

    CHECK_TOOL_USAGE(
        BOOST_WARN_MESSAGE( sizeof(int) == sizeof(short), "memory won't be used efficiently" ),
        output.is_equal( CHECK_PATTERN( "warning in " TEST_CASE_NAME ": memory won't be used efficiently\n", 2 ) )
    );

    int obj_size = 33;

    CHECK_TOOL_USAGE(
        BOOST_WARN_MESSAGE( obj_size <= 8, "object size " << obj_size << " too big to be efficiently passed by value" ),
        output.is_equal( CHECK_PATTERN( "warning in " TEST_CASE_NAME
                                        ": object size 33 too big to be efficiently passed by value\n", 3 ) )
    );

}

//____________________________________________________________________________//

void
test_BOOST_CHECK_MESSAGE()
{
#undef  TEST_CASE_NAME
#define TEST_CASE_NAME << '\"' << "test_BOOST_CHECK_MESSAGE" << '\"' <<

    unit_test_log::instance().set_log_threshold_level( log_all_errors );


    CHECK_TOOL_USAGE(
        BOOST_CHECK_MESSAGE( 2+2 == 5, "Well, may be that what I belive in" ),
        output.is_equal( CHECK_PATTERN( "error in " TEST_CASE_NAME ": Well, may be that what I belive in\n", 2 ) )
    );

}

//____________________________________________________________________________//

void
test_BOOST_REQUIRE_MESSAGE()
{
#undef  TEST_CASE_NAME
#define TEST_CASE_NAME << '\"' << "test_BOOST_REQUIRE_MESSAGE" << '\"' <<

    unit_test_log::instance().set_log_threshold_level( log_all_errors );

    CHECK_CRITICAL_TOOL_USAGE(
        BOOST_REQUIRE_MESSAGE( false, "Here we should stop" ),
        false, output.is_equal(
            CHECK_PATTERN( "fatal error in " TEST_CASE_NAME ": Here we should stop" << "\n", 3 ) )
    );
}

//____________________________________________________________________________//

struct B {
    B( int i ) : m_i( i ) {}

    friend bool operator==( B const& b1, B const& b2 ) { return b1.m_i == b2.m_i; }
    friend std::ostream& operator<<( std::ostream& str, B const& b ) { str << "B(" << b.m_i << ")"; return str; }

    int m_i;
};

void
test_BOOST_CHECK_EQUAL()
{
#undef  TEST_CASE_NAME
#define TEST_CASE_NAME << '\"' << "test_BOOST_CHECK_EQUAL" << '\"' <<

    unit_test_log::instance().set_log_threshold_level( log_all_errors );

    int i=1;
    int j=2;

    CHECK_TOOL_USAGE(
        BOOST_CHECK_EQUAL( i, j ),
        output.is_equal( CHECK_PATTERN( "error in " TEST_CASE_NAME ": test i == j failed [1 != 2]\n", 2 ) )
    );

    char const* str1 = "test1";
    char const* str2 = "test12";

    CHECK_TOOL_USAGE(
        BOOST_CHECK_EQUAL( str1, str2 ),
        output.is_equal( CHECK_PATTERN( "error in " TEST_CASE_NAME ": test str1 == str2 failed [test1 != test12]\n", 2 ) )
    );

    str1 = NULL;
    str2 = NULL;

    CHECK_TOOL_USAGE(
        BOOST_CHECK_EQUAL( str1, str2 ),
        output.is_empty()
    );

    str1 = "test";
    str2 = NULL;

    CHECK_TOOL_USAGE(
        BOOST_CHECK_EQUAL( str1, str2 ),
        output.is_equal( CHECK_PATTERN( "error in " TEST_CASE_NAME ": test str1 == str2 failed [test != null string]\n", 2 ) )
    );

    B b1(1);
    B b2(2);

    CHECK_TOOL_USAGE(
        BOOST_CHECK_EQUAL( b1, b2 ),
        output.is_equal( CHECK_PATTERN( "error in " TEST_CASE_NAME ": test b1 == b2 failed [B(1) != B(2)]\n", 2 ) )
    );
}

//____________________________________________________________________________//

bool is_even( int i )        { return i%2 == 0;  }
int  foo( int arg, int mod ) { return arg % mod; }

BOOST_TEST_DONT_PRINT_LOG_VALUE( std::list<int> )

extended_predicate_value
compare_lists( std::list<int> const& l1, std::list<int> const& l2 )
{
    if( l1.size() != l2.size() ) {
        extended_predicate_value res( false );

        res.p_message.reset( new boost::wrap_stringstream );

        *res.p_message << " Different sizes [" << l1.size() << "!=" << l2.size() << "]";

        return res;
    }

    return true;
}

void
test_BOOST_CHECK_PREDICATE()
{
#undef  TEST_CASE_NAME
#define TEST_CASE_NAME << '\"' << "test_BOOST_CHECK_PREDICATE" << '\"' <<

    CHECK_TOOL_USAGE(
        BOOST_CHECK_PREDICATE( &is_even, 1, (14) ),
        output.is_empty()
    );

    int i = 17;
    CHECK_TOOL_USAGE(
        BOOST_CHECK_PREDICATE( &is_even, 1, (i) ),
        output.is_equal( CHECK_PATTERN( "error in " TEST_CASE_NAME ": test &is_even(i) failed for 17\n", 2 ) )
    );

    CHECK_TOOL_USAGE(
        BOOST_CHECK_PREDICATE( std::not_equal_to<int>(), 2, (i,17) ),
        output.is_equal( CHECK_PATTERN( "error in " TEST_CASE_NAME ": test std::not_equal_to<int>()(i, 17) failed for (17, 17)\n", 2 ) )
    );

    CHECK_TOOL_USAGE(
        BOOST_CHECK_PREDICATE( boost::compose_f_gxy( std::ptr_fun( &is_even ), std::ptr_fun( &foo ) ), 2, (i,15) ),
        output.is_empty()
    );

    std::list<int> l1, l2, l3;
    l1.push_back( 1 );
    l3.push_back( 1 );
    l1.push_back( 2 );
    l3.push_back( 3 );

    CHECK_TOOL_USAGE(
        BOOST_CHECK_PREDICATE( &compare_lists, 2, (l1,l2) ),
        output.is_equal( CHECK_PATTERN( "error in " TEST_CASE_NAME ": test &compare_lists(l1, l2) failed for (, ) Different sizes [2!=0]\n", 2 ) )
    );
}

//____________________________________________________________________________//

void
test_BOOST_REQUIRE_PREDICATE()
{
#undef  TEST_CASE_NAME
#define TEST_CASE_NAME << '\"' << "test_BOOST_REQUIRE_PREDICATE" << '\"' <<

    int arg1 = 1;
    int arg2 = 2;

    CHECK_CRITICAL_TOOL_USAGE(
        BOOST_REQUIRE_PREDICATE( std::less_equal<int>(), 2, ( arg1, arg2 ) ),
        output.is_empty(), false
    );

   CHECK_CRITICAL_TOOL_USAGE(
        BOOST_REQUIRE_PREDICATE( std::less_equal<int>(), 2, ( arg2, arg1 ) ),
        false, output.is_equal( CHECK_PATTERN( 
                    "fatal error in " TEST_CASE_NAME ": test std::less_equal<int>()(arg2, arg1) "
                    "failed for (" << arg2 << ", " << arg1 << ")\n", 4 ) )
    );
}

//____________________________________________________________________________//

void
test_BOOST_ERROR()
{
#undef  TEST_CASE_NAME
#define TEST_CASE_NAME << '\"' << "test_BOOST_ERROR" << '\"' <<

    unit_test_log::instance().set_log_threshold_level( log_all_errors );

    CHECK_TOOL_USAGE(
        BOOST_ERROR( "Fail to miss an error" ),
        output.is_equal( CHECK_PATTERN( "error in " TEST_CASE_NAME ": Fail to miss an error\n", 2 ) )
    );

    CHECK_CRITICAL_TOOL_USAGE(
        BOOST_FAIL( "No! No! Show must go on." ),
        false, output.is_equal( CHECK_PATTERN( "fatal error in " TEST_CASE_NAME ": No! No! Show must go on.\n", 2 ) )
    );
}

//____________________________________________________________________________//

struct my_exception {
    explicit my_exception( int ec = 0 ) : m_error_code( ec ) {}
    
    int m_error_code;
};

bool is_critical( my_exception const& ex ) { return ex.m_error_code < 0; }

void
test_BOOST_CHECK_THROW()
{
#undef  TEST_CASE_NAME
#define TEST_CASE_NAME << '\"' << "test_BOOST_CHECK_THROW" << '\"' <<

    unit_test_log::instance().set_log_threshold_level( log_all_errors );

    int i=0;
    CHECK_TOOL_USAGE(
        BOOST_CHECK_THROW( i++, my_exception ),
        output.is_equal( CHECK_PATTERN( "error in " TEST_CASE_NAME ": exception my_exception is expected\n", 2 ) )
    );

    unit_test_log::instance().set_log_threshold_level( log_successful_tests );

    CHECK_TOOL_USAGE(
        BOOST_CHECK_THROW( throw my_exception(), my_exception ),
        output.is_equal( CHECK_PATTERN( "info: exception my_exception is caught\n", 2 ) )
    );

    unit_test_log::instance().set_log_threshold_level( log_all_errors );
}

//____________________________________________________________________________//

void
test_BOOST_CHECK_EXCEPTION()
{
#undef  TEST_CASE_NAME
#define TEST_CASE_NAME << '\"' << "test_BOOST_CHECK_EXCEPTION" << '\"' <<

    unit_test_log::instance().set_log_threshold_level( log_all_errors );

    CHECK_TOOL_USAGE(
        BOOST_CHECK_EXCEPTION( throw my_exception( 1 ), my_exception, is_critical ),
        output.is_equal( CHECK_PATTERN( "error in " TEST_CASE_NAME ": incorrect exception my_exception is caught\n", 2 ) )
    );

    unit_test_log::instance().set_log_threshold_level( log_successful_tests );

    CHECK_TOOL_USAGE(
        BOOST_CHECK_EXCEPTION( throw my_exception( -1 ), my_exception, is_critical ),
        output.is_equal( CHECK_PATTERN( "info: incorrect exception my_exception is caught\n", 2 ) )
    );

    unit_test_log::instance().set_log_threshold_level( log_all_errors );
}

//____________________________________________________________________________//

void
test_BOOST_CHECK_NO_THROW()
{
#undef  TEST_CASE_NAME
#define TEST_CASE_NAME << '\"' << "test_BOOST_CHECK_NO_THROW" << '\"' <<

    int i=0;
    CHECK_TOOL_USAGE(
        BOOST_CHECK_NO_THROW( i++ ),
        output.is_empty() 
    );

    CHECK_TOOL_USAGE(
        BOOST_CHECK_NO_THROW( throw my_exception() ),
        output.is_equal( CHECK_PATTERN( "error in " TEST_CASE_NAME ": exception was thrown by throw my_exception()\n", 2 ) )
    );
}

//____________________________________________________________________________//

void
test_BOOST_CHECK_EQUAL_COLLECTIONS()
{
#undef  TEST_CASE_NAME
#define TEST_CASE_NAME << '\"' << "test_BOOST_CHECK_EQUAL_COLLECTIONS" << '\"' <<

    unit_test_log::instance().set_log_threshold_level( log_all_errors );

    int pattern [] = { 1, 2, 3, 4, 5, 6, 7 };

    std::list<int> testlist;

    testlist.push_back( 1 );
    testlist.push_back( 2 );
    testlist.push_back( 4 ); // 3
    testlist.push_back( 4 );
    testlist.push_back( 5 );
    testlist.push_back( 7 ); // 6
    testlist.push_back( 7 );

#if !defined(__BORLANDC__)
    CHECK_TOOL_USAGE(
        BOOST_CHECK_EQUAL_COLLECTIONS( testlist.begin(), testlist.end(), pattern ),
            output.is_equal( CHECK_PATTERN( 
              "error in " TEST_CASE_NAME ": test {testlist.begin(), testlist.end()} == {pattern, ...} failed in a position 2 [4 != 3]\n"
              << normalize_file_name( __FILE__ ) << "(" << __LINE__ << "): "
              << "error in " TEST_CASE_NAME ": test {testlist.begin(), testlist.end()} == {pattern, ...} failed in a position 5 [7 != 6]\n"
              , 6 ) )
    );
#else
    CHECK_TOOL_USAGE(
        BOOST_CHECK_EQUAL_COLLECTIONS( testlist.begin(), testlist.end(), pattern ),
            output.is_equal( CHECK_PATTERN( 
              "error in " TEST_CASE_NAME ": test {testlist.begin(), testlist.end()} == {pattern, ...} failed in a position 2 [4 != 3]\n"
              << normalize_file_name( __FILE__ ) << "(" << (__LINE__-6) << "): "
              << "error in " TEST_CASE_NAME ": test {testlist.begin(), testlist.end()} == {pattern, ...} failed in a position 5 [7 != 6]\n"
              , 6 ) )
    );
#endif

}

//____________________________________________________________________________//

void
test_BOOST_IS_DEFINED()
{
#define SYMBOL1
#define SYMBOL2 std::cout
#define ONE_ARG( arg ) arg
#define TWO_ARG( arg1, arg2 ) BOOST_JOIN( arg1, arg2 )

    BOOST_CHECK( BOOST_IS_DEFINED(SYMBOL1) );
    BOOST_CHECK( BOOST_IS_DEFINED(SYMBOL2) );
    BOOST_CHECK( !BOOST_IS_DEFINED( SYMBOL3 ) );
    BOOST_CHECK( BOOST_IS_DEFINED( ONE_ARG(arg1) ) );
    BOOST_CHECK( !BOOST_IS_DEFINED( ONE_ARG1(arg1) ) );
    BOOST_CHECK( BOOST_IS_DEFINED( TWO_ARG(arg1,arg2) ) );
    BOOST_CHECK( !BOOST_IS_DEFINED( TWO_ARG1(arg1,arg2) ) );
}

//____________________________________________________________________________//

void
test_BOOST_BITWISE_EQUAL()
{
#undef  TEST_CASE_NAME
#define TEST_CASE_NAME << '\"' << "test_BOOST_BITWISE_EQUAL" << '\"' <<

    CHECK_TOOL_USAGE(
        BOOST_BITWISE_EQUAL( 0x16, 0x16 ),
        output.is_empty()
    );

    CHECK_TOOL_USAGE(
        BOOST_BITWISE_EQUAL( (char)0x06, (char)0x16 ),
        output.is_equal( CHECK_PATTERN( "error in " TEST_CASE_NAME ": test (char)0x06 =.= (char)0x16 in the position 4 failed\n", 2 ) )
    );

    CHECK_TOOL_USAGE(
        BOOST_BITWISE_EQUAL( (char)0x26, (char)0x04 ),
        output.is_equal( 
        std::string( CHECK_PATTERN( "error in " TEST_CASE_NAME ": test (char)0x26 =.= (char)0x04 in the position 1 failed\n", 4 ) )
            .append( CHECK_PATTERN( "error in " TEST_CASE_NAME ": test (char)0x26 =.= (char)0x04 in the position 5 failed\n", 4 ) ) )
    );
}

//____________________________________________________________________________//


test_suite*
init_unit_test_suite( int /*argc*/, char* /*argv*/[] )
{
    test_suite* test = BOOST_TEST_SUITE("Test Tools test");

    test->add( BOOST_TEST_CASE( &test_BOOST_CHECK ) );
    test->add( BOOST_TEST_CASE( &test_BOOST_REQUIRE ) );
    test->add( BOOST_TEST_CASE( &test_BOOST_MESSAGE ) );
    test->add( BOOST_TEST_CASE( &test_BOOST_WARN ) );
    test->add( BOOST_TEST_CASE( &test_BOOST_CHECKPOINT ) );
    test->add( BOOST_TEST_CASE( &test_BOOST_WARN_MESSAGE ) );
    test->add( BOOST_TEST_CASE( &test_BOOST_CHECK_MESSAGE ) );
    test->add( BOOST_TEST_CASE( &test_BOOST_REQUIRE_MESSAGE ) );
    test->add( BOOST_TEST_CASE( &test_BOOST_CHECK_EQUAL ) );
    test->add( BOOST_TEST_CASE( &test_BOOST_ERROR ) );
    test->add( BOOST_TEST_CASE( &test_BOOST_CHECK_THROW ) );
    test->add( BOOST_TEST_CASE( &test_BOOST_CHECK_NO_THROW ) );
    test->add( BOOST_TEST_CASE( &test_BOOST_CHECK_EXCEPTION ) );
    test->add( BOOST_TEST_CASE( &test_BOOST_CHECK_EQUAL_COLLECTIONS ) );
    test->add( BOOST_TEST_CASE( &test_BOOST_IS_DEFINED ) );
    test->add( BOOST_TEST_CASE( &test_BOOST_CHECK_PREDICATE ) );
    test->add( BOOST_TEST_CASE( &test_BOOST_REQUIRE_PREDICATE ) );
    test->add( BOOST_TEST_CASE( &test_BOOST_BITWISE_EQUAL ) );

    return test;
}

//____________________________________________________________________________//

// ***************************************************************************
//  Revision History :
//  
//  $Log$
//  Revision 1.25  2003/11/06 07:59:20  rogeeff
//  *** empty log message ***
//
//  Revision 1.24  2003/11/06 07:31:42  rogeeff
//  Licence update
//
//  Revision 1.23  2003/11/02 06:12:06  rogeeff
//  manipulator usage tests added
//  collections comarison tests updated
//
//  Revision 1.22  2003/10/27 07:13:32  rogeeff
//  licence update
//
//  Revision 1.21  2003/07/15 09:01:36  rogeeff
//  eliminate tolerance definition by number of rounding errors
//
//  Revision 1.20  2003/07/02 09:14:22  rogeeff
//  move log formatter in public interface
//
//  Revision 1.19  2003/06/20 11:01:57  rogeeff
//  no message
//
//  Revision 1.18  2003/06/09 09:24:47  rogeeff
//  added test for:
//  BOOST_TEST_DONT_PRINT_LOG_VALUE
//  custom predicate
//  BOOST_CHECK_EXCEPTION
//
//  Revision 1.17  2003/02/18 22:17:12  rogeeff
//  Visual Age fix
//
//  Revision 1.16  2003/02/14 06:40:58  rogeeff
//  Intel on linux fix
//
//  Revision 1.15  2003/02/13 08:47:12  rogeeff
//  *** empty log message ***
//
//  Revision 1.14  2002/12/09 05:18:34  rogeeff
//  switched to use unit_test_result_saver for internal testing
//  switched to wrap_stringstream
//  test cases added for the NULL char strings comparisons
//
//  Revision 1.13  2002/11/02 20:23:24  rogeeff
//  wrapstream copy constructor isuue fix reworked
//
//  Revision 1.12  2002/11/02 20:04:43  rogeeff
//  release 1.29.0 merged into the main trank
//

// ***************************************************************************

// EOF

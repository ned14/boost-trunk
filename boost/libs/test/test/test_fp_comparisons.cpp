//  (C) Copyright Gennadiy Rozental 2001-2003.
//  See accompanying license for terms and conditions of use.

//  See http://www.boost.org for most recent version including documentation.
//
//  File        : $RCSfile$
//
//  Version     : $Revision$
//
//  Description : tests floating point comparison algorithms
// ***************************************************************************

// Boost.Test
#include <boost/test/floating_point_comparison.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_result.hpp>
#include <boost/test/test_case_template.hpp>
using namespace boost::unit_test_framework;
using namespace boost::test_toolbox;

// Boost
#include <boost/mpl/list.hpp>

// STL
#include <iostream>

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

#if !defined(__BORLANDC__)
#define CHECK_PATTERN( msg, shift ) \
    (boost::wrap_stringstream().ref() << normalize_file_name( __FILE__ ) << "(" << __LINE__ << "): " << msg).str()

#else

#define CHECK_PATTERN( msg, shift ) \
    (boost::wrap_stringstream().ref() << normalize_file_name( __FILE__ ) << "(" << (__LINE__-shift) << "): " << msg).str()

#endif
//____________________________________________________________________________//

template<typename FPT>
void
test_BOOST_CHECK_CLOSE( FPT = FPT() )
{
#undef  TEST_CASE_NAME
#define TEST_CASE_NAME << '\"' << "test_BOOST_CHECK_CLOSE" << "\"" <<
    unit_test_log::instance().set_log_threshold_level( log_messages );

    BOOST_MESSAGE( "testing BOOST_CHECK_CLOSE for " << typeid(FPT).name() );


#define BOOST_CHECK_CLOSE_SHOULD_PASS( first, second, e )       \
    fp1     = static_cast<FPT>(first);                          \
    fp2     = static_cast<FPT>(second);                         \
    epsilon = static_cast<FPT>(e);                              \
                                                                \
    CHECK_TOOL_USAGE(                                           \
        BOOST_CHECK_CLOSE( fp1, fp2, epsilon ),                 \
        output.is_empty()                                       \
    )                                                           \
/**/

#define BOOST_CHECK_CLOSE_SHOULD_FAIL( first, second, e )       \
    fp1     = static_cast<FPT>(first);                          \
    fp2     = static_cast<FPT>(second);                         \
    epsilon = static_cast<FPT>(e);                              \
                                                                \
    CHECK_TOOL_USAGE(                                           \
        BOOST_CHECK_CLOSE( fp1, fp2, epsilon ),                 \
        output.is_equal( CHECK_PATTERN( "error in " TEST_CASE_NAME ": test fp1 ~= fp2 failed [" \
                                        << fp1 << " !~= " << fp2 << " (+/-" << epsilon << ")]\n", 0 ) ) \
    )                                                           \
/**/
    FPT fp1, fp2, epsilon;

    BOOST_CHECK_CLOSE_SHOULD_PASS( 1, 1, 0 );

    BOOST_CHECK_CLOSE_SHOULD_FAIL( 0, 1e-20, 1e-7 );
    BOOST_CHECK_CLOSE_SHOULD_FAIL( 0, 1e-30, 1e-7 );
    BOOST_CHECK_CLOSE_SHOULD_FAIL( 0, -1e-10, 1e-3 );
    BOOST_CHECK_CLOSE_SHOULD_FAIL( 0.123456, 0.123457, 1e-6 );

    BOOST_CHECK_CLOSE_SHOULD_PASS( 0.123456, 0.123457, 1e-5 );

    BOOST_CHECK_CLOSE_SHOULD_FAIL( 0.123456, -0.123457, 1e-5 );

    BOOST_CHECK_CLOSE_SHOULD_PASS( 1.23456e28, 1.23457e28, 1e-5 );

    BOOST_CHECK_CLOSE_SHOULD_FAIL( 1.23456e-10, 1.23457e-11, 1e-5 );
    BOOST_CHECK_CLOSE_SHOULD_FAIL( 1.111e-10, 1.112e-10, 0.0008999 );
    BOOST_CHECK_CLOSE_SHOULD_FAIL( 1.112e-10, 1.111e-10, 0.0008999 );

    BOOST_CHECK_CLOSE_SHOULD_PASS( 1     , 1.0001, 1.1e-4 );
    BOOST_CHECK_CLOSE_SHOULD_PASS( 1.0002, 1.0001, 1.1e-4 );
    
    BOOST_CHECK_CLOSE_SHOULD_FAIL( 1     , 1.0002, 1.1e-4 );
}

BOOST_META_FUNC_TEST_CASE( test_BOOST_CHECK_CLOSE );

//____________________________________________________________________________//

void
test_close_at_tolerance()
{
#undef  TEST_CASE_NAME
#define TEST_CASE_NAME << '\"' << "test_close_at_tolerance" << "\"" <<

    double fp1     = 1.00000001;
    double fp2     = 1.00000002;
    double epsilon = 1e-8;

    CHECK_TOOL_USAGE(
        BOOST_CHECK_PREDICATE( close_at_tolerance<double>( epsilon, FPC_WEAK ), 2, ( fp1, fp2 ) ),
        output.is_empty()
    );

    CHECK_TOOL_USAGE(
        BOOST_CHECK_CLOSE( fp1, fp2, epsilon ),
        output.is_equal( CHECK_PATTERN( "error in " TEST_CASE_NAME ": test fp1 ~= fp2 failed [" 
                                        << fp1 << " !~= " << fp2 << " (+/-" << epsilon << ")]\n", 3 ) )
    );

    fp1     = 1.23456e-10;
    fp2     = 1.23457e-10;
    epsilon = 8.1e-6;

    CHECK_TOOL_USAGE(
        BOOST_CHECK_PREDICATE( close_at_tolerance<double>( epsilon, FPC_WEAK ), 2, ( fp1, fp2 ) ),
        output.is_empty()
    );

    CHECK_TOOL_USAGE(
        BOOST_CHECK_PREDICATE( close_at_tolerance<double>( epsilon ), 2, ( fp1, fp2 ) ),
        output.is_equal( CHECK_PATTERN( 
                    "error in " TEST_CASE_NAME ": test close_at_tolerance<double>( epsilon )(fp1, fp2) "
                    "failed for (" << fp1 << ", " << fp2 << ")\n", 4 ) )
    );
}

//____________________________________________________________________________//

test_suite*
init_unit_test_suite( int /*argc*/, char* /*argv*/[] ) {
    test_suite* test = BOOST_TEST_SUITE("FP compare test");

    typedef boost::mpl::list<float,double,long double> FPTs;

    test->add( BOOST_FUNC_TEMPLATE_TEST_CASE( test_BOOST_CHECK_CLOSE, FPTs  ) );
    test->add( BOOST_TEST_CASE( &test_close_at_tolerance ) );

    return test;
}

//____________________________________________________________________________//

// ***************************************************************************
//  Revision History :
//  
//  $Log$
//  Revision 1.6  2003/10/27 07:13:32  rogeeff
//  licence update
//
//  Revision 1.5  2003/07/15 09:01:36  rogeeff
//  eliminate tolerance definition by number of rounding errors
//
//  Revision 1.4  2003/07/02 09:14:22  rogeeff
//  move log formatter in public interface
//
//  Revision 1.3  2003/06/09 09:25:24  rogeeff
//  1.30.beta1
//
//  Revision 1.2  2003/02/15 21:53:39  rogeeff
//  cwpro8 fix

// ***************************************************************************

// EOF

//  (C) Copyright Gennadiy Rozental 2001-2004.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.
//
//  File        : $RCSfile$
//
//  Version     : $Revision$
//
//  Description : privide core implementation for Unit Test Framework. 
//  Extensions could be provided in separate files
// ***************************************************************************

#ifndef BOOST_UNIT_TEST_MAIN_IPP_012205GER
#define BOOST_UNIT_TEST_MAIN_IPP_012205GER

// Boost.Test
#include <boost/test/unit_test_suite.hpp>
#include <boost/test/unit_test_log.hpp>
#include <boost/test/unit_test_result.hpp>
#include <boost/test/utils/wrap_stringstream.hpp>

// BOOST
#include <boost/mem_fn.hpp>
#include <boost/timer.hpp>

// STL
#include <list>
#include <algorithm>

#include <boost/test/detail/suppress_warnings.hpp>

namespace boost {

namespace unit_test {

// ************************************************************************** //
// **************            test_case_scope_tracker           ************** //
// ************************************************************************** //

struct test_case_scope_tracker {
    explicit            test_case_scope_tracker( test_case const& tc ) 
    : m_tc( tc )
    {
        unit_test_log.track_test_case_enter( m_tc );
    }
    ~test_case_scope_tracker()
    {
        unit_test_log.track_test_case_exit( m_tc, (long)(m_timer.elapsed() * 1e6) );
    }

private:
    test_case const&    m_tc;
    boost::timer        m_timer;
};

// ************************************************************************** //
// **************                   test_case                  ************** //
// ************************************************************************** //

ut_detail::unit_test_monitor the_monitor;

typedef unit_test_result const* unit_test_result_cptr;

struct test_case::Impl {
    Impl( bool monitor_run_ ) : m_monitor_run( monitor_run_ ), m_results_set( unit_test_result_cptr() ) {}

    bool                        m_monitor_run;          // true - unit_test_monitor will be user to monitor running
                                                        // of implementation function
    std::list<test_case const*> m_dependencies_list;    // list of test cases this test case depends on. We won't run it until they pass
    unit_test_result_cptr       m_results_set;          // results set instance reference for this test case
    
    static bool                 s_abort_testing;        // used to flag critical error and try gracefully stop testing

    bool                        check_dependencies();
};

bool test_case::Impl::s_abort_testing = false;

//____________________________________________________________________________//


inline bool
test_case::Impl::check_dependencies()
{
    return std::find_if( m_dependencies_list.begin(), 
                         m_dependencies_list.end(), 
                         std::not1( boost::mem_fn( &test_case::has_passed ) ) ) == m_dependencies_list.end();
}

//____________________________________________________________________________//

test_case::test_case( const_string name_, bool type, unit_test_counter stages_amount_, bool monitor_run_ )
: p_timeout( 0 ), p_expected_failures( 0 ), p_type( type ),
  p_name( std::string( name_.begin(), name_.end() ) ),
  p_compound_stage( false ), p_stages_amount( stages_amount_ ),
  m_pimpl( new Impl( monitor_run_ ) )
{
}

//____________________________________________________________________________//

unit_test_counter
test_case::size() const
{
    return 1;
}

//____________________________________________________________________________//

void
test_case::depends_on( test_case const* rhs )
{
    m_pimpl->m_dependencies_list.push_back( rhs );
}

//____________________________________________________________________________//

bool
test_case::has_passed() const
{
    return m_pimpl->m_results_set != unit_test_result_cptr() && m_pimpl->m_results_set->has_passed();
}

//____________________________________________________________________________//

void
test_case::run()
{
    using ut_detail::unit_test_monitor;

    test_case_scope_tracker scope_tracker( *this );
    
    // 0. Check if we allowed to run this test case
    if( !m_pimpl->check_dependencies() )
        return;

    m_pimpl->s_abort_testing = false;

    // 1. Init test results
    unit_test_result_tracker result_tracker( p_name.get(), p_expected_failures );
    m_pimpl->m_results_set = &unit_test_result::instance();

    // 2. Initialize test case
    if( m_pimpl->m_monitor_run ) {
        error_level_type setup_result =
            the_monitor.execute_and_translate( this, &test_case::do_init, p_timeout );

        if( setup_result != unit_test_monitor::test_ok ) {
            m_pimpl->s_abort_testing  = unit_test_monitor::is_critical_error( setup_result );

            BOOST_UT_LOG_ENTRY( log_fatal_errors ) << "Test case setup has failed";

            return;
        }
    }
    else {
        do_init();
    }

    // 3. Run test case (all stages)
    for( unit_test_counter i=0; i != p_stages_amount; ++i ) {
        p_compound_stage.value = false; // could be set by do_run to mark compound stage;
                                        // than no need to report progress here

        if( m_pimpl->m_monitor_run ) {
            error_level_type run_result =
                the_monitor.execute_and_translate( this, &test_case::do_run, p_timeout );

            if( unit_test_monitor::is_critical_error( run_result ) ) {
                m_pimpl->s_abort_testing = true;

                BOOST_UT_LOG_ENTRY( log_fatal_errors ) << "Testing aborted";
            }

            if( m_pimpl->s_abort_testing )
                return;
        }
        else {
            do_run();
        }

        if( p_stages_amount != 1 && !p_compound_stage ) // compound test
            unit_test_log.log_progress();
    }

    // 3. Finalize test case
    if( m_pimpl->m_monitor_run ) {
        error_level_type teardown_result =
            the_monitor.execute_and_translate( this, &test_case::do_destroy, p_timeout );
        
        m_pimpl->s_abort_testing = unit_test_monitor::is_critical_error( teardown_result );
    }
    else {
        do_destroy();
    }
}

//____________________________________________________________________________//

// ************************************************************************** //
// **************                  test_suite                  ************** //
// ************************************************************************** //

struct test_suite::Impl {
    std::list<test_case*>           m_test_cases;
    std::list<test_case*>::iterator m_curr_test_case;
    unit_test_counter               m_cumulative_size;
};

//____________________________________________________________________________//

test_suite::test_suite( const_string name )
: test_case( name, false, 0, false ), m_pimpl( new Impl )
{
    m_pimpl->m_cumulative_size = 0;
}

//____________________________________________________________________________//

static void safe_delete_test_case( test_case* ptr ) { boost::checked_delete<test_case>( ptr ); }

test_suite::~test_suite()
{   
    std::for_each( m_pimpl->m_test_cases.begin(), m_pimpl->m_test_cases.end(), &safe_delete_test_case );
}

//____________________________________________________________________________//

void
test_suite::add( test_case* tc, unit_test_counter exp_fail, int timeout )
{
    if( exp_fail != 0 ) {
        tc->p_expected_failures.value = exp_fail;
    }

    p_expected_failures.value += tc->p_expected_failures;

    if( timeout != 0 )
        tc->p_timeout.value = timeout;

    m_pimpl->m_test_cases.push_back( tc );
    m_pimpl->m_cumulative_size += tc->size();

    p_stages_amount.value = p_stages_amount + 1;
}

//____________________________________________________________________________//

unit_test_counter
test_suite::size() const
{
    return m_pimpl->m_cumulative_size;
}

//____________________________________________________________________________//

void
test_suite::do_init()
{
    m_pimpl->m_curr_test_case = m_pimpl->m_test_cases.begin();
}

//____________________________________________________________________________//

void
test_suite::do_run()
{
    if( (*m_pimpl->m_curr_test_case)->size() > 1 )
        p_compound_stage.value = true;
    (*m_pimpl->m_curr_test_case)->run();
    ++m_pimpl->m_curr_test_case;
}

//____________________________________________________________________________//

// ************************************************************************** //
// **************               object generators              ************** //
// ************************************************************************** //

namespace ut_detail {

std::string const&
normalize_test_case_name( std::string& name_ )
{
    if( name_[0] == '&' )
        name_.erase( 0, 1 );

    return name_;
}

} // namespace ut_detail

} // namespace unit_test

} // namespace boost

#include <boost/test/detail/enable_warnings.hpp>

// ***************************************************************************
//  Revision History :
//  
//  $Log$
//  Revision 1.1  2005/01/22 19:22:13  rogeeff
//  implementation moved into headers section to eliminate dependency of included/minimal component on src directory
//
//  Revision 1.19  2005/01/21 07:26:41  rogeeff
//  xml printing helpers reworked to employ generic custom manipulators
//
//  Revision 1.17  2005/01/18 08:30:08  rogeeff
//  unit_test_log rework:
//     eliminated need for ::instance()
//     eliminated need for << end and ...END macro
//     straitend interface between log and formatters
//     change compiler like formatter name
//     minimized unit_test_log interface and reworked to use explicit calls
//
//  Revision 1.16  2004/06/07 07:34:23  rogeeff
//  detail namespace renamed
//
//  Revision 1.15  2004/05/21 06:26:10  rogeeff
//  licence update
//
//  Revision 1.14  2004/05/18 13:26:47  dgregor
//  unit_test_suite.cpp: Try to work around an Intel 7.1 bug with conversions in a base class.
//
//  Revision 1.13  2004/05/11 11:05:04  rogeeff
//  basic_cstring introduced and used everywhere
//  class properties reworked
//  namespace names shortened
//
//  Revision 1.12  2003/12/01 00:42:37  rogeeff
//  prerelease cleaning
//
// ***************************************************************************

#endif // BOOST_UNIT_TEST_MAIN_IPP_012205GER

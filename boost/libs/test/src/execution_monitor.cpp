//  (C) Copyright Gennadiy Rozental 2001-2004.
//  (C) Copyright Beman Dawes and Ullrich Koethe 1995-2001.
//  Use, modification, and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.
//
//  File        : $RCSfile$
//
//  Version     : $Revision$
//
//  Description : provides execution monitor implementation for all supported
//  configurations, including Microsoft structured exception based, unix signals
//  based and special workarounds for borland
//
//  Note that when testing requirements or user wishes preclude use of this
//  file as a separate compilation unit, it may be included as a header file.
//
//  Header dependencies are deliberately restricted to reduce coupling to other
//  boost libraries.
// ***************************************************************************

// Boost.Test
#include <boost/test/execution_monitor.hpp>

// BOOST
#include <boost/cstdlib.hpp>  // for exit codes
#include <boost/config.hpp>   // for workarounds

// STL
#include <string>             // for string
#include <new>                // for bad_alloc
#include <typeinfo>           // for bad_cast, bad_typeid
#include <exception>          // for exception, bad_exception
#include <stdexcept>          // for std exception hierarchy
#include <cstring>            // for C string API
#include <cassert>            // for assert
#include <cstddef>            // for NULL

#ifdef BOOST_NO_STDC_NAMESPACE
namespace std { using ::strlen; using ::strncat; }
#endif

// Microsoft + other compatible compilers such as Intel
#if !defined(BOOST_DISABLE_WIN32) &&                                        \
    !defined(__BORLANDC__) &&                                               \
    (defined(_MSC_VER) && !defined(__COMO__)) ||                            \
    (defined(__INTEL__) && defined(__MWERKS__) && __MWERKS__ >= 0x3000)

#define BOOST_MS_STRCTURED_EXCEPTION_HANDLING
#include <wtypes.h>
#include <winbase.h>
#include <excpt.h>
#include <eh.h>

#if !defined(NDEBUG) && !defined(__MWERKS__)  // __MWERKS__ does not seem to supply implementation of C runtime debug hooks, causing linking errors
#define BOOST_MS_CRT_DEBUG_HOOK
#include <crtdbg.h>
#endif

#elif (defined(__BORLANDC__) && defined(_Windows) && !defined(BOOST_DISABLE_WIN32))
#define BOOST_MS_STRCTURED_EXCEPTION_HANDLING
#include <windows.h>  // Borland 5.5.1 has its own way of doing things.

#elif defined(BOOST_HAS_SIGACTION)

#define BOOST_SIGACTION_BASED_SIGNAL_HANDLING
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>

#else

#define BOOST_NO_SIGNAL_HANDLING

#endif

namespace boost {

namespace detail {

using unit_test::const_string;

//  boost::execution_monitor::execute() calls boost::detail::catch_signals() to
//    execute user function with signals control
//  boost::execution_monitor::execute() calls boost::detail::report_error(...) to
//    report any caught exception and throw execution_exception

const std::size_t REPORT_ERROR_BUFFER_SIZE = 512;

static int  catch_signals( execution_monitor & exmon, bool catch_system_errors, int timeout ); //  timeout is in seconds. 0 implies none.

static void report_error( 
    execution_exception::error_code   ec,
    const_string                      msg1,         // first part of the message
    const_string                      msg2 = "" );  // second part of the message; sum length msg1 + msg2 should not
                                                    // exceed REPORT_ERROR_BUFFER_SIZE; never concatenate messages
                                                    // manually, cause it should work even in case of memory lack

//____________________________________________________________________________//

// Declaration for Microsoft structured exception handling (unix alternative - signal)
#ifdef BOOST_MS_STRCTURED_EXCEPTION_HANDLING

//  this class defined per the Microsoft structured exception documentation
class ms_se_exception {
public:
    // Constructor
    explicit        ms_se_exception( unsigned int n )
    : m_se_id( n )                      {}

    // Destructor
                    ~ms_se_exception()  {}

    // access methods
    unsigned int    id() const          { return m_se_id; }

private:
    // Data members
    unsigned int    m_se_id;
};

//____________________________________________________________________________//

void ms_se_trans_func( unsigned int id, _EXCEPTION_POINTERS* exps );
void ms_se_forward_func( unsigned int id, _EXCEPTION_POINTERS* exps );
static void report_ms_se_error( unsigned int id );

//____________________________________________________________________________//

// Declarations for unix-style signal handling
#elif defined(BOOST_SIGACTION_BASED_SIGNAL_HANDLING)

class unix_signal_exception {
    typedef execution_exception::error_code error_code_type;
public:
    // Constructor
    unix_signal_exception( execution_exception::error_code ec, const_string em )
    : m_error_code( ec ), m_error_message( em )             {}

    // Destructor
    ~unix_signal_exception()                                {}

    // access methods
    error_code_type error_code() const      { return m_error_code;    }
    const_string    error_message() const   { return m_error_message; }
private:
    // Data members
    error_code_type m_error_code;
    const_string    m_error_message;
};

#endif

//____________________________________________________________________________//

#if defined(BOOST_MS_CRT_DEBUG_HOOK)

int
assert_reporting_function( int reportType, char* userMessage, int* retVal )
{
    switch( reportType ) {
    case _CRT_ASSERT:
        detail::report_error( execution_exception::user_error, userMessage );

        return 1; // return value and retVal are not important since we never reach this line
    case _CRT_ERROR:
        detail::report_error( execution_exception::system_error, userMessage );

        return 1; // return value and retVal are not important since we never reach this line
    default:
        return 0; // use usual reporting method
    }
}

#endif

} // namespace detail

// ************************************************************************** //
// **************               execution_monitor              ************** //
// ************************************************************************** //

int
execution_monitor::run_function()
{
    return m_custom_translators ? (*m_custom_translators)( *this ) : function();
}

//____________________________________________________________________________//

int
execution_monitor::execute( bool catch_system_errors, int timeout )
{
    using unit_test::const_string;

#if defined(BOOST_MS_STRCTURED_EXCEPTION_HANDLING) && !defined(__BORLANDC__)
    if( catch_system_errors )
        _set_se_translator( detail::ms_se_trans_func );
    else
        _set_se_translator( detail::ms_se_forward_func );
#endif

#if defined(BOOST_MS_CRT_DEBUG_HOOK)
    if( catch_system_errors )
        _CrtSetReportHook( &detail::assert_reporting_function );
#endif

    try {
        return detail::catch_signals( *this, catch_system_errors, timeout );
    }

    //  Catch-clause reference arguments are a bit different from function
    //  arguments (ISO 15.3 paragraphs 18 & 19).  Apparently const isn't
    //  required.  Programmers ask for const anyhow, so we supply it.  That's
    //  easier than answering questions about non-const usage.

    catch( char const* ex )
      { detail::report_error( execution_exception::cpp_exception_error, "C string: ", ex ); }
    catch( std::string const& ex )
    { detail::report_error( execution_exception::cpp_exception_error, "std::string: ", ex.c_str() ); }

    //  std:: exceptions

    catch( std::bad_alloc const& ex )
      { detail::report_error( execution_exception::cpp_exception_error, "std::bad_alloc: ", ex.what() ); }

#if !defined(__BORLANDC__) || __BORLANDC__ > 0x0551
    catch( std::bad_cast const& ex )
      { detail::report_error( execution_exception::cpp_exception_error, "std::bad_cast: ", ex.what() ); }
    catch( std::bad_typeid const& ex )
      { detail::report_error( execution_exception::cpp_exception_error, "std::bad_typeid: ", ex.what() ); }
#else
    catch( std::bad_cast const& ex )
      { detail::report_error( execution_exception::cpp_exception_error, "std::bad_cast" ); }
    catch( std::bad_typeid const& ex )
      { detail::report_error( execution_exception::cpp_exception_error, "std::bad_typeid" ); }
#endif

    catch( std::bad_exception const& ex )
      { detail::report_error( execution_exception::cpp_exception_error, "std::bad_exception: ", ex.what() ); }
    catch( std::domain_error const& ex )
      { detail::report_error( execution_exception::cpp_exception_error, "std::domain_error: ", ex.what() ); }
    catch( std::invalid_argument const& ex )
      { detail::report_error( execution_exception::cpp_exception_error, "std::invalid_argument: ", ex.what() ); }
    catch( std::length_error const& ex )
      { detail::report_error( execution_exception::cpp_exception_error, "std::length_error: ", ex.what() ); }
    catch( std::out_of_range const& ex )
      { detail::report_error( execution_exception::cpp_exception_error, "std::out_of_range: ", ex.what() ); }
    catch( std::range_error const& ex )
      { detail::report_error( execution_exception::cpp_exception_error, "std::range_error: ", ex.what() ); }
    catch( std::overflow_error const& ex )
      { detail::report_error( execution_exception::cpp_exception_error, "std::overflow_error: ", ex.what() ); }
    catch( std::underflow_error const& ex )
      { detail::report_error( execution_exception::cpp_exception_error, "std::underflow_error: ", ex.what() ); }
    catch( std::logic_error const& ex )
      { detail::report_error( execution_exception::cpp_exception_error, "std::logic_error: ", ex.what() ); }
    catch( std::runtime_error const& ex )
      { detail::report_error( execution_exception::cpp_exception_error, "std::runtime_error: ", ex.what() ); }
    catch( std::exception const& ex )
      { detail::report_error( execution_exception::cpp_exception_error, "std::exception: ", ex.what() ); }

#if   defined(BOOST_MS_STRCTURED_EXCEPTION_HANDLING)
    catch( detail::ms_se_exception const& ex )
      { detail::report_ms_se_error( ex.id() ); }
#elif defined(BOOST_SIGACTION_BASED_SIGNAL_HANDLING)
    catch( detail::unix_signal_exception const& ex )
      { detail::report_error( ex.error_code(), ex.error_message() ); }
#endif  // BOOST_SIGACTION_BASED_SIGNAL_HANDLING

    catch( execution_exception const& ) { throw; }

    catch( ... )
      { detail::report_error( execution_exception::cpp_exception_error, "unknown type" ); }

    return 0;  // never reached; supplied to quiet compiler warnings
} // execute

//____________________________________________________________________________//

namespace detail {

#if defined(BOOST_SIGACTION_BASED_SIGNAL_HANDLING)

// ************************************************************************** //
// **************          boost::detail::signal_handler       ************** //
// ************************************************************************** //

class signal_handler {
public:
    // Constructor
    explicit signal_handler( bool catch_system_errors, int timeout );

    // Destructor
    ~signal_handler();

    // access methods
    static sigjmp_buf&      jump_buffer()
    {
        assert( s_active_handler );

        return s_active_handler->m_sigjmp_buf;
    }

private:
    // Data members
    struct sigaction        m_same_action_for_all_signals;
    struct sigaction        m_old_SIGFPE_action;
    struct sigaction        m_old_SIGTRAP_action;
    struct sigaction        m_old_SIGSEGV_action;
    struct sigaction        m_old_SIGBUS_action;
    struct sigaction        m_old_SIGABRT_action;
    struct sigaction        m_old_SIGALRM_action;

    sigjmp_buf              m_sigjmp_buf;

    signal_handler*         m_prev_handler;
    static signal_handler*  s_active_handler;

    bool                    m_catch_system_errors;
    bool                    m_set_timeout;
};

signal_handler* signal_handler::s_active_handler = NULL; //!! need to be placed in thread specific storage

//____________________________________________________________________________//

extern "C" {

static void execution_monitor_signal_handler( int sig )
{
    siglongjmp( signal_handler::jump_buffer(), sig );
}

}

//____________________________________________________________________________//

signal_handler::signal_handler( bool catch_system_errors, int timeout )
: m_prev_handler( s_active_handler ),
  m_catch_system_errors( catch_system_errors ),
  m_set_timeout( timeout > 0 )
{
    s_active_handler = this;

    if( m_catch_system_errors || m_set_timeout ) {
        m_same_action_for_all_signals.sa_flags   = 0;
        m_same_action_for_all_signals.sa_handler = &execution_monitor_signal_handler;
        sigemptyset( &m_same_action_for_all_signals.sa_mask );
    }

    if( m_catch_system_errors ) {
        sigaction( SIGFPE , &m_same_action_for_all_signals, &m_old_SIGFPE_action  );
        sigaction( SIGTRAP, &m_same_action_for_all_signals, &m_old_SIGTRAP_action );
        sigaction( SIGSEGV, &m_same_action_for_all_signals, &m_old_SIGSEGV_action );
        sigaction( SIGBUS , &m_same_action_for_all_signals, &m_old_SIGBUS_action  );
        sigaction( SIGABRT, &m_same_action_for_all_signals, &m_old_SIGABRT_action  );
    }

    if( m_set_timeout ) {
        sigaction( SIGALRM , &m_same_action_for_all_signals, &m_old_SIGALRM_action );
        alarm( timeout );
    }
}

//____________________________________________________________________________//

signal_handler::~signal_handler()
{
    typedef struct sigaction* sigaction_ptr;

    assert( s_active_handler == this );

    if( m_set_timeout ) {
        alarm( 0 );
        sigaction( SIGALRM, &m_old_SIGALRM_action, sigaction_ptr() );
    }

    if( m_catch_system_errors ) {
        sigaction( SIGFPE , &m_old_SIGFPE_action , sigaction_ptr() );
        sigaction( SIGTRAP, &m_old_SIGTRAP_action, sigaction_ptr() );
        sigaction( SIGSEGV, &m_old_SIGSEGV_action, sigaction_ptr() );
        sigaction( SIGBUS , &m_old_SIGBUS_action , sigaction_ptr() );
        sigaction( SIGABRT, &m_old_SIGABRT_action, sigaction_ptr() );
    }

    s_active_handler = m_prev_handler;
}

//____________________________________________________________________________//

// ************************************************************************** //
// **************          boost::detail::catch_signals        ************** //
// ************************************************************************** //

int catch_signals( execution_monitor & exmon, bool catch_system_errors, int timeout )
{
    signal_handler                  local_signal_handler( catch_system_errors, timeout );
    int                             result = 0;
    execution_exception::error_code ec     = execution_exception::no_error;
    const_string                    em;

    volatile int sigtype = sigsetjmp( signal_handler::jump_buffer(), 1 );
    if( sigtype == 0 ) {
        result = exmon.run_function();
    }
    else {
        switch(sigtype) {
        case SIGALRM:
            ec = execution_exception::timeout_error;
            em = BOOST_TEST_L( "signal: SIGALRM (timeout while executing function)" );
            break;
        case SIGTRAP:
            ec = execution_exception::system_error;
            em = BOOST_TEST_L( "signal: SIGTRAP (perhaps integer divide by zero)" );
            break;
        case SIGFPE:
            ec = execution_exception::system_error;
            em = BOOST_TEST_L( "signal: SIGFPE (arithmetic exception)" );
            break;
        case SIGABRT:
            ec = execution_exception::system_error;
            em = BOOST_TEST_L( "signal: SIGABRT (application abort requested)" );
            break;
        case SIGSEGV:
        case SIGBUS:
            ec = execution_exception::system_fatal_error;
            em = BOOST_TEST_L( "signal: memory access violation" );
            break;
        default:
            ec = execution_exception::system_error;
            em = BOOST_TEST_L( "signal: unrecognized signal" );
        }
    }

    if( ec != execution_exception::no_error ) {
        throw unix_signal_exception( ec, em );
    }

    return result;
}  // unix catch_signals

//____________________________________________________________________________//

#elif (defined(__BORLANDC__) && defined(_Windows) && !defined(BOOST_DISABLE_WIN32))

// this works for Borland but not other Win32 compilers (which trap too many cases)
int catch_signals( execution_monitor & exmon, bool catch_system_errors, int )
{
    int result;

    if( catch_system_errors ) {
        __try { result = exmon.run_function(); }

        __except (1)
        {
            throw ms_se_exception( GetExceptionCode() );
        }
    }
    else {
        result = exmon.run_function();
    }
    return result;
}

#else  // default signal handler

int catch_signals( execution_monitor& exmon, bool, int )
{
    return exmon.run_function();
}

#endif  // choose signal handler

// ************************************************************************** //
// **************   Microsoft structured exception handling    ************** //
// ************************************************************************** //

#if defined(BOOST_MS_STRCTURED_EXCEPTION_HANDLING)

void
ms_se_trans_func( unsigned int id, _EXCEPTION_POINTERS* /* exps */ )
{
    throw ms_se_exception( id );
}

//____________________________________________________________________________//

void
ms_se_forward_func( unsigned int /* id */, _EXCEPTION_POINTERS* /* exps */ )
{
    throw;
}

//____________________________________________________________________________//

void
report_ms_se_error( unsigned int id )
{
    switch( id ) {
        // cases classified as fatal_system_error
    case EXCEPTION_ACCESS_VIOLATION:
        detail::report_error( execution_exception::system_fatal_error, "memory access violation" );
        break;

    case EXCEPTION_ILLEGAL_INSTRUCTION:
        detail::report_error( execution_exception::system_fatal_error, "illegal instruction" );
        break;

    case EXCEPTION_PRIV_INSTRUCTION:
        detail::report_error( execution_exception::system_fatal_error, "privileged instruction" );
        break;

    case EXCEPTION_IN_PAGE_ERROR:
        detail::report_error( execution_exception::system_fatal_error, "memory page error" );
        break;

    case EXCEPTION_STACK_OVERFLOW:
        detail::report_error( execution_exception::system_fatal_error, "stack overflow" );
        break;

        // cases classified as (non-fatal) system_trap
    case EXCEPTION_DATATYPE_MISALIGNMENT:
        detail::report_error( execution_exception::system_error, "data misalignment" );
        break;

    case EXCEPTION_INT_DIVIDE_BY_ZERO:
        detail::report_error( execution_exception::system_error, "integer divide by zero" );
        break;

    case EXCEPTION_INT_OVERFLOW:
        detail::report_error( execution_exception::system_error, "integer overflow" );
        break;

    case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
        detail::report_error( execution_exception::system_error, "array bounds exceeded" );
        break;

    case EXCEPTION_FLT_DIVIDE_BY_ZERO:
        detail::report_error( execution_exception::system_error, "floating point divide by zero" );
        break;

    case EXCEPTION_FLT_STACK_CHECK:
        detail::report_error( execution_exception::system_error, "floating point stack check" );
        break;

    case EXCEPTION_FLT_DENORMAL_OPERAND:
    case EXCEPTION_FLT_INEXACT_RESULT:
    case EXCEPTION_FLT_INVALID_OPERATION:
    case EXCEPTION_FLT_OVERFLOW:
    case EXCEPTION_FLT_UNDERFLOW:
        detail::report_error( execution_exception::system_error, "floating point error" );
        break;

    default:
        detail::report_error( execution_exception::system_error, "unrecognized exception or signal" );
        break;
    }  // switch
}  // report_ms_se_error

//____________________________________________________________________________//

#endif  // Microsoft structured exception handling

// ************************************************************************** //
// **************                  report_error                ************** //
// ************************************************************************** //

static void report_error( execution_exception::error_code ec, const_string msg1, const_string msg2 )
{
    static char buf[REPORT_ERROR_BUFFER_SIZE];

    buf[0] = '\0';

    std::strncat( buf, msg1.begin(), sizeof(buf)-1 );
    std::strncat( buf, msg2.begin(), sizeof(buf) - msg1.size() - 1 );

    throw execution_exception( ec, buf );
}

//____________________________________________________________________________//

} // namespace detail

} // namespace boost

// ***************************************************************************
//  Revision History :
//
//  $Log$
//  Revision 1.33  2004/06/07 07:34:22  rogeeff
//  detail namespace renamed
//
//  Revision 1.32  2004/05/21 06:26:09  rogeeff
//  licence update
//
//  Revision 1.31  2004/05/11 11:04:44  rogeeff
//  basic_cstring introduced and used everywhere
//  class properties reworked
//  namespace names shortened
//
//  Revision 1.30  2003/12/20 11:27:28  johnmaddock
//  Added fixes for Borland C++ 6.0 compiler (With EDG frontend).
//
//  Revision 1.29  2003/12/01 00:42:37  rogeeff
//  prerelease cleaning
//

// ***************************************************************************

// EOF

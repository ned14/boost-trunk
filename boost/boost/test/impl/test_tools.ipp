//  (C) Copyright Gennadiy Rozental 2005.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.
//
//  File        : $RCSfile$
//
//  Version     : $Revision$
//
//  Description : supplies offline implementation for the Test Tools
// ***************************************************************************

#ifndef BOOST_TEST_TOOLS_IPP_012205GER
#define BOOST_TEST_TOOLS_IPP_012205GER

// Boost.Test
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_result.hpp>
#include <boost/test/unit_test_log.hpp>
#include <boost/test/output_test_stream.hpp>

// Boost
#include <boost/config.hpp>

// STL
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cctype>
#include <cwchar>
#ifdef BOOST_STANDARD_IOSTREAMS
#include <ios>
#endif
#include <cstdarg>

# ifdef BOOST_NO_STDC_NAMESPACE
namespace std { using ::strcmp; using ::strlen; using ::isprint; using ::va_list; }
#if !defined( BOOST_NO_CWCHAR )
namespace std { using ::wcscmp; }
#endif
# endif

#include <boost/test/detail/suppress_warnings.hpp>

namespace boost {

namespace test_tools {

namespace tt_detail {

// ************************************************************************** //
// **************            TOOL BOX Implementation           ************** //
// ************************************************************************** //

void
check_impl( predicate_result const& pr, wrap_stringstream& check_descr,
            const_string file_name, std::size_t line_num,
            tool_level tl, check_type ct,
            std::size_t num_of_args, ... )
{
    using namespace boost::unit_test;

    if( !!pr )
        tl = PASS;

    unit_test::log_level    ll;
    char const*             prefix;
    char const*             suffix;

    switch( tl ) {
    case PASS:
        unit_test_result::instance().inc_passed_assertions();

        ll      = log_successful_tests;
        prefix  = "test ";
        suffix  = " passed";
        break;
    case WARN:
        ll      = log_warnings;
        prefix  = "condition ";
        suffix  = " is not satisfied";
        break;
    case CHECK:
        unit_test_result::instance().inc_failed_assertions();

        ll      = log_all_errors;
        prefix  = "test ";
        suffix  = " failed";
        break;
    case REQUIRE:
        unit_test_result::instance().inc_failed_assertions();

        ll      = log_fatal_errors;
        prefix  = "critical test ";
        suffix  = " failed";
        break;
    default:
        return;
    }

    switch( ct ) {
    case CHECK_PRED:
        unit_test_log << begin() << file( file_name ) << line( line_num ) << ll << prefix << check_descr.str() << suffix;
        
        if( !pr.has_empty_message() )
            unit_test_log << ". " << pr.message();
        
        unit_test_log << end();
        break;
    case CHECK_MSG:
        unit_test_log << begin() << file( file_name ) << line( line_num ) << ll << check_descr.str();
        
        if( !pr.has_empty_message() ) {
            unit_test_log << ". " << pr.message();
        }

        unit_test_log << end();
        break;
    case MSG_ONLY:
        unit_test_log << begin() << file( file_name ) << line( line_num ) << log_messages << check_descr.str() << end();
        break;
    case SET_CHECKPOINT:
        unit_test_log << begin() << file( file_name ) << line( line_num ) << log_test_suites 
                      << checkpoint( check_descr.str() ) << end();
        break;
    case CHECK_EQUAL: {
        std::va_list args;

        va_start( args, num_of_args );
        char const* arg1_descr  = va_arg( args, char const* );
        char const* arg1_val    = va_arg( args, char const* );
        char const* arg2_descr  = va_arg( args, char const* );
        char const* arg2_val    = va_arg( args, char const* );

        unit_test_log << begin() << file( file_name ) << line( line_num ) << ll 
                      << prefix << arg1_descr << " == " << arg2_descr << suffix;

        if( tl != PASS )
            unit_test_log << " [" << arg1_val << " != " << arg2_val << "]" ;

        va_end( args );
        
        if( !pr.has_empty_message() )
            unit_test_log << ". " << pr.message();

        unit_test_log << end();
        break;
    }
    case CHECK_CLOSE: {
        std::va_list args;

        va_start( args, num_of_args );
        char const* arg1_descr  = va_arg( args, char const* );
        char const* arg1_val    = va_arg( args, char const* );
        char const* arg2_descr  = va_arg( args, char const* );
        char const* arg2_val    = va_arg( args, char const* );
           /* toler_descr = */    va_arg( args, char const* );
        char const* toler_val   = va_arg( args, char const* );

        unit_test_log << begin() << file( file_name ) << line( line_num ) << ll;

        unit_test_log << "difference between " << arg1_descr << "{" << arg1_val << "}" 
                      << " and "               << arg2_descr << "{" << arg2_val << "}"
                      << ( tl == PASS ? " doesn't exceed " : " exceeds " )
                      << toler_val << "%",

        va_end( args );
        
        if( !pr.has_empty_message() )
            unit_test_log << ". " << pr.message();

        unit_test_log << end();
        break;
    }
    case CHECK_PRED_WITH_ARGS: {
        unit_test_log << begin() << file( file_name ) << line( line_num ) << ll << prefix << check_descr.str();

        // print predicate call description
        {
            std::va_list args;
            va_start( args, num_of_args );

            unit_test_log << "( ";
            for( std::size_t i = 0; i < num_of_args; ++i ) {
                unit_test_log << va_arg( args, char const* );
                va_arg( args, char const* ); // skip argument value;
                
                if( i != num_of_args-1 )
                    unit_test_log << ", ";
            }
            unit_test_log << " )" << suffix;
            va_end( args );
        }
                        
        if( tl != PASS ) {
            std::va_list args;
            va_start( args, num_of_args );

            unit_test_log << " for ( ";
            for( std::size_t i = 0; i < num_of_args; ++i ) {
                va_arg( args, char const* ); // skip argument description;            
                unit_test_log << va_arg( args, char const* );
                
                if( i != num_of_args-1 )
                    unit_test_log << ", ";
            }
            unit_test_log << " )";
            va_end( args );
        }
       
        if( !pr.has_empty_message() )
            unit_test_log << ". " << pr.message();

        unit_test_log << end();
        break;
    }
    case CHECK_EQUAL_COLL: {
        std::va_list args;

        va_start( args, num_of_args );
        char const* left_begin_descr    = va_arg( args, char const* );
        char const* left_end_descr      = va_arg( args, char const* );
        char const* right_begin_descr   = va_arg( args, char const* );
        char const* right_end_descr     = va_arg( args, char const* );

        unit_test_log << begin() << file( file_name ) << line( line_num ) << ll 
                      << prefix 
                      << "{ " << left_begin_descr  << ", " << left_end_descr  << " } == { " 
                              << right_begin_descr << ", " << right_end_descr << " }"
                      << suffix;

        va_end( args );
        
        if( !pr.has_empty_message() )
            unit_test_log << ". " << pr.message();

        unit_test_log << end();
        break;
    }
    case CHECK_BITWISE_EQUAL: {
        std::va_list args;

        va_start( args, num_of_args );
        char const* left_descr    = va_arg( args, char const* );
        char const* right_descr   = va_arg( args, char const* );

        unit_test_log << begin() << file( file_name ) << line( line_num ) << ll 
                      << prefix << left_descr  << " =.= " << right_descr << suffix;

        va_end( args );
        
        if( !pr.has_empty_message() )
            unit_test_log << ". " << pr.message();

        unit_test_log << end();
        break;
    }
    }

    if( tl == REQUIRE )
        throw test_tool_failed();
}

//____________________________________________________________________________//

predicate_result
equal_impl( char const* left, char const* right )
{
    return (left && right) ? std::strcmp( left, right ) == 0 : (left == right);
}

//____________________________________________________________________________//

#if !defined( BOOST_NO_CWCHAR )

predicate_result
equal_impl( wchar_t const* left, wchar_t const* right )
{
    return (left && right) ? std::wcscmp( left, right ) == 0 : (left == right);
}

#endif // !defined( BOOST_NO_CWCHAR )

//____________________________________________________________________________//

bool
is_defined_impl( const_string symbol_name, const_string symbol_value )
{
    symbol_value.trim_left( 2 );
    return symbol_name != symbol_value;
}

//____________________________________________________________________________//

// ************************************************************************** //
// **************               log print helper               ************** //
// ************************************************************************** //

void
print_log_value<char>::operator()( std::ostream& ostr, char t )
{
    if( (std::isprint)( t ) )
        ostr << '\'' << t << '\'';
    else
        ostr << std::hex
        // showbase is only available for new style streams:
#ifndef BOOST_NO_STD_LOCALE
        << std::showbase
#else
        << "0x"
#endif
        << (int)t;
}

//____________________________________________________________________________//

void
print_log_value<unsigned char>::operator()( std::ostream& ostr, unsigned char t )
{
    ostr << std::hex
        // showbase is only available for new style streams:
#ifndef BOOST_NO_STD_LOCALE
        << std::showbase
#else
        << "0x"
#endif
       << (int)t;
}

//____________________________________________________________________________//

void
print_log_value<char const*>::operator()( std::ostream& ostr, char const* t )
{
    ostr << ( t ? t : "null string" );
}

//____________________________________________________________________________//

void
print_log_value<wchar_t const*>::operator()( std::ostream& ostr, wchar_t const* t )
{
    ostr << ( t ? t : L"null string" );
}

//____________________________________________________________________________//

} // namespace tt_detail

// ************************************************************************** //
// **************               output_test_stream             ************** //
// ************************************************************************** //

struct output_test_stream::Impl
{
    std::fstream    m_pattern_to_match_or_save;
    bool            m_match_or_save;
    std::string     m_synced_string;

    char            get_char()
    {
        char res;
        do {
            m_pattern_to_match_or_save.get( res );
        } while( res == '\r'                        &&
                 !m_pattern_to_match_or_save.fail() &&
                 !m_pattern_to_match_or_save.eof() );

        return res;
    }

    void            check_and_fill( predicate_result& res )
    {
        if( !res.p_predicate_value )
            res.message() << "Output content: \"" << m_synced_string << '\"';
    }
};

//____________________________________________________________________________//

output_test_stream::output_test_stream( const_string pattern_file_name, bool match_or_save )
: m_pimpl( new Impl )
{
    if( !pattern_file_name.is_empty() )
        m_pimpl->m_pattern_to_match_or_save.open( pattern_file_name.begin(), match_or_save ? std::ios::in : std::ios::out );

    m_pimpl->m_match_or_save = match_or_save;
}

//____________________________________________________________________________//

output_test_stream::~output_test_stream()
{
}

//____________________________________________________________________________//

predicate_result
output_test_stream::is_empty( bool flush_stream )
{
    sync();

    result_type res( m_pimpl->m_synced_string.empty() );

    m_pimpl->check_and_fill( res );

    if( flush_stream )
        flush();

    return res;
}

//____________________________________________________________________________//

predicate_result
output_test_stream::check_length( std::size_t length_, bool flush_stream )
{
    sync();

    result_type res( m_pimpl->m_synced_string.length() == length_ );

    m_pimpl->check_and_fill( res );

    if( flush_stream )
        flush();

    return res;
}

//____________________________________________________________________________//

predicate_result
output_test_stream::is_equal( const_string arg, bool flush_stream )
{
    sync();

    result_type res( const_string( m_pimpl->m_synced_string ) == arg );

    m_pimpl->check_and_fill( res );

    if( flush_stream )
        flush();

    return res;
}

//____________________________________________________________________________//

predicate_result
output_test_stream::match_pattern( bool flush_stream )
{
    sync();

    result_type result( true );

    if( !m_pimpl->m_pattern_to_match_or_save.is_open() ) {
        result = false;
        result.message() << "Couldn't open pattern file for "
            << ( m_pimpl->m_match_or_save ? "reading" : "writing");
    }
    else {
        if( m_pimpl->m_match_or_save ) {
            for ( std::string::size_type i = 0; i < m_pimpl->m_synced_string.length(); ++i ) {
                char c = m_pimpl->get_char();

                result = !m_pimpl->m_pattern_to_match_or_save.fail() &&
                         !m_pimpl->m_pattern_to_match_or_save.eof() &&
                         (m_pimpl->m_synced_string[i] == c);

                if( !result ) {
                    std::string::size_type suffix_size  = (std::min)( m_pimpl->m_synced_string.length() - i,
                                                                    static_cast<std::string::size_type>(5) );

                    // try to log area around the mismatch
                    result.message() << "Mismatch at position " << i << '\n'
                        << "..." << m_pimpl->m_synced_string.substr( i, suffix_size ) << "..." << '\n'
                        << "..." << c;

                    std::string::size_type counter = suffix_size;
                    while( --counter ) {
                        char c = m_pimpl->get_char();

                        if( m_pimpl->m_pattern_to_match_or_save.fail() ||
                            m_pimpl->m_pattern_to_match_or_save.eof() )
                            break;

                        result.message() << c;
                    }

                    result.message() << "...";

                    // skip rest of the bytes. May help for further matching
                    m_pimpl->m_pattern_to_match_or_save.ignore( m_pimpl->m_synced_string.length() - i - suffix_size);
                    break;
                }
            }
        }
        else {
            m_pimpl->m_pattern_to_match_or_save.write( m_pimpl->m_synced_string.c_str(),
                                                       static_cast<std::streamsize>( m_pimpl->m_synced_string.length() ) );
            m_pimpl->m_pattern_to_match_or_save.flush();
        }
    }

    if( flush_stream )
        flush();

    return result;
}

//____________________________________________________________________________//

void
output_test_stream::flush()
{
    m_pimpl->m_synced_string.erase();

#ifndef BOOST_NO_STRINGSTREAM
    str( std::string() );
#else
    seekp( 0, std::ios::beg );
#endif
}

//____________________________________________________________________________//

std::size_t
output_test_stream::length()
{
    sync();

    return m_pimpl->m_synced_string.length();
}

//____________________________________________________________________________//

void
output_test_stream::sync()
{
#ifdef BOOST_NO_STRINGSTREAM
    m_pimpl->m_synced_string.assign( str(), pcount() );
    freeze( false );
#else
    m_pimpl->m_synced_string = str();
#endif
}

//____________________________________________________________________________//

} // namespace test_tools

} // namespace boost

// ***************************************************************************
//  Revision History :
//
//  $Log$
//  Revision 1.3  2005/02/01 06:40:07  rogeeff
//  copyright update
//  old log entries removed
//  minor stilistic changes
//  depricated tools removed
//
//  Revision 1.2  2005/01/30 03:18:27  rogeeff
//  test tools implementation completely reworked. All tools inplemented through single vararg function
//
//  Revision 1.1  2005/01/22 19:22:12  rogeeff
//  implementation moved into headers section to eliminate dependency of included/minimal component on src directory
//
//  Revision 1.43  2005/01/19 06:40:05  vawjr
//  deleted redundant \r in many \r\r\n sequences of the source.  VC8.0 doesn't like them
//
//  Revision 1.42  2005/01/18 08:30:08  rogeeff
//  unit_test_log rework:
//     eliminated need for ::instance()
//     eliminated need for << end and ...END macro
//     straitend interface between log and formatters
//     change compiler like formatter name
//     minimized unit_test_log interface and reworked to use explicit calls
//
// ***************************************************************************

#endif // BOOST_TEST_TOOLS_IPP_012205GER

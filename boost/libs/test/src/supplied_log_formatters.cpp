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
//  Description : implemets Unit Test Log formatters
// ***************************************************************************

// Boost.Test
#include <boost/test/detail/supplied_log_formatters.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <boost/test/unit_test_result.hpp>

// BOOST
#include <boost/version.hpp>

// STL
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>

namespace boost {

namespace unit_test {

namespace ut_detail {

// ************************************************************************** //
// **************           msvc65_like_log_formatter          ************** //
// ************************************************************************** //

msvc65_like_log_formatter::msvc65_like_log_formatter( unit_test_log const& log ) 
: unit_test_log_formatter( log )
{}

//____________________________________________________________________________//

void
msvc65_like_log_formatter::start_log( std::ostream& output, bool log_build_info )
{
    if( log_build_info )
        output  << "Platform: " << BOOST_PLATFORM            << '\n'
                << "Compiler: " << BOOST_COMPILER            << '\n'
                << "STL     : " << BOOST_STDLIB              << '\n'
                << "Boost   : " << BOOST_VERSION/100000      << "."
                                << BOOST_VERSION/100 % 1000  << "."
                                << BOOST_VERSION % 100       << '\n';
}

//____________________________________________________________________________//

void
msvc65_like_log_formatter::log_header( std::ostream& output, unit_test_counter test_cases_amount )
{
    output  << "Running " << test_cases_amount << " test "
        << (test_cases_amount > 1 ? "cases" : "case") << "...\n";
}

//____________________________________________________________________________//

void
msvc65_like_log_formatter::finish_log( std::ostream& /* output */ )
{
}

//____________________________________________________________________________//

void
msvc65_like_log_formatter::track_test_case_scope( std::ostream& output, test_case const& tc, bool in_out )
{
    output << (in_out ? "Entering" : "Leaving")
        << " test " << ( tc.p_type ? "case" : "suite" )
        << " \"" << tc.p_name << "\"";
}

//____________________________________________________________________________//

void
msvc65_like_log_formatter::log_exception( std::ostream& output, const_string test_case_name, const_string explanation )
{
    output << "Exception in \"" << test_case_name << "\": " << explanation;

    log_checkpoint_data const& chpd = checkpoint_data();

    if( !chpd.m_message.empty() ) {
        output << '\n';
        print_prefix( output, chpd.m_file, chpd.m_line );
        output << "last checkpoint: " << chpd.m_message;
    }
}

//____________________________________________________________________________//

void
msvc65_like_log_formatter::begin_log_entry( std::ostream& output, log_entry_types let )
{
    switch( let ) {
        case BOOST_UTL_ET_INFO:
            print_prefix( output, entry_data().m_file, entry_data().m_line );
            output << "info: ";
            break;
        case BOOST_UTL_ET_MESSAGE:
            break;
        case BOOST_UTL_ET_WARNING:
            print_prefix( output, entry_data().m_file, entry_data().m_line );
            output << "warning in \"" << unit_test_result::instance().test_case_name() << "\": ";
            break;
        case BOOST_UTL_ET_ERROR:
            print_prefix( output, entry_data().m_file, entry_data().m_line );
            output << "error in \"" << unit_test_result::instance().test_case_name() << "\": ";
            break;
        case BOOST_UTL_ET_FATAL_ERROR:
            print_prefix( output, entry_data().m_file, entry_data().m_line );
            output << "fatal error in \"" << unit_test_result::instance().test_case_name() << "\": ";
            break;
    }
}

//____________________________________________________________________________//

void
msvc65_like_log_formatter::log_entry_value( std::ostream& output, const_string value )
{
    output << value;
}

//____________________________________________________________________________//

void
msvc65_like_log_formatter::end_log_entry( std::ostream& /* output */ )
{
}

//____________________________________________________________________________//

void
msvc65_like_log_formatter::print_prefix( std::ostream& output, const_string file, std::size_t line )
{
    output << file << '(' << line << "): ";
}

//____________________________________________________________________________//

// ************************************************************************** //
// **************               xml_log_formatter              ************** //
// ************************************************************************** //

xml_log_formatter::xml_log_formatter( unit_test_log const& log ) 
: unit_test_log_formatter( log ), m_indent( 0 )
{
}

//____________________________________________________________________________//

void
xml_log_formatter::start_log( std::ostream& output, bool log_build_info )
{
    output  << "<TestLog";

    if( log_build_info )
        output  << " platform=\"" << BOOST_PLATFORM            << '\"'
                << " compiler=\"" << BOOST_COMPILER            << '\"'
                << " stl=\""      << BOOST_STDLIB              << '\"'
                << " boost=\""    << BOOST_VERSION/100000      << "."
                                  << BOOST_VERSION/100 % 1000  << "."
                                  << BOOST_VERSION % 100       << '\"';

    output  << ">\n";
}

//____________________________________________________________________________//

void
xml_log_formatter::log_header( std::ostream& /* output */, unit_test_counter /* test_cases_amount */ )
{
}

//____________________________________________________________________________//

void
xml_log_formatter::finish_log( std::ostream& output )
{
    output  << "</TestLog>\n";
}

//____________________________________________________________________________//

void
xml_log_formatter::track_test_case_scope( std::ostream& output, test_case const& tc, bool in_out )
{
    if( !in_out )
        m_indent -= 2;

    print_indent( output );

    output << (in_out ? "<" : "</")
        << ( tc.p_type ? "TestCase" : "TestSuite" );

    if( in_out )
        output << " name=\"" << tc.p_name << "\"";

    output << ">";

    if( in_out )
        m_indent += 2;
}

//____________________________________________________________________________//

void
xml_log_formatter::log_exception( std::ostream& output, const_string test_case_name, const_string explanation )
{
    print_indent( output );
    output << "<Exception name=\"" << test_case_name << "\">\n";
    
    m_indent += 2;

    print_indent( output );
    output << explanation << '\n';

    log_checkpoint_data const& chpd = checkpoint_data();

    if( !chpd.m_message.empty() ) {
        print_indent( output );
        output << "<LastCheckpoint file=\"" << chpd.m_file << "\""
            << " line=\"" << chpd.m_line << "\">\n";

        m_indent += 2;

        print_indent( output );
        output << chpd.m_message << "\n";

        m_indent -= 2;

        print_indent( output );
        output << "</LastCheckpoint>\n";
    }

    m_indent -= 2;
    print_indent( output );

    output << "</Exception>";
}

//____________________________________________________________________________//

void
xml_log_formatter::begin_log_entry( std::ostream& output, log_entry_types let )
{
    static literal_string xml_tags[] = { "Info", "Message", "Warning", "Error", "FatalError" };

    print_indent( output );

    m_curr_tag = xml_tags[let];
    output << '<' << m_curr_tag
        << " file=\"" << entry_data().m_file<< '\"'
        << " line=\"" << entry_data().m_line << '\"'
        << ">\n";

    m_indent += 2;
    print_indent( output );
}

//____________________________________________________________________________//

void
xml_log_formatter::log_entry_value( std::ostream& output, const_string value )
{
    output << value;
}

//____________________________________________________________________________//

void
xml_log_formatter::end_log_entry( std::ostream& output )
{
    if( m_curr_tag.is_empty() )
        return;

    output << '\n';

    m_indent -= 2;
    print_indent( output );

    output << "</" << m_curr_tag << ">";

    m_curr_tag.clear();
}

//____________________________________________________________________________//

void
xml_log_formatter::print_indent( std::ostream& output )
{
    output << std::setw( m_indent ) << "";
}

//____________________________________________________________________________//

} // namespace ut_detail

} // namespace unit_test

} // namespace boost

// ***************************************************************************
//  Revision History :
//
//  $Log$
//  Revision 1.10  2004/06/07 07:34:22  rogeeff
//  detail namespace renamed
//
//  Revision 1.9  2004/05/21 06:26:09  rogeeff
//  licence update
//
//  Revision 1.8  2004/05/13 09:04:43  rogeeff
//  added fixed_mapping
//
//  Revision 1.7  2004/05/11 11:04:44  rogeeff
//  basic_cstring introduced and used everywhere
//  class properties reworked
//  namespace names shortened
//
//  Revision 1.6  2003/12/01 00:42:37  rogeeff
//  prerelease cleaning
//

// ***************************************************************************

// EOF

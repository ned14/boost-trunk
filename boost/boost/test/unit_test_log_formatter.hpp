//  (C) Copyright Gennadiy Rozental 2003.
//  See accompanying license for terms and conditions of use.

//  See http://www.boost.org for most recent version including documentation.
//
//  File        : $RCSfile$
//
//  Version     : $Revision$
//
//  Description : 
// ***************************************************************************

#ifndef BOOST_UNIT_TEST_LOG_FORMATTER_HPP
#define BOOST_UNIT_TEST_LOG_FORMATTER_HPP

// Boost.Test
#include <boost/test/detail/unit_test_config.hpp>
#include <boost/test/unit_test_log.hpp>

// BOOST

// STL
#include <iosfwd>
#include <string> // need only forward decl

namespace boost {

namespace unit_test_framework {

// ************************************************************************** //
// **************            unit_test_log_formatter           ************** //
// ************************************************************************** //

class unit_test_log_formatter {
public:
    enum log_entry_types { BOOST_UTL_ET_INFO, 
                           BOOST_UTL_ET_MESSAGE,
                           BOOST_UTL_ET_WARNING,
                           BOOST_UTL_ET_ERROR,
                           BOOST_UTL_ET_FATAL_ERROR };

    // Constructor
    explicit unit_test_log_formatter( unit_test_log const& log )
    : m_log( log ) {}

    // Destructor
    virtual             ~unit_test_log_formatter() {}

    // Formatter interface
    virtual void        start_log( std::ostream& output, bool log_build_info ) = 0;
    virtual void        log_header( std::ostream& output, unit_test_counter test_cases_amount ) = 0;
    virtual void        finish_log( std::ostream& output ) = 0;

    virtual void        track_test_case_scope( std::ostream& output, test_case const& tc, bool in_out ) = 0;
    virtual void        log_exception( std::ostream& output, std::string const& test_case_name, c_string_literal explanation ) = 0;

    virtual void        begin_log_entry( std::ostream& output, log_entry_types let ) = 0;
    virtual void        log_entry_value( std::ostream& output, std::string const& value ) = 0;
    virtual void        end_log_entry( std::ostream& output ) = 0;

protected:
    // Implementation interface
    log_entry_data      const& entry_data() const       { return m_log.entry_data(); }
    log_checkpoint_data const& checkpoint_data() const  { return m_log.checkpoint_data(); }

private:
    // Data members
    unit_test_log const& m_log;
};

} // namespace unit_test_framework

} // namespace boost

// ***************************************************************************
//  Revision History :
//  
//  $Log$
//  Revision 1.2  2003/10/27 07:13:12  rogeeff
//  licence update
//
//  Revision 1.1  2003/07/02 09:15:57  rogeeff
//  move log formatter in public interface
//

// ***************************************************************************

#endif // BOOST_UNIT_TEST_LOG_FORMATTER_HPP


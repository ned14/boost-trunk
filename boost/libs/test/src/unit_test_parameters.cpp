//  (C) Copyright Gennadiy Rozental 2001-2002.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for updates, documentation, and revision history.
//
//  File        : $RCSfile$
//
//  Version     : $Id$
//
//  Description : simple implementation for Unit Test Framework parameter 
//  handling routines. May be rewritten in future to use some kind of 
//  command-line arguments parsing facility and environment variable handling 
//  facility
// ***************************************************************************

// Boost.Test
#include <boost/test/detail/unit_test_parameters.hpp>

//BOOST
#include <boost/config.hpp>           // for broken compiler workarounds
// for strcmp etc:
#include <cstring>
#include <cstdlib>

# ifdef BOOST_NO_STDC_NAMESPACE
namespace std { using ::getenv; using ::strncmp; using ::strcmp; }
# endif

namespace boost {

namespace unit_test_framework {

const struct parameter_names {
    char const* env_name;
    char const* cla_name;
} parameter_cla_names [] = {
    { LOGLEVEL          , "--log_level" },
    { NO_RESULT_CODE    , "--result_code" },
    { RESULT_REPORT     , "--report_level" },
    { TESTS_TO_RUN      , "--run_test" },
    { SAVE_TEST_PATTERN , "--save_pattern" },
    { BUILD_INFO        , "--build_info" },
    { NULL              , NULL }
    
} ;

std::string
retrieve_framework_parameter( char const* parameter_name, int* argc, char** argv )
{
    // first try to find parameter among command line arguments if present
    if( argc != NULL ) {
        // locate corresponding cla name
        parameter_names const* curr = parameter_cla_names;
        while( curr->env_name != NULL && std::strcmp( curr->env_name, parameter_name ) != 0 )
            curr++;

        if( curr->env_name != NULL ) {
            std::string parameter_cla_name = curr->cla_name;
            parameter_cla_name += '=';
            
            for( int i = 1; i < *argc; ++i ) {
                if( std::strncmp( parameter_cla_name.data(), argv[i], parameter_cla_name.length() ) == 0 ) {
                    std::string result = argv[i] + parameter_cla_name.length();
                    
                    for( int j = i; j < *argc; ++j ) {
                        argv[j] = argv[j+1];
                    }
                    --(*argc);
                    
                    return result;
                }
            }
        }
    }

    char const* env_var_value = std::getenv( parameter_name );
    return  env_var_value == NULL ? "" : env_var_value;
}

//____________________________________________________________________________//

} // namespace unit_test_framework

} // namespace boost

// ***************************************************************************
//  Revision History :
//  
//  $Log$
//  Revision 1.5  2002/11/02 20:04:42  rogeeff
//  release 1.29.0 merged into the main trank
//

// ***************************************************************************

// EOF


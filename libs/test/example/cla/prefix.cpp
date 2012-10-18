//  (C) Copyright Gennadiy Rozental 2001-2012.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.

// Boost.Runtime.Param
#include <boost/test/utils/runtime/cla/named_parameter.hpp>
#include <boost/test/utils/runtime/cla/parser.hpp>

namespace rt  = boost::runtime;
namespace cla = boost::runtime::cla;

// STL
#include <iostream>

int main() {
    char* argv[] = { "basic", "/abcd", "25", "-klmn", "abs" };
    int argc = sizeof(argv)/sizeof(char*);

    try {
        cla::parser P;

        P << cla::named_parameter<std::string>( "abcd" ) - ( cla::prefix = "/" )
          << cla::named_parameter<std::string>( "klmn" );

        P.parse( argc, argv );

        std::cout << "abcd = " << P.get<std::string>( "abcd" ) << std::endl;
        std::cout << "klnm = " << P.get<std::string>( "klmn" ) << std::endl;
    }
    catch( rt::logic_error const& ex ) {
        std::cout << "Logic error: " << ex.msg() << std::endl;
        return -1;
    }

    return 0;
}

// EOF

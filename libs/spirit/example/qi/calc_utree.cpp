/*=============================================================================
    Copyright (c) 2001-2010 Hartmut Kaiser
    Copyright (c) 2001-2010 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
///////////////////////////////////////////////////////////////////////////////
//
//  Plain calculator example demonstrating the grammar. The parser is a
//  syntax checker only and does not do any semantic evaluation.
//
//  [ JDG May 10, 2002 ]        spirit1
//  [ JDG March 4, 2007 ]       spirit2
//  [ HK November 30, 2010 ]    spirit2/utree
//
///////////////////////////////////////////////////////////////////////////////

// #define BOOST_SPIRIT_DEBUG

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_utree.hpp>

#include <iostream>
#include <string>

namespace client
{
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    namespace spirit = boost::spirit;

    ///////////////////////////////////////////////////////////////////////////////
    //  Our calculator grammar
    ///////////////////////////////////////////////////////////////////////////////
    template <typename Iterator>
    struct calculator : qi::grammar<Iterator, ascii::space_type, spirit::utree()>
    {
        calculator() : calculator::base_type(expression)
        {
            using qi::uint_;
            using qi::char_;

            expression =
                term
                >> *(   (char_('+') >> term)
                    |   (char_('-') >> term)
                    )
                ;

            term =
                factor
                >> *(   (char_('*') >> factor)
                    |   (char_('/') >> factor)
                    )
                ;

            factor =
                uint_
                |   char_('(') >> expression >> char_(')')
                |   (char_('-') >> factor)
                |   (char_('+') >> factor)
                ;

            BOOST_SPIRIT_DEBUG_NODE(expression);
            BOOST_SPIRIT_DEBUG_NODE(term);
            BOOST_SPIRIT_DEBUG_NODE(factor);
        }

        qi::rule<Iterator, ascii::space_type, spirit::utree()> expression, term, factor;
    };
}

///////////////////////////////////////////////////////////////////////////////
//  Main program
///////////////////////////////////////////////////////////////////////////////
int
main()
{
    std::cout << "/////////////////////////////////////////////////////////\n\n";
    std::cout << "Expression parser...\n\n";
    std::cout << "/////////////////////////////////////////////////////////\n\n";
    std::cout << "Type an expression...or [q or Q] to quit\n\n";

    using boost::spirit::ascii::space;
    using boost::spirit::utree;
    typedef std::string::const_iterator iterator_type;
    typedef client::calculator<iterator_type> calculator;

    calculator calc; // Our grammar

    std::string str;
    while (std::getline(std::cin, str))
    {
        if (str.empty() || str[0] == 'q' || str[0] == 'Q')
            break;

        std::string::const_iterator iter = str.begin();
        std::string::const_iterator end = str.end();
        utree ut;
        bool r = phrase_parse(iter, end, calc, space, ut);

        if (r && iter == end)
        {
            std::cout << "-------------------------\n";
            std::cout << "Parsing succeeded: " << ut << "\n";
            std::cout << "-------------------------\n";
        }
        else
        {
            std::string rest(iter, end);
            std::cout << "-------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "stopped at: \": " << rest << "\"\n";
            std::cout << "-------------------------\n";
        }
    }

    std::cout << "Bye... :-) \n\n";
    return 0;
}



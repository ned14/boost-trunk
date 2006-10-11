/*=============================================================================
    Copyright (c) 2002-2003 Joel de Guzman
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
////////////////////////////////////////////////////////////////////////////
//
//  HTML/XML like tag matching grammar
//  Demonstrates phoenix and dynamic_scopes and parametric parsers
//  This is discussed in the "Dynamic Scopes" chapter in the Spirit User's Guide.
//
//  [ JDG 6/30/2002 ]
//
////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/core.hpp>
#include <boost/spirit/attribute.hpp>
#include <boost/spirit/phoenix/core.hpp>
#include <boost/spirit/phoenix/operator.hpp>
#include <boost/spirit/phoenix/object.hpp>
#include <boost/spirit/phoenix/object.hpp>
#include <boost/spirit/phoenix/object.hpp>
#include <boost/spirit/phoenix/stl.hpp>
#include <iostream>
#include <string>

////////////////////////////////////////////////////////////////////////////
using namespace std;
using namespace boost::spirit;
using namespace boost::phoenix;

////////////////////////////////////////////////////////////////////////////
//
//  HTML/XML like tag matching grammar
//
////////////////////////////////////////////////////////////////////////////
struct tags_dynamic_scope : boost::spirit::dynamic_scope<tags_dynamic_scope, string> 
{
    tags_dynamic_scope() : tag(*this) {}
    member1 tag;
};

struct tags : public grammar<tags> 
{
    template <typename ScannerT>
    struct definition {

        definition(tags const& /*self*/)
        {
            element = start_tag >> *element >> end_tag;

            start_tag =
                    '<'
                >>  lexeme_d
                    [
                        (+alpha_p)
                        [
                            //  construct string from arg1 and arg2 lazily
                            //  and assign to element.tag

                            element.tag = construct<string>(arg1, arg2)
                        ]
                    ]
                >> '>';

            end_tag = "</" >> f_str_p(begin(element.tag), end(element.tag)) >> '>';
        }

        rule<ScannerT, tags_dynamic_scope::context_t> element;
        rule<ScannerT> start_tag, end_tag;

        rule<ScannerT, tags_dynamic_scope::context_t> const&
        start() const { return element; }
    };
};

////////////////////////////////////////////////////////////////////////////
//
//  Main program
//
////////////////////////////////////////////////////////////////////////////
int
main()
{
    cout << "/////////////////////////////////////////////////////////\n\n";
    cout << "\t\tHTML/XML like tag matching parser demo \n\n";
    cout << "/////////////////////////////////////////////////////////\n\n";
    cout << "Type an HTML/XML like nested tag input...or [q or Q] to quit\n\n";
    cout << "Example: <html><head></head><body></body></html>\n\n";

    tags p;    //  Our parser

    string str;
    while (getline(cin, str))
    {
        if (str.empty() || str[0] == 'q' || str[0] == 'Q')
            break;

        parse_info<> info = parse(str.c_str(), p, space_p);

        if (info.full)
        {
            cout << "-------------------------\n";
            cout << "Parsing succeeded\n";
            cout << "-------------------------\n";
        }
        else
        {
            cout << "-------------------------\n";
            cout << "Parsing failed\n";
            cout << "stopped at: \": " << info.stop << "\"\n";
            cout << "-------------------------\n";
        }
    }

    cout << "Bye... :-) \n\n";
    return 0;
}



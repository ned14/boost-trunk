/*=============================================================================
    Spirit v1.6.2
    Copyright (c) 2001-2003 Hartmut Kaiser
    http://spirit.sourceforge.net/

    Permission to copy, use, modify, sell and distribute this software is
    granted provided this copyright notice appears in all copies. This
    software is provided "as is" without express or implied warranty, and
    with no claim as to its suitability for any purpose.
=============================================================================*/
///////////////////////////////////////////////////////////////////////////////
// This sample shows the usage of the list_p utility parser
//  1. parsing a simple ',' delimited list w/o item formatting
//  2. parsing a CSV list (comma separated values - strings, integers or reals)
//  3. parsing a token list (token separated values - strings, integers or
//     reals)
// with an action parser directly attached to the item part of the list_p
// generated parser

#include <string>
#include <iostream>
#include <cassert>

#include <boost/spirit/core.hpp>
#include <boost/spirit/utility/confix.hpp>
#include <boost/spirit/utility/lists.hpp>
#include <boost/spirit/utility/escape_char.hpp>

#include <iostream>
#include <cassert>
#include <string>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
using namespace std;
using namespace boost::spirit;

///////////////////////////////////////////////////////////////////////////////
// actor, attached to the list_p parser
class list_actor
{
public:
    list_actor (std::vector<std::string> &vec_) : vec(vec_) {}

    // The following operator() is called by the action parser generated by
    // attaching this actor to a list_p generated list parser.

    template <typename ActionIterT>
    void operator() (ActionIterT const &first, ActionIterT const &last) const
    {
        vec.push_back(std::string(first, last-first));
    }

private:
    std::vector<std::string> &vec;
};

///////////////////////////////////////////////////////////////////////////////
// main entry point
int main ()
{
    // 1. parsing a simple ',' delimited list w/o item formatting
    char const*                 plist_wo_item = "element1,element2,element3";
    rule<>                      list_wo_item;
    std::vector<std::string>    vec_list;

    list_wo_item =
            list_p[append(vec_list)]
        ;

    parse_info<> result = parse (plist_wo_item, list_wo_item);

    cout << "-----------------------------------------------------------------"
        << endl;

    if (result.hit)
    {
        cout
            << "Parsing simple list" << endl
            << "\t" << plist_wo_item << endl
            << "Parsed successfully!" << endl << endl;

        cout
            << "Actor was called " << (int)vec_list.size()
            << " times: " << endl;

        cout
            << "Results got from the list parser:" << endl;
        for (std::vector<std::string>::iterator it = vec_list.begin();
             it != vec_list.end(); ++it)
        {
            cout << *it << endl;
        }
    }
    else
    {
        cout << "Failed to parse simple list!" << endl;
    }

    cout << endl;

    // 2. parsing a CSV list (comma separated values - strings, integers or
    // reals)
    char const *plist_csv = "\"string\",\"string with an embedded \\\"\","
        "12345,0.12345e4";
    rule<> list_csv, list_csv_item;
    std::vector<std::string> vec_item;

    vec_list.clear();

    list_csv_item =
            confix_p('\"', *c_escape_ch_p, '\"')
        |   longest_d[real_p | int_p]
        ;

    list_csv =
            list_p(
                list_csv_item[append(vec_item)],
                ','
            )[append(vec_list)]
        ;

    result = parse (plist_csv, list_csv);

    cout << "-----------------------------------------------------------------"
        << endl;
    if (result.hit)
    {
        cout
            << "Parsing CSV list (comma separated values) " << endl
            << "\t" << plist_csv << endl
            << "Parsed successfully!" << endl << endl;

        if (result.full)
        {
            cout << "Matched " << (int)vec_list.size() <<
                " list elements (full list): " << endl;
        }
        else
        {
            cout << "Matched " << (int)vec_list.size() <<
                " list elements: " << endl;
        }

        cout << "The list parser matched:" << endl;
        for (std::vector<std::string>::iterator itl = vec_list.begin();
                itl != vec_list.end(); ++itl)
        {
            cout << *itl << endl;
        }

        cout << endl << "Item(s) got directly from the item parser:" << endl;
        for (std::vector<std::string>::iterator it = vec_item.begin();
                it != vec_item.end(); ++it)
        {
            cout << *it << endl;
        }

    }
    else
    {
        cout << "Failed to parse CSV list!" << endl;
    }

    cout << endl;

    // 3. parsing a token list (token separated values - strings, integers or
    // reals) with an action parser directly attached to the item part of the
    // list_p generated parser
    char const *plist_csv_direct = "\"string\"<par>\"string with an embedded "
        "\\\"\"<par>12345<par>0.12345e4";
    rule<> list_csv_direct, list_csv_direct_item;

    vec_list.clear();
    vec_item.clear();

    // Note: the list parser is here generated through the list_p.direct()
    // generator function. This inhibits re-attachment of the item_actor_direct
    // during parser construction (see: comment in utility/lists.hpp)
    list_csv_direct_item =
            confix_p('\"', *c_escape_ch_p, '\"')
        |   longest_d[real_p | int_p]
        ;

    list_csv_direct =
            list_p.direct(
                (*list_csv_direct_item)[list_actor(vec_item)],
                "<par>"
            )[list_actor(vec_list)]
        ;

    result = parse (plist_csv_direct, list_csv_direct);

    cout << "-----------------------------------------------------------------"
        << endl;
    if (result.hit)
    {
        cout
            << "Parsing CSV list (comma separated values)" << endl
            << "The list parser was generated with 'list_p.direct()'" << endl
            << "\t" << plist_csv_direct << endl
            << "Parsed successfully!" << endl << endl;

        if (result.full)
        {
            cout << "Matched " << vec_list.size() <<
                " list elements (full list): " << endl;
        }
        else
        {
            cout << "Matched " << vec_list.size() <<
                " list elements: " << endl;
        }

        cout << "The list parser matched:" << endl;
        for (std::vector<std::string>::iterator itl = vec_list.begin();
                itl != vec_list.end(); ++itl)
        {
            cout << *itl << endl;
        }

        cout << endl << "Items got directly from the item parser:" << endl;
        for (std::vector<std::string>::iterator it = vec_item.begin();
                it != vec_item.end(); ++it)
        {
            cout << *it << endl;
        }

    }
    else
    {
        cout << "Failed to parse CSV list!" << endl;
    }

    cout << endl;

    return 0;
}

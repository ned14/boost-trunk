/*=============================================================================
    Spirit v1.6.1
    Copyright (c) 2001-2003 Daniel Nuffer
    http://spirit.sourceforge.net/

    Permission to copy, use, modify, sell and distribute this software is
    granted provided this copyright notice appears in all copies. This
    software is provided "as is" without express or implied warranty, and
    with no claim as to its suitability for any purpose.
=============================================================================*/
// JDG 4-16-03 Modified from ast_calc.cpp as a test

#include <boost/spirit/core.hpp>
#include <boost/spirit/tree/ast.hpp>
#include <boost/spirit/tree/tree_to_xml.hpp>

#include <iostream>
#include <stack>
#include <functional>
#include <string>
#include <cassert>

using namespace boost::spirit;

////////////////////////////////////////////////////////////////////////////
//
//  Our calculator grammar
//
////////////////////////////////////////////////////////////////////////////
struct calculator : public grammar<calculator>
{
    static const int integerID = 1;
    static const int factorID = 2;
    static const int termID = 3;
    static const int expressionID = 4;

    template <typename ScannerT>
    struct definition
    {
        definition(calculator const& /*self*/)
        {
            //  Start grammar definition
            integer     =   leaf_node_d[real_p]; // we're not really using a real
                                                 // but just for compile checking
                                                 // the AST tree match code...
            factor      =   integer
                        |   inner_node_d[ch_p('(') >> expression >> ch_p(')')]
                        |   (root_node_d[ch_p('-')] >> factor);

            term        =   factor >>
                            *(  (root_node_d[ch_p('*')] >> factor)
                              | (root_node_d[ch_p('/')] >> factor)
                            );

            expression  =   term >>
                            *(  (root_node_d[ch_p('+')] >> term)
                              | (root_node_d[ch_p('-')] >> term)
                            );
            //  End grammar definition
        }

        rule<ScannerT, parser_context, parser_tag<expressionID> >   expression;
        rule<ScannerT, parser_context, parser_tag<termID> >         term;
        rule<ScannerT, parser_context, parser_tag<factorID> >       factor;
        rule<ScannerT, parser_context, parser_tag<integerID> >      integer;

        rule<ScannerT, parser_context, parser_tag<expressionID> > const&
        start() const { return expression; }
    };
};

////////////////////////////////////////////////////////////////////////////
using namespace std;
using namespace boost::spirit;

typedef char const*                         iterator_t;
typedef tree_match<iterator_t>              parse_tree_match_t;
typedef parse_tree_match_t::tree_iterator   iter_t;

////////////////////////////////////////////////////////////////////////////
long evaluate(parse_tree_match_t hit);
long eval_expression(iter_t const& i);

long evaluate(tree_parse_info<> info)
{
    return eval_expression(info.trees.begin());
}

long eval_expression(iter_t const& i)
{
    switch (i->value.id().to_long())
    {
        case calculator::integerID:
        {
            assert(i->children.size() == 0);
            // extract integer (not always delimited by '\0')
            string integer(i->value.begin(), i->value.end());
            return strtol(integer.c_str(), 0, 10);
        }

        case calculator::factorID:
        {
            // factor can only be unary minus
            assert(*i->value.begin() == '-');
            return - eval_expression(i->children.begin());
        }

        case calculator::termID:
        {
            if (*i->value.begin() == '*')
            {
                assert(i->children.size() == 2);
                return eval_expression(i->children.begin()) *
                    eval_expression(i->children.begin()+1);
            }
            else if (*i->value.begin() == '/')
            {
                assert(i->children.size() == 2);
                return eval_expression(i->children.begin()) /
                    eval_expression(i->children.begin()+1);
            }
            else
                assert(0);
        }

        case calculator::expressionID:
        {
            if (*i->value.begin() == '+')
            {
                assert(i->children.size() == 2);
                return eval_expression(i->children.begin()) +
                    eval_expression(i->children.begin()+1);
            }
            else if (*i->value.begin() == '-')
            {
                assert(i->children.size() == 2);
                return eval_expression(i->children.begin()) -
                    eval_expression(i->children.begin()+1);
            }
            else
                assert(0);
        }

        default:
            assert(0); // error
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////
int
parse(char const* str)
{
    calculator calc;
    tree_parse_info<> info = ast_parse(str, calc, space_p);

    if (info.full)
        return evaluate(info);
    else
        return -1;
}

int
main()
{
    assert(parse("12345") == 12345);
    assert(parse("-12345") == -12345);
    assert(parse("1 + 2") == 1 + 2);
    assert(parse("1 * 2") == 1 * 2);
    assert(parse("1/2 + 3/4") == 1/2 + 3/4);
    assert(parse("1 + 2 + 3 + 4") == 1 + 2 + 3 + 4);
    assert(parse("1 * 2 * 3 * 4") == 1 * 2 * 3 * 4);
    assert(parse("(1 + 2) * (3 + 4)") == (1 + 2) * (3 + 4));
    assert(parse("(-1 + 2) * (3 + -4)") == (-1 + 2) * (3 + -4));
    assert(parse("1 + ((6 * 200) - 20) / 6") == 1 + ((6 * 200) - 20) / 6);
    assert(parse("(1 + (2 + (3 + (4 + 5))))") == (1 + (2 + (3 + (4 + 5)))));
    assert(parse("1 + 2 + 3 + 4 + 5") == 1 + 2 + 3 + 4 + 5);
    assert(parse("(12 * 22) + (36 + -4 + 5)") == (12 * 22) + (36 + -4 + 5));
    assert(parse("(12 * 22) / (5 - 10 + 15)") == (12 * 22) / (5 - 10 + 15));
    assert(parse("12 * 6 * 15 + 5 - 25") == 12 * 6 * 15 + 5 - 25);

    cout << "SUCCESS!!!\n";
    return 0;
}



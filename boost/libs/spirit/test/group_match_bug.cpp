/*=============================================================================
    Copyright (c) 2004 Joao Abecasis
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include <boost/spirit/core.hpp>

#include <boost/spirit/attribute/dynamic_scope.hpp>

#include <boost/spirit/tree/ast.hpp>
#include <boost/spirit/tree/parse_tree.hpp>

using namespace boost::spirit;

struct test_dynamic_scope : dynamic_scope<test_dynamic_scope, int>
{
    test_dynamic_scope() : value(*this) {}
    member1 value;
};

struct test_grammar : public grammar<test_grammar>
{
    template <typename ScannerT>
    struct definition
    {
        definition(const test_grammar&)
        {
        }

        rule<ScannerT, test_dynamic_scope::context_t> const & start() const
        {
            return first;
        }

        rule<ScannerT, test_dynamic_scope::context_t> first;
    };
};

int main()
{
    parse("abcd", test_grammar());
    pt_parse("abcd", test_grammar());
    ast_parse("abcd", test_grammar());
}



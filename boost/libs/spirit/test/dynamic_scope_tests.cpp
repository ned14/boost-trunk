/*=============================================================================
    Copyright (c) 2001-2003 Joel de Guzman
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include <iostream>
#include <boost/detail/lightweight_test.hpp>

#define PHOENIX_LIMIT 5
#define PHOENIX_DYNAMIC_LIMIT 5

using namespace std;

#include <boost/spirit/core.hpp>
#include <boost/spirit/attribute/dynamic_scope.hpp>
#include <boost/spirit/phoenix/core.hpp>
#include <boost/spirit/phoenix/bind.hpp>
#include <boost/spirit/phoenix/operator.hpp>
using namespace boost::spirit;
using namespace boost::phoenix;

///////////////////////////////////////////////////////////////////////////////
//
//  Dynamic Scope tests
//
///////////////////////////////////////////////////////////////////////////////
struct my_dynamic_scope1 : dynamic_scope<my_dynamic_scope1, double>
{
    my_dynamic_scope1() : val(*this) {}
    member1 val;
};

struct my_dynamic_scope2 : dynamic_scope<my_dynamic_scope2, char>
{
    my_dynamic_scope2() : ch(*this) {}
    member1 ch;
};

struct my_dynamic_scope3 : dynamic_scope<my_dynamic_scope3, char>
{
    my_dynamic_scope3() : ch(*this) {}
    member1 ch;
};

struct X { int a; int b; };

#if defined(BOOST_SPIRIT_DEBUG)
//  If debugging is switched on, all dynamic_scope members should have a 
//  corresponding output streaming operator
std::ostream &
operator<< (std::ostream& o, X const &x)
{
    o << "X(" << x.a << ", " << x.b << ")";
    return o;
}
#endif // defined(BOOST_SPIRIT_DEBUG)

struct my_dynamic_scope4 : dynamic_scope<my_dynamic_scope4, X>
{
    my_dynamic_scope4() : x(*this) {}
    member1 x;
};

// MWCW8.3 needs the default constructor here or it won't compile.
// It should not be needed.
struct Y { Y() {} Y(int) {} };

#if defined(BOOST_SPIRIT_DEBUG)
//  If debugging is switched on, all dynamic_scope members should have a 
//  corresponding output streaming operator
std::ostream &
operator<< (std::ostream& o, Y const &x)
{
    o << "Y";
    return o;
}
#endif // defined(BOOST_SPIRIT_DEBUG)

struct my_dynamic_scope5 : boost::spirit::dynamic_scope<my_dynamic_scope5, int, Y>
{
    my_dynamic_scope5() : y(*this) {}
    member1 y;
};

SPIRIT_DYNAMIC_SCOPE(my_dynamic_scope6, (int, x)(int, y)(int, z));

/* The macro above expands to the code below:

    struct my_dynamic_scope6 : dynamic_scope<my_dynamic_scope6, int, int, int>
    {
        my_dynamic_scope6() : x(*this), y(*this), z(*this) {}
        member1 x;
        member2 y;
        member3 z;
    };
*/

void
dynamic_scope_tests()
{
    rule<phrase_scanner_t, my_dynamic_scope1::context_t> num_list;
    double n;

    num_list =
    (
        real_p[num_list.val = arg1] >>  *(',' >> real_p[num_list.val += arg1])
    )
    [ref(n) = num_list.val];

    parse_info<char const*> pi;
    pi = parse("123, 456, 789", num_list, space_p);
    BOOST_TEST(pi.hit);
    BOOST_TEST(pi.full);
    BOOST_TEST(n == 123 + 456 + 789);

    rule<scanner<>, my_dynamic_scope2::context_t> rev;
    rev = anychar_p[rev.ch = arg1] >> !rev >> f_ch_p(rev.ch);

    pi = parse("xyzzyx", rev);
    BOOST_TEST(pi.hit);
    BOOST_TEST(pi.full);

    pi = parse("xyzczyx", rev);
    BOOST_TEST(!pi.hit);

    subrule<0, my_dynamic_scope3::context_t> rev2;
    pi = parse("atoyyota",
        rev2 = anychar_p[rev2.ch = arg1] >> !rev2 >> f_ch_p(rev2.ch)
    );

    BOOST_TEST(pi.hit);
    BOOST_TEST(pi.full);

    pi = parse("whatdahell",
        rev2 = anychar_p[rev2.ch = arg1] >> !rev2 >> f_ch_p(rev2.ch)
    );
    BOOST_TEST(!pi.hit);

    rule<phrase_scanner_t, my_dynamic_scope4::context_t> complex_p;
    complex_p =
            int_p[bind(&X::a, complex_p.x) = arg1]
        >>  ','
        >>  int_p[bind(&X::b, complex_p.x) = arg1]
    ;

    X x;
    pi = parse("123, 456", complex_p[ref(x) = arg1], space_p);
    BOOST_TEST(pi.hit);
    BOOST_TEST(x.a == 123);
    BOOST_TEST(x.b == 456);

    rule<scanner<>, my_dynamic_scope5::context_t> init1; // compile check only
    rule<> r1 = init1(3, 3); // member2 is constructed from int

    rule<scanner<>, my_dynamic_scope6::context_t> init2; // compile check only
    rule<> r2 = init2(3); // member2 and member3 are default constructed
}

///////////////////////////////////////////////////////////////////////////////
//
//  Main
//
///////////////////////////////////////////////////////////////////////////////
int
main()
{
    dynamic_scope_tests();
    return boost::report_errors();
}


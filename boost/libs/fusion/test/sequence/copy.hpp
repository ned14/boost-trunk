/*=============================================================================
    Copyright (c) 1999-2003 Jaakko J�rvi
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#include <boost/detail/lightweight_test.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/preprocessor/cat.hpp>

#if !defined(FUSION_AT)
#define FUSION_AT at_c
#endif

#if !defined(FUSION_MAKE)
#define FUSION_MAKE BOOST_PP_CAT(make_, FUSION_SEQUENCE)
#endif

#if !defined(FUSION_TIE)
#define FUSION_TIE BOOST_PP_CAT(FUSION_SEQUENCE, _tie)
#endif

namespace
{
    // classes with different kinds of conversions
    class AA {};
    class BB : public AA {};
    struct CC { CC() {} CC(const BB&) {} };
    struct DD { operator CC() const { return CC(); }; };
}

void
test()
{
    using namespace boost::fusion;

    FUSION_SEQUENCE<int, char> t1(4, 'a');
    FUSION_SEQUENCE<int, char> t2(5, 'b');
    t2 = t1;
    BOOST_TEST(FUSION_AT<0>(t1) == FUSION_AT<0>(t2));
    BOOST_TEST(FUSION_AT<1>(t1) == FUSION_AT<1>(t2));

    FUSION_SEQUENCE<long, std::string> t3(2, "a");
    t3 = t1;
    BOOST_TEST((double)FUSION_AT<0>(t1) == FUSION_AT<0>(t3));
    BOOST_TEST(FUSION_AT<1>(t1) == FUSION_AT<1>(t3)[0]);

    // testing copy and assignment with implicit conversions
    // between elements testing tie

    FUSION_SEQUENCE<char, BB*, BB, DD> t;
    FUSION_SEQUENCE<int, AA*, CC, CC> a(t);
    a = t;

    int i; char c; double d;
    FUSION_TIE(i, c, d) = FUSION_MAKE(1, 'a', 5.5);

    BOOST_TEST(i==1);
    BOOST_TEST(c=='a');
    BOOST_TEST(d>5.4 && d<5.6);
}

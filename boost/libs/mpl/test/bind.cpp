//-----------------------------------------------------------------------------
// boost mpl/test/bind.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Peter Dimov, Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#include "boost/mpl/bind.hpp"
#include "boost/mpl/assert_is_same.hpp"
#include "boost/mpl/aux_/preprocessor.hpp"

namespace mpl = boost::mpl;

struct test1
{
    template< typename T1 > struct apply
    {
        typedef T1 type;
    };
};

#if 0

#define BIND_DEF(i, ap) \
    typedef mpl::BOOST_PP_CAT(bind, BOOST_PP_TUPLE_ELEM(2, 0, ap))< \
          BOOST_PP_CAT(f, BOOST_PP_TUPLE_ELEM(2, 0, ap)) \
        , BOOST_MPL_PP_ENUM(0, i, BOOST_MPL_PP_PROJECT2ND, int) \
        BOOST_PP_COMMA_IF(i) BOOST_PP_CAT(_, BOOST_PP_TUPLE_ELEM(2, 1, ap)) \
        BOOST_PP_COMMA_IF(BOOST_PP_DEC(i))
        BOOST_MPL_PP_ENUM(i, BOOST_PP_TUPLE_ELEM(2, 0, ap), BOOST_MPL_PP_PROJECT2ND, int) \
        >::type b##i; \

    typedef b##i::apply<
        , BOOST_MPL_PP_ENUM(0, i, BOOST_MPL_PP_PROJECT2ND, int) \
          char
        BOOST_PP_COMMA_IF(arity)
        BOOST_MPL_PP_ENUM(1, arity, BOOST_MPL_PP_PROJECT2ND, int)
        >::type t1;

/**/

#define BIND_TEST(arity, placeholder) \
    BOOST_PP_REPEAT_2ND(
          0
        , arity
        , BIND_DEF
        , (arity, placeholder)
        )

    typedef b##i::apply<
          char
        BOOST_PP_COMMA_IF(arity)
        BOOST_MPL_PP_ENUM(1, arity, BOOST_MPL_PP_PROJECT2ND, int)
        >::type t1;

    typedef b##i::apply<
          char
        BOOST_PP_COMMA_IF(arity)
        BOOST_MPL_PP_ENUM(1, arity, BOOST_MPL_PP_PROJECT2ND, int)
        >::type t1;

        
    typedef mpl::bind2<test2, int, _1,int,int>::type b2;

#endif

int main()
{
    using namespace mpl::placeholder;

    typedef mpl::bind<test1,int> b0;
//    typedef mpl::apply0<b0>::type res;
//    BOOST_MPL_ASSERT_IS_SAME(res,int);

    typedef mpl::bind1st<mpl::apply1<_,_>,test1> b1;

//    typedef mpl::bind1<test1, _1> b1;
    typedef mpl::bind1<test1, _2> b2;
    typedef mpl::bind1<test1, _3> b3;
    typedef mpl::bind1<test1, mpl::bind1<test1,_1> > b4;

    typedef mpl::bind1<_1, char> b5;

    typedef b1::apply<char,int,int,int,int>::type t1;
    typedef b2::apply<int,char,int,int,int>::type t2;
    typedef b3::apply<int,int,char,int,int>::type t3;
    typedef b4::apply<char,int,int,int,int>::type t4;
    typedef b5::apply<test1>::type t5;
    typedef mpl::apply1<b5,test1>::type t5_1;

    BOOST_MPL_ASSERT_IS_SAME(t1, char);
    BOOST_MPL_ASSERT_IS_SAME(t2, char);
    BOOST_MPL_ASSERT_IS_SAME(t3, char);
    BOOST_MPL_ASSERT_IS_SAME(t4, char);
    BOOST_MPL_ASSERT_IS_SAME(t5, char);
    BOOST_MPL_ASSERT_IS_SAME(t5_1, char);
/*
    typedef mpl::bind5<f5,_1,int,int,int,int>::type b1;
    typedef mpl::bind5<f5,int,_1,int,int,int>::type b2;
    typedef mpl::bind5<f5,int,int,_1,int,int>::type b3;
    typedef mpl::bind5<f5,int,int,int,_1,int>::type b4;
    typedef mpl::bind5<f5,int,int,int,int,_1>::type b5;

    typedef b1::apply<char,int,int,int,int>::type t1;
    typedef b1::apply<char,int,int,int,int>::type t1;


    typedef mpl::bind2<test2, _2, int,int,int>::type b3;
    typedef mpl::bind2<test2, int, _2,int,int>::type b4;

m    typedef b2::apply<int,char,int>::type t2;
    typedef b3::apply<int,int,char>::type t3;

    BOOST_MPL_ASSERT_IS_SAME(t1, char);
    BOOST_MPL_ASSERT_IS_SAME(t2, char);
    BOOST_MPL_ASSERT_IS_SAME(t3, char);
*/
//    std::cout << typeid(t4).name();
    return 0;
}

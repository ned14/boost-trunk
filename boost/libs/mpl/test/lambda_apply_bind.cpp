
// Copyright (c) Aleksey Gurtovoy 2001-2004
//
// Use, modification and distribution are subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy 
// at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/apply.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/plus.hpp>

#include <boost/mpl/aux_/test/test.hpp>

#include <vector>


MPL_TEST_CASE()
{
    typedef plus<int_<2>,int_<3> > plus1;
    typedef lambda<plus1>::type plus2;
    MPL_ASSERT_SAME(2,( plus1,plus2 ));

    typedef lambda<std::vector<int> >::type v;
    MPL_ASSERT_SAME(2,( v,std::vector<int> ));

    typedef lambda<std::vector<_1> >::type make_vector;
    typedef make_vector::apply<int>::type v;
    MPL_ASSERT_SAME(2,( v,std::vector<int> ));
}

MPL_TEST_CASE()
{
    typedef plus<_1,_2> plus_fun;
    typedef apply<plus_fun,int_<2>,int_<3> >::type res;

    MPL_ASSERT_EQUAL(2,( res::value,5 ));
}

MPL_TEST_CASE()
{
    typedef apply<_1, plus<_1,_2> >::type plus_fun;
    MPL_ASSERT_SAME(3,( plus_fun,plus<_1,_2> ));

    typedef apply<plus_fun,int_<2>,int_<3> >::type res;
    MPL_ASSERT_EQUAL(2,( res::value,5 ));
}

MPL_TEST_CASE()
{
    typedef lambda< lambda<_1,void_> >::type make_lambda;
    typedef make_lambda::apply< std::vector<int> >::type v;
    MPL_ASSERT_SAME(2,( v,std::vector<int> ));

    typedef make_lambda::apply< std::vector<_1> >::type make_vector;
    typedef make_vector::apply<int>::type v_int;
    MPL_ASSERT_SAME(2,( v,std::vector<int> ));
}

MPL_TEST_CASE()
{
    typedef apply< _1, std::vector<int> >::type v;
    MPL_ASSERT_SAME(2,( v,std::vector<int> ));

    typedef apply< _1, std::vector<_1> >::type v_lambda;
    typedef apply<v_lambda,int>::type v_int;
    MPL_ASSERT_SAME(2,( v,std::vector<int> ));
}

MPL_TEST_CASE()
{
    typedef apply< lambda<_1>, std::vector<int> >::type v;
    MPL_ASSERT_SAME(2,( v,std::vector<int> ));

    typedef apply< lambda<_1>, std::vector<_1> >::type make_vector;
    typedef make_vector::apply<int>::type v_int;
    MPL_ASSERT_SAME(2,( v,std::vector<int> ));
}

MPL_TEST_CASE()
{
    typedef apply< lambda<_1>, plus<_1,_2> >::type plus_fun;
    typedef plus_fun::apply< int_<2>,int_<3> >::type res;

    MPL_ASSERT_EQUAL(2,( res::value,5 ));
}

MPL_TEST_CASE()
{
    typedef bind2<plus<>,_1,_1> b1;
    typedef lambda<b1>::type b2;
    MPL_ASSERT_SAME(2,( b1,b2 ));
}

MPL_TEST_CASE()
{
#if !BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x0302))
    typedef lambda< lambda< bind2<plus<>,_1,_1> > >::type make_lambda;
    typedef make_lambda::type::apply< int_<5> >::type res;
    MPL_ASSERT_EQUAL(2,( res::value,10 ));
#endif
}

MPL_TEST_CASE()
{
    typedef apply< bind2<plus<>,_1,_1>, int_<5> >::type res;
    MPL_ASSERT_EQUAL(2,( res::value,10 ));
}

MPL_TEST_CASE()
{
    typedef apply<_1, lambda<plus<_1,_2> > >::type plus_fun;
    typedef plus_fun::type::apply< int_<2>,int_<3> >::type res;

    MPL_ASSERT_EQUAL(2,( res::value,5 ));
}

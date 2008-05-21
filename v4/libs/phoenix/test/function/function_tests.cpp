/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#include <iostream>
#include <cmath>
#include <boost/detail/lightweight_test.hpp>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator.hpp>
#include <boost/phoenix/function.hpp>

using namespace boost::phoenix;
using namespace boost::phoenix::arg_names;
using namespace std;

    struct test_impl
    {
        typedef void result_type;
        void operator()() const
        {
            cout << "Test lazy functions...\n";
        }
    };

    function<test_impl> test;

    struct sqr_impl
    {
        template <typename Sig>
        struct result;
        
        template <typename This, typename Arg>
        struct result<This(Arg)>
        {
            typedef Arg type;
        };
        
        template <typename This, typename Arg>
        struct result<This(Arg &)>
          : result<This(Arg)>
        {};

        template <typename Arg>
        Arg operator()(Arg n) const
        {
            return n * n;
        }
    };

    function<sqr_impl> sqr;

    struct fact_impl
    {
        template <typename Sig>
        struct result;
        
        template <typename This, typename Arg>
        struct result<This(Arg)>
        {
            typedef Arg type;
        };
        
        template <typename This, typename Arg>
        struct result<This(Arg &)>
          : result<This(Arg)>
        {};

        template <typename Arg>
        Arg operator()(Arg n) const
        {
            return (n <= 0) ? 1 : n * (*this)(n-1);
        }
    };

    function<fact_impl> fact;

    struct pow_impl
    {
        template <typename Sig>
        struct result;
        
        template <typename This, typename Arg1, typename Arg2>
        struct result<This(Arg1, Arg2)>
        {
            typedef Arg1 type;
        };
        
        template <typename This, typename Arg1, typename Arg2>
        struct result<This(Arg1 &, Arg2)>
          : result<This(Arg1, Arg2)>
        {};

        template <typename Arg1, typename Arg2>
        Arg1 operator()(Arg1 a, Arg2 b) const
        {
            using std::pow;
            return pow(a, b);
        }
    };

    function<pow_impl> power;

    struct add_impl
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
        struct result<This(Arg1, Arg2, Arg3, Arg4)>
        {
            typedef Arg1 type;
        };

        template <typename This, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
        struct result<This(Arg1 &, Arg2, Arg3, Arg4)>
          : result<This(Arg1, Arg2, Arg3, Arg4)>
        {};

        template <typename Arg1, typename Arg2, typename Arg3, typename Arg4>
        Arg1 operator()(Arg1 a, Arg2 b, Arg3 c, Arg4 d) const
        {
            return a + b + c + d;
        }
    };

    function<add_impl> add;

int
main()
{
    using std::pow;
    int i5 = 5;
    double d5 = 5, d3 = 3;

    test()();
    BOOST_TEST(sqr(arg1)(i5) == (i5*i5));
    BOOST_TEST(fact(4)() == 24);
    BOOST_TEST(fact(arg1)(i5) == 120);
    BOOST_TEST((int)power(arg1, arg2)(d5, d3) == (int)pow(d5, d3));
    BOOST_TEST((sqr(arg1) + 5)(i5) == ((i5*i5)+5));
    BOOST_TEST(add(arg1, arg1, arg1, arg1)(i5) == (5+5+5+5));

    int const ic5 = 5;
    // testing consts
    BOOST_TEST(sqr(arg1)(ic5) == (ic5*ic5));

    return boost::report_errors();
}

/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#include <iostream>
#include <string>

#define PHOENIX_LIMIT 6

#include <boost/detail/lightweight_test.hpp>
#include <boost/spirit/phoenix/core.hpp>
#include <boost/spirit/phoenix/operator.hpp>
#include <boost/spirit/phoenix/scope/dynamic.hpp>

struct my_closure : boost::phoenix::dynamic_scope<int, std::string, double>
{
    my_closure() : num(*this), message(*this), real(*this) {}

    member1 num;
    member2 message;
    member3 real;
};

int
main()
{
    using namespace boost::phoenix;

    my_closure clos;

    {   //  First stack frame
        dynamic_frame<my_closure::self_type> frame(clos);
        (clos.num = 123)();
        (clos.num += 456)();
        (clos.real = clos.num / 56.5)();
        (clos.message = "Hello " + std::string("World "))();

        {   //  Second stack frame
            dynamic_frame<my_closure::self_type> frame(clos);
            (clos.num = 987)();
            (clos.message = "Abracadabra ")();
            (clos.real = clos.num * 1e30)();

            {   //  Third stack frame
                boost::fusion::vector<int, char const*, double> init(-1, "Direct Init ", 3.14);
                dynamic_frame<my_closure::self_type> frame(clos, init);

                (std::cout << clos.message << clos.num << ", " << clos.real << '\n')();
                BOOST_TEST(clos.num() == -1);
                BOOST_TEST(clos.real() == 3.14);
                BOOST_TEST(clos.message() == "Direct Init ");
            }

            (std::cout << clos.message << clos.num << ", " << clos.real << '\n')();
            BOOST_TEST(clos.num() == 987);
            BOOST_TEST(clos.real() == clos.num() * 1e30);
            BOOST_TEST(clos.message() == "Abracadabra ");        
        }

        (std::cout << clos.message << clos.num << ", " << clos.real << '\n')();
        BOOST_TEST(clos.num() == 123+456);
        BOOST_TEST(clos.real() == clos.num() / 56.5);
        BOOST_TEST(clos.message() == "Hello " + std::string("World "));
    }

    return 0;
}

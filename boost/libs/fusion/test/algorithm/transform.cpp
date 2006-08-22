/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#include <boost/detail/lightweight_test.hpp>
#include <boost/fusion/sequence/container/vector/vector.hpp>
#include <boost/fusion/sequence/adapted/mpl.hpp>
#include <boost/fusion/sequence/io/out.hpp>
#include <boost/fusion/sequence/generation/make_vector.hpp>
#include <boost/fusion/sequence/comparison/equal_to.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/type_traits/is_class.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/type_traits/is_reference.hpp>

struct square
{
    template <typename T>
    struct result
    {
        BOOST_STATIC_ASSERT(!boost::is_reference<T>::value);
        typedef int type;
    };

    template <typename T>
    int operator()(T x) const
    {
        return x * x;
    }
};

struct add
{
    template <typename A, typename B>
    struct result
    {
        typedef int type;
    };

    template <typename A, typename B>
    int operator()(A a, B b) const
    {
        return a + b;
    }
};

int
main()
{
    using namespace boost::fusion;
    using boost::mpl::range_c;

    std::cout << tuple_open('[');
    std::cout << tuple_close(']');
    std::cout << tuple_delimiter(", ");

/// Testing the transform

    {
        typedef range_c<int, 5, 9> sequence_type;
        sequence_type sequence;
        std::cout << transform(sequence, square()) << std::endl;
        BOOST_TEST((transform(sequence, square()) == make_vector(25, 36, 49, 64)));
    }

    {
        typedef range_c<int, 5, 9> mpl_list1;
        std::cout << transform(mpl_list1(), square()) << std::endl;
        BOOST_TEST((transform(mpl_list1(), square()) == make_vector(25, 36, 49, 64)));
    }
    
    {
        vector<int, int, int> tup(1, 2, 3);
        std::cout << transform(tup, square()) << std::endl;
        BOOST_TEST((transform(tup, square()) == make_vector(1, 4, 9)));
    }

    {
        vector<int, int, int> tup1(1, 2, 3);
        vector<int, int, int> tup2(4, 5, 6);
        std::cout << transform(tup1, tup2, add()) << std::endl;
        BOOST_TEST((transform(tup1, tup2, add()) == make_vector(5, 7, 9)));
    }

    return boost::report_errors();
}


/*=============================================================================
    Copyright (c) 2003 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#include <boost/detail/lightweight_test.hpp>
#include <boost/spirit/fusion/sequence/tuple.hpp>
#include <boost/spirit/fusion/sequence/io.hpp>
#include <boost/spirit/fusion/sequence/equal_to.hpp>
#include <boost/spirit/fusion/sequence/make_tuple.hpp>
#include <boost/spirit/fusion/algorithm/erase.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/int.hpp>

int
main()
{
    using namespace boost::fusion;
    using boost::mpl::vector_c;
    using boost::mpl::begin;
    using boost::mpl::advance;
    using boost::mpl::int_;

    std::cout << tuple_open('[');
    std::cout << tuple_close(']');
    std::cout << tuple_delimiter(", ");

/// Testing erase

    {
        char const* s = "Ruby";
        typedef tuple<int, char, double, char const*> tuple_type;
        tuple_type t1(1, 'x', 3.3, s);
        tuple_iterator<2, tuple_type> pos(t1);

        std::cout << erase(t1, pos) << std::endl;
        BOOST_TEST((erase(t1, pos) == make_tuple(1, 'x', s)));
    }

    {
        typedef vector_c<int, 1, 2, 3, 4, 5> mpl_vec;
        typedef boost::mpl::begin<mpl_vec>::type mpl_vec_begin;
        typedef boost::mpl::advance<mpl_vec_begin, int_<3> >::type mpl_vec_at3;

        std::cout << erase(mpl_vec(), mpl_vec_at3()) << std::endl;
        BOOST_TEST((erase(mpl_vec(), mpl_vec_at3())
            == make_tuple(1, 2, 3, 5)));
    }

    return boost::report_errors();
}


/*=============================================================================
    Copyright (c) 2003 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#include <boost/test/minimal.hpp>
#include <boost/spirit/fusion/sequence/tuple.hpp>
#include <boost/spirit/fusion/sequence/io.hpp>
#include <boost/spirit/fusion/sequence/make_tuple.hpp>
#include <boost/spirit/fusion/sequence/equal_to.hpp>
#include <boost/spirit/fusion/iterator/tuple_iterator.hpp>
#include <boost/spirit/fusion/algorithm/replace.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/int.hpp>
#include <string>

int
test_main(int, char*[])
{
    using namespace boost::fusion;
    using boost::mpl::vector_c;
    using boost::mpl::advance;
    using boost::mpl::int_;
    namespace mpl = boost::mpl;

    std::cout << tuple_open('[');
    std::cout << tuple_close(']');
    std::cout << tuple_delimiter(", ");

/// Testing replace

    {
        char const* s = "Ruby";
        typedef tuple<int, char, double, char const*> tuple_type;
        tuple_type t(1, 'x', 3.3, s);
        tuple_iterator<2, tuple_type> pos(t);

        std::cout << replace(t, pos, 123456) << std::endl;
        BOOST_TEST((replace(t, pos, 123456)
            == make_tuple(1, 'x', 123456, s)));

        std::cout << replace(t, begin(t), "happy") << std::endl;
        BOOST_TEST((replace(t, begin(t), "happy")
            == make_tuple(std::string("happy"), 'x', 3.3, s)));
    }

    {
        typedef vector_c<int, 1, 2, 3, 4, 5> mpl_vec;
        typedef mpl::begin<mpl_vec>::type mpl_vec_begin;
        typedef advance<mpl_vec_begin, int_<3> >::type mpl_vec_at3;

        std::cout << replace(mpl_vec(), mpl_vec_at3(), int_<66>()) << std::endl;
        BOOST_TEST((replace(mpl_vec(), mpl_vec_at3(), int_<66>())
            == make_tuple(1, 2, 3, 66, 5)));
    }

    return 0;
}


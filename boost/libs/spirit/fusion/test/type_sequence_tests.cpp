/*=============================================================================
    Copyright (c) 2003 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#include <boost/detail/lightweight_test.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/spirit/fusion/sequence/tuple.hpp>
#include <boost/spirit/fusion/sequence/io.hpp>
#include <boost/spirit/fusion/sequence/equal_to.hpp>
#include <boost/spirit/fusion/sequence/type_sequence.hpp>
#include <boost/spirit/fusion/sequence/generate.hpp>
#include <boost/spirit/fusion/sequence/make_tuple.hpp>

struct X
{
    operator char const*() const
    {
        return "<X-object>";
    }
};

int
main()
{
    using namespace boost::fusion;
    using boost::mpl::vector_c;
    using boost::mpl::int_;
    using boost::mpl::list;
    namespace mpl = boost::mpl;

    std::cout << tuple_open('[');
    std::cout << tuple_close(']');
    std::cout << tuple_delimiter(", ");

/// Testing type_sequence

    {
        typedef list<int, double, X> mpl_list1;
        typedef mpl::begin<mpl_list1>::type begin_type;
        typedef mpl::end<mpl_list1>::type end_type;
        typedef tuple<int, double, X> tuple_type;

        type_sequence_iterator<begin_type> iter;
        tuple_type t1(iter);
        std::cout << t1 << std::endl;

        BOOST_TEST(t1 == tuple_type());
    }

    {
        typedef list<int, double, X, int> mpl_list1;
        type_sequence<mpl_list1> view;
        std::cout << generate(view) << std::endl;

        BOOST_TEST((generate(view) == tuple<int, double, X, int>()));
    }

    { // MPL constant integer vector

        typedef vector_c<int, 1, 2, 3, 4, 5> mpl_vec;
        type_sequence<mpl_vec> view;
        std::cout << generate(view) << std::endl;

        BOOST_TEST((generate(view) ==
            tuple<
                int_<1>
              , int_<2>
              , int_<3>
              , int_<4>
              , int_<5> >()));
    }

#ifdef FUSION_COMFORMING_COMPILER

    { // Direct MPL sequence operations

        typedef vector_c<int, 1, 2, 3, 4, 5> mpl_vec;
        std::cout << generate(mpl_vec()) << std::endl;

        tuple<
            int_<1>
          , int_<2>
          , int_<3>
          , int_<4>
          , int_<5> >
        expected;

        BOOST_TEST((generate(mpl_vec()) == expected));
        BOOST_TEST((mpl_vec() == expected));
        BOOST_TEST((expected == mpl_vec()));

        boost::fusion::begin(mpl_vec()); // compile check only
        boost::fusion::end(mpl_vec()); // compile check only

        {   // Testing a VC7.1 bug (see note on deref.hpp)

            typedef vector_c<int, 1, 2, 3> v1_type;
            v1_type v1;
            int i = *boost::fusion::begin(v1);
            (void)i;
        }
    }

#endif

    return boost::report_errors();
}


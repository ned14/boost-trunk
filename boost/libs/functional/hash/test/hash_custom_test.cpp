
//  (C) Copyright Daniel James 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>
#include <cstddef>

namespace test
{
    struct custom
    {
        int value_;

        std::size_t hash() const
        {
            return value_ * 10;
        }

#if !defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP)
        friend std::size_t hash_value(custom const& x )
        {
            return x.hash();
        }
#endif

        custom(int x) : value_(x) {}
    };
}

#if defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP)
namespace boost
{
    std::size_t hash_value(test::custom x)
    {
        return x.hash();
    }
}
#endif

#include "./config.hpp"

#ifdef TEST_EXTENSIONS
#  ifdef TEST_STD_INCLUDES
#    include <functional>
#  else
#    include <boost/functional/hash/hash.hpp>
#  endif
#endif

#define BOOST_AUTO_TEST_MAIN
#include <boost/test/auto_unit_test.hpp>

#ifdef TEST_EXTENSIONS

#include <vector>
#include <string>
#include <cctype>

BOOST_AUTO_UNIT_TEST(custom_tests)
{
    HASH_NAMESPACE::hash<test::custom> custom_hasher;
    BOOST_CHECK(custom_hasher(10) == 100u);
    test::custom x(55);
    BOOST_CHECK(custom_hasher(x) == 550u);

    {
        using namespace HASH_NAMESPACE;
        BOOST_CHECK(custom_hasher(x) == hash_value(x));
    }

    std::vector<test::custom> custom_vector;
    custom_vector.push_back(5);
    custom_vector.push_back(25);
    custom_vector.push_back(35);

    std::size_t seed = 0;
    HASH_NAMESPACE::hash_combine(seed, test::custom(5));
    HASH_NAMESPACE::hash_combine(seed, test::custom(25));
    HASH_NAMESPACE::hash_combine(seed, test::custom(35));

    std::size_t seed2 = 0;
    HASH_NAMESPACE::hash_combine(seed2, 50u);
    HASH_NAMESPACE::hash_combine(seed2, 250u);
    HASH_NAMESPACE::hash_combine(seed2, 350u);

    BOOST_CHECK(seed ==
            HASH_NAMESPACE::hash_range(custom_vector.begin(), custom_vector.end()));
    BOOST_CHECK(seed == seed2);
}

#endif // TEST_EXTENSIONS

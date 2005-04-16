
//  Copyright Daniel James 2005. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "./config.hpp"

#ifdef TEST_STD_INCLUDES
#  include <functional>
#else
#  include <boost/functional/hash/hash.hpp>
#endif

#define BOOST_AUTO_TEST_MAIN
#include <boost/test/auto_unit_test.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/limits.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

#include "./compile_time.hpp"

template <class T>
void numeric_test(T*)
{
    typedef std::numeric_limits<T> limits;

    compile_time_tests((T*) 0);

    HASH_NAMESPACE::hash<T> x1;
    HASH_NAMESPACE::hash<T> x2;

    T v1 = -5;
    BOOST_CHECK(x1(v1) == x2(v1));
    BOOST_CHECK(x1(T(-5)) == x2(T(-5)));
    BOOST_CHECK(x1(T(0)) == x2(T(0)));
    BOOST_CHECK(x1(T(10)) == x2(T(10)));
    BOOST_CHECK(x1(T(25)) == x2(T(25)));
    BOOST_CHECK(x1(T(5) - T(5)) == x2(T(0)));
    BOOST_CHECK(x1(T(6) + T(4)) == x2(T(10)));

#if defined(TEST_EXTENSIONS)
    BOOST_CHECK(x1(T(-5)) == HASH_NAMESPACE::hash_value(T(-5)));
    BOOST_CHECK(x1(T(0)) == HASH_NAMESPACE::hash_value(T(0)));
    BOOST_CHECK(x1(T(10)) == HASH_NAMESPACE::hash_value(T(10)));
    BOOST_CHECK(x1(T(25)) == HASH_NAMESPACE::hash_value(T(25)));

    if (limits::is_integer)
    {
        BOOST_CHECK(HASH_NAMESPACE::hash_value(T(-5)) == (std::size_t)T(-5));
        BOOST_CHECK(HASH_NAMESPACE::hash_value(T(0)) == (std::size_t)T(0u));
        BOOST_CHECK(HASH_NAMESPACE::hash_value(T(10)) == (std::size_t)T(10u));
        BOOST_CHECK(HASH_NAMESPACE::hash_value(T(25)) == (std::size_t)T(25u));
    }
#endif
}

template <class T>
void limits_test(T*)
{
    typedef std::numeric_limits<T> limits;

    if(limits::is_specialized)
    {
        HASH_NAMESPACE::hash<T> x1;
        HASH_NAMESPACE::hash<T> x2;

        T min_value = (limits::min)();
        T max_value = (limits::max)();

        BOOST_CHECK(x1(min_value) == x2((limits::min)()));
        BOOST_CHECK(x1(max_value) == x2((limits::max)()));

#if defined(TEST_EXTENSIONS)
        BOOST_CHECK(x1(min_value) == HASH_NAMESPACE::hash_value(min_value));
        BOOST_CHECK(x1(max_value) == HASH_NAMESPACE::hash_value(max_value));

        if (limits::is_integer)
        {
            BOOST_CHECK(HASH_NAMESPACE::hash_value(min_value)
                    == std::size_t(min_value));
            BOOST_CHECK(HASH_NAMESPACE::hash_value(max_value)
                    == std::size_t(max_value));
        }
#endif
    }
}

template <class T>
void poor_quality_tests(T*)
{
    typedef std::numeric_limits<T> limits;

    HASH_NAMESPACE::hash<T> x1;
    HASH_NAMESPACE::hash<T> x2;

    // A hash function can legally fail these tests, but it'll not be a good
    // sign.
    if(T(1) != T(-1))
        BOOST_CHECK(x1(T(1)) !=  x2(T(-1)));
    if(T(1) != T(2))
        BOOST_CHECK(x1(T(1)) !=  x2(T(2)));
    if((limits::max)() != (limits::max)() - 1)
        BOOST_CHECK(x1((limits::max)()) != x2((limits::max)() - 1));
}

#define NUMERIC_TEST(type, name) \
    BOOST_AUTO_UNIT_TEST(BOOST_PP_CAT(test_, name)) { \
        numeric_test((type*) 0); \
        limits_test((type*) 0); \
        poor_quality_tests((type*) 0); \
    }

NUMERIC_TEST(bool, bool)
NUMERIC_TEST(char, char)
NUMERIC_TEST(signed char, schar)
NUMERIC_TEST(unsigned char, uchar)
#ifndef BOOST_NO_INTRINSIC_WCHAR_T
NUMERIC_TEST(wchar_t, wchar)
#endif
NUMERIC_TEST(short, short)
NUMERIC_TEST(unsigned short, ushort)
NUMERIC_TEST(int, int)
NUMERIC_TEST(unsigned int, uint)
NUMERIC_TEST(long, hash_long)
NUMERIC_TEST(unsigned long, ulong)

NUMERIC_TEST(float, float)
NUMERIC_TEST(double, double)
NUMERIC_TEST(long double, ldouble)

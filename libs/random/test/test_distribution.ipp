/* test_distribution.ipp
 *
 * Copyright Steven Watanabe 2010
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * $Id$
 *
 */

#include <boost/random/linear_congruential.hpp>
#include <sstream>

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_constructors) {
    BOOST_RANDOM_DISTRIBUTION dist;
    BOOST_CHECK_EQUAL(dist.BOOST_RANDOM_ARG1(), BOOST_RANDOM_ARG1_DEFAULT);
#ifdef BOOST_RANDOM_ARG2
    BOOST_CHECK_EQUAL(dist.BOOST_RANDOM_ARG2(), BOOST_RANDOM_ARG2_DEFAULT);
#endif
    BOOST_RANDOM_DISTRIBUTION dist_one(BOOST_RANDOM_ARG1_VALUE);
    BOOST_CHECK_EQUAL(dist_one.BOOST_RANDOM_ARG1(), BOOST_RANDOM_ARG1_VALUE);
#ifdef BOOST_RANDOM_ARG2
    BOOST_CHECK_EQUAL(dist_one.BOOST_RANDOM_ARG2(), BOOST_RANDOM_ARG2_DEFAULT);
#endif
#ifdef BOOST_RANDOM_ARG2
    BOOST_RANDOM_DISTRIBUTION dist_two(BOOST_RANDOM_ARG1_VALUE, BOOST_RANDOM_ARG2_VALUE);
    BOOST_CHECK_EQUAL(dist_two.BOOST_RANDOM_ARG1(), BOOST_RANDOM_ARG1_VALUE);
    BOOST_CHECK_EQUAL(dist_two.BOOST_RANDOM_ARG2(), BOOST_RANDOM_ARG2_VALUE);
#endif
    BOOST_RANDOM_DISTRIBUTION copy(dist);
    BOOST_CHECK_EQUAL(dist, copy);
    BOOST_RANDOM_DISTRIBUTION copy_one(dist_one);
    BOOST_CHECK_EQUAL(dist_one, copy_one);
#ifdef BOOST_RANDOM_ARG2
    BOOST_RANDOM_DISTRIBUTION copy_two(dist_two);
    BOOST_CHECK_EQUAL(dist_two, copy_two);
#endif
}

BOOST_AUTO_TEST_CASE(test_param) {
#ifdef BOOST_RANDOM_ARG2
    BOOST_RANDOM_DISTRIBUTION dist(BOOST_RANDOM_ARG1_VALUE, BOOST_RANDOM_ARG2_VALUE);
#else
    BOOST_RANDOM_DISTRIBUTION dist(BOOST_RANDOM_ARG1_VALUE);
#endif
    BOOST_RANDOM_DISTRIBUTION::param_type param = dist.param();
    BOOST_CHECK_EQUAL(param.BOOST_RANDOM_ARG1(), BOOST_RANDOM_ARG1_VALUE);
#ifdef BOOST_RANDOM_ARG2
    BOOST_CHECK_EQUAL(param.BOOST_RANDOM_ARG2(), BOOST_RANDOM_ARG2_VALUE);
#endif
    BOOST_RANDOM_DISTRIBUTION copy1(param);
    BOOST_CHECK_EQUAL(dist, copy1);
    BOOST_RANDOM_DISTRIBUTION copy2;
    copy2.param(param);
    BOOST_CHECK_EQUAL(dist, copy2);

    BOOST_RANDOM_DISTRIBUTION::param_type param_copy = param;
    BOOST_CHECK_EQUAL(param, param_copy);
    BOOST_CHECK(param == param_copy);
    BOOST_CHECK(!(param != param_copy));
    BOOST_RANDOM_DISTRIBUTION::param_type param_default;
    BOOST_CHECK_EQUAL(param_default.BOOST_RANDOM_ARG1(), BOOST_RANDOM_ARG1_DEFAULT);
#ifdef BOOST_RANDOM_ARG2
    BOOST_CHECK_EQUAL(param_default.BOOST_RANDOM_ARG2(), BOOST_RANDOM_ARG2_DEFAULT);
#endif
    BOOST_CHECK(param != param_default);
    BOOST_CHECK(!(param == param_default));
    BOOST_RANDOM_DISTRIBUTION::param_type param_one(BOOST_RANDOM_ARG1_VALUE);
    BOOST_CHECK_EQUAL(param_one.BOOST_RANDOM_ARG1(), BOOST_RANDOM_ARG1_VALUE);
#ifdef BOOST_RANDOM_ARG2
    BOOST_CHECK_EQUAL(param_one.BOOST_RANDOM_ARG2(), BOOST_RANDOM_ARG2_DEFAULT);
#endif
#ifdef BOOST_RANDOM_ARG2
    BOOST_CHECK(param != param_one);
    BOOST_CHECK(!(param == param_one));
#endif
    BOOST_CHECK(param_default != param_one);
    BOOST_CHECK(!(param_default == param_one));
#ifdef BOOST_RANDOM_ARG2
    BOOST_RANDOM_DISTRIBUTION::param_type param_two(BOOST_RANDOM_ARG1_VALUE, BOOST_RANDOM_ARG2_VALUE);
    BOOST_CHECK_EQUAL(param_two.BOOST_RANDOM_ARG1(), BOOST_RANDOM_ARG1_VALUE);
    BOOST_CHECK_EQUAL(param_two.BOOST_RANDOM_ARG2(), BOOST_RANDOM_ARG2_VALUE);
#endif
}

BOOST_AUTO_TEST_CASE(test_min_max) {
    BOOST_RANDOM_DISTRIBUTION dist;
    BOOST_CHECK_EQUAL((dist.min)(), BOOST_RANDOM_DIST0_MIN);
    BOOST_CHECK_EQUAL((dist.max)(), BOOST_RANDOM_DIST0_MAX);
    BOOST_RANDOM_DISTRIBUTION dist_one(BOOST_RANDOM_ARG1_VALUE);
    BOOST_CHECK_EQUAL((dist_one.min)(), BOOST_RANDOM_DIST1_MIN);
    BOOST_CHECK_EQUAL((dist_one.max)(), BOOST_RANDOM_DIST1_MAX);
#ifdef BOOST_RANDOM_ARG2
    BOOST_RANDOM_DISTRIBUTION dist_two(BOOST_RANDOM_ARG1_VALUE, BOOST_RANDOM_ARG2_VALUE);
    BOOST_CHECK_EQUAL((dist_two.min)(), BOOST_RANDOM_DIST2_MIN);
    BOOST_CHECK_EQUAL((dist_two.max)(), BOOST_RANDOM_DIST2_MAX);
#endif
}

BOOST_AUTO_TEST_CASE(test_comparison) {
    BOOST_RANDOM_DISTRIBUTION dist;
    BOOST_RANDOM_DISTRIBUTION dist_copy(dist);
    BOOST_RANDOM_DISTRIBUTION dist_one(BOOST_RANDOM_ARG1_VALUE);
    BOOST_RANDOM_DISTRIBUTION dist_one_copy(dist_one);
#ifdef BOOST_RANDOM_ARG2
    BOOST_RANDOM_DISTRIBUTION dist_two(BOOST_RANDOM_ARG1_VALUE, BOOST_RANDOM_ARG2_VALUE);
    BOOST_RANDOM_DISTRIBUTION dist_two_copy(dist_two);
#endif
    BOOST_CHECK(dist == dist_copy);
    BOOST_CHECK(!(dist != dist_copy));
    BOOST_CHECK(dist_one == dist_one_copy);
    BOOST_CHECK(!(dist_one != dist_one_copy));
    BOOST_CHECK(dist != dist_one);
    BOOST_CHECK(!(dist == dist_one));
#ifdef BOOST_RANDOM_ARG2
    BOOST_CHECK(dist_two == dist_two_copy);
    BOOST_CHECK(!(dist_two != dist_two_copy));
    BOOST_CHECK(dist != dist_two);
    BOOST_CHECK(!(dist == dist_two));
    BOOST_CHECK(dist_one != dist_two);
    BOOST_CHECK(!(dist_one == dist_two));
#endif
}

BOOST_AUTO_TEST_CASE(test_streaming) {
#ifdef BOOST_RANDOM_ARG2
    BOOST_RANDOM_DISTRIBUTION dist(BOOST_RANDOM_ARG1_VALUE, BOOST_RANDOM_ARG2_VALUE);
#else
    BOOST_RANDOM_DISTRIBUTION dist(BOOST_RANDOM_ARG1_VALUE);
#endif
    std::stringstream stream;
    stream << dist;
    BOOST_RANDOM_DISTRIBUTION restored_dist;
    stream >> restored_dist;
    BOOST_CHECK_EQUAL(dist, restored_dist);
}

BOOST_AUTO_TEST_CASE(test_generation) {
    boost::minstd_rand0 gen;
    BOOST_RANDOM_DISTRIBUTION dist BOOST_RANDOM_TEST1_PARAMS;
    BOOST_RANDOM_DISTRIBUTION dist_two BOOST_RANDOM_TEST2_PARAMS;
	typedef BOOST_RANDOM_DISTRIBUTION::result_type result_type;
    for(int i = 0; i < 10; ++i) {
        result_type value = dist(gen);
#ifdef BOOST_RANDOM_TEST1_MIN
        BOOST_CHECK_GE(value, BOOST_RANDOM_TEST1_MIN);
#endif
#ifdef BOOST_RANDOM_TEST1_MAX
        BOOST_CHECK_LE(value, BOOST_RANDOM_TEST1_MAX);
#endif
        result_type value_two = dist_two(gen);
#ifdef BOOST_RANDOM_TEST2_MIN
        BOOST_CHECK_GE(value_two, BOOST_RANDOM_TEST2_MIN);
#endif
#ifdef BOOST_RANDOM_TEST2_MAX
        BOOST_CHECK_LE(value_two, BOOST_RANDOM_TEST2_MAX);
#endif
        result_type value_param = dist_two(gen, dist.param());
#ifdef BOOST_RANDOM_TEST1_MIN
        BOOST_CHECK_GE(value_param, BOOST_RANDOM_TEST1_MIN);
#endif
#ifdef BOOST_RANDOM_TEST1_MAX
        BOOST_CHECK_LE(value_param, BOOST_RANDOM_TEST1_MAX);
#endif
        result_type value_two_param = dist(gen, dist_two.param());
#ifdef BOOST_RANDOM_TEST2_MIN
        BOOST_CHECK_GE(value_two_param, BOOST_RANDOM_TEST2_MIN);
#endif
#ifdef BOOST_RANDOM_TEST2_MAX
        BOOST_CHECK_LE(value_two_param, BOOST_RANDOM_TEST2_MAX);
#endif
    }
}

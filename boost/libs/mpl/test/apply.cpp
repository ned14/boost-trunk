
// Copyright (c) Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/apply.hpp>
#include <boost/mpl/limits/arity.hpp>
#include <boost/mpl/aux_/preprocessor/params.hpp>
#include <boost/mpl/aux_/preprocessor/enum.hpp>

#include <boost/mpl/aux_/test.hpp>

#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/if.hpp>
#include <boost/preprocessor/cat.hpp>


#define APPLY_0_FUNC_DEF(i) \
    struct f0 { typedef char type; }; \
/**/

#define APPLY_N_FUNC_DEF(i) \
    struct first##i \
    { \
        template< BOOST_MPL_PP_PARAMS(i, typename U) > \
        struct apply { typedef U1 type; }; \
    }; \
    \
    struct last##i \
    { \
        template< BOOST_MPL_PP_PARAMS(i, typename U) > \
        struct apply { typedef BOOST_PP_CAT(U,i) type; }; \
    }; \
/**/

#define APPLY_FUNC_DEF(z, i, unused) \
    BOOST_PP_IF( \
          i \
        , APPLY_N_FUNC_DEF \
        , APPLY_0_FUNC_DEF \
        )(i) \
/**/

namespace { namespace test {
BOOST_PP_REPEAT(
      BOOST_MPL_LIMIT_METAFUNCTION_ARITY
    , APPLY_FUNC_DEF
    , unused
    )
}}

#define APPLY_0_TEST(i, apply_) \
    typedef apply_<test::f##i>::type t; \
    { MPL_ASSERT_SAME(2,(t, char)); } \
/**/

#define APPLY_N_TEST(i, apply_) \
    typedef apply_< \
          test::first##i \
        , char \
        BOOST_PP_COMMA_IF(BOOST_PP_DEC(i)) \
        BOOST_MPL_PP_ENUM(BOOST_PP_DEC(i), int) \
        >::type t1; \
    \
    typedef apply_< \
          test::last##i \
        , BOOST_MPL_PP_ENUM(BOOST_PP_DEC(i), int) \
        BOOST_PP_COMMA_IF(BOOST_PP_DEC(i)) char \
        >::type t2; \
    { MPL_ASSERT_SAME(2,(t1, char)); } \
    { MPL_ASSERT_SAME(2,(t2, char)); } \
/**/

#define APPLY_TEST(z, i, APPLY_NAME) \
    BOOST_PP_IF( \
          i \
        , APPLY_N_TEST \
        , APPLY_0_TEST \
        )(i, APPLY_NAME(i)) \
/**/


MPL_TEST_CASE()
{
#   define MAKE_APPLY_N_NAME(i) apply##i
    BOOST_PP_REPEAT(
          BOOST_MPL_LIMIT_METAFUNCTION_ARITY
        , APPLY_TEST
        , MAKE_APPLY_N_NAME
        )
}

#if defined(BOOST_MPL_HAS_APPLY)
MPL_TEST_CASE()
{
#   define MAKE_APPLY_NAME(i) apply
    BOOST_PP_REPEAT(
          BOOST_MPL_LIMIT_METAFUNCTION_ARITY
        , APPLY_TEST
        , MAKE_APPLY_NAME
        )
}
#endif

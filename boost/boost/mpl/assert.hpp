
#ifndef BOOST_MPL_ASSERT_HPP_INCLUDED
#define BOOST_MPL_ASSERT_HPP_INCLUDED

// Copyright (c) Aleksey Gurtovoy 2000-2004
//
// Use, modification and distribution are subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy 
// at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/aux_/test/assert.hpp>
#include <boost/preprocessor/cat.hpp>

#define BOOST_MPL_ASSERT_EQUAL(arity, tuple)        MPL_ASSERT_EQUAL(arity, tuple)
#define BOOST_MPL_ASSERT_NOT_EQUAL(arity, tuple)    MPL_ASSERT_NOT_EQUAL(arity, tuple)
#define BOOST_MPL_ASSERT_SAME(arity, tuple)         MPL_ASSERT_SAME(arity, tuple)
#define BOOST_MPL_ASSERT_NOT_SAME(arity, tuple)     MPL_ASSERT_NOT_SAME(arity, tuple)


#if !defined(__BORLANDC__)
template< bool C > struct ASSERT { enum { ASSERTION_FAILED }; };
template<> struct ASSERT<false> {};

#   define BOOST_MPL_MESSAGE( c, msg ) \
    struct BOOST_PP_CAT(__ASSERTION__,msg) : ASSERT<c> {}; \
    enum { n = BOOST_PP_CAT(__ASSERTION__,msg)::ASSERTION_FAILED }\
/**/
#else
template< bool C > struct ASSERTION_FAILED { ASSERTION_FAILED(void const volatile*); };
template<> struct ASSERTION_FAILED<false> {};

#   define BOOST_MPL_MESSAGE( c, msg ) \
    void msg##_( ASSERTION_FAILED<c> = (struct BOOST_PP_CAT(__ASSERTION__,msg)*)(0) ) \
/**/
#endif


#endif // BOOST_MPL_ASSERT_HPP_INCLUDED


#ifndef BOOST_MPL_AUX_TEST_TEST_CASE_HPP_INCLUDED
#define BOOST_MPL_AUX_TEST_TEST_CASE_HPP_INCLUDED

// Copyright (c) Aleksey Gurtovoy 2002-2004
//
// Use, modification and distribution are subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy 
// at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/preprocessor/cat.hpp>

#if 0

#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/enum.hpp> 


#define MPL_AUX_TEST_PARAM_DEF(unused, prefix, i, elem) \
    BOOST_PP_COMMA_IF(i) prefix elem \
/**/

#define MPL_TEST_CASE( name, params_seq ) \
template< \
      BOOST_PP_SEQ_FOR_EACH_I( MPL_AUX_TEST_PARAM_DEF, typename, params_seq ) \
    > \
void name() \
/**/

#define MPL_TEST( test, params_seq ) \
    test< BOOST_PP_SEQ_ENUM(params_seq) >() \
/**/

#else

#   define MPL_TEST_CASE() void BOOST_PP_CAT(test,__LINE__)()

#endif

#endif // BOOST_MPL_AUX_TEST_TEST_CASE_HPP_INCLUDED

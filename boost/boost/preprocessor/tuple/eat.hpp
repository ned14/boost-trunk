#ifndef BOOST_PREPROCESSOR_TUPLE_EAT_HPP
#define BOOST_PREPROCESSOR_TUPLE_EAT_HPP

// Copyright (C) 2001
// Housemarque Oy
// http://www.housemarque.com
//
// Permission to copy, use, modify, sell and distribute this software is
// granted provided this copyright notice appears in all copies. This
// software is provided "as is" without express or implied warranty, and
// with no claim as to its suitability for any purpose.

// See http://www.boost.org for most recent version.

/*! \file

<a href="../../../../boost/preprocessor/tuple/eat.hpp">Click here to see the header.</a>
*/

//! Expands to a macro that eats a tuple of the specified length.
/*!
BOOST_PP_TUPLE_EAT() is designed to be used with BOOST_PP_IF() like
BOOST_PP_EMPTY().

For example,

<PRE>\verbatim
  BOOST_PP_IF(0,BOOST_PP_ENUM_PARAMS,BOOST_PP_TUPLE_EAT(2))(10,P)
\endverbatim</PRE>

expands to nothing.
*/
#define BOOST_PP_TUPLE_EAT(N) BOOST_PP_TUPLE_EAT_DELAY(N)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_TUPLE_EAT_DELAY(N) BOOST_PP_TUPLE##N##_EAT
#define BOOST_PP_TUPLE0_EAT()
#define BOOST_PP_TUPLE1_EAT(A)
#define BOOST_PP_TUPLE2_EAT(A,B)
#define BOOST_PP_TUPLE3_EAT(A,B,C)
#define BOOST_PP_TUPLE4_EAT(A,B,C,D)
#define BOOST_PP_TUPLE5_EAT(A,B,C,D,E)
#define BOOST_PP_TUPLE6_EAT(A,B,C,D,E,F)
#define BOOST_PP_TUPLE7_EAT(A,B,C,D,E,F,G)
#define BOOST_PP_TUPLE8_EAT(A,B,C,D,E,F,G,H)
#endif
#endif

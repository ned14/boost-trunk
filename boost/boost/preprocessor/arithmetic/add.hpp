#ifndef BOOST_PREPROCESSOR_ARITHMETIC_ADD_HPP
#define BOOST_PREPROCESSOR_ARITHMETIC_ADD_HPP

/* Copyright (C) 2001
 * Housemarque Oy
 * http://www.housemarque.com
 *
 * Permission to copy, use, modify, sell and distribute this software is
 * granted provided this copyright notice appears in all copies. This
 * software is provided "as is" without express or implied warranty, and
 * with no claim as to its suitability for any purpose.
 *
 * See http://www.boost.org for most recent version.
 */

/** \file

<a href="../../../../boost/preprocessor/arithmetic/add.hpp">Click here to see the header.</a>
*/

#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/while.hpp>

/** Expands to the sum of X and Y.

For example, BOOST_PP_ADD(4,3) expands to 7 (a single token).
*/
#define BOOST_PP_ADD(X,Y) BOOST_PP_ADD_D(0,X,Y)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_ADD_D(D,X,Y) BOOST_PP_TUPLE_ELEM(2,0,BOOST_PP_WHILE##D(BOOST_PP_ADD_C,BOOST_PP_ADD_F,(X,Y)))
#if !defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__) && __MWERKS__ <= 0x2406
#  define BOOST_PP_ADD_C(D,P) BOOST_PP_TUPLE_ELEM(2,1,P)
#  define BOOST_PP_ADD_F(D,P) (BOOST_PP_INC(BOOST_PP_TUPLE_ELEM(2,0,P)),BOOST_PP_DEC(BOOST_PP_TUPLE_ELEM(2,1,P)))
#else
#  define BOOST_PP_ADD_C(D,P) BOOST_PP_TUPLE2_ELEM1 P
#  define BOOST_PP_ADD_F(D,P) (BOOST_PP_INC(BOOST_PP_TUPLE2_ELEM0 P),BOOST_PP_DEC(BOOST_PP_TUPLE2_ELEM1 P))
#endif
#endif

/** Obsolete. Use BOOST_PP_ADD(). */
#define BOOST_PREPROCESSOR_ADD(X,Y) BOOST_PP_ADD(X,Y)
#endif

#ifndef BOOST_PREPROCESSOR_LIST_FOLD_LEFT_HPP
#define BOOST_PREPROCESSOR_LIST_FOLD_LEFT_HPP

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

#include <boost/preprocessor/list/adt.hpp>
#include <boost/preprocessor/while.hpp>

/** <p>Iterates <code>F(D,P,X)</code> for each element <code>X</code> of the
list <code>L</code> (from the left or the start of the list).</p>

<p>In other words, expands to:</p>

<pre>
  F
  ( D
  , ... F(D, F(D,P,BOOST_PP_LIST_AT(L,0)), BOOST_PP_LIST_AT(L,1)) ...
  , BOOST_PP_LIST_AT(L,BOOST_PP_DEC(BOOST_PP_LIST_SIZE(L))
  )
</pre>

<h3>Note</h3>
<ul>
  <li>Folding, or accumulation, is a very general pattern of computation.
      Most list operations can be implemented in terms of folding.</li>
</ul>

<h3>See</h3>
<ul>
  <li>BOOST_PP_LIST_FOLD_RIGHT()</li>
</ul>

<h3>Uses</h3>
<ul>
  <li>BOOST_PP_WHILE()</li>
</ul>

<h3>Test</h3>
<ul>
  <li><a href="../../test/list_test.cpp">list_test.cpp</a></li>
</ul>
*/
#define BOOST_PP_LIST_FOLD_LEFT(F,P,L) BOOST_PP_LIST_FOLD_LEFT_D(0,F,P,L)

#define BOOST_PP_LIST_FOLD_LEFT_D(D,F,P,L) BOOST_PP_TUPLE_ELEM(3,1,BOOST_PP_WHILE##D(BOOST_PP_LIST_FOLD_LEFT_C,BOOST_PP_LIST_FOLD_LEFT_F,(F,P,L)))
#if !defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__) && __MWERKS__ <= 0x2406
#  define BOOST_PP_LIST_FOLD_LEFT_C(D,X) BOOST_PP_TUPLE_ELEM(3,2,BOOST_PP_TUPLE_ELEM(3,2,X))
#  define BOOST_PP_LIST_FOLD_LEFT_F(D,X) (BOOST_PP_TUPLE_ELEM(3,0,X),BOOST_PP_TUPLE_ELEM(3,0,X)(D,BOOST_PP_TUPLE_ELEM(3,1,X),BOOST_PP_TUPLE_ELEM(3,0,BOOST_PP_TUPLE_ELEM(3,2,X))),BOOST_PP_TUPLE_ELEM(3,1,BOOST_PP_TUPLE_ELEM(3,2,X)))
#elif !defined(BOOST_NO_COMPILER_CONFIG) && defined(_MSC_VER)
#  define BOOST_PP_LIST_FOLD_LEFT_C(D,X) BOOST_PP_TUPLE3_ELEM2 BOOST_PP_TUPLE3_ELEM2 X
#  define BOOST_PP_LIST_FOLD_LEFT_F(D,X) (BOOST_PP_TUPLE_ELEM(3,0,X),BOOST_PP_TUPLE3_ELEM0 X(D,BOOST_PP_TUPLE3_ELEM1 X,BOOST_PP_TUPLE3_ELEM0 BOOST_PP_TUPLE3_ELEM2 X),BOOST_PP_TUPLE3_ELEM1 BOOST_PP_TUPLE3_ELEM2 X)
#else
#  define BOOST_PP_LIST_FOLD_LEFT_C(D,X) BOOST_PP_TUPLE3_ELEM2 BOOST_PP_TUPLE3_ELEM2 X
#  define BOOST_PP_LIST_FOLD_LEFT_F(D,X) (BOOST_PP_TUPLE3_ELEM0 X,BOOST_PP_TUPLE3_ELEM0 X(D,BOOST_PP_TUPLE3_ELEM1 X,BOOST_PP_TUPLE3_ELEM0 BOOST_PP_TUPLE3_ELEM2 X),BOOST_PP_TUPLE3_ELEM1 BOOST_PP_TUPLE3_ELEM2 X)
#endif
#endif

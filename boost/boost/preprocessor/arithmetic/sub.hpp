#ifndef BOOST_PREPROCESSOR_ARITHMETIC_SUB_HPP
#define BOOST_PREPROCESSOR_ARITHMETIC_SUB_HPP

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

#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/while.hpp>

/** <p>Expands to the difference of <code>X</code> and <code>Y</code>.</p>

<p>Both <code>X</code> and <code>Y</code> must expand to integer literals
in the range [0, BOOST_PP_LIMIT_MAG].</p>

<p>For example, <code>BOOST_PP_SUB(4,3)</code> expands to <code>1</code> (a
single token).</p>

<h3>Test</h3>
<ul>
  <li><a href="../../test/arithmetic_test.cpp">arithmetic_test.cpp</a></li>
</ul>
*/
#define BOOST_PP_SUB(X,Y) BOOST_PP_SUB_D(0,X,Y)

/** <p>Can be used inside BOOST_PP_WHILE() (see for an explanation of the D parameter).</p> */
#define BOOST_PP_SUB_D(D,X,Y) BOOST_PP_TUPLE_ELEM(2,0,BOOST_PP_WHILE##D(BOOST_PP_SUB_C,BOOST_PP_SUB_F,(X,Y)))

#define BOOST_PP_SUB_C(D,RC) BOOST_PP_TUPLE_ELEM(2,1,RC)
#define BOOST_PP_SUB_F(D,RC) (BOOST_PP_DEC(BOOST_PP_TUPLE_ELEM(2,0,RC)),BOOST_PP_DEC(BOOST_PP_TUPLE_ELEM(2,1,RC)))
#endif

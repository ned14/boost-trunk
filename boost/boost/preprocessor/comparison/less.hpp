#ifndef BOOST_PREPROCESSOR_COMPARISON_LESS_HPP
#define BOOST_PREPROCESSOR_COMPARISON_LESS_HPP

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

#include <boost/preprocessor/comparison/less_equal.hpp>
#include <boost/preprocessor/comparison/not_equal.hpp>
#include <boost/preprocessor/logical/and.hpp>

/** <P>Expands to 1 if X&lt;Y and 0 otherwise.</P>

<H3>Uses</H3>
<UL>
  <LI>BOOST_PP_WHILE()
</UL>
*/
#define BOOST_PP_LESS(X,Y) BOOST_PP_LESS_D(0,X,Y)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_LESS_D(D,X,Y) BOOST_PP_AND(BOOST_PP_NOT_EQUAL_D(D,X,Y),BOOST_PP_LESS_EQUAL_D(D,X,Y))
#endif

/** <P>Obsolete. Use BOOST_PP_LESS().</P> */
#define BOOST_PREPROCESSOR_LESS(X,Y) BOOST_PP_LESS(X,Y)
#endif

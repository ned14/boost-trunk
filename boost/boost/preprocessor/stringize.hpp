#ifndef BOOST_PREPROCESSOR_STRINGIZE_HPP
#define BOOST_PREPROCESSOR_STRINGIZE_HPP

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

/** <p>Stringizes <code>X</code> after it is macro expanded.</p>

<h3>Example</h3>
<ul>
  <li><a href="../../example/note.c">note.c</a></li>
</ul>
*/
#define BOOST_PP_STRINGIZE(X) BOOST_PP_STRINGIZE_DELAY(X)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_STRINGIZE_DELAY(X) BOOST_PP_DO_STRINGIZE(X)
#define BOOST_PP_DO_STRINGIZE(X) #X
#endif

/** <p>Obsolete. Use BOOST_PP_STRINGIZE().</p> */
#define BOOST_PREPROCESSOR_STRINGIZE(E) BOOST_PP_STRINGIZE(E)
#endif

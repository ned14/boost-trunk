#ifndef BOOST_PREPROCESSOR_ASSERT_MSG_HPP
#define BOOST_PREPROCESSOR_ASSERT_MSG_HPP

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

#include <boost/preprocessor/empty.hpp>
#include <boost/preprocessor/if.hpp>

/** <p>Expands to nothing if <code>C != 0</code> and to <code>MSG</code> if
<code>C == 0</code>.</p> */
#define BOOST_PP_ASSERT_MSG(C,MSG) BOOST_PP_IF(C,BOOST_PP_EMPTY,MSG BOOST_PP_EMPTY)()

/** <p>Obsolete. Use BOOST_PP_ASSERT_MSG().</p> */
#define BOOST_PREPROCESSOR_ASSERT_MSG(C,MSG) BOOST_PP_ASSERT_MSG(C,MSG)
#endif

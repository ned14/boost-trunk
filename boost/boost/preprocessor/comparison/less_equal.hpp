#ifndef BOOST_PREPROCESSOR_COMPARISON_LESS_EQUAL_HPP
#define BOOST_PREPROCESSOR_COMPARISON_LESS_EQUAL_HPP

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

<a href="../../../../boost/preprocessor/comparison/less_equal.hpp">Click here to see the header.</a>
*/

#ifndef BOOST_PREPROCESSOR_ARITHMETIC_SUB_HPP
#  include <boost/preprocessor/arithmetic/sub.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_LOGICAL_NOT_HPP
#  include <boost/preprocessor/logical/not.hpp>
#endif

//! Expands to 1 if X<=Y and 0 otherwise.
#define BOOST_PREPROCESSOR_LESS_EQUAL(X,Y) BOOST_PREPROCESSOR_LESS_EQUAL_I(0,X,Y)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PREPROCESSOR_LESS_EQUAL_I(I,X,Y) BOOST_PREPROCESSOR_NOT(BOOST_PREPROCESSOR_SUB_I(I,X,Y))
#endif /* DOXYGEN_SHOULD_SKIP_THIS */
#endif

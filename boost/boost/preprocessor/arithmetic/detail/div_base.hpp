# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Permission to copy, use, modify, sell and distribute this software is
#  * granted provided this copyright notice appears in all copies. This
#  * software is provided "as is" without express or implied warranty, and
#  * with no claim as to its suitability for any purpose.
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_ARITHMETIC_DETAIL_DIV_BASE_HPP
# define BOOST_PREPROCESSOR_ARITHMETIC_DETAIL_DIV_BASE_HPP
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/arithmetic/sub.hpp>
# include <boost/preprocessor/comparison/less_equal.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_DIV_BASE */
#
# if ~BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_EDG
#    define BOOST_PP_DIV_BASE BOOST_PP_DIV_BASE_I
# else
#    define BOOST_PP_DIV_BASE(x, y) BOOST_PP_DIV_BASE_I(x, y)
# endif
#
# define BOOST_PP_DIV_BASE_I(x, y) BOOST_PP_WHILE(BOOST_PP_DIV_BASE_P, BOOST_PP_DIV_BASE_O, (0, x, y))
#
# if BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_EDG
#    define BOOST_PP_DIV_BASE_P(d, rxy) BOOST_PP_DIV_BASE_P_D(d, BOOST_PP_TUPLE_REM_3 rxy)
#    define BOOST_PP_DIV_BASE_P_D(d, im) BOOST_PP_DIV_BASE_P_I(d, im)
# else
#    define BOOST_PP_DIV_BASE_P(d, rxy) BOOST_PP_DIV_BASE_P_I(d, BOOST_PP_NIL, BOOST_PP_TUPLE_ELEM(3, 1, rxy), BOOST_PP_TUPLE_ELEM(3, 2, rxy))
# endif
#
# define BOOST_PP_DIV_BASE_P_I(d, r, x, y) BOOST_PP_LESS_EQUAL_D(d, y, x)
#
# if BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_EDG
#    define BOOST_PP_DIV_BASE_O(d, rxy) BOOST_PP_DIV_BASE_O_D(d, BOOST_PP_TUPLE_REM_3 rxy)
#    define BOOST_PP_DIV_BASE_O_D(d, im) BOOST_PP_DIV_BASE_O_I(d, im)
# else
#    define BOOST_PP_DIV_BASE_O(d, rxy) BOOST_PP_DIV_BASE_O_I(d, BOOST_PP_TUPLE_ELEM(3, 0, rxy), BOOST_PP_TUPLE_ELEM(3, 1, rxy), BOOST_PP_TUPLE_ELEM(3, 2, rxy))
# endif
#
# define BOOST_PP_DIV_BASE_O_I(d, r, x, y) (BOOST_PP_INC(r), BOOST_PP_SUB_D(d, x, y), y)
#
# /* BOOST_PP_DIV_BASE_D */
#
# if ~BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_EDG
#    define BOOST_PP_DIV_BASE_D BOOST_PP_DIV_BASE_D_I
# else
#    define BOOST_PP_DIV_BASE_D(d, x, y) BOOST_PP_DIV_BASE_D_I(d, x, y)
# endif
#
# define BOOST_PP_DIV_BASE_D_I(d, x, y) BOOST_PP_WHILE_ ## d(BOOST_PP_DIV_BASE_P, BOOST_PP_DIV_BASE_O, (0, x, y))
#
# endif

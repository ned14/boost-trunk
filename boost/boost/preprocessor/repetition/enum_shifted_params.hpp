# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Permission to copy, use, modify, sell and distribute this software is
#  * granted provided this copyright notice appears in all copies. This
#  * software is provided "as is" without express or implied warranty, and
#  * with no claim as to its suitability for any purpose.
#  *
#  * See http://www.boost.org for most recent version.
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# ifndef BOOST_PREPROCESSOR_REPETITION_ENUM_SHIFTED_PARAMS_HPP
# define BOOST_PREPROCESSOR_REPETITION_ENUM_SHIFTED_PARAMS_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/punctuation/comma_if.hpp>
# include <boost/preprocessor/repetition/repeat.hpp>
#
# /* BOOST_PP_ENUM_SHIFTED_PARAMS */
#
# if ~BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_EDG
#    define BOOST_PP_ENUM_SHIFTED_PARAMS(count, param) BOOST_PP_REPEAT(BOOST_PP_DEC(count), BOOST_PP_ENUM_SHIFTED_PARAMS_M, param)
# else
#    define BOOST_PP_ENUM_SHIFTED_PARAMS(count, param) BOOST_PP_ENUM_SHIFTED_PARAMS_D(count, param)
#    define BOOST_PP_ENUM_SHIFTED_PARAMS_D(count, param) BOOST_PP_REPEAT(BOOST_PP_DEC(count), BOOST_PP_ENUM_SHIFTED_PARAMS_M, param)
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_EDG
#    define BOOST_PP_ENUM_SHIFTED_PARAMS_M(z, n, param) BOOST_PP_COMMA_IF(n) BOOST_PP_CAT(param, BOOST_PP_INC(n))
# else
#    define BOOST_PP_ENUM_SHIFTED_PARAMS_M(z, n, param) BOOST_PP_ENUM_SHIFTED_PARAMS_M_D(z, n, param)
#    define BOOST_PP_ENUM_SHIFTED_PARAMS_M_D(z, n, param) BOOST_PP_COMMA_IF(n) BOOST_PP_CAT(param, BOOST_PP_INC(n))
# endif
#
# /* BOOST_PP_ENUM_SHIFTED_PARAMS_Z */
#
# if ~BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_EDG
#    define BOOST_PP_ENUM_SHIFTED_PARAMS_Z(z, count, param) BOOST_PP_REPEAT_ ## z(BOOST_PP_DEC(count), BOOST_PP_ENUM_SHIFTED_PARAMS_M, param)
# else
#    define BOOST_PP_ENUM_SHIFTED_PARAMS_Z(z, count, param) BOOST_PP_ENUM_SHIFTED_PARAMS_Z_D(z, count, param)
#    define BOOST_PP_ENUM_SHIFTED_PARAMS_Z_D(z, count, param) BOOST_PP_REPEAT_ ## z(BOOST_PP_DEC(count), BOOST_PP_ENUM_SHIFTED_PARAMS_M, param)
# endif
#
# endif

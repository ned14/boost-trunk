# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.  Permission to copy, use,        *
#  *     modify, sell, and distribute this software is granted provided       *
#  *     this copyright notice appears in all copies.  This software is       *
#  *     provided "as is" without express or implied warranty, and with       *
#  *     no claim at to its suitability for any purpose.                      *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_LOGICAL_BITNOR_HPP
# define BOOST_PREPROCESSOR_LOGICAL_BITNOR_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_BITNOR */
#
# if BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_IDEAL
#    define BOOST_PP_BITNOR(x, y) BOOST_PP_CAT(BOOST_PP_BITNOR_, BOOST_PP_CAT(x, y))
# else
#    if ~BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_MWCW
#        define BOOST_PP_BITNOR(x, y) BOOST_PP_BITNOR_D(x, y)
#    else
#        define BOOST_PP_BITNOR(x, y) BOOST_PP_EVIL_BITNOR_D((x, y))
#        define BOOST_PP_EVIL_BITNOR_D(par) BOOST_PP_BITNOR_D ## par
#    endif
#    define BOOST_PP_BITNOR_D(x, y) BOOST_PP_BITNOR_ ## x ## y
# endif
#
# define BOOST_PP_BITNOR_00 1
# define BOOST_PP_BITNOR_01 0
# define BOOST_PP_BITNOR_10 0
# define BOOST_PP_BITNOR_11 0
#
# endif

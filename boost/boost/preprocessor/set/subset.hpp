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
# ifndef BOOST_PREPROCESSOR_SET_SUBSET_HPP
# define BOOST_PREPROCESSOR_SET_SUBSET_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/set/first_n.hpp>
# include <boost/preprocessor/set/rest_n.hpp>
#
# /* BOOST_PP_SET_SUBSET */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SET_SUBSET(set, i, len) BOOST_PP_SET_FIRST_N(len, BOOST_PP_SET_REST_N(i, set))
# else
#    define BOOST_PP_SET_SUBSET(set, i, len) BOOST_PP_SET_SUBSET_I(set, i, len)
#    define BOOST_PP_SET_SUBSET_I(set, i, len) BOOST_PP_SET_FIRST_N(len, BOOST_PP_SET_REST_N(i, set))
# endif
#
# endif

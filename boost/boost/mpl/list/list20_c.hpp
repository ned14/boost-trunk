//-----------------------------------------------------------------------------
// boost mpl/list/list20_c.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_LIST_LIST20_C_HPP_INCLUDED
#define BOOST_MPL_LIST_LIST20_C_HPP_INCLUDED

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include "boost/mpl/list/list10_c.hpp"
#endif

#include "boost/mpl/aux_/config/use_preprocessed.hpp"

#if !defined(BOOST_MPL_NO_PREPROCESSED_HEADERS) \
 && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER list20_c.hpp
#   include "boost/mpl/list/aux_/include_preprocessed.hpp"

#else

#   include "boost/preprocessor/iterate.hpp"

namespace boost {
namespace mpl {

#   define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(11, 20, "boost/mpl/list/aux_/numbered_c.hpp"))
#   include BOOST_PP_ITERATE()

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_USE_PREPROCESSED_HEADERS

#endif // BOOST_MPL_LIST_LIST20_C_HPP_INCLUDED

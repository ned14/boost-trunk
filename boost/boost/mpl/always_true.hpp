//-----------------------------------------------------------------------------
// boost mpl/always_true.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MPL_ALWAYS_TRUE_HPP_INCLUDED
#define BOOST_MPL_ALWAYS_TRUE_HPP_INCLUDED

#include "boost/mpl/bool_c.hpp"
#include "boost/mpl/aux_/none.hpp"
#include "boost/mpl/aux_/preprocessor/def_params_tail.hpp"
#include "boost/mpl/limits/arity.hpp"
#include "boost/mpl/aux_/config/dtp.hpp"
#include "boost/config.hpp"

namespace boost {
namespace mpl {

struct always_true
{
    template<
          typename T
        BOOST_MPL_AUX_DEF_PARAMS_TAIL(1, typename T)
        >
    struct apply
        : true_c
    {
    };
};

struct always_false
{
    template<
          typename T0
        BOOST_MPL_AUX_DEF_PARAMS_TAIL(1, typename T)
        >
    struct apply
        : false_c
    {
    };
};

#if defined(BOOST_NO_DEFAULT_TEMPLATE_PARAMETERS_IN_NESTED_TEMPLATES)

namespace aux {

template< long N >
struct arity< always_true, N >
{
    BOOST_STATIC_CONSTANT(long
        , value = BOOST_MPL_METAFUNCTION_MAX_ARITY
        );
};

template< long N >
struct arity< always_false, N >
{
    BOOST_STATIC_CONSTANT(long
        , value = BOOST_MPL_METAFUNCTION_MAX_ARITY
        );
};

} // namespace aux

#endif // #if defined(BOOST_NO_DEFAULT_TEMPLATE_PARAMETERS_IN_NESTED_TEMPLATES)

} // namespace mpl
} // namespace boost

#endif // #ifndef BOOST_MPL_ALWAYS_TRUE_HPP_INCLUDED

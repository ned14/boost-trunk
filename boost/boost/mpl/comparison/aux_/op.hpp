//-----------------------------------------------------------------------------
// boost mpl/comparison/aux_/op.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MPL_COMPARISON_AUX_OP_HPP_INCLUDED
#define BOOST_MPL_COMPARISON_AUX_OP_HPP_INCLUDED

#include "boost/mpl/bool_c.hpp"
#include "boost/mpl/aux_/lambda_spec.hpp"
#include "boost/config.hpp"

#define BOOST_MPL_AUX_COMPARISON_OP(name, shortcut, op) \
namespace boost { namespace mpl { \
template< \
      typename T1 \
    , typename T2 \
    > \
struct name \
{ \
    BOOST_STATIC_CONSTANT(bool, value = (T1::value op T2::value)); \
    typedef bool_c<value> type; \
}; \
\
BOOST_MPL_AUX_LAMBDA_SPEC(2, name) \
\
template< long N > \
struct shortcut \
{ \
    template< typename T > struct apply \
    { \
        BOOST_STATIC_CONSTANT(bool, value = (T::value op N)); \
        typedef bool_c<value> type; \
    }; \
}; \
}} \
/**/

#endif // BOOST_MPL_COMPARISON_AUX_OP_HPP_INCLUDED

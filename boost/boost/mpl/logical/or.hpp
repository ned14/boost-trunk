//-----------------------------------------------------------------------------
// boost mpl/logical/or.hpp header file
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

#ifndef BOOST_MPL_LOGICAL_OR_HPP_INCLUDED
#define BOOST_MPL_LOGICAL_OR_HPP_INCLUDED

#include "boost/mpl/apply_if.hpp"
#include "boost/mpl/bool_c.hpp"
#include "boost/mpl/logical/aux_/op.hpp"

namespace boost {
namespace mpl {

template<
      typename T0
    , typename T1
    >
struct logical_or2
{
    typedef typename apply_if<T0, true_c, T1>::type type;
    BOOST_STATIC_CONSTANT(bool, value = type::value);
};

} // namespace mpl
} // namespace boost

BOOST_MPL_AUX_LOGICAL_OP(logical_or, false_c)

#endif // BOOST_MPL_LOGICAL_OR_HPP_INCLUDED

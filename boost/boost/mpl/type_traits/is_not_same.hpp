//-----------------------------------------------------------------------------
// boost mpl/type_traits/is_not_same.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MPL_TYPE_TRAITS_IS_NOT_SAME_HPP_INCLUDED
#define BOOST_MPL_TYPE_TRAITS_IS_NOT_SAME_HPP_INCLUDED

#include "boost/mpl/placeholder.hpp"
#include "boost/type_traits/same_traits.hpp"
#include "boost/mpl/aux_/lambda_spec.hpp"
#include "boost/config.hpp"

namespace boost {
namespace mpl {

template<
      typename T1
    , typename T2
    >
struct is_not_same
{
    BOOST_STATIC_CONSTANT(bool, value = (!boost::is_same<T1,T2>::value));
    typedef bool_c<value> type;
};

BOOST_MPL_AUX_LAMBDA_SPEC(2, is_not_same)

} // namespace mpl
} // namespace boost

#endif // #ifndef BOOST_MPL_TYPE_TRAITS_IS_NOT_SAME_HPP_INCLUDED

//-----------------------------------------------------------------------------
// boost mpl/functional/logical_not.hpp header file
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

#ifndef BOOST_MPL_FUNCTIONAL_LOGICAL_NOT_HPP_INCLUDED
#define BOOST_MPL_FUNCTIONAL_LOGICAL_NOT_HPP_INCLUDED

#include "boost/mpl/bool_c.hpp"

namespace boost {
namespace mpl {

template< typename T >
struct logical_not
{
 private:
    typedef typename T::type t_;
 
 public:
    BOOST_STATIC_CONSTANT(bool, value = (!t_::value));
    typedef bool_c<value> type;
};

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_FUNCTIONAL_LOGICAL_NOT_HPP_INCLUDED

//-----------------------------------------------------------------------------
// boost mpl/execute.hpp header file
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

#ifndef BOOST_MPL_EXECUTE_HPP_INCLUDED
#define BOOST_MPL_EXECUTE_HPP_INCLUDED

#include "boost/mpl/select_if.hpp"
#include "boost/mpl/bool_c.hpp"
#include "boost/type_traits/conversion_traits.hpp"

namespace boost {
namespace mpl {

namespace aux {

template< typename T, typename P >
inline
T execute_params(P& p, false_c)
{
    return T();
}

template< typename T, typename P >
inline
P& execute_params(P& p, true_c)
{
    return p;
}

} // namespace aux

template< typename T>
inline
void execute()
{
    T();
}

template< typename T, typename P >
inline
void execute(P& param)
{
    typedef bool_c< boost::is_convertible<P,T>::value > c;
    // 'static_cast' needed by GCC 2.95-3
    static_cast<T>(aux::execute_params<T>(param, c()));
}

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_EXECUTE_HPP_INCLUDED

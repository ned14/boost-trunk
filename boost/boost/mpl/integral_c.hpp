//-----------------------------------------------------------------------------
// boost/mpl/intergal_c.hpp header file
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

#ifndef BOOST_MPL_INTEGRAL_C_HPP_INCLUDED
#define BOOST_MPL_INTEGRAL_C_HPP_INCLUDED

#include "boost/mpl/is_reflective.hpp"
#include "boost/config.hpp"

namespace boost {
namespace mpl {

template< typename T, T N >
struct integral_c
#if defined(BOOST_MPL_NO_IS_REFLECTIVE_TRAIT_SPECIALIZATION)
    : aux::reflective_type_base
#endif
{
    BOOST_STATIC_CONSTANT(T, value = N);
    typedef integral_c type;
    typedef T value_type;

    // agurt, 15/jan/02: MSVC6.5 workaround; the compiler gives an ICE 
    // if you write 'N + 1' instead of 'value + 1'    
    typedef integral_c<T, value + 1> next;
    typedef integral_c<T, value - 1> prior;

    // enables uniform function call syntax for families of overloaded 
    // functions that return objects of both arithmetic ('int', 'long',
    // 'double', etc.) and 'integral_c<..>' types (for an example, see 
    // "mpl/example/power.cpp")
    operator T() const { return this->value; } 
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) && (!defined(BOOST_MSVC) && (BOOST_MSVC != 1301))
// 'bool' constant doesn't have 'next'/'prior' members
template< bool C >
struct integral_c<bool, C>
#if defined(BOOST_MPL_NO_IS_REFLECTIVE_TRAIT_SPECIALIZATION)
    : aux::reflective_type_base
#endif
{
    BOOST_STATIC_CONSTANT(bool, value = C);
    typedef integral_c type;
    operator bool() const { return this->value; }
};
#endif

#if !defined(BOOST_MPL_NO_IS_REFLECTIVE_TRAIT_SPECIALIZATION)
template< typename T, T N >
struct is_reflective< integral_c<T,N> >
{
    BOOST_STATIC_CONSTANT(bool, value = true);
    typedef is_reflective type;
};
#endif

} // namespace mpl
} // namespace boost 

#endif // BOOST_MPL_INTEGRAL_C_HPP_INCLUDED

//-----------------------------------------------------------------------------
// boost mpl/bool_c.hpp header file
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

#ifndef BOOST_MPL_BOOL_C_HPP_INCLUDED
#define BOOST_MPL_BOOL_C_HPP_INCLUDED

#include "boost/mpl/is_reflective.hpp"
#include "boost/config.hpp"

namespace boost {
namespace mpl {

template< bool C > struct bool_c
#if defined(BOOST_MPL_NO_IS_REFLECTIVE_TRAIT_SPECIALIZATION)
    : aux::reflective_type_base
#endif
{
    BOOST_STATIC_CONSTANT(bool, value = C);
    typedef bool_c type;
    typedef bool value_type;
    operator bool() const { return this->value; }
};

// shorcuts
typedef bool_c<true> true_c;
typedef bool_c<false> false_c;


#if !defined(BOOST_MPL_NO_IS_REFLECTIVE_TRAIT_SPECIALIZATION)
template< bool C >
struct is_reflective< bool_c<C> >
{
    BOOST_STATIC_CONSTANT(bool, value = true);
    typedef is_reflective type;
};
#endif

} // namespace mpl
} // namespace boost 

#endif // BOOST_MPL_BOOL_C_HPP_INCLUDED

//-----------------------------------------------------------------------------
// boost mpl/is_reflective.hpp header file
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

#ifndef BOOST_MPL_IS_REFLECTIVE_HPP_INCLUDED
#define BOOST_MPL_IS_REFLECTIVE_HPP_INCLUDED

#include "boost/mpl/aux_/config/dependent_nttp.hpp"
#include "boost/config.hpp"

#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
 || defined(BOOST_NO_DEPENDENT_NON_TYPE_PARAMETER_IN_PARTIAL_SPECIALIZATION)

#   define BOOST_MPL_NO_IS_REFLECTIVE_TRAIT_SPECIALIZATION
#	include "boost/type_traits/conversion_traits.hpp"

#endif

namespace boost {
namespace mpl {

#if defined(BOOST_MPL_NO_IS_REFLECTIVE_TRAIT_SPECIALIZATION)

namespace aux {
struct reflective_type_base {};
}

template<
      typename T
    >
struct is_reflective
    : boost::is_convertible<
		  T
		, aux::reflective_type_base
		>
{
};

#else

template<
      typename T
    >
struct is_reflective
{
    BOOST_STATIC_CONSTANT(bool, value = false);
    typedef is_reflective type;
};

#endif // #if defined(BOOST_MPL_USE_REFLECTIVE_TYPE_BASE)

} // namespace mpl
} // namespace boost 

#endif // #ifndef BOOST_MPL_IS_REFLECTIVE_HPP_INCLUDED

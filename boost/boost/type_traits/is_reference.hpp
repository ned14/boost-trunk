
//  (C) Copyright David Abrahams Steve Cleary, Beman Dawes, Howard
//  Hinnant & John Maddock 2000-2002.  Permission to copy, use,
//  modify, sell and distribute this software is granted provided this
//  copyright notice appears in all copies. This software is provided
//  "as is" without express or implied warranty, and with no claim as
//  to its suitability for any purpose.
//
//  See http://www.boost.org for most recent version including documentation.

#ifndef BOOST_TT_IS_REFERENCE_HPP_INCLUDED
#define BOOST_TT_IS_REFERENCE_HPP_INCLUDED

#include "boost/type_traits/config.hpp"

#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#   include "boost/type_traits/detail/yes_no_type.hpp"
#   include "boost/type_traits/detail/wrap.hpp"
#endif

#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) && defined(BOOST_MSVC)
#   include "boost/type_traits/detail/is_function_type_tester.hpp"
#   include "boost/type_traits/detail/false_result.hpp"
#endif

// should be the last #include
#include "boost/type_traits/detail/bool_trait_def.hpp"

namespace boost { 

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

BOOST_TT_AUX_BOOL_TRAIT_DEF1(is_reference,T,false)
BOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC1_1(typename T,is_reference,T&,true)

#if defined(__BORLANDC__)
// these are illegal specialisations; cv-qualifies applied to
// references have no effect according to [8.3.2p1],
// C++ Builder requires them though as it treats cv-qualified
// references as distinct types...
BOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC1_1(typename T,is_reference,T& const,true)
BOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC1_1(typename T,is_reference,T& volatile,true)
BOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC1_1(typename T,is_reference,T& const volatile,true)
#endif

#else

#ifdef BOOST_MSVC
#   pragma warning(push)
#   pragma warning(disable: 4181)
#endif

namespace detail {

using ::boost::type_traits::yes_type;
using ::boost::type_traits::no_type;
using ::boost::type_traits::wrap;

template <typename T> T&(* is_reference_tester1(wrap<T>) )(wrap<T>);
char BOOST_TT_DECL is_reference_tester1(...);

template <typename T> no_type is_reference_tester2(T&(*)(wrap<T>));
yes_type BOOST_TT_DECL is_reference_tester2(...);

#if defined(BOOST_MSVC)

template< typename T >
struct is_reference_or_function_type
{
    BOOST_STATIC_CONSTANT(
        bool, value = sizeof(
            ::boost::detail::is_reference_tester2(
                ::boost::detail::is_reference_tester1(wrap<T>())
                )) == 1
        );
};

template <bool>
struct is_reference_helper
    : ::boost::type_traits::false_result
{
};

template <>
struct is_reference_helper<true>
{
    template< typename T > struct result_
    {
        // if not a function type, then it's indeed a reference
        static T t;
        BOOST_STATIC_CONSTANT(bool, value = 
            sizeof(::boost::type_traits::is_function_type_tester(t)) != 
                sizeof(::boost::type_traits::yes_type)
            );
    };
};

template <typename T>
struct is_reference_impl
    : is_reference_helper<
          ::boost::detail::is_reference_or_function_type<T>::value
        >::template result_<T>
{
};

#else

template< typename T >
struct is_reference_impl
{
    BOOST_STATIC_CONSTANT(
        bool, value = sizeof(
            ::boost::detail::is_reference_tester2(
                ::boost::detail::is_reference_tester1(wrap<T>())
                )) == 1
        );
};

#endif // BOOST_MSVC

} // namespace detail

BOOST_TT_AUX_BOOL_TRAIT_DEF1(is_reference,T,::boost::detail::is_reference_impl<T>::value)
BOOST_TT_AUX_BOOL_TRAIT_SPEC1(is_reference,void,false)
#ifndef BOOST_NO_CV_VOID_SPECIALIZATIONS
BOOST_TT_AUX_BOOL_TRAIT_SPEC1(is_reference,void const,false)
BOOST_TT_AUX_BOOL_TRAIT_SPEC1(is_reference,void volatile,false)
BOOST_TT_AUX_BOOL_TRAIT_SPEC1(is_reference,void const volatile,false)
#endif

#ifdef BOOST_MSVC
#   pragma warning(pop)
#endif

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

} // namespace boost

#include "boost/type_traits/detail/bool_trait_undef.hpp"

#endif // BOOST_TT_IS_REFERENCE_HPP_INCLUDED

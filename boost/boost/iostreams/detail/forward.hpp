// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_FORWARD_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_FORWARD_HPP_INCLUDED   

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif                  
 
#include <boost/iostreams/detail/config/limits.hpp>
#include <boost/iostreams/detail/param_type.hpp>
#include <boost/iostreams/detail/push_params.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

//------Macros for defining forwarding constructors and open overloads--------//
    
//
// Macro: BOOST_IOSTREAMS_DEFINE_FORWARDING_FUNCTIONS(mode, name, helper).
// Description: Defines constructors and overloads of 'open' which construct
//      a device using the given argument list and pass it to 'open_impl'. 
//      Assumes that 'policy_type' is an alias for the device type.
//      Not supported on Intel 7.1 and VC6.5.
//
#define BOOST_IOSTREAMS_FORWARD(class, impl, policy, params, args) \
    class(typename ::boost::iostreams::detail::param_type<policy>::type t params()) \
    { this->impl(::boost::iostreams::detail::wrap(t) args()); } \
    class(const ::boost::reference_wrapper<policy>& ref params()) \
    { this->impl(ref args()); } \
    void open(typename ::boost::iostreams::detail::param_type<policy>::type t params()) \
    { this->impl(::boost::iostreams::detail::wrap(t) args()); } \
    void open(const ::boost::reference_wrapper<policy>& ref params()) \
    { this->impl(ref args()); } \
    BOOST_PP_REPEAT_FROM_TO( \
        1, BOOST_PP_INC(BOOST_IOSTREAMS_MAX_FORWARDING_ARITY), \
        BOOST_IOSTREAMS_FORWARDING_CTOR, (class, impl, policy) \
    ) \
    BOOST_PP_REPEAT_FROM_TO( \
        1, BOOST_PP_INC(BOOST_IOSTREAMS_MAX_FORWARDING_ARITY), \
        BOOST_IOSTREAMS_FORWARDING_FN, (class, impl, policy) \
    ) \
    /**/
#define BOOST_IOSTREAMS_FORWARDING_CTOR(z, n, tuple) \
    template<BOOST_PP_ENUM_PARAMS_Z(z, n, typename U)> \
    BOOST_PP_TUPLE_ELEM(3, 0, tuple) \
    (BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, const U, &u)) \
    { this->BOOST_PP_TUPLE_ELEM(3, 1, tuple) \
      ( BOOST_PP_TUPLE_ELEM(3, 2, tuple) \
        (BOOST_PP_ENUM_PARAMS_Z(z, n, u)) ); } \
    /**/
#define BOOST_IOSTREAMS_FORWARDING_FN(z, n, tuple) \
    template<BOOST_PP_ENUM_PARAMS_Z(z, n, typename U)> \
    void open(BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, const U, &u)) \
    { this->BOOST_PP_TUPLE_ELEM(3, 1, tuple) \
      ( BOOST_PP_TUPLE_ELEM(3, 2, tuple) \
        (BOOST_PP_ENUM_PARAMS_Z(z, n, u)) ); } \
    /**/

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_FORWARD_HPP_INCLUDED

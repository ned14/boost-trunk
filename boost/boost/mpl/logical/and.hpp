//-----------------------------------------------------------------------------
// boost mpl/logical/and.hpp header file
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

#ifndef BOOST_MPL_LOGICAL_AND_HPP_INCLUDED
#define BOOST_MPL_LOGICAL_AND_HPP_INCLUDED

#include "boost/mpl/bool_c.hpp"
#include "boost/mpl/aux_/nested_type_wknd.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"
#include "boost/config.hpp"

namespace boost {
namespace mpl {

namespace aux {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<
      bool C, typename T1, typename T2, typename T3, typename T4
    >
struct logical_and_impl
    : false_c
{
};

template<
      typename T1, typename T2, typename T3, typename T4
    >
struct logical_and_impl<true,T1,T2,T3,T4>
    : logical_and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value,T2,T3,T4,true_c
        >
{
};

template<>
struct logical_and_impl<true,true_c,true_c,true_c,true_c>
    : true_c
{
};

#else

template< bool C > struct logical_and_impl
{
    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : false_c
    {
    };
};

template<> struct logical_and_impl<true>
{
    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : logical_and_impl< BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value >
            ::template result_<T2,T3,T4,true_c>
    {
    };

#if defined(BOOST_MSVC) && BOOST_MSVC == 1300
    template<>
    struct result_<true_c,true_c,true_c,true_c>
        : true_c
    {
    };
};
#else
};

template<>
struct logical_and_impl<true>::result_<true_c,true_c,true_c,true_c>
    : true_c
{
};
#endif // BOOST_MSVC == 1300

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

} // namespace aux

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(T1)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(T2)
    , typename T3 = true_c
    , typename T4 = true_c
    , typename T5 = true_c
    >
struct logical_and
#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    : aux::logical_and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value,T2,T3,T4,T5
        >
#else
    : aux::logical_and_impl< BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value >
        ::template result_<T2,T3,T4,T5>
#endif
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(5,logical_and,(T1,T2,T3,T4,T5))
};

BOOST_MPL_AUX_VOID_SPEC_EXT(2,5,logical_and)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_LOGICAL_AND_HPP_INCLUDED


#ifndef BOOST_MPL_VECTOR_AUX_AT_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_AT_HPP_INCLUDED

// Copyright (c) 2000-04 Aleksey Gurtovoy
//
// Use, modification and distribution are subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy 
// at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include "boost/mpl/at_fwd.hpp"
#include "boost/mpl/vector/aux_/tag.hpp"
#include "boost/mpl/long.hpp"
#include "boost/mpl/aux_/type_wrapper.hpp"
#include "boost/mpl/aux_/value_wknd.hpp"
#include "boost/mpl/aux_/config/typeof.hpp"
#include "boost/mpl/aux_/config/ctps.hpp"

namespace boost {
namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template< typename Vector, long n_ >
struct v_at
{
    typedef long_< (Vector::lower_bound_::value + n_) > index_;
    typedef __typeof__( Vector::item_(index_()) ) type;
};

template<>
struct at_impl< aux::vector_tag >
{
    template< typename Vector, typename N > struct apply
        : aux::wrapped_type< typename v_at<
              Vector
            , BOOST_MPL_AUX_VALUE_WKND(N)::value
            >::type >
    {
    };
};

#else

#   if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
    && !defined(BOOST_NO_NON_TYPE_TEMPLATE_PARTIAL_SPECIALIZATION)

template< typename Vector, long n_ > struct v_at;

template< long S >
struct at_impl< aux::vector_tag<S> >
{
    template< typename Vector, typename N > struct apply
#if !defined(__BORLANDC__)
        : v_at<
              Vector
            , BOOST_MPL_AUX_VALUE_WKND(N)::value
            >
    {
#else
    {
        typedef typename v_at<
              Vector
            , BOOST_MPL_AUX_VALUE_WKND(N)::value
            >::type type;
#endif
    };
};

#   else

namespace aux {

template< long n_ > struct v_at_impl
{
    template< typename V > struct result_;
};

} // namespace aux

template< typename T, long n_ >
struct v_at
    : aux::v_at_impl<n_>::template result_<T>
{
};

#   endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_VECTOR_AUX_AT_HPP_INCLUDED

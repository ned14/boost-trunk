
#ifndef BOOST_MPL_AUX_VECTOR_ITERATOR_HPP_INCLUDED
#define BOOST_MPL_AUX_VECTOR_ITERATOR_HPP_INCLUDED

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

#include "boost/mpl/vector/aux_/at.hpp"
#include "boost/mpl/iterator_tag.hpp"
#include "boost/mpl/plus.hpp"
#include "boost/mpl/minus.hpp"
#include "boost/mpl/advance_fwd.hpp"
#include "boost/mpl/distance_fwd.hpp"
#include "boost/mpl/next.hpp"
#include "boost/mpl/prior.hpp"
#include "boost/mpl/aux_/iterator_names.hpp"
//#include "boost/mpl/aux_/value_wknd.hpp"
#include "boost/mpl/aux_/config/nttp.hpp"
#include "boost/mpl/aux_/config/ctps.hpp"
#include "boost/mpl/aux_/config/workaround.hpp"

namespace boost {
namespace mpl {

template<
      typename Vector
    , BOOST_MPL_AUX_NTTP_DECL(long, n_)
    >
struct v_iter
{
    typedef ra_iter_tag_ category;
    typedef typename v_at<Vector,n_>::type type;

    typedef long_<n_> pos;

#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    enum { 
          next_ = n_ + 1
        , prior_ = n_ - 1
    };
    
    typedef v_iter<Vector,next_> next;
    typedef v_iter<Vector,prior_> prior;

    template< typename Distance > struct BOOST_MPL_AUX_ITERATOR_ADVANCE
    {
        enum { pos_ = n_ + BOOST_MPL_AUX_VALUE_WKND(Distance)::value };
        typedef v_iter<Vector,pos_> type;
    };

    template< typename U > struct BOOST_MPL_AUX_ITERATOR_DISTANCE
        : minus<typename U::pos,pos>
    {
    };
#endif

};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<
      typename Vector
    , BOOST_MPL_AUX_NTTP_DECL(long, n_)
    >
struct next< v_iter<Vector,n_> >
{
    enum { next_ = n_ + 1 };
    typedef v_iter<Vector,next_> type;
};

template<
      typename Vector
    , BOOST_MPL_AUX_NTTP_DECL(long, n_)
    >
struct prior< v_iter<Vector,n_> >
{
    enum { prior_ = n_ - 1 };
    typedef v_iter<Vector,prior_> type;
};

BOOST_MPL_AUX_AGLORITHM_NAMESPACE_BEGIN

template<
      typename Vector
    , BOOST_MPL_AUX_NTTP_DECL(long, n_)
    , typename Distance
    >
struct advance< v_iter<Vector,n_>,Distance>
{
    typedef v_iter<
          Vector
        , (n_ + Distance::value)
        > type;
};

template< 
      typename Vector
    , BOOST_MPL_AUX_NTTP_DECL(long, n_)
    , BOOST_MPL_AUX_NTTP_DECL(long, m_)
    > 
struct distance< v_iter<Vector,n_>, v_iter<Vector,m_> >
{
    BOOST_STATIC_CONSTANT(long, value = (m_ - n_));
#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
    typedef long_<value> type;
#else
    typedef long_<(m_ - n_)> type;
#endif
};

BOOST_MPL_AUX_AGLORITHM_NAMESPACE_END

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_AUX_VECTOR_ITERATOR_HPP_INCLUDED

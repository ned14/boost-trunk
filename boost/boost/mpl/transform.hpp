
#ifndef BOOST_MPL_TRANSFORM_HPP_INCLUDED
#define BOOST_MPL_TRANSFORM_HPP_INCLUDED

// Copyright (c) Aleksey Gurtovoy 2000-2004
// Copyright (c) David Abrahams 2003-2004
//
// Use, modification and distribution are subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy 
// at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/fold.hpp>
#include <boost/mpl/reverse_fold.hpp>
#include <boost/mpl/pair_view.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>

namespace boost { namespace mpl {

namespace aux { 

template< 
      typename Seq
    , typename Op
    , typename In
    >
struct transform1_impl
    : fold< 
          Seq
        , typename In::state
        , bind2< typename In::operation
            , _1
            , bind1<Op, _2>
            > 
        >
{
};

template< 
      typename Seq
    , typename Op
    , typename In
    >
struct reverse_transform1_impl
    : reverse_fold< 
          Seq
        , typename In::state
        , bind2< typename In::operation
            , _1
            , bind1<Op, _2>
            > 
        >
{
};

template< 
      typename Seq1
    , typename Seq2
    , typename Op
    , typename In
    >
struct transform2_impl
    : fold< 
          pair_view<Seq1,Seq2>
        , typename In::state
        , bind2< typename In::operation
            , _1
            , bind2<Op
                , bind1<first<>,_2>
                , bind1<second<>,_2>
                >
            > 
        >
{
};

template< 
      typename Seq1
    , typename Seq2
    , typename Op
    , typename In
    >
struct reverse_transform2_impl
    : reverse_fold< 
          pair_view<Seq1,Seq2>
        , typename In::state
        , bind2< typename In::operation
            , _1
            , bind2<Op
                , bind1<first<>,_2>
                , bind1<second<>,_2>
                >
            > 
        >
{
};

} // namespace aux 

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(3, transform1)
BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(4, transform2)

BOOST_MPL_AUX_AGLORITHM_NAMESPACE_BEGIN

template<
      typename BOOST_MPL_AUX_NA_PARAM(Seq1)
    , typename BOOST_MPL_AUX_NA_PARAM(Seq2OrOperation)
    , typename BOOST_MPL_AUX_NA_PARAM(Operation)
    >
struct transform
  : if_<
          is_na<Operation>
        , transform1<Seq1,Seq2OrOperation>
        , transform2<Seq1,Seq2OrOperation,Operation>
        >::type
{
};

BOOST_MPL_AUX_AGLORITHM_NAMESPACE_END

BOOST_MPL_AUX_NA_ALGORITHM_SPEC(3, transform)

}}

#endif // BOOST_MPL_TRANSFORM_HPP_INCLUDED

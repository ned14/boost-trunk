
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
#include <boost/mpl/fold_backward.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>

namespace boost { namespace mpl {

namespace aux { 

template< 
      typename Sequence
    , typename Operation
    , typename Inserter
    >
struct transform_impl
    : fold< 
          Sequence
        , typename Inserter::state
        , bind2< typename Inserter::operation
            , _1
            , bind1< typename lambda<Operation>::type, _2>
            > 
        >
{
};

template< 
      typename Sequence
    , typename Operation
    , typename Inserter
    >
struct reverse_transform_impl
    : fold_backward< 
          Sequence
        , typename Inserter::state
        , bind2< typename Inserter::operation
            , _1
            , bind1< typename lambda<Operation>::type, _2>
            > 
        >
{
};

} // namespace aux 

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(3, transform)

}}

#endif // BOOST_MPL_TRANSFORM_HPP_INCLUDED


#ifndef BOOST_MPL_COPY_IF_HPP_INCLUDED
#define BOOST_MPL_COPY_IF_HPP_INCLUDED

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
#include <boost/mpl/aux_/copy_if_op.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/protect.hpp>

namespace boost { namespace mpl {

namespace aux {

template<
      typename Sequence
    , typename Predicate
    , typename Inserter
    >
struct copy_if_impl
    : fold<
          Sequence
        , typename Inserter::state
        , protect< aux::copy_if_op<
              typename Inserter::operation
            , typename lambda<Predicate>::type
            > >
        >
{
};

template<
      typename Sequence
    , typename Predicate
    , typename Inserter
    >
struct reverse_copy_if_impl
    : fold_backward<
          Sequence
        , typename Inserter::state
        , protect< aux::copy_if_op<
              typename Inserter::operation
            , typename lambda<Predicate>::type
            > >
        >
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(3, copy_if)

}}

#endif // BOOST_MPL_COPY_IF_HPP_INCLUDED

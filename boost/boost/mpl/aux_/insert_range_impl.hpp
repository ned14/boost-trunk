
#ifndef BOOST_MPL_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED

// Copyright (c) Aleksey Gurtovoy 2000-2004
//
// Use, modification and distribution are subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy 
// at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/reverse_iter_fold.hpp>
#include <boost/mpl/reverse_fold.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/apply_if.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/iter_push_front.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/type_traits/same_traits.hpp>

namespace boost { namespace mpl {

// default implementation; conrete sequences might override it by 
// specializing either the 'insert_range_impl' or the primary 
// 'insert_range' template

namespace aux {

template<
      typename Pos
    , typename Range
    >
struct iter_range_inserter
{
    template< typename Sequence, typename Iterator > struct apply
    {
        typedef typename aux::iter_push_front<
              typename apply_if<
                  is_same<Pos,typename Iterator::next>
                , reverse_fold< Range, Sequence, push_front<_,_> >
                , identity<Sequence>
                >::type
            , Iterator
            >::type type;
    };
};

} // namespace aux


template< typename Tag >
struct insert_range_impl
{
    template<
          typename Sequence
        , typename Pos
        , typename Range
        >
    struct apply
        : iter_fold_backward<
              Sequence
            , typename clear<Sequence>::type
            , aux::iter_range_inserter<Pos,Range>
            >
    {
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(3,insert_range_impl)

}}

#endif // BOOST_MPL_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED

//-----------------------------------------------------------------------------
// boost mpl/insert_range.hpp header file
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

#ifndef BOOST_MPL_INSERT_RANGE_HPP_INCLUDED
#define BOOST_MPL_INSERT_RANGE_HPP_INCLUDED

#include "boost/mpl/iter_fold.hpp"
#include "boost/mpl/fold_reverse.hpp"
#include "boost/mpl/clear.hpp"
#include "boost/mpl/push_front.hpp"
#include "boost/mpl/identity.hpp"
#include "boost/mpl/apply_if.hpp"
#include "boost/mpl/sequence_tag.hpp"
#include "boost/mpl/type_traits/is_same.hpp"
#include "boost/mpl/aux_/lambda_spec.hpp"
#include "boost/mpl/aux_/iter_push_front.hpp"

#include "boost/type_traits/same_traits.hpp"

namespace boost {
namespace mpl {

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
                  is_same<Pos,Iterator>
                , fold_reverse< Range, Sequence, push_front<_,_> >
                , identity<Sequence>
                >::type
            , Iterator
            >::type type;
    };
};

} // namespace aux


template< typename Tag >
struct insert_algorithm_traits
{
    template<
          typename Sequence
        , typename Pos
        , typename Range
        >
    struct algorithm
    {
        typedef typename iter_fold<
              Sequence
            , typename clear<Sequence>::type
            , project1st<_,_>
            , aux::iter_range_inserter<Pos,T>
            >::type type;
    };
};

template<
      typename Sequence
    , typename Pos
    , typename Range
    >
struct insert_range
{
 private:
    typedef typename sequence_tag<Sequence>::type tag_;
 
 public:
    typedef typename insert_range_algorithm_traits<tag_>
        ::template algorithm< Sequence,Pos,Range >::type type;
};

BOOST_MPL_AUX_LAMBDA_SPEC(3, insert_range)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_INSERT_RANGE_HPP_INCLUDED

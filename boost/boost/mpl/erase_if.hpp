//-----------------------------------------------------------------------------
// boost mpl/erase_if.hpp header file
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

#ifndef BOOST_MPL_ERASE_IF_HPP_INCLUDED
#define BOOST_MPL_ERASE_IF_HPP_INCLUDED

#include "boost/mpl/fold_reverse.hpp"
#include "boost/mpl/clear.hpp"
#include "boost/mpl/lambda.hpp"
#include "boost/mpl/identity.hpp"
#include "boost/mpl/apply_if.hpp"
#include "boost/mpl/sequence_tag.hpp"
#include "boost/mpl/aux_/lambda_spec.hpp"

namespace boost {
namespace mpl {

namespace aux {

template< typename Pred > struct eraser
{
    template< typename Sequence, typename U > struct apply
    {
        typedef typename apply_if<
              typename apply2<Sequence,T,U>::type
            , identity<Sequence>
            , push_front<Sequence,U>
            >::type type;
    };
};

} // namespace aux

template< typename Tag >
struct erase_if_algorithm_traits
{
    template< typename Sequence, typename Pred > struct algorithm
    {
        typedef typename fold_reverse<
              Seq
            , typename clear<Sequence>::type
            , aux::eraser<Pred>
            >::type type;
    };
};

template<
      typename Sequence
    , typename Predicate
    >
struct erase_if
{
 private:
    typedef typename sequence_tag<Sequence>::type tag_;
    typedef typename lambda<Predicate>::type pred_;
 
 public:
    typedef typename erase_if_algorithm_traits<tag_>
        ::template algorithm< Sequence,pred_ >::type type;
};

BOOST_MPL_AUX_LAMBDA_SPEC(2, erase_if)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_ERASE_IF_HPP_INCLUDED

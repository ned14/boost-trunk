//-----------------------------------------------------------------------------
// boost mpl/iter_fold_if.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy, David Abrahams
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MPL_ITER_FOLD_IF_HPP_INCLUDED
#define BOOST_MPL_ITER_FOLD_IF_HPP_INCLUDED

#include "boost/mpl/aux_/iter_fold_if.hpp"
#include "boost/mpl/type_traits/is_not_same.hpp"
#include "boost/mpl/logical/and.hpp"
#include "boost/mpl/logical/not.hpp"
#include "boost/mpl/begin_end.hpp"
#include "boost/mpl/project1st.hpp"
#include "boost/mpl/lambda.hpp"
#include "boost/mpl/bind.hpp"
#include "boost/mpl/apply.hpp"
#include "boost/mpl/aux_/lambda_spec.hpp"

namespace boost {
namespace mpl {

namespace aux {

template< 
      typename LastIterator
    , typename Pred
    >
struct fold_if_pred
{
    template<
          typename State
        , typename Iterator
        >
    struct apply
    {
        typedef typename logical_and2<
              is_not_same<Iterator,LastIterator>
            , apply2< Pred,State,Iterator >
            >::type type;
    };
};

} // namespace aux

template<
      typename Sequence
    , typename State
    , typename ForwardOp
    , typename ForwardPredicate
    , typename BackwardOp = project1st<_,_>
    , typename BackwardPredicate = ForwardPredicate
    >
struct iter_fold_if
{
 private:
    typedef typename begin<Sequence>::type first_;
    typedef typename end<Sequence>::type last_;

    typedef aux::fold_if_pred<
          last_
        , typename lambda<ForwardPredicate>::type
        > forward_pred_;

    typedef aux::fold_if_pred<
          last_
        , typename lambda<BackwardPredicate>::type
        > backward_pred_;

 public:
    typedef typename aux::iter_fold_if<
          first_
        , State
        , typename lambda<ForwardOp>::type
        , forward_pred_
        , typename lambda<BackwardOp>::type
        , backward_pred_
        >::state type;
};

#if defined(__MWERKS__) && (__MWERKS__ <= 0x3000)
BOOST_MPL_AUX_LAMBDA_SPEC(4, iter_fold_if)
BOOST_MPL_AUX_LAMBDA_SPEC(5, iter_fold_if)
#endif

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_ITER_FOLD_IF_HPP_INCLUDED

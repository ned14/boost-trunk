//-----------------------------------------------------------------------------
// boost mpl/aux_/iter_fold_if.hpp header file
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

#ifndef BOOST_MPL_AUX_ITER_FOLD_IF_HPP_INCLUDED
#define BOOST_MPL_AUX_ITER_FOLD_IF_HPP_INCLUDED

#include "boost/mpl/limits/unrolling.hpp"
#include "boost/mpl/identity.hpp"
#include "boost/mpl/next.hpp"
#include "boost/mpl/bool_c.hpp"
#include "boost/mpl/apply.hpp"
#include "boost/mpl/select_if.hpp"

#include "boost/preprocessor/arithmetic/sub.hpp"
#include "boost/preprocessor/repeat.hpp"
#include "boost/preprocessor/inc.hpp"
#include "boost/preprocessor/dec.hpp"
#include "boost/preprocessor/cat.hpp"

namespace boost {
namespace mpl {
namespace aux {

template< typename Iterator, typename State >
struct iter_fold_null_step
{
    typedef State state;
    typedef Iterator iterator;
};

template<bool>
struct iter_fold_step_impl
{
    template<
          typename Iterator
        , typename State
        , typename StateOp
        , typename IteratorOp
        >
    struct result_
    {
        typedef typename apply2< StateOp,State,Iterator >::type state;
        typedef typename IteratorOp::type iterator;
        typedef false_c is_last;
    };
};

template<>
struct iter_fold_step_impl<false>
{
    template<
          typename Iterator
        , typename State
        , typename StateOp
        , typename IteratorOp
        >
    struct result_
    {
        typedef State state;
        typedef Iterator iterator;
        typedef true_c is_last;
    };
};

#if defined(__GNUC__) && (__GNUC__ == 2) && (__GNUC_MINOR__ <= 95)
template<
      typename F
    , typename T1
    , typename T2
    >
struct apply2_result
    : apply2<F,T1,T2>::type
{
};

template<
      typename Iterator
    , typename State
    , typename ForwardOp
    , typename Predicate
    >
struct iter_fold_forward_step
    : iter_fold_step_impl< apply2_result<Predicate,State,Iterator>::value >
        ::template result_< Iterator,State,ForwardOp,next<Iterator> >
{
};

template<
      typename Iterator
    , typename State
    , typename BackwardOp
    , typename Predicate
    >
struct iter_fold_backward_step
    : iter_fold_step_impl< apply2_result<Predicate,State,Iterator>::value >
        ::template result_< Iterator,State,BackwardOp,identity<Iterator> >
{
};

#else

template<
      typename Iterator
    , typename State
    , typename ForwardOp
    , typename Predicate
    , typename IsLast = typename apply2<Predicate,State,Iterator>::type
    >
struct iter_fold_forward_step
    : iter_fold_step_impl< IsLast::value >
        ::template result_< Iterator,State,ForwardOp,next<Iterator> >
{
};

template<
      typename Iterator
    , typename State
    , typename BackwardOp
    , typename Predicate
    , typename IsLast = typename apply2<Predicate,State,Iterator>::type
    >
struct iter_fold_backward_step
    : iter_fold_step_impl< IsLast::value >
        ::template result_< Iterator,State,BackwardOp,identity<Iterator> >
{
};

#endif // #if defined(__GNUC__) && (__GNUC__ == 2) && (__GNUC_MINOR__ <= 95)


// local macros, #undef-ined at the end of the header

#define AUX_ITER_FOLD_FORWARD_STEP(i, unused) \
    typedef iter_fold_forward_step< \
          typename BOOST_PP_CAT(forward_step,i)::iterator \
        , typename BOOST_PP_CAT(forward_step,i)::state \
        , ForwardOp \
        , ForwardPredicate \
        > BOOST_PP_CAT(forward_step, BOOST_PP_INC(i)); \
/**/

#define AUX_ITER_FOLD_BACKWARD_STEP_FUNC(i) \
    typedef iter_fold_backward_step< \
          typename BOOST_PP_CAT(forward_step,BOOST_PP_DEC(i))::iterator \
        , typename BOOST_PP_CAT(backward_step,i)::state \
        , BackwardOp \
        , BackwardPredicate \
        > BOOST_PP_CAT(backward_step,BOOST_PP_DEC(i)); \
/**/

#define AUX_ITER_FOLD_BACKWARD_STEP(i, unused) \
    AUX_ITER_FOLD_BACKWARD_STEP_FUNC( \
        BOOST_PP_SUB(BOOST_MPL_LIMIT_UNROLLING,i) \
        ) \
/**/

#define AUX_LAST_FORWARD_STEP \
    BOOST_PP_CAT(forward_step, BOOST_MPL_LIMIT_UNROLLING) \
/**/

#define AUX_LAST_BACKWARD_STEP \
    BOOST_PP_CAT(backward_step, BOOST_MPL_LIMIT_UNROLLING) \
/**/

template<
      typename Iterator
    , typename State
    , typename ForwardOp
    , typename ForwardPredicate
    , typename BackwardOp
    , typename BackwardPredicate
    >
struct iter_fold_if
{
 private:
    typedef iter_fold_null_step<Iterator,State> forward_step0;
    BOOST_PP_REPEAT(
          BOOST_MPL_LIMIT_UNROLLING
        , AUX_ITER_FOLD_FORWARD_STEP
        , unused
        )
    
    typedef typename select_if<
          typename AUX_LAST_FORWARD_STEP::is_last
        , iter_fold_null_step<
              typename AUX_LAST_FORWARD_STEP::iterator
            , typename AUX_LAST_FORWARD_STEP::state
            >
        , iter_fold_if<
              typename AUX_LAST_FORWARD_STEP::iterator
            , typename AUX_LAST_FORWARD_STEP::state
            , ForwardOp
            , ForwardPredicate
            , BackwardOp
            , BackwardPredicate
            >
        >::type AUX_LAST_BACKWARD_STEP;

    BOOST_PP_REPEAT(
          BOOST_MPL_LIMIT_UNROLLING
        , AUX_ITER_FOLD_BACKWARD_STEP
        , unused
        )

 public:
    typedef typename backward_step0::state state;
    typedef typename AUX_LAST_BACKWARD_STEP::iterator iterator;
};

#undef AUX_LAST_BACKWARD_STEP
#undef AUX_LAST_FORWARD_STEP
#undef AUX_ITER_FOLD_BACKWARD_STEP
#undef AUX_ITER_FOLD_BACKWARD_STEP_FUNC
#undef AUX_ITER_FOLD_FORWARD_STEP

} // namespace aux
} // namespace mpl
} // namespace boost

#endif // #ifndef BOOST_MPL_AUX_ITER_FOLD_IF_HPP_INCLUDED

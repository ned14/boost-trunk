//-----------------------------------------------------------------------------
// boost mpl/reverse_iter_fold.hpp header file
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

#ifndef BOOST_MPL_ITER_FOLD_BACKWARD_HPP_INCLUDED
#define BOOST_MPL_ITER_FOLD_BACKWARD_HPP_INCLUDED

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/O1_size.hpp>
#include <boost/mpl/arg.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/aux_/reverse_iter_fold_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost {
namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(State)
    , typename BOOST_MPL_AUX_NA_PARAM(BackwardOp)
    , typename ForwardOp = arg<1>
    >
struct reverse_iter_fold
{
    typedef typename aux::reverse_iter_fold_impl<
          ::boost::mpl::O1_size<Sequence>::value
        , typename begin<Sequence>::type
        , typename end<Sequence>::type
        , State
        , typename lambda<BackwardOp>::type
        , typename lambda<ForwardOp>::type
        >::state type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , reverse_iter_fold
        , (Sequence,State,BackwardOp,ForwardOp)
        )
};

BOOST_MPL_AUX_NA_SPEC(3, reverse_iter_fold)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_ITER_FOLD_BACKWARD_HPP_INCLUDED

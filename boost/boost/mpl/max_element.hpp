//-----------------------------------------------------------------------------
// boost mpl/max_element.hpp header file
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

#ifndef BOOST_MPL_MAX_ELEMENT_HPP_INCLUDED
#define BOOST_MPL_MAX_ELEMENT_HPP_INCLUDED

#include "boost/mpl/iter_fold.hpp"
#include "boost/mpl/begin_end.hpp"
#include "boost/mpl/select_if.hpp"
#include "boost/mpl/apply.hpp"
#include "boost/mpl/aux_/lambda_spec.hpp"

namespace boost {
namespace mpl {

namespace aux {

template< typename Predicate >
struct select_max
{
    template< typename OldIterator, typename Iterator >
    struct apply
    {
        typedef typename apply2<
              Predicate
            , typename OldIterator::type
            , typename Iterator::type
            >::type condition_;

        typedef typename select_if<
              condition_
            , Iterator
            , OldIterator
            >::type type;
    };
};

} // namespace aux 

template<
      typename Sequence
    , typename Predicate
    >
struct max_element
{
    typedef typename iter_fold<
          Sequence
        , typename begin<Sequence>::type
        , aux::select_max<Predicate>
        >::type type;
};

BOOST_MPL_AUX_LAMBDA_SPEC(2, max_element)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_MAX_ELEMENT_HPP_INCLUDED

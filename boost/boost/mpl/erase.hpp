//-----------------------------------------------------------------------------
// boost mpl/erase.hpp header file
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

#ifndef BOOST_MPL_ERASE_HPP_INCLUDED
#define BOOST_MPL_ERASE_HPP_INCLUDED

#include "boost/mpl/iter_fold.hpp"
#include "boost/mpl/clear.hpp"
#include "boost/mpl/identity.hpp"
#include "boost/mpl/protect.hpp"
#include "boost/mpl/apply_if.hpp"
#include "boost/mpl/sequence_tag.hpp"
#include "boost/mpl/aux_/lambda_spec.hpp"
#include "boost/mpl/aux_/iter_push_front.hpp"
#include "boost/mpl/type_traits/is_same.hpp"

namespace boost {
namespace mpl {

namespace aux {

template< typename Pos > struct iter_eraser
{
    template< typename Sequence, typename Iterator > struct apply
    {
        typedef typename apply_if<
              is_same<Pos,Iterator>
            , identity<Sequence>
            , aux::iter_push_front<Sequence,Iterator>
            >::type type;
    };
};

} // namespace aux


template< typename Tag >
struct erase_algorithm_traits
{
    template<
          typename Sequence
        , typename Pos
        >
    struct algorithm
    {
        typedef typename iter_fold<
              Sequence
            , typename clear<Sequence>::type
            , project1st<_,_>
            , protect< aux::iter_eraser<Pos> >
            >::type type;
    };
};

template<
      typename Sequence
    , typename Pos
    >
struct erase
{
 private:
    typedef typename sequence_tag<Sequence>::type tag_;
 
 public:
    typedef typename erase_algorithm_traits<tag_>
        ::template algorithm< Sequence,Pos >::type type;
};

BOOST_MPL_AUX_LAMBDA_SPEC(2, erase)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_ERASE_HPP_INCLUDED

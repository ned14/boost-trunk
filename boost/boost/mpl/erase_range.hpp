//-----------------------------------------------------------------------------
// boost mpl/erase_range.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Eric Friedman, Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MPL_ERASE_RANGE_HPP_INCLUDED
#define BOOST_MPL_ERASE_RANGE_HPP_INCLUDED

#include "boost/mpl/clear.hpp"
#include "boost/mpl/push_front.hpp"
#include "boost/mpl/copy_backward.hpp"
#include "boost/mpl/iterator_range.hpp"
#include "boost/mpl/aux_/lambda_spec.hpp"

namespace boost {
namespace mpl {

template< typename Tag >
struct erase_range_algorithm_traits
{
    template<
          typename Sequence
        , typename First
        , typename Last
        >
    struct algorithm
    {
     private:
        // 1st half: [begin, first)
        typedef iterator_range<
              typename begin<Sequence>::type
            , First
            > first_half_;

        // 2nd half: [last, end) ... that is, [last + 1, end)
        typedef iterator_range<
              Last
            , typename end<Sequence>::type
            > second_half_;

        typedef typename copy_backward<
              second_half_
            , push_front<_,_>
            , typename clear<Sequence>::type
            >::type half_sequence_;

     public:
        typedef typename copy_backward<
              first_half_
            , push_front<_,_>
            , half_sequence_
            >::type type;
    };

};

template<
      typename Sequence
    , typename First
    , typename Last
    >
struct erase_range
{
 private:
    typedef typename sequence_tag<Sequence>::type tag_;

 public:
    typedef typename erase_range_algorithm_traits<tag_>
        ::template algorithm< Sequence,First,Last >::type type;
};

BOOST_MPL_AUX_LAMBDA_SPEC(3, erase_range)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_ERASE_RANGE_HPP_INCLUDED

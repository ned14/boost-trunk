//-----------------------------------------------------------------------------
// boost mpl/erase_range.hpp header file
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

#ifndef BOOST_MPL_ERASE_RANGE_HPP_INCLUDED
#define BOOST_MPL_ERASE_RANGE_HPP_INCLUDED

#include "boost/mpl/clear.hpp"
#include "boost/mpl/iter_fold.hpp"
#include "boost/mpl/pair.hpp"
#include "boost/mpl/project1st.hpp"
#include "boost/mpl/select_if.hpp"
#include "boost/mpl/type_traits/is_same.hpp"
#include "boost/mpl/aux_/lambda_spec.hpp"
#include "boost/mpl/aux_/iter_push_front.hpp"
#include "boost/mpl/aux_/apply_1st.hpp"

namespace boost {
namespace mpl {

namespace aux {

template< typename First, typename Last > struct range_eraser;

template<
      typename First
    , typename Last
    >
struct range_1st_part_copier
{
    template< typename Sequence, typename Iterator > struct apply
    {
        typedef typename Sequence::type seq_;
        typedef typename select_if<
              is_same<Iterator,First>
            , pair< range_eraser<First,Last>, seq_ >
            , pair<
                  range_1st_part_copier<First,Last>
                , aux::iter_push_front< seq_,Iterator >
                >
            >::type type;
    };
};

struct range_2nd_part_copier
{
    template< typename Sequence, typename Iterator > struct apply
    {
        typedef typename Sequence::type seq_;
        typedef pair<
              range_2nd_part_copier
            , aux::iter_push_front< seq_,Iterator >
            > type;
    };
};

template<
      typename First
    , typename Last
    >
struct range_eraser
{
    template< typename Sequence, typename Iterator > struct apply
    {
        typedef typename select_if<
              boost::is_same<Iterator,Last>
            , pair<
                  range_1st_part_copier<First,Last>
                , aux::iter_push_front< Sequence,Iterator >
                >
            , pair< range_eraser<First,Last>, Sequence >
            >::type type;
    };
};

} // namespace aux

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
        typedef typename iter_fold<
              Sequence
            , pair<
                  aux::range_1st_part_copier<First,Last>
                , clear<Sequence>
                >
            , project1st<_,_>
            , aux::apply_1st
            >::type pair_;

     public:
        typedef typename pair_::second type;
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

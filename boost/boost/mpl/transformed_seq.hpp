//-----------------------------------------------------------------------------
// boost mpl/transformed_seq.hpp header file
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

#ifndef BOOST_MPL_TRANSFORMED_SEQ_HPP_INCLUDED
#define BOOST_MPL_TRANSFORMED_SEQ_HPP_INCLUDED

#include "boost/mpl/iterator_range.hpp"
#include "boost/mpl/begin_end.hpp"
#include "boost/mpl/apply.hpp"

namespace boost {
namespace mpl {

template< typename Iterator, typename F >
struct transform_iter
{
    typedef Iterator base;
    typedef typename base::category category;
    typedef transform_iter<typename base::next,F> next;
    
    typedef typename apply1<
          F
        , typename base::type
        >::type type;
};

template< typename Sequence, typename F >
struct transformed_seq
    : iterator_range<
          transform_iter< typename begin<Sequence>::type,F >
        , transform_iter< typename end<Sequence>::type,F >
        >
{
};

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_TRANSFORMED_SEQ_HPP_INCLUDED

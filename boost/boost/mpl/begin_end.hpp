//-----------------------------------------------------------------------------
// boost mpl/begin_end.hpp header file
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

#ifndef BOOST_MPL_BEGIN_END_HPP_INCLUDED
#define BOOST_MPL_BEGIN_END_HPP_INCLUDED

#include "boost/mpl/sequence_tag.hpp"
#include "boost/mpl/aux_/lambda_spec.hpp"

namespace boost {
namespace mpl {

template< typename Tag >
struct begin_algorithm_traits
{
    template< typename Sequence > struct algorithm
    {
        typedef typename Sequence::begin type;
    };
};

template< typename Tag >
struct end_algorithm_traits
{
    template< typename Sequence > struct algorithm
    {
        typedef typename Sequence::end type;
    };
};

template< typename Sequence >
struct begin
{
 private:
    typedef typename sequence_tag<Sequence>::type tag_;
 
 public:
    typedef typename begin_algorithm_traits<tag_>
        ::template algorithm< Sequence >::type type;
};

template< typename Sequence >
struct end
{
 private:
    typedef typename sequence_tag<Sequence>::type tag_;
 
 public:
    typedef typename end_algorithm_traits<tag_>
        ::template algorithm< Sequence >::type type;
};

BOOST_MPL_AUX_LAMBDA_SPEC(1, begin)
BOOST_MPL_AUX_LAMBDA_SPEC(1, end)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_BEGIN_END_HPP_INCLUDED

//-----------------------------------------------------------------------------
// boost mpl/back.hpp header file
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

#ifndef BOOST_MPL_BACK_HPP_INCLUDED
#define BOOST_MPL_BACK_HPP_INCLUDED

#include "boost/mpl/begin_end.hpp"
#include "boost/mpl/sequence_tag.hpp"
#include "boost/mpl/identity.hpp"
#include "boost/mpl/is_reflective.hpp"
#include "boost/mpl/aux_/lambda_spec.hpp"

namespace boost {
namespace mpl {

template< typename Tag >
struct back_algorithm_traits
{
    template< typename Sequence > struct algorithm
    {
     private:
        typedef typename end<Sequence>::type iter_;
        typedef typename iter_::prior last_;
     
     public:
        typedef typename last_::type type;
    };
};

namespace aux {

template< typename Sequence >
struct back_impl
{
 private:
    typedef typename sequence_tag<Sequence>::type tag_;
    typedef typename back_algorithm_traits<tag_>
        ::template algorithm< Sequence >::type result_;
 public:
    typedef typename apply_if<
          is_reflective<result_>
        , result_
        , identity<result_>
        >::type type;
};

} // namespace aux

template< typename Sequence >
struct back
    : aux::back_impl<Sequence>::type
{
};

BOOST_MPL_AUX_LAMBDA_SPEC(1, back)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_BACK_HPP_INCLUDED

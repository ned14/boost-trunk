//-----------------------------------------------------------------------------
// boost mpl/distance.hpp header file
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

#ifndef BOOST_MPL_DISTANCE_HPP_INCLUDED
#define BOOST_MPL_DISTANCE_HPP_INCLUDED

#include "boost/mpl/aux_/iter_distance.hpp"
#include "boost/mpl/aux_/is_random_access.hpp"
#include "boost/mpl/iter_fold.hpp"
#include "boost/mpl/iterator_range.hpp"
#include "boost/mpl/integral_c.hpp"
#include "boost/mpl/next.hpp"
#include "boost/mpl/aux_/lambda_spec.hpp"
#include "boost/config.hpp"

namespace boost {
namespace mpl {

namespace aux {

// random-access iterators
template< bool > struct distance_impl
{
    template< typename First, typename Last > struct result_
        : aux::iter_distance<First,Last>
    {
    };
};

// forward/bidirectional iterators
template<> struct distance_impl<false>
{
    template< typename First, typename Last > struct result_
    {
        typedef typename iter_fold<
              iterator_range<First,Last>
            , integral_c<unsigned long, 0>
            , next<_>
            >::type type;
        
        BOOST_STATIC_CONSTANT(unsigned long, value = type::value);
    };
};

} // namespace aux

template<
      typename First
    , typename Last
    >
struct distance
    : aux::distance_impl<
          aux::is_random_access<First>::value
        >::template result_<First,Last>
{
};

BOOST_MPL_AUX_LAMBDA_SPEC(2, distance)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_DISTANCE_HPP_INCLUDED

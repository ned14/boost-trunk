//-----------------------------------------------------------------------------
// boost mpl/advance.hpp header file
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

#ifndef BOOST_MPL_ADVANCE_HPP_INCLUDED
#define BOOST_MPL_ADVANCE_HPP_INCLUDED

#include "boost/mpl/aux_/advance_forward.hpp"
#include "boost/mpl/aux_/iter_advance.hpp"
#include "boost/mpl/aux_/is_random_access.hpp"
#include "boost/mpl/arithmetic/negate.hpp"
#include "boost/mpl/comparison/less.hpp"
#include "boost/mpl/next.hpp"
#include "boost/mpl/prior.hpp"
#include "boost/mpl/integral_c.hpp"
#include "boost/mpl/apply_if.hpp"
#include "boost/mpl/apply.hpp"
#include "boost/mpl/aux_/lambda_spec.hpp"

namespace boost {
namespace mpl {

namespace aux {

// random-access iterators
template< bool > struct advance_impl
{
    template< typename Iterator, typename N > struct result_
        : aux::iter_advance<Iterator,N>
    {
    };
};

// forward/bidirectional iterators
template<> struct advance_impl<false>
{
    template< typename Iterator, typename N > struct result_
    {
     private:
        typedef less< N, integral_c<long,0> > less_0_;
        typedef typename select_if<less_0_, negate<N>, N>::type N_;
        typedef typename select_if<less_0_, prior<_>, next<_> >::type op_;

     public:
        typedef typename aux::advance_forward<N_::value>
            ::template result_<Iterator,op_>::type type;
    };
};

} // namespace aux

template<
      typename Iterator
    , typename N
    >
struct advance
    : aux::advance_impl<
          aux::is_random_access<Iterator>::value
        >::template result_<Iterator,N>
{
};

template<
      typename Iterator
    , long N
    >
struct advance_c
    : aux::advance_impl<
          aux::is_random_access<Iterator>::value
        >::template result_< Iterator,integral_c<long,N> >
{
};

BOOST_MPL_AUX_LAMBDA_ARITY_SPEC(2, advance)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_ADVANCE_HPP_INCLUDED

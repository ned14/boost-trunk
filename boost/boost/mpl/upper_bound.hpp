//-----------------------------------------------------------------------------
// boost mpl/upper_bound.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MPL_UPPER_BOUND_HPP_INCLUDED
#define BOOST_MPL_UPPER_BOUND_HPP_INCLUDED

#include "boost/mpl/size.hpp"
#include "boost/mpl/advance.hpp"
#include "boost/mpl/begin_end.hpp"
#include "boost/mpl/integral_c.hpp"
#include "boost/mpl/lambda.hpp"
#include "boost/mpl/apply_if.hpp"
#include "boost/mpl/apply.hpp"
#include "boost/mpl/aux_/lambda_spec.hpp"

namespace boost {
namespace mpl {

namespace aux {

// agurt, 31/mar/02: to workwaround VC7.0 early template instantiation bug
template< long Distance >
struct upper_bound_step;

template<>
struct upper_bound_step<0>
{
    template<
          typename Predicate
        , typename T
        , typename DeferredIterator
        >
    struct result_
    {
        typedef typename DeferredIterator::type type;
    };
};

template< long Distance >
struct upper_bound_step
{
    template<
          typename Predicate
        , typename T
        , typename DeferredIterator
        >
    struct result_
    {
        typedef integral_c<long, Distance / 2> offset_;
        typedef typename DeferredIterator::type iter_;
        typedef typename advance<iter_, offset_>::type middle_;
        typedef typename apply_if<
#if defined(BOOST_MSVC) && (BOOST_MSVC < 1300)
              apply2<Predicate,T,typename apply0<middle_>::type>
#else
              apply2<Predicate,T,typename middle_::type>
#endif
            , typename upper_bound_step<offset_::value>
                ::template result_< Predicate,T,DeferredIterator >
            , typename upper_bound_step<Distance - offset_::value - 1>
                ::template result_< Predicate,T,next<middle_> >
            >::type type;
    };
};

} // namespace aux

template<
      typename Sequence
    , typename T
    , typename Predicate
    >
struct upper_bound
{
 private:
    typedef typename lambda<Predicate>::type pred_;

 public:
    typedef typename aux::upper_bound_step< size<Sequence>::value >
        ::template result_< pred_,T,begin<Sequence> >::type type;
};

BOOST_MPL_AUX_LAMBDA_SPEC(3, upper_bound)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_UPPER_BOUND_HPP_INCLUDED

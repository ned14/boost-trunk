//-----------------------------------------------------------------------------
// boost mpl/compose/f_gxy.hpp header file
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

#ifndef BOOST_MPL_COMPOSE_F_GXY_HPP_INCLUDED
#define BOOST_MPL_COMPOSE_F_GXY_HPP_INCLUDED

#include "boost/mpl/apply.hpp"
#include "boost/mpl/placeholder.hpp"
#include "boost/mpl/aux_/config/lambda_support.hpp"

namespace boost {
namespace mpl {

namespace aux {

template<
      typename F
    , typename G
    , typename X
    , typename Y
    >
struct f_gxy
{
 private:
    typedef typename apply2<G,X,Y>::type P;
 
 public:
    typedef apply1<F,P> type;
};

} // namespace aux

template<
      typename F
    , typename G
    >
struct compose_f_gxy
{
    template< typename X, typename Y > struct apply
        : aux::f_gxy<F,G,X,Y>::type
    {
    };
};

template<
      typename F
    , typename G
    >
struct compose_f_gyx
{
    template< typename X, typename Y > struct apply
        : aux::f_gxy<F,G,Y,X>::type
    {
    };
};

#if !defined(BOOST_MPL_NO_LAMDBA_SUPPORT)
template<
      typename F
    , typename G
    >
struct lambda< compose_f_gxy<F,G> >
{
    typedef compose_f_gxy<F,G> type;
};

template<
      typename F
    , typename G
    >
struct lambda< compose_f_gyx<F,G> >
{
    typedef compose_f_gyx<F,G> type;
};
#endif

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_COMPOSE_F_GXY_HPP_INCLUDED


#ifndef BOOST_MPL_NUMERIC_CAST_HPP_INCLUDED
#define BOOST_MPL_NUMERIC_CAST_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

// agurt 21/sep/04: portability macro for the sake of MSVC 6.x-7.0; 
// resolves conflicts with 'boost::numeric_cast' function template.
// use it in your own code _only_ if you care about compatibility with 
// these outdated compilers!
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
#   define BOOST_MPL_AUX_NUMERIC_CAST numeric_cast_
#else
#   define BOOST_MPL_AUX_NUMERIC_CAST numeric_cast
#endif

namespace boost { namespace mpl {

// no default implementation; the definition is needed to make MSVC happy

template< typename SourceTag, typename TargetTag > struct BOOST_MPL_AUX_NUMERIC_CAST
{
    template< typename N > struct apply;
};


namespace aux {

template<
      typename F
    , typename Tag1
    , typename Tag2
    >
struct cast1st_impl
{
    template< typename N1, typename N2 > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : apply_wrap2< 
              F
            , typename apply_wrap1< BOOST_MPL_AUX_NUMERIC_CAST<Tag1,Tag2>,N1 >::type
            , N2
            >
    {
#else
    {
    typedef typename apply_wrap2< 
              F
            , typename apply_wrap1< BOOST_MPL_AUX_NUMERIC_CAST<Tag1,Tag2>,N1 >::type
            , N2
            >::type type;
#endif
    };
};

template<
      typename F
    , typename Tag1
    , typename Tag2
    >
struct cast2nd_impl
{
    template< typename N1, typename N2 > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : apply_wrap2< 
              F
            , N1
            , typename apply_wrap1< BOOST_MPL_AUX_NUMERIC_CAST<Tag2,Tag1>,N2 >::type
            >
    {
#else
    {
        typedef typename apply_wrap2< 
              F
            , N1
            , typename apply_wrap1< BOOST_MPL_AUX_NUMERIC_CAST<Tag2,Tag1>,N2 >::type
            >::type type;
#endif
    };
};

} // namespace aux

}}

#endif // BOOST_MPL_NUMERIC_CAST_HPP_INCLUDED

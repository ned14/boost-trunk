
#ifndef BOOST_MPL_AUX_CONFIG_NTTP_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_NTTP_HPP_INCLUDED

// Copyright (c) Aleksey Gurtovoy 2001-2004
//
// Use, modification and distribution are subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy 
// at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

// MSVC 6.5 ICE-s on the code as simple as this:
//
//    namespace std {
//    template< typename Char > struct string;
//    }
//
//    void foo(std::string<char>);
//
//    namespace boost { namespace mpl {
//    template< int > struct arg;
//    }}
//
// fortunately, a workaround is simple as well:
//
//    typedef int nttp_int;
//    template< nttp_int > struct arg;

#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)

#include <boost/preprocessor/cat.hpp>

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
namespace boost { namespace mpl {
typedef int     nttp_int;
typedef long    nttp_long;
}}
#endif

#   define BOOST_MPL_AUX_NTTP_DECL(T, x) BOOST_PP_CAT(nttp_,T) x /**/

#else
#   define BOOST_MPL_AUX_NTTP_DECL(T, x) T x /**/
#endif

#endif // BOOST_MPL_AUX_CONFIG_NTTP_HPP_INCLUDED

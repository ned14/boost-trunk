//-----------------------------------------------------------------------------
// boost mpl/type_traits/aux_/trait.hpp header file
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

#ifndef BOOST_MPL_TYPE_TRAITS_AUX_TRAIT_HPP_INCLUDED
#define BOOST_MPL_TYPE_TRAITS_AUX_TRAIT_HPP_INCLUDED

#include "boost/mpl/aux_/pred.hpp"
#include "boost/mpl/aux_/lambda_spec.hpp"
#include "boost/mpl/aux_/preprocessor/params.hpp"

#define BOOST_MPL_AUX_TRAIT_TEMPLATE(i, name) \
namespace boost { namespace mpl { \
template< \
      BOOST_MPL_PP_PARAMS(0, i, typename T) \
    > \
struct name \
    : aux::pred< boost::name<BOOST_MPL_PP_PARAMS(0, i, T)> > \
{ \
}; \
\
BOOST_MPL_AUX_LAMBDA_SPEC(i, name) \
}} \
/**/

#endif // BOOST_MPL_TYPE_TRAITS_AUX_TRAIT_HPP_INCLUDED

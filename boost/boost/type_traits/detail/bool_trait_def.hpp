//-----------------------------------------------------------------------------
// boost/type_traits/detail/bool_trait_def.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

// no include guards, the header is intended for multiple inclusion!

#include "boost/type_traits/detail/bool_trait.hpp"
#include "boost/config.hpp"

#define BOOST_TT_AUX_BOOL_TRAIT_DEF1(trait,T,value) \
template< typename T > struct trait \
    : ::boost::type_traits::bool_trait< value > \
{ \
}; \
/**/

#define BOOST_TT_AUX_BOOL_TRAIT_DEF2(trait,T1,T2,value) \
template< typename T1, typename T2 > struct trait \
    : ::boost::type_traits::bool_trait< value > \
{ \
}; \
/**/

#define BOOST_TT_AUX_BOOL_TRAIT_SPEC1(trait,sp,value) \
template<> struct trait<sp> \
    : ::boost::type_traits::bool_trait< value > \
{ \
}; \
/**/

#define BOOST_TT_AUX_BOOL_TRAIT_SPEC2(trait,sp1,sp2,value) \
template<> struct trait<sp1,sp2> \
    : ::boost::type_traits::bool_trait< value > \
{ \
}; \
/**/

#define BOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC1_1(param,trait,sp,value) \
template< param > struct trait<sp> \
    : ::boost::type_traits::bool_trait< value > \
{ \
}; \
/**/

#define BOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC1_2(param1,param2,trait,sp,value) \
template< param1, param2 > struct trait<sp> \
    : ::boost::type_traits::bool_trait< value > \
{ \
}; \
/**/

#define BOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC2_1(param,trait,sp1,sp2,value) \
template< param > struct trait<sp1,sp2> \
    : ::boost::type_traits::bool_trait< value > \
{ \
}; \
/**/

#define BOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC2_2(param1,param2,trait,sp1,sp2,value) \
template< param1, param2 > struct trait<sp1,sp2> \
    : ::boost::type_traits::bool_trait< value > \
{ \
}; \
/**/

#ifndef BOOST_NO_CV_SPECIALIZATIONS
#   define BOOST_TT_AUX_BOOL_TRAIT_CV_SPEC1(trait,sp,value) \
    BOOST_TT_AUX_BOOL_TRAIT_SPEC1(trait,sp,value) \
    BOOST_TT_AUX_BOOL_TRAIT_SPEC1(trait,sp const,value) \
    BOOST_TT_AUX_BOOL_TRAIT_SPEC1(trait,sp volatile,value) \
    BOOST_TT_AUX_BOOL_TRAIT_SPEC1(trait,sp const volatile,value) \
    /**/
#else
#   define BOOST_TT_AUX_BOOL_TRAIT_CV_SPEC1(trait,sp,value) \
    BOOST_TT_AUX_BOOL_TRAIT_SPEC1(trait,sp,value) \
    /**/
#endif

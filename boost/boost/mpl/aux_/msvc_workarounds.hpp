//-----------------------------------------------------------------------------
// boost mpl/aux_/msvc_workarounds.hpp header file
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

#ifndef BOOST_MPL_AUX_MSVC_WORKAROUNDS_HPP_INCLUDED
#define BOOST_MPL_AUX_MSVC_WORKAROUNDS_HPP_INCLUDED

#include "boost/config.hpp"

#if defined(BOOST_MSVC) && (BOOST_MSVC <= 1300)

#include "boost/mpl/aux_/preprocessor/params.hpp"

namespace boost {
namespace mpl {
namespace aux {

template< typename T > struct msvc_never_true
{
    BOOST_STATIC_CONSTANT(bool, value = false);
};

// warning: not a well-formed C++
// workaround for MSVC 6.5's "dependent template typedef bug"
#define BOOST_MPL_AUX_MSVC_DEPENDENT_TEMPLATE_WRAPPER_DEF(name, templ, arity) \
template< typename F> struct name \
{ \
    template< bool > struct f_ : F {}; \
    template<> struct f_<true> \
    { \
        template< BOOST_MPL_PP_PARAMS(0, arity, typename P) > struct templ {}; \
    }; \
    \
    template< BOOST_MPL_PP_PARAMS(0, arity, typename T) > struct result_ \
        : f_< msvc_never_true<F>::value > \
            ::template templ< BOOST_MPL_PP_PARAMS(0, arity, T) > \
    { \
    }; \
}; \
/**/

} // namespace aux
} // namespace mpl
} // namespace boost

#endif // #if defined(BOOST_MSVC) && (BOOST_MSVC <= 1300)

#endif // BOOST_MPL_AUX_MSVC_WORKAROUNDS_HPP_INCLUDED

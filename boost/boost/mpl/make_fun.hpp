//-----------------------------------------------------------------------------
// boost mpl/make_fun.hpp header file
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

#ifndef BOOST_MPL_MAKE_FUN_HPP_INCLUDED
#define BOOST_MPL_MAKE_FUN_HPP_INCLUDED

#include "boost/mpl/limits/arity.hpp"
#include "boost/mpl/aux_/preprocessor/params.hpp"
#include "boost/mpl/aux_/config/ttp.hpp"

#include "boost/preprocessor/repeat_2nd.hpp"
#include "boost/preprocessor/inc.hpp"
#include "boost/preprocessor/if.hpp"

namespace boost {
namespace mpl {

#if !defined(BOOST_NO_TEMPLATE_TEMPLATE_PARAMETERS)

// local macros, #undef-ined at the end of the header
#define AUX_MAKE_FUN_PARAMS(i, param) \
    BOOST_MPL_PP_PARAMS(1, BOOST_PP_INC(i), param) \
/**/

#define AUX_MAKE_F0_TEMPLATE_DEF(i)
#define AUX_MAKE_FN_TEMPLATE_DEF(i) \
template< \
      template< AUX_MAKE_FUN_PARAMS(i, typename P) > class F \
    > \
struct make_f##i \
{ \
    typedef make_f##i type; \
    template< AUX_MAKE_FUN_PARAMS(i, typename U) > struct apply \
        : F< AUX_MAKE_FUN_PARAMS(i, U) > \
    { \
    }; \
}; \
/**/

#define AUX_MAKE_FN_DEF(i, unused) \
    BOOST_PP_IF( \
        i \
      , AUX_MAKE_FN_TEMPLATE_DEF \
      , AUX_MAKE_F0_TEMPLATE_DEF \
      )(i) \
/**/
      
// make_f#
BOOST_PP_REPEAT_2ND(
      BOOST_PP_INC(BOOST_MPL_METAFUNCTION_MAX_ARITY)
    , AUX_MAKE_FN_DEF
    , unused
    )

#undef AUX_MAKE_FN_DEF
#undef AUX_MAKE_FN_TEMPLATE_DEF
#undef AUX_MAKE_F0_TEMPLATE_DEF
#undef AUX_MAKE_FUN_PARAMS

// for backward compatibility
template< template<typename> class F >
struct make_f_x
{
    template<typename U>
    struct apply
        : F<U>
    {
    };
};

template< template<typename, typename> class F >
struct make_f_xy
{
    template<typename U1, typename U2>
    struct apply
        : F<U1,U2>
    {
    };
};

template< template<typename, typename> class F >
struct make_f_yx
{
    template<typename U1, typename U2>
    struct apply
        : F<U2,U1>
    {
    };
};


#   define BOOST_MPL_MAKE_F_X(name, f) typedef boost::mpl::make_f_x<f> name
#   define BOOST_MPL_MAKE_F_XY(name, f) typedef boost::mpl::make_f_xy<f> name
#   define BOOST_MPL_MAKE_F_YX(name, f) typedef boost::mpl::make_f_yx<f> name

#else

#   define BOOST_MPL_MAKE_F_X(name, f) \
    struct name { template< typename U > struct apply : f<U> {}; } \
/**/

#   define BOOST_MPL_MAKE_F_XY(name, f) struct name \
    { template< typename U1, typename U2 > struct apply : f<U1,U2> {}; } \
/**/

#   define BOOST_MPL_MAKE_F_YX(name, f) struct name \
    { template< typename U1, typename U2 > struct apply : f<U2,U1> {}; } \
/**/

#endif // #if !defined(BOOST_NO_TEMPLATE_TEMPLATE_PARAMETERS)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_MAKE_FUN_HPP_INCLUDED

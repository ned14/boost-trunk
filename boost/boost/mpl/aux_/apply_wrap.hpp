
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_AUX_APPLY_WRAP_HPP_INCLUDED
#define BOOST_AUX_APPLY_WRAP_HPP_INCLUDED

// Copyright (c) Aleksey Gurtovoy 2000-2004
//
// Use, modification and distribution are subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy 
// at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/aux_/arity.hpp>
#   include <boost/mpl/aux_/na.hpp>
#   include <boost/mpl/aux_/msvc_never_true.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER apply_wrap.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/arity.hpp>
#   include <boost/mpl/aux_/preprocessor/params.hpp>
#   include <boost/mpl/aux_/preprocessor/enum.hpp>
#   include <boost/mpl/aux_/preprocessor/add.hpp>
#   include <boost/mpl/aux_/config/dtp.hpp>
#   include <boost/mpl/aux_/config/eti.hpp>
#   include <boost/mpl/aux_/config/msvc.hpp>
#   include <boost/mpl/aux_/config/workaround.hpp>

#   include <boost/preprocessor/comma_if.hpp>
#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/iterate.hpp>


namespace boost { namespace mpl { namespace aux {

// local macros, #undef-ined at the end of the header
#   define AUX778076_APPLY_WRAP_PARAMS(n, param) \
    BOOST_MPL_PP_PARAMS(n, param) \
    /**/

#   define AUX778076_APPLY_WRAP_SPEC_PARAMS(n, param) \
    BOOST_MPL_PP_ENUM(BOOST_PP_INC(n), param) \
    /**/


#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, <boost/mpl/aux_/apply_wrap.hpp>))
#include BOOST_PP_ITERATE()


#   undef AUX778076_APPLY_WRAP_SPEC_PARAMS
#   undef AUX778076_APPLY_WRAP_PARAMS

}}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_AUX_APPLY_WRAP_HPP_INCLUDED

///// iteration, depth == 1

#elif BOOST_PP_ITERATION_DEPTH() == 1

#   define i_ BOOST_PP_FRAME_ITERATION(1)
#   if i_ == 0

template< typename F >
struct apply_wrap0 : F
{
};

#if defined(BOOST_MPL_CFG_MSVC_ETI_BUG)
//: workaround for the ETI bug
template<>
struct apply_wrap0<int>
{
    typedef int type;
};
#endif

#   else // i_ > 0

#   if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
// MSVC version

#define AUX778076_MSVC_DTW_NAME BOOST_PP_CAT(msvc_apply,i_)
#define AUX778076_MSVC_DTW_ORIGINAL_NAME apply
#define AUX778076_MSVC_DTW_ARITY i_
#include <boost/mpl/aux_/msvc_dtw.hpp>

template<
      typename F, AUX778076_APPLY_WRAP_PARAMS(i_, typename T)
    >
struct BOOST_PP_CAT(apply_wrap,i_)
{
    // Metafunction forwarding confuses vc6
    typedef typename BOOST_PP_CAT(msvc_apply,i_)<F>::template result_<
          AUX778076_APPLY_WRAP_PARAMS(i_, T)
        >::type type;
};

#   elif defined(BOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
// MWCW/Borland version

template<
      int N, typename F, AUX778076_APPLY_WRAP_PARAMS(i_, typename T)
    >
struct BOOST_PP_CAT(apply_wrap_impl,i_);

#define BOOST_PP_ITERATION_PARAMS_2 \
    (3,(0, BOOST_MPL_LIMIT_METAFUNCTION_ARITY - i_, <boost/mpl/aux_/apply_wrap.hpp>))
#include BOOST_PP_ITERATE()

template<
      typename F, AUX778076_APPLY_WRAP_PARAMS(i_, typename T)
    >
struct BOOST_PP_CAT(apply_wrap,i_)
    : BOOST_PP_CAT(apply_wrap_impl,i_)<
          ::boost::mpl::aux::arity<F,i_>::value
        , F
        , AUX778076_APPLY_WRAP_PARAMS(i_, T)
        >::type
{
};

#   else
// ISO98 C++, with minor concession to vc7

template<
      typename F, AUX778076_APPLY_WRAP_PARAMS(i_, typename T)
    >
struct BOOST_PP_CAT(apply_wrap,i_)
{
    // Metafunction forwarding confuses vc7
    typedef typename F::template apply<
         AUX778076_APPLY_WRAP_PARAMS(i_, T)
        >::type type;
};

#   endif // workarounds

#if defined(BOOST_MPL_CFG_MSVC_ETI_BUG)
//: workaround for ETI bug
template<>
struct BOOST_PP_CAT(apply_wrap,i_)<AUX778076_APPLY_WRAP_SPEC_PARAMS(i_, int)>
{
    typedef int type;
};
#endif

#   endif // i_ > 0
#   undef i_

///// iteration, depth == 2

#elif BOOST_PP_ITERATION_DEPTH() == 2

#   define j_ BOOST_PP_FRAME_ITERATION(2)

template<
      typename F, AUX778076_APPLY_WRAP_PARAMS(i_, typename T)
    >
struct BOOST_PP_CAT(apply_wrap_impl,i_)<
          BOOST_MPL_PP_ADD(i_, j_)
        , F
        , AUX778076_APPLY_WRAP_PARAMS(i_, T)
        >
{
    typedef typename F::template apply<
          AUX778076_APPLY_WRAP_PARAMS(i_, T)
        BOOST_PP_COMMA_IF(j_) BOOST_MPL_PP_ENUM(j_, na)
        > type;
};

#   undef j_

#endif // BOOST_PP_IS_ITERATING


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

// no include guards, the header is intended for multiple inclusion!

#include <boost/mpl/aux_/preprocessor/params.hpp>

// local macros, #undef-ined at the end of the header
#define AUX778076_DTW_PARAMS(param) \
    BOOST_MPL_PP_PARAMS(AUX778076_MSVC_DTW_ARITY, param) \
/**/

#define AUX778076_DTW_ORIGINAL_NAME \
    AUX778076_MSVC_DTW_ORIGINAL_NAME \
/**/

// warning: not a well-formed C++
// workaround for MSVC 6.5's "dependent template typedef bug"

template< typename F>
struct AUX778076_MSVC_DTW_NAME
{
    template< bool > struct f_ : F {};
    template<> struct f_<true>
    {
        template< AUX778076_DTW_PARAMS(typename P) > struct AUX778076_DTW_ORIGINAL_NAME
        {
        };
    };

    template< AUX778076_DTW_PARAMS(typename T) > struct result_
        : f_< aux::msvc_never_true<F>::value >
            ::template AUX778076_DTW_ORIGINAL_NAME< AUX778076_DTW_PARAMS(T) >
    {
    };
};

#undef AUX778076_DTW_ORIGINAL_NAME
#undef AUX778076_DTW_PARAMS

#undef AUX778076_MSVC_DTW_NAME
#undef AUX778076_MSVC_DTW_ORIGINAL_NAME
#undef AUX778076_MSVC_DTW_ARITY

//-----------------------------------------------------------------------------
// boost mpl/list.hpp header file
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

#ifndef BOOST_MPL_LIST_C_HPP_INCLUDED
#define BOOST_MPL_LIST_C_HPP_INCLUDED

#include "boost/mpl/aux_/config/use_preprocessed.hpp"

#if defined(BOOST_MPL_USE_PREPROCESSED_HEADERS)
#   include "boost/mpl/aux_/preprocessed/list_c.hpp"
#else

#include "boost/mpl/list/aux_/impl.hpp"
#include "boost/mpl/limits/list.hpp"
#include "boost/mpl/integral_c.hpp"
#include "boost/mpl/aux_/preprocessor/params.hpp"
#include "boost/mpl/aux_/preprocessor/default_params.hpp"
#include "boost/mpl/aux_/preprocessor/enum.hpp"
#include "boost/mpl/aux_/config/msvc_typename.hpp"

#include "boost/preprocessor/tuple/elem.hpp"
#include "boost/config.hpp"

#include <climits>

namespace boost {
namespace mpl {

#define AUX_LIST_PARAMS(param) \
    BOOST_MPL_PP_PARAMS( \
          0 \
        , BOOST_MPL_LIMIT_LIST_SIZE \
        , param \
        ) \
/**/

#define AUX_LIST_DEFAULT_PARAMS(param, value) \
    BOOST_MPL_PP_DEFAULT_PARAMS( \
          0 \
        , BOOST_MPL_LIMIT_LIST_SIZE \
        , param \
        , value \
        ) \
/**/

#define AUX_LIST_C_PARAMS_FUNC(i, tc) \
    integral_c< \
          BOOST_PP_TUPLE_ELEM(2, 0, tc) \
        , BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(2, 1, tc), i) \
        > \
/**/

#define AUX_LIST_C_PARAMS(T, C) \
    BOOST_MPL_PP_ENUM( \
          0 \
        , BOOST_MPL_LIMIT_LIST_SIZE \
        , AUX_LIST_C_PARAMS_FUNC \
        , (T, C) \
        ) \
/**/

namespace aux {

template< typename T > struct list_c_param
{
    typedef long type;
    BOOST_STATIC_CONSTANT(long, value = LONG_MAX);
};

#define AUX_LIST_C_UNSIGNED_PARAM_SPEC(T) \
template<> struct list_c_param<T> \
{ \
    typedef unsigned long type; \
    BOOST_STATIC_CONSTANT(unsigned long, value = ULONG_MAX); \
}; \
/**/

AUX_LIST_C_UNSIGNED_PARAM_SPEC(unsigned char)
AUX_LIST_C_UNSIGNED_PARAM_SPEC(unsigned short)
AUX_LIST_C_UNSIGNED_PARAM_SPEC(unsigned int)
AUX_LIST_C_UNSIGNED_PARAM_SPEC(unsigned long)

#undef AUX_LIST_C_UNSIGNED_PARAM_SPEC

template<
      typename T
    , AUX_LIST_PARAMS(BOOST_MSVC_TYPENAME list_c_param<T>::type C)
    >
struct list_c_impl
{
    typedef typename list_c_param<T>::type param_type_;
    typedef aux::list_count_if_not<
          integral_c<param_type_,list_c_param<T>::value>
        , AUX_LIST_C_PARAMS(param_type_, C)
        > arg_num_;

    typedef typename aux::list_impl_chooser< arg_num_::value >
        ::template result_< AUX_LIST_C_PARAMS(T, (T)C) >::type type;
};

} // namespace aux

template<
      typename T
    , AUX_LIST_DEFAULT_PARAMS(
          BOOST_MSVC_TYPENAME aux::list_c_param<T>::type C
        , aux::list_c_param<T>::value
        )
    >
struct list_c
    : aux::list_c_impl< T, AUX_LIST_PARAMS(C) >::type
{
    typedef typename aux::list_c_impl<
          T
        , AUX_LIST_PARAMS(C)
        >::type type;
};

#undef AUX_LIST_C_PARAMS
#undef AUX_LIST_DEFAULT_PARAMS
#undef AUX_LIST_C_PARAMS_FUNC
#undef AUX_LIST_PARAMS

} // namespace mpl
} // namespace boost

#endif // #if defined(BOOST_MPL_USE_PREPROCESSED_HEADERS)

#endif // BOOST_MPL_LIST_C_HPP_INCLUDED

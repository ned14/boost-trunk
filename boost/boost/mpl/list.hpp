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

#ifndef BOOST_MPL_LIST_HPP_INCLUDED
#define BOOST_MPL_LIST_HPP_INCLUDED

#include "boost/mpl/aux_/config/use_preprocessed.hpp"

#if defined(BOOST_MPL_USE_PREPROCESSED_HEADERS)
#   include "boost/mpl/aux_/preprocessed/list.hpp"
#else

#include "boost/mpl/list/aux_/impl.hpp"
#include "boost/mpl/limits/list.hpp"
#include "boost/mpl/aux_/preprocessor/params.hpp"
#include "boost/mpl/aux_/preprocessor/default_params.hpp"

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

namespace aux {

template< AUX_LIST_PARAMS(typename T) >
struct list_impl
{
    typedef aux::list_count_if_not< aux::none, AUX_LIST_PARAMS(T) > arg_num_;
    typedef typename aux::list_impl_chooser< arg_num_::value >
        ::template result_< AUX_LIST_PARAMS(T) >::type type;
};

} // namespace aux

template< AUX_LIST_DEFAULT_PARAMS(typename T, aux::none) >
struct list
    : aux::list_impl< AUX_LIST_PARAMS(T) >::type
{
    typedef typename aux::list_impl<
          AUX_LIST_PARAMS(T)
        >::type type;
};

#undef AUX_LIST_DEFAULT_PARAMS
#undef AUX_LIST_PARAMS

} // namespace mpl
} // namespace boost

#endif // #if defined(BOOST_MPL_USE_PREPROCESSED_HEADERS)

#endif // BOOST_MPL_LIST_HPP_INCLUDED

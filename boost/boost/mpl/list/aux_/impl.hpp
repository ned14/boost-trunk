//-----------------------------------------------------------------------------
// boost mpl/list/aux_/impl.hpp header file
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

#ifndef BOOST_MPL_LIST_AUX_IMPL_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_IMPL_HPP_INCLUDED

#include "boost/mpl/limits/list.hpp"
#include "boost/preprocessor/cat.hpp"
#include "boost/preprocessor/stringize.hpp"

#define AUX_LIST_HEADER \
    BOOST_PP_STRINGIZE( \
        BOOST_PP_CAT( \
              BOOST_PP_CAT(boost/mpl/list/list, BOOST_MPL_LIMIT_LIST_SIZE) \
            , .hpp) \
        ) \
/**/

#include AUX_LIST_HEADER
#undef AUX_LIST_HEADER

#include "boost/mpl/aux_/count_if_not.hpp"
#include "boost/mpl/aux_/none.hpp"
#include "boost/mpl/aux_/preprocessor/params.hpp"
#include "boost/mpl/aux_/preprocessor/default_params.hpp"

#include "boost/preprocessor/repeat_2nd.hpp"
#include "boost/preprocessor/if.hpp"

namespace boost {
namespace mpl {

// local macros, #undef-ined at the end of the header

#define AUX_LIST_PARAMS(param) \
    BOOST_MPL_PP_PARAMS( \
          0 \
        , BOOST_MPL_LIMIT_LIST_SIZE \
        , param \
        ) \
/**/

namespace aux {
template< long > struct list_impl_chooser;
}

#define AUX_LIST_IMPL_CHOOSER_0_DEF(unused) \
namespace aux { \
template<> \
struct list_impl_chooser<0> \
{ \
    template< AUX_LIST_PARAMS(typename T) > \
    struct result_ \
    { \
        typedef list0 type; \
    }; \
}; \
} \
/**/

#define AUX_LIST_IMPL_CHOOSER_N_DEF(i) \
namespace aux { \
template<> \
struct list_impl_chooser<i> \
{ \
    template< AUX_LIST_PARAMS(typename T) > \
    struct result_ \
    { \
        typedef list##i< BOOST_MPL_PP_PARAMS(0, i, T) > type; \
    }; \
}; \
} \
/**/

#define AUX_LIST_IMPL_CHOOSER_DEF(i, unused) \
    BOOST_PP_IF( \
          i \
        , AUX_LIST_IMPL_CHOOSER_N_DEF \
        , AUX_LIST_IMPL_CHOOSER_0_DEF \
        )(i) \
/**/

// list_impl_chooser<#>
BOOST_PP_REPEAT_2ND(
      BOOST_MPL_LIMIT_LIST_SIZE
    , AUX_LIST_IMPL_CHOOSER_DEF
    , unused
    )

// aux::list_count_if_not
BOOST_MPL_AUX_COUNT_IF_NOT(list, BOOST_MPL_LIMIT_LIST_SIZE)

#undef AUX_LIST_IMPL_CHOOSER_DEF
#undef AUX_LIST_IMPL_CHOOSER_N_DEF
#undef AUX_LIST_IMPL_CHOOSER_0_DEF
#undef AUX_LIST_DEFAULT_PARAMS
#undef AUX_LIST_PARAMS

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_LIST_AUX_IMPL_HPP_INCLUDED

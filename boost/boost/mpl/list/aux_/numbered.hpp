//-----------------------------------------------------------------------------
// boost mpl/list/aux_/numbered.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Peter Dimov, Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

// no include guards, the header is intended for multiple inclusion!

#include "boost/mpl/list/aux_/node.hpp"
#include "boost/mpl/aux_/preprocessor/params.hpp"

#include "boost/preprocessor/repeat_2nd.hpp"
#include "boost/preprocessor/arithmetic/add.hpp"
#include "boost/preprocessor/dec.hpp"
#include "boost/preprocessor/if.hpp"
#include "boost/preprocessor/identity.hpp"
#include "boost/preprocessor/empty.hpp"
#include "boost/preprocessor/cat.hpp"

namespace boost {
namespace mpl {

// local macros, #undef-ined at the end of the header
#define AUX_LIST_N_DEF(i) \
template< BOOST_MPL_PP_PARAMS(0, i, typename T) > \
struct BOOST_PP_CAT(list, i) \
    : list_node< \
          T0 \
        , BOOST_PP_CAT(list, BOOST_PP_DEC(i)) \
          BOOST_PP_CAT(BOOST_PP_, BOOST_PP_IF(BOOST_PP_DEC(i), IDENTITY(<), EMPTY))() \
              BOOST_MPL_PP_PARAMS(1, i, T) \
          BOOST_PP_CAT(BOOST_PP_, BOOST_PP_IF(BOOST_PP_DEC(i), IDENTITY(>), EMPTY))() \
        > \
{ \
    typedef BOOST_PP_CAT(list, i) type; \
}; \
/**/

#define AUX_LIST_DEF(i, offset) \
    AUX_LIST_N_DEF(BOOST_PP_ADD(offset, i)) \
/**/

// list#
BOOST_PP_REPEAT_2ND(
      BOOST_MPL_AUX_NUMBERED_LIST_BLOCK_SIZE
    , AUX_LIST_DEF
    , BOOST_MPL_AUX_NUMBERED_LIST_BLOCK_START
    )

#undef AUX_LIST_DEF
#undef AUX_LIST_N_DEF

} // namespace mpl
} // namespace boost

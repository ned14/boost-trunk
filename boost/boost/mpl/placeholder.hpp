//-----------------------------------------------------------------------------
// boost mpl/placeholder.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Peter Dimov, Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MPL_PLACEHOLDER_HPP_INCLUDED
#define BOOST_MPL_PLACEHOLDER_HPP_INCLUDED

#include "boost/mpl/limits/arity.hpp"

#include "boost/preprocessor/repeat.hpp"
#include "boost/preprocessor/inc.hpp"
#include "boost/preprocessor/cat.hpp"

namespace boost {
namespace mpl {

template< long N > struct arg;

typedef arg<-1> _;

namespace placeholder {
using boost::mpl::_;
}

// local macros, #undef-ined at the end of the header
#define AUX_PLACEHOLDER_N_DEF(n) \
typedef arg<n> BOOST_PP_CAT(_,n); \
namespace placeholder { \
using boost::mpl::BOOST_PP_CAT(_,n); \
} \
/**/

#define AUX_PLACEHOLDER_DEF(n, unused) \
    AUX_PLACEHOLDER_N_DEF(BOOST_PP_INC(n)) \
/**/

// typedef arg<#> _#; namespace placeholder { using boost::mpl::_#; }
BOOST_PP_REPEAT(
      // agurt, 17/mar/02: one more placeholder for the last 'apply#' 
      // specialization
      BOOST_PP_INC(BOOST_MPL_METAFUNCTION_MAX_ARITY)
    , AUX_PLACEHOLDER_DEF
    , unused
    )

#undef AUX_PLACEHOLDER_DEF
#undef AUX_PLACEHOLDER_N_DEF

} // namespace mpl
} // namespace boost 

#endif // BOOST_MPL_PLACEHOLDER_HPP_INCLUDED

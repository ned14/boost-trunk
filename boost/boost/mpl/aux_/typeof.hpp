//-----------------------------------------------------------------------------
// boost mpl/aux_/typeof.hpp header file
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

#ifndef BOOST_MPL_AUX_TYPEOF_HPP_INCLUDED
#define BOOST_MPL_AUX_TYPEOF_HPP_INCLUDED

#include "boost/config.hpp"

#if !defined(__ICL)

namespace boost {
namespace mpl {

// the implementation below is based on "A Portable typeof Operator" article
// by Bill Gibbons, C++ User Journal, November 2000

namespace aux {
template< long N > struct typeof_answer { typedef char type[N]; };
template< long > struct typeof_c;
}

#define BOOST_MPL_AUX_REGISTER_TYPE(index, T) \
namespace boost { namespace mpl { namespace aux { \
template<> struct typeof_c<index> { typedef T type; }; \
typeof_answer<index>::type& type_index(T const&); \
}}} \
/**/

#if defined(BOOST_NO_INCLASS_MEMBER_INITIALIZATION) || defined(BOOST_MSVC) && (BOOST_MSVC == 1301)
#   define BOOST_MPL_AUX_TYPEOF(x) long
#else
#   define BOOST_MPL_AUX_TYPEOF(x) \
boost::mpl::aux::typeof_c< \
    sizeof(boost::mpl::aux::type_index(x)) \
    >::type \
/**/
#endif

} // namespace mpl
} // namespace boost

BOOST_MPL_AUX_REGISTER_TYPE(1, bool)
BOOST_MPL_AUX_REGISTER_TYPE(2, signed char)
BOOST_MPL_AUX_REGISTER_TYPE(3, unsigned char)
BOOST_MPL_AUX_REGISTER_TYPE(4, char)
#if !defined(BOOST_NO_INTRINSIC_WCHAR_T)
BOOST_MPL_AUX_REGISTER_TYPE(5, wchar_t)
#endif
BOOST_MPL_AUX_REGISTER_TYPE(6, short)
BOOST_MPL_AUX_REGISTER_TYPE(7, unsigned short)
BOOST_MPL_AUX_REGISTER_TYPE(8, int)
BOOST_MPL_AUX_REGISTER_TYPE(9, unsigned int)
BOOST_MPL_AUX_REGISTER_TYPE(10, long)
BOOST_MPL_AUX_REGISTER_TYPE(11, unsigned long)
BOOST_MPL_AUX_REGISTER_TYPE(12, float)
BOOST_MPL_AUX_REGISTER_TYPE(13, double)
BOOST_MPL_AUX_REGISTER_TYPE(14, long double)

#else

namespace boost {
namespace mpl {

namespace aux {
template< long > struct typeof_c { typedef long type; };
}

} // namespace mpl
} // namespace boost

#   define BOOST_MPL_AUX_TYPEOF(x) aux::typeof_c<x>::type

#endif // #if !defined(__ICL)

#endif // BOOST_MPL_AUX_TYPEOF_HPP_INCLUDED

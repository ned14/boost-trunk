//-----------------------------------------------------------------------------
// boost mpl/same_as.hpp header file
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

#ifndef BOOST_MPL_SAME_AS_HPP_INCLUDED
#define BOOST_MPL_SAME_AS_HPP_INCLUDED

#include "boost/mpl/bool_c.hpp"
#include "boost/type_traits/same_traits.hpp"
#include "boost/mpl/lambda_fwd.hpp"
#include "boost/mpl/aux_/config/lambda_support.hpp"
#include "boost/config.hpp"

namespace boost {
namespace mpl {

template< typename T1 >
struct same_as
{
    template< typename T2 > struct apply
    {
        BOOST_STATIC_CONSTANT(bool, value =
            (::boost::is_same<T1,T2>::value)
            );
        
        typedef bool_c<value> type;
    };
};

template< typename T1 >
struct not_same_as
{
    template< typename T2 > struct apply
    {
        BOOST_STATIC_CONSTANT(bool, value =
            (!::boost::is_same<T1,T2>::value)
            );
        
        typedef bool_c<value> type;
    };
};

#if !defined(BOOST_MPL_NO_LAMDBA_SUPPORT)
template< typename T1 > struct lambda< same_as<T1> >
{
    typedef same_as<T1> type;
};

template< typename T1 > struct lambda< not_same_as<T1> >
{
    typedef not_same_as<T1> type;
};
#endif

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_SAME_AS_HPP_INCLUDED

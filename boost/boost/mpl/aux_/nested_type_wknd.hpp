
#ifndef BOOST_MPL_AUX_NESTED_TYPE_WKND_HPP_INCLUDED
#define BOOST_MPL_AUX_NESTED_TYPE_WKND_HPP_INCLUDED

// Copyright (c) 2000-04 Aleksey Gurtovoy
//
// Use, modification and distribution are subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy 
// at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/gcc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, BOOST_TESTED_AT(0x0302)) \
    || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x561)) \
    || BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x530))

namespace boost { namespace mpl { namespace aux {

template< typename T >
struct nested_type_wknd
    : T::type
{
};

}}} // namespace boost::mpl::aux

#   define BOOST_MPL_AUX_NESTED_TYPE_WKND(T) \
    ::boost::mpl::aux::nested_type_wknd<T> \
/**/

#else

#   define BOOST_MPL_AUX_NESTED_TYPE_WKND(T) T::type

#endif // BOOST_MPL_CFG_GCC et al.

#endif // BOOST_MPL_AUX_NESTED_TYPE_WKND_HPP_INCLUDED

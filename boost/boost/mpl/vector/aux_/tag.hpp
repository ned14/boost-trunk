
#ifndef BOOST_MPL_VECTOR_AUX_TAG_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_TAG_HPP_INCLUDED

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

#include "boost/mpl/aux_/config/typeof.hpp"

namespace boost { namespace mpl { namespace aux {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
struct vector_tag;
#else
template< long N > struct vector_tag;
#endif

}}} // namespace boost::mpl::aux

#endif // BOOST_MPL_VECTOR_AUX_TAG_HPP_INCLUDED

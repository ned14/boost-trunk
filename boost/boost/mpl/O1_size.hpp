
#ifndef BOOST_MPL_O1_SIZE_HPP_INCLUDED
#define BOOST_MPL_O1_SIZE_HPP_INCLUDED

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

#include <boost/mpl/O1_size_fwd.hpp>
#include <boost/mpl/aux_/O1_size_impl.hpp>
#include <boost/mpl/aux_/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost {
namespace mpl {

// returns sequence size if it's an O(1) operation; otherwise returns -1
template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct O1_size
    : O1_size_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
};

BOOST_MPL_AUX_NA_SPEC(1, O1_size)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_O1_SIZE_HPP_INCLUDED


#ifndef BOOST_MPL_VECTOR_AUX_BEGIN_END_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_BEGIN_END_HPP_INCLUDED

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

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   include "boost/mpl/begin_end_fwd.hpp"
#   include "boost/mpl/vector/aux_/iterator.hpp"
#   include "boost/mpl/vector/aux_/tag.hpp"

namespace boost {
namespace mpl {

template<>
struct begin_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
    {
        typedef v_iter<Vector,0> type;
    };
};

template<>
struct end_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
    {
        enum { size_ = Vector::upper_bound_ - Vector::lower_bound_ };
        typedef v_iter<Vector,size_> type;
    };
};

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#endif // BOOST_MPL_VECTOR_AUX_BEGIN_END_HPP_INCLUDED

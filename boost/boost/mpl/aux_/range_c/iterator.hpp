
#ifndef BOOST_MPL_AUX_RANGE_C_ITERATOR_HPP_INCLUDED
#define BOOST_MPL_AUX_RANGE_C_ITERATOR_HPP_INCLUDED

// Copyright (c) Aleksey Gurtovoy 2000-2004
//
// Use, modification and distribution are subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy 
// at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/iterator_tag.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/aux_/iterator_names.hpp>

namespace boost { namespace mpl {

template< typename N >
struct range_c_iterator
{
    typedef random_access_iterator_tag category;
    typedef N type;

    typedef range_c_iterator<typename N::next> next;
    typedef range_c_iterator<typename N::prior> prior;

    template< typename D >
    struct BOOST_MPL_AUX_ITERATOR_ADVANCE
    {
        typedef range_c_iterator<
              typename plus<N,D>::type
            > type;
    };

    template< typename U >
    struct BOOST_MPL_AUX_ITERATOR_DISTANCE
    {
        typedef typename minus<typename U::type,N>::type type;
    };
};

}}

#endif // BOOST_MPL_AUX_RANGE_C_ITERATOR_HPP_INCLUDED

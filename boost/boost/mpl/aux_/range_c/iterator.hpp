//-----------------------------------------------------------------------------
// boost mpl/aux_/range_c/iterator.hpp header file
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

#ifndef BOOST_MPL_AUX_RANGE_C_ITERATOR_HPP_INCLUDED
#define BOOST_MPL_AUX_RANGE_C_ITERATOR_HPP_INCLUDED

#include "boost/mpl/integral_c.hpp"
#include "boost/mpl/iterator_category.hpp"
#include "boost/config.hpp"

namespace boost {
namespace mpl {

template< typename T, T N >
struct range_c_iterator
{
    typedef random_access_iterator_tag category;

    typedef integral_c<T,N> type;
    BOOST_STATIC_CONSTANT(T, value = N);

    typedef range_c_iterator<T,value + 1> next;
    typedef range_c_iterator<T,value - 1> prior;

    template< typename D > struct advance_
    {
        // temporary 'result_' is a MSVC6.5 workaround
        BOOST_STATIC_CONSTANT(T, result_ = N + D::value);
        typedef range_c_iterator<T,result_> type;
    };

    template< typename U > struct distance_
    {
        BOOST_STATIC_CONSTANT(long, value = U::value - N);
        typedef integral_c<long, value> type;
    };
};

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_AUX_RANGE_C_ITERATOR_HPP_INCLUDED

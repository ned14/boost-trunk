//-----------------------------------------------------------------------------
// boost mpl/aux_/advance_forward.hpp header file
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

#ifndef BOOST_MPL_AUX_ADVANCE_FORWARD_HPP_INCLUDED
#define BOOST_MPL_AUX_ADVANCE_FORWARD_HPP_INCLUDED

#include "boost/mpl/apply.hpp"

namespace boost {
namespace mpl {
namespace aux {

template< long N >
struct advance_forward
{
    template< typename Iterator, typename Op > struct result_
    {
        typedef typename apply1<Op, Iterator>::type next_;
        typedef typename advance_forward<N-1>
            ::template result_<next_,Op>::type type;
    };
};

template<>
struct advance_forward<0>
{
    template< typename Iterator, typename Op > struct result_
    {
        typedef Iterator type;
    };
};

} // namespace aux
} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_AUX_ADVANCE_FORWARD_HPP_INCLUDED

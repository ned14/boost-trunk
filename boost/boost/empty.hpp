//-----------------------------------------------------------------------------
// boost empty.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2003
// Eric Friedman
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_EMPTY_HPP
#define BOOST_EMPTY_HPP

#include <iosfwd> // for std::basic_ostream forward declare

#include "boost/config.hpp"
#include "boost/detail/templated_streams.hpp"
#include "boost/mpl/bool.hpp"
#include "boost/type_traits/is_pod.hpp"

namespace boost {

struct empty
{
};

template <>
struct is_pod<empty>
{
    BOOST_STATIC_CONSTANT(bool, value = true);
    typedef mpl::bool_<value> type;
};

bool operator==(const empty&, const empty&)
{
    return true;
}

bool operator<(const empty&, const empty&)
{
    return false;
}

BOOST_TEMPLATED_STREAM_TEMPLATE(E,T)
inline BOOST_TEMPLATED_STREAM(ostream, E,T)& operator<<(
      BOOST_TEMPLATED_STREAM(ostream, E,T)& out
    , const empty&
    )
{
    // (output nothing)
    return out;
}

} // namespace boost

#endif // BOOST_EMPTY_HPP

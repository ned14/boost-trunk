#ifndef BOOST_ARCHIVE_FAST_ARRAY_SERIALIZATION_HPP
#define BOOST_ARCHIVE_FAST_ARRAY_SERIALIZATION_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// traits.hpp:

// (C) Copyright 2005 Matthias Troyer . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// This header is used to define archive traits to customize serialization

#include <boost/mpl/bool.hpp>

namespace boost {
namespace archive {

/// Traits class to specify whether an archive provides fast array serialization for a type

template <class Archive, class Type>
struct has_fast_array_serialization 
  : public mpl::bool_<false> 
{};
  

} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_FAST_ARRAY_SERIALIZATION_HPP

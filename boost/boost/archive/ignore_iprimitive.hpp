#ifndef BOOST_ARCHIVE_IGNORE_IPRIMITIVE_HPP
#define BOOST_ARCHIVE_IGNORE_IPRIMITIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// ignore_iprimitive.hpp
//
// ignore any load from an archive, essentially a no-op archive.
// probably an archive archetype, but we need better archive concepts to
// check this.

// (C) Copyright 2005 Matthias Troyer 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>

namespace boost { 
namespace archive {

/// @brief a minimal input archive, which ignores any load
///
/// This class implements a minimal input archive, probably an input archive
/// archetype, doing nothing at any load. It's use, besides acting as an
/// archetype is as a base class to implement special archives that ignore 
/// loading of most types

class ignore_iprimitive
{
public:
    /// a trivial default constructor
    ignore_iprimitive()
    {}
  
  
	/// don't do anything when loading binary data
    void load_binary(void *, std::size_t )
	{}
	
	/// don't do anything when loading arrays
    template<class T>
    void load_array(T *, std::size_t )
    {}

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    friend class load_access;
protected:
#else
public:
#endif

	/// don't do anything when loading primitive types
    template<class T>
    void load(T & t)
	{
    }
};

} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_IGNORE_IPRIMITIVE_HPP

#ifndef BOOST_ARCHIVE_IGNORE_OPRIMITIVE_HPP
#define BOOST_ARCHIVE_IGNORE_OPRIMITIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// ignore_oprimitive.hpp
//
// ignore any save to an archive, essentially a no-op archive.
// probably an archive archetype, but we need better archive concepts to
// check this.

// (C) Copyright 2005 Matthias Troyer 
// Fast array serialization (C) Copyright 2005 Matthias Troyer 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.


namespace boost {
namespace archive {

/// @brief a minimal output archive, which ignores any save
///
/// This class implements a minimal output archive, probably an output archive
/// archetype, doing nothing at any save. It's use, besides acting as an
/// archetype is as a base class to implement special archives that ignore 
/// saving of most types

class ignore_oprimitive
{
public:
    /// a trivial default constructor
    ignore_oprimitive()
    {}

	/// don't do anything when saving binary data
    void save_binary(const void *, std::size_t )
	{
	}
	
	/// don't do anything when saving arrays
    template<class T>
    void save_array(T const *, std::size_t )
    {
    }

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    friend class save_access;
protected:
#else
public:
#endif

	/// don't do anything when saving primitive types
    template<class T>
    void save(const T & t)
    {
    }
};


} //namespace boost 
} //namespace archive 

#endif // BOOST_ARCHIVE_IGNORE_OPRIMITIVE_HPP

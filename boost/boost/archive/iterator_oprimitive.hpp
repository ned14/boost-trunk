#ifndef BOOST_ARCHIVE_ITERATOR_OPRIMITIVE_HPP
#define BOOST_ARCHIVE_ITERATOR_OPRIMITIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// iterator_oprimitive.hpp
//
// an archive that saves values to an output iterator
// 

// (C) Copyright 2005 Matthias Troyer 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.


namespace boost {
namespace archive {

/// @brief a minimal output archive, saving to an output iterator
///
/// This class template uses an output iterator to save values.
/// Note that it does not satisfy the full output archive concept since it
/// does not support binary saving, and only supports serialization of
/// types in the set of value type of the output iterator.  The type
/// of output iterator is given as the template parameter.


template <class OutputIterator>
class iterator_oprimitive
{
public:

    /// the type of output iterator
    typedef OutputIterator iterator;
	
	/// the constructor takes the output iterator as argument
    iterator_oprimitive(iterator it)
	 : iter(it)
    {}

	// binary saving is not implemented!
    // void save_binary(const void * address, std::size_t count )
	
#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    friend class save_access;
protected:
#else
public:
#endif

    /// primitives are saved by writing to the output iterator
    template<class T>
    void save(const T & t)
    {
	  *iter = t;
	  ++iter;
    }
	
private:
    iterator iter;
};


} //namespace boost 
} //namespace archive 

#endif // BOOST_ARCHIVE_ITERATOR_OPRIMITIVE_HPP

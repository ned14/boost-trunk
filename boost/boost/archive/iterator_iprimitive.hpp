#ifndef BOOST_ARCHIVE_ITERATOR_IPRIMITIVE_HPP
#define BOOST_ARCHIVE_ITERATOR_IPRIMITIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// iterator_iprimitive.hpp
//
// an archive that loads values from an input iterator
// 

// (C) Copyright 2005 Matthias Troyer 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.


namespace boost {
namespace archive {

/// @brief an input archive, reading from an iterator
///
/// This class template uses an input iterator to load values.
/// Note that it does not satisfy the full input archive concept since it
/// does not support binary loading, and only supports deserialization of
/// types convertible from the value type of the input iterator.  The type
/// of input iterator is given as the template parameter.

template <class InputIterator>
class iterator_iprimitive
{
public:

    /// the type of input iterator
    typedef InputIterator iterator;
	
	/// the constructor takes the input iterator as argument
    iterator_iprimitive(iterator it)
	 : iter(it)
    {}

	// binary loading is not implemented!
    // void load_binary(void * address, std::size_t count )
	
#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    friend class load_access;
protected:
#else
public:
#endif

    /// primitives are loaded by reading from the input iterator
    template<class T>
    void load(T & t)
    {
	  t = *iter;
	  ++iter;
    }
	
private:
    iterator iter;
};


} //namespace boost 
} //namespace archive 

#endif // BOOST_ARCHIVE_ITERATOR_IPRIMITIVE_HPP

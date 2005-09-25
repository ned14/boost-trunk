#ifndef BOOST_ARCHIVE_FORWARD_IPRIMITIVE_HPP
#define BOOST_ARCHIVE_FORWARD_IPRIMITIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// forward_iprimitive.hpp
//
// forwards any load, load_array or load_binary to another archive.
// 

// (C) Copyright 2005 Matthias Troyer 
// Fast array serialization (C) Copyright 2005 Matthias Troyer 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.


namespace boost {
namespace archive {

/// @brief a minimal input archive, which forwards reading to another archive
///
/// This class template is designed to use the loading facilities of another
/// input archive (the "implementation archive", whose type is specified by 
/// the template argument, to handle serialization of primitive types, 
/// while serialization for specific types can be overriden independently 
/// of that archive.

template <class ImplementationArchive>
class forward_iprimitive
{
public:

    /// the type of the archive to which the loading of primitive types will be forwarded
    typedef ImplementationArchive implementation_archive_type;
	
	/// the constructor takes a reference to the implementation archive used for loading primitve types
    forward_iprimitive(implementation_archive_type& ar)
	 : implementation_archive(ar)
    {}

	/// binary loading is forwarded to the implementation archive
    void load_binary(void * address, std::size_t count )
	{
	  implementation_archive.load_binary(address,count);
	}
	
	/// loading of arrays is forwarded to the implementation archive
    template<class T>
    void load_array(T * address, std::size_t count)
    {
	  implementation_archive.load_array(address,count);
    }

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    friend class load_access;
protected:
#else
public:
#endif

    ///  loading of primitives is forwarded to the implementation archive
    template<class T>
    void load(T & t)
    {
	  implementation_archive >> t;
    }
	
private:
    implementation_archive_type& implementation_archive;
};


} //namespace boost 
} //namespace archive 

#endif // BOOST_ARCHIVE_FORWARD_IPRIMITIVE_HPP

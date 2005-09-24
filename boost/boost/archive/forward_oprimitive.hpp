#ifndef BOOST_ARCHIVE_FORWARD_OPRIMITIVE_HPP
#define BOOST_ARCHIVE_FORWARD_OPRIMITIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// forward_oprimitive.hpp
//
// forwards any save, save_array or save_binary to another archive.
// 

// (C) Copyright 2005 Matthias Troyer 
// Fast array serialization (C) Copyright 2005 Matthias Troyer 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.


namespace boost {
namespace archive {

/// @brief a minimal output archive, which forwards saving to another archive
///
/// This class template is designed to use the saving facilities of another
/// output archive (the "implementation archive", whose type is specified by 
/// the template argument, to handle serialization of primitive types, 
/// while serialization for specific types can be overriden independently 
/// of that archive.

template <class ImplementationArchive>
class forward_oprimitive
{
public:

    /// the type of the archive to which the saving of primitive types will be forwarded
    typedef ImplementationArchive implementation_archive_type;
	
	/// the constructor takes a reference to the implementation archive used for saving primitve types
    forward_oprimitive(implementation_archive_type& ar)
	 : implementation_archive(ar)
    {}

	/// binary saving is forwarded to the implementation archive
    void save_binary(const void * address, std::size_t count )
	{
	  implementation_archive.save_binary(address,count);
	}
	
	/// saving of arrays is forwarded to the implementation archive
    template<class T>
    void save_array(T const * address, std::size_t count)
    {
	  implementation_archive.save_array(address,count);
    }

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    friend class save_access;
protected:
#else
public:
#endif

    ///  saving of primitives is forwarded to the implementation archive
    template<class T>
    void save(const T & t)
    {
	  implementation_archive.save(t);
    }
	
private:
    implementation_archive_type& implementation_archive;
};


} //namespace boost 
} //namespace archive 

#endif // BOOST_ARCHIVE_FORWARD_OPRIMITIVE_HPP

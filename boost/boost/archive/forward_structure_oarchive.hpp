#ifndef BOOST_ARCHIVE_FORWARD_STRUCTURE_OARCHIVE_HPP
#define BOOST_ARCHIVE_FORWARD_STRUCTURE_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// forward_structure_iarchive.hpp

// (C) Copyright 2005 Matthias Troyer 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/pfto.hpp>

#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/common_oarchive.hpp>
#include <boost/archive/basic_archive.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost { 
namespace archive {

template<class Archive, class ImplementationArchive>
class forward_structure_oarchive 
  : public  detail::common_oarchive<Archive>
{
public:

    typedef ImplementationArchive implementation_archive_type;
	
    forward_structure_oarchive(implementation_archive_type& ar) 
	  : detail::common_oarchive<Archive>(no_header),
		implementation_archive(ar)
	{
	}
		
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
    friend class detail::interface_oarchive<Archive>;
    friend class load_access;
protected:
#endif

    // intermediate level to support override of operators
    // for templates in the absence of partial function 
    // template ordering
    template<class T>
    void save_override(T const& t, BOOST_PFTO int)
    {
        archive::save(* this->This(), t);
    }
	
#define BOOST_ARCHIVE_FORWARD_IMPLEMENTATION(T) \
    void save_override(T const & t , int)             \
	{                                           \
	  implementation_archive << t;              \
	}

BOOST_ARCHIVE_FORWARD_IMPLEMENTATION(class_id_optional_type)
BOOST_ARCHIVE_FORWARD_IMPLEMENTATION(version_type)
BOOST_ARCHIVE_FORWARD_IMPLEMENTATION(class_id_type)
BOOST_ARCHIVE_FORWARD_IMPLEMENTATION(class_id_reference_type)
BOOST_ARCHIVE_FORWARD_IMPLEMENTATION(object_id_type)
BOOST_ARCHIVE_FORWARD_IMPLEMENTATION(tracking_type)
BOOST_ARCHIVE_FORWARD_IMPLEMENTATION(container_size_type)
BOOST_ARCHIVE_FORWARD_IMPLEMENTATION(class_name_type)

#undef BOOST_ARCHIVE_FORWARD_IMPLEMENTATION
private:
    /// the actual archive used to serialize the information we actually want to store
    implementation_archive_type& implementation_archive;
};


} // namespace archive
} // namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_FORWARD_STRUCTURE_OARCHIVE_HPP

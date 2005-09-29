#ifndef BOOST_ARCHIVE_IGNORE_STRUCTURE_OARCHIVE_HPP
#define BOOST_ARCHIVE_IGNORE_STRUCTURE_OARCHIVE_HPP

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

template<class Archive>
class ignore_structure_oarchive 
  : public  detail::common_oarchive<Archive>
{
public:
	
    ignore_structure_oarchive()
	  : detail::common_oarchive<Archive>(no_header)
	{
	}
		
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
    friend class detail::interface_oarchive<Archive>;
    friend class save_access;
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
	
#define BOOST_ARCHIVE_IGNORE_IMPLEMENTATION(T) \
    void save_override(T const & t , int)      \
	{}                                         \

BOOST_ARCHIVE_IGNORE_IMPLEMENTATION(class_id_optional_type)
BOOST_ARCHIVE_IGNORE_IMPLEMENTATION(version_type)
BOOST_ARCHIVE_IGNORE_IMPLEMENTATION(class_id_type)
BOOST_ARCHIVE_IGNORE_IMPLEMENTATION(class_id_reference_type)
BOOST_ARCHIVE_IGNORE_IMPLEMENTATION(object_id_type)
BOOST_ARCHIVE_IGNORE_IMPLEMENTATION(object_reference_type)
BOOST_ARCHIVE_IGNORE_IMPLEMENTATION(tracking_type)
BOOST_ARCHIVE_IGNORE_IMPLEMENTATION(container_size_type)
BOOST_ARCHIVE_IGNORE_IMPLEMENTATION(class_name_type)

#undef BOOST_ARCHIVE_IGNORE_IMPLEMENTATION
};


} // namespace archive
} // namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_IGNORE_STRUCTURE_OARCHIVE_HPP

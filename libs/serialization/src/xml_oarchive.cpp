/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// xml_oarchive.cpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#if (defined _MSC_VER) && (_MSC_VER == 1200)
#  pragma warning (disable : 4786) // too long name, harmless warning
#endif

#define BOOST_ARCHIVE_SOURCE
#include <boost/archive/xml_oarchive.hpp>

#include <boost/archive/impl/basic_xml_oarchive.ipp>
#include <boost/archive/impl/archive_pointer_oserializer.ipp>
#include <boost/archive/impl/xml_oarchive_impl.ipp>

namespace boost {
namespace archive {

// explicitly instantiate for this type of xml stream
template class basic_xml_oarchive<naked_xml_oarchive, false> ;
template class detail::archive_pointer_oserializer<naked_xml_oarchive> ;
template class xml_oarchive_impl<naked_xml_oarchive, false> ;

// explicitly instantiate for this type of xml stream
template class basic_xml_oarchive<xml_oarchive, true> ;
template class detail::archive_pointer_oserializer<xml_oarchive> ;
template class xml_oarchive_impl<xml_oarchive, true> ;

} // namespace archive
} // namespace boost

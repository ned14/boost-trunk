#ifndef  BOOST_SERIALIZATION_HASH_MAP_HPP
#define BOOST_SERIALIZATION_HASH_MAP_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// serialization/hash_map.hpp:
// serialization for stl hash_map templates

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifdef BOOST_HAS_HASH

#include <hash_map>

#include <boost/serialization/utility.hpp>
#include <boost/serialization/collections_save_imp.hpp>
#include <boost/serialization/collections_load_imp.hpp>
#include <boost/serialization/split_free.hpp>

// function specializations must be defined in the appropriate
// namespace - boost::serialization
#ifdef BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
namespace boost { namespace serialization {
#elif defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)
namespace _STLP_STD {
#else
namespace BOOST_STD_EXTENSION_NAMESPACE {
#endif

template<class Archive, class Key, class Compare, class Allocator >
inline void save(
    Archive & ar,
    const BOOST_STD_EXTENSION_NAMESPACE::hash_map<Key, Compare, Allocator> &t,
    const unsigned int file_version
){
    boost::serialization::stl::save_collection<
        Archive, 
        BOOST_STD_EXTENSION_NAMESPACE::hash_map<Key, Compare, Allocator> 
    >(ar, t);
}

template<class Archive, class Key, class Compare, class Allocator >
inline void load(
    Archive & ar,
    BOOST_STD_EXTENSION_NAMESPACE::hash_map<Key, Compare, Allocator> &t,
    const unsigned int file_version
){
    boost::serialization::stl::load_collection<
        Archive,
        BOOST_STD_EXTENSION_NAMESPACE::hash_map<Key, Compare, Allocator>,
        boost::serialization::stl::archive_input_map<
            Archive, 
            BOOST_STD_EXTENSION_NAMESPACE::hash_map<Key, Compare, Allocator> 
        >,
        boost::serialization::stl::no_reserve_imp<
            BOOST_STD_EXTENSION_NAMESPACE::hash_map<Key, Compare, Allocator> 
        >
    >(ar, t);
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<class Archive, class Key, class Compare, class Allocator >
inline void serialize(
    Archive & ar,
    BOOST_STD_EXTENSION_NAMESPACE::hash_map<Key, Compare, Allocator> &t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

// hash_multimap
template<class Archive, class Key, class Compare, class Allocator >
inline void save(
    Archive & ar,
    const BOOST_STD_EXTENSION_NAMESPACE::hash_multimap<Key, Compare, Allocator> &t,
    const unsigned int file_version
){
    boost::serialization::stl::save_collection<
        Archive, 
        BOOST_STD_EXTENSION_NAMESPACE::hash_multimap<Key, Compare, Allocator> 
    >(ar, t);
}

template<class Archive, class Key, class Compare, class Allocator >
inline void load(
    Archive & ar,
    BOOST_STD_EXTENSION_NAMESPACE::hash_multimap<Key, Compare, Allocator> &t,
    const unsigned int file_version
){
    boost::serialization::stl::load_collection<
        Archive,
        BOOST_STD_EXTENSION_NAMESPACE::hash_multimap<Key, Compare, Allocator>,
        boost::serialization::stl::archive_input_map<
            Archive, 
            BOOST_STD_EXTENSION_NAMESPACE::hash_multimap<Key, Compare, Allocator> 
        >,
        boost::serialization::stl::no_reserve_imp<
            BOOST_STD_EXTENSION_NAMESPACE::hash_multimap<Key, Compare, Allocator> 
        >
    >(ar, t);
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<class Archive, class Key, class Compare, class Allocator >
inline void serialize(
    Archive & ar,
    BOOST_STD_EXTENSION_NAMESPACE::hash_multimap<Key, Compare, Allocator> &t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

#ifdef BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
}} // namespace boost::serialization
#else
} // BOOST_STD_EXTENSION_NAMESPACE
#endif

#endif // BOOST_HAS_HASH
#endif // BOOST_SERIALIZATION_HASH_MAP_HPP

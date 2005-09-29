// (C) Copyright 2005 Matthias Troyer . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_ARCHIVE_SUPPORTS_TYPEMAP_SERIALIZATION_HPP
#define BOOST_ARCHIVE_SUPPORTS_TYPEMAP_SERIALIZATION_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

// This header is used to define archive traits to customize serialization

#include <boost/config.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_fundamental.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/remove_extent.hpp>
#include <boost/mpl/if.hpp>
#include <boost/shared_ptr.hpp>

#include <vector>
#include <deque>
#include <list>

#ifdef BOOST_HAS_SLIST
#include <slist>
#endif

#if defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)
#define STD _STLP_STD
#else
#define STD BOOST_STD_EXTENSION_NAMESPACE
#endif


namespace boost {
namespace archive {

/// @brief Traits to check for typemap serialization
///
/// Typemap serialization is a two-stage process, to support, e.g. MPI serialization without copying.
///
/// Upon deserialization, in a first stage, the memory for all objects is allocated using only
/// the "structure" information from an archive, that is only the special types of the serialization
/// library are deserialized, such as class ids, pointers, and size types of containers. That information
/// has to be sufficient to allocate all the memory
///
/// In a second stage, the serialization library is used again, to register the address of all data members,
/// thus building a memory map of the data structures, which is then used to fill the data members. This
/// stage requires that serialization is done by serializing all members directly, and not temporaries.
///
/// Typemap serialization hence allows only a subset of the serialization functionalities. Serialization
/// has to proceed by serializing all data members directly, and the objects must be constructible only
/// using information serialized through the special types of the serialization library

template <class Archive, class Type>
struct supports_typemap_serialization;

template <class Archive, class Type>
struct supports_typemap_serialization
 : public mpl::if_
            < 
			  is_pointer<Type>,
			  supports_typemap_serialization<Archive,typename remove_pointer<Type>::type>,
			  mpl::if_
                <
				  is_array<Type>,
				  supports_typemap_serialization<Archive,typename remove_extent<Type>::type>,
			      is_fundamental<Type>
				>
			>::type
{};

// specialization for std::vector

template <class Archive, class U, class Allocator>
struct supports_typemap_serialization<Archive, STD::vector<U,Allocator> >
 : public supports_typemap_serialization<Archive,U>
{};

// exception: std::vecctor<bool> cannot be optimized

template <class Archive, class Allocator>
struct supports_typemap_serialization<Archive, STD::vector<bool,Allocator> >
 : public mpl::bool_<false>
{};

// specialization for std::list

template <class Archive, class U, class Allocator>
struct supports_typemap_serialization<Archive, STD::list<U,Allocator> >
 : public supports_typemap_serialization<Archive,U>
{};


// specialization for std::deque

template <class Archive, class U, class Allocator>
struct supports_typemap_serialization<Archive, STD::deque<U,Allocator> >
 : public supports_typemap_serialization<Archive,U>
{};

// specialization for std::slist

#ifdef BOOST_HAS_SLIST
template <class Archive, class U, class Allocator>
struct supports_typemap_serialization<Archive, STD::slist<U,Allocator> >
 : public supports_typemap_serialization<Archive,U>
{};
#endif

// specialization for boost::shared_ptr

template <class Archive, class T>
struct supports_typemap_serialization<Archive, boost::shared_ptr<T> >
 : public supports_typemap_serialization<Archive,T>
{};

} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_SUPPORTS_TYPEMAP_SERIALIZATION_HPP

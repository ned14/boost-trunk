#ifndef BOOST_ARCHIVE_ONLY_DATA_OARCHIVE_HPP
#define BOOST_ARCHIVE_ONLY_DATA_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// only_structure_iarchive.hpp

// (C) Copyright 2005 Matthias Troyer 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/basic_archive.hpp>
#include <boost/archive/fast_array_serialization.hpp>
#include <boost/archive/ignore_structure_oarchive.hpp>
#include <boost/archive/forward_oprimitive.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost { 
namespace archive {

// an archive wrapper that stores only the data members but not the
// special types defined by the serialization library
// to define the data structures (classes, pointers, container sizes, ...)

template <class ImplementationArchive>
class only_data_oarchive 
  : public forward_oprimitive<ImplementationArchive>,
    public ignore_structure_oarchive<only_data_oarchive<ImplementationArchive> >
{
public:
    only_data_oarchive(ImplementationArchive& ar) 
	  : forward_oprimitive<ImplementationArchive>(ar)
	{
	}
};

template <class Type, class ImplementationArchive>
struct fast_array_serialization<only_data_oarchive<ImplementationArchive>,Type>
  : public fast_array_serialization<ImplementationArchive,Type>
{};



} // namespace archive
} // namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_ONLY_STRUCTURE_OARCHIVE_HPP

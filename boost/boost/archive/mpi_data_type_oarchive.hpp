// (C) Copyright 2005 Matthias Troyer 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_ARCHIVE_ONLY_DATA_OARCHIVE_HPP
#define BOOST_ARCHIVE_ONLY_DATA_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/archive/detail/mpi_type.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/basic_archive.hpp>
#include <boost/archive/fast_array_serialization.hpp>
#include <boost/archive/ignore_structure_oarchive.hpp>
#include <boost/archive/mpi_data_type_oprimitive.hpp>

#include <boost/mpl/bool.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost { 
namespace archive {

// an archive wrapper that stores only the data members but not the
// special types defined by the serialization library
// to define the data structures (classes, pointers, container sizes, ...)

class mpi_data_type_oarchive 
  : public mpi_data_type_oprimitive,
    public ignore_structure_oarchive<mpi_data_type_oarchive>
{
public:
    mpi_data_type_oarchive() 
	{}
};

template <class Type>
struct fast_array_serialization<mpi_data_type_oarchive,Type>
  : public is_mpi_type<Type>
{};



} // namespace archive
} // namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_ONLY_STRUCTURE_OARCHIVE_HPP

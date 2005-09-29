// (C) Copyright 2005 Matthias Troyer 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_ARCHIVE_MPI_PACKED_IARCHIVE_HPP
#define BOOST_ARCHIVE_MPI_PACKED_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/archive/detail/mpi_type.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/basic_binary_iarchive.hpp>
#include <boost/archive/fast_array_serialization.hpp>
#include <boost/archive/mpi_packed_iprimitive.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost { 
namespace archive {

// an archive that packs binary data into an MPI buffer

class mpi_packed_iarchive 
  : public mpi_packed_iprimitive,
    public basic_binary_iarchive<mpi_packed_iarchive>
{
public:
    mpi_packed_iarchive
	  (
	    std::vector<char> const & b, 
		MPI::Comm const & c = MPI::COMM_WORLD,
		unsigned int flags = 0
	  ) 
	 : mpi_packed_iprimitive(b,c),
	   basic_binary_iarchive<mpi_packed_iarchive>(flags)
	{}
	
	
    mpi_packed_iarchive
	  (
	    std::vector<char> const & b, 
		unsigned int flags = 0
	  ) 
	 : mpi_packed_iprimitive(b,MPI::COMM_WORLD),
	   basic_binary_iarchive<mpi_packed_iarchive>(flags)
	{}
};

template <class Type>
struct fast_array_serialization<mpi_packed_iarchive,Type>
  : public is_mpi_type<Type>
{};



} // namespace archive
} // namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_MPI_PACKED_IARCHIVE_HPP

// (C) Copyright 2005 Matthias Troyer 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_ARCHIVE_MPI_PACKED_IPRIMITIVE_HPP
#define BOOST_ARCHIVE_MPI_PACKED_IPRIMITIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif


#include <mpicxx.h>
#include <iostream>

#include <cstddef> // size_t

#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{ 
    using ::size_t; 
} // namespace std
#endif

#include <boost/archive/detail/mpi_type.hpp>
#include <boost/archive/detail/get_data.hpp>
#include <vector>

namespace boost {
namespace archive {

/////////////////////////////////////////////////////////////////////////
// class mpi_packed_iprimitive - deserialization using MPI::Unack

class mpi_packed_iprimitive
{
public:
    
    mpi_packed_iprimitive(std::vector<char> const & b, MPI::Comm const & c = MPI::COMM_WORLD)
	 : buffer(b),
	   comm(c),
	   position(0)
	{
	}

    void load_binary(void *address, std::size_t count)
	{
	  load_impl(address,MPI_BYTE,count);
	}
	
    // fast saving of arrays of fundamental types
    template<class T>
    void load_array(T *address, std::size_t count)
    {
        load_impl(address, mpi_type<T>::value, count);
    }
	
#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    friend class load_access;
protected:
#else
public:
#endif

    // default saving of primitives.
    template<class T>
    void load( T & t)
    {
        load_impl(&t, mpi_type<T>::value, 1);
    }

private:

    void load_impl(void * p, MPI_Datatype t, int l)
	{
	  // unpack the data from the buffer
	  MPI::Unpack(detail::get_data(buffer), buffer.size(), position, p, l, comm);
	}
	
	std::vector<char> const & buffer;
	MPI::Comm const & comm;
	int position;
};


} //namespace boost 
} //namespace archive 

#endif // BOOST_ARCHIVE_MPI_PACKED_IPRIMITIVE_HPP

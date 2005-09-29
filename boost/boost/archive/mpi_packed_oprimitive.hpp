// (C) Copyright 2005 Matthias Troyer 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_ARCHIVE_MPI_PACKED_OPRIMITIVE_HPP
#define BOOST_ARCHIVE_MPI_PACKED_OPRIMITIVE_HPP

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
// class mpi_packed_oprimitive - serialization using MPI::Pack

class mpi_packed_oprimitive
{
public:
    
    mpi_packed_oprimitive(std::vector<char> & b, MPI::Comm const & c = MPI::COMM_WORLD)
	 : buffer(b),
	   comm(c)
	{
	}
	
    void save_binary(void const *address, std::size_t count)
	{
	  save_impl(address,MPI_BYTE,count);
	}
	
    // fast saving of arrays of fundamental types
    template<class T>
    void save_array(T const *address, std::size_t count)
    {
        save_impl(address, mpi_type<T>::value, count);
    }
	
#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    friend class save_access;
protected:
#else
public:
#endif

    // default saving of primitives.
    template<class T>
    void save(const T & t)
    {
        save_impl(&t, mpi_type<T>::value, 1);
    }

private:

    void save_impl(void const * p, MPI_Datatype t, int l)
	{
	  // allocate enough memory
	  int memory_needed = MPI::Pack_size(l,t,comm);
	  int position = buffer.size();
	  buffer.resize(position + memory_needed);
	  
	  // pack the data into the buffer
	  MPI::Pack(p, l, detail::get_data(buffer), buffer.size(), position, comm);
	  
	  // reduce the buffer size if needed
	  BOOST_ASSERT(position <= buffer.size());
	  if (position < buffer.size())
	    buffer.resize(position);
	}
	
    std::vector<char>& buffer;
	MPI::Comm const & comm;
};


} //namespace boost 
} //namespace archive 

#endif // BOOST_ARCHIVE_MPI_PACKED_OPRIMITIVE_HPP

// (C) Copyright 2005 Matthias Troyer 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_ARCHIVE_MPI_DATA_TYPE_OPRIMITIVE_HPP
#define BOOST_ARCHIVE_MPI_DATA_TYPE_OPRIMITIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif


#include <mpi.h>

#include <cstddef> // size_t

#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{ 
    using ::size_t; 
} // namespace std
#endif

#include <boost/archive/detail/mpi_type.hpp>
#include <boost/archive/mpi_data_type.hpp>
#include <boost/optional.hpp>
#include <vector>


namespace boost {
namespace archive {

namespace detail {

  template <class T, class Allocator>
  const T* get_data(std::vector<T>& v)
  {
    return &(v[0]);
  }

  template <class T, class Allocator>
  const T* get_data(const std::vector<T>& v)
  {
    return get_data(const_cast< std::vector<T>&>(v));
  }

}


/////////////////////////////////////////////////////////////////////////
// class mpi_data_type_oprimitive - creation of custom MPI data types

class mpi_data_type_oprimitive
{
public:
    
	// trivial default constructor
    mpi_data_type_oprimitive()
	{}
	
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

    // create and return the custom MPI data type
    const mpi_data_type& data_type() const 
	{
	  if (!datatype.is_commited()) // we did not create the data type yet
	  {
	    int err = MPI_Type_struct
		            (
					  addresses.size(), 
					  detail::get_data(lengths),
					  detail::get_data(addresses),
					  detail::get_data(types),
					  datatype.get_ptr()
					);
    
 	    if (err != MPI_SUCCESS)
   		   boost::throw_exception(std::runtime_error("invalid MPI datatype"));
    
	    datatype.commit();
	  }
	  
	  return datatype.get();
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
	  BOOST_ASSERT ( !datatype.is_commited() );
	  
	  // convert pointer to an MPI address
	  MPI_Aint addr;
	  MPI_Address(p,&addr);
	  
	  // store address, type and length
	  addresses.push_back(addr);
	  types.push_back(t);
	  lengths.push_back(l);
	}
	
    std::vector<MPI_Aint> addresses;
    std::vector<MPI_Datatype> types;
    std::vector<int> lengths;
	
	mutable mpi_data_type datatype;
};


} //namespace boost 
} //namespace archive 

#endif // BOOST_ARCHIVE_MPI_DATA_TYPE_OPRIMITIVE_HPP

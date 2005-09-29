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


#include <mpicxx.h>
#include <cstddef> // size_t

#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{ 
    using ::size_t; 
} // namespace std
#endif

#include <boost/archive/detail/mpi_type.hpp>
#include <boost/archive/detail/get_data.hpp>
#include <boost/throw_exception.hpp>
#include <stdexcept>
#include <vector>

namespace boost {
namespace archive {

/////////////////////////////////////////////////////////////////////////
// class mpi_data_type_oprimitive - creation of custom MPI data types

class mpi_data_type_oprimitive
{
public:
    
	// trivial default constructor
    mpi_data_type_oprimitive()
	 : is_committed(false)
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
	MPI::Datatype data_type() 
	{
	  if (!is_committed)
	  {
	  
#ifndef BOOST_USE_MPI_C_BINDINGS
	    datatype.Create_struct
		            (
					  addresses.size(), 
					  boost::detail::get_data(lengths),
					  boost::detail::get_data(addresses),
					  boost::detail::get_data(types)
					);
#else  
        MPI_Datatype d;
  		int err=MPI_Type_create_struct
		            (
					  addresses.size(), 
					  boost::detail::get_data(lengths),
					  boost::detail::get_data(addresses),
					  boost::detail::get_data(types),
					  &d
					);
		if (err)
		  boost::throw_exception(std::runtime_error("Error calling MPI_Type_struct"));
		  
		datatype = d;
#endif
	    datatype.Commit();
		is_committed = true;
	  }
	  
	  return datatype;
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
	  BOOST_ASSERT ( !is_committed );
	  
	  // store address, type and length
	  addresses.push_back(MPI::Get_address(const_cast<void *>(p)));
	  types.push_back(t);
	  lengths.push_back(l);
	}
	
    std::vector<MPI::Aint> addresses;
#ifndef BOOST_USE_MPI_C_BINDINGS
    std::vector<MPI::Datatype> types;
#else
    std::vector<MPI_Datatype> types;
#endif
    std::vector<int> lengths;
	
	bool is_committed;
	MPI::Datatype datatype;
};


} //namespace boost 
} //namespace archive 

#endif // BOOST_ARCHIVE_MPI_DATA_TYPE_OPRIMITIVE_HPP

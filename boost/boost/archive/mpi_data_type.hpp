// (C) Copyright 2005 Matthias Troyer . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_ARCHIVE_MPI_DATA_TYPE_HPP
#define BOOST_ARCHIVE_MPI_DATA_TYPE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <mpi.h>
#include <boost/throw_exception.hpp>
#include <boost/noncopyable.hpp>
#include <boost/assert.hpp>
#include <boost/shared_ptr.hpp>
#include <stdexcept>

namespace boost {

/// @brief A C++ wrapper for MPI_Datatype
///
/// Wrapping an MPI_Datatype, and taking care of freeing the type at the end

class mpi_data_type_impl : public boost::noncopyable
{
public:
  mpi_data_type_impl()
   : committed_(false)
  {}
  
  void commit()
  {
    BOOST_ASSERT ( ! committed_ );
	int err = MPI_Type_commit(&datatype_);
	if (err)
	  boost::throw_exception(std::runtime_error("MPI error on committing datatype"));
	committed_ = true;
  }
  
  void free()
  {
    BOOST_ASSERT( committed_ );
    int err=MPI_Type_free(&datatype_);
	if (err)
	  boost::throw_exception(std::runtime_error("MPI error on freeing datatype"));
	committed_ = false;
  }
  
  bool is_committed() const
  {
    return committed_;
  }
  
  operator MPI_Datatype() const
  {
    return datatype_;
  }

  ~mpi_data_type_impl()
  {
    if (committed_)
      free();
  }

  MPI_Datatype* get_ptr()
  {
    return &datatype_;
  }

  const MPI_Datatype* get_ptr() const
  {
    return &datatype_;
  }
  
private:
    
  bool committed_;
  MPI_Datatype datatype_;
};

// implements a shallow copy

class mpi_data_type
{
public:
  mpi_data_type()
   : pimpl_(new mpi_data_type_impl())
  {}
  
  void commit()
  {
    pimpl_->commit();
  }
  
  void free()
  {
    pimpl_->free();
  }
  
  bool is_committed() const
  {
    return pimpl_->is_committed();
  }
  
  operator MPI_Datatype() const
  {
    return *pimpl_;
  }

  MPI_Datatype* get_ptr()
  {
    return pimpl_->get_ptr();
  }

  const MPI_Datatype* get_ptr() const
  {
    return pimpl_->get_ptr();
  }


private:
  boost::shared_ptr<mpi_data_type_impl> pimpl_;
};



} // namespace boost

#endif // BOOST_ARCHIVE_MPI_DATA_TYPE_HPP

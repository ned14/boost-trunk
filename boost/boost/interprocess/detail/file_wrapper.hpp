//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztañaga 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_FILE_WRAPPER_HPP
#define BOOST_INTERPROCESS_DETAIL_FILE_WRAPPER_HPP

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/detail/os_file_functions.hpp>
#include <boost/interprocess/detail/move.hpp>
#include <boost/interprocess/detail/creation_tags.hpp>

namespace boost {
namespace interprocess {
namespace detail{

class file_wrapper
{
   public:

   /*!Default constructor. Represents an empty file_wrapper.*/
   file_wrapper();

   /*!Creates a shared memory object with name "name" and mode "mode", with the access mode "mode"
      If the file previously exists, throws an error.*/
   file_wrapper(detail::create_only_t, const char *name, mode_t mode)
   {  this->priv_open_or_create(DoCreate, name, mode);  }

   /*!Tries to create a file with name "name" and mode "mode", with the
      access mode "mode". If the file previously exists, it tries to open it with mode "mode".
      Otherwise throws an error.*/
   file_wrapper(detail::open_or_create_t, const char *name, mode_t mode)
   {  this->priv_open_or_create(DoCreateOrOpen, name, mode);  }

   /*!Tries to open a shared memory object with name "name", with the access mode "mode". 
      If the file does not previously exist, it throws an error.*/
   file_wrapper(detail::open_only_t, const char *name, mode_t mode)
   {  this->priv_open_or_create(DoOpen, name, mode);  }

   /*!Moves the ownership of "moved"'s shared memory object to *this. 
      After the call, "moved" does not represent any shared memory object. 
      Does not throw*/
   file_wrapper
      (detail::moved_object<file_wrapper> &moved)
   {  this->swap(moved.get());   }

   /*!Moves the ownership of "moved"'s shared memory to *this.
      After the call, "moved" does not represent any shared memory. 
      Does not throw*/
   file_wrapper &operator=
      (detail::moved_object<file_wrapper> &moved)
   {  
      file_wrapper tmp(moved);
      this->swap(tmp);
      return *this;  
   }

   /*!Swaps to shared_memory_objects. Does not throw*/
   void swap(file_wrapper &other);

   /*!Erases a shared memory object from the system.*/
   static bool remove(const char *name);
   
   /*!Sets the size of the shared memory mapping*/
   void truncate(offset_t length);

   /*!Closes the shared memory mapping. All mapped regions are still
      valid after destruction. The shared memory object still exists and
      can be newly opened.*/
   ~file_wrapper();

   /*!Returns the name of the file.*/
   const char *get_name() const;

   /*!Return access mode*/
   mode_t get_mode() const;

   /*!Get mapping handle*/
   handle_t get_mapping_handle() const;

   private:
   /*!Closes a previously opened file mapping. Never throws.*/
   void priv_close();
   /*!Closes a previously opened file mapping. Never throws.*/
   bool priv_open_or_create(create_enum_t type, const char *filename, mode_t mode);

   handle_t  m_handle;
   mode_t      m_mode;
   std::string       m_filename;
};

inline file_wrapper::file_wrapper() 
   :  m_handle(handle_t(detail::invalid_file()))
{}

inline file_wrapper::~file_wrapper() 
{  this->priv_close(); }

/*!Returns the name of the file.*/
inline const char *file_wrapper::get_name() const
{  return m_filename.c_str(); }

inline void file_wrapper::swap(file_wrapper &other)
{  
   std::swap(m_handle,  other.m_handle);
   std::swap(m_mode,    other.m_mode);
   m_filename.swap(other.m_filename);   
}

inline handle_t file_wrapper::get_mapping_handle() const
{  return m_handle;  }

inline mode_t file_wrapper::get_mode() const
{  return m_mode; }

inline bool file_wrapper::priv_open_or_create
   (create_enum_t type, 
    const char *filename,
    mode_t mode)
{
   m_filename = filename;

   if(mode != read_only && mode != read_write){
      error_info err(mode_error);
      throw interprocess_exception(err);
   }

   //Open file existing native API to obtain the handle
   switch(type){
      case DoOpen:
         m_handle = open_existing_file(filename, mode);
      break;
      case DoCreate:
         m_handle = create_new_file(filename, mode);
      break;
      case DoCreateOrOpen:
         m_handle = create_or_open_file(filename, mode);
      break;
      default:
         {
            error_info err = other_error;
            throw interprocess_exception(err);
         }
   }

   //Check for error
   if(m_handle == invalid_file()){
      throw interprocess_exception(error_info(system_error_code()));
   }

   m_mode = mode;
   return true;
}

inline bool file_wrapper::remove(const char *filename)
{  return delete_file(filename); }

inline void file_wrapper::truncate(offset_t length)
{
   if(!truncate_file(m_handle, length)){
      error_info err(system_error_code());
      throw interprocess_exception(err);
   }
}

inline void file_wrapper::priv_close()
{
   if(m_handle != invalid_file()){
      close_file(m_handle);
      m_handle = invalid_file();
   }
}

}  //namespace detail{
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_FILE_WRAPPER_HPP

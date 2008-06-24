//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2008. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_WINDOWS_SHARED_MEMORY_HPP
#define BOOST_INTERPROCESS_WINDOWS_SHARED_MEMORY_HPP

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/detail/workaround.hpp>

#if !defined(BOOST_WINDOWS) || defined(BOOST_DISABLE_WIN32)
#error "This header can only be used in Windows operating systems"
#endif

#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/interprocess/detail/os_file_functions.hpp>
#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/detail/win32_api.hpp>
#include <cstddef>
#include <boost/cstdint.hpp>
#include <string>

//!\file
//!Describes a class representing a native windows shared memory.

namespace boost {
namespace interprocess {

//!A class that wraps the native Windows shared memory
//!that is implemented as a file mapping of the paging file.
//!Unlike shared_memory_object, windows_shared_memory has
//!no kernel persistence and the shared memory is destroyed
//!when all processes destroy all their windows_shared_memory
//!objects and mapped regions for the same shared memory
//!or the processes end/crash.
//!
//!Warning: Windows native shared memory and interprocess portable
//!shared memory (boost::interprocess::shared_memory_object)
//!can't communicate between them.
class windows_shared_memory
{
   /// @cond
   //Non-copyable and non-assignable
   windows_shared_memory(const windows_shared_memory &);
   windows_shared_memory &operator=(const windows_shared_memory &);
   /// @endcond

   public:

   //!Default constructor.
   //!Represents an empty windows_shared_memory.
   windows_shared_memory();

   //!Creates a new native shared memory with name "name" and mode "mode",
   //!with the access mode "mode".
   //!If the file previously exists, throws an error.
   windows_shared_memory(create_only_t, const char *name, mode_t mode, std::size_t size)
   {  this->priv_open_or_create(detail::DoCreate, name, mode, size);  }

   //!Tries to create a shared memory object with name "name" and mode "mode", with the
   //!access mode "mode". If the file previously exists, it tries to open it with mode "mode".
   //!Otherwise throws an error.
   windows_shared_memory(open_or_create_t, const char *name, mode_t mode, std::size_t size)
   {  this->priv_open_or_create(detail::DoOpenOrCreate, name, mode, size);  }

   //!Tries to open a shared memory object with name "name", with the access mode "mode". 
   //!If the file does not previously exist, it throws an error.
   windows_shared_memory(open_only_t, const char *name, mode_t mode)
   {  this->priv_open_or_create(detail::DoOpen, name, mode, 0);  }

   //!Moves the ownership of "moved"'s shared memory object to *this. 
   //!After the call, "moved" does not represent any shared memory object. 
   //!Does not throw
   #ifndef BOOST_INTERPROCESS_RVALUE_REFERENCE
   windows_shared_memory
      (detail::moved_object<windows_shared_memory> moved)
   {  this->swap(moved.get());   }
   #else
   windows_shared_memory(windows_shared_memory &&moved)
   {  this->swap(moved);   }
   #endif

   //!Moves the ownership of "moved"'s shared memory to *this.
   //!After the call, "moved" does not represent any shared memory. 
   //!Does not throw
   #ifndef BOOST_INTERPROCESS_RVALUE_REFERENCE
   windows_shared_memory &operator=
      (detail::moved_object<windows_shared_memory> moved)
   {  
      windows_shared_memory tmp(moved);
      this->swap(tmp);
      return *this;  
   }
   #else
   windows_shared_memory &operator=(windows_shared_memory &&moved)
   {  
      windows_shared_memory tmp(detail::move_impl(moved));
      this->swap(tmp);
      return *this;  
   }
   #endif

   //!Swaps to shared_memory_objects. Does not throw
   void swap(windows_shared_memory &other);

   //!Destroys *this. All mapped regions are still valid after
   //!destruction. When all mapped regions and windows_shared_memory
   //!objects referring the shared memory are destroyed, the
   //!operating system will destroy the shared memory.
   ~windows_shared_memory();

   //!Returns the name of the shared memory.
   const char *get_name() const;

   //!Returns access mode
   mode_t get_mode() const;

   //!Returns the mapping handle. Never throws
   mapping_handle_t get_mapping_handle() const;

   /// @cond
   private:

   //!Closes a previously opened file mapping. Never throws.
   void priv_close();

   //!Closes a previously opened file mapping. Never throws.
   bool priv_open_or_create(detail::create_enum_t type, const char *filename, mode_t mode, std::size_t size);

   void *         m_handle;
   mode_t         m_mode;
   std::string    m_name;
   /// @endcond
};

/// @cond

inline windows_shared_memory::windows_shared_memory() 
   :  m_handle(0)
{}

inline windows_shared_memory::~windows_shared_memory() 
{  this->priv_close(); }

inline const char *windows_shared_memory::get_name() const
{  return m_name.c_str(); }

inline void windows_shared_memory::swap(windows_shared_memory &other)
{  
   std::swap(m_handle,  other.m_handle);
   std::swap(m_mode,    other.m_mode);
   m_name.swap(other.m_name);   
}

inline mapping_handle_t windows_shared_memory::get_mapping_handle() const
{  mapping_handle_t mhnd = { m_handle, true};   return mhnd;   }

inline mode_t windows_shared_memory::get_mode() const
{  return m_mode; }

inline bool windows_shared_memory::priv_open_or_create
   (detail::create_enum_t type, const char *filename, mode_t mode, std::size_t size)
{
   m_name = filename ? filename : "";

   unsigned long file_map_access = 0;
   unsigned long map_access = 0;

   switch(mode)
   {
      case read_only:
         file_map_access   |= winapi::page_readonly;
         map_access        |= winapi::file_map_read;
      break;
      case read_write:
         file_map_access   |= winapi::page_readwrite;
         map_access        |= winapi::file_map_write;
      break;
      case copy_on_write:
         file_map_access   |= winapi::page_writecopy;
         map_access        |= winapi::file_map_copy;
      break;
      default:
         {
            error_info err(mode_error);
            throw interprocess_exception(err);
         }
      break;
   }

   switch(type){
      case detail::DoOpen:
         m_handle = winapi::open_file_mapping
            (map_access, filename);
      break;
      case detail::DoCreate:
      case detail::DoOpenOrCreate:
      {
         __int64 s = size;
         unsigned long high_size(s >> 32), low_size((boost::uint32_t)s);
         m_handle = winapi::create_file_mapping
            (winapi::invalid_handle_value, file_map_access, high_size, low_size, filename);
      }
      break;
      default:
         {
            error_info err = other_error;
            throw interprocess_exception(err);
         }
   }

   if(!m_handle || (type == detail::DoCreate && winapi::get_last_error() == winapi::error_already_exists)){
      error_info err = system_error_code();
      this->priv_close();
      throw interprocess_exception(err);
   }

   m_mode = mode;
   return true;
}

inline void windows_shared_memory::priv_close()
{
   if(m_handle){
      winapi::close_handle(m_handle);
      m_handle = 0;
   }
}

//!Trait class to detect if a type is
//!movable
template<>
struct is_movable<windows_shared_memory>
{
   static const bool value = true;
};

///@endcond

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_WINDOWS_SHARED_MEMORY_HPP

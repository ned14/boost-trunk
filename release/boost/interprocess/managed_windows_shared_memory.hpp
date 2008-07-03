//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2008. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_MANAGED_WINDOWS_SHARED_MEMORY_HPP
#define BOOST_INTERPROCESS_MANAGED_WINDOWS_SHARED_MEMORY_HPP

#if (defined _MSC_VER) && (_MSC_VER >= 1200)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/detail/managed_open_or_create_impl.hpp>
#include <boost/interprocess/detail/managed_memory_impl.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/windows_shared_memory.hpp>
#include <boost/interprocess/detail/move.hpp>

namespace boost {
namespace interprocess {

//!A basic managed windows shared memory creation class. Initializes the 
//!shared memory segment. Inherits all basic functionality from 
//!basic_managed_memory_impl<CharType, AllocationAlgorithm, IndexType>
//!Unlike basic_managed_shared_memory, it has
//!no kernel persistence and the shared memory is destroyed
//!when all processes destroy all their windows_shared_memory
//!objects and mapped regions for the same shared memory
//!or the processes end/crash.
//!
//!Warning: basic_managed_windows_shared_memory and
//!basic_managed_shared_memory can't communicate between them.
template
      <
         class CharType, 
         class AllocationAlgorithm, 
         template<class IndexConfig> class IndexType
      >
class basic_managed_windows_shared_memory 
   : public detail::basic_managed_memory_impl
      <CharType, AllocationAlgorithm, IndexType
      ,detail::managed_open_or_create_impl<windows_shared_memory>::ManagedOpenOrCreateUserOffset>
{
   /// @cond
   private:
   typedef detail::basic_managed_memory_impl 
      <CharType, AllocationAlgorithm, IndexType,
      detail::managed_open_or_create_impl<windows_shared_memory>::ManagedOpenOrCreateUserOffset>   base_t;
   typedef detail::create_open_func<base_t>        create_open_func_t;

   basic_managed_windows_shared_memory *get_this_pointer()
   {  return this;   }

   private:
   typedef typename base_t::char_ptr_holder_t   char_ptr_holder_t;
   /// @endcond

   public: //functions

   //!Default constructor. Does nothing.
   //!Useful in combination with move semantics
   basic_managed_windows_shared_memory()
   {}

   //!Creates shared memory and creates and places the segment manager. 
   //!This can throw.
   basic_managed_windows_shared_memory
      (create_only_t create_only, const char *name,
       std::size_t size, const void *addr = 0)
      : m_wshm(create_only, name, size, read_write, addr, 
                create_open_func_t(get_this_pointer(), detail::DoCreate))
   {}

   //!Creates shared memory and creates and places the segment manager if
   //!segment was not created. If segment was created it connects to the
   //!segment.
   //!This can throw.
   basic_managed_windows_shared_memory
      (open_or_create_t open_or_create,
      const char *name, std::size_t size, 
      const void *addr = 0)
      : m_wshm(open_or_create, name, size, read_write, addr, 
                create_open_func_t(get_this_pointer(), 
                detail::DoOpenOrCreate))
   {}

   //!Connects to a created shared memory and its segment manager.
   //!This can throw.
   basic_managed_windows_shared_memory
      (open_only_t open_only, const char* name, const void *addr = 0)
      : m_wshm(open_only, name, read_write, addr, 
                create_open_func_t(get_this_pointer(), 
                detail::DoOpen))
   {}

   //!Connects to a created shared memory and its segment manager
   //!in copy_on_write mode.
   //!This can throw.
   basic_managed_windows_shared_memory
      (open_copy_on_write_t, const char* name, const void *addr = 0)
      : m_wshm(open_only, name, copy_on_write, addr, 
                create_open_func_t(get_this_pointer(), detail::DoOpen))
   {}

   //!Connects to a created shared memory and its segment manager
   //!in read-only mode.
   //!This can throw.
   basic_managed_windows_shared_memory
      (open_read_only_t, const char* name, const void *addr = 0)
      : base_t()
      , m_wshm(open_only, name, read_only, addr, 
                create_open_func_t(get_this_pointer(), detail::DoOpen))
   {}

   //!Moves the ownership of "moved"'s managed memory to *this.
   //!Does not throw
   #ifndef BOOST_INTERPROCESS_RVALUE_REFERENCE
   basic_managed_windows_shared_memory
      (detail::moved_object<basic_managed_windows_shared_memory> moved)
   {  this->swap(moved.get());   }
   #else
   basic_managed_windows_shared_memory(basic_managed_windows_shared_memory &&moved)
   {  this->swap(moved);   }
   #endif

   //!Moves the ownership of "moved"'s managed memory to *this.
   //!Does not throw
   #ifndef BOOST_INTERPROCESS_RVALUE_REFERENCE
   basic_managed_windows_shared_memory &operator=
      (detail::moved_object<basic_managed_windows_shared_memory> moved)
   {  this->swap(moved.get());   return *this;  }
   #else
   basic_managed_windows_shared_memory &operator=
      (basic_managed_windows_shared_memory &&moved)
   {  this->swap(moved);   return *this;  }
   #endif

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. All mapped regions are still valid after
   //!destruction. When all mapped regions and basic_managed_windows_shared_memory
   //!objects referring the shared memory are destroyed, the
   //!operating system will destroy the shared memory.
   ~basic_managed_windows_shared_memory()
   {}

   //!Swaps the ownership of the managed mapped memories managed by *this and other.
   //!Never throws.
   void swap(basic_managed_windows_shared_memory &other)
   {
      base_t::swap(other);
      m_wshm.swap(other.m_wshm);
   }
   /// @cond

   //!Tries to find a previous named allocation address. Returns a memory
   //!buffer and the object count. If not found returned pointer is 0.
   //!Never throws.
   template <class T>
   std::pair<T*, std::size_t> find  (char_ptr_holder_t name)
   {
      if(m_wshm.get_mapped_region().get_mode() == read_only){
         return base_t::template find_no_lock<T>(name);
      }
      else{
         return base_t::template find<T>(name);
      }
   }

   private:
   detail::managed_open_or_create_impl<windows_shared_memory, false> m_wshm;
   /// @endcond
};

///@cond

//!Trait class to detect if a type is
//!movable
template
      <
         class CharType, 
         class AllocationAlgorithm, 
         template<class IndexConfig> class IndexType
      >
struct is_movable<basic_managed_windows_shared_memory
   <CharType,  AllocationAlgorithm, IndexType>
>
{
   static const bool value = true;
};

///@endcond

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_MANAGED_WINDOWS_SHARED_MEMORY_HPP

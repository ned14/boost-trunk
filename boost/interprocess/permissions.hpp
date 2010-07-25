//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_PERMISSIONS_HPP
#define BOOST_INTERPROCESS_PERMISSIONS_HPP

#if (defined _MSC_VER) && (_MSC_VER >= 1200)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/interprocess_fwd.hpp>

#if (defined BOOST_INTERPROCESS_WINDOWS)

#include <boost/interprocess/detail/win32_api.hpp>

#endif

//!\file
//!Describes permissions class

namespace boost {
namespace interprocess {

#if (defined BOOST_INTERPROCESS_WINDOWS)

namespace detail {

template <int Dummy>
struct unrestricted_permissions_holder
{
   static winapi::interprocess_all_access_security unrestricted;
};

template<int Dummy>
winapi::interprocess_all_access_security unrestricted_permissions_holder<Dummy>::unrestricted;

}  //namespace detail {

#endif   //defined BOOST_INTERPROCESS_WINDOWS

//!The permissions class represents permissions to be set to shared memory or
//!files, that can be constructed form usual permission representations:
//!a SECURITY_ATTRIBUTES pointer in windows or ORed rwx chmod integer in UNIX.
class permissions
{
   /// @cond
   #if (defined BOOST_INTERPROCESS_WINDOWS)
   typedef void*  os_permissions_type;
   #else
   typedef int    os_permissions_type;
   #endif   //#if (defined BOOST_INTERPROCESS_WINDOWS)
   os_permissions_type  m_perm;
   /// @endcond

   public:
   //!Constructs a permissions object from a user provided os-dependent
   //!permissions.
   permissions(os_permissions_type type)
      : m_perm(type)
   {}

   //!Constructs a default permissions object:
   //!A null security descriptor pointer for windows or 0644
   //!for UNIX.
   permissions()
   {  set_default(); }

   void set_default()
   {
      #if (defined BOOST_INTERPROCESS_WINDOWS)
      m_perm = 0;
      #else
      m_perm = 0644;
      #endif
   }

   void set_unrestricted()
   {
      #if (defined BOOST_INTERPROCESS_WINDOWS)
      m_perm = &detail::unrestricted_permissions_holder<0>::unrestricted;
      #else
      m_perm = 0666;
      #endif
   }

   void set_permissions(os_permissions_type perm)
   {  m_perm = perm; }

   os_permissions_type get_permissions() const
   {  return m_perm; }
};

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_PERMISSIONS_HPP

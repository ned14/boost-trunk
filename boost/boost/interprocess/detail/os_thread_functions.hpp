//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztañaga 2005-2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_OS_THREAD_FUNCTIONS_HPP
#define BOOST_INTERPROCESS_DETAIL_OS_THREAD_FUNCTIONS_HPP

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#if (defined BOOST_WINDOWS) && !(defined BOOST_DISABLE_WIN32)
#  include <boost/interprocess/sync/win32/win32_sync_primitives.hpp>
#else
#  ifdef BOOST_HAS_UNISTD_H
#    include <pthread.h>
#    include <unistd.h>
#  else
#    error Unknown platform
#  endif
#endif

namespace boost {
namespace interprocess {
namespace detail{

#if (defined BOOST_WINDOWS) && !(defined BOOST_DISABLE_WIN32)

typedef unsigned long OS_thread_id_t;

inline OS_thread_id_t get_current_thread_id()
{  return winapi::get_current_thread_id();  }

inline OS_thread_id_t get_invalid_thread_id()
{  return OS_thread_id_t(0xffffffff);  }

inline OS_thread_id_t equal_thread_id(OS_thread_id_t id1, OS_thread_id_t id2)
{  return id1 == id2;  }

#else    //#if (defined BOOST_WINDOWS) && !(defined BOOST_DISABLE_WIN32)

typedef pthread_t OS_thread_id_t;

inline pthread_t get_current_thread_id()
{  return pthread_self();  }

inline OS_thread_id_t invalid_thread_id()
{  
   static pthread_t invalid_id;
   return invalid_id;
}

inline OS_thread_id_t equal_thread_id(OS_thread_id_t id1, OS_thread_id_t id2)
{  return 0 != pthread_equal(id1, id2);  }

#endif   //#if (defined BOOST_WINDOWS) && !(defined BOOST_DISABLE_WIN32)

}  //namespace detail{
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_OS_THREAD_FUNCTIONS_HPP

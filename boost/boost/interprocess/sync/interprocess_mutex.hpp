//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztañaga 2005-2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
//
// Parts of the pthread code come from Boost Threads code.
//
//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2001-2003
// William E. Kempf
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation.  William E. Kempf makes no representations
// about the suitability of this software for any purpose.
// It is provided "as is" without express or implied warranty.
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_MUTEX_HPP
#define BOOST_INTERPROCESS_MUTEX_HPP

#if (defined _MSC_VER) && (_MSC_VER >= 1200)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <assert.h>

#if (defined BOOST_WINDOWS) && !(defined BOOST_DISABLE_WIN32)
#  include <boost/interprocess/sync/win32/win32_sync_primitives.hpp>
#else    //#if (defined BOOST_WINDOWS) && !(defined BOOST_DISABLE_WIN32)
#  include <pthread.h>
#  include <errno.h>   
#  include <boost/interprocess/sync/posix/pthread_helpers.hpp>   
#endif   //#if (defined BOOST_WINDOWS) && !(defined BOOST_DISABLE_WIN32)

/*!\file
   Describes interprocess_mutex class
*/

namespace boost {

namespace interprocess {

class interprocess_condition;

/*!Wraps a interprocess_mutex that can be placed in shared memory and can be 
   shared between processes. Allows timed lock tries*/
class interprocess_mutex
{
   //Non-copyable
   interprocess_mutex(const interprocess_mutex &);
   interprocess_mutex &operator=(const interprocess_mutex &);

   friend class interprocess_condition;
   public:

   /*!Constructor. Throws interprocess_exception on error.*/
   interprocess_mutex();

   /*!Destructor. If any process uses the mutex after the destructor is called
      the result is undefined. Does not throw.*/
   ~interprocess_mutex();

   /*!Effects: The calling thread tries to obtain ownership of the mutex, and
         if another thread has ownership of the mutex, it waits until it can
         obtain the ownership. If a thread takes ownership of the mutex the
         mutex must be unlocked by the same mutex.
      Throws: interprocess_exception on error.*/
   void lock();

   /*!Effects: The calling thread tries to obtain ownership of the mutex, and
         if another thread has ownership of the mutex returns immediately.
      Returns: If the thread acquires ownership of the mutex, returns true, if
         the another thread has ownership of the mutex, returns false.
      Throws: interprocess_exception on error.*/
   bool try_lock();

   /*!Effects: The calling thread will try to obtain exclusive ownership of the
         mutex if it can do so in until the specified time is reached. If the
         mutex supports recursive locking, the mutex must be unlocked the same
         number of times it is locked. 
      Returns: If the thread acquires ownership of the mutex, returns true, if
         the timeout expires returns false. 
      Throws: interprocess_exception on error.*/
   bool timed_lock(const boost::posix_time::ptime &abs_time);

   /*!Effects: The calling thread releases the exclusive ownership of the mutex.
      Throws: interprocess_exception on error.*/
   void unlock();

   private:

   #if (defined BOOST_WINDOWS) && !(defined BOOST_DISABLE_WIN32)
   volatile long m_s;
   #else    //#if (defined BOOST_WINDOWS) && !(defined BOOST_DISABLE_WIN32)
   #ifdef _POSIX_TIMEOUTS
      pthread_mutex_t   m_mut;
   #else
      pthread_mutex_t   m_mut;
      pthread_cond_t    m_cond;
      bool              m_locked;
   #endif
   #endif   //#if (defined BOOST_WINDOWS) && !(defined BOOST_DISABLE_WIN32)
};

}  //namespace interprocess {

}  //namespace boost {

#if (defined BOOST_WINDOWS) && !(defined BOOST_DISABLE_WIN32)
#  include <boost/interprocess/sync/win32/interprocess_mutex.hpp>
#else 
#  include <boost/interprocess/sync/posix/interprocess_mutex.hpp>
#endif   //#if (defined BOOST_WINDOWS) && !(defined BOOST_DISABLE_WIN32)

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_MUTEX_HPP

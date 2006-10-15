//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztañaga 2005-2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_named_upgradable_mutex_HPP
#define BOOST_INTERPROCESS_named_upgradable_mutex_HPP

#if (defined _MSC_VER) && (_MSC_VER >= 1200)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/detail/creation_tags.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/detail/managed_open_or_create_impl.hpp>
#include <boost/interprocess/sync/interprocess_upgradable_mutex.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>

/*!\file
   Describes a named upgradable mutex class for inter-process synchronization
*/

namespace boost {

namespace interprocess {

class named_condition;

/*!A upgradable mutex with a global name, so it can be found from different 
   processes. This mutex can't be placed in shared memory, and
   each process should have it's own named upgradable mutex.*/
class named_upgradable_mutex
{
   //Non-copyable
   named_upgradable_mutex();
   named_upgradable_mutex(const named_upgradable_mutex &);
   named_upgradable_mutex &operator=(const named_upgradable_mutex &);
   friend class named_condition;

   public:
   /*!Creates a global interprocess_mutex with a name.*/
   named_upgradable_mutex(detail::create_only_t create_only, const char *name);

   /*!Opens or creates a global upgradable mutex with a name. 
      If the upgradable mutex is created, this call is equivalent to create(). 
      If the upgradable mutex is already created, this call is equivalent to open(). 
      Throws interprocess_exception on error.*/
   named_upgradable_mutex(detail::open_or_create_t open_or_create, const char *name);

   /*!Opens a global upgradable mutex with a name if that mutex is previously.
      created. If it is not previously created this function return false.
      Throws interprocess_exception on error.*/
   named_upgradable_mutex(detail::open_only_t open_only, const char *name);

   /*!Closes the named upgradable mutex. Does not throw*/
   ~named_upgradable_mutex();

   //Exclusive locking

   /*!Effects: The calling thread tries to obtain exclusive ownership of the mutex,
         and if another thread has exclusive, sharable or upgradable ownership of
         the mutex, it waits until it can obtain the ownership.
      Throws: interprocess_exception on error.*/
   void lock();

   /*!Effects: The calling thread tries to acquire exclusive ownership of the mutex
         without waiting. If no other thread has exclusive, sharable or upgradable
         ownership of the mutex this succeeds.
      Returns: If it can acquire exclusive ownership immediately returns true.
         If it has to wait, returns false.
      Throws: interprocess_exception on error.*/
   bool try_lock();

   /*!Effects: The calling thread tries to acquire exclusive ownership of the mutex
         waiting if necessary until no other thread has has exclusive, sharable or
         upgradable ownership of the mutex or abs_time is reached. 
      Returns: If acquires exclusive ownership, returns true. Otherwise returns false. 
      Throws: interprocess_exception on error.*/
   bool timed_lock(const boost::posix_time::ptime &abs_time);

   /*!Precondition: The thread must have exclusive ownership of the mutex. 
      Effects: The calling thread releases the exclusive ownership of the mutex. 
      Throws: An exception derived from interprocess_exception on error.*/
   void unlock();

   //Sharable locking

   /*!Effects: The calling thread tries to obtain sharable ownership of the mutex,
         and if another thread has exclusive or upgradable ownership of the mutex,
         waits until it can obtain the ownership.
      Throws: interprocess_exception on error.*/
   void lock_sharable();

   /*!Effects: The calling thread tries to acquire sharable ownership of the mutex
         without waiting. If no other thread has has exclusive or upgradable ownership
         of the mutex this succeeds. 
      Returns: If it can acquire sharable ownership immediately returns true. If it
         has to wait, returns false. 
      Throws: interprocess_exception on error.*/
   bool try_lock_sharable();

   /*!Effects: The calling thread tries to acquire sharable ownership of the mutex
         waiting if necessary until no other thread has has exclusive or upgradable
         ownership of the mutex or abs_time is reached. 
      Returns: If acquires sharable ownership, returns true. Otherwise returns false. 
      Throws: interprocess_exception on error.*/
   bool timed_lock_sharable(const boost::posix_time::ptime &abs_time);

   /*!Precondition: The thread must have sharable ownership of the mutex. 
      Effects: The calling thread releases the sharable ownership of the mutex. 
      Throws: An exception derived from interprocess_exception on error.*/
   void unlock_sharable();

   //Upgradable locking

   /*!Effects: The calling thread tries to obtain upgradable ownership of the mutex,
         and if another thread has exclusive or upgradable ownership of the mutex,
         waits until it can obtain the ownership.
      Throws: interprocess_exception on error.*/
   void lock_upgradable();

   /*!Effects: The calling thread tries to acquire upgradable ownership of the mutex
         without waiting. If no other thread has has exclusive or upgradable ownership
         of the mutex this succeeds. 
      Returns: If it can acquire upgradable ownership immediately returns true.
         If it has to wait, returns false.
      Throws: interprocess_exception on error.*/
   bool try_lock_upgradable();

   /*!Effects: The calling thread tries to acquire upgradable ownership of the mutex
         waiting if necessary until no other thread has has exclusive or upgradable
         ownership of the mutex or abs_time is reached.
      Returns: If acquires upgradable ownership, returns true. Otherwise returns false. 
      Throws: interprocess_exception on error.*/
   bool timed_lock_upgradable(const boost::posix_time::ptime &abs_time);

   /*!Precondition: The thread must have upgradable ownership of the mutex. 
      Effects: The calling thread releases the upgradable ownership of the mutex. 
      Throws: An exception derived from interprocess_exception on error.*/
   void unlock_upgradable();

   //Demotions

   /*!Precondition: The thread must have exclusive ownership of the mutex. 
      Effects: The thread atomically releases exclusive ownership and acquires
         upgradable ownership. This operation is non-blocking. 
      Throws: An exception derived from interprocess_exception on error.*/
   void unlock_and_lock_upgradable();

   /*!Precondition: The thread must have exclusive ownership of the mutex. 
      Effects: The thread atomically releases exclusive ownership and acquires
         sharable ownership. This operation is non-blocking. 
      Throws: An exception derived from interprocess_exception on error.*/
   void unlock_and_lock_sharable();

   /*!Precondition: The thread must have upgradable ownership of the mutex. 
      Effects: The thread atomically releases upgradable ownership and acquires
         sharable ownership. This operation is non-blocking. 
      Throws: An exception derived from interprocess_exception on error.*/
   void unlock_upgradable_and_lock_sharable();

   //Promotions

   /*!Precondition: The thread must have upgradable ownership of the mutex. 
      Effects: The thread atomically releases upgradable ownership and acquires
         exclusive ownership. This operation will block until all threads with
         sharable ownership releas it. 
      Throws: An exception derived from interprocess_exception on error.*/
   void unlock_upgradable_and_lock();

   /*!Precondition: The thread must have upgradable ownership of the mutex. 
      Effects: The thread atomically releases upgradable ownership and tries to
         acquire exclusive ownership. This operation will fail if there are threads
         with sharable ownership, but it will maintain upgradable ownership. 
      Returns: If acquires exclusive ownership, returns true. Otherwise returns false.
      Throws: An exception derived from interprocess_exception on error.*/
   bool try_unlock_upgradable_and_lock();

   /*!Precondition: The thread must have upgradable ownership of the mutex. 
      Effects: The thread atomically releases upgradable ownership and tries to acquire
         exclusive ownership, waiting if necessary until abs_time. This operation will
         fail if there are threads with sharable ownership or timeout reaches, but it
         will maintain upgradable ownership. 
      Returns: If acquires exclusive ownership, returns true. Otherwise returns false. 
      Throws: An exception derived from interprocess_exception on error. */
   bool timed_unlock_upgradable_and_lock(const boost::posix_time::ptime &abs_time);

   /*!Precondition: The thread must have sharable ownership of the mutex. 
      Effects: The thread atomically releases sharable ownership and tries to acquire
         exclusive ownership. This operation will fail if there are threads with sharable
         or upgradable ownership, but it will maintain sharable ownership.
      Returns: If acquires exclusive ownership, returns true. Otherwise returns false. 
      Throws: An exception derived from interprocess_exception on error.*/
   bool try_unlock_sharable_and_lock();

   bool try_unlock_sharable_and_lock_upgradable();

   /*! Erases a named upgradable mutex from the system*/
   static bool remove(const char *name);

   private:

   interprocess_upgradable_mutex *mutex() const
   {  return static_cast<interprocess_upgradable_mutex*>(m_shmem.get_address()); }

   detail::managed_open_or_create_impl<shared_memory_object> m_shmem;

   class construct_func_t;
};

class named_upgradable_mutex::construct_func_t
{
   public:
   enum CreationType {  open_only, open_or_create, create_only  };

   construct_func_t(CreationType type)
      :  m_creation_type(type){}

   bool operator()(void *address, std::size_t size, bool created) const
   {   
      switch(m_creation_type){
         case open_only:
            return true;
         break;
         case create_only:
         case open_or_create:
            if(created){
               new(address)interprocess_upgradable_mutex;
            }
            return true;
         break;

         default:
            return false;
         break;
      }
      return true;
   }
   private:
   CreationType       m_creation_type;
};

inline named_upgradable_mutex::~named_upgradable_mutex()
{}

inline named_upgradable_mutex::named_upgradable_mutex
   (detail::create_only_t, const char *name)
   :  m_shmem  (create_only
               ,name
               ,sizeof(interprocess_upgradable_mutex) +
                  detail::managed_open_or_create_impl<shared_memory_object>::
                     ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(construct_func_t::create_only))
{}

inline named_upgradable_mutex::named_upgradable_mutex
   (detail::open_or_create_t, const char *name)
   :  m_shmem  (open_or_create
               ,name
               ,sizeof(interprocess_upgradable_mutex) +
                  detail::managed_open_or_create_impl<shared_memory_object>::
                     ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(construct_func_t::open_or_create))
{}

inline named_upgradable_mutex::named_upgradable_mutex
   (detail::open_only_t, const char *name)
   :  m_shmem  (open_only
               ,name
               ,read_write
               ,0
               ,construct_func_t(construct_func_t::open_only))
{}

inline void named_upgradable_mutex::lock()
{  this->mutex()->lock();  }

inline void named_upgradable_mutex::unlock()
{  this->mutex()->unlock();  }

inline bool named_upgradable_mutex::try_lock()
{  return this->mutex()->try_lock();  }

inline bool named_upgradable_mutex::timed_lock
   (const boost::posix_time::ptime &abs_time)
{  return this->mutex()->timed_lock(abs_time);  }

inline void named_upgradable_mutex::lock_upgradable()
{  this->mutex()->lock_upgradable();  }

inline void named_upgradable_mutex::unlock_upgradable()
{  this->mutex()->unlock_upgradable();  }

inline bool named_upgradable_mutex::try_lock_upgradable()
{  return this->mutex()->try_lock_upgradable();  }

inline bool named_upgradable_mutex::timed_lock_upgradable
   (const boost::posix_time::ptime &abs_time)
{  return this->mutex()->timed_lock_upgradable(abs_time);  }

inline void named_upgradable_mutex::lock_sharable()
{  this->mutex()->lock_sharable();  }

inline void named_upgradable_mutex::unlock_sharable()
{  this->mutex()->unlock_sharable();  }

inline bool named_upgradable_mutex::try_lock_sharable()
{  return this->mutex()->try_lock_sharable();  }

inline bool named_upgradable_mutex::timed_lock_sharable
   (const boost::posix_time::ptime &abs_time)
{  return this->mutex()->timed_lock_sharable(abs_time);  }

inline void named_upgradable_mutex::unlock_and_lock_upgradable()
{  this->mutex()->unlock_and_lock_upgradable();  }

inline void named_upgradable_mutex::unlock_and_lock_sharable()
{  this->mutex()->unlock_and_lock_sharable();  }

inline void named_upgradable_mutex::unlock_upgradable_and_lock_sharable()
{  this->mutex()->unlock_upgradable_and_lock_sharable();  }

inline void named_upgradable_mutex::unlock_upgradable_and_lock()
{  this->mutex()->unlock_upgradable_and_lock();  }

inline bool named_upgradable_mutex::try_unlock_upgradable_and_lock()
{  return this->mutex()->try_unlock_upgradable_and_lock();  }

inline bool named_upgradable_mutex::timed_unlock_upgradable_and_lock
   (const boost::posix_time::ptime &abs_time)
{  return this->mutex()->timed_unlock_upgradable_and_lock(abs_time);  }

inline bool named_upgradable_mutex::try_unlock_sharable_and_lock()
{  return this->mutex()->try_unlock_sharable_and_lock();  }

inline bool named_upgradable_mutex::try_unlock_sharable_and_lock_upgradable()
{  return this->mutex()->try_unlock_sharable_and_lock_upgradable();  }

inline bool named_upgradable_mutex::remove(const char *name)
{  return shared_memory_object::remove(name); }

}  //namespace interprocess {

}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_named_upgradable_mutex_HPP

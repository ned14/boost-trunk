//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gazta�aga 2004-2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/sync/named_semaphore.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include "named_creation_template.hpp"
#include "mutex_test_template.hpp"

static const std::size_t SemCount      = 1;
static const std::size_t RecSemCount   = 100;
static const char *      SemName = "named_semaphore";

struct deleter
{
   ~deleter()
   {  boost::interprocess::named_semaphore::remove(SemName); }
};

//This wrapper is necessary to plug this class
//in named creation tests and interprocess_mutex tests
class named_semaphore_test_wrapper
   : public deleter, public boost::interprocess::named_semaphore
{
   public:
   named_semaphore_test_wrapper()
      :  boost::interprocess::named_semaphore
            (boost::interprocess::open_or_create, SemName, SemCount)
   {}

   named_semaphore_test_wrapper(boost::interprocess::detail::create_only_t)
      :  boost::interprocess::named_semaphore
            (boost::interprocess::create_only, SemName, SemCount)
   {}

   named_semaphore_test_wrapper(boost::interprocess::detail::open_only_t)
      :  boost::interprocess::named_semaphore
            (boost::interprocess::open_only, SemName)
   {}

   named_semaphore_test_wrapper(boost::interprocess::detail::open_or_create_t)
      :  boost::interprocess::named_semaphore
            (boost::interprocess::open_or_create, SemName, SemCount)
   {}

   ~named_semaphore_test_wrapper()
   {
      try{
         
      }
      catch(...){
      }
   }

   void lock()
   {  this->wait();  }

   bool try_lock()
   {  return this->try_wait();  }

   bool timed_lock(const boost::posix_time::ptime &pt)
   {  return this->timed_wait(pt);  }

   void unlock()
   {  this->post();  }

   protected:
   named_semaphore_test_wrapper(int initial_count)
      :  boost::interprocess::named_semaphore
            (boost::interprocess::create_only, SemName, initial_count)
   {}
};

//This wrapper is necessary to plug this class
//in recursive tests
class recursive_named_semaphore_test_wrapper
   :  public named_semaphore_test_wrapper
{
   public:
   recursive_named_semaphore_test_wrapper()
      :  named_semaphore_test_wrapper(RecSemCount)
   {}
};

int main ()
{
   using namespace boost::interprocess;
   try{
      named_semaphore::remove(SemName);
      test::test_named_creation<named_semaphore_test_wrapper>();
      test::test_all_lock<named_semaphore_test_wrapper>();
      test::test_all_recursive_lock<recursive_named_semaphore_test_wrapper>();
      test::test_all_mutex<false, named_semaphore_test_wrapper>();
   }
   catch(std::exception &ex){
      std::cout << ex.what() << std::endl;
      return 1;
   }
   return 0;
}

#include <boost/interprocess/detail/config_end.hpp>

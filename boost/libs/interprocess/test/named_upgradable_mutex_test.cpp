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
#include "mutex_test_template.hpp"
#include "sharable_mutex_test_template.hpp"
#include "named_creation_template.hpp"
#include <boost/interprocess/sync/named_upgradable_mutex.hpp>

struct deleter
{
   ~deleter()
   {  boost::interprocess::named_upgradable_mutex::remove("named_upgradable_mutex"); }
};

//This wrapper is necessary to have a default constructor
//in generic mutex_test_template functions
class named_upgradable_mutex_lock_test_wrapper
   : public boost::interprocess::named_upgradable_mutex
{
   public:
   named_upgradable_mutex_lock_test_wrapper()
      :  boost::interprocess::named_upgradable_mutex
            (boost::interprocess::open_or_create, "named_upgradable_mutex")
   {}
};

//This wrapper is necessary to have a common constructor
//in generic named_creation_template functions
class named_upgradable_mutex_creation_test_wrapper
   : public deleter, public boost::interprocess::named_upgradable_mutex
{
   public:
   named_upgradable_mutex_creation_test_wrapper
      (boost::interprocess::detail::create_only_t)
      :  boost::interprocess::named_upgradable_mutex
            (boost::interprocess::create_only, "named_upgradable_mutex")
   {}

   named_upgradable_mutex_creation_test_wrapper
      (boost::interprocess::detail::open_only_t)
      :  boost::interprocess::named_upgradable_mutex
            (boost::interprocess::open_only, "named_upgradable_mutex")
   {}

   named_upgradable_mutex_creation_test_wrapper
      (boost::interprocess::detail::open_or_create_t)
      :  boost::interprocess::named_upgradable_mutex
            (boost::interprocess::open_or_create, "named_upgradable_mutex")
   {}
};

int main ()
{
   try{
      using namespace boost::interprocess;
      named_upgradable_mutex::remove("named_upgradable_mutex");

      test::test_named_creation<named_upgradable_mutex_creation_test_wrapper>();
/*
      test::test_all_lock<named_upgradable_mutex_lock_test_wrapper>();
      test::test_all_mutex<true, named_upgradable_mutex_lock_test_wrapper>();
      test::test_all_sharable_mutex<true, named_upgradable_mutex_lock_test_wrapper>();
*/
   }
   catch(std::exception &ex){
      std::cout << ex.what() << std::endl;
      return 1;
   }
   return 0;
}

#include <boost/interprocess/detail/config_end.hpp>

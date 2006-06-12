//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztañaga 2005-2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/indexes/null_index.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/mem_algo/simple_seq_fit.hpp>
#include <cstddef>
#include <assert.h>

using namespace boost::interprocess;
typedef basic_managed_shared_memory
   <char, simple_seq_fit<mutex_family>, null_index>
my_shared_objects_t;

int main ()
{
   //Create shared memory
   my_shared_objects_t::remove("MySharedMemory");
   my_shared_objects_t segment
      (create_only,
      "MySharedMemory",//segment name
      65536);           //segment size in bytes

   //Allocate a portion of the segment
   void * shptr   = segment.allocate(1024/*bytes to allocate*/);
   my_shared_objects_t::handle_t handle = segment.get_handle_from_address(shptr);
   if(!segment.belongs_to_segment(shptr)){
      return 1;
   }
   if(shptr != segment.get_address_from_handle(handle)){
      return 1;
   }

   segment.deallocate(shptr);
   return 0;
}

#include <boost/interprocess/detail/config_end.hpp>

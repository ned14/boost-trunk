//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2006-2007. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#include <boost/interprocess/detail/config_begin.hpp>
//[doc_managed_multiple_allocation
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/detail/move.hpp> //boost::interprocess::move
#include <cassert>//assert
#include <cstring>//std::memset
#include <new>    //std::nothrow
#include <vector> //std::vector


int main()
{
   using namespace boost::interprocess;
   typedef managed_shared_memory::multiallocation_chain multiallocation_chain;

   //Remove shared memory on construction and destruction
   struct shm_remove
   {
      shm_remove() { shared_memory_object::remove("MySharedMemory"); }
      ~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
   } remover;

   managed_shared_memory managed_shm(create_only, "MySharedMemory", 65536);

   //Allocate 16 elements of 100 bytes in a single call. Non-throwing version.
   multiallocation_chain chain(managed_shm.allocate_many(100, 16, std::nothrow));

   //Check if the memory allocation was successful
   if(chain.empty()) return 1;

   //Allocated buffers
   std::vector<void*> allocated_buffers;

   //Initialize our data
   while(!chain.empty()){
      void *buf = chain.front();
      chain.pop_front();
      allocated_buffers.push_back(buf);
      //The iterator must be incremented before overwriting memory
      //because otherwise, the iterator is invalidated.
      std::memset(buf, 0, 100);
   }

   //Now deallocate
   while(!allocated_buffers.empty()){
      managed_shm.deallocate(allocated_buffers.back());
      allocated_buffers.pop_back();
   }

   //Allocate 10 buffers of different sizes in a single call. Throwing version
   std::size_t sizes[10];
   for(std::size_t i = 0; i < 10; ++i)
      sizes[i] = i*3;

   chain = managed_shm.allocate_many(sizes, 10);
   managed_shm.deallocate_many(boost::interprocess::move(chain));
   return 0;
}
//]
#include <boost/interprocess/detail/config_end.hpp>

//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2004-2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/slist.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/offset_ptr.hpp>
#include "dummy_test_allocator.hpp"
#include "list_test.hpp"
#include "movable_int.hpp"
#include "emplace_test.hpp"

using namespace boost::interprocess;

//Explicit instantiation to detect compilation errors
template class boost::interprocess::slist<test::movable_and_copyable_int, 
   test::dummy_test_allocator<test::movable_and_copyable_int> >;

typedef allocator<int, managed_shared_memory::segment_manager> ShmemAllocator;
typedef slist<int, ShmemAllocator> MyList;

//typedef allocator<volatile int, managed_shared_memory::segment_manager> ShmemVolatileAllocator;
//typedef slist<volatile int, ShmemVolatileAllocator> MyVolatileList;

typedef allocator<test::movable_int, managed_shared_memory::segment_manager> ShmemMoveAllocator;
typedef slist<test::movable_int, ShmemMoveAllocator> MyMoveList;

typedef allocator<test::movable_and_copyable_int, managed_shared_memory::segment_manager> ShmemCopyMoveAllocator;
typedef slist<test::movable_and_copyable_int, ShmemCopyMoveAllocator> MyCopyMoveList;

typedef allocator<test::copyable_int, managed_shared_memory::segment_manager> ShmemCopyAllocator;
typedef slist<test::copyable_int, ShmemCopyAllocator> MyCopyList;

class recursive_slist
{
public:
   int id_;
   slist<recursive_slist> slist_;
};

void recursive_slist_test()//Test for recursive types
{
   slist<recursive_slist> recursive_list_list;
}

int main ()
{
   recursive_slist_test();
   {
      //Now test move semantics
      slist<recursive_slist> original;
      slist<recursive_slist> move_ctor(boost::interprocess::move(original));
      slist<recursive_slist> move_assign;
      move_assign = boost::interprocess::move(move_ctor);
      move_assign.swap(original);
   }

   if(test::list_test<managed_shared_memory, MyList, false>())
      return 1;

   if(test::list_test<managed_shared_memory, MyMoveList, false>())
      return 1;

   if(test::list_test<managed_shared_memory, MyCopyMoveList, false>())
      return 1;

//   if(test::list_test<managed_shared_memory, MyVolatileList, false>())
//      return 1;

   if(test::list_test<managed_shared_memory, MyCopyList, false>())
      return 1;

   const test::EmplaceOptions Options = (test::EmplaceOptions)
      (test::EMPLACE_FRONT | test::EMPLACE_AFTER | test::EMPLACE_BEFORE  | test::EMPLACE_AFTER);

   if(!boost::interprocess::test::test_emplace
      < slist<test::EmplaceInt>, Options>())
      return 1;
}

#include <boost/interprocess/detail/config_end.hpp>


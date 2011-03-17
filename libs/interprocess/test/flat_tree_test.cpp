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
#include <set>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/flat_set.hpp>
#include <boost/interprocess/containers/flat_map.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/indexes/flat_map_index.hpp>
#include "print_container.hpp"
#include "dummy_test_allocator.hpp"
#include "movable_int.hpp"
#include "set_test.hpp"
#include "map_test.hpp"
#include "emplace_test.hpp"

/////////////////////////////////////////////////////////////////
//                                                               
//  This example repeats the same operations with std::set and   
//  shmem_set using the node allocator                           
//  and compares the values of both containers                   
//                                                               
/////////////////////////////////////////////////////////////////

using namespace boost::interprocess;
/*
//Explicit instantiation to detect compilation errors
template class boost::interprocess::flat_set
   <test::movable_and_copyable_int
   ,std::less<test::movable_and_copyable_int>
   ,test::dummy_test_allocator<test::movable_and_copyable_int> >;

template class boost::interprocess::flat_map
   <test::movable_and_copyable_int
   ,test::movable_and_copyable_int
   ,std::less<test::movable_and_copyable_int>
   ,test::dummy_test_allocator<std::pair<test::movable_and_copyable_int
                                        ,test::movable_and_copyable_int> > >;

template class boost::interprocess::flat_multiset
   <test::movable_and_copyable_int
   ,std::less<test::movable_and_copyable_int>
   ,test::dummy_test_allocator<test::movable_and_copyable_int> >;

template class boost::interprocess::flat_multimap
   <test::movable_and_copyable_int
   ,test::movable_and_copyable_int
   ,std::less<test::movable_and_copyable_int>
   ,test::dummy_test_allocator<std::pair<test::movable_and_copyable_int
                                        ,test::movable_and_copyable_int> > >;
*/
//Customize managed_shared_memory class
typedef basic_managed_shared_memory
   <char,
    //simple_seq_fit<mutex_family>,
    rbtree_best_fit<mutex_family>,
    iset_index
   > my_managed_shared_memory;

//Alias allocator type
typedef allocator<int, my_managed_shared_memory::segment_manager> 
   shmem_allocator_t;
typedef allocator<test::movable_int, my_managed_shared_memory::segment_manager> 
   shmem_movable_allocator_t;
typedef allocator<std::pair<int, int>, my_managed_shared_memory::segment_manager> 
   shmem_pair_allocator_t;
typedef allocator<std::pair<test::movable_int, test::movable_int>, my_managed_shared_memory::segment_manager> 
   shmem_movable_pair_allocator_t;

typedef allocator<test::movable_and_copyable_int, my_managed_shared_memory::segment_manager> 
   shmem_move_copy_allocator_t;

typedef allocator<test::copyable_int, my_managed_shared_memory::segment_manager> 
   shmem_copy_allocator_t;

typedef allocator<std::pair<test::movable_and_copyable_int, test::movable_and_copyable_int>, my_managed_shared_memory::segment_manager> 
   shmem_move_copy_pair_allocator_t;

//Alias set types
typedef std::set<int>                                                   MyStdSet;
typedef std::multiset<int>                                              MyStdMultiSet;
typedef std::map<int, int>                                              MyStdMap;
typedef std::multimap<int, int>                                         MyStdMultiMap;

typedef flat_set<int, std::less<int>, shmem_allocator_t>                MyShmSet;
typedef flat_multiset<int, std::less<int>, shmem_allocator_t>           MyShmMultiSet;
typedef flat_map<int, int, std::less<int>, shmem_pair_allocator_t>      MyShmMap;
typedef flat_multimap<int, int, std::less<int>, shmem_pair_allocator_t> MyShmMultiMap;

typedef flat_set<test::movable_int, std::less<test::movable_int>
                ,shmem_movable_allocator_t>                             MyMovableShmSet;
typedef flat_multiset<test::movable_int,std::less<test::movable_int>
                     ,shmem_movable_allocator_t>                        MyMovableShmMultiSet;
typedef flat_map<test::movable_int, test::movable_int
                ,std::less<test::movable_int>
                ,shmem_movable_pair_allocator_t>                        MyMovableShmMap;
typedef flat_multimap<test::movable_int, test::movable_int
                ,std::less<test::movable_int>
                ,shmem_movable_pair_allocator_t>                        MyMovableShmMultiMap;

typedef flat_set<test::movable_and_copyable_int, std::less<test::movable_and_copyable_int>
                ,shmem_move_copy_allocator_t>                             MyMoveCopyShmSet;
typedef flat_multiset<test::movable_and_copyable_int,std::less<test::movable_and_copyable_int>
                     ,shmem_move_copy_allocator_t>                        MyMoveCopyShmMultiSet;

typedef flat_set<test::copyable_int, std::less<test::copyable_int>
                ,shmem_copy_allocator_t>                                MyCopyShmSet;
typedef flat_multiset<test::copyable_int,std::less<test::copyable_int>
                     ,shmem_copy_allocator_t>                           MyCopyShmMultiSet;

typedef flat_map<test::movable_and_copyable_int, test::movable_and_copyable_int
                ,std::less<test::movable_and_copyable_int>
                ,shmem_move_copy_pair_allocator_t>                        MyMoveCopyShmMap;
typedef flat_multimap<test::movable_and_copyable_int, test::movable_and_copyable_int
                ,std::less<test::movable_and_copyable_int>
                ,shmem_move_copy_pair_allocator_t>                        MyMoveCopyShmMultiMap;


//Test recursive structures
class recursive_flat_set
{
public:
   int id_;
   flat_set<recursive_flat_set> flat_set_;
   friend bool operator< (const recursive_flat_set &a, const recursive_flat_set &b)
   {  return a.id_ < b.id_;   }
};

class recursive_flat_map
{
public:
   int id_;
   flat_map<recursive_flat_map, recursive_flat_map> map_;
   recursive_flat_map (const recursive_flat_map&x)
      :id_(x.id_), map_(x.map_)
   {}
   recursive_flat_map &operator=(const recursive_flat_map &x)
   { id_ = x.id_; map_ = x.map_; return *this; }

   friend bool operator< (const recursive_flat_map &a, const recursive_flat_map &b)
   {  return a.id_ < b.id_;   }
};

//Test recursive structures
class recursive_flat_multiset
{
public:
   int id_;
   flat_multiset<recursive_flat_multiset> flat_set_;
   friend bool operator< (const recursive_flat_multiset &a, const recursive_flat_set &b)
   {  return a.id_ < b.id_;   }
};

class recursive_flat_multimap
{
public:
   int id_;
   flat_map<recursive_flat_multimap, recursive_flat_multimap> map_;
   recursive_flat_multimap (const recursive_flat_multimap&x)
      :id_(x.id_), map_(x.map_)
   {}
   recursive_flat_multimap &operator=(const recursive_flat_multimap &x)
   { id_ = x.id_; map_ = x.map_; return *this; }
   friend bool operator< (const recursive_flat_multimap &a, const recursive_flat_multimap &b)
   {  return a.id_ < b.id_;   }
};

template<class C>
void test_move()
{
   //Now test move semantics
   C original;
   C move_ctor(boost::interprocess::move(original));
   C move_assign;
   move_assign = boost::interprocess::move(move_ctor);
   move_assign.swap(original);
}

int main()
{
   using namespace boost::interprocess::test;

   //Now test move semantics
   {
      test_move<flat_set<recursive_flat_set> >();
      test_move<flat_multiset<recursive_flat_multiset> >();
      test_move<flat_map<recursive_flat_map, recursive_flat_map> >();
      test_move<flat_multimap<recursive_flat_multimap, recursive_flat_multimap> >();
   }


   if (0 != set_test<my_managed_shared_memory
                  ,MyShmSet
                  ,MyStdSet
                  ,MyShmMultiSet
                  ,MyStdMultiSet>()){
      std::cout << "Error in set_test<MyShmSet>" << std::endl;
      return 1;
   }

   if (0 != set_test_copyable<my_managed_shared_memory
                  ,MyShmSet
                  ,MyStdSet
                  ,MyShmMultiSet
                  ,MyStdMultiSet>()){
      std::cout << "Error in set_test<MyShmSet>" << std::endl;
      return 1;
   }

   if (0 != set_test<my_managed_shared_memory
                  ,MyMovableShmSet
                  ,MyStdSet
                  ,MyMovableShmMultiSet
                  ,MyStdMultiSet>()){
      std::cout << "Error in set_test<MyMovableShmSet>" << std::endl;
      return 1;
   }

   if (0 != set_test<my_managed_shared_memory
                  ,MyMoveCopyShmSet
                  ,MyStdSet
                  ,MyMoveCopyShmMultiSet
                  ,MyStdMultiSet>()){
      std::cout << "Error in set_test<MyMoveCopyShmSet>" << std::endl;
      return 1;
   }

   if (0 != set_test<my_managed_shared_memory
                  ,MyCopyShmSet
                  ,MyStdSet
                  ,MyCopyShmMultiSet
                  ,MyStdMultiSet>()){
      std::cout << "Error in set_test<MyCopyShmSet>" << std::endl;
      return 1;
   }

   if (0 != map_test<my_managed_shared_memory
                  ,MyShmMap
                  ,MyStdMap
                  ,MyShmMultiMap
                  ,MyStdMultiMap>()){
      std::cout << "Error in set_test<MyShmMap>" << std::endl;
      return 1;
   }

   if (0 != map_test_copyable<my_managed_shared_memory
                  ,MyShmMap
                  ,MyStdMap
                  ,MyShmMultiMap
                  ,MyStdMultiMap>()){
      std::cout << "Error in set_test<MyShmMap>" << std::endl;
      return 1;
   }

//   if (0 != map_test<my_managed_shared_memory
//                  ,MyMovableShmMap
//                  ,MyStdMap
//                  ,MyMovableShmMultiMap
//                  ,MyStdMultiMap>()){
//      return 1;
//   }

   if (0 != map_test<my_managed_shared_memory
                  ,MyMoveCopyShmMap
                  ,MyStdMap
                  ,MyMoveCopyShmMultiMap
                  ,MyStdMultiMap>()){
      std::cout << "Error in set_test<MyMoveCopyShmMap>" << std::endl;
      return 1;
   }

   //#if !defined(__GNUC__) || (__GNUC__ < 4) || (__GNUC_MINOR__ < 3)
   const test::EmplaceOptions SetOptions = (test::EmplaceOptions)(test::EMPLACE_HINT | test::EMPLACE_ASSOC);
   const test::EmplaceOptions MapOptions = (test::EmplaceOptions)(test::EMPLACE_HINT_PAIR | test::EMPLACE_ASSOC_PAIR);

   if(!boost::interprocess::test::test_emplace<flat_map<test::EmplaceInt, test::EmplaceInt>, MapOptions>())
      return 1;
   if(!boost::interprocess::test::test_emplace<flat_multimap<test::EmplaceInt, test::EmplaceInt>, MapOptions>())
      return 1;
   if(!boost::interprocess::test::test_emplace<flat_set<test::EmplaceInt>, SetOptions>())
      return 1;
   if(!boost::interprocess::test::test_emplace<flat_multiset<test::EmplaceInt>, SetOptions>())
      return 1;
   //#endif   //!defined(__GNUC__)
   return 0;

}

#include <boost/interprocess/detail/config_end.hpp>

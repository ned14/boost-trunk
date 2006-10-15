//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gazta�aga 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifdef _MSC_VER
#pragma warning (disable : 4503)
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/offset_ptr.hpp>
#include <boost/interprocess/smart_ptr/unique_ptr.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/list.hpp>
#include <boost/interprocess/containers/set.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <stdio.h>

using namespace boost::interprocess;

class MyClass
{
   public:
   MyClass()
   {}
};

//Deleter. Takes a pointer to the segment manager which
//has a function to delete the object from the shared memory
//segment. 
struct MyDeleter
{
   typedef offset_ptr<MyClass> pointer;

   MyDeleter(managed_shared_memory::segment_manager *mngr)
      :  m_mngr(mngr)
   {}

   void operator()(pointer ptr)
   {  m_mngr->destroy_ptr(ptr.get());  }

   offset_ptr<managed_shared_memory::segment_manager> m_mngr;
};

typedef unique_ptr<MyClass, MyDeleter> my_unique_ptr_class;
typedef set <my_unique_ptr_class
            ,std::less<my_unique_ptr_class>
            ,allocator  <my_unique_ptr_class
                        ,managed_shared_memory::segment_manager>
            > MySet;

typedef list<my_unique_ptr_class
            ,allocator  <my_unique_ptr_class
                        ,managed_shared_memory::segment_manager>
            > MyList;

typedef vector <my_unique_ptr_class
               ,allocator  <my_unique_ptr_class
                           ,managed_shared_memory::segment_manager>
            > MyVector;

typedef basic_string<char
                    ,std::char_traits<char>
                    ,allocator<char
                              ,managed_shared_memory::segment_manager>
            > MyString;

typedef allocator<MyString
                 ,managed_shared_memory::segment_manager
            > MyStrAllocator;


typedef vector <MyString, MyStrAllocator> MyStringVector;

int main()
{
   //Create managed shared memory
   shared_memory_object::remove("mysegment");
   managed_shared_memory segment(create_only, "mysegment", 10000);
   
   //Create to unique_ptr using dynamic allocation
   my_unique_ptr_class my_ptr (segment.construct<MyClass>(anonymous_instance)()
                              ,segment.get_segment_manager());
   my_unique_ptr_class my_ptr2(segment.construct<MyClass>(anonymous_instance)()
                              ,segment.get_segment_manager());

   //Backup relative pointers to future tests
   offset_ptr<MyClass> ptr1 = my_ptr.get();
   offset_ptr<MyClass> ptr2 = my_ptr2.get();

   //Test some copy constructors
   my_unique_ptr_class my_ptr3(0, segment.get_segment_manager());
   my_unique_ptr_class my_ptr4(move(my_ptr3));

   //Construct a list and fill
   MyList list(segment.get_segment_manager());

   //Insert from my_unique_ptr_class
   list.push_front(move(my_ptr));
   list.push_back(move(my_ptr2));

   //Check pointers
   assert(my_ptr.get() == 0);
   assert(my_ptr2.get() == 0);
   assert(list.begin()->get() == ptr1);
   assert(list.rbegin()->get() == ptr2);
/*
   MyList list2(move(list));
   list2.swap(move(MyList(segment.get_segment_manager())));
   list.swap(move(MyList(segment.get_segment_manager())));
*/

   assert(list.begin()->get() == ptr1);
   assert(list.rbegin()->get() == ptr2);

   //Construct a set and fill
   typedef std::less<my_unique_ptr_class> set_less_t;
   MySet set(set_less_t(), segment.get_segment_manager());

   //Insert in set from list passing ownership
   set.insert(move(*list.begin()));
   set.insert(move(*list.rbegin()));

   //Check pointers
   assert(list.begin()->get() == 0);
   assert(list.rbegin()->get()== 0);

   //A set is ordered by std::less<my_unique_ptr_class> so
   //be careful when comparing pointers
   if(ptr1 < ptr2){
      assert(set.begin()->get()  == ptr1);
      assert(set.rbegin()->get() == ptr2);
   }
   else{
      assert(set.rbegin()->get() == ptr1);
      assert(set.begin()->get()  == ptr2);
   }
/*
   MySet set2(move(set));
   set2.swap(move(MySet(set_less_t(), segment.get_segment_manager())));
   set.swap(move(MySet(set_less_t(), segment.get_segment_manager())));
*/

   //Now with vector
   MyVector vector(segment.get_segment_manager());

   //Insert from my_unique_ptr_class
   if(ptr1 < ptr2){
      vector.insert(vector.begin(), move(*set.begin()));
      vector.insert(vector.end(),   move(*set.rbegin()));
   }
   else{
      vector.insert(vector.begin(), move(*set.rbegin()));
      vector.insert(vector.end(),   move(*set.begin()));
   }

   //Check pointers
   assert(my_ptr.get() == 0);
   assert(my_ptr2.get() == 0);
   assert(vector.begin()->get() == ptr1);
   assert(vector.rbegin()->get() == ptr2);

   MyVector vector2(move(vector));
   vector2.swap(vector);

   assert(vector.begin()->get() == ptr1);
   assert(vector.rbegin()->get() == ptr2);
   
   MyStringVector strvect(segment.get_segment_manager());

   char buffer[64];
   for(int i = 0; i < 100; ++i){
      MyString str(segment.get_segment_manager());
      sprintf(buffer, "%d", i);
      str = buffer;
      strvect.push_back(move(str));
   }

   return 0;
}

#include <boost/interprocess/detail/config_end.hpp>

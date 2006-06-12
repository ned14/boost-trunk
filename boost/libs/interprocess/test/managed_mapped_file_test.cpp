//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztañaga 2004-2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/managed_mapped_file.hpp>
#include <cstdio>

using namespace boost::interprocess;

int main ()
{
   const int FileSize          = 65536;
   const char *const FileName = "MyMappedFile";

   //STL compatible allocator object for memory-mapped file
   typedef allocator<int, managed_mapped_file::segment_manager>
      allocator_int_t;
   //A vector that uses that allocator
   typedef boost::interprocess::vector<int, allocator_int_t> MyVect;

   {
      //Remove the file it is already created
      std::remove(FileName);

      const int max              = 100;
      void *array[max];
      //Named allocate capable shared memory allocator
      managed_mapped_file mfile(create_only, FileName, FileSize);

      int i;
      //Let's allocate some memory 
      for(i = 0; i < max; ++i){
         array[i] = mfile.allocate(i+1);
      }

      //Deallocate allocated memory
      for(i = 0; i < max; ++i){
         mfile.deallocate(array[i]);
      }
   }

   {
      //Remove the file it is already created
      std::remove(FileName);

      //Named allocate capable memory mapped file front-end
      managed_mapped_file mfile(create_only, FileName, FileSize);

      //Construct the STL-like allocator with the segment manager
      const allocator_int_t myallocator (mfile.get_segment_manager());

      //Construct vector
      MyVect *mfile_vect = mfile.construct<MyVect> ("MyVector") (myallocator);

      //Test that vector can be found via name
      if(mfile_vect != mfile.find<MyVect>("MyVector").first)
         return -1;

      //Destroy and check it is not present
      mfile.destroy<MyVect> ("MyVector");
      if(0 != mfile.find<MyVect>("MyVector").first)
         return -1;

      //Construct a vector in the memory-mapped file
      mfile_vect = mfile.construct<MyVect> ("MyVector") (myallocator);
      
      //Flush cached data from memory-mapped file to disk
      mfile.flush();
   }
   {

      //Map preexisting file again in memory
      managed_mapped_file mfile(open_only, FileName);

      //Check vector is still there
      MyVect *mfile_vect = mfile.find<MyVect>("MyVector").first;
      if(!mfile_vect)
         return -1;

      //Destroy and check it is not present
      mfile.destroy_ptr(mfile_vect);
      if(0 != mfile.find<MyVect>("MyVector").first)
         return -1;
   }

   return 0;
}
/*
#include <boost/interprocess/managed_mapped_file.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/vector.hpp>

using boost::interprocess::managed_mapped_file;
using boost::interprocess::allocator;
using boost::interprocess::vector;
using boost::interprocess::create_only;

typedef allocator<int, managed_mapped_file::segment_manager> int_alloc;
typedef vector<int, int_alloc> shvi;
typedef allocator<shvi, managed_mapped_file::segment_manager> vec_alloc;
typedef vector<shvi, vec_alloc> shvvi;

int main()
{
   std::remove("./file_mapping");
   managed_mapped_file file_mapping(create_only, "./file_mapping", 1000);

   shvvi * svvi = file_mapping.construct<shvvi>("Vector") (file_mapping.get_segment_manager());
   shvi * svi = file_mapping.construct<shvi>("SubVector") (file_mapping.get_segment_manager());

   svvi->push_back(*svi);

   return 0;
}
*/



   #include <boost/interprocess/shared_memory_object.hpp>
   #include <boost/interprocess/mapped_region.hpp>
   #include <iostream>
   #include "doc_anonymous_semaphore_shared_data.hpp"

   using namespace boost::interprocess;
   
   int main ()
   {
      try{
         //Erase previous shared memory
         shared_memory_object::remove("shared_memory");

         //Create a shared memory object.
         shared_memory_object shm
            (create_only                  //only create
            ,"shared_memory"              //name
            ,read_write  //read-write mode
            );

         //Set size
         shm.truncate(sizeof(shared_memory_buffer));

         //Map the whole shared memory in this process
         mapped_region region
            (shm                       //What to map
            ,read_write //Map it as read-write
            );

         //Get the address of the mapped region
         void * addr       = region.get_address();

         //Construct the shared structure in memory
         shared_memory_buffer * data = new (addr) shared_memory_buffer;

         const int NumMsg = 100;

         //Insert data in the array
         for(int i = 0; i < NumMsg; ++i){
            data->nempty.wait();
            data->mutex.wait();
            data->items[i % shared_memory_buffer::NumItems] = i;
            data->mutex.post();
            data->nstored.post();
         }
      }
      catch(interprocess_exception &ex){
         std::cout << ex.what() << std::endl;
         return 1;
      }

      //Erase shared memory
      shared_memory_object::remove("shared_memory");

      return 0;
   }

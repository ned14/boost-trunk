   #include <boost/interprocess/shared_memory.hpp>
   #include <iostream>
   #include "doc_anonymous_semaphore_shared_data.hpp"

   using namespace boost::interprocess;
   
   int main ()
   {
      try{
         //Create a shared memory object.
         shared_memory_object shm
            (open_only                    //only create
            ,"shared_memory"              //name
            ,memory_mappable::read_write  //read-write mode
            );

         //Map the whole shared memory in this process
         mapped_region region
            (shm                       //What to map
            ,mapped_region::read_write //Map it as read-write
            );

         //Get the address of the mapped region
         void * addr       = region.get_address();

         //Obtain the shared structure
         shared_memory_buffer * data = static_cast<shared_memory_buffer*>(addr);

         const int NumMsg = 100;

         int extracted_data [NumMsg];

         //Extract the data
         for(int i = 0; i < NumMsg; ++i){
            data->nstored.wait();
            data->mutex.wait();
            extracted_data[i] = data->items[i % shared_memory_buffer::NumItems];
            data->mutex.post();
            data->nempty.post();
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

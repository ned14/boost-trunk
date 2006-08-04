   #include <boost/interprocess/shared_memory.hpp>
   #include <boost/interprocess/sync/scoped_lock.hpp>
   #include <iostream>
   #include <cstring>
   #include "doc_anonymous_condition_shared_data.hpp"

   using namespace boost::interprocess;
   
   int main ()
   {
      try{
         //Erase previous shared memory
         shared_memory_object::remove("shared_memory");

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

         //Obtain a pointer to the shared structure
         trace_queue * data = static_cast<trace_queue*>(addr);

         //Print messages until the other process marks the end
         bool end_loop = false;
         do{
            scoped_lock<interprocess_mutex> lock(data->mutex);
            if(!data->message_in){
               data->cond_empty.wait(lock);
            }
            if(std::strcmp(data->items, "last message") == 0){
               end_loop = true;
            }
            else{
               //Print the message
               std::cout << data->items << std::endl;
               //Notify the other process that the buffer is empty
               data->message_in = false;
               data->cond_full.notify_one();
            }
         }
         while(!end_loop);
      }
      catch(interprocess_exception &ex){
         std::cout << ex.what() << std::endl;
         return 1;
      }

      //Erase shared memory
      shared_memory_object::remove("shared_memory");

      return 0;
   }

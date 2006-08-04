   #include <boost/interprocess/shared_memory.hpp>
   #include <boost/interprocess/sync/scoped_lock.hpp>
   #include <iostream>
   #include <cstdio>
   #include "doc_anonymous_condition_shared_data.hpp"

   using namespace boost::interprocess;
   
   int main ()
   {
      try{
         //Erase previous shared memory
         shared_memory_object::remove("shared_memory");

         //Create a shared memory object.
         shared_memory_object shm
            (create_only               //only create
            ,"shared_memory"           //name
            ,memory_mappable::read_write   //read-write mode
            );

         //Set size
         shm.truncate(sizeof(trace_queue));

         //Map the whole shared memory in this process
         mapped_region region
            (shm                       //What to map
            ,mapped_region::read_write //Map it as read-write
            );

         //Get the address of the mapped region
         void * addr       = region.get_address();

         //Construct the shared structure in memory
         trace_queue * data = new (addr) trace_queue;

         const int NumMsg = 100;

         for(int i = 0; i < NumMsg; ++i){
            scoped_lock<interprocess_mutex> lock(data->mutex);
            if(data->message_in){
               data->cond_full.wait(lock);
            }
            if(i == (NumMsg-1))
               std::sprintf(data->items, "%s", "last message");
            else
               std::sprintf(data->items, "%s_%d", "my_trace", i);

            //Notify to the other process that there is a message
            data->cond_empty.notify_one();

            //Mark message buffer as full
            data->message_in = true;
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

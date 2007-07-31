   #include <boost/interprocess/ipc/message_queue.hpp>
   #include <iostream>
   #include <vector>

   using namespace boost::interprocess;
   
   int main ()
   {
      try{
         //Open a message queue.
         message_queue mq
            (open_only        //only create
            ,"message_queue"  //name
            );

         unsigned int priority;
         unsigned int recvd_size;

         //Receive 100 numbers
         for(int i = 0; i < 100; ++i){
            int number;
            mq.receive(&number, sizeof(number), recvd_size, priority);
            if(number != i || recvd_size != sizeof(number))
               return 1;
         }
      }
      catch(interprocess_exception &ex){
         std::cout << ex.what() << std::endl;
         return 1;
      }

      return 0;
   }

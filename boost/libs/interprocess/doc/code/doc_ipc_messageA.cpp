   #include <boost/interprocess/detail/config_begin.hpp>
   #include <boost/interprocess/detail/workaround.hpp>

   #include <boost/interprocess/managed_shared_memory.hpp>
   #include <cstddef>

   int main ()
   {
      using namespace boost::interprocess;

      //A shared memory front-end that is able to 
      //allocate raw memory buffers from a shared memory segment
      //Create the shared memory segment and initialize needed resources
      managed_shared_memory::remove("MySharedMemory");
      managed_shared_memory segment
         (create_only, 
         "MySharedMemory",  //segment name
         65536);             //segment size in bytes

      //Allocate a portion of the segment
      void * shptr   = segment.allocate(1024/*bytes to allocate*/);

      //An handle from the base address can identify any byte of the shared 
      //memory segment even if it is mapped in different base addresses
      managed_shared_memory::handle_t handle = segment.get_handle_from_address(shptr);
      (void)handle;
      // Copy message to buffer
      // . . .
      // Send handle to other process
      // . . .
      // Wait response from other process
      // . . .

      //Deallocate the portion previously allocated
      segment.deallocate(shptr);
      return 0;
   }

   #include <boost/interprocess/detail/config_end.hpp>

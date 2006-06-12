   #include <boost/interprocess/detail/config_begin.hpp>
   #include <boost/interprocess/detail/workaround.hpp>

   #include <boost/interprocess/managed_shared_memory.hpp>

   int main ()
   {
      using namespace boost::interprocess;
      typedef std::pair<double, int> MyType;

      //A shared memory front-end that is able to construct 
      //objects associated with a c-string
      //Create the shared memory segment and initialize resources
      managed_shared_memory::remove("MySharedMemory");
      managed_shared_memory segment(
         create_only,
         "MySharedMemory",   //segment name
         65536);              //segment size in bytes

      //Create an object of MyType initialized to {0.0, 0}
      MyType *instance = segment.construct<MyType>
         ("MyType instance")  /*name of the object*/
         (0.0                 /*ctor first argument*/,
          0                   /*ctor second argument*/);    

      //Create an array of 10 elements of MyType initialized to {0.0, 0}
      MyType *array = segment.construct<MyType>
         ("MyType array")     /*name of the object*/
         [10]                 /*number of elements*/
         (0.0                 /*ctor first argument*/,
          0                   /*ctor second argument*/);    
      return 0;
   }

   #include <boost/interprocess/detail/config_end.hpp>

boost_add_library(
  boost_thread
  barrier.cpp condition.cpp exceptions.cpp mutex.cpp once.cpp recursive_mutex.cpp 
  thread.cpp tss_hooks.cpp tss_dll.cpp tss_pe.cpp tss.cpp xtime.cpp
  SHARED_COMPILE_FLAGS "-DBOOST_THREAD_BUILD_DLL=1"
  STATIC_COMPILE_FLAGS "-DBOOST_THREAD_BUILD_LIB=1"
  NO_SINGLE_THREADED
  )


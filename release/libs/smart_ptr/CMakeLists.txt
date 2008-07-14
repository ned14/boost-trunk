boost_library_project(
  Smart_ptr
  TESTDIRS test
  HEADERS enable_shared_from_this.hpp pointer_cast.hpp 
  scoped_array.hpp scoped_ptr.hpp shared_array.hpp shared_ptr.hpp weak_ptr.hpp
  DESCRIPTION "Five smart pointer class templates."
  AUTHORS "Greg Colvin"
          "Beman Dawes <bdawes -at- acm.org>"
          "Peter Dimov <pdimov -at- mmltd.net>"
          "Darin Adler"
  )
  

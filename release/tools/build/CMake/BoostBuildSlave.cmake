##########################################################################
# Boost Build Slave Support                                              #
##########################################################################
# Copyright (C) 2008 Troy D. Straszheim                                  #
#                                                                        #
# Distributed under the Boost Software License, Version 1.0.             #
# See accompanying file LICENSE_1_0.txt or copy at                       #
#   http://www.boost.org/LICENSE_1_0.txt                                 #
##########################################################################
option(BOOST_BUILD_SLAVE "Be a build slave, report build/testing" OFF)

message(STATUS "Configuring test/compile drivers")
  
if(CMAKE_VERBOSE_MAKEFILE)
  set(BOOST_DRIVER_VERBOSE True)
else(CMAKE_VERBOSE_MAKEFILE)
  set(BOOST_DRIVER_VERBOSE False)
endif(CMAKE_VERBOSE_MAKEFILE)

# the program that does the posting when BOOST_BUILD_SLAVE is on
configure_file(tools/build/CMake/post.py.in ${CMAKE_BINARY_DIR}/post.py @ONLY)

# the programs that sit between 'make' and the test binaries, one does xmlization
# the other doesn't.  T
configure_file(tools/build/CMake/passthru.py.in ${CMAKE_BINARY_DIR}/passthru.py @ONLY)
configure_file(tools/build/CMake/xmlize.py.in ${CMAKE_BINARY_DIR}/xmlize.py @ONLY)

#
# the test driver is either 
#
if(BOOST_BUILD_SLAVE)
  set(BOOST_TEST_DRIVER ${CMAKE_BINARY_DIR}/xmlize.py)
else(BOOST_BUILD_SLAVE)
  set(BOOST_TEST_DRIVER ${CMAKE_BINARY_DIR}/passthru.py)
endif(BOOST_BUILD_SLAVE)

if(BOOST_BUILD_SLAVE)

  #
  #  Redirect various build steps
  # 
  set(CMAKE_CXX_COMPILE_OBJECT 
    "${BOOST_TEST_DRIVER} <CMAKE_CURRENT_BINARY_DIR> cxx_compile_object <OBJECT> ${CMAKE_CXX_COMPILE_OBJECT}")

  set(CMAKE_CXX_CREATE_SHARED_LIBRARY  
    "${BOOST_TEST_DRIVER} <CMAKE_CURRENT_BINARY_DIR> create_shared_library <TARGET> ${CMAKE_CXX_CREATE_SHARED_LIBRARY}") 
    
  set(CMAKE_CXX_CREATE_STATIC_LIBRARY  
    "${BOOST_TEST_DRIVER} <CMAKE_CURRENT_BINARY_DIR> create_static_library <TARGET> ${CMAKE_CXX_CREATE_STATIC_LIBRARY}") 

  set(CMAKE_CXX_LINK_EXECUTABLE  
    "${BOOST_TEST_DRIVER} <CMAKE_CURRENT_BINARY_DIR> link_executable <TARGET> ${CMAKE_CXX_LINK_EXECUTABLE}") 

endif(BOOST_BUILD_SLAVE)

macro(boost_post_results PROJECT_NAME_ LIBRARY_TARGET WHAT LOGDIR)

  if(BOOST_BUILD_SLAVE)
    add_custom_command(TARGET ${LIBRARY_TARGET}
      POST_BUILD
      COMMAND ${CMAKE_BINARY_DIR}/post.py ${PROJECT_NAME_} ${WHAT} ${LOGDIR}
      COMMENT "${PROJECT_NAME_}: posting build results for ${WHAT} from ${LOGDIR}"
      )
    set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${LOGDIR}/Log.xml)

  endif(BOOST_BUILD_SLAVE)
endmacro(boost_post_results LIBRARY_TARGET)

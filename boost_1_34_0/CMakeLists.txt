##########################################################################
# CMake Build Rules for Boost                                            #
##########################################################################
# Copyright (C) 2007 Douglas Gregor <doug.gregor@gmail.com>              #
# Copyright (C) 2007 Troy Straszheim                                     #
#                                                                        #
# Distributed under the Boost Software License, Version 1.0.             #
# See accompanying file LICENSE_1_0.txt or copy at                       #
#   http://www.boost.org/LICENSE_1_0.txt                                 #
##########################################################################
# Basic Usage:                                                           #
#                                                                        #
#   On Unix variants:                                                    #
#     ccmake BOOST_DIRECTORY                                             #
#                                                                        #
#     (c)onfigure options to your liking, then (g)enerate                #
#     makefiles. Use "make" to build, "make test" to test, "make         #
#     install" to install, and "make package" to build binary            #
#     packages.                                                          #
#                                                                        #
#   On Windows:                                                          #
#     run the CMake GNU, load the Boost directory, and generate          #
#     project files or makefiles for your environment.                   #
#                                                                        #
# For more information about CMake, see http://www.cmake.org             #
##########################################################################
cmake_minimum_required(VERSION 2.4.5 FATAL_ERROR)
set(CMAKE_BACKWARDS_COMPATIBILITY 2.4)
project(Boost)

##########################################################################
# Version information                                                    #
##########################################################################
set(BOOST_VERSION_MAJOR 1)
set(BOOST_VERSION_MINOR 34)
set(BOOST_VERSION_SUBMINOR 0)
set(BOOST_VERSION "${BOOST_VERSION_MAJOR}.${BOOST_VERSION_MINOR}.${BOOST_VERSION_SUBMINOR}")
##########################################################################

##########################################################################
# Boost CMake modules                                                    #
##########################################################################
list(APPEND CMAKE_MODULE_PATH ${Boost_SOURCE_DIR}/tools/build/CMake)
include(BoostUtils)
include(BoostConfig)
include(BoostCore)
include(BoostTesting)
##########################################################################

##########################################################################
# Build Features and Variants                                            #
##########################################################################

# User-level options deciding which variants we will build. 
option(BUILD_STATIC "Whether to build static libraries" ON)
option(BUILD_SHARED "Whether to build shared libraries" ON)
option(BUILD_DEBUG "Whether to build debugging libraries" ON)
option(BUILD_RELEASE "Whether to build release libraries" ON)
option(BUILD_SINGLE_THREADED "Whether to build single-threaded libraries" ON)
option(BUILD_MULTI_THREADED "Whether to build multi-threaded libraries" ON)

# For now, we only actually support static/dynamic run-time variants for 
# Visual C++. Provide both options for Visual C++ users, but just fix
# the values of the variables for all other platforms.
if(MSVC)
  option(BUILD_STATIC_RUNTIME "Whether to build libraries linking against the static runtime" ON)
  option(BUILD_DYNAMIC_RUNTIME "Whether to build libraries linking against the dynamic runtime" ON)
else(MSVC)
  set(BUILD_STATIC_RUNTIME OFF)
  set(BUILD_DYNAMIC_RUNTIME ON)
endif(MSVC)

# The default set of library variants that we will be building
boost_add_default_variant(RELEASE DEBUG)
boost_add_default_variant(STATIC SHARED)
if(MSVC)
  boost_add_default_variant(MULTI_THREADED SINGLE_THREADED)
else(MSVC)
  boost_add_default_variant(SINGLE_THREADED MULTI_THREADED)
endif(MSVC)
boost_add_default_variant(DYNAMIC_RUNTIME STATIC_RUNTIME)

# Extra features used by some libraries
set(BUILD_PYTHON_NODEBUG ON)
boost_add_extra_variant(PYTHON_NODEBUG PYTHON_DEBUG)
##########################################################################

##########################################################################
# Installation                                                           #
##########################################################################
if(BOOST_VERSION_SUBMINOR GREATER 0)
  set(BOOST_HEADER_DIR 
      "include/boost-${BOOST_VERSION_MAJOR}_${BOOST_VERSION_MINOR}_${BOOST_VERSION_SUBMINOR}")
else(BOOST_VERSION_SUBMINOR GREATER 0)
  set(BOOST_HEADER_DIR 
      "include/boost-${BOOST_VERSION_MAJOR}_${BOOST_VERSION_MINOR}")  
endif(BOOST_VERSION_SUBMINOR GREATER 0)
install(DIRECTORY boost 
        DESTINATION ${BOOST_HEADER_DIR}
        PATTERN "CVS" EXCLUDE
        REGEX ".svn" EXCLUDE)
##########################################################################

##########################################################################
# Binary packages                                                        #
##########################################################################
set(CPACK_PACKAGE_NAME "Boost")
set(CPACK_PACKAGE_VENDOR "Boost.org")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Boost")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${Boost_SOURCE_DIR}/README.txt")
set(CPACK_RESOURCE_FILE_README "${Boost_SOURCE_DIR}/README.txt")
set(CPACK_RESOURCE_FILE_LICENSE "${Boost_SOURCE_DIR}/LICENSE_1_0.txt")
set(CPACK_RESOURCE_FILE_WELCOME "${Boost_SOURCE_DIR}/Welcome.txt")
set(CPACK_PACKAGE_VERSION "${BOOST_VERSION}")
set(CPACK_PACKAGE_VERSION_MAJOR "${BOOST_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${BOOST_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${BOOST_VERSION_SUBMINOR}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Boost")
if(WIN32 AND NOT UNIX)
  # There is a bug in NSI that does not handle full unix paths properly. Make
  # sure there is at least one set of four (4) backlasshes.
  # NOTE: No Boost icon yet
#  set(CPACK_PACKAGE_ICON "${Boost_SOURCE_DIR}/tools/build/CMake\\\\InstallIcon.bmp")
#  set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\MyExecutable.exe")
  set(CPACK_NSIS_DISPLAY_NAME "Boost ${BOOST_VERSION_MAJOR}.${BOOST_VERSION_MINOR}.${BOOST_VERSION_SUBMINOR}")
  set(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.boost.org")
  set(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.boost.org")
  set(CPACK_NSIS_CONTACT "boost-users@lists.boost.org")
  set(CPACK_NSIS_MODIFY_PATH ON)
  
  # Encode the compiler name in the package 
  if (MSVC60)
    set(CPACK_PACKAGE_FILE_NAME "Boost-${BOOST_VERSION}-vc6")
  elseif (MSVC70)
    set(CPACK_PACKAGE_FILE_NAME "Boost-${BOOST_VERSION}-vc7")
  elseif (MSVC71)
    set(CPACK_PACKAGE_FILE_NAME "Boost-${BOOST_VERSION}-vc71")
  elseif (MSVC80)
    set(CPACK_PACKAGE_FILE_NAME "Boost-${BOOST_VERSION}-vc8")
  elseif (BORLAND)
    set(CPACK_PACKAGE_FILE_NAME "Boost-${BOOST_VERSION}-borland")  
  endif (MSVC60)
endif(WIN32 AND NOT UNIX)
include(CPack)
##########################################################################


##########################################################################
# Building Boost libraries                                               #
##########################################################################
# Always include the Boost source directory, so that we can find
# include files in boost/
include_directories(${Boost_SOURCE_DIR})

# Put the libaries and binaries that get built into directories at the
# top of the build tree rather than in hard-to-find leaf
# directories. This simplifies manual testing and the use of the build
# tree rather than installed Boost libraries.
SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# Boost.Build version 2 does this due to trouble with autolinking
# during building and testing.  
# TODO: See if we can actually use auto-linking in our regression tests.
add_definitions(-DBOOST_ALL_NO_LIB=1)

# Add build rules for all of the Boost libraries
add_subdirectory(libs)

# Add build rules for all of the Boost tools
add_subdirectory(tools)
##########################################################################

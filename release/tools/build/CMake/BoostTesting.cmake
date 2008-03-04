##########################################################################
# Regression Testing Support for Boost                                   #
##########################################################################
# Copyright (C) 2007 Douglas Gregor <doug.gregor@gmail.com>              #
# Copyright (C) 2007 Troy Straszheim                                     #
#                                                                        #
# Distributed under the Boost Software License, Version 1.0.             #
# See accompanying file LICENSE_1_0.txt or copy at                       #
#   http://www.boost.org/LICENSE_1_0.txt                                 #
##########################################################################
# This file provides a set of CMake macros that support regression
# testing for Boost libraries. For each of the test macros below, the
# first argument, testname, states the name of the test that will be
# created. If no other arguments are provided, the source file
# testname.cpp will be used as the source file; otherwise, source
# files should be listed immediately after the name of the test.
#
# The macros for creating regression tests are:
#   boost_test_run: Builds an executable and runs it as a test. The test
#                   succeeds if it builds and returns 0 when executed.
#
#   boost_test_run_fail: Builds an executable and runs it as a test. The
#                        test succeeds if it builds but returns a non-zero
#                        exit code when executed.
#  
#   boost_test_compile: Tests that the given source file compiles without 
#                       any errors.
#
#   boost_test_compile_fail: Tests that the given source file produces 
#                            errors when compiled.

# User-controlled option that can be used to enable/disable regression
# testing. By default, we disable testing, because most users won't
# want or need to perform regression testing on Boost. The Boost build
# is significantly faster when we aren't also building regression
# tests.
option(BUILD_TESTING "Enable testing" OFF)
include(CTest)

# This macro is an internal utility macro that helps parse the
# arguments passed to the Boost testing commands. It will generally
# not be used by Boost developers.
#
#   boost_test_parse_args(testname 
#                         [source1 source2 ...]
#                         [ARGS arg1 arg2... ]
#                         [COMPILE_FLAGS compileflags]
#                         [LINK_FLAGS linkflags]
#                         [LINK_LIBS linklibs]
#                         [DEPENDS libdepend1 libdepend2 ...])
#
# testname is the name of the test. The remaining arguments passed to
# this macro will be parsed and categorized for the developer-level
# test macros to use. 
#
# Variables affected:
#
#   BOOST_TEST_OKAY: Will be set to TRUE if it is okay to build and
#   run this test.
#
#   BOOST_TEST_SOURCES: Will be populated with the set of source files
#   that should be used to compile this test. If the user has provided
#   source files, BOOST_TEST_SOURCES will contain those; otherwise,
#   BOOST_TEST_SOURCES will only contain "testname.cpp".
#
#   BOOST_TEST_arg: Will be populated with the arguments provided for
#   the arguemnt "arg", where "arg" can be any of the extra arguments
#   specified above.
macro(boost_test_parse_args testname)
  set(BOOST_TEST_OKAY TRUE)
  set(BOOST_TEST_COMPILE_FLAGS "")
  parse_arguments(BOOST_TEST 
    "LINK_LIBS;LINK_FLAGS;DEPENDS;COMPILE_FLAGS;ARGS"
    ""
    ${ARGN}
    )
    
  # Check each of the dependencies to see if we can still build this
  # test.
  foreach(ARG ${BOOST_TEST_DEPENDS})
    get_target_property(DEPEND_TYPE ${ARG} TYPE)
    get_target_property(DEPEND_LOCATION ${ARG} LOCATION)
    # If building static libraries is turned off, don't try to build
    # the test
    if (NOT BUILD_STATIC AND ${DEPEND_TYPE} STREQUAL "STATIC_LIBRARY")
      set(BOOST_TEST_OKAY FALSE)
    endif (NOT BUILD_STATIC AND ${DEPEND_TYPE} STREQUAL "STATIC_LIBRARY")

    # If building shared libraries is turned off, don't try to build
    # the test
    if (NOT BUILD_SHARED AND ${DEPEND_TYPE} STREQUAL "SHARED_LIBRARY")
      set(BOOST_TEST_OKAY FALSE)
    endif (NOT BUILD_SHARED AND ${DEPEND_TYPE} STREQUAL "SHARED_LIBRARY")
  endforeach(ARG ${BOOST_TEST_DEPENDS})

  # Setup the SOURCES variables. If no sources are specified, use the
  # name of the test.cpp
  if (BOOST_TEST_DEFAULT_ARGS)
    set(BOOST_TEST_SOURCES ${BOOST_TEST_DEFAULT_ARGS})
  else (BOOST_TEST_DEFAULT_ARGS)
    set(BOOST_TEST_SOURCES "${testname}.cpp")
  endif (BOOST_TEST_DEFAULT_ARGS)

  # If testing is turned off, this test is not okay
  if (NOT BUILD_TESTING)
    set(BOOST_TEST_OKAY FALSE)
  endif(NOT BUILD_TESTING)
endmacro(boost_test_parse_args)

# This macro creates a Boost regression test that will be executed. If
# the test can be built, executed, and exits with a return code of
# zero, it will be considered to have passed.
#
#   boost_test_run(testname 
#                  [source1 source2 ...]
#                  [ARGS arg1 arg2... ]
#                  [COMPILE_FLAGS compileflags]
#                  [LINK_FLAGS linkflags]
#                  [LINK_LIBS linklibs]
#                  [DEPENDS libdepend1 libdepend2 ...])
#
# testname is the name of the test. source1, source2, etc. are the
# source files that will be built and linked into the test
# executable. If no source files are provided, the file "testname.cpp"
# will be used instead.
#
# There are several optional arguments to control how the regression
# test is built and executed:
#
#   ARGS: Provides additional arguments that will be passed to the
#   test executable when it is run.
#
#   COMPILE_FLAGS: Provides additional compilation flags that will be
#   used when building this test. For example, one might want to add
#   "-DBOOST_SIGNALS_ASSERT=1" to turn on assertions within the library.
#
#   LINK_FLAGS: Provides additional flags that will be passed to the
#   linker when linking the test excecutable. This option should not
#   be used to link in additional libraries; see LINK_LIBS and
#   DEPENDS.
#
#   LINK_LIBS: Provides additional libraries against which the test
#   executable will be linked. For example, one might provide "expat"
#   as options to LINK_LIBS, to state that this executable should be
#   linked against the external "expat" library. Use LINK_LIBS for
#   libraries external to Boost; for Boost libraries, use DEPENDS.
#
#   DEPENDS: States that this test executable depends on and links
#   against another Boost library. The argument to DEPENDS should be
#   the name of a particular variant of a Boost library, e.g.,
#   boost_signals-static.
#
# Example:
#   boost_test_run(signal_test DEPENDS boost_signals-static)
#
# TODO: 
#   - Improve handling of DEPENDS, so that we can specify just the
#     library's abstract target (e.g., "boost_signals"), and possibly
#     some features required for building the test (e.g.,
#     MULTI_THREADED, STATIC). The test macros should then pick the
#     best library variant available to meet those features and the
#     current build variant (Debug or Release).
macro(boost_test_run testname)
  if (BUILD_TESTING)
    boost_add_executable(${testname} ${ARGN}
      OUTPUT_NAME tests/${PROJECT_NAME}/${testname}
      NO_INSTALL)
    if (THIS_EXE_OKAY)
      add_test("${PROJECT_NAME}::${testname}" 
        ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}/tests/${PROJECT_NAME}/${testname} 
        ${THIS_EXE_ARGS})
    endif (THIS_EXE_OKAY)
  endif(BUILD_TESTING)
endmacro(boost_test_run)

# This macro creates a Boost regression test that will be executed. If
# the test can be built, executed, and exits with a return code that
# is not zero, it will be considered to have passed.
#
#   boost_test_run_fail(testname 
#                       [source1 source2 ...]
#                       [ARGS arg1 arg2... ]
#                       [COMPILE_FLAGS compileflags]
#                       [LINK_FLAGS linkflags]
#                       [LINK_LIBS linklibs]
#                       [DEPENDS libdepend1 libdepend2 ...])
#
# testname is the name of the test. source1, source2, etc. are the
# source files that will be built and linked into the test
# executable. If no source files are provided, the file "testname.cpp"
# will be used instead.
#
# There are several optional arguments to control how the regression
# test is built and executed:
#
#   ARGS: Provides additional arguments that will be passed to the
#   test executable when it is run.
#
#   COMPILE_FLAGS: Provides additional compilation flags that will be
#   used when building this test. For example, one might want to add
#   "-DBOOST_SIGNALS_ASSERT=1" to turn on assertions within the library.
#
#   LINK_FLAGS: Provides additional flags that will be passed to the
#   linker when linking the test excecutable. This option should not
#   be used to link in additional libraries; see LINK_LIBS and
#   DEPENDS.
#
#   LINK_LIBS: Provides additional libraries against which the test
#   executable will be linked. For example, one might provide "expat"
#   as options to LINK_LIBS, to state that this executable should be
#   linked against the external "expat" library. Use LINK_LIBS for
#   libraries external to Boost; for Boost libraries, use DEPENDS.
#
#   DEPENDS: States that this test executable depends on and links
#   against another Boost library. The argument to DEPENDS should be
#   the name of a particular variant of a Boost library, e.g.,
#   boost_signals-static.
#
# Example:
#   boost_test_run_fail(prg_exec_fail1 DEPENDS boost_prg_exec_monitor-static)
#
# TODO: 
#   - Improve handling of DEPENDS, so that we can specify just the
#     library's abstract target (e.g., "boost_signals"), and possibly
#     some features required for building the test (e.g.,
#     MULTI_THREADED, STATIC). The test macros should then pick the
#     best library variant available to meet those features and the
#     current build variant (Debug or Release).
macro(boost_test_run_fail testname)
  if (BUILD_TESTING)
    boost_add_executable(${testname} ${ARGN}
      OUTPUT_NAME tests/${PROJECT_NAME}/${testname}
      NO_INSTALL)
    if (THIS_EXE_OKAY)
      add_test("${PROJECT_NAME}::${testname}" 
        ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}/tests/${PROJECT_NAME}/${testname} 
        ${THIS_EXE_ARGS})
      set_tests_properties("${PROJECT_NAME}::${testname}" 
        PROPERTIES WILL_FAIL TRUE)
    endif (THIS_EXE_OKAY)
  endif(BUILD_TESTING)
endmacro(boost_test_run_fail)

# Under construction...

macro(boost_test_link testname)
  boost_test_parse_args(${testname} ${ARGN})
  if(BOOST_TEST_OKAY)
    add_test("${PROJECT_NAME}::${testname}"
  	     ${CMAKE_CTEST_COMMAND}
             --build-and-test
             "${Boost_SOURCE_DIR}/tools/build/CMake/LinkTest"
             "${Boost_BINARY_DIR}/tools/build/CMake/LinkTest"
             --build-generator "${CMAKE_GENERATOR}"
             --build-makeprogram "${MAKEPROGRAM}"
	     --build-project LinkTest
	     --build-options -DSOURCE=${CMAKE_CURRENT_SOURCE_DIR}/${BOOST_TEST_SOURCES} -DINCLUDES=${Boost_SOURCE_DIR} -DCOMPILE_FLAGS="${BOOST_TEST_COMPILE_FLAGS}")
  endif(BOOST_TEST_OKAY)
endmacro(boost_test_link)

# This macro creates a Boost regression test that will be compiled,
# but not linked or executed. If the test can be compiled with no
# failures, the test passes.
#
#   boost_test_compile(testname 
#                      [source1]
#                      [COMPILE_FLAGS compileflags])
#
# testname is the name of the test. source1 is the name of the source
# file that will be built. If no source file is provided, the file
# "testname.cpp" will be used instead.
#
# The COMPILE_FLAGS argument provides additional arguments that will
# be passed to the compiler when building this test.

# Example:
#   boost_test_compile(advance)
macro(boost_test_compile testname)
  boost_test_parse_args(${testname} ${ARGN})

  # Determine the include directories to pass along to the underlying
  # project.
  get_directory_property(BOOST_TEST_INCLUDE_DIRS INCLUDE_DIRECTORIES)
  set(BOOST_TEST_INCLUDES "")
  foreach(DIR ${BOOST_TEST_INCLUDE_DIRS})
    set(BOOST_TEST_INCLUDES "${BOOST_TEST_INCLUDES}:${DIR}")
  endforeach(DIR ${BOOST_TEST_INCLUDE_DIRS})

  if(BOOST_TEST_OKAY)
    add_test("${PROJECT_NAME}::${testname}"
  	     ${CMAKE_CTEST_COMMAND}
             --build-and-test
             "${Boost_SOURCE_DIR}/tools/build/CMake/CompileTest"
             "${Boost_BINARY_DIR}/tools/build/CMake/CompileTest"
             --build-generator "${CMAKE_GENERATOR}"
             --build-makeprogram "${MAKEPROGRAM}"
	     --build-project CompileTest
	     --build-options -DSOURCE=${CMAKE_CURRENT_SOURCE_DIR}/${BOOST_TEST_SOURCES} -DINCLUDES=${BOOST_TEST_INCLUDES} -DCOMPILE_FLAGS=${BOOST_TEST_COMPILE_FLAGS})
  endif(BOOST_TEST_OKAY)
endmacro(boost_test_compile)

# This macro creates a Boost regression test that will be compiled,
# but compilation should fail. It is used to test, e.g., that certain
# disallowed syntax does in fact cause a compilation failure.
#
#   boost_test_compile_fail(testname 
#                           [source1]
#                           [COMPILE_FLAGS compileflags])
#
# testname is the name of the test. source1 is the name of the source
# file that will be built. If no source file is provided, the file
# "testname.cpp" will be used instead.
#
# The COMPILE_FLAGS argument provides additional arguments that will
# be passed to the compiler when building this test.

# Example:
#   boost_test_compile_fail(function_test_fail1)
macro(boost_test_compile_fail testname)
  boost_test_parse_args(${testname} ${ARGN})

  # Determine the include directories to pass along to the underlying
  # project.
  get_directory_property(BOOST_TEST_INCLUDE_DIRS INCLUDE_DIRECTORIES)
  set(BOOST_TEST_INCLUDES "")
  foreach(DIR ${BOOST_TEST_INCLUDE_DIRS})
    set(BOOST_TEST_INCLUDES "${BOOST_TEST_INCLUDES}:${DIR}")
  endforeach(DIR ${BOOST_TEST_INCLUDE_DIRS})
    
  if(BOOST_TEST_OKAY)
    add_test("${PROJECT_NAME}::${testname}"
	     ${CMAKE_CTEST_COMMAND}
             --build-and-test
             "${Boost_SOURCE_DIR}/tools/build/CMake/CompileTest"
             "${Boost_BINARY_DIR}/tools/build/CMake/CompileTest"
             --build-generator "${CMAKE_GENERATOR}"
             --build-makeprogram "${MAKEPROGRAM}"
	     --build-project CompileTest
	     --build-options -DSOURCE=${CMAKE_CURRENT_SOURCE_DIR}/${BOOST_TEST_SOURCES} -DINCLUDES=${BOOST_TEST_INCLUDES} -DCOMPILE_FLAGS=${BOOST_TEST_COMPILE_FLAGS})
    set_tests_properties("${PROJECT_NAME}::${testname}" PROPERTIES WILL_FAIL ON)
  endif(BOOST_TEST_OKAY)
endmacro(boost_test_compile_fail)

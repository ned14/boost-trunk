#
#  DartConfig.cmake
#
#

#
# Where to send results to, and how
#
set(DROP_METHOD "xmlrpc")
set(DROP_SITE "http://dart.resophonic.com:8081")
set(DROP_LOCATION "boost_1_34_0")

#
# No test may run longer than 3 minutes.  Haven't seen any problems with this,
# since no boost tests hang or run nearly this long.
#
set(DART_TESTING_TIMEOUT 180)

#
# Build Notes
#
# Put files in a special directory where they will be shipped to the dart server and 
# make available with a click or two on the dashboard next to the build name.
#
set(NOTES_DIR ${CMAKE_BINARY_DIR}/Testing/Notes)
file(MAKE_DIRECTORY ${NOTES_DIR})
if (UNIX)
  exec_program(uname ARGS -a > ${NOTES_DIR}/uname.txt OUTPUT_VARIABLE DEVNULL)
  exec_program(${CMAKE_CXX_COMPILER} --version > ${NOTES_DIR}/compiler-version.txt OUTPUT_VARIABLE DEVNULL)
else(UNIX)
  # anything in the Windows world that ought to go here?
endif(UNIX)

#
# Build Name 
#
# On unix we glom together bits of the uname, compiler version, e.g. 'Linux-2.6.1/i686/gcc-4.1.2/Release'
# Windows version is quite primitive just yet.
#
if (UNIX)
  exec_program(${CMAKE_CXX_COMPILER} ARGS ${CMAKE_CXX_COMPILER_ARG1} -dumpversion OUTPUT_VARIABLE COMPILER_VERSION)
  exec_program(uname ARGS -s OUTPUT_VARIABLE OSTYPE)
  exec_program(uname ARGS -r OUTPUT_VARIABLE OSVERSION)
  exec_program(uname ARGS -p OUTPUT_VARIABLE ARCH)
  if("${ARCH}" STREQUAL "unknown")
    exec_program(uname ARGS -m OUTPUT_VARIABLE ARCH)
  endif("${ARCH}" STREQUAL "unknown")
  set(BUILDNAME ${OSTYPE}-${OSVERSION}/${ARCH}/gcc-${COMPILER_VERSION})
else(UNIX)
  # improve me on Windows....   or is there nothing to improve.
  set(BUILDNAME "${BOOST_TOOLSET}")
endif(UNIX)

#
#  Append either Release or Debug (or both) to BUILDNAME.  This seems important, one can see
#  the effect of optimization flags on test passing rates.
#
if (BUILD_RELEASE)
  set (BUILDNAME "${BUILDNAME}/Release")
endif(BUILD_RELEASE)
if (BUILD_DEBUG)
  set (BUILDNAME "${BUILDNAME}/Debug")
endif(BUILD_DEBUG)

#
#  Happy status message
#
message(STATUS "Testing is ON.  Dart build name = '${BUILDNAME}'")

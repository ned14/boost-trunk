boost_library_project(
  TR1
  TESTDIRS test
  HEADERS tr1
  MODULARIZED
  DESCRIPTION "An implementation of the C++ Technical Report on Standard Library Extensions. This library does not itself implement the TR1 components, rather it's a thin wrapper that will include your standard library's TR1 implementation (if it has one), otherwise it will include the Boost Library equivalents, and import them into namespace std::tr1."
  AUTHORS "John Maddock <john -at- johnmaddock.co.uk>"
  )

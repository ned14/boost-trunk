boost_library_project(
  Integer
  TESTDIRS test
  HEADERS integer.hpp integer_fwd.hpp integer_traits.hpp integer
  DESCRIPTION "The organization of boost integer headers and classes is designed to take advantage of <stdint.h> types from the 1999 C standard without resorting to undefined behavior in terms of the 1998 C++ standard. The header <boost/cstdint.hpp> makes the standard integer types safely available in namespace boost without placing any names in namespace std."
  AUTHORS "Beman Dawes <bdawes -at- acm.org>"
          "Daryle Walker <darylew -at- hotmail.com>"
)

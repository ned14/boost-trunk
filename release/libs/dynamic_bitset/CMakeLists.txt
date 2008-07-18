boost_library_project(
  Dynamic_bitset
  TESTDIRS test
  HEADERS dynamic_bitset.hpp dynamic_bitset_fwd.hpp dynamic_property_map.hpp dynamic_bitset
  MODULARIZED
  DESCRIPTION "A runtime-sized version of std::bitset"
  AUTHORS "Jeremy Siek <jeremy.siek -at- gmail.com>"
          "Chuck Allison"
)

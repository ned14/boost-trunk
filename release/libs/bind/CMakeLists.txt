boost_library_project(
  Bind
  TESTDIRS test
  HEADERS bind.hpp bind
  DESCRIPTION "A generalization of the standard functions std::bind1st and std::bind2nd. It supports arbitrary function objects, functions, function pointers, and member function pointers, and is able to bind any argument to a specific value or route input arguments into arbitrary positions."
  AUTHORS "Peter Dimov <pdimov -at- mmltd.net>"
)



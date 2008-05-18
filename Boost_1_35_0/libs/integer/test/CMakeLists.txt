boost_test_run(cstdint_test ../cstdint_test.cpp)
boost_test_run(integer_test ../integer_test.cpp)
boost_test_run(integer_traits_test ../integer_traits_test.cpp
               DEPENDS boost_test_exec_monitor)

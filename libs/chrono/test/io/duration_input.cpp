//  io_ex2.cpp  ----------------------------------------------------------//

//  Copyright 2010 Howard Hinnant
//  Copyright 2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

/*
 This code was adapted by Vicente J. Botet Escriba from Hinnant's html documentation.
 Many thanks to Howard for making his code available under the Boost license.

 */

#include <boost/chrono/chrono_io.hpp>
#include <sstream>
#include <boost/detail/lightweight_test.hpp>

template<typename D>
void test_good(const char* str, D res)
{
  std::istringstream in(str);
  D d(0);
  in >> d;
  BOOST_TEST(in.good());
  BOOST_TEST(d == res);
}

template<typename DFail, typename DGood>
void test_fail(const char* str, DFail r, DGood res)
{
  {
    std::istringstream in(str);
    DFail d = DFail::zero();
    in >> d;
    BOOST_TEST(in.fail());
    BOOST_TEST(d == DFail::zero());
  }
  {
    std::istringstream in(str);
    DGood d = DGood::zero();
    in >> d;
    BOOST_TEST(in.good());
    BOOST_TEST(d == res);
  }
}

int main()
{
  using namespace boost::chrono;
  using namespace boost;

  test_good("5000 hours", hours(5000));
  test_good("5000 minutes", minutes(5000));
  test_good("5000 seconds", seconds(5000));
  test_good("5000 milliseconds", milliseconds(5000));
  test_good("5000 microseconds", microseconds(5000));
  test_good("5000 nanoseconds", nanoseconds(5000));
  test_good("5000 deciseconds", duration<int_least64_t, deci> (5000));
  test_good("5000 [1/30]seconds", duration<int_least64_t, ratio<1, 30> > (5000));

  test_good("5000 h", hours(5000));
  test_good("5000 m", minutes(5000));
  test_good("5000 s", seconds(5000));
  test_good("5000 ms", milliseconds(5000));
  test_good("5000 ns", nanoseconds(5000));
  test_good("5000 ds", duration<int_least64_t, deci> (5000));
  test_good("5000 [1/30]s", duration<int_least64_t, ratio<1, 30> > (5000));

  test_good("5000 milliseconds", seconds(5));
  test_good("5 milliseconds", nanoseconds(5000000));
  test_good("4000 ms", seconds(4));
  test_fail("3001 ms", seconds(3), milliseconds(3001));

}


/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE-1.0 or http://www.boost.org/LICENSE-1.0)

 */

#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/date_time/microsec_time_clock.hpp"
#include "boost/date_time/testfrmwk.hpp"


int
main() 
{
#ifdef BOOST_DATE_TIME_HAS_HIGH_PRECISION_CLOCK

  using namespace boost::posix_time;

  //  ptime last = boost::date_time::microsec_resolution_clock<ptime>::local_time();
  ptime last = microsec_clock::local_time();

  int max = 30;
  for (int i = 0; i<max; i++)
  {
    for (int j=0; j<100000; j++)
    {
#if defined(BOOST_HAS_FTIME)
      SYSTEMTIME st;
      GetSystemTime(&st);
#endif
    }

    ptime t1 = second_clock::local_time();
    std::cout << to_simple_string(t1) << std::endl;

    ptime t2 = microsec_clock::local_time();
    std::cout << to_simple_string(t2) << std::endl;
    check("hours match", t1.time_of_day().hours() == t2.time_of_day().hours());
    check("minutes match", 
          t1.time_of_day().minutes() == t2.time_of_day().minutes());
    check("seconds match", 
          t1.time_of_day().minutes() == t2.time_of_day().minutes());
    check("hours date", t1.date() == t2.date());
    check("last is less", last < t2);
    last = t2;

    
  }
#else
  check("Get time of day micro second clock not supported due to inadequate compiler/platform", false);
#endif
  return printTestStats();

}


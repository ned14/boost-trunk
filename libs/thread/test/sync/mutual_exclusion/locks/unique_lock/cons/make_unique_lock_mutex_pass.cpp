// Copyright (C) 2012 Vicente J. Botet Escriba
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// <boost/thread/lock_factories.hpp>

// template <class Mutex>
// unique_lock<Mutex> make_unique_lock(Mutex&);

#include <boost/thread/lock_factories.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/detail/lightweight_test.hpp>

#if ! defined(BOOST_NO_CXX11_AUTO) && ! defined BOOST_NO_CXX11_HDR_INITIALIZER_LIST

boost::mutex m;

#if defined BOOST_THREAD_USES_CHRONO

typedef boost::chrono::system_clock Clock;
typedef Clock::time_point time_point;
typedef Clock::duration duration;
typedef boost::chrono::milliseconds ms;
typedef boost::chrono::nanoseconds ns;
#else
#endif

void f()
{
#if defined BOOST_THREAD_USES_CHRONO
  time_point t0 = Clock::now();
  time_point t1;
  {
    auto&& _ = boost::make_unique_lock(m);
    t1 = Clock::now();
  }
  ns d = t1 - t0 - ms(250);
  // This test is spurious as it depends on the time the thread system switches the threads
  BOOST_TEST(d < ns(2500000)+ms(1000)); // within 2.5ms
#else
  //time_point t0 = Clock::now();
  //time_point t1;
  {
    auto _ = boost::make_unique_lock(m);
    //t1 = Clock::now();
  }
  //ns d = t1 - t0 - ms(250);
  // This test is spurious as it depends on the time the thread system switches the threads
  //BOOST_TEST(d < ns(2500000)+ms(1000)); // within 2.5ms
#endif
}

int main()
{
  m.lock();
  boost::thread t(f);
#if defined BOOST_THREAD_USES_CHRONO
  boost::this_thread::sleep_for(ms(250));
#else
#endif
  m.unlock();
  t.join();

  return boost::report_errors();
}
#else
int main()
{
  return boost::report_errors();
}
#endif


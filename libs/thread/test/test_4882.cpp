// Copyright (C) 2010 Vicente Botet
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_THREAD_VERSION 2

#include <boost/thread/thread.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <boost/detail/no_exceptions_support.hpp>

#include <iostream>

boost::shared_mutex mutex;

void thread()
{
  std::cout << __FILE__ << ":" << __LINE__ << std::endl;
  BOOST_TRY
  {
    for (int i =0; i<10; ++i)
    {
#if 0
      boost::system_time timeout = boost::get_system_time() + boost::posix_time::milliseconds(50);

      if (mutex.timed_lock(timeout))
      {
        std::cout << __FILE__ << ":" << __LINE__ << " i="<<i << std::endl;
        boost::this_thread::sleep(boost::posix_time::milliseconds(10));
        mutex.unlock();
        std::cout << __FILE__ << ":" << __LINE__ << " i="<<i << std::endl;
      }
#else
      boost::chrono::system_clock::time_point timeout = boost::chrono::system_clock::now() + boost::chrono::milliseconds(50);

      std::cout << __FILE__ << ":" << __LINE__ << " i="<<i << std::endl;
      if (mutex.try_lock_until(timeout))
      {
        std::cout << __FILE__ << ":" << __LINE__ << " i="<<i << std::endl;
        boost::this_thread::sleep_for(boost::chrono::milliseconds(10));
        mutex.unlock();
        std::cout << __FILE__ << ":" << __LINE__ << " i="<<i << std::endl;
      }
#endif
    }
  }
  BOOST_CATCH (boost::lock_error& le)
  {
    std::cerr << "lock_error exception\n";
  }
  BOOST_CATCH (...)
  {
    std::cerr << " exception\n";
  }
  BOOST_CATCH_END
  std::cout << __FILE__ << ":" << __LINE__ << std::endl;
}

int main()
{
  std::cout << __FILE__ << ":" << __LINE__ << std::endl;
  const int nrThreads = 20;
  boost::thread* threads[nrThreads];

  for (int i = 0; i < nrThreads; ++i)
    threads[i] = new boost::thread(&thread);

  for (int i = 0; i < nrThreads; ++i)
  {
    threads[i]->join();
    std::cout << __FILE__ << ":" << __LINE__ << std::endl;
    delete threads[i];
  }
  std::cout << __FILE__ << ":" << __LINE__ << std::endl;
  return 0;
}

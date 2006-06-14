//
// scoped_lock.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2006 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SCOPED_LOCK_HPP
#define BOOST_ASIO_DETAIL_SCOPED_LOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/push_options.hpp>

#include <boost/asio/detail/noncopyable.hpp>

namespace boost {
namespace asio {
namespace detail {

// Helper class to lock and unlock a mutex automatically.
template <typename Mutex>
class scoped_lock
  : private noncopyable
{
public:
  // Constructor acquires the lock.
  scoped_lock(Mutex& m)
    : mutex_(m)
  {
    mutex_.lock();
    locked_ = true;
  }

  // Destructor releases the lock.
  ~scoped_lock()
  {
    if (locked_)
      mutex_.unlock();
  }

  // Explicitly acquire the lock.
  void lock()
  {
    if (!locked_)
    {
      mutex_.lock();
      locked_ = true;
    }
  }

  // Explicitly release the lock.
  void unlock()
  {
    if (locked_)
    {
      mutex_.unlock();
      locked_ = false;
    }
  }

private:
  // The underlying mutex.
  Mutex& mutex_;

  // Whether the mutex is currently locked or unlocked.
  bool locked_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_SCOPED_LOCK_HPP

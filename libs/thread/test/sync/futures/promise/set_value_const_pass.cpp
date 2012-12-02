//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// Copyright (C) 2011 Vicente J. Botet Escriba
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// <boost/thread/future.hpp>

// class promise<R>

// void promise::set_value(const R& r);

#define BOOST_THREAD_VERSION 3

#include <boost/thread/future.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <boost/static_assert.hpp>

struct A
{
  A()
  {
  }
  A(const A&)
  {
    throw 10;
  }
};

int main()
{

  {
    typedef int T;
    T i = 3;
    boost::promise<T> p;
    boost::future<T> f = p.get_future();
    p.set_value(i);
    ++i;
    BOOST_TEST(f.get() == 3);
    --i;
    try
    {
      p.set_value(i);
      BOOST_TEST(false);
    }
    catch (const boost::future_error& e)
    {
      BOOST_TEST(e.code() == boost::system::make_error_code(boost::future_errc::promise_already_satisfied));
    }
    catch (...)
    {
      BOOST_TEST(false);
    }
  }
  {
    typedef A T;
    T i;
    boost::promise<T> p;
    boost::future<T> f = p.get_future();
    try
    {
      p.set_value(i);
      BOOST_TEST(false);
    }
    catch (int j)
    {
      BOOST_TEST(j == 10);
    }
    catch (...)
    {
      BOOST_TEST(false);
    }
  }

  return boost::report_errors();
}


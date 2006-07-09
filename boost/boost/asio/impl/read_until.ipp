//
// read_until.ipp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2006 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_READ_UNTIL_IPP
#define BOOST_ASIO_READ_UNTIL_IPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/push_options.hpp>

#include <boost/asio/detail/push_options.hpp>
#include <algorithm>
#include <limits>
#include <string>
#include <utility>
#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/buffer.hpp>
#include <boost/asio/error_handler.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/const_buffers_iterator.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_dispatch_helpers.hpp>

namespace boost {
namespace asio {

template <typename Sync_Read_Stream, typename Allocator>
inline std::size_t read_until(Sync_Read_Stream& s,
    boost::asio::basic_streambuf<Allocator>& b, char delim)
{
  return read_until(s, b, delim, throw_error());
}

template <typename Sync_Read_Stream, typename Allocator, typename Error_Handler>
std::size_t read_until(Sync_Read_Stream& s,
    boost::asio::basic_streambuf<Allocator>& b, char delim,
    Error_Handler error_handler)
{
  std::size_t next_search_start = 0;
  for (;;)
  {
    // Determine the range of the data to be searched.
    typedef typename boost::asio::basic_streambuf<
      Allocator>::const_buffers_type const_buffers_type;
    typedef boost::asio::detail::const_buffers_iterator<
      const_buffers_type> iterator;
    const_buffers_type buffers = b.data();
    iterator begin(buffers, next_search_start);
    iterator end(buffers, (std::numeric_limits<std::size_t>::max)());

    // Look for a match.
    iterator iter = std::find(begin, end, delim);
    if (iter != end)
    {
      // Found a match. We're done.
      return iter.position() + 1;
    }
    else
    {
      // No match. Next search can start with the new data.
      next_search_start = end.position();
    }

    // Need more data.
    typename Sync_Read_Stream::error_type error;
    b.commit(s.read_some(b.prepare(512), boost::asio::assign_error(error)));
    if (error)
    {
      error_handler(error);
      return 0;
    }
  }
}

template <typename Sync_Read_Stream, typename Allocator>
inline std::size_t read_until(Sync_Read_Stream& s,
    boost::asio::basic_streambuf<Allocator>& b, const std::string& delim)
{
  return read_until(s, b, delim, throw_error());
}

namespace detail
{
  // Algorithm that finds a subsequence of equal values in a sequence. Returns
  // (iterator,true) if a full match was found, in which case the iterator
  // points to the beginning of the match. Returns (iterator,false) if a
  // partial match was found at the end of the first sequence, in which case
  // the iterator points to the beginning of the partial match. Returns
  // (last1,false) if no full or partial match was found.
  template <typename Iterator1, typename Iterator2>
  std::pair<Iterator1, bool> partial_search(
      Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2)
  {
    for (Iterator1 iter1 = first1; iter1 != last1; ++iter1)
    {
      Iterator1 test_iter1 = iter1;
      Iterator2 test_iter2 = first2;
      for (;; ++test_iter1, ++test_iter2)
      {
        if (test_iter2 == last2)
          return std::make_pair(iter1, true);
        if (test_iter1 == last1)
        {
          if (test_iter2 != first2)
            return std::make_pair(iter1, false);
          else
            break;
        }
        if (*test_iter1 != *test_iter2)
          break;
      }
    }
    return std::make_pair(last1, false);
  }
} // namespace detail

template <typename Sync_Read_Stream, typename Allocator, typename Error_Handler>
std::size_t read_until(Sync_Read_Stream& s,
    boost::asio::basic_streambuf<Allocator>& b, const std::string& delim,
    Error_Handler error_handler)
{
  std::size_t next_search_start = 0;
  for (;;)
  {
    // Determine the range of the data to be searched.
    typedef typename boost::asio::basic_streambuf<
      Allocator>::const_buffers_type const_buffers_type;
    typedef boost::asio::detail::const_buffers_iterator<
      const_buffers_type> iterator;
    const_buffers_type buffers = b.data();
    iterator begin(buffers, next_search_start);
    iterator end(buffers, (std::numeric_limits<std::size_t>::max)());

    // Look for a match.
    std::pair<iterator, bool> result = boost::asio::detail::partial_search(
        begin, end, delim.begin(), delim.end());
    if (result.first != end)
    {
      if (result.second)
      {
        // Full match. We're done.
        return result.first.position() + delim.length();
      }
      else
      {
        // Partial match. Next search needs to start from beginning of match.
        next_search_start = result.first.position();
      }
    }
    else
    {
      // No match. Next search can start with the new data.
      next_search_start = end.position();
    }

    // Need more data.
    typename Sync_Read_Stream::error_type error;
    b.commit(s.read_some(b.prepare(512), boost::asio::assign_error(error)));
    if (error)
    {
      error_handler(error);
      return 0;
    }
  }
}

template <typename Sync_Read_Stream, typename Allocator>
inline std::size_t read_until(Sync_Read_Stream& s,
    boost::asio::basic_streambuf<Allocator>& b, const boost::regex& expr)
{
  return read_until(s, b, expr, throw_error());
}

template <typename Sync_Read_Stream, typename Allocator, typename Error_Handler>
std::size_t read_until(Sync_Read_Stream& s,
    boost::asio::basic_streambuf<Allocator>& b, const boost::regex& expr,
    Error_Handler error_handler)
{
  std::size_t next_search_start = 0;
  for (;;)
  {
    // Determine the range of the data to be searched.
    typedef typename boost::asio::basic_streambuf<
      Allocator>::const_buffers_type const_buffers_type;
    typedef boost::asio::detail::const_buffers_iterator<
      const_buffers_type> iterator;
    const_buffers_type buffers = b.data();
    iterator begin(buffers, next_search_start);
    iterator end(buffers, (std::numeric_limits<std::size_t>::max)());

    // Look for a match.
    boost::match_results<iterator> match_results;
    if (boost::regex_search(begin, end, match_results, expr,
          boost::match_default | boost::match_partial))
    {
      if (match_results[0].matched)
      {
        // Full match. We're done.
        return match_results[0].second.position();
      }
      else
      {
        // Partial match. Next search needs to start from beginning of match.
        next_search_start = match_results[0].first.position();
      }
    }
    else
    {
      // No match. Next search can start with the new data.
      next_search_start = end.position();
    }

    // Need more data.
    typename Sync_Read_Stream::error_type error;
    b.commit(s.read_some(b.prepare(512), boost::asio::assign_error(error)));
    if (error)
    {
      error_handler(error);
      return 0;
    }
  }
}

namespace detail
{
  template <typename Async_Read_Stream, typename Allocator, typename Handler>
  class read_until_delim_handler
  {
  public:
    read_until_delim_handler(Async_Read_Stream& stream,
        boost::asio::basic_streambuf<Allocator>& streambuf, char delim,
        std::size_t next_search_start, Handler handler)
      : stream_(stream),
        streambuf_(streambuf),
        delim_(delim),
        next_search_start_(next_search_start),
        handler_(handler)
    {
    }

    void operator()(const typename Async_Read_Stream::error_type& e,
        std::size_t bytes_transferred)
    {
      // Check for errors.
      if (e)
      {
        std::size_t bytes = 0;
        handler_(e, bytes);
        return;
      }

      // Commit received data to streambuf's get area.
      streambuf_.commit(bytes_transferred);

      // Determine the range of the data to be searched.
      typedef typename boost::asio::basic_streambuf<
        Allocator>::const_buffers_type const_buffers_type;
      typedef boost::asio::detail::const_buffers_iterator<
        const_buffers_type> iterator;
      const_buffers_type buffers = streambuf_.data();
      iterator begin(buffers, next_search_start_);
      iterator end(buffers, (std::numeric_limits<std::size_t>::max)());

      // Look for a match.
      iterator iter = std::find(begin, end, delim_);
      if (iter != end)
      {
        // Found a match. We're done.
        std::size_t bytes = iter.position() + 1;
        handler_(e, bytes);
        return;
      }

      // No match. Start a new asynchronous read operation to obtain more data.
      next_search_start_ = end.position();
      stream_.async_read_some(streambuf_.prepare(512), *this);
    }

  //private:
    Async_Read_Stream& stream_;
    boost::asio::basic_streambuf<Allocator>& streambuf_;
    char delim_;
    std::size_t next_search_start_;
    Handler handler_;
  };

  template <typename Async_Read_Stream, typename Allocator, typename Handler>
  inline void* asio_handler_allocate(std::size_t size,
      read_until_delim_handler<Async_Read_Stream,
        Allocator, Handler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, &this_handler->handler_);
  }

  template <typename Async_Read_Stream, typename Allocator, typename Handler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      read_until_delim_handler<Async_Read_Stream,
        Allocator, Handler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, &this_handler->handler_);
  }

  template <typename Handler_To_Dispatch, typename Async_Read_Stream,
      typename Allocator, typename Handler>
  inline void asio_handler_dispatch(const Handler_To_Dispatch& handler,
      read_until_delim_handler<Async_Read_Stream,
        Allocator, Handler>* this_handler)
  {
    boost_asio_handler_dispatch_helpers::dispatch_handler(
        handler, &this_handler->handler_);
  }
} // namespace detail

template <typename Async_Read_Stream, typename Allocator, typename Handler>
void async_read_until(Async_Read_Stream& s,
    boost::asio::basic_streambuf<Allocator>& b, char delim, Handler handler)
{
  // Determine the range of the data to be searched.
  typedef typename boost::asio::basic_streambuf<
    Allocator>::const_buffers_type const_buffers_type;
  typedef boost::asio::detail::const_buffers_iterator<
    const_buffers_type> iterator;
  const_buffers_type buffers = b.data();
  iterator begin(buffers, 0);
  iterator end(buffers, (std::numeric_limits<std::size_t>::max)());

  // Look for a match.
  iterator iter = std::find(begin, end, delim);
  if (iter != end)
  {
    // Found a match. We're done.
    typename Async_Read_Stream::error_type error;
    std::size_t bytes = iter.position() + 1;
    s.io_service().post(detail::bind_handler(handler, error, bytes));
    return;
  }

  // No match. Start a new asynchronous read operation to obtain more data.
  s.async_read_some(b.prepare(512),
      detail::read_until_delim_handler<Async_Read_Stream, Allocator, Handler>(
        s, b, delim, end.position(), handler));
}

namespace detail
{
  template <typename Async_Read_Stream, typename Allocator, typename Handler>
  class read_until_delim_string_handler
  {
  public:
    read_until_delim_string_handler(Async_Read_Stream& stream,
        boost::asio::basic_streambuf<Allocator>& streambuf,
        const std::string& delim, std::size_t next_search_start,
        Handler handler)
      : stream_(stream),
        streambuf_(streambuf),
        delim_(delim),
        next_search_start_(next_search_start),
        handler_(handler)
    {
    }

    void operator()(const typename Async_Read_Stream::error_type& e,
        std::size_t bytes_transferred)
    {
      // Check for errors.
      if (e)
      {
        std::size_t bytes = 0;
        handler_(e, bytes);
        return;
      }

      // Commit received data to streambuf's get area.
      streambuf_.commit(bytes_transferred);

      // Determine the range of the data to be searched.
      typedef typename boost::asio::basic_streambuf<
        Allocator>::const_buffers_type const_buffers_type;
      typedef boost::asio::detail::const_buffers_iterator<
        const_buffers_type> iterator;
      const_buffers_type buffers = streambuf_.data();
      iterator begin(buffers, next_search_start_);
      iterator end(buffers, (std::numeric_limits<std::size_t>::max)());

      // Look for a match.
      std::pair<iterator, bool> result = boost::asio::detail::partial_search(
          begin, end, delim_.begin(), delim_.end());
      if (result.first != end)
      {
        if (result.second)
        {
          // Full match. We're done.
          std::size_t bytes = result.first.position() + delim_.length();
          handler_(e, bytes);
          return;
        }
        else
        {
          // Partial match. Next search needs to start from beginning of match.
          next_search_start_ = result.first.position();
        }
      }
      else
      {
        // No match. Next search can start with the new data.
        next_search_start_ = end.position();
      }

      // No match. Start a new asynchronous read operation to obtain more data.
      stream_.async_read_some(streambuf_.prepare(512), *this);
    }

  //private:
    Async_Read_Stream& stream_;
    boost::asio::basic_streambuf<Allocator>& streambuf_;
    std::string delim_;
    std::size_t next_search_start_;
    Handler handler_;
  };

  template <typename Async_Read_Stream, typename Allocator, typename Handler>
  inline void* asio_handler_allocate(std::size_t size,
      read_until_delim_string_handler<Async_Read_Stream,
        Allocator, Handler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, &this_handler->handler_);
  }

  template <typename Async_Read_Stream, typename Allocator, typename Handler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      read_until_delim_string_handler<Async_Read_Stream,
        Allocator, Handler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, &this_handler->handler_);
  }

  template <typename Handler_To_Dispatch, typename Async_Read_Stream,
      typename Allocator, typename Handler>
  inline void asio_handler_dispatch(const Handler_To_Dispatch& handler,
      read_until_delim_string_handler<Async_Read_Stream,
        Allocator, Handler>* this_handler)
  {
    boost_asio_handler_dispatch_helpers::dispatch_handler(
        handler, &this_handler->handler_);
  }
} // namespace detail

template <typename Async_Read_Stream, typename Allocator, typename Handler>
void async_read_until(Async_Read_Stream& s,
    boost::asio::basic_streambuf<Allocator>& b, const std::string& delim,
    Handler handler)
{
  // Determine the range of the data to be searched.
  typedef typename boost::asio::basic_streambuf<
    Allocator>::const_buffers_type const_buffers_type;
  typedef boost::asio::detail::const_buffers_iterator<
    const_buffers_type> iterator;
  const_buffers_type buffers = b.data();
  iterator begin(buffers, 0);
  iterator end(buffers, (std::numeric_limits<std::size_t>::max)());

  // Look for a match.
  std::size_t next_search_start;
  std::pair<iterator, bool> result = boost::asio::detail::partial_search(
      begin, end, delim.begin(), delim.end());
  if (result.first != end)
  {
    if (result.second)
    {
      // Full match. We're done.
      typename Async_Read_Stream::error_type error;
      std::size_t bytes = result.first.position() + delim.length();
      s.io_service().post(detail::bind_handler(handler, error, bytes));
      return;
    }
    else
    {
      // Partial match. Next search needs to start from beginning of match.
      next_search_start = result.first.position();
    }
  }
  else
  {
    // No match. Next search can start with the new data.
    next_search_start = end.position();
  }

  // No match. Start a new asynchronous read operation to obtain more data.
  s.async_read_some(b.prepare(512),
      detail::read_until_delim_string_handler<
        Async_Read_Stream, Allocator, Handler>(
          s, b, delim, next_search_start, handler));
}

namespace detail
{
  template <typename Async_Read_Stream, typename Allocator, typename Handler>
  class read_until_expr_handler
  {
  public:
    read_until_expr_handler(Async_Read_Stream& stream,
        boost::asio::basic_streambuf<Allocator>& streambuf,
        const boost::regex& expr, std::size_t next_search_start,
        Handler handler)
      : stream_(stream),
        streambuf_(streambuf),
        expr_(expr),
        next_search_start_(next_search_start),
        handler_(handler)
    {
    }

    void operator()(const typename Async_Read_Stream::error_type& e,
        std::size_t bytes_transferred)
    {
      // Check for errors.
      if (e)
      {
        std::size_t bytes = 0;
        handler_(e, bytes);
        return;
      }

      // Commit received data to streambuf's get area.
      streambuf_.commit(bytes_transferred);

      // Determine the range of the data to be searched.
      typedef typename boost::asio::basic_streambuf<
        Allocator>::const_buffers_type const_buffers_type;
      typedef boost::asio::detail::const_buffers_iterator<
        const_buffers_type> iterator;
      const_buffers_type buffers = streambuf_.data();
      iterator begin(buffers, next_search_start_);
      iterator end(buffers, (std::numeric_limits<std::size_t>::max)());

      // Look for a match.
      boost::match_results<iterator> match_results;
      if (boost::regex_search(begin, end, match_results, expr_,
            boost::match_default | boost::match_partial))
      {
        if (match_results[0].matched)
        {
          // Full match. We're done.
          std::size_t bytes = match_results[0].second.position();
          handler_(e, bytes);
          return;
        }
        else
        {
          // Partial match. Next search needs to start from beginning of match.
          next_search_start_ = match_results[0].first.position();
        }
      }
      else
      {
        // No match. Next search can start with the new data.
        next_search_start_ = end.position();
      }

      // No match. Start a new asynchronous read operation to obtain more data.
      stream_.async_read_some(streambuf_.prepare(512), *this);
    }

  //private:
    Async_Read_Stream& stream_;
    boost::asio::basic_streambuf<Allocator>& streambuf_;
    boost::regex expr_;
    std::size_t next_search_start_;
    Handler handler_;
  };

  template <typename Async_Read_Stream, typename Allocator, typename Handler>
  inline void* asio_handler_allocate(std::size_t size,
      read_until_expr_handler<Async_Read_Stream,
        Allocator, Handler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, &this_handler->handler_);
  }

  template <typename Async_Read_Stream, typename Allocator, typename Handler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      read_until_expr_handler<Async_Read_Stream,
        Allocator, Handler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, &this_handler->handler_);
  }

  template <typename Handler_To_Dispatch, typename Async_Read_Stream,
      typename Allocator, typename Handler>
  inline void asio_handler_dispatch(const Handler_To_Dispatch& handler,
      read_until_expr_handler<Async_Read_Stream,
        Allocator, Handler>* this_handler)
  {
    boost_asio_handler_dispatch_helpers::dispatch_handler(
        handler, &this_handler->handler_);
  }
} // namespace detail

template <typename Async_Read_Stream, typename Allocator, typename Handler>
void async_read_until(Async_Read_Stream& s,
    boost::asio::basic_streambuf<Allocator>& b, const boost::regex& expr,
    Handler handler)
{
  // Determine the range of the data to be searched.
  typedef typename boost::asio::basic_streambuf<
    Allocator>::const_buffers_type const_buffers_type;
  typedef boost::asio::detail::const_buffers_iterator<
    const_buffers_type> iterator;
  const_buffers_type buffers = b.data();
  iterator begin(buffers, 0);
  iterator end(buffers, (std::numeric_limits<std::size_t>::max)());

  // Look for a match.
  std::size_t next_search_start;
  boost::match_results<iterator> match_results;
  if (boost::regex_search(begin, end, match_results, expr,
        boost::match_default | boost::match_partial))
  {
    if (match_results[0].matched)
    {
      // Full match. We're done.
      typename Async_Read_Stream::error_type error;
      std::size_t bytes = match_results[0].second.position();
      s.io_service().post(detail::bind_handler(handler, error, bytes));
      return;
    }
    else
    {
      // Partial match. Next search needs to start from beginning of match.
      next_search_start = match_results[0].first.position();
    }
  }
  else
  {
    // No match. Next search can start with the new data.
    next_search_start = end.position();
  }

  // No match. Start a new asynchronous read operation to obtain more data.
  s.async_read_some(b.prepare(512),
      detail::read_until_expr_handler<Async_Read_Stream, Allocator, Handler>(
        s, b, expr, next_search_start, handler));
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_READ_UNTIL_IPP

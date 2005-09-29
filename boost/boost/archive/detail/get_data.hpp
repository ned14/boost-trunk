// (C) Copyright 2005 Matthias Troyer 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_ARCHIVE_DETAIL_GET_DATA_HPP
#define BOOST_ARCHIVE_DETAIL_GET_DATA_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <vector>

namespace boost {
namespace detail {

  template <class T, class Allocator>
  T* get_data(std::vector<T,Allocator>& v)
  {
    return &(v[0]);
  }

  template <class T, class Allocator>
  const T* get_data(const std::vector<T,Allocator>& v)
  {
    return get_data(const_cast<std::vector<T,Allocator>&>(v));
  }

} //namespace detail 
} //namespace boost 

#endif // BOOST_ARCHIVE_DETAIL_GET_DATA_HPP

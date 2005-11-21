#ifndef BOOST_ARCHIVE_ARRAY_OPTIMIZED_HPP
#define BOOST_ARCHIVE_ARRAY_OPTIMIZED_HPP

// (C) Copyright 2005 Matthias Troyer and Dave Abrahams
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/type_traits/is_convertible.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/apply.hpp>

namespace boost { 

namespace archive { namespace array {

// base class for optimized archives

template <class Derived>
struct optimized
{};

} } // end namespace archive::array

namespace serialization {


// Overload optimize for optimized archives
template <class Archive, class ValueType>
typename mpl::apply1<
    typename Archive::use_array_optimization
  , ValueType
>::type
optimize_array(archive::array::optimized<Archive>*, ValueType*)
{
    typedef typename mpl::apply1<
        BOOST_DEDUCED_TYPENAME Archive::use_array_optimization
      , ValueType
    >::type result;
    
    return result();
}

} // end namespace serialization
} // end namespace boost

#endif // BOOST_ARCHIVE_ARRAY_OPTIMIZED_HPP

#ifndef BOOST_ARCHIVE_ARRAY_OPTIMIZED_HPP
#define BOOST_ARCHIVE_ARRAY_OPTIMIZED_HPP

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// (C) Copyright 2005 Matthias Troyer. 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/serialization/load_array.hpp>
#include <boost/serialization/save_array.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/apply.hpp>
#include <iostream>

namespace boost { 

namespace archive { namespace array {

// CRTP base class for optimized archives

template <class Derived>
struct optimized
{
  Derived& archive()
  {
    return static_cast<Derived&>(*this);
  }
};

} } // end namespace archive::array

namespace serialization {


// Overload optimize for optimized archives
template <class Archive, class ValueType>
typename mpl::apply1<
    typename Archive::use_array_optimization
  , ValueType
>::type
optimize(archive::array::optimized<Archive>*, ValueType*)
{
    typedef typename mpl::apply1<
        BOOST_DEDUCED_TYPENAME Archive::use_array_optimization
      , ValueType
    >::type result;
    
    return result();
}

} // end namespace serialization
} // end namespace boost

// required by smart_cast for compilers not implementing 
// partial template specialization

BOOST_BROKEN_COMPILER_TYPE_TRAITS_SPECIALIZATION(boost::archive::array::binary_iarchive)

#endif // BOOST_ARCHIVE_ARRAY_OPTIMIZED_HPP

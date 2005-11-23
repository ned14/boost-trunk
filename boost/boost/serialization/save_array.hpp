#ifndef BOOST_SERIALIZATION_SAVE_ARRAY_HPP
#define BOOST_SERIALIZATION_SAVE_ARRAY_HPP

// (C) Copyright 2005 Matthias Troyer and Dave Abrahams
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/array.hpp>
#include <iostream>

namespace boost { namespace serialization {

  // Hooks for saving arrays

  // optimized_save_array
  //
  // Used to select either the standard array saving procedure or an
  // optimized one depending on properties of the array's element type.
  // Will usually be called with an MPL predicate as a fifth argument
  // saying whether optimization should be applied, e.g.:
  //
  //    optimized_save_array(ar, p, n, v, is_fundamental<element_type>())
  //
  // Most array-optimized archives won't need to call it directly,
  // since they will be derived from archive::array::optimized, 
  // which provides the call.
  
template <class Archive, class ValueType>
void optimized_save_array(
  Archive& ar, ValueType const * p, std::size_t n, unsigned int version, 
  boost::mpl::false_)
{
  // Optimization not appropriate; use standard procedure
  while (n--)
    ar << serialization::make_nvp("item", *p++);
}


// optimized save implementation: save each element
template <class Archive, class ValueType>
void optimized_save_array(
  Archive& ar, ValueType const * p, std::size_t n, unsigned int version, 
  boost::mpl::true_)
{
  // dispatch to archive-format-specific optimization for types that
  // meet the optimization criteria
  ar.save_array(p,n,version);
}


  // save_array
  //
  // Authors of serialization for types containing arrays will call
  // this function to ensure that optimizations will be applied when
  // possible.

template <class Archive, class ValueType>
inline void save_array(Archive& ar, ValueType const * p, std::size_t n, unsigned int version)
{
  optimized_save_array(ar, p, n, version, optimize_array(&ar, p) );
}


} } // end namespace boost::serialization

#endif //BOOST_SERIALIZATION_SAVE_ARRAY_HPP

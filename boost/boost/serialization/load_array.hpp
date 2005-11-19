#ifndef BOOST_SERIALIZATION_LOAD_ARRAY_HPP
#define BOOST_SERIALIZATION_LOAD_ARRAY_HPP

// (C) Copyright 2005 Matthias Troyer. 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/bool.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization.hpp>
#include <boost/pfto.hpp>

namespace boost { namespace serialization {

// default load implementation: load each element

template <class Archive, class ValueType>
void load_array_optimized(Archive& ar, ValueType * p, std::size_t n, unsigned int version, boost::mpl::false_)
{
  while (n--)
    ar >> serialization::make_nvp("item", *p++);
}

// optimized load implementation: load each element
template <class Archive, class ValueType>
void load_array_optimized(Archive& ar, ValueType * p, std::size_t n, unsigned int version, boost::mpl::true_)
{
  ar.load_array(p,n,version);
}

//  to be overloaded by archive implementors

template <class Archive, class ValueType>
inline void load_array_override(Archive& ar, ValueType * p, std::size_t n, unsigned BOOST_PFTO int version)
{
  serialization::load_array_optimized(ar, p, n, version, boost::mpl::false_() );
}

// Interface for serialization users

template <class Archive, class ValueType>
inline void load_array(Archive& ar, ValueType * p, std::size_t n, unsigned int version)
{
  load_array_override(ar, p, boost::serialization::version_type(version) );
}


} } // end namespace boost::serialization

#endif //BOOST_SERIALIZATION_LOAD_ARRAY_HPP

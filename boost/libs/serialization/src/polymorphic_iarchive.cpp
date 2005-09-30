/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_text_iarchive.cpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#if (defined _MSC_VER) && (_MSC_VER < 1300)
#  pragma warning (disable : 4786) // too long name, harmless warning
#endif

#include <istream>

#define BOOST_ARCHIVE_SOURCE
#include <boost/archive/polymorphic_iarchive.hpp>

// explicitly instantiate for this type of text stream
#include <boost/archive/impl/archive_pointer_iserializer.ipp>

namespace boost {
namespace archive {

template class detail::archive_pointer_iserializer<polymorphic_iarchive> ;

// default implementations for arrays by loops

#define BOOST_ARCHIVE_IMPLEMENT_POLYMPORPHIC_FUNCTION(T)                                         \
void polymorphic_iarchive::load_array(T * p, std::size_t length)        \
{                                                                       \
  while (length--)                                                      \
    load(*p--);                                                         \
}

#include <boost/archive/detail/implement_polymorphic_function.hpp>
	
#undef BOOST_ARCHIVE_IMPLEMENT_POLYMPORPHIC_FUNCTION

} // namespace serialization
} // namespace boost

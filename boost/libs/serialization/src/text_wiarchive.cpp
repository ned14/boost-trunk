/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// text_wiarchive.cpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>

#include <boost/static_assert.hpp>
#ifdef BOOST_NO_STD_WSTREAMBUF
BOOST_STATIC_ASSERT(false);
#else

#include <istream>
#include <boost/archive/text_wiarchive.hpp>

// explicitly instantiate for this type of text stream
#include <boost/archive/impl/basic_text_iprimitive.ipp>
#include <boost/archive/impl/basic_text_iarchive.ipp>
#include <boost/archive/impl/text_wiarchive_impl.ipp>
#include <boost/archive/impl/archive_pointer_iserializer.ipp>

namespace boost {
namespace archive {

template class basic_text_iprimitive<std::wistream> ;
template class basic_text_iarchive<text_wiarchive> ;
template class text_wiarchive_impl<text_wiarchive> ;
template class detail::archive_pointer_iserializer<text_wiarchive> ;

} // namespace archive
} // namespace boost

#endif // BOOST_NO_STD_WSTREAMBUF



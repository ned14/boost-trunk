/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// text_woarchive_impl.ipp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . Permission to copy, 
// use, modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided "as is"
// without express or implied warranty, and with no claim as to its suitability
// for any purpose.

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifndef BOOST_NO_STD_WSTREAMBUF

#include <cstring>
#if defined(BOOST_NO_STDC_NAMESPACE) && ! defined(__LIBCOMO__)
namespace std{ 
    using ::strlen; 
} // namespace std
#endif

#include <ostream>

#include <boost/utf8_codecvt_facet.hpp>
#include <boost/archive/text_woarchive.hpp>
#include <boost/archive/codecvt_null.hpp>
#include <boost/archive/add_facet.hpp>

namespace boost {
namespace archive {

//////////////////////////////////////////////////////////////////////
// implementation of woarchive functions
//
template<class Archive>
void text_woarchive_impl<Archive>::save(const char *s)
{
    // note: superfluous local variable fixes borland warning
    size_t size = strlen(s);
    * this->This() << size;
    this->This()->newtoken();
    while(*s != '\0')
        os.put(os.widen(*s++));
}

template<class Archive>
void text_woarchive_impl<Archive>::save(const std::string &s)
{
    size_t size = s.size();
    * this->This() << size;
    this->This()->newtoken();
    const char * cptr = s.data();
    while(size-- > 0)
        os.put(os.widen(*cptr++));
}

#ifndef BOOST_NO_INTRINSIC_WCHAR_T
template<class Archive>
void text_woarchive_impl<Archive>::save(const wchar_t *ws)
{
    size_t size = std::wostream::traits_type::length(ws);
    * this->This() << size;
    this->This()->newtoken();
    os.write(ws, size);
}
#endif

#ifndef BOOST_NO_STD_WSTRING
template<class Archive>
void text_woarchive_impl<Archive>::save(const std::wstring &ws)
{
    size_t size = ws.length();
    * this->This() << size;
    this->This()->newtoken();
    os.write(ws.data(), size);
}
#endif

} // namespace archive
} // namespace boost

#endif


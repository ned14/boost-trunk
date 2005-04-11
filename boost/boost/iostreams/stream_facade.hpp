// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_STREAM_FACADE_HPP_INCLUDED
#define BOOST_IOSTREAMS_STREAM_FACADE_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/iostreams/constants.hpp>
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/config/overload_resolution.hpp>
#include <boost/iostreams/detail/forward.hpp>
#include <boost/iostreams/detail/iostream.hpp>  // standard streams.
#include <boost/iostreams/detail/select.hpp>
#include <boost/iostreams/streambuf_facade.hpp>
#include <boost/mpl/and.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace iostreams { namespace detail {

template<typename Device, typename Tr>
struct stream_facade_traits {
    typedef typename io_char<Device>::type                     char_type;
    typedef Tr                                                 traits_type;
    typedef typename io_category<Device>::type                 mode;
    typedef typename
            select<
                mpl::and_<
                    is_convertible<mode, input>,
                    is_convertible<mode, output>
                >,
                BOOST_IOSTREAMS_BASIC_IOSTREAM(char_type, traits_type),
                is_convertible<mode, input>,
                BOOST_IOSTREAMS_BASIC_ISTREAM(char_type, traits_type),
                else_,
                BOOST_IOSTREAMS_BASIC_OSTREAM(char_type, traits_type)
            >::type type;
};

// By encapsulating initialization in a base, we can define the macro
// BOOST_IOSTREAMS_DEFINE_FORWARDING_FUNCTIONS to generate constuctors
// without base member initializer lists.
template< typename Device,
          typename Tr =
              BOOST_IOSTREAMS_CHAR_TRAITS(
                  BOOST_DEDUCED_TYPENAME io_char<Device>::type
              ),
          typename Alloc =
              std::allocator<
                  BOOST_DEDUCED_TYPENAME io_char<Device>::type
              >,
          typename Base = // VC6 Workaround.
              BOOST_DEDUCED_TYPENAME
              detail::stream_facade_traits<Device, Tr>::type >
class stream_facade_base
    : protected base_from_member< streambuf_facade<Device, Tr, Alloc> >,
      public Base
{
private:
    typedef base_from_member< streambuf_facade<Device, Tr, Alloc> > pbase_type;
    typedef typename stream_facade_traits<Device, Tr>::type         stream_type;
protected:
    using pbase_type::member; // Avoid warning about 'this' in initializer list.
public:
    stream_facade_base() : pbase_type(), stream_type(&member) { }
};

} } } // End namespaces detail, iostreams, boost.

#ifdef BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION
# include <boost/iostreams/detail/broken_overload_resolution/stream_facade.hpp>
#else

namespace boost { namespace iostreams {

//
// Template name: stream_facade.
// Description: A iostream which reads from and writes to an instance of a
//      designated device type.
// Template paramters:
//      Device - A device type.
//      Alloc - The allocator type.
//
template< typename Device,
          typename Tr =
              BOOST_IOSTREAMS_CHAR_TRAITS(
                  BOOST_DEDUCED_TYPENAME io_char<Device>::type
              ),
          typename Alloc =
              std::allocator<
                  BOOST_DEDUCED_TYPENAME io_char<Device>::type
              > >
struct stream_facade : detail::stream_facade_base<Device, Tr, Alloc> {
public:
    typedef typename io_char<Device>::type  char_type;
    BOOST_IOSTREAMS_STREAMBUF_TYPEDEFS(Tr)
private:
    typedef typename
            detail::stream_facade_traits<
                Device, Tr
            >::type                         stream_type;
    typedef Device                          policy_type;
public:
    stream_facade() { }
    BOOST_IOSTREAMS_FORWARD( stream_facade, open_impl, Device,
                             BOOST_IOSTREAMS_PUSH_PARAMS,
                             BOOST_IOSTREAMS_PUSH_ARGS )
    bool is_open() const { return this->member.is_open(); }
    void close() { this->member.close(); }
    Device& operator*() { return *this->member; }
    Device* operator->() { return &*this->member; }
private:
    void open_impl(const Device& dev BOOST_IOSTREAMS_PUSH_PARAMS()) // For forwarding.
    { 
        this->clear(); 
        this->member.open(dev BOOST_IOSTREAMS_PUSH_ARGS()); 
    }
};

} } // End namespaces iostreams, boost.

#endif // #ifdef BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION

#endif // #ifndef BOOST_IOSTREAMS_STREAM_FACADE_HPP_INCLUDED

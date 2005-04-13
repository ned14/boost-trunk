// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_OPERATIONS_HPP_INCLUDED
#define BOOST_IOSTREAMS_OPERATIONS_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <utility>           // pair.
#include <boost/config.hpp>  // NO_STD_LOCALE, DEDUCED_TYPENAME, MSVC.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/constants.hpp>  // constants.
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/dispatch.hpp>
#include <boost/iostreams/detail/streambuf.hpp>
#include <boost/iostreams/detail/wrap_unwrap.hpp>
#include <boost/iostreams/positioning.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/integer_traits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/not.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <boost/iostreams/detail/config/disable_warnings.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, < 1300) //-----------------------------------//
# include <boost/iostreams/detail/vc6/operations.hpp>
#else // #if BOOST_WORKAROUND(BOOST_MSVC, < 1300) //--------------------------//

namespace boost { namespace iostreams {

//--------------Fundamental i/o operations------------------------------------//

template<typename T> struct operations;

namespace detail {

struct custom_tag { };

template<typename T>
struct is_custom
    : mpl::not_<
          is_base_and_derived< custom_tag, operations<T> >
      >
    { };

// Implementation templates for simulated tag dispatch.
template<typename T> struct read_impl;
template<typename T> struct write_impl;
template<typename T> struct filter_impl;
template<typename T> struct direct_impl;
template<typename T> struct seek_impl;
template<typename T> struct close_impl;
template<typename T> struct flush_device_impl;
template<typename T> struct flush_filter_impl;
template<typename T> struct imbue_impl;
template<typename T> struct optimal_buffer_size_impl;

} // End namespace detail.

template<typename T>
struct operations : detail::custom_tag { };

template<typename T>
typename io_int<T>::type get(T& t)
{ return detail::read_impl<T>::get(detail::unwrap(t)); }

template<typename T>
inline std::streamsize
read(T& t, typename io_char<T>::type* s, std::streamsize n)
{ return detail::read_impl<T>::read(detail::unwrap(t), s, n); }

template<typename T, typename Source>
std::streamsize
read(T& t, Source& src, typename io_char<T>::type* s, std::streamsize n)
{ return detail::filter_impl<T>::read(detail::unwrap(t), src, s, n); }

template<typename T>
void putback(T& t, typename io_char<T>::type c)
{ detail::read_impl<T>::putback(detail::unwrap(t), c); }

template<typename T>
void put(T& t, typename io_char<T>::type c)
{ detail::write_impl<T>::put(detail::unwrap(t), c); }

template<typename T>
inline void write(T& t, const typename io_char<T>::type* s, std::streamsize n)
{ detail::write_impl<T>::write(detail::unwrap(t), s, n); }

template<typename T, typename Sink>
void write( T& t, Sink& snk, const typename io_char<T>::type* s, 
            std::streamsize n )
{ detail::filter_impl<T>::write(detail::unwrap(t), snk, s, n); }

template<typename T>
inline std::streampos
seek( T& t, stream_offset off, BOOST_IOS::seekdir way,
      BOOST_IOS::openmode which = BOOST_IOS::in | BOOST_IOS::out )
{ return detail::seek_impl<T>::seek(detail::unwrap(t), off, way, which); }

template<typename T>
inline std::pair<
    BOOST_DEDUCED_TYPENAME io_char<T>::type*,
    BOOST_DEDUCED_TYPENAME io_char<T>::type*
>
input_sequence(T& t) { return detail::direct_impl<T>::input_sequence(t); }

template<typename T>
inline std::pair<
    BOOST_DEDUCED_TYPENAME io_char<T>::type*,
    BOOST_DEDUCED_TYPENAME io_char<T>::type*
>
output_sequence(T& t) { return detail::direct_impl<T>::output_sequence(t); }

template<typename T>
void close(T& t, BOOST_IOS::openmode which)
{ detail::close_impl<T>::close(detail::unwrap(t), which); }

template<typename T, typename Sink>
void close(T& t, Sink& snk, BOOST_IOS::openmode which)
{ detail::close_impl<T>::close(detail::unwrap(t), snk, which); }

template<typename T>
bool flush(T& t)
{ return detail::flush_device_impl<T>::flush(detail::unwrap(t)); }

template<typename T, typename Sink>
bool flush(T& t, Sink& snk)
{ return detail::flush_filter_impl<T>::flush(detail::unwrap(t), snk); }

template<typename T, typename Locale>
void imbue(T& t, const Locale& loc)
{ detail::imbue_impl<T>::imbue(detail::unwrap(t), loc); }

template<typename T>
std::streamsize optimal_buffer_size(const T& t)
{
    typedef detail::optimal_buffer_size_impl<T> impl;
    return impl::optimal_buffer_size(detail::unwrap(t));
}

//----------------------------------------------------------------------------//

namespace detail {

//------------------Definition of read_impl-----------------------------------//

template<typename T>
struct read_impl
    : mpl::if_<
          detail::is_custom<T>,
          operations<T>,
          read_impl<
              BOOST_DEDUCED_TYPENAME
              detail::dispatch<
                  T, istream_tag, streambuf_tag, input
              >::type
          >
      >::type
    { };

template<>
struct read_impl<istream_tag> {
    template<typename T>
    static typename io_int<T>::type get(T& t)
    { return t.get(); }

    template<typename T>
    static std::streamsize
    read(T& t, typename io_char<T>::type* s, std::streamsize n)
    { t.read(s, n); return t.gcount(); }

    template<typename T>
    static void putback(T& t, typename io_char<T>::type c)
    { t.putback(c); }
};

template<>
struct read_impl<streambuf_tag> {
    template<typename T>
    static typename io_int<T>::type get(T& t)
    { return t.sbumpc(); }

    template<typename T>
    static std::streamsize
    read(T& t, typename io_char<T>::type* s, std::streamsize n)
    { return t.sgetn(s, n); }

    template<typename T>
    static void putback(T& t, typename io_char<T>::type c)
    { t.sputbackc(c); }
};

template<>
struct read_impl<input> {
    template<typename T>
    static typename io_int<T>::type get(T& t)
    {
        typedef typename io_char<T>::type               char_type;
        typedef BOOST_IOSTREAMS_CHAR_TRAITS(char_type)  traits_type;
        char_type c;
        return t.read(&c, 1) == 1 ?
            traits_type::to_int_type(c) :
            traits_type::eof();
    }

    template<typename T>
    static std::streamsize
    read(T& t, typename io_char<T>::type* s, std::streamsize n)
    { return t.read(s, n); }

    template<typename T>
    static void putback(T& t, typename io_char<T>::type c)
    {
        typedef typename io_category<T>::type category;
        BOOST_STATIC_ASSERT((is_convertible<category, peekable_tag>::value));
        t.putback(c);
    }
};

//------------------Definition of write_impl----------------------------------//

template<typename T>
struct write_impl
    : mpl::if_<
          detail::is_custom<T>,
          operations<T>,
          write_impl<
              BOOST_DEDUCED_TYPENAME
              detail::dispatch<
                  T, ostream_tag, streambuf_tag, output
              >::type
          >
      >::type
    { };

template<>
struct write_impl<ostream_tag> {
    template<typename T>
    static void put(T& t, typename io_char<T>::type c)
    { t.put(c); }

    template<typename T>
    static void write
        (T& t, const typename io_char<T>::type* s, std::streamsize n)
    { t.write(s, n); }
};

template<>
struct write_impl<streambuf_tag> {
    template<typename T>
    static void put(T& t, typename io_char<T>::type c)
    { t.sputc(c); }

    template<typename T>
    static void write
        (T& t, const typename io_char<T>::type* s, std::streamsize n)
    { t.sputn(s, n); }
};

template<>
struct write_impl<output> {
    template<typename T>
    static void put(T& t, typename io_char<T>::type c)
    { t.write(&c, 1); }

    template<typename T>
    static void
    write(T& t, const typename io_char<T>::type* s, std::streamsize n)
    { t.write(s, n); }
};

//------------------Definition of filter_impl---------------------------------//

template<typename T>
struct filter_impl
    : mpl::if_<
          detail::is_custom<T>,
          operations<T>,
          filter_impl<
              BOOST_DEDUCED_TYPENAME
              detail::dispatch<
                  T, multichar_tag, any_tag
              >::type
          >
      >::type
    { };

template<>
struct filter_impl<multichar_tag> {
    template<typename T, typename Source>
    static std::streamsize read
        (T& t, Source& src, typename io_char<T>::type* s, std::streamsize n)
    { return t.read(src, s, n); }

    template<typename T, typename Sink>
    static void write( T& t, Sink& snk, const typename io_char<T>::type* s,
                       std::streamsize n )
    { t.write(snk, s, n); }
};

template<>
struct filter_impl<any_tag> {
    template<typename T, typename Source>
    static std::streamsize read
        (T& t, Source& src, typename io_char<T>::type* s, std::streamsize n)
    {
        typedef typename io_char<T>::type               char_type;
        typedef BOOST_IOSTREAMS_CHAR_TRAITS(char_type)  traits_type;
        std::streamsize result;
        for (result = 0; result < n; ++result) {
            typename io_int<T>::type c = t.get(src);
            if (traits_type::eq_int_type(c, traits_type::eof()))
                break;
            s[result] = traits_type::to_char_type(c);
        }
        return result;
    }
    template<typename T, typename Sink>
    static void write( T& t, Sink& snk, const typename io_char<T>::type* s,
                       std::streamsize n )
    { for (std::streamsize off = 0; off < n; ++off) t.put(snk, s[off]); }
};

//------------------Definition of direct_impl-------------------------------//

template<typename T>
struct direct_impl
    : mpl::if_<
          detail::is_custom<T>,
          operations<T>,
          direct_impl<direct_tag>
      >::type
    { };

template<>
struct direct_impl<direct_tag> {
    template<typename U>
    static std::pair<
        BOOST_DEDUCED_TYPENAME io_char<U>::type*,
        BOOST_DEDUCED_TYPENAME io_char<U>::type*
    >
    input_sequence(U& u) { return u.input_sequence(); }

    template<typename U>
    static std::pair<
        BOOST_DEDUCED_TYPENAME io_char<U>::type*,
        BOOST_DEDUCED_TYPENAME io_char<U>::type*
    >
    output_sequence(U& u) { return u.output_sequence(); }
};

//------------------Definition of seek_impl-----------------------------------//

template<typename T>
struct seek_impl
    : mpl::if_<
          detail::is_custom<T>,
          operations<T>,
          seek_impl<
              BOOST_DEDUCED_TYPENAME
              detail::dispatch<
                  T, iostream_tag, istream_tag, ostream_tag,
                  streambuf_tag, detail::two_head, any_tag
              >::type
          >
      >::type
    { };

struct seek_impl_basic_ios {
    template<typename T>
    static std::streampos seek( T& t, stream_offset off,
                                BOOST_IOS::seekdir way,
                                BOOST_IOS::openmode which )
    { 
        if ( way == BOOST_IOS::beg && 
             ( off < integer_traits<std::streamoff>::const_min ||
               off > integer_traits<std::streamoff>::const_max ) )
        {
            return t.rdbuf()->pubseekpos(offset_to_position(off));
        } else {
            return t.rdbuf()->pubseekoff(off, way, which); 
        }
    }
};

template<>
struct seek_impl<iostream_tag> : seek_impl_basic_ios { };

template<>
struct seek_impl<istream_tag> : seek_impl_basic_ios { };

template<>
struct seek_impl<ostream_tag> : seek_impl_basic_ios { };

template<>
struct seek_impl<streambuf_tag> {
    template<typename T>
    static std::streampos seek( T& t, stream_offset off,
                                BOOST_IOS::seekdir way,
                                BOOST_IOS::openmode which )
    { 
        if ( way == BOOST_IOS::beg && 
             ( off < integer_traits<std::streamoff>::const_min ||
               off > integer_traits<std::streamoff>::const_max ) )
        {
            return t.pubseekpos(offset_to_position(off));
        } else {
            return t.pubseekoff(off, way, which); 
        }
    }
};

template<>
struct seek_impl<two_head> {
    template<typename T>
    static std::streampos seek( T& t, stream_offset off,
                                BOOST_IOS::seekdir way,
                                BOOST_IOS::openmode which )
    { return t.seek(off, way, which); }
};

template<>
struct seek_impl<any_tag> {
    template<typename T>
    static std::streampos seek( T& t, stream_offset off,
                                BOOST_IOS::seekdir way,
                                BOOST_IOS::openmode )
    { return t.seek(off, way); }
};

//------------------Definition of close_impl----------------------------------//

template<typename T>
struct close_tag {
    typedef typename io_category<T>::type category;
    typedef typename
            mpl::eval_if<
                is_convertible<category, closable_tag>,
                mpl::if_<
                    mpl::or_<
                        is_convertible<category, detail::two_sequence>,
                        is_convertible<category, dual_use>
                    >,
                    detail::two_sequence,
                    closable_tag
                >,
                mpl::identity<any_tag>
            >::type type;
};

template<typename T>
struct close_impl
    : mpl::if_<
          detail::is_custom<T>,
          operations<T>,
          close_impl<BOOST_DEDUCED_TYPENAME close_tag<T>::type>
      >::type
    { };

template<>
struct close_impl<any_tag> {
    template<typename T>
    static void close(T& t, BOOST_IOS::openmode which)
    {
        if ((which & BOOST_IOS::out) != 0)
            iostreams::flush(t);
    }
    template<typename T, typename Sink>
    static void close(T& t, Sink& snk, BOOST_IOS::openmode which)
    {
        if ((which & BOOST_IOS::out) != 0)
            iostreams::flush(t, snk);
    }
};

#include <boost/iostreams/detail/config/disable_warnings.hpp> // Borland.
template<>
struct close_impl<closable_tag> {
    template<typename T>
    static void close(T& t, BOOST_IOS::openmode which)
    {
        typedef typename io_category<T>::type category;
        const bool in =  is_convertible<category, input>::value &&
                        !is_convertible<category, output>::value;
        if (in == ((which & BOOST_IOS::in) != 0))
            t.close();
    }
    template<typename T, typename Sink>
    static void close(T& t, Sink& snk, BOOST_IOS::openmode which)
    {
        typedef typename io_category<T>::type category;
        const bool in =  is_convertible<category, input>::value &&
                        !is_convertible<category, output>::value;
        if (in == ((which & BOOST_IOS::in) != 0))
            t.close(snk);
    }
};
#include <boost/iostreams/detail/config/enable_warnings.hpp>

template<>
struct close_impl<two_sequence> {
    template<typename T>
    static void close(T& t, BOOST_IOS::openmode which) { t.close(which); }
    template<typename T, typename Sink>
    static void close(T& t, Sink& snk, BOOST_IOS::openmode which)
    { t.close(snk, which); }
};

//------------------Definition of flush_device_impl---------------------------//

template<typename T>
struct flush_device_impl
    : mpl::if_<
          detail::is_custom<T>,
          operations<T>,
          flush_device_impl<
              BOOST_DEDUCED_TYPENAME
              detail::dispatch<
                  T, ostream_tag, streambuf_tag, flushable_tag, any_tag
              >::type
          >
      >::type
    { };

template<>
struct flush_device_impl<ostream_tag> {
    template<typename T>
    static bool flush(T& t)
    { return t.rdbuf()->BOOST_IOSTREAMS_PUBSYNC() == 0; }
};

template<>
struct flush_device_impl<streambuf_tag> {
    template<typename T>
    static bool flush(T& t)
    { return t.BOOST_IOSTREAMS_PUBSYNC() == 0; }
};

template<>
struct flush_device_impl<flushable_tag> {
    template<typename T>
    static bool flush(T& t) { return t.flush(); }
};

template<>
struct flush_device_impl<any_tag> {
    template<typename T>
    static bool flush(T&) { return true; }
};

//------------------Definition of flush_filter_impl---------------------------//

template<typename T>
struct flush_filter_impl
    : mpl::if_<
          detail::is_custom<T>,
          operations<T>,
          flush_filter_impl<
              BOOST_DEDUCED_TYPENAME
              detail::dispatch<
                  T, flushable_tag, any_tag
              >::type
          >
      >::type
    { };

template<>
struct flush_filter_impl<flushable_tag> {
    template<typename T, typename Sink>
    static bool flush(T& t, Sink& snk) { return t.flush(snk); }
};

template<>
struct flush_filter_impl<any_tag> {
    template<typename T, typename Sink>
    static bool flush(T&, Sink&) { return false; }
};

//------------------Definition of imbue_impl----------------------------------//

template<typename T>
struct imbue_impl
    : mpl::if_<
          detail::is_custom<T>,
          operations<T>,
          imbue_impl<
              BOOST_DEDUCED_TYPENAME
              detail::dispatch<
                  T, streambuf_tag, localizable_tag, any_tag
              >::type
          >
      >::type
    { };

template<>
struct imbue_impl<any_tag> {
    template<typename T, typename Locale>
    static void imbue(T&, const Locale&) { }
};

template<>
struct imbue_impl<streambuf_tag> {
    template<typename T, typename Locale>
    static void imbue(T& t, const Locale& loc) { t.pubimbue(loc); }
};

template<>
struct imbue_impl<localizable_tag> {
    template<typename T, typename Locale>
    static void imbue(T& t, const Locale& loc) { t.imbue(loc); }
};

//------------------Definition of optimal_buffer_size_impl--------------------//

template<typename T>
struct optimal_buffer_size_impl
    : mpl::if_<
          detail::is_custom<T>,
          operations<T>,
          optimal_buffer_size_impl<
              BOOST_DEDUCED_TYPENAME
              detail::dispatch<
                  T, optimally_buffered_tag, device_tag, filter_tag
              >::type
          >
      >::type
    { };

template<>
struct optimal_buffer_size_impl<optimally_buffered_tag> {
    template<typename T>
    static std::streamsize optimal_buffer_size(const T& t)
    { return t.optimal_buffer_size(); }
};

template<>
struct optimal_buffer_size_impl<device_tag> {
    template<typename T>
    static std::streamsize optimal_buffer_size(const T&)
    { return default_device_buffer_size; }
};

template<>
struct optimal_buffer_size_impl<filter_tag> {
    template<typename T>
    static std::streamsize optimal_buffer_size(const T&)
    { return default_filter_buffer_size; }
};

} // End namespace detail.

//----------------------------------------------------------------------------//

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #if BOOST_WORKAROUND(BOOST_MSVC, < 1300) //-------------------------//
#endif // #ifndef BOOST_IOSTREAMS_OPERATIONS_HPP_INCLUDED //------------------//

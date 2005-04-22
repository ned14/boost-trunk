// (C) Copyright Jonathan Turkanis 2005.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Note: bidirectional streams are not supported.

#ifndef BOOST_IOSTREAMS_COMPOSE_HPP_INCLUDED
#define BOOST_IOSTREAMS_COMPOSE_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <algorithm>          // min.
#include <utility>            // pair.
#include <boost/config.hpp>   // DEDUCED_TYPENAME.
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/call_traits.hpp>
#include <boost/iostreams/detail/closer.hpp>
#include <boost/iostreams/detail/enable_if_stream.hpp>
#include <boost/iostreams/operations.hpp>
#include <boost/iostreams/traits.hpp>      // io_mode, is_direct.
#include <boost/mpl/if.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace iostreams {

namespace detail {

template<typename Filter, typename Device>
struct composite_mode {
    typedef typename io_mode<Filter>::type               filter_mode;
    typedef typename io_mode<Device>::type               device_mode;
    typedef is_convertible<filter_mode, dual_use>        is_dual_use;
    typedef typename 
            mpl::eval_if<
                is_convertible<filter_mode, dual_use>,
                mpl::if_<
                    is_convertible<device_mode, input>,
                    input,
                    output
                >,
                mpl::identity<device_mode>
            >::type                                      type;
};

//
// Template name: composite_device.
// Description: Provides a Device view of a Filter, Device pair.
// Template paramters:
//      Filter - A model of Filter.
//      Device - An indirect model of Device.
//
template< typename Filter, 
          typename Device,
          typename Mode = 
              typename composite_mode<Filter, Device>::type >
class composite_device {
private:
    typedef typename detail::param_type<Device>::type  param_type;
    typedef typename detail::value_type<Device>::type  value_type;
public:
    typedef typename io_char<Filter>::type             char_type;
    struct io_category
        : Mode,
          device_tag,
          closable_tag,
          flushable_tag,
          localizable_tag,
          optimally_buffered_tag
        { };
    composite_device(const Filter& flt, param_type dev);
    std::streamsize read(char_type* s, std::streamsize n);
    std::streamsize write(const char_type* s, std::streamsize n);
    stream_offset seek( stream_offset off, BOOST_IOS::seekdir way,
                        BOOST_IOS::openmode which =
                            BOOST_IOS::in | BOOST_IOS::out );

    void close(BOOST_IOS::openmode which = BOOST_IOS::in | BOOST_IOS::out);
    bool flush();
    std::streamsize optimal_buffer_size() const;

    template<typename Locale> // Avoid dependency on <locale>
    void imbue(const Locale& loc)
    {
        iostreams::imbue(filter_, loc);
        iostreams::imbue(device_, loc);
    }
private:
    Filter      filter_;
    value_type  device_;
};

//
// Template name: composite_device.
// Description: Provides a Device view of a Filter, Device pair.
// Template paramters:
//      Filter - A model of Filter.
//      Device - An indirect model of Device.
//
template<typename Filter1, typename Filter2>
class composite_filter {
public:
    typedef typename io_char<Filter1>::type char_type;
    struct io_category
        : io_mode<Filter1>::type,
          filter_tag,
          closable_tag,
          flushable_tag,
          localizable_tag,
          optimally_buffered_tag
        { };
    composite_filter(const Filter1& filter1, const Filter2& filter2)
        : filter1_(filter1), filter2_(filter2)
        { }

    template<typename Source>
    std::streamsize read(Source& src, char_type* s, std::streamsize n)
    {
        composite_device<Filter2, Source> cmp(filter2_, src);
        return iostreams::read(filter1_, cmp, s, n);
    }

    template<typename Sink>
    std::streamsize write(Sink& snk, const char_type* s, std::streamsize n)
    {
        composite_device<Filter2, Sink> cmp(filter2_, snk);
        return iostreams::write(filter1_, cmp, s, n);
    }

    template<typename Device>
    stream_offset seek( Device& dev, stream_offset off, BOOST_IOS::seekdir way,
                        BOOST_IOS::openmode which =
                            BOOST_IOS::in | BOOST_IOS::out )
    {
        composite_device<Filter2, Device> cmp(filter2_, dev);
        return iostreams::seek(filter1_, cmp, off, way, which);
    }

    template<typename Device>
    void close( Device& dev,
                BOOST_IOS::openmode which =
                    BOOST_IOS::in | BOOST_IOS::out )
    {
        composite_device<Filter2, Device> cmp(filter2_, dev);
        iostreams::close(filter1_, cmp, which);
    }

    template<typename Device>
    bool flush(Device& dev)
    {
        composite_device<Filter2, Device> cmp(filter2_, dev);
        return iostreams::flush(filter1_, cmp);
    }

    std::streamsize optimal_buffer_size() const
    {
        std::streamsize first = iostreams::optimal_buffer_size(filter1_);
        std::streamsize second = iostreams::optimal_buffer_size(filter2_);
        return first < second ? second : first;
    }

    template<typename Locale> // Avoid dependency on <locale>
    void imbue(const Locale& loc)
    {   // To do: consider using RAII.
        iostreams::imbue(filter_, loc);
        iostreams::imbue(device_, loc);
    }
private:
    Filter1  filter1_;
    Filter2  filter2_;
};

template<typename Filter, typename FilterOrDevice>
struct composite_traits
    : mpl::if_<
          is_device<FilterOrDevice>,
          composite_device<Filter, FilterOrDevice>,
          composite_filter<Filter, FilterOrDevice>
      >
    { };

} // End namespace detail.

template<typename Filter, typename FilterOrDevice>
struct composite_view : detail::composite_traits<Filter, FilterOrDevice>::type {
    typedef typename detail::param_type<FilterOrDevice>::type param_type;
    composite_view(const Filter& flt, param_type dev)
        : detail::composite_traits<Filter, FilterOrDevice>::type(flt, dev)
        { }
};

//--------------Implementation of compose-------------------------------------//

// Note: The following workarounds are patterned after resolve.hpp. It has not
// yet been confirmed that they are necessary.

#ifndef BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION //-------------------------//
# ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES //-------------------------------//

template<typename Filter, typename FilterOrDevice>
composite_view<Filter, FilterOrDevice>
compose( const Filter& filter, const FilterOrDevice& fod
         BOOST_IOSTREAMS_DISABLE_IF_STREAM(FilterOrDevice) )
{ return composite_view<Filter, FilterOrDevice>(filter, fod); }

template<typename Filter, typename Ch, typename Tr>
composite_view< Filter, std::basic_streambuf<Ch, Tr> >
compose(const Filter& filter, std::basic_streambuf<Ch, Tr>& sb)
{ return composite_view< std::basic_streambuf<Ch, Tr> >(filter, sb); }

template<typename Filter, typename Ch, typename Tr>
composite_view< Filter, std::basic_istream<Ch, Tr> >
compose(const Filter& filter, std::basic_istream<Ch, Tr>& is)
{ return composite_view< std::basic_istream<Ch, Tr> >(filter, is); }

template<typename Filter, typename Ch, typename Tr>
composite_view< Filter, std::basic_ostream<Ch, Tr> >
compose(const Filter& filter, std::basic_ostream<Ch, Tr>& os)
{ return composite_view< std::basic_ostream<Ch, Tr> >(filter, os); }

template<typename Filter, typename Ch, typename Tr>
composite_view< Filter, std::basic_iostream<Ch, Tr> >
compose(const Filter& filter, std::basic_iostream<Ch, Tr>& io)
{ return composite_view< std::basic_iostream<Ch, Tr> >(filter, io); }

# else // # ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES //---------------------//

template<typename Filter, typename FilterOrDevice>
composite_view<Filter, FilterOrDevice>
compose( const Filter& filter, const FilterOrDevice& fod
         BOOST_IOSTREAMS_DISABLE_IF_STREAM(FilterOrDevice) )
{ return composite_view<Filter, FilterOrDevice>(filter, fod); }

template<typename Filter>
composite_view<Filter, std::streambuf>
compose(const Filter& filter, std::streambuf& sb)
{ return composite_view<std::streambuf>(filter, sb); }

template<typename Filter>
composite_view<Filter, std::istream>
compose(const Filter& filter, std::istream& is)
{ return composite_view<std::istream>(filter, is); }

template<typename Filter>
composite_view<Filter, std::ostream>
compose(const Filter& filter, std::ostream& os)
{ return composite_view<std::ostream>(filter, os); }

template<typename Filter>
composite_view<Filter, std::iostream>
compose(const Filter& filter, std::iostream& io)
{ return composite_view<std::iostream>(filter, io); }

# endif // # ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES //--------------------//
#else // #ifndef BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION //----------------//

template<typename Filter, typename Stream>
composite_view<Filter, Stream>
compose(const Filter& filter, const Stream& strm, mpl::true_)
{   // Bad overload resolution.
    return composite_view<Filter, Stream>(filter, const_cast<Stream&>(strm));
}

template<typename Filter, typename FilterOrDevice>
composite_view<Filter, FilterOrDevice>
compose(const Filter& filter, const FilterOrDevice& fod, mpl::false_)
{ return composite_view<Filter, FilterOrDevice>(filter, fod); }

template<typename Filter, typename FilterOrDevice>
composite_view<Filter, FilterOrDevice>
compose( const Filter& filter, const FilterOrDevice& fod
         BOOST_IOSTREAMS_DISABLE_IF_STREAM(T) )
{ return compose(filter, fod, is_std_io<FilterOrDevice>()); }

# if !BOOST_WORKAROUND(__BORLANDC__, < 0x600) && \
     !BOOST_WORKAROUND(BOOST_MSVC, <= 1300) && \
     !defined(__GNUC__) // ---------------------------------------------------//

template<typename Filter, typename FilterOrDevice>
composite_view<Filter, FilterOrDevice>
compose (const Filter& filter, FilterOrDevice& fod)
{ return composite_view<Filter, FilterOrDevice>(filter, fod); }

# endif // Borland 5.x, VC6-7.0 or GCC 2.9x //--------------------------------//
#endif // #ifndef BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION //---------------//

//----------------------------------------------------------------------------//

namespace detail {

//--------------Implementation of composite_device---------------------------//

template<typename Filter, typename Device, typename Mode>
composite_device<Filter, Device, Mode>::composite_device
    (const Filter& flt, param_type dev)
    : filter_(flt), device_(dev)
    { }

template<typename Filter, typename Device, typename Mode>
inline std::streamsize composite_device<Filter, Device, Mode>::read
    (char_type* s, std::streamsize n)
{ return iostreams::read(filter_, device_, s, n); }

template<typename Filter, typename Device, typename Mode>
inline std::streamsize composite_device<Filter, Device, Mode>::write
    (const char_type* s, std::streamsize n)
{ return iostreams::write(filter_, device_, s, n); }

template<typename Filter, typename Device, typename Mode>
stream_offset composite_device<Filter, Device, Mode>::seek
    (stream_offset off, BOOST_IOS::seekdir way, BOOST_IOS::openmode which)
{ return iostreams::seek(filter_, device_, off, way, which); }

template<typename Filter, typename Device, typename Mode>
void composite_device<Filter, Device, Mode>::close
    (BOOST_IOS::openmode which = BOOST_IOS::in | BOOST_IOS::out)
{
    external_closer<Device>          close_device(device_, which);
    external_closer<Filter, Device>  close_filter(filter_, device_, which);
}

template<typename Filter, typename Device, typename Mode>
bool composite_device<Filter, Device, Mode>::flush()
{   // To do: consider using RAII.
    bool r1 = iostreams::flush(filter_, device_);
    bool r2 = iostreams::flush(device_);
    return r1 && r2;
}

template<typename Filter, typename Device, typename Mode>
std::streamsize 
composite_device<Filter, Device, Mode>::optimal_buffer_size() const
{ return iostreams::optimal_buffer_size(device_); }

} // End namespace detail.

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_COMPOSE_HPP_INCLUDED

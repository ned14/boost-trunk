// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_CHAINBUF_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CHAINBUF_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              

#include <streambuf>
#include <boost/config.hpp>                    // BOOST_MSVC, template friends.
#include <boost/iostreams/detail/access_control.hpp>
#include <boost/iostreams/detail/chain.hpp>
#include <boost/iostreams/detail/translate_int_type.hpp>
#include <boost/iostreams/detail/streambuf/linked_streambuf.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/noncopyable.hpp>

namespace boost { namespace iostreams { namespace detail {

//--------------Definition of chainbuf----------------------------------------//

//
// Template name: chainbuf.
// Description: Stream buffer which operates by delegating to the first
//      linked_streambuf in a chain.
// Template paramters:
//      Chain - The chain type.
//
template<typename Chain, typename Mode, typename Access>
class chainbuf
    : public std::basic_streambuf<
                 typename Chain::char_type,
                 typename Chain::traits_type
             >,
      public access_control<typename Chain::client_type, Access>,
      private noncopyable
{
private:
    typedef access_control<chain_client<Chain>, Access>      client_type;
public:
    typedef typename Chain::char_type                        char_type;
    BOOST_IOSTREAMS_STREAMBUF_TYPEDEFS(typename Chain::traits_type)
protected:
    typedef linked_streambuf<char_type, traits_type>         delegate_type;
    chainbuf() { client_type::set_chain(&chain_); }
    int_type underflow() 
        { sentry t(this); return translate(delegate().underflow()); }
    int_type pbackfail(int_type c)
        { sentry t(this); return translate(delegate().pbackfail(c)); }
    std::streamsize xsgetn(char_type* s, std::streamsize n)
        { sentry t(this); return delegate().xsgetn(s, n); }
    int_type overflow(int_type c)
        { sentry t(this); return translate(delegate().overflow(c)); }
    std::streamsize xsputn(const char_type* s, std::streamsize n)
        { sentry t(this); return delegate().xsputn(s, n); }
    int sync() { sentry t(this); return delegate().sync(); }
    pos_type seekoff( off_type off, std::ios::seekdir way,
                      std::ios::openmode which =
                          std::ios::in | std::ios::out )
        { sentry t(this); return delegate().seekoff(off, way, which); }
    pos_type seekpos( pos_type sp,
                      std::ios::openmode which =
                          std::ios::in | std::ios::out )
        { sentry t(this); return delegate().seekpos(sp, which); }
protected:
    typedef std::basic_streambuf<
                 typename Chain::char_type,
                 typename Chain::traits_type
            >                                                base_type;
    BOOST_IOSTREAMS_USING_PROTECTED_STREAMBUF_MEMBERS(base_type)
private:

    // Translate from std int_type to chain's int_type.
    typedef std::char_traits<char_type>                      std_traits;
    typedef typename Chain::traits_type                      chain_traits;
    typename chain_traits::int_type 
    static translate(typename std_traits::int_type c)
    { return translate_int_type<std_traits, chain_traits>(c); }

    delegate_type& delegate() { return static_cast<delegate_type&>(*chain_); }
    void get_pointers()
        {
            setg(delegate().eback(), delegate().gptr(), delegate().egptr());
            setp(delegate().pbase(), delegate().epptr());
            pbump((int) (delegate().pptr() - delegate().pbase()));
        }
    void set_pointers()
        {
            delegate().setg(eback(), gptr(),egptr());
            delegate().setp(pbase(), epptr());
            delegate().pbump((int) (pptr() - pbase()));
        }
    struct sentry {
        sentry(chainbuf<Chain, Mode, Access>* buf) : buf_(buf)
            { buf_->set_pointers(); }
        ~sentry() { buf_->get_pointers(); }
        chainbuf<Chain, Mode, Access>* buf_;
    };
    friend struct sentry;
    Chain chain_;
};

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CHAINBUF_HPP_INCLUDED

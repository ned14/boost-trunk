// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_RANDOM_ACCESS_CONTAINER_ADAPTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_RANDOM_ACCESS_CONTAINER_ADAPTER_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              

#include <boost/config.hpp>          // make sure size_t is in std.
#include <algorithm>                 // copy, min.
#include <cstddef>                   // size_t.
#include <ios>                       // ios_base.
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/error.hpp>
#include <boost/mpl/if.hpp>
#include <boost/ref.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace iostreams { namespace detail {

struct one_file_pointer {
    one_file_pointer() : ptr_(0) { }
    std::size_t& gptr() { return ptr_; }
    std::size_t& pptr() { return ptr_; }
    std::size_t ptr_;
};

struct two_file_pointers {
    two_file_pointers() : gptr_(0), pptr_(0) { }
    std::size_t& gptr() { return gptr_; }
    std::size_t& pptr() { return pptr_; }
    std::size_t gptr_;
    std::size_t pptr_;
};

template<typename Mode>
struct file_pointers 
    : mpl::if_<
          is_convertible<Mode, detail::two_head>,
          two_file_pointers,
          one_file_pointer
     >::type
    { };

template<typename Container, typename Mode>
class random_access_container_adapter {
public:
    typedef Container                       container_type;
    typedef typename Container::value_type  char_type;
    struct category 
        : device_tag,
          Mode
        { };
    random_access_container_adapter()
        : pimpl_(new impl(new Container(), true)) { }
    random_access_container_adapter(const Container& cnt)
        : pimpl_(new impl(new Container(cnt), true)) { }
    random_access_container_adapter(const reference_wrapper<Container>& ref)
        : pimpl_(new impl(ref.get_pointer(), false)) { }
    std::streamsize read(char_type* s, std::streamsize n);
    void write(const char_type* s, std::streamsize n);
    std::streamoff seek( std::streamoff, std::ios::seekdir,
                         std::ios::openmode = std::ios::in | std::ios::out );
    Container container() const { return *pimpl_->cnt_; }
    void container(const Container& cnt)
    { 
        shared_ptr<impl> pimpl(new impl(new Container(cnt), true));
        pimpl_.swap(pimpl);
    }
private:
    Container& cnt() { return *pimpl_->cnt_; }
    typedef typename Container::size_type  size_type;
    struct impl : file_pointers<Mode> {
        impl(Container* cnt, bool owns) : cnt_(cnt), owns_(owns) { }
        ~impl() { if (owns_) delete cnt_; }
        Container*  cnt_;
        bool        owns_;
    };
    shared_ptr<impl> pimpl_;
};
                    
//------------------Implementation of random_access_container_adapter---------//

template<typename Container, typename Mode>
std::streamsize random_access_container_adapter<Container, Mode>::read
    (char_type* s, std::streamsize n)
{
    BOOST_STATIC_ASSERT((is_convertible<Mode, input>::value));
    using namespace std;
    streamsize avail = 
        static_cast<streamsize>(cnt().size() - pimpl_->gptr());
    streamsize result = std::min(n, avail);
    copy( cnt().begin() + pimpl_->gptr(), // Loop might be safer.
          cnt().begin() + pimpl_->gptr() + result, 
          s ); 
    pimpl_->gptr() += result;
    return result;
}

template<typename Container, typename Mode>
void random_access_container_adapter<Container, Mode>::write
    (const char_type* s, std::streamsize n)
{
    BOOST_STATIC_ASSERT((is_convertible<Mode, output>::value));
    using namespace std;
    streamsize capacity = 
        static_cast<streamoff>(cnt().size() - pimpl_->pptr());
    streamsize amt = std::min(n, capacity);
    copy(s, s + amt, cnt().begin() + pimpl_->pptr()); // Loop might be safer.
    pimpl_->pptr() += amt;
    if (amt < n) {
        cnt().insert(cnt().end(), s + amt, s + n);
        pimpl_->pptr() = static_cast<streamoff>(cnt().size());
    }
}

template<typename Container, typename Mode>
std::streamoff random_access_container_adapter<Container, Mode>::seek
    (std::streamoff off, std::ios::seekdir way, std::ios::openmode which)
{
    using namespace std;
    if (way == ios::cur && pimpl_->gptr() != pimpl_->pptr())
       bad_seek();
    bool dual = is_convertible<Mode, two_sequence>::value;
    if ((which & ios::in) || !dual) {
        std::size_t next;
        switch (way) {
        case ios::beg:
            next = off; 
            break;
        case ios::cur:
            next = pimpl_->gptr() + off; 
            break;
        case ios::end: 
            next = cnt().size() + off; 
            break;
        }
        if (next >= 0 && next < cnt().size())
            pimpl_->gptr() = next;
        else
            bad_seek();
    }
    if ((which & ios::out) && dual) {
        std::size_t next;
        switch (way) {
        case ios::beg:
            next = off; 
            break;
        case ios::cur:
            next = pimpl_->pptr() + off; 
            break;
        case ios::end:
            next = cnt().size() + off; 
            break;
        }
        if (next >= 0 && next < cnt().size())
            pimpl_->pptr() = next;
        else
            bad_seek();
    }
    return static_cast<std::streamoff>(
               (which & ios::in) ?
                    pimpl_->gptr() :
                    pimpl_->pptr()
           );
}

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_RANDOM_ACCESS_CONTAINER_ADAPTER_HPP_INCLUDED

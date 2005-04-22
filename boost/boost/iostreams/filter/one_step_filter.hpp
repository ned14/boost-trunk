// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_ONE_STEP_FILTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_ONE_STEP_FILTER_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              

#include <algorithm>                          // copy, min.
#include <cassert>
#include <iterator>                           // back_inserter
#include <vector>
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/closer.hpp>
#include <boost/iostreams/detail/ios.hpp>     // openmode, streamsize.

#include <boost/iostreams/detail/config/disable_warnings.hpp>  // MSVC.

namespace boost { namespace iostreams {

//
// Template name: one_step_filter.
// Template paramters:
//      Ch - The character type.
//      Alloc - The allocator type.
// Description: Utility for defining DualUseFilters which filter an
//      entire stream at once. To use, override the protected virtual
//      member do_filter.
// Note: This filter should not be copied while it is in use.
//
template<typename Ch, typename Alloc = std::allocator<Ch> >
class one_step_filter  {
public:
    typedef Ch char_type;
    struct io_category
        : dual_use,
          filter_tag,
          multichar_tag,
          closable_tag
        { };
    one_step_filter() : ptr_(0), state_(0) { }
    virtual ~one_step_filter() { }

    template<typename Source>
    std::streamsize read(Source& src, char_type* s, std::streamsize n)
    {
        using namespace std;
        assert(!(state_ & f_write));
        state_ |= f_read;
        if (!(state_ & f_eof))
            do_read(src);
        streamsize amt =
            (std::min)(n, static_cast<streamsize>(data_.size() - ptr_));
        if (amt) {
            BOOST_IOSTREAMS_CHAR_TRAITS(char_type)::copy(s, &data_[ptr_], amt);
            ptr_ += amt;
        }
        return detail::check_eof(amt);
    }

    template<typename Sink>
    std::streamsize write(Sink&, const char_type* s, std::streamsize n)
    {
        assert(!(state_ & f_read));
        state_ |= f_write;
        data_.insert(data_.end(), s, s + n);
        return n;
    }
    
    typedef one_step_filter<Ch, Alloc> self;
    friend struct detail::closer<self>;
    template<typename Sink>
    void close(Sink& sink, BOOST_IOS::openmode which)
    {
        if ((state_ & f_read) && (which & BOOST_IOS::in)) 
            close();

        if ((state_ & f_write) && (which & BOOST_IOS::out)) {
            detail::closer<self> closer(*this);
            vector_type filtered;
            do_filter(data_, filtered);
            boost::iostreams::write( 
                sink, &filtered[0],
                static_cast<std::streamsize>(filtered.size())
            );
        }
    }

protected:
    typedef std::vector<Ch, Alloc>           vector_type;
    typedef typename vector_type::size_type  size_type;
private:
    virtual void do_filter(const vector_type& src, vector_type& dest) = 0;

    template<typename Source>
    void do_read(Source& src)
    {
        using std::streamsize;
        vector_type data;
        while (true) {
            const streamsize  size = default_device_buffer_size;
            Ch                buf[size];
            streamsize        amt;
            if ((amt = boost::iostreams::read(src, buf, size)) == -1)
                break;
            data.insert(data.end(), buf, buf + amt);
        }
        do_filter(data, data_);
        state_ |= f_eof;
    }

    void close()
    {
        data_.clear();
        ptr_ = 0;
        state_ = 0;
    }

    enum {
        f_read   = 1,
        f_write  = f_read << 1,
        f_eof    = f_write << 1
    };

    // Note: typically will not be copied while vector contains data.
    vector_type  data_;
    size_type    ptr_;
    int          state_;
};

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>  // MSVC.

#endif // #ifndef BOOST_IOSTREAMS_ONE_STEP_FILTER_HPP_INCLUDED

// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_CHAIN_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CHAIN_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              

#include <algorithm>                            // for_each.
#include <cassert>
#include <exception>
#include <functional>                           // unary_function.
#include <list>
#include <memory>                               // allocator, auto_ptr.
#include <stdexcept>                            // logic_error.
#include <boost/checked_delete.hpp>
#include <boost/config.hpp>                     // BOOST_MSVC, template friends.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/constants.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/iostreams/is_device.hpp>
#include <boost/iostreams/is_filter.hpp>
#include <boost/iostreams/detail/access_control.hpp>
#include <boost/iostreams/detail/character.hpp>
#include <boost/iostreams/detail/push.hpp>
#include <boost/iostreams/detail/wrap_unwrap.hpp>
#include <boost/iostreams/streambuf_facade.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace iostreams {

namespace detail {

template<typename Chain> class chain_client;

//
// Concept name: Chain.
// Description: Represents a chain of stream buffers which provides access 
//     to the first buffer in the chain and send notifications when the 
//     streambufs are added to or removed from chain.
// Refines: Closable device with mode equal to typename Chain::mode.
// Models: chain, converting_chain.
// Example:
//
//    class chain {
//    public:
//        typedef xxx chain_type;
//        typedef xxx client_type;
//        typedef xxx mode;
//        bool is_complete() const;                  // Ready for i/o.
//        template<typename T>
//        void push( const T& t,                     // Adds a stream buffer to
//                   streamsize,                     // chain, based on t, with 
//                   streamsize );                   // given buffer and putback
//                                                   // buffer sizes. Pass -1 to
//                                                   // request default size.
//    protected:
//        void register_client(client_type* client); // Associate client.
//        void notify();                             // Notify client.
//    };
// 

//
// Description: Represents a chain of filters with an optional device at the
//      end.
// Template parameters:
//      Self - A class deriving from the current instantiation of this template.
//          This is an example of the Curiously Recurring Template Pattern.
//      Ch - The character type.
//      Tr - The character traits type.
//      Alloc - The allocator type.
//      Mode - A mode tag.
//
template<typename Self, typename Ch, typename Tr, typename Alloc, typename Mode>
class chain_base {
public:
    typedef Ch                                     char_type;
    BOOST_IOSTREAMS_STREAMBUF_TYPEDEFS(Tr)
    typedef Alloc                                  allocator_type;
    typedef Mode                                   mode;
    struct io_category
        : Mode,
          device_tag,
          closable_tag 
        { };
    typedef chain_client<Self>                     client_type;
    friend class chain_client<Self>;
private:
    typedef linked_streambuf<Ch>                   streambuf_type;
    typedef std::list<streambuf_type*>             list_type;
    typedef chain_base<Self, Ch, Tr, Alloc, Mode>  my_type;
protected:
    chain_base() : pimpl_(new chain_impl) { }
    chain_base(const chain_base& rhs): pimpl_(rhs.pimpl_) { }
public:

    #if defined(BOOST_MSVC) && _MSC_VER == 1300
        virtual ~chain_base() { } // If omitted, some tests fail on VC7.0. Why?
    #endif

    //----------Buffer sizing-------------------------------------------------//

    // Sets the size of the buffer created for the devices to be added to this
    // chain. Does not affect the size of the buffer for devices already
    // added.
    void set_buffer_size(std::streamsize n)
        { pimpl_->device_buffer_size_ = n; }

    // Sets the size of the buffer created for the filters to be added
    // to this chain. Does not affect the size of the buffer for filters already
    // added.
    void set_filter_buffer_size(std::streamsize n)
        { pimpl_->filter_buffer_size_ = n; }

    // Sets the size of the putback buffer for filters and devices to be added
    // to this chain. Does not affect the size of the buffer for filters or
    // devices already added.
    void set_pback_size(std::streamsize n) { pimpl_->pback_size_ = n; }

    //----------Device interface----------------------------------------------//

    std::streamsize read(char_type* s, std::streamsize n)
        { return list().front()->sgetn(s, n); }
    void write(const char_type* s, std::streamsize n)
        { list().front()->sputn(s, n); }
    off_type seek(off_type off, std::ios::seekdir way)
        { return list().front()->pubseekoff(off, way); }

    //----------Direct stream buffer access-----------------------------------//

    streambuf_type& operator*() { return *list().front(); }
    streambuf_type* operator->() { return list().front(); }
public:
    typedef typename list_type::size_type size_type;
    BOOST_IOSTREAMS_DEFINE_PUSH(mode, char_type, push, push_impl)
    void pop();
    bool empty() const { return list().empty(); }
    size_type size() const { return list().size(); }
    void reset();

    // Returns true if this chain is non-empty and its final link
    // is a source or sink, i.e., if it is ready to perform i/o.
    bool is_complete() const { return pimpl_->complete_; }
private:
    template<typename T>
    void push_impl( const T& t,
                    std::streamsize buffer_size = -1,
                    std::streamsize pback_size = -1 )
        {
            typedef BOOST_IOSTREAMS_CATEGORY(T)       category;
            typedef typename unwrap_ios<T>::type      policy_type;
            typedef streambuf_facade<
                        policy_type, 
                        std::char_traits<char_type>,
                        Alloc, Mode
                    >                                 facade_type;
            BOOST_STATIC_ASSERT((is_convertible<category, Mode>::value));
            if (is_complete()) 
                throw std::logic_error("chain complete");
            streambuf_type* prev = !empty() ? list().back() : 0;
            buffer_size = 
                buffer_size != -1 ? 
                    buffer_size : 
                    is_filter<policy_type>::value ?
                        pimpl_->filter_buffer_size_ :
                        pimpl_->device_buffer_size_;
            pback_size = 
                pback_size != -1 ? 
                    pback_size : 
                    pimpl_->pback_size_;
            std::auto_ptr<facade_type>
                buf(new facade_type(t, buffer_size, pback_size));
            list().push_back(buf.get());
            buf.release();
            if (is_device<policy_type>::value)
                pimpl_->complete_ = true;
            if (prev) prev->set_next(list().back());
            notify();
        }

    list_type& list() { return pimpl_->links_; }
    const list_type& list() const { return pimpl_->links_; }
    void register_client(client_type* client) { pimpl_->client_ = client; }
    void notify() { if (pimpl_->client_) pimpl_->client_->notify(); }

    //----------Nested classes------------------------------------------------//

    // The static member close and the structs closer are used by
    // chain_impl::close. A more elegant solution using boost::bind failed on
    // VC6 and Borland.

    static void close(streambuf_type* b, std::ios::openmode m)
    { if (m & std::ios::out) b->pubsync(); b->close(m); }

    struct closer : public std::unary_function<streambuf_type*, void> {
        closer(std::ios::openmode m) : mode_(m) { }
        void operator() (streambuf_type* b) { close(b, mode_); }
        std::ios::openmode mode_;
    };
    friend struct closer;
    struct chain_impl {
        chain_impl()
            : client_(0), device_buffer_size_(default_buffer_size),
              filter_buffer_size_(default_filter_buffer_size),
              pback_size_(default_pback_buffer_size),
              complete_(false)
            { }
        ~chain_impl()
            {
                try { close(); } catch (std::exception&) { }
                std::for_each( links_.begin(), links_.end(),
                               checked_deleter<streambuf_type>() );
            }
        void close()
            {
                using namespace std;
                if (!complete_) return;
                links_.front()->pubsync();
                if (is_convertible<Mode, input>::value)
                    for_each( links_.rbegin(), links_.rend(), 
                              closer(ios::in) );
                if (is_convertible<Mode, output>::value)
                    for_each( links_.begin(), links_.end(), 
                              closer(ios::out) );
            }
        list_type        links_;
        client_type*     client_;
        std::streamsize  device_buffer_size_,
                         filter_buffer_size_,
                         pback_size_;
        bool             complete_;
    };
    friend struct chain_impl;

    //----------Member data---------------------------------------------------//

private:
    shared_ptr<chain_impl> pimpl_;
};

//
// Macro: BOOST_IOSTREAMS_DECL_CHAIN(name, category)
// Description: Defines a template derived from chain_base appropriate for a
//      particular i/o category. The template has the following parameters:
//      Ch - The character type.
//      Tr - The character traits type.
//      Alloc - The allocator type.
// Macro parameters:
//      name_ - The name of the template to be defined.
//      category_ - The i/o category of the template to be defined.
//
#define BOOST_IOSTREAMS_DECL_CHAIN(name_, default_char_) \
    template< typename Mode, typename Ch = default_char_, \
              typename Tr = std::char_traits<Ch>, \
              typename Alloc = std::allocator<Ch> > \
    class name_ : public boost::iostreams::detail::chain_base< \
                            name_<Mode, Ch, Tr, Alloc>, \
                            Ch, Tr, Alloc, Mode \
                         > \
    { \
    public: \
        struct io_category : device_tag, Mode { }; \
        typedef Mode                                                     mode; \
    private: \
        typedef boost::iostreams::detail::chain_base< \
                    name_<Mode, Ch, Tr, Alloc>, \
                    Ch, Tr, Alloc, Mode \
                >                                                        base_type; \
    public: \
        typedef Ch                                                       char_type; \
        typedef Tr                                                       traits_type; \
        typedef typename traits_type::int_type                           int_type; \
        typedef typename traits_type::off_type                           off_type; \
        name_() { } \
        name_(const name_& rhs) { *this = rhs; } \
        name_& operator=(const name_& rhs) \
        { base_type::operator=(rhs); return *this; } \
    }; \
    /**/
BOOST_IOSTREAMS_DECL_CHAIN(chain, char)
BOOST_IOSTREAMS_DECL_CHAIN(wchain, wchar_t)
#undef BOOST_IOSTREAMS_DECL_CHAIN

//--------------Definition of chain_client------------------------------------//

//
// Template name: chain_client
// Description: Class whose instances provide access to an underlying chain
//      using an interface similar to the chains.
// Subclasses: the various stream and stream buffer templates.
//
template<typename Chain>
class chain_client {
public:
    typedef Chain                             chain_type;
    typedef typename chain_type::char_type    char_type;
    typedef typename chain_type::traits_type  traits_type;
    typedef typename chain_type::size_type    size_type;
    typedef typename chain_type::mode         mode;

    chain_client(chain_type* chn = 0) : chain_(chn ) { }
    chain_client(chain_client* client) : chain_(client->chain_) { }
    virtual ~chain_client() { }

        // Returns a copy of the underlying chain.
    chain_type filters() { return *chain_; }
    chain_type filters() const { return *chain_; }

    bool is_complete() const { return chain_->is_complete(); }
    void set_buffer_size(std::streamsize n) { chain_->set_buffer_size(n); }
    void set_filter_buffer_size(std::streamsize n)
        { chain_->set_filter_buffer_size(n); }
    void set_pback_size(std::streamsize n) { chain_->set_pback_size(n); }
    BOOST_IOSTREAMS_DEFINE_PUSH(mode, char_type, push, push_impl)
    void pop() { chain_->pop(); }
    bool empty() const { return chain_->empty(); }
    size_type size() { return chain_->size(); }
    void reset() { chain_->reset(); }
protected:
    template<typename T>
    void push_impl(const T& t BOOST_IOSTREAMS_PUSH_PARAMS())
    { chain_->push(t BOOST_IOSTREAMS_PUSH_ARGS()); }
    chain_type& ref() { return *chain_; }
    void set_chain(chain_type* c) 
    { chain_ = c; chain_->register_client(this); }
#if !defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS) && \
    (!BOOST_WORKAROUND(__BORLANDC__, < 0x600))
    template<typename S, typename C, typename T, typename A, typename M>
    friend class chain_base;
#else
    public:
#endif
    virtual void notify() { }
private:
    chain_type* chain_;
};

//--------------Implementation of chain_base----------------------------------//

template<typename Self, typename Ch, typename Tr, typename Alloc, typename Mode>
void chain_base<Self, Ch, Tr, Alloc, Mode>::reset()
{
    using namespace std;
    pimpl_->close();
    for_each(list().begin(), list().end(), checked_deleter<streambuf_type>());
    list().clear();
    pimpl_->complete_ = false;
}

template<typename Self, typename Ch, typename Tr, typename Alloc, typename Mode>
void chain_base<Self, Ch, Tr, Alloc, Mode>::pop()
{
    assert(!empty());
    pimpl_->close();
    delete list().back();
    list().pop_back();
    pimpl_->complete_ = false;
}

} // End namespace detail.

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CHAIN_HPP_INCLUDED

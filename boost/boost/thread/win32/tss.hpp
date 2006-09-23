// Copyright (C) 2001-2003 William E. Kempf
// Copyright (C) 2006 Roland Schwarz
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// This work is a reimplementation along the design and ideas
// of William E. Kempf.

#ifndef BOOST_TSS_RS06092305_HPP
#define BOOST_TSS_RS06092305_HPP

#include <boost/thread/win32/config.hpp>

#include <boost/utility.hpp>
#include <boost/function.hpp>
#include <boost/thread/win32/exceptions.hpp>

namespace boost {

// disable warnings about non dll import
// see: http://www.boost.org/more/separate_compilation.html#dlls
#ifdef BOOST_MSVC
#	pragma warning(push)
#	pragma warning(disable: 4251 4231 4660 4275)
#endif

namespace detail {

class BOOST_THREAD_DECL tss : private noncopyable
{
public:
    tss(boost::function1<void, void*>* pcleanup) {
        if (pcleanup == 0) throw boost::thread_resource_error();
        try
        {
            init(pcleanup);
        }
        catch (...)
        {
            delete pcleanup;
            throw boost::thread_resource_error();
        }
    }

    void* get() const;
    void set(void* value);
    void cleanup(void* p);

private:
    unsigned int m_slot; //This is a "pseudo-slot", not a native slot

    void init(boost::function1<void, void*>* pcleanup);
};

template <typename T>
struct tss_adapter
{
    template <typename F>
    tss_adapter(const F& cleanup) : m_cleanup(cleanup) { }
    void operator()(void* p) { m_cleanup(static_cast<T*>(p)); }
    boost::function1<void, T*> m_cleanup;
};

} // namespace detail

template <typename T>
class thread_specific_ptr : private noncopyable
{
public:
    thread_specific_ptr()
        : m_tss(new boost::function1<void, void*>(
                    boost::detail::tss_adapter<T>(
                        &thread_specific_ptr<T>::cleanup)))
    {
    }
    thread_specific_ptr(void (*clean)(T*))
        : m_tss(new boost::function1<void, void*>(
                    boost::detail::tss_adapter<T>(clean)))
    {
    }
    ~thread_specific_ptr() { reset(); }

    T* get() const { return static_cast<T*>(m_tss.get()); }
    T* operator->() const { return get(); }
    T& operator*() const { return *get(); }
    T* release() { T* temp = get(); if (temp) m_tss.set(0); return temp; }
    void reset(T* p=0)
    {
        T* cur = get();
        if (cur == p) return;
        m_tss.set(p);
        if (cur) m_tss.cleanup(cur);
    }

private:
    static void cleanup(T* p) { delete p; }
    detail::tss m_tss;
};

#ifdef BOOST_MSVC
#	pragma warning(pop)
#endif

} // namespace boost

#endif //BOOST_TSS_RS06092305_HPP

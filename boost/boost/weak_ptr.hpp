#ifndef BOOST_WEAK_PTR_HPP_INCLUDED
#define BOOST_WEAK_PTR_HPP_INCLUDED

//
//  weak_ptr.hpp
//
//  Copyright (c) 2001, 2002 Peter Dimov
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  See http://www.boost.org/libs/smart_ptr/weak_ptr.htm for documentation.
//

#include <boost/shared_ptr.hpp>

#include <cstring> // for std::memcpy

#ifdef BOOST_MSVC  // moved here to work around VC++ compiler crash
# pragma warning(push)
# pragma warning(disable:4284) // odd return type for operator->
#endif

namespace boost
{

template<class T> class weak_ptr
{
private:

    // Borland 5.5.1 specific workarounds
    typedef weak_ptr<T> this_type;

public:

    typedef T element_type;

    weak_ptr(): px(0), pn()
    {
    }

//  generated copy constructor, assignment, destructor are fine

    template<class Y>
    weak_ptr(weak_ptr<Y> const & r): pn(r.pn) // never throws
    {
        // r.px may be an invalid pointer value
        using namespace std;
        memcpy(&this->px, &r.px, sizeof(r.px));
    }

    template<class Y>
    weak_ptr(shared_ptr<Y> const & r): px(r.px), pn(r.pn) // never throws
    {
    }

#if !defined(BOOST_MSVC) || (BOOST_MSVC > 1200)

    template<class Y>
    weak_ptr & operator=(weak_ptr<Y> const & r) // never throws
    {
        px = r.px;
        pn = r.pn;
        return *this;
    }

    template<class Y>
    weak_ptr & operator=(shared_ptr<Y> const & r) // never throws
    {
        px = r.px;
        pn = r.pn;
        return *this;
    }

#endif

    void reset()
    {
        this_type().swap(*this);
    }

    long use_count() const // never throws
    {
        return pn.use_count();
    }

    bool expired() const // never throws
    {
        return pn.use_count() == 0;
    }

    void swap(this_type & other) // never throws
    {
        std::swap(px, other.px);
        pn.swap(other.pn);
    }

    void _internal_assign(T * px2, detail::shared_count const & pn2) // implementation detail
    {
        px = px2;
        pn = pn2;
    }

    bool _internal_less(this_type const & rhs) const // implementation detail, never throws
    {
        return pn < rhs.pn;
    }

// Tasteless as this may seem, making all members public allows member templates
// to work in the absence of member template friends. (Matthew Langston)

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS

private:

    template<class Y> friend class weak_ptr;
    template<class Y> friend class shared_ptr;

#endif

    T * px;                     // contained pointer
    detail::weak_count pn;      // reference counter

};  // weak_ptr

template<class T> inline bool operator<(weak_ptr<T> const & a, weak_ptr<T> const & b)
{
    return a._internal_less(b);
}

template<class T> void swap(weak_ptr<T> & a, weak_ptr<T> & b)
{
    a.swap(b);
}

template<class T> shared_ptr<T> make_shared(weak_ptr<T> const & r) // never throws
{
#if defined(BOOST_HAS_THREADS)

    // optimization: avoid throw overhead
    if(r.use_count() == 0)
    {
        return shared_ptr<T>();
    }

    try
    {
        return shared_ptr<T>(r);
    }
    catch(bad_weak_ptr const &)
    {
        // Q: how can we get here?
        // A: another thread may have invalidated r after the use_count test above.
        return shared_ptr<T>();
    }

#else

    // optimization: avoid try/catch overhead when single threaded
    return r.use_count() == 0? shared_ptr<T>(): shared_ptr<T>(r);

#endif
}

} // namespace boost

#ifdef BOOST_MSVC
# pragma warning(pop)
#endif    

#endif  // #ifndef BOOST_WEAK_PTR_HPP_INCLUDED

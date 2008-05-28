
// Copyright 2008 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNORDERED_DETAIL_ALLOCATOR_HPP_INCLUDED
#define BOOST_UNORDERED_DETAIL_ALLOCATOR_HPP_INCLUDED

namespace boost
{
namespace unordered_detail
{
    // TODO: Use std::allocator if it's up to the task.

    template <class T> class allocator;

    // specialize for void:
    template <> class allocator<void> {
    public:
        typedef void* pointer;
        typedef const void* const_pointer;
        // reference-to-void members are impossible.
        typedef void value_type;
        template <class U> struct rebind { typedef allocator<U> other; };
    };

    template <class T> class allocator {
    public:
        typedef size_t    size_type;
        typedef ptrdiff_t difference_type;
        typedef T*        pointer;
        typedef const T*  const_pointer;
        typedef T&        reference;
        typedef const T&  const_reference;
        typedef T         value_type;

        template <class U> struct rebind { typedef allocator<U> other; };
        
        allocator() {}
        template <class U> allocator(const allocator<U>&) {}

        pointer address(reference x) const { return &x; }
        const_pointer address(const_reference x) const { return & x; }

        pointer allocate(size_type num, allocator<void>::const_pointer = 0)
        {
            return static_cast<pointer>(::operator new(num * sizeof(T)));
        }

        void deallocate(pointer p, size_type)
        {
            ::operator delete(static_cast<void*>(p));
        }

        size_type max_size() const throw()
        {
            return (std::numeric_limits<size_type>::max)();
        }

        void construct(pointer p, const T& val)
        {
            new (static_cast<void*>(p)) T(val);
        }

#if defined(BOOST_HAS_RVALUE_REFS) && defined(BOOST_HAS_VARIADIC_TMPL)
        // TODO: I might need my own std::forward. Where will this end?
        template<class... Args> void construct(pointer p, Args&&... args)
        {
            new (static_cast<void*>(p)) T(std::forward<Args>(args)...);

        }
#else
        // TODO: Need something smarter...
        template <class Arg1>
        void construct(pointer p, Arg1 const& arg1)
        {
            new (static_cast<void*>(p)) T(arg1);
        }

        template <class Arg1, class Arg2>
        void construct(pointer p, Arg1 const& arg1, Arg2 const& arg2)
        {
            new (static_cast<void*>(p)) T(arg1, arg2);
        }

        template <class Arg1, class Arg2, class Arg3>
        void construct(pointer p, Arg1 const& arg1, Arg2 const& arg2, Arg3 const& arg3)
        {
            new (static_cast<void*>(p)) T(arg1, arg2, arg3);
        }
#endif

        void destroy(pointer p)
        {
            p->~T();
        }
    };

    template <class T>
    bool operator==(allocator<T> const&, allocator<T> const&)
    {
        return true;
    }

    template <class T>
    bool operator!=(allocator<T> const&, allocator<T> const&)
    {
        return false;
    }
}
}

#endif

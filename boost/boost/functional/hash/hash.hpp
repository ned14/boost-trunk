
//  (C) Copyright Daniel James 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  Based on Peter Dimov's proposal
//  http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2005/n1756.pdf
//  issue 6.18. 

#if !defined(BOOST_FUNCTIONAL_HASH_HASH_HPP)
#define BOOST_FUNCTIONAL_HASH_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/config.hpp>
#include <cstddef>
#include <cmath>
#include <string>
#include <functional>
#include <boost/limits.hpp>
#include <boost/functional/detail/float_functions.hpp>
#include <boost/detail/workaround.hpp>
#if !defined(BOOST_NO_CV_SPECIALIZATIONS)
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#endif

namespace boost
{
#if defined(__BORLANDC__)
    // Borland complains about an ambiguous function overload
    // when compiling boost::hash<bool>.
    std::size_t hash_value(bool);
#endif
    
    std::size_t hash_value(int);
    std::size_t hash_value(unsigned int);
    std::size_t hash_value(long);
    std::size_t hash_value(unsigned long);

    template <class T> std::size_t hash_value(T*);

    std::size_t hash_value(float v);
    std::size_t hash_value(double v);
    std::size_t hash_value(long double v);

#if BOOST_WORKAROUND(__GNUC__, < 3) && !defined(__SGI_STL_PORT) && !defined(_STLPORT_VERSION)
    template <class Ch, class A>
    std::size_t hash_value(std::basic_string<Ch, std::string_char_traits<Ch>, A> const&);
#else
    template <class Ch, class A>
    std::size_t hash_value(std::basic_string<Ch, std::char_traits<Ch>, A> const&);
#endif

    template <class It> std::size_t hash_range(It first, It last);
    template <class It> void hash_range(std::size_t&, It first, It last);
#if !defined(BOOST_NO_CV_SPECIALIZATIONS)
    template <class Range> std::size_t hash_range(Range const& range);
    template <class Range> void hash_range(std::size_t&, Range const& range);
#endif

    template <class T> void hash_combine(std::size_t& seed, T const& v);

    // Implementation

#if defined(__BORLANDC__)
    inline std::size_t hash_value(bool v)
    {
        return static_cast<std::size_t>(v);
    }
#endif

    inline std::size_t hash_value(int v)
    {
        return static_cast<std::size_t>(v);
    }

    inline std::size_t hash_value(unsigned int v)
    {
        return static_cast<std::size_t>(v);
    }

    inline std::size_t hash_value(long v)
    {
        return static_cast<std::size_t>(v);
    }

    inline std::size_t hash_value(unsigned long v)
    {
        return static_cast<std::size_t>(v);
    }

    // Implementation by Alberto Barbati and Dave Harris.
    template <class T> inline std::size_t hash_value(T* v)
    {
        std::size_t x = static_cast<std::size_t>(
           reinterpret_cast<std::ptrdiff_t>(v));
        return x + (x >> 3);
    }

    namespace hash_detail
    {
        // This allows boost::hash to be specialised for classes in the
        // standard namespace. It appears that a strict two phase template
        // implementation only finds overloads that are in the current
        // namespace at the point of definition (at instantiation
        // it only finds new overloads via. ADL on the dependant paramters or
        // something like that).
        template <class T>
        struct call_hash
        {
            static std::size_t call(T const& v)
            {
                using namespace boost;
                return hash_value(v);
            }
        };
    }

    template <class T>
    inline void hash_combine(std::size_t& seed, T const& v)
    {
        seed ^= hash_detail::call_hash<T>::call(v)
            + 0x9e3779b9 + (seed<<6) + (seed>>2);
    }

    template <class It>
    inline std::size_t hash_range(It first, It last)
    {
        std::size_t seed = 0;

        for(; first != last; ++first)
        {
            hash_combine(seed, *first);
        }

        return seed;
    }

    template <class It>
    inline void hash_range(std::size_t& seed, It first, It last)
    {
        for(; first != last; ++first)
        {
            hash_combine(seed, *first);
        }
    }

#if !defined(BOOST_NO_CV_SPECIALIZATIONS)
    template <class Range>
    inline std::size_t hash_range(Range const& range)
    {
        return hash_range(boost::const_begin(range), boost::const_end(range));
    }

    template <class Range>
    inline void hash_range(std::size_t& seed, Range const& range)
    {
        hash_range(seed, boost::const_begin(range), boost::const_end(range));
    }
#endif

#if BOOST_WORKAROUND(__GNUC__, < 3) && !defined(__SGI_STL_PORT) && !defined(_STLPORT_VERSION)
    template <class Ch, class A>
    inline std::size_t hash_value(std::basic_string<Ch, std::string_char_traits<Ch>, A> const& v)
#else
    template <class Ch, class A>
    inline std::size_t hash_value(std::basic_string<Ch, std::char_traits<Ch>, A> const& v)
#endif
    {
        return hash_range(v.begin(), v.end());
    }

    namespace hash_detail
    {
        template <class T>
        inline std::size_t float_hash_value(T v)
        {
            int exp;
            v = boost::hash_detail::call_frexp(v, &exp);

            std::size_t seed = 0;

            std::size_t const length
                = (std::numeric_limits<T>::digits +
                        std::numeric_limits<int>::digits - 1)
                / std::numeric_limits<int>::digits;

            for(std::size_t i = 0; i < length; ++i)
            {
                v = boost::hash_detail::call_ldexp(v, std::numeric_limits<int>::digits);
                int const part = static_cast<int>(v);
                v -= part;
                boost::hash_combine(seed, part);
            }

            boost::hash_combine(seed, exp);

            return seed;
        }
    }

    inline std::size_t hash_value(float v)
    {
        return boost::hash_detail::float_hash_value(v);
    }

    inline std::size_t hash_value(double v)
    {
        return boost::hash_detail::float_hash_value(v);
    }

    inline std::size_t hash_value(long double v)
    {
        return boost::hash_detail::float_hash_value(v);
    }

    // boost::hash

    template <class T> struct hash
        : std::unary_function<T, std::size_t>
    {
        std::size_t operator()(T const& val) const
        {
            return hash_detail::call_hash<T>::call(val);
        }
    };
}

#endif

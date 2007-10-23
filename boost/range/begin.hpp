// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_BEGIN_HPP
#define BOOST_RANGE_BEGIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/range/config.hpp>

#ifdef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
#include <boost/range/detail/begin.hpp>
#else

#include <boost/range/iterator.hpp>

namespace boost
{

#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564)) && \
    !BOOST_WORKAROUND(__GNUC__, < 3) \
    /**/
namespace range_detail
{
#endif

    //////////////////////////////////////////////////////////////////////
    // primary template
    //////////////////////////////////////////////////////////////////////

    template< typename C >
    inline BOOST_DEDUCED_TYPENAME range_iterator<C>::type
    boost_range_begin( C& c )
    {
        return c.begin();
    }

    //////////////////////////////////////////////////////////////////////
    // pair
    //////////////////////////////////////////////////////////////////////

    template< typename Iterator >
    inline Iterator boost_range_begin( const std::pair<Iterator,Iterator>& p )
    {
        return p.first;
    }

    template< typename Iterator >
    inline Iterator boost_range_begin( std::pair<Iterator,Iterator>& p )
    {
        return p.first;
    }

    //////////////////////////////////////////////////////////////////////
    // array
    //////////////////////////////////////////////////////////////////////

    //
    // May this be discarded? Or is it needed for bad compilers?
    //
    template< typename T, std::size_t sz >
    inline const T* boost_range_begin( const T (&array)[sz] )
    {
        return array;
    }

    template< typename T, std::size_t sz >
    inline T* boost_range_begin( T (&array)[sz] )
    {
        return array;
    }


#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564)) && \
    !BOOST_WORKAROUND(__GNUC__, < 3) \
    /**/
} // namespace 'range_detail'
#endif


template< class T >
inline BOOST_DEDUCED_TYPENAME range_iterator<T>::type begin( T& r )
{
#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564)) && \
    !BOOST_WORKAROUND(__GNUC__, < 3) \
    /**/
    using namespace range_detail;
#endif
    return boost_range_begin( r );
}

template< class T >
inline BOOST_DEDUCED_TYPENAME range_iterator<const T>::type begin( const T& r )
{
#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564)) && \
    !BOOST_WORKAROUND(__GNUC__, < 3) \
    /**/
    using namespace range_detail;
#endif
    return boost_range_begin( r );
}

} // namespace boost

#endif // BOOST_NO_FUNCTION_TEMPLATE_ORDERING

namespace boost
{
    template< class T >
    inline BOOST_DEDUCED_TYPENAME range_iterator<const T>::type
    const_begin( const T& r )
    {
        return boost::begin( r );
    }
}

#endif


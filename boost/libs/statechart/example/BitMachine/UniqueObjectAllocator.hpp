#ifndef UNIQUE_OBJECT_ALLOCATOR_HPP_INCLUDED
#define UNIQUE_OBJECT_ALLOCATOR_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) Andreas Huber Doenni 2002-2004.
// Use, modification and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/detail/avoid_unused_warning.hpp>

#include <boost/config.hpp>

#ifdef BOOST_MSVC
#  pragma warning( push )
#  pragma warning( disable: 4511 ) // copy constructor could not be generated
#  pragma warning( disable: 4512 ) // assignment operator could not be generated
#endif

#include <boost/type_traits/alignment_of.hpp>

#ifdef BOOST_MSVC
#  pragma warning( pop )
#endif

#include <boost/type_traits/type_with_alignment.hpp>
#include <boost/assert.hpp>

#include <cstddef> // size_t



//////////////////////////////////////////////////////////////////////////////
template< class T >
class UniqueObjectAllocator
{
  public:
    //////////////////////////////////////////////////////////////////////////
    static void * allocate( size_t size )
    {
      boost::fsm::detail::avoid_unused_warning( size );
      BOOST_ASSERT( !constructed_ && ( size == sizeof( T ) ) );
      constructed_ = true;
      return &storage_.data[ 0 ];
    }

    static void deallocate( void * p, size_t size )
    {
      boost::fsm::detail::avoid_unused_warning( p );
      boost::fsm::detail::avoid_unused_warning( size );
      BOOST_ASSERT( constructed_ &&
        ( p == &storage_.data[ 0 ] ) && ( size == sizeof( T ) ) );
      constructed_ = false;
    }

  private:
    //////////////////////////////////////////////////////////////////////////
    union storage
    {
      char data[ sizeof( T ) ];
      typename boost::type_with_alignment<
        boost::alignment_of< T >::value >::type aligner_;
    };

    static bool constructed_;
    static storage storage_;
};

template< class T >
bool UniqueObjectAllocator< T >::constructed_ = false;
template< class T >
typename UniqueObjectAllocator< T >::storage
  UniqueObjectAllocator< T >::storage_;



#endif

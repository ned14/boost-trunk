#ifndef BOOST_FSM_EXAMPLE_UNIQUE_OBJECT_HPP_INCLUDED
#define BOOST_FSM_EXAMPLE_UNIQUE_OBJECT_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2002-2004
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include "UniqueObjectAllocator.hpp"



//////////////////////////////////////////////////////////////////////////////
template< class Derived >
class UniqueObject
{
  public:
    //////////////////////////////////////////////////////////////////////////
    static void * operator new( size_t size )
    {
      return UniqueObjectAllocator< Derived >::allocate( size );
    }

    static void operator delete( void * p, size_t size )
    {
      UniqueObjectAllocator< Derived >::deallocate( p, size );
    }

  protected:
    //////////////////////////////////////////////////////////////////////////
    UniqueObject() {}
    ~UniqueObject() {}
};



#endif

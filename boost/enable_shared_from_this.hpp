#ifndef BOOST_ENABLE_SHARED_FROM_THIS_HPP_INCLUDED
#define BOOST_ENABLE_SHARED_FROM_THIS_HPP_INCLUDED

//
//  enable_shared_from_this.hpp
//
//  Copyright (c) 2002 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//  http://www.boost.org/libs/smart_ptr/enable_shared_from_this.html
//

#include <boost/shared_ptr.hpp>
#include <boost/assert.hpp>
#include <boost/config.hpp>

namespace boost
{

template< class T > class enable_shared_from_this;
template< class T, class Y > void sp_accept_owner( shared_ptr<Y> * ptr, enable_shared_from_this<T> const * pe );
template< class T, class Y > void sp_accept_owner( shared_ptr<Y> * ptr, enable_shared_from_this<T> const * pe, void * /*pd*/ );

template< class T > class enable_shared_from_this
{
protected:

    enable_shared_from_this()
    {
    }

    enable_shared_from_this(enable_shared_from_this const &)
    {
    }

    enable_shared_from_this & operator=(enable_shared_from_this const &)
    {
        return *this;
    }

// virtual destructor because we need a vtable for dynamic_cast from base to derived to work
    virtual ~enable_shared_from_this()
    {
// make sure no dangling shared_ptr objects were created by the
// user calling shared_from_this() but never passing ownership of the object
// to a shared_ptr.
        BOOST_ASSERT( _shared_count.use_count() <= 1 );
    }

public:

    shared_ptr<T> shared_from_this()
    {
        init_weak_once();
        T * p = dynamic_cast<T *>( this );
        return shared_ptr<T>( detail::shared_count( _weak_count ), p );
    }

    shared_ptr<T const> shared_from_this() const
    {
        init_weak_once();
        T const * p = dynamic_cast<T const *>( this );
        return shared_ptr<T const>( detail::shared_count( _weak_count ), p );
    }

private:

    mutable detail::weak_count _weak_count;
    mutable detail::shared_count _shared_count;

    void init_weak_once() const
    {
        if( _weak_count.empty() )
        {
            detail::shared_count( (void*)0, detail::sp_deleter_wrapper() ).swap( _shared_count );
            _weak_count = _shared_count;
        }
    }

    template<typename U>
    void sp_accept_owner( shared_ptr<U> & owner ) const
    {
        if( _weak_count.use_count() == 0 )
        {
            _weak_count = owner.get_shared_count();
        }else if( !_shared_count.empty() )
        {
            BOOST_ASSERT( owner.unique() ); // no weak_ptrs to owner should exist either, but there's no way to check that
            typedef detail::sp_deleter_wrapper D;
            D * pd = static_cast<D *>( _shared_count.get_deleter( BOOST_SP_TYPEID(D) ) );
            BOOST_ASSERT( pd != 0 );
            pd->set_deleter( owner );
            owner.reset( _shared_count, owner.get() );
            detail::shared_count().swap( _shared_count );
        }
    }

    template< class U, class Y > friend void sp_accept_owner( shared_ptr<Y> * ptr, enable_shared_from_this<U> const * pe );
    template< class U, class Y > friend void sp_accept_owner( shared_ptr<Y> * ptr, enable_shared_from_this<U> const * pe, void * /*pd*/ );
};

template< class T, class Y > inline void sp_accept_owner( shared_ptr<Y> * ptr, enable_shared_from_this<T> const * pe )
{
    if( pe != 0 )
    {
        pe->sp_accept_owner( *ptr );
    }
}

template< class T, class Y > inline void sp_accept_owner( shared_ptr<Y> * ptr, enable_shared_from_this<T> const * pe, void * /*pd*/ )
{
    if( pe != 0 )
    {
        pe->sp_accept_owner( *ptr );
    }
}

} // namespace boost

#endif  // #ifndef BOOST_ENABLE_SHARED_FROM_THIS_HPP_INCLUDED

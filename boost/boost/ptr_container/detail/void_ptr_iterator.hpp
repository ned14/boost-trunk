//
// Boost.Pointer Container
//
//  Copyright Thorsten Ottosen 2003-2005. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/ptr_container/
//

#ifndef BOOST_PTR_CONTAINER_DETAIL_VOID_PTR_ITERATOR_HPP
#define BOOST_PTR_CONTAINER_DETAIL_VOID_PTR_ITERATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/config.hpp>
#include <boost/iterator/iterator_traits.hpp>

namespace boost
{
    //namespace ptr_container_detail
    //{
        template
        < 
            class VoidIter, 
            class T
        >
        class void_ptr_iterator
        {
        public:
            typedef T        value_type;
            typedef T&       reference;
            typedef T*       pointer;

            typedef  BOOST_DEDUCED_TYPENAME iterator_difference<VoidIter>::type
                             difference_type;           
            typedef  BOOST_DEDUCED_TYPENAME iterator_category<VoidIter>::type
                             iterator_category;           
        private:

            VoidIter iter_;

        public:
            void_ptr_iterator() : iter_()
            { }

            void_ptr_iterator( VoidIter r ) : iter_(r)
            { }

            //
            // Remark: passing by value breaks vc7.1 
            //
            template< class MutableIterator, class MutableT >
            void_ptr_iterator( const void_ptr_iterator<MutableIterator,MutableT>& r )
             : iter_(r.base())
            { }

            T& operator*() const
            {
                return *static_cast<T*>( *iter_ );
            }

            T* operator->() const
            {
                return static_cast<T*>( *iter_ );
            }
            
            void_ptr_iterator& operator++()
            {
                ++iter_;
                return *this;
            }

            void_ptr_iterator operator++(int)
            {
                void_ptr_iterator res = *this;
                ++iter_;
                return res;
            }

            void_ptr_iterator& operator--()
            {
                --iter_;
                return *this;
            }

            void_ptr_iterator operator--(int)
            {
                void_ptr_iterator res = *this;
                --iter_;
                return res;
            }

            void_ptr_iterator& operator+=( difference_type n )
            {
                iter_ += n;
                return *this;
            }

            void_ptr_iterator& operator-=( difference_type n )
            {
                iter_ -= n;
                return *this;
            }

            T& operator[]( difference_type n ) const
            {
                return *static_cast<T*>( *(iter_ + n) );
            }

            VoidIter base() const
            {
                return iter_;
            }

            friend inline bool operator==( void_ptr_iterator l, void_ptr_iterator r )
            {
                return l.iter_ == r.iter_;
            }

            friend inline bool operator!=( void_ptr_iterator l, void_ptr_iterator r )
            {
                return l.iter_ != r.iter_;
            }

            //
            // Friend functions are always instantiated and so 
            // will cause problems with a list's iterators;
            // Therefore we provide these as ordinary members
            //
            bool operator<( void_ptr_iterator r ) const
            {
                return iter_ < r.iter_;
            }

            bool operator<=( void_ptr_iterator r ) const
            {
                return iter_ <= r.iter_;
            }
            
            bool operator>( void_ptr_iterator r ) const
            {
                return iter_ > r.iter_;
            }
            
            bool operator>=( void_ptr_iterator r ) const
            {
                return iter_ >= r.iter_;
            }

        }; // class 'void_ptr_iterator'

        template< class VoidIter, class T >
        inline void_ptr_iterator<VoidIter,T> 
        operator+( void_ptr_iterator<VoidIter,T> l, 
                   BOOST_DEDUCED_TYPENAME void_ptr_iterator<VoidIter,T>::difference_type n )
        {
            l += n;
            return l;
        }

        template< class VoidIter, class T >
        inline void_ptr_iterator<VoidIter,T> 
        operator+( BOOST_DEDUCED_TYPENAME void_ptr_iterator<VoidIter,T>::difference_type n, 
                   void_ptr_iterator<VoidIter,T> r ) 

        {
            r += n;
            return r;
        }

        template< class VoidIter, class T >
        inline void_ptr_iterator<VoidIter,T> 
        operator-( void_ptr_iterator<VoidIter,T> l, 
                   BOOST_DEDUCED_TYPENAME void_ptr_iterator<VoidIter,T>::difference_type n )
        {
            l -= n;
            return l;
        }

        template< class VoidIter, class T >
        inline void_ptr_iterator<VoidIter,T> 
        operator-( BOOST_DEDUCED_TYPENAME void_ptr_iterator<VoidIter,T>::difference_type n, 
                   void_ptr_iterator<VoidIter,T> r ) 

        {
            r -= n;
            return r;
        }

        template< class VoidIter, class T >
        inline BOOST_DEDUCED_TYPENAME void_ptr_iterator<VoidIter,T>::difference_type
        operator-( void_ptr_iterator<VoidIter,T> l,
                   void_ptr_iterator<VoidIter,T> r ) 

        {
            return l.base() - r.base();
        }

    //} // nameespace 'ptr_container_detail'
    
}

#endif

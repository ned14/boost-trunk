//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztañaga 2005-2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_OFFSET_PTR_HPP
#define BOOST_OFFSET_PTR_HPP

#if (defined _MSC_VER) && (_MSC_VER >= 1200)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/interprocess/detail/cast_tags.hpp>
#include <boost/assert.hpp>
#include <boost/type_traits/has_trivial_constructor.hpp>
#include <boost/type_traits/has_trivial_destructor.hpp>

/*!\file
   Describes a smart pointer that stores the offset between this pointer and
   target pointee, called offset_ptr.
*/
namespace boost {

namespace interprocess {

/*!A smart pointer that stores the offset between between the pointer and the
   the object it points. This allows offset allows special properties, since
   the pointer is independent from the address address of the pointee, if the
   pointer and the pointee are still separated by the same offset. This feature
   converts offset_ptr in a smart pointer that can be placed in shared memory and
   memory mapped files mapped in different addresses in every process.*/
template <class PointedType>
class offset_ptr
{
   typedef boost::interprocess::workaround::random_it<PointedType> random_it_t;
   typedef offset_ptr<PointedType>                          self_t;
   typedef typename random_it_t::const_pointer              const_pointer_t;
   typedef typename random_it_t::const_reference            const_reference_t;

   void unspecified_bool_type_func() const {}
   typedef void (self_t::*unspecified_bool_type)() const;

   void set_offset(const void *ptr)
   {  
      //offset == 1 && ptr != 0 is not legal for this pointer
      if(ptr){
         m_offset = detail::char_ptr_cast(ptr) - 
                    detail::char_ptr_cast(this);
         BOOST_ASSERT(m_offset != 1);
      }
      else{
         m_offset = 1;
      }
   }

   void inc_offset(std::ptrdiff_t bytes)
   {  m_offset += bytes;   }

   void dec_offset(std::ptrdiff_t bytes)
   {  m_offset -= bytes;   }

   void* get_pointer(void) const
   {  return m_offset == 1 ? 0 : detail::char_ptr_cast(this) + m_offset; }

   std::ptrdiff_t m_offset; //Distance between this object and pointed address

   public:
   typedef typename random_it_t::pointer                    pointer;
   typedef typename random_it_t::reference                  reference;
   typedef typename random_it_t::value_type                 value_type;
   typedef typename random_it_t::difference_type            difference_type;
   typedef typename random_it_t::iterator_category          iterator_category;

   public:   //Public Functions

   /*!Constructor from raw pointer (allows "0" pointer conversion). Never throws.*/
   offset_ptr(pointer ptr = 0) {  this->set_offset(ptr); }

   /*!Constructor from other pointer. Never throws.*/
   template <class T>
   offset_ptr(T *ptr) 
   {  pointer p (ptr);  (void)p; this->set_offset(ptr); }

   /*!Constructor from other offset_ptr */
   offset_ptr(const offset_ptr& ptr) 
   {  this->set_offset(ptr.get());   }

   /*!Constructor from other offset_ptr. If pointers of pointee types are 
      convertible, offset_ptrs will be convertibles. Never throws.*/
   template<class T2>
   offset_ptr(const offset_ptr<T2> &ptr) 
   {  pointer p(ptr.get());  (void)p; this->set_offset(ptr.get());   }

   /*!Emulates static_cast operator. Never throws.  */
   template<class Y>
   offset_ptr(const offset_ptr<Y> & r, detail::static_cast_tag)
   {  this->set_offset(static_cast<PointedType*>(r.get()));   }

   /*!Emulates const_cast operator. Never throws.*/
   template<class Y>
   offset_ptr(const offset_ptr<Y> & r, detail::const_cast_tag)
   {  this->set_offset(const_cast<PointedType*>(r.get()));   }

   /*!Emulates dynamic_cast operator. Never throws.*/
   template<class Y>
   offset_ptr(const offset_ptr<Y> & r, detail::dynamic_cast_tag)
   {  this->set_offset(dynamic_cast<PointedType*>(r.get()));   }

   /*!Emulates reinterpret_cast operator. Never throws.*/
   template<class Y>
   offset_ptr(const offset_ptr<Y> & r, detail::reinterpret_cast_tag)
   {  this->set_offset(reinterpret_cast<PointedType*>(r.get()));   }

   /*!Obtains raw pointer from offset. Never throws.*/
   pointer get()const
   {  return (pointer)this->get_pointer();   }

   /*!Pointer-like -> operator. It can return 0 pointer. Never throws.*/
   pointer operator->() const           
   {  return this->get(); }

   /*!Dereferencing operator, if it is a null offset_ptr behavior 
         is undefined. Never throws.*/
   reference operator* () const           
   {  return *(this->get());   }

   /*!Indexing operator. Never throws.*/
   reference operator[](std::ptrdiff_t idx) const   
   {  return this->get()[idx];  }

   /*!Assignment from pointer (saves extra conversion). Never throws.*/
   offset_ptr& operator= (pointer from)
   {  this->set_offset(from); return *this;  }

   /*!Assignment from other offset_ptr. Never throws.*/
   offset_ptr& operator= (const offset_ptr & pt)
   {  pointer p(pt.get());  (void)p; this->set_offset(pt.get());  return *this;  }

   /*!Assignment from related offset_ptr. If pointers of pointee types 
         are assignable, offset_ptrs will be assignable. Never throws.*/
   template <class T2>
   offset_ptr& operator= (const offset_ptr<T2> & pt)
   {  this->set_offset(pt.get());  return *this;  }
 
   /*!offset_ptr + std::ptrdiff_t. Never throws.*/
   offset_ptr operator+ (std::ptrdiff_t offset) const   
   {  return offset_ptr(this->get()+offset);   }

   /*!offset_ptr - std::ptrdiff_t. Never throws.*/
   offset_ptr operator- (std::ptrdiff_t offset) const   
   {  return offset_ptr(this->get()-offset);   }

   /*!offset_ptr += std::ptrdiff_t. Never throws.*/
   offset_ptr &operator+= (std::ptrdiff_t offset)
   {  this->inc_offset(offset * sizeof (PointedType));   return *this;  }

   /*!offset_ptr -= std::ptrdiff_t. Never throws.*/
   offset_ptr &operator-= (std::ptrdiff_t offset)
   {  this->dec_offset(offset * sizeof (PointedType));   return *this;  }

   /*!++offset_ptr. Never throws.*/
   offset_ptr& operator++ (void) 
   {  this->inc_offset(sizeof (PointedType));   return *this;  }

   /*!offset_ptr++. Never throws.*/
   offset_ptr operator++ (int)
   {  offset_ptr temp(*this); ++*this; return temp; }

   /*!--offset_ptr. Never throws.*/
   offset_ptr& operator-- (void) 
   {  this->dec_offset(sizeof (PointedType));   return *this;  }

   /*!offset_ptr--. Never throws.*/
   offset_ptr operator-- (int)
   {  offset_ptr temp(*this); --*this; return temp; }

   /*!safe bool conversion operator. Never throws.*/
   operator unspecified_bool_type() const  
   {  return this->get()? &self_t::unspecified_bool_type_func : 0;   }

   /*!Not operator. Not needed in theory, but improves portability. 
      Never throws.*/
   bool operator! () const
   {  return this->get() == 0;   }
/*
   friend void swap (offset_ptr &pt, offset_ptr &pt2)
   {  
      value_type *ptr = pt.get();
      pt = pt2;
      pt2 = ptr;
   }
*/
};

/*!offset_ptr<T1> == offset_ptr<T2>. Never throws.*/
template<class T1, class T2>
inline bool operator== (const offset_ptr<T1> &pt1, 
                        const offset_ptr<T2> &pt2)
{  return pt1.get() == pt2.get();  }

/*!offset_ptr<T1> != offset_ptr<T2>. Never throws.*/
template<class T1, class T2>
inline bool operator!= (const offset_ptr<T1> &pt1, 
                        const offset_ptr<T2> &pt2)
{  return pt1.get() != pt2.get();  }

/*!offset_ptr<T1> < offset_ptr<T2>. Never throws.*/
template<class T1, class T2>
inline bool operator< (const offset_ptr<T1> &pt1, 
                       const offset_ptr<T2> &pt2)
{  return pt1.get() < pt2.get();  }

/*!offset_ptr<T1> <= offset_ptr<T2>. Never throws.*/
template<class T1, class T2>
inline bool operator<= (const offset_ptr<T1> &pt1, 
                        const offset_ptr<T2> &pt2)
{  return pt1.get() <= pt2.get();  }

/*!offset_ptr<T1> > offset_ptr<T2>. Never throws.*/
template<class T1, class T2>
inline bool operator> (const offset_ptr<T1> &pt1, 
                       const offset_ptr<T2> &pt2)
{  return pt1.get() > pt2.get();  }

/*!offset_ptr<T1> >= offset_ptr<T2>. Never throws.*/
template<class T1, class T2>
inline bool operator>= (const offset_ptr<T1> &pt1, 
                        const offset_ptr<T2> &pt2)
{  return pt1.get() >= pt2.get();  }

/*!operator<< */
template<class E, class T, class Y> 
inline std::basic_ostream<E, T> & operator<< 
   (std::basic_ostream<E, T> & os, offset_ptr<Y> const & p)
{  return os << p.get();   }

/*!operator>> */
template<class E, class T, class Y> 
inline std::basic_istream<E, T> & operator>> 
   (std::basic_istream<E, T> & os, offset_ptr<Y> & p)
{  Y * tmp; return os >> tmp; p = tmp;   }

/*!std::ptrdiff_t + offset_ptr  */
template<class T>
inline offset_ptr<T> operator+(std::ptrdiff_t diff, const offset_ptr<T>& right)
{  return right + diff;  }

/*!offset_ptr - offset_ptr  */
template<class T, class T2>
inline std::ptrdiff_t operator- (const offset_ptr<T> &pt, const offset_ptr<T2> &pt2)
{  return pt.get()- pt2.get();   }

/*!swap specialization */
template<class T>
inline void swap (boost::interprocess::offset_ptr<T> &pt, 
                  boost::interprocess::offset_ptr<T> &pt2)
{  
   typename offset_ptr<T>::value_type *ptr = pt.get();
   pt = pt2;
   pt2 = ptr;
}

/*!get_pointer() enables boost::mem_fn to recognize offset_ptr. 
   Never throws.*/
template<class T>
inline T * get_pointer(boost::interprocess::offset_ptr<T> const & p)
{  return p.get();   }

/*!Simulation of static_cast between pointers. Never throws.*/
template<class T, class U> 
inline boost::interprocess::offset_ptr<T> 
   static_pointer_cast(boost::interprocess::offset_ptr<U> const & r)
{  
   return boost::interprocess::offset_ptr<T>
            (r, boost::interprocess::detail::static_cast_tag());  
}

/*!Simulation of const_cast between pointers. Never throws.*/
template<class T, class U> 
inline boost::interprocess::offset_ptr<T>
   const_pointer_cast(boost::interprocess::offset_ptr<U> const & r)
{  
   return boost::interprocess::offset_ptr<T>
            (r, boost::interprocess::detail::const_cast_tag());  
}

/*!Simulation of dynamic_cast between pointers. Never throws.*/
template<class T, class U> 
inline boost::interprocess::offset_ptr<T> 
   dynamic_pointer_cast(boost::interprocess::offset_ptr<U> const & r)
{  
   return boost::interprocess::offset_ptr<T>
            (r, boost::interprocess::detail::dynamic_cast_tag());  
}

/*!Simulation of reinterpret_cast between pointers. Never throws.*/
template<class T, class U> 
inline boost::interprocess::offset_ptr<T>
   reinterpret_pointer_cast(boost::interprocess::offset_ptr<U> const & r)
{  
   return boost::interprocess::offset_ptr<T>
            (r, boost::interprocess::detail::reinterpret_cast_tag());  
}

}  //namespace interprocess {

/*!has_trivial_constructor<> == true_type specialization for optimizations*/
template <class T>
struct has_trivial_constructor
   < boost::interprocess::offset_ptr<T> > 
   : public true_type
{};

/*!has_trivial_destructor<> == true_type specialization for optimizations*/
template <class T>
struct has_trivial_destructor
   < boost::interprocess::offset_ptr<T> > 
   : public true_type
{};

}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif //#ifndef BOOST_OFFSET_PTR_HPP


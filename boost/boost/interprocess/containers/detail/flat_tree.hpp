/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Hewlett-Packard Company makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 *
 * Copyright (c) 1996
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 */
///////////////////////////////////////////////////////////////////////////////
//
// Parts of this file come from SGI's stl_tree.h and stl_algo.h files. 
// Modified by Ion Gaztañaga 2005.
// Renaming, isolating and porting to generic algorithms. Pointer typedef 
// set to allocator::pointer to allow placing it in shared memory.
//
///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// The Loki Library
// Copyright (c) 2001 by Andrei Alexandrescu
// This code accompanies the book:
// Alexandrescu, Andrei. "Modern C++ Design: Generic Programming and Design 
//     Patterns Applied". Copyright (c) 2001. Addison-Wesley.
// Permission to use, copy, modify, distribute and sell this software for any 
//     purpose is hereby granted without fee, provided that the above copyright 
//     notice appear in all copies and that both that copyright notice and this 
//     permission notice appear in supporting documentation.
// The author or Addison-Welsey Longman make no representations about the 
//     suitability of this software for any purpose. It is provided "as is" 
//     without express or implied warranty.
///////////////////////////////////////////////////////////////////////////////
//
// Parts of this file come from AssocVector.h file from Loki library
//
////////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztañaga 2005-2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_FLAT_TREE_HPP
#define BOOST_INTERPROCESS_FLAT_TREE_HPP

#if (defined _MSC_VER) && (_MSC_VER >= 1200)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/detail/allocator_utilities.hpp>
#include <boost/iterator/reverse_iterator.hpp>
#include <algorithm>
#include <functional>
#include <utility>

namespace boost {

namespace interprocess {

namespace detail {

template <class Key, class Value, class KeyOfValue, 
          class Compare, class Alloc>
class flat_tree
{
   typedef boost::interprocess::vector<Value, Alloc>         vector_t;
   typedef typename vector_t::allocator_type          allocator_t;

 public:
   class value_compare
      : private Compare
   {
      typedef Value              first_argument_type;
      typedef Value              second_argument_type;
      typedef bool               return_type;
    public:     
      value_compare(const Compare &pred) 
         : Compare(pred)
      {}

      bool operator()(const Value& lhs, const Value& rhs) const
      { 
         KeyOfValue key_extract;
         return Compare::operator()(key_extract(lhs), key_extract(rhs)); 
      }

      const Compare &get_comp() const
         {  return *this;  }
      
      Compare &get_comp()
         {  return *this;  }
   };

 private:
   struct Data 
      //Inherit from value_compare to do EBO
      : public value_compare
   {
     public:
      Data(const Compare &comp,
           const vector_t &vect) 
         : value_compare(comp), m_vect(vect){}

      Data(const value_compare &comp,
           const vector_t &vect) 
         : value_compare(comp), m_vect(vect){}

      Data(const Compare &comp,
           const allocator_t &alloc) 
         : value_compare(comp), m_vect(alloc){}
     public:
      vector_t m_vect;
   };

   Data m_data;

 public:

   typedef typename vector_t::value_type              value_type;
   typedef typename vector_t::pointer                 pointer;
   typedef typename vector_t::const_pointer           const_pointer;
   typedef typename vector_t::reference               reference;
   typedef typename vector_t::const_reference         const_reference;
   typedef Key                                        key_type;
   typedef Compare                                    key_compare;
   typedef typename vector_t::allocator_type          allocator_type;
   typedef typename allocator_type::size_type         size_type;
   typedef typename allocator_type::difference_type   difference_type;
   typedef typename vector_t::iterator                iterator;
   typedef typename vector_t::const_iterator          const_iterator;
	typedef boost::reverse_iterator<iterator>          reverse_iterator;
	typedef boost::reverse_iterator<const_iterator>    const_reverse_iterator;
   

   // allocation/deallocation
   flat_tree(const Compare& comp     = Compare(), 
             const allocator_type& a = allocator_type())
      : m_data(comp, a)
   { }

   flat_tree(const flat_tree& x) 
      :  m_data(x.m_data, x.m_data.m_vect)
   { }

   ~flat_tree() { }

   flat_tree&  operator=(const flat_tree& x)
      {  flat_tree(x).swap(*this); return *this;  }

 public:    
   // accessors:
   Compare key_comp() const 
      { return this->m_data.get_comp(); }

   allocator_type get_allocator() const 
      { return this->m_data.m_vect.get_allocator(); }

   iterator begin() 
      { return this->m_data.m_vect.begin(); }

   const_iterator begin() const 
      { return this->m_data.m_vect.begin(); }

   iterator end() 
      { return this->m_data.m_vect.end(); }

   const_iterator end() const 
      { return this->m_data.m_vect.end(); }

   reverse_iterator rbegin() 
      { return reverse_iterator(this->end()); }

   const_reverse_iterator rbegin() const 
      {  return const_reverse_iterator(this->end());  }

   reverse_iterator rend() 
      { return reverse_iterator(this->begin()); }

   const_reverse_iterator rend() const 
      { return const_reverse_iterator(this->begin()); } 

   bool empty() const 
      { return this->m_data.m_vect.empty(); }

   size_type size() const 
      { return this->m_data.m_vect.size(); }

   size_type max_size() const 
      { return this->m_data.m_vect.max_size(); }

   void swap(flat_tree& other) 
   {
      vector_t & myvect    = this->m_data.m_vect;
      vector_t & othervect = other.m_data.m_vect;
      myvect.swap(othervect);
      value_compare& mycomp    = this->m_data;
      value_compare& othercomp = other.m_data;
      detail::do_swap(mycomp, othercomp);
   }
    
 public:
   // insert/erase
   std::pair<iterator,bool> insert_unique(const value_type& val)
   {  return this->priv_insert_unique(this->begin(), this->end(), val); }

   // insert/erase
   std::pair<iterator,bool> priv_insert_unique
      (iterator beg, iterator end, const value_type& val)
   {
      bool found = true;
      const value_compare &value_comp  = this->m_data;
      iterator i = this->priv_lower_bound(beg, end, KeyOfValue()(val));

      if (i == end || value_comp(val, *i)){
         i = this->m_data.m_vect.insert(i, val);
         found = false;
      }
      return std::make_pair(i, !found);
   }

   iterator insert_equal(const value_type& val)
   {
      iterator i = this->upper_bound(KeyOfValue()(val));
      i = this->m_data.m_vect.insert(i, val);
      return i;
   }

   iterator insert_unique(iterator pos, const value_type& val)
   {
/* old code
      const value_compare &value_comp = this->m_data;

      if (pos != this->end() && value_comp(*pos, val)){
         if(++pos == this->end() ||
               !value_comp(*pos, val)){
            if(value_comp(val, *pos))
               return this->m_data.m_vect.insert(pos, val);
            else
               return pos;
         }
      }
      return insert_unique(val).first;
*/
   /* N1780
      To insert val at pos:
      if pos == end || val <= *pos
         if pos == begin || val >= *(pos-1)
            insert val before pos
         else
            insert val before upper_bound(val)
      else if pos+1 == end || val <= *(pos+1)
         insert val after pos
      else
         insert val before lower_bound(val)
  */

      const value_compare &value_comp = this->m_data;

      if(pos == this->end() || value_comp(val, *pos)){
         if(pos != this->begin() && !value_comp(val, pos[-1])){
            if(value_comp(pos[-1], val)){
               return this->m_data.m_vect.insert(pos, val);
            }
            else{
               return pos;
            }
         }
         return this->priv_insert_unique(this->begin(), pos, val).first;
      }
      /* Works, but increases code complexity
      //Next check
      else if (value_comp(*pos, val) && !value_comp(pos[1], val)){
         if(value_comp(val, pos[1])){
            return this->m_data.m_vect.insert(pos+1, val);
         }
         else{
            return pos;
         }
      }*/
      else{
         //[... pos ... val ... ]
         //The hint is before the insertion position, so insert it
         //in the remaining range
         return this->priv_insert_unique(pos, this->end(), val).first;
      }
   }

   iterator insert_equal(iterator pos, const value_type& val)
   {
   /* N1780
      To insert val at pos:
      if pos == end || val <= *pos
         if pos == begin || val >= *(pos-1)
            insert val before pos
         else
            insert val before upper_bound(val)
      else if pos+1 == end || val <= *(pos+1)
         insert val after pos
      else
         insert val before lower_bound(val)
   */
      const value_compare &value_comp = this->m_data;

      if(pos == this->end() || !value_comp(*pos, val)){
         if (pos == this->begin() || !value_comp(val, pos[-1])){
            return this->m_data.m_vect.insert(pos, val);
         }
         else{
            return this->m_data.m_vect.insert
//               (this->upper_bound(KeyOfValue()(val)), val);
               (this->priv_upper_bound(this->begin(), pos, KeyOfValue()(val)), val);
         }
      }
      /*Works, but increases code complexity
      else if (++pos == this->end() || !value_comp(*pos, val)){
         return this->m_data.m_vect.insert(pos, val);
      }
      */
      else{
         return this->m_data.m_vect.insert
            //(this->lower_bound(KeyOfValue()(val)), val);
            (this->priv_lower_bound(pos, this->end(), KeyOfValue()(val)), val);
      }
   }

   template <class InIt>
   void insert_unique(InIt first, InIt last)
   {
      for ( ; first != last; ++first)
         this->insert_unique(*first);
   }

   template <class InIt>
   void insert_equal(InIt first, InIt last)
   {
      for ( ; first != last; ++first)
         this->insert_equal(*first);
   }

   iterator erase(const_iterator position)
      {  return this->m_data.m_vect.erase(position);  }

   size_type erase(const key_type& k)
   {
      std::pair<iterator,iterator > itp = this->equal_range(k);
      size_type ret = static_cast<size_type>(itp.second-itp.first);
      if (ret){
         this->erase(itp.first, itp.second);
      }
      
      return ret;
   }

   iterator erase(const_iterator first, const_iterator last)
      {  return this->m_data.m_vect.erase(first, last);  }

   void clear()
      {  this->m_data.m_vect.clear();  }      

   // set operations:
   iterator find(const key_type& k)
   {
      const Compare &key_comp = this->m_data.get_comp();
      iterator i = this->lower_bound(k);

      if (i != this->end() && key_comp(k, KeyOfValue()(*i))){  
         i = this->end();  
      }
      return i;
   }

   const_iterator find(const key_type& k) const
   {
      const Compare &key_comp = this->m_data.get_comp();
      const_iterator i = this->lower_bound(k);

      if (i != this->end() && key_comp(k, KeyOfValue()(*i))){  
         i = this->end();  
      }
      return i;
   }

   size_type count(const key_type& k) const
   {
      std::pair<const_iterator, const_iterator> p = this->equal_range(k);
      size_type n = p.second - p.first;
      return n;
   }

   iterator lower_bound(const key_type& k)
   {
      return this->priv_lower_bound(this->begin(), this->end(), k);
   }

   const_iterator lower_bound(const key_type& k) const
   {
      return this->priv_lower_bound(this->begin(), this->end(), k);
   }

   iterator upper_bound(const key_type& k)
   {
      return this->priv_upper_bound(this->begin(), this->end(), k);
   }

   const_iterator upper_bound(const key_type& k) const
   {
      return this->priv_upper_bound(this->begin(), this->end(), k);
   }

   std::pair<iterator,iterator> equal_range(const key_type& k)
   {  
      return this->priv_equal_range(this->begin(), this->end(), k);
   }

   std::pair<const_iterator, const_iterator> equal_range(const key_type& k) const
   {  
      return this->priv_equal_range(this->begin(), this->end(), k);
   }

   size_type capacity() const           
      { return this->m_data.m_vect.capacity(); }

   void reserve(size_type count)       
      { this->m_data.m_vect.reserve(count);   }

 private:

   template <class RanIt>
   RanIt priv_lower_bound(RanIt first, RanIt last,
                          const key_type & key) const
   {
      const Compare &key_comp = this->m_data.get_comp();
      KeyOfValue key_extract;
      difference_type len = last - first, half;
      RanIt middle;

      while (len > 0) {
         half = len >> 1;
         middle = first;
         middle += half;

         if (key_comp(key_extract(*middle), key)) {
            ++middle;
            first = middle;
            len = len - half - 1;
         }
         else
            len = half;
      }
      return first;
   }

   template <class RanIt>
   RanIt priv_upper_bound(RanIt first, RanIt last,
                          const key_type & key) const
   {
      const Compare &key_comp = this->m_data.get_comp();
      KeyOfValue key_extract;
      difference_type len = last - first, half;
      RanIt middle;

      while (len > 0) {
         half = len >> 1;
         middle = first;
         middle += half;

         if (key_comp(key, key_extract(*middle))) {
            len = half;
         }
         else{
            first = ++middle;
            len = len - half - 1;  
         }
      }
      return first;
   }

   template <class RanIt>
   std::pair<RanIt, RanIt>
      priv_equal_range(RanIt first, RanIt last, const key_type& key) const
   {
      const Compare &key_comp = this->m_data.get_comp();
      KeyOfValue key_extract;
      difference_type len = last - first, half;
      RanIt middle, left, right;

      while (len > 0) {
         half = len >> 1;
         middle = first;
         middle += half;

         if (key_comp(key_extract(*middle), key)){
            first = middle;
            ++first;
            len = len - half - 1;
         }
         else if (key_comp(key, key_extract(*middle))){
            len = half;
         }
         else {
            left = this->priv_lower_bound(first, middle, key);
            first += len;
            right = this->priv_upper_bound(++middle, first, key);
            return std::pair<RanIt, RanIt>(left, right);
         }
      }
      return std::pair<RanIt, RanIt>(first, first);
   }        

   template <class FwdIt>
   void priv_insert_unique(FwdIt first, FwdIt last, std::forward_iterator_tag)
   {
      size_type len = static_cast<size_type>(std::distance(first, last));
      this->reserve(this->size()+len);
      priv_insert_unique(first, last, std::input_iterator_tag());
   }

   template <class FwdIt>
   void priv_insert_equal(FwdIt first, FwdIt last, std::forward_iterator_tag)
   {
      size_type len = static_cast<size_type>(std::distance(first, last));
      this->reserve(this->size()+len);
      this->priv_insert_equal(first, last, std::input_iterator_tag());
   }

   template <class InIt>
   void priv_insert_unique(InIt first, InIt last, std::input_iterator_tag)
   {
      for ( ; first != last; ++first)
         this->insert_unique(*first);
   }

   template <class InIt>
   void priv_insert_equal(InIt first, InIt last, std::input_iterator_tag)
   {
      for ( ; first != last; ++first)
         this->insert_equal(*first);
   }
};

template <class Key, class Value, class KeyOfValue, 
          class Compare, class Alloc>
inline bool 
operator==(const flat_tree<Key,Value,KeyOfValue,Compare,Alloc>& x, 
           const flat_tree<Key,Value,KeyOfValue,Compare,Alloc>& y)
{
  return x.size() == y.size() &&
         std::equal(x.begin(), x.end(), y.begin());
}

template <class Key, class Value, class KeyOfValue, 
          class Compare, class Alloc>
inline bool 
operator<(const flat_tree<Key,Value,KeyOfValue,Compare,Alloc>& x, 
          const flat_tree<Key,Value,KeyOfValue,Compare,Alloc>& y)
{
  return std::lexicographical_compare(x.begin(), x.end(), 
                                      y.begin(), y.end());
}

template <class Key, class Value, class KeyOfValue, 
          class Compare, class Alloc>
inline bool 
operator!=(const flat_tree<Key,Value,KeyOfValue,Compare,Alloc>& x, 
           const flat_tree<Key,Value,KeyOfValue,Compare,Alloc>& y) 
   {  return !(x == y); }

template <class Key, class Value, class KeyOfValue, 
          class Compare, class Alloc>
inline bool 
operator>(const flat_tree<Key,Value,KeyOfValue,Compare,Alloc>& x, 
          const flat_tree<Key,Value,KeyOfValue,Compare,Alloc>& y) 
   {  return y < x;  }

template <class Key, class Value, class KeyOfValue, 
          class Compare, class Alloc>
inline bool 
operator<=(const flat_tree<Key,Value,KeyOfValue,Compare,Alloc>& x, 
           const flat_tree<Key,Value,KeyOfValue,Compare,Alloc>& y) 
   {  return !(y < x);  }

template <class Key, class Value, class KeyOfValue, 
          class Compare, class Alloc>
inline bool 
operator>=(const flat_tree<Key,Value,KeyOfValue,Compare,Alloc>& x, 
           const flat_tree<Key,Value,KeyOfValue,Compare,Alloc>& y) 
   {  return !(x < y);  }


template <class Key, class Value, class KeyOfValue, 
          class Compare, class Alloc>
inline void 
swap(flat_tree<Key,Value,KeyOfValue,Compare,Alloc>& x, 
     flat_tree<Key,Value,KeyOfValue,Compare,Alloc>& y)
   {  x.swap(y);  }

}  //namespace detail {

}  //namespace interprocess {

}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif // BOOST_INTERPROCESS_FLAT_TREE_HPP

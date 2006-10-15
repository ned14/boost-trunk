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
//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gazta�aga 2005-2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
//
// This file comes from SGI's stl_map/stl_multimap files. 
// Modified by Ion Gazta�aga 2005.
// Renaming, isolating and porting to generic algorithms. Pointer typedef 
// set to allocator::pointer to allow placing it in shared memory.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_FLAT_MAP_HPP
#define BOOST_INTERPROCESS_FLAT_MAP_HPP

#if (defined _MSC_VER) && (_MSC_VER >= 1200)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/interprocess_fwd.hpp>
#include <utility>
#include <functional>
#include <memory>
#include <boost/detail/allocator_utilities.hpp>
#include <boost/interprocess/containers/detail/flat_tree.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/interprocess/detail/move.hpp>

namespace boost { namespace interprocess {

// Forward declarations of operators == and <, needed for friend declarations.
template <class Key, class T, class Pred, class Alloc>
class flat_map;

template <class Key, class T, class Pred, class Alloc>
inline bool operator==(const flat_map<Key,T,Pred,Alloc>& x, 
                       const flat_map<Key,T,Pred,Alloc>& y);

template <class Key, class T, class Pred, class Alloc>
inline bool operator<(const flat_map<Key,T,Pred,Alloc>& x, 
                      const flat_map<Key,T,Pred,Alloc>& y);

template <class Key, class T, class Pred, class Alloc>
class flat_map 
{
 private:
   //This is the real tree stored here. It's based on a movable pair
   typedef detail::flat_tree<Key, 
                           detail::pair<Key, T>, 
                           detail::select1st< detail::pair<Key, T> >, 
                           Pred, 
                           typename boost::detail::allocator::
                              rebind_to<Alloc, detail::pair<Key, T> >::type> impl_tree_t;

   //This is the tree that we should store if pair was movable
   typedef detail::flat_tree<Key, 
                           std::pair<Key, T>, 
                           detail::select1st< std::pair<Key, T> >, 
                           Pred, 
                           Alloc> tree_t;

//   tree_t m_flat_tree;  // flat tree representing flat_map
   impl_tree_t m_flat_tree;  // flat tree representing flat_map

   typedef typename impl_tree_t::value_type             impl_value_type;
   typedef typename impl_tree_t::pointer                impl_pointer;
   typedef typename impl_tree_t::const_pointer          impl_const_pointer;
   typedef typename impl_tree_t::reference              impl_reference;
   typedef typename impl_tree_t::const_reference        impl_const_reference;
   typedef typename impl_tree_t::value_compare          impl_value_compare;
   typedef typename impl_tree_t::iterator               impl_iterator;
   typedef typename impl_tree_t::const_iterator         impl_const_iterator;
   typedef typename impl_tree_t::reverse_iterator       impl_reverse_iterator;
   typedef typename impl_tree_t::const_reverse_iterator impl_const_reverse_iterator;
   typedef typename impl_tree_t::allocator_type         impl_allocator_type;
   typedef detail::moved_object<impl_value_type>        impl_moved_value_type;
/*
   template<class D, class S>
   static D &force(S &s)
   {  return *(reinterpret_cast<D*>(&s)); }
*/
   template<class D, class S>
   static D &force(const S &s)
   {  return *const_cast<D*>((reinterpret_cast<const D*>(&s))); }
 public:
   // typedefs:
   typedef typename tree_t::key_type               key_type;
   typedef typename tree_t::value_type             value_type;
   typedef typename tree_t::pointer                pointer;
   typedef typename tree_t::const_pointer          const_pointer;
   typedef typename tree_t::reference              reference;
   typedef typename tree_t::const_reference        const_reference;
   typedef typename tree_t::value_compare          value_compare;
   typedef T                                       mapped_type;
   typedef typename tree_t::key_compare            key_compare;
   typedef typename tree_t::iterator               iterator;
   typedef typename tree_t::const_iterator         const_iterator;
   typedef typename tree_t::reverse_iterator       reverse_iterator;
   typedef typename tree_t::const_reverse_iterator const_reverse_iterator;
   typedef typename tree_t::size_type              size_type;
   typedef typename tree_t::difference_type        difference_type;
   typedef typename tree_t::allocator_type         allocator_type;

   // allocation/deallocation

   explicit flat_map(const Pred& comp = Pred(), const allocator_type& a = allocator_type()) 
      : m_flat_tree(comp, force<impl_allocator_type>(a)) {}

   template <class InputIterator>
   flat_map(InputIterator first, InputIterator last)
      : m_flat_tree(Pred(), force<impl_allocator_type>(allocator_type()))
      { m_flat_tree.insert_unique(first, last); }

   template <class InputIterator>
   flat_map(InputIterator first, InputIterator last, const Pred& comp = Pred(),
         const allocator_type& a = allocator_type())
      : m_flat_tree(comp, force<impl_allocator_type>(a)) 
      { m_flat_tree.insert_unique(first, last); }

   flat_map(const flat_map<Key,T,Pred,Alloc>& x) 
      : m_flat_tree(x.m_flat_tree) {}

   flat_map(const detail::moved_object<flat_map<Key,T,Pred,Alloc> >& x) 
      : m_flat_tree(move(x.get().m_flat_tree)) {}

   flat_map<Key,T,Pred,Alloc>& operator=(const flat_map<Key, T, Pred, Alloc>& x)
      {  m_flat_tree = x.m_flat_tree;   return *this;  }

   flat_map<Key,T,Pred,Alloc>& operator=(const detail::moved_object<flat_map<Key, T, Pred, Alloc> >& x)
      {  m_flat_tree.swap(x.get().m_flat_tree);   return *this;  }

   // accessors:

   key_compare key_comp() const 
      { return force<key_compare>(m_flat_tree.key_comp()); }

   value_compare value_comp() const 
      { return value_compare(force<key_compare>(m_flat_tree.key_comp())); }

   allocator_type get_allocator() const 
      { return force<allocator_type>(m_flat_tree.get_allocator()); }

   iterator begin() 
      { return force<iterator>(m_flat_tree.begin()); }

   const_iterator begin() const 
      { return force<const_iterator>(m_flat_tree.begin()); }

   iterator end() 
      { return force<iterator>(m_flat_tree.end()); }

   const_iterator end() const 
      { return force<const_iterator>(m_flat_tree.end()); }

   reverse_iterator rbegin() 
      { return force<reverse_iterator>(m_flat_tree.rbegin()); }

   const_reverse_iterator rbegin() const 
      { return force<const_reverse_iterator>(m_flat_tree.rbegin()); }

   reverse_iterator rend() 
      { return force<reverse_iterator>(m_flat_tree.rend()); }

   const_reverse_iterator rend() const 
      { return force<const_reverse_iterator>(m_flat_tree.rend()); }

   bool empty() const 
      { return m_flat_tree.empty(); }

   size_type size() const 
      { return m_flat_tree.size(); }

   size_type max_size() const 
      { return m_flat_tree.max_size(); }

   T &operator[](const key_type& k) 
   {
      iterator i = lower_bound(k);
      // i->first is greater than or equivalent to k.
      if (i == end() || key_comp()(k, (*i).first))
         i = insert(i, value_type(k, T()));
      return (*i).second;
   }

   T &operator[](const detail::moved_object<key_type>& mk) 
   {
      key_type &k = mk.get();
      iterator i = lower_bound(k);
      // i->first is greater than or equivalent to k.
      if (i == end() || key_comp()(k, (*i).first))
         i = insert(i, value_type(k, move(T())));
      return (*i).second;
   }

   void swap(flat_map<Key,T,Pred,Alloc>& x) 
      { m_flat_tree.swap(x.m_flat_tree); }

   void swap(const detail::moved_object<flat_map<Key,T,Pred,Alloc> >& x) 
      { m_flat_tree.swap(x.get().m_flat_tree); }

   // insert/erase

   std::pair<iterator,bool> insert(const value_type& x) 
      { return force<std::pair<iterator,bool> >(
         m_flat_tree.insert_unique(force<impl_value_type>(x))); }

   std::pair<iterator,bool> insert(const detail::moved_object<value_type>& x) 
      { return force<std::pair<iterator,bool> >(
         m_flat_tree.insert_unique(force<impl_moved_value_type>(x))); }

   iterator insert(iterator position, const value_type& x)
      { return force<iterator>(
         m_flat_tree.insert_unique(force<impl_iterator>(position), force<impl_value_type>(x))); }

   iterator insert(iterator position, const detail::moved_object<value_type>& x)
      { return force<iterator>(
         m_flat_tree.insert_unique(force<impl_iterator>(position), force<impl_moved_value_type>(x))); }

   template <class InputIterator>
   void insert(InputIterator first, InputIterator last) 
      {  m_flat_tree.insert_unique(first, last);  }

   void erase(const_iterator position) 
      { m_flat_tree.erase(force<impl_const_iterator>(position)); }

   size_type erase(const key_type& x) 
      { return m_flat_tree.erase(x); }

   void erase(const_iterator first, const_iterator last)
      { m_flat_tree.erase(force<impl_const_iterator>(first), force<impl_const_iterator>(last)); }

   void clear() 
      { m_flat_tree.clear(); }

   // flat_map operations:

   iterator find(const key_type& x) 
      { return force<iterator>(m_flat_tree.find(x)); }

   const_iterator find(const key_type& x) const 
      { return force<const_iterator>(m_flat_tree.find(x)); }

   size_type count(const key_type& x) const 
      {  return m_flat_tree.find(x) == m_flat_tree.end() ? 0 : 1;  }

   iterator lower_bound(const key_type& x) 
      {  return force<iterator>(m_flat_tree.lower_bound(x)); }

   const_iterator lower_bound(const key_type& x) const 
      {  return force<const_iterator>(m_flat_tree.lower_bound(x)); }

   iterator upper_bound(const key_type& x) 
      {  return force<iterator>(m_flat_tree.upper_bound(x)); }

   const_iterator upper_bound(const key_type& x) const 
      {  return force<const_iterator>(m_flat_tree.upper_bound(x)); }
     
   std::pair<iterator,iterator> equal_range(const key_type& x) 
      {  return force<std::pair<iterator,iterator> >(m_flat_tree.equal_range(x)); }

   std::pair<const_iterator,const_iterator> equal_range(const key_type& x) const 
      {  return force<std::pair<const_iterator,const_iterator> >(m_flat_tree.equal_range(x)); }

   size_type capacity() const           
      { return m_flat_tree.capacity(); }

   void reserve(size_type count)       
      { m_flat_tree.reserve(count);   }

   template <class K1, class T1, class C1, class A1>
   friend bool operator== (const flat_map<K1, T1, C1, A1>&,
                           const flat_map<K1, T1, C1, A1>&);
   template <class K1, class T1, class C1, class A1>
   friend bool operator< (const flat_map<K1, T1, C1, A1>&,
                           const flat_map<K1, T1, C1, A1>&);
};

template <class Key, class T, class Pred, class Alloc>
inline bool operator==(const flat_map<Key,T,Pred,Alloc>& x, 
                       const flat_map<Key,T,Pred,Alloc>& y) 
   {  return x.m_flat_tree == y.m_flat_tree;  }

template <class Key, class T, class Pred, class Alloc>
inline bool operator<(const flat_map<Key,T,Pred,Alloc>& x, 
                      const flat_map<Key,T,Pred,Alloc>& y) 
   {  return x.m_flat_tree < y.m_flat_tree;   }

template <class Key, class T, class Pred, class Alloc>
inline bool operator!=(const flat_map<Key,T,Pred,Alloc>& x, 
                       const flat_map<Key,T,Pred,Alloc>& y) 
   {  return !(x == y); }

template <class Key, class T, class Pred, class Alloc>
inline bool operator>(const flat_map<Key,T,Pred,Alloc>& x, 
                      const flat_map<Key,T,Pred,Alloc>& y) 
   {  return y < x;  }

template <class Key, class T, class Pred, class Alloc>
inline bool operator<=(const flat_map<Key,T,Pred,Alloc>& x, 
                       const flat_map<Key,T,Pred,Alloc>& y) 
   {  return !(y < x);  }

template <class Key, class T, class Pred, class Alloc>
inline bool operator>=(const flat_map<Key,T,Pred,Alloc>& x, 
                       const flat_map<Key,T,Pred,Alloc>& y) 
   {  return !(x < y);  }

template <class Key, class T, class Pred, class Alloc>
inline void swap(flat_map<Key,T,Pred,Alloc>& x, 
                 flat_map<Key,T,Pred,Alloc>& y) 
   {  x.swap(y);  }

template <class Key, class T, class Pred, class Alloc>
inline void swap(const detail::moved_object<flat_map<Key,T,Pred,Alloc> >& x, 
                 flat_map<Key,T,Pred,Alloc>& y) 
   {  x.get().swap(y);  }

template <class Key, class T, class Pred, class Alloc>
inline void swap(flat_map<Key,T,Pred,Alloc>& x, 
                 const detail::moved_object<flat_map<Key,T,Pred,Alloc> >& y) 
   {  x.swap(y.get());  }

/*!This class is movable*/
template <class T, class P, class A>
struct is_movable<flat_map<T, P, A> >
{
   enum {   value = true };
};

// Forward declaration of operators < and ==, needed for friend declaration.

template <class Key, class T, 
          class Pred,
          class Alloc>
class flat_multimap;

template <class Key, class T, class Pred, class Alloc>
inline bool operator==(const flat_multimap<Key,T,Pred,Alloc>& x, 
                       const flat_multimap<Key,T,Pred,Alloc>& y);

template <class Key, class T, class Pred, class Alloc>
inline bool operator<(const flat_multimap<Key,T,Pred,Alloc>& x, 
                      const flat_multimap<Key,T,Pred,Alloc>& y);

template <class Key, class T, class Pred, class Alloc>
class flat_multimap 
{
 private:
   //This is the real tree stored here. It's based on a movable pair
   typedef detail::flat_tree<Key, 
                           detail::pair<Key, T>, 
                           detail::select1st< detail::pair<Key, T> >, 
                           Pred, 
                           typename boost::detail::allocator::
                              rebind_to<Alloc, detail::pair<Key, T> >::type> impl_tree_t;

   typedef detail::flat_tree<Key, 
                           std::pair<Key, T>, 
                           detail::select1st< std::pair<Key, T> >, 
                           Pred, 
                           Alloc> tree_t;
//   tree_t m_flat_tree;  // flat tree representing flat_multimap
   impl_tree_t m_flat_tree;  // flat tree representing flat_map

   typedef typename impl_tree_t::value_type             impl_value_type;
   typedef typename impl_tree_t::pointer                impl_pointer;
   typedef typename impl_tree_t::const_pointer          impl_const_pointer;
   typedef typename impl_tree_t::reference              impl_reference;
   typedef typename impl_tree_t::const_reference        impl_const_reference;
   typedef typename impl_tree_t::value_compare          impl_value_compare;
   typedef typename impl_tree_t::iterator               impl_iterator;
   typedef typename impl_tree_t::const_iterator         impl_const_iterator;
   typedef typename impl_tree_t::reverse_iterator       impl_reverse_iterator;
   typedef typename impl_tree_t::const_reverse_iterator impl_const_reverse_iterator;
   typedef typename impl_tree_t::allocator_type         impl_allocator_type;
   typedef detail::moved_object<impl_value_type>        impl_moved_value_type;
/*
   template<class D, class S>
   static D &force(S &s)
   {  return *(reinterpret_cast<D*>(&s)); }
*/
   template<class D, class S>
   static D &force(const S &s)
   {  return *const_cast<D*>((reinterpret_cast<const D*>(&s))); }

 public:
   // typedefs:
   typedef typename tree_t::key_type               key_type;
   typedef typename tree_t::value_type             value_type;
   typedef typename tree_t::pointer                pointer;
   typedef typename tree_t::const_pointer          const_pointer;
   typedef typename tree_t::reference              reference;
   typedef typename tree_t::const_reference        const_reference;
   typedef typename tree_t::value_compare          value_compare;
   typedef T                                       mapped_type;
   typedef typename tree_t::key_compare            key_compare;
   typedef typename tree_t::iterator               iterator;
   typedef typename tree_t::const_iterator         const_iterator;
   typedef typename tree_t::reverse_iterator       reverse_iterator;
   typedef typename tree_t::const_reverse_iterator const_reverse_iterator;
   typedef typename tree_t::size_type              size_type;
   typedef typename tree_t::difference_type        difference_type;
   typedef typename tree_t::allocator_type         allocator_type;

   // allocation/deallocation
   explicit flat_multimap(const Pred& comp = Pred(),
                          const allocator_type& a = allocator_type())
      : m_flat_tree(comp, force<impl_allocator_type>(a)) { }

   template <class InputIterator>
   flat_multimap(InputIterator first, InputIterator last,
            const Pred& comp        = Pred(),
            const allocator_type& a = allocator_type())
      : m_flat_tree(comp, force<impl_allocator_type>(a)) 
      { m_flat_tree.insert_equal(first, last); }

   flat_multimap(const flat_multimap<Key,T,Pred,Alloc>& x) 
      : m_flat_tree(x.m_flat_tree) { }

   flat_multimap(const detail::moved_object<flat_multimap<Key,T,Pred,Alloc> >& x) 
      : m_flat_tree(move(x.get().m_flat_tree)) { }

   flat_multimap<Key,T,Pred,Alloc>&
   operator=(const flat_multimap<Key,T,Pred,Alloc>& x) 
      {  m_flat_tree = x.m_flat_tree;   return *this;  }

   flat_multimap<Key,T,Pred,Alloc>&
   operator=(const detail::moved_object<flat_multimap<Key,T,Pred,Alloc> >& x) 
      {  m_flat_tree.swap(x.get().m_flat_tree);   return *this;  }
   // accessors:

   key_compare key_comp() const 
      { return force<key_compare>(m_flat_tree.key_comp()); }

   value_compare value_comp() const 
      { return value_compare(force<key_compare>(m_flat_tree.key_comp())); }

   allocator_type get_allocator() const 
      { return force<allocator_type>(m_flat_tree.get_allocator()); }

   iterator begin() 
      { return force<iterator>(m_flat_tree.begin()); }

   const_iterator begin() const 
      { return force<const_iterator>(m_flat_tree.begin()); }

   iterator end() 
      { return force<iterator>(m_flat_tree.end()); }

   const_iterator end() const 
      { return force<const_iterator>(m_flat_tree.end()); }

   reverse_iterator rbegin() 
      { return force<reverse_iterator>(m_flat_tree.rbegin()); }

   const_reverse_iterator rbegin() const 
      { return force<const_reverse_iterator>(m_flat_tree.rbegin()); }

   reverse_iterator rend() 
      { return force<reverse_iterator>(m_flat_tree.rend()); }

   const_reverse_iterator rend() const 
      { return force<const_reverse_iterator>(m_flat_tree.rend()); }

   bool empty() const 
      { return m_flat_tree.empty(); }

   size_type size() const 
      { return m_flat_tree.size(); }

   size_type max_size() const 
      { return m_flat_tree.max_size(); }

   void swap(flat_multimap<Key,T,Pred,Alloc>& x) 
      { m_flat_tree.swap(x.m_flat_tree); }

   void swap(const detail::moved_object<flat_multimap<Key,T,Pred,Alloc> >& x) 
      { m_flat_tree.swap(x.get().m_flat_tree); }

   // insert/erase
   iterator insert(const value_type& x) 
      { return force<iterator>(m_flat_tree.insert_equal(force<impl_value_type>(x))); }

   iterator insert(const detail::moved_object<value_type>& x) 
      { return force<iterator>(m_flat_tree.insert_equal(force<impl_moved_value_type>(x))); }

   iterator insert(iterator position, const value_type& x) 
      { return force<iterator>(m_flat_tree.insert_equal(force<impl_iterator>(position), force<impl_value_type>(x))); }

   iterator insert(iterator position, const detail::moved_object<value_type>& x) 
      { return force<iterator>(m_flat_tree.insert_equal(force<impl_iterator>(position), force<impl_moved_value_type>(x))); }

   template <class InputIterator>
   void insert(InputIterator first, InputIterator last) 
      {  m_flat_tree.insert_equal(first, last); }

   void erase(const_iterator position) 
      { m_flat_tree.erase(force<impl_const_iterator>(position)); }

   size_type erase(const key_type& x) 
      { return m_flat_tree.erase(x); }

   void erase(const_iterator first, const_iterator last)
      { m_flat_tree.erase(force<impl_const_iterator>(first), force<impl_const_iterator>(last)); }

   void clear() 
      { m_flat_tree.clear(); }

   // flat_multimap operations:

   iterator find(const key_type& x)
      { return force<iterator>(m_flat_tree.find(x)); }

   const_iterator find(const key_type& x) const 
      { return force<const_iterator>(m_flat_tree.find(x)); }

   size_type count(const key_type& x) const 
      { return m_flat_tree.count(x); }

   iterator lower_bound(const key_type& x) 
      {return force<iterator>(m_flat_tree.lower_bound(x)); }

   const_iterator lower_bound(const key_type& x) const 
      {  return force<const_iterator>(m_flat_tree.lower_bound(x));  }

   iterator upper_bound(const key_type& x) 
      {return force<iterator>(m_flat_tree.upper_bound(x)); }

   const_iterator upper_bound(const key_type& x) const 
      {  return force<const_iterator>(m_flat_tree.upper_bound(x)); }

   std::pair<iterator,iterator> equal_range(const key_type& x) 
      {  return force<std::pair<iterator,iterator> >(m_flat_tree.equal_range(x));   }

   std::pair<const_iterator,const_iterator> 
      equal_range(const key_type& x) const 
      {  return force<std::pair<const_iterator,const_iterator> >(m_flat_tree.equal_range(x));   }

   size_type capacity() const           
      { return m_flat_tree.capacity(); }

   void reserve(size_type count)       
      { m_flat_tree.reserve(count);   }

   template <class K1, class T1, class C1, class A1>
   friend bool operator== (const flat_multimap<K1, T1, C1, A1>& x,
                           const flat_multimap<K1, T1, C1, A1>& y);

   template <class K1, class T1, class C1, class A1>
   friend bool operator< (const flat_multimap<K1, T1, C1, A1>& x,
                          const flat_multimap<K1, T1, C1, A1>& y);
};

template <class Key, class T, class Pred, class Alloc>
inline bool operator==(const flat_multimap<Key,T,Pred,Alloc>& x, 
                       const flat_multimap<Key,T,Pred,Alloc>& y) 
   {  return x.m_flat_tree == y.m_flat_tree;  }

template <class Key, class T, class Pred, class Alloc>
inline bool operator<(const flat_multimap<Key,T,Pred,Alloc>& x, 
                      const flat_multimap<Key,T,Pred,Alloc>& y) 
   {  return x.m_flat_tree < y.m_flat_tree;   }

template <class Key, class T, class Pred, class Alloc>
inline bool operator!=(const flat_multimap<Key,T,Pred,Alloc>& x, 
                       const flat_multimap<Key,T,Pred,Alloc>& y) 
   {  return !(x == y);  }

template <class Key, class T, class Pred, class Alloc>
inline bool operator>(const flat_multimap<Key,T,Pred,Alloc>& x, 
                      const flat_multimap<Key,T,Pred,Alloc>& y) 
   {  return y < x;  }

template <class Key, class T, class Pred, class Alloc>
inline bool operator<=(const flat_multimap<Key,T,Pred,Alloc>& x, 
                       const flat_multimap<Key,T,Pred,Alloc>& y) 
   {  return !(y < x);  }

template <class Key, class T, class Pred, class Alloc>
inline bool operator>=(const flat_multimap<Key,T,Pred,Alloc>& x, 
                       const flat_multimap<Key,T,Pred,Alloc>& y) 
   {  return !(x < y);  }

template <class Key, class T, class Pred, class Alloc>
inline void swap(flat_multimap<Key,T,Pred,Alloc>& x, 
                 flat_multimap<Key,T,Pred,Alloc>& y) 
   {  x.swap(y);  }

template <class Key, class T, class Pred, class Alloc>
inline void swap(const detail::moved_object<flat_multimap<Key,T,Pred,Alloc> >& x, 
                 flat_multimap<Key,T,Pred,Alloc>& y) 
   {  x.get().swap(y);  }


template <class Key, class T, class Pred, class Alloc>
inline void swap(flat_multimap<Key,T,Pred,Alloc>& x, 
                 const detail::moved_object<flat_multimap<Key,T,Pred,Alloc> > & y) 
   {  x.swap(y.get());  }

/*!This class is movable*/
template <class T, class P, class A>
struct is_movable<flat_multimap<T, P, A> >
{
   enum {   value = true };
};

}} //namespace boost { namespace interprocess {

#include <boost/interprocess/detail/config_end.hpp>

#endif /* BOOST_INTERPROCESS_FLAT_MAP_HPP */


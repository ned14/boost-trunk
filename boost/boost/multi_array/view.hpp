// Copyright (C) 2002 Ronald Garcia
//
// Permission to copy, use, sell and distribute this software is granted
// provided this copyright notice appears in all copies. 
// Permission to modify the code and to distribute modified code is granted
// provided this copyright notice appears in all copies, and a notice 
// that the code was modified is included with the copyright notice.
//
// This software is provided "as is" without express or implied warranty, 
// and with no claim as to its suitability for any purpose.
//

#ifndef BOOST_MULTI_ARRAY_VIEW_RG071301_HPP
#define BOOST_MULTI_ARRAY_VIEW_RG071301_HPP

//
// view.hpp - code for creating "views" of array data.
//

#include "boost/multi_array/base.hpp"
#include "boost/multi_array/concept_checks.hpp"
#include "boost/multi_array/iterator.hpp"
#include "boost/multi_array/storage_order.hpp"
#include "boost/multi_array/subarray.hpp"
#include "boost/multi_array/algorithm.hpp"
#include "boost/array.hpp"
#include "boost/limits.hpp"
#include <algorithm>
#include <cstddef>
#include <functional>
#include <numeric>

namespace boost {
namespace detail {
namespace multi_array {

// TPtr = const T* defaulted in base.hpp
template <typename T, std::size_t NumDims, typename TPtr>
class const_multi_array_view :
    public boost::detail::multi_array::multi_array_impl_base<T,NumDims>
{
  typedef boost::detail::multi_array::multi_array_impl_base<T,NumDims> super_type;
public: 
  typedef typename super_type::value_type value_type;
  typedef typename super_type::const_reference const_reference;
  typedef typename super_type::const_iterator const_iterator;
  typedef typename super_type::const_iter_base const_iter_base;
  typedef typename super_type::const_reverse_iterator const_reverse_iterator;
  typedef typename super_type::element element;
  typedef typename super_type::size_type size_type;
  typedef typename super_type::difference_type difference_type;
  typedef typename super_type::index index;
  typedef typename super_type::extent_range extent_range;

  // template typedefs
  template <std::size_t NDims>
  struct const_array_view {
    typedef boost::detail::multi_array::const_multi_array_view<T,NDims> type;
  };

  template <std::size_t NDims>
  struct array_view {
    typedef boost::detail::multi_array::multi_array_view<T,NDims> type;
  };

  template <typename OPtr>
  const_multi_array_view(const 
			 const_multi_array_view<T,NumDims,OPtr>& other) :
    base_(other.base_), origin_offset_(other.origin_offset_),
    num_elements_(other.num_elements_), extent_list_(other.extent_list_),
    stride_list_(other.stride_list_), index_base_list_(other.index_base_list_)
  { }


  template <class BaseList>
  void reindex(const BaseList& values) {
    boost::copy_n(values.begin(),num_dimensions(),index_base_list_.begin());
    origin_offset_ =
      calculate_indexing_offset(stride_list_,index_base_list_);
  }

  void reindex(index value) {
    index_base_list_.assign(value);
    origin_offset_ =
      calculate_indexing_offset(stride_list_,index_base_list_);
  }

  size_type num_dimensions() const { return NumDims; }

  size_type size() const { return extent_list_.front(); }
  size_type max_size() const { return num_elements(); }
  bool empty() const { return size() == 0; }

  const size_type* shape() const {
    return extent_list_.data();
  }

  const index* strides() const {
    return stride_list_.data();
  }

  const T* origin() const { return base_+origin_offset_; }

  size_type num_elements() const { return num_elements_; }

  const index* index_bases() const {
    return index_base_list_.data();
  }

  template <typename IndexList>
  const element& operator()(IndexList indices) const {
    return super_type::access_element(boost::type<const element&>(),
				      origin(),
				      indices,strides());
  }

  // Only allow const element access
  const_reference operator[](index idx) const {
    return super_type::access(boost::type<const_reference>(),
			      idx,origin(),
			      shape(),strides(),
			      index_bases());
  }

  // see generate_array_view in base.hpp
#if !defined(BOOST_MSVC) || BOOST_MSVC > 1300
  template <int NDims>
#else
  template <int NumDims, int NDims> // else ICE
#endif // BOOST_MSVC
  typename const_array_view<NDims>::type 
  operator[](const boost::detail::multi_array::
	     index_gen<NumDims,NDims>& indices)
    const {
    typedef const_array_view<NDims>::type return_type;
    return
      super_type::generate_array_view(boost::type<return_type>(),
				      indices,
				      shape(),
				      strides(),
				      index_bases(),
				      origin());
  }
  const_iterator begin() const {
    return const_iterator(const_iter_base(*index_bases(),origin(),
				   shape(),strides(),index_bases()));
  }

  const_iterator end() const {
    return const_iterator(const_iter_base(*index_bases()+*shape(),origin(),
				   shape(),strides(),index_bases()));
  }
  
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }

  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }


  template <typename OPtr>
  bool operator==(const
		  const_multi_array_view<T,NumDims,OPtr>& rhs)
    const {
    if(std::equal(extent_list_.begin(),
		  extent_list_.end(),
		  rhs.extent_list_.begin()))
      return std::equal(begin(),end(),rhs.begin());
    else return false;
  }

  template <typename OPtr>
  bool operator<(const
		 const_multi_array_view<T,NumDims,OPtr>& rhs)
    const {
    return std::lexicographical_compare(begin(),end(),rhs.begin(),rhs.end());
  }

  template <typename OPtr>
  bool operator!=(const
		  const_multi_array_view<T,NumDims,OPtr>& rhs)
    const {
    return !(*this == rhs);
  }

  template <typename OPtr>
  bool operator>(const
		 const_multi_array_view<T,NumDims,OPtr>& rhs)
    const {
    return rhs < *this;
  }

  template <typename OPtr>
  bool operator<=(const
		 const_multi_array_view<T,NumDims,OPtr>& rhs)
    const {
    return !(*this > rhs);
  }

  template <typename OPtr>
  bool operator>=(const
		 const_multi_array_view<T,NumDims,OPtr>& rhs)
    const {
    return !(*this < rhs);
  }


#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
protected:
  template <typename,std::size_t> friend class multi_array_impl_base;
  template <typename,std::size_t,typename> friend class const_multi_array_view;
#else
public: // should be protected
#endif

  // This constructor is used by multi_array_impl_base::generate_array_view
  // to create strides  
  template <typename ExtentList, typename Index>
  explicit const_multi_array_view(TPtr base,
			   const ExtentList& extents,
			   const boost::array<Index,NumDims>& strides): 
    base_(base), origin_offset_(0) {

    index_base_list_.assign(0);

    // Get the extents and strides
    boost::copy_n(extents.begin(),NumDims,extent_list_.begin());
    boost::copy_n(strides.begin(),NumDims,stride_list_.begin());

    // Calculate the array size
    num_elements_ = std::accumulate(extent_list_.begin(),extent_list_.end(),
			    size_type(1),std::multiplies<size_type>());
    assert(num_elements_ != 0);
  }

  typedef boost::array<size_type,NumDims> size_list;
  typedef boost::array<index,NumDims> index_list;

  TPtr base_;
  index origin_offset_;
  size_type num_elements_;
  size_list extent_list_;
  index_list stride_list_;
  index_list index_base_list_;

private:
  // const_multi_array_view cannot be assigned to (no deep copies!)
  const_multi_array_view& operator=(const const_multi_array_view& other);
};


template <typename T, std::size_t NumDims>
class multi_array_view :
  public const_multi_array_view<T,NumDims,T*>
{
  typedef const_multi_array_view<T,NumDims,T*> super_type;
public: 
  typedef typename super_type::value_type value_type;
  typedef typename super_type::reference reference;
  typedef typename super_type::iterator iterator;
  typedef typename super_type::iter_base iter_base;
  typedef typename super_type::reverse_iterator reverse_iterator;
  typedef typename super_type::const_reference const_reference;
  typedef typename super_type::const_iterator const_iterator;
  typedef typename super_type::const_iter_base const_iter_base;
  typedef typename super_type::const_reverse_iterator const_reverse_iterator;
  typedef typename super_type::element element;
  typedef typename super_type::size_type size_type;
  typedef typename super_type::difference_type difference_type;
  typedef typename super_type::index index;
  typedef typename super_type::extent_range extent_range;

  // template typedefs
  template <std::size_t NDims>
  struct const_array_view {
    typedef boost::detail::multi_array::const_multi_array_view<T,NDims> type;
  };

  template <std::size_t NDims>
  struct array_view {
    typedef boost::detail::multi_array::multi_array_view<T,NDims> type;
  };

  // Assignment from other ConstMultiArray types.
  template <typename ConstMultiArray>
  multi_array_view& operator=(const ConstMultiArray& other) {
    function_requires< 
      boost::detail::multi_array::
      ConstMultiArrayConcept<ConstMultiArray,NumDims> >();

    // make sure the dimensions agree
    assert(other.num_dimensions() == num_dimensions());
    assert(std::equal(other.shape(),other.shape()+num_dimensions(),
		      shape()));
    // iterator-based copy
    std::copy(other.begin(),other.end(),begin());
    return *this;
  }


  multi_array_view& operator=(const multi_array_view& other) {
    if (&other != this) {
      // make sure the dimensions agree
      assert(other.num_dimensions() == num_dimensions());
      assert(std::equal(other.shape(),other.shape()+num_dimensions(),
			shape()));
      // iterator-based copy
      std::copy(other.begin(),other.end(),begin());
    }
    return *this;
  }

  element* origin() { return base_+origin_offset_; }

  template <class IndexList>
  element& operator()(const IndexList& indices) {
    return super_type::access_element(boost::type<element&>(),
				      origin(),
				      indices,strides());
  }


  reference operator[](index idx) {
    return super_type::access(boost::type<reference>(),
			      idx,origin(),
			      shape(),strides(),
			      index_bases());
  }


  // see generate_array_view in base.hpp
#if !defined(BOOST_MSVC) || BOOST_MSVC > 1300
  template <int NDims>
#else
  template <int NumDims, int NDims> // else ICE
#endif // BOOST_MSVC
  typename array_view<NDims>::type 
  operator[](const boost::detail::multi_array::
	     index_gen<NumDims,NDims>& indices) {
    typedef array_view<NDims>::type return_type;
    return
      super_type::generate_array_view(boost::type<return_type>(),
				      indices,
				      shape(),
				      strides(),
				      index_bases(),
				      origin());
  }
  
  
  iterator begin() {
    return iterator(iter_base(*index_bases(),origin(),
				   shape(),strides(),index_bases()));
  }

  iterator end() {
    return iterator(iter_base(*index_bases()+*shape(),origin(),
				   shape(),strides(),index_bases()));
  }

  reverse_iterator rbegin() {
    return reverse_iterator(end());
  }

  reverse_iterator rend() {
    return reverse_iterator(begin());
  }

  // Using declarations don't seem to work for g++
  // These are the proxies to work around this.

  const element* origin() const { return super_type::origin(); }

  template <class IndexList>
  const element& operator()(const IndexList& indices) const {
    return super_type::operator()(indices);
  }

  const_reference operator[](index idx) const {
    return super_type::operator[](idx);
  }

  // see generate_array_view in base.hpp
#if !defined(BOOST_MSVC) || BOOST_MSVC > 1300
  template <int NDims>
#else
  template <int NumDims, int NDims> // else ICE
#endif // BOOST_MSVC
  typename const_array_view<NDims>::type 
  operator[](const boost::detail::multi_array::
	     index_gen<NumDims,NDims>& indices)
    const {
    return super_type::operator[](indices);
  }
  
  const_iterator begin() const {
    return super_type::begin();
  }

  const_iterator end() const {
    return super_type::end();
  }

  const_reverse_iterator rbegin() const {
    return super_type::rbegin();
  }

  const_reverse_iterator rend() const {
    return super_type::rend();
  }

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
private:
  template <typename,std::size_t> friend class multi_array_impl_base;
#else
public: // should be private
#endif

  // constructor used by multi_array_impl_base::generate_array_view to
  // generate array views
  template <typename ExtentList, typename Index>
  explicit multi_array_view(T* base,
			    const ExtentList& extents,
			    const boost::array<Index,NumDims>& strides) :
    super_type(base,extents,strides) { }

};

} // namespace multi_array
} // namespace detail

//
// traits classes to get array_view types
//
template <typename Array, int N>
class array_view_gen {
  typedef typename Array::element element;
public:
  typedef boost::detail::multi_array::multi_array_view<element,N> type;
};

template <typename Array, int N>
class const_array_view_gen {
  typedef typename Array::element element;
public:
  typedef boost::detail::multi_array::const_multi_array_view<element,N> type;  
};

} // namespace boost

#endif // BOOST_MULTI_ARRAY_VIEW_RG071301_HPP


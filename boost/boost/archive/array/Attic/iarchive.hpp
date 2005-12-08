#ifndef BOOST_ARCHIVE_ARRAY_IARCHIVE_HPP
#define BOOST_ARCHIVE_ARRAY_IARCHIVE_HPP

// (C) Copyright 2005 Matthias Troyer and Dave Abrahams
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/archive/basic_archive.hpp>
#include <boost/archive/archive_exception.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/detail/get_data.hpp>
#include <boost/type_traits/has_trivial_constructor.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/pfto.hpp>


namespace boost { namespace archive { namespace array {

  // To conveniently array-optimize an input archive X:
  //
  //   * Derive it from iarchive<X, Impl>, where Impl is an 
  //     archive implementation base class from 
  //     Boost.Serialization
  //
  //   * add a member function template that implements the
  //     procedure for serializing arrays of T (for appropriate T)
  //
  //       template <class T>
  //       load_array(serialization::array<T> &, unsigned int)
  //
  //   * add a unary MPL lambda expression member called
  //     use_array_optimization whose result is convertible to
  //     mpl::true_ iff array elements of type T can be serialized
  //     with the load_array member function, and to mpl::false_ if
  //     the unoptimized procedure must be used. 

template <class Derived, class Base>
class iarchive
 : public Base
{
public:
  iarchive() {}
  
  // replace the forwarding constructors by preprocessor magic
  template <class T1>
  iarchive(T1 & x1) : Base(x1) 
  {}

  template <class T1>
  iarchive(T1 const & x1) : Base(x1) 
  {}

  template <class T1, class T2>
  iarchive(T1& x1, T2 x2) : Base(x1,x2) 
  {}

  // save_override for std::vector and serialization::array dispatches to 
  // save_optimized with an additional argument.
  // 
  // If that argument is of type mpl::true_, an optimized serialization is provided
  // If it is false, we just forward to the default serialization in the base class
  
  //the default version dispatches to the base class
  template<class T>
  void load_optimized(T &t, unsigned int version, mpl::false_)
  {
    Base::load_override(t, version);
  }

  // the optimized implementation for vector uses serialization::array
  template<class U, class Allocator>
  void load_optimized(
    std::vector<U, Allocator> &t, unsigned int version, mpl::true_)
  {
    t.clear();
    // retrieve number of elements
    boost::archive::container_size_type count;
    *this->This() >> BOOST_SERIALIZATION_NVP(count);
    t.resize(count);
    * this->This() >> serialization::make_array(serialization::detail::get_data(t),t.size());
  }

  // the optimized implementation for serialization::array uses save_array
  template<class ValueType>
  void load_optimized(
    serialization::array<ValueType> &t, unsigned int version, mpl::true_)
  {
    This()->load_array(t,version);
  }


  // to load a vector:
  // if the value type is trivially constructable or an optimized array save exists, 
  // then we can use the optimized version

  template<class ValueType, class Allocator>
  void load_override(std::vector<ValueType,Allocator> &x, unsigned int version)
  {
    typedef typename mpl::apply1<
        BOOST_DEDUCED_TYPENAME Derived::use_array_optimization
      , ValueType
    >::type use_optimized;
    load_optimized(x,version, mpl::or_<use_optimized,has_trivial_constructor<ValueType> >() );   
  }
  
  
  // dispatch loading of arrays to the optimized version where supported
  template<class ValueType>
  void load_override(serialization::array<ValueType> const& x, unsigned int version)
  {
    typedef typename mpl::apply1<
        BOOST_DEDUCED_TYPENAME Derived::use_array_optimization
      , ValueType
    >::type use_optimized;
    load_optimized(const_cast<serialization::array<ValueType>&>(x),version,use_optimized());
  }

  // Load everything else in the usual way, forwarding on to the
  // Base class
  template<class T>
  void load_override(T & x, unsigned BOOST_PFTO int version)
  {
    Base::load_override(x, static_cast<unsigned int>(version));
  }
private:
  Derived * This()
  {
    return static_cast<Derived*>(this);
  }
};


} } } // end namespace boost::archive::array



#endif // BOOST_ARCHIVE_ARRAY_OARCHIVE_HPP


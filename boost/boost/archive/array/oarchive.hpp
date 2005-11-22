#ifndef BOOST_ARCHIVE_ARRAY_OARCHIVE_HPP
#define BOOST_ARCHIVE_ARRAY_OARCHIVE_HPP

// (C) Copyright 2005 Matthias Troyer and Dave Abrahams
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/archive/basic_archive.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/save_array.hpp>
#include <boost/serialization/detail/get_data.hpp>
#include <boost/serialization/collections_save_imp.hpp>
#include <boost/type_traits/has_trivial_constructor.hpp>
#include <boost/type_traits/has_trivial_destructor.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/pfto.hpp>


namespace boost { namespace archive { namespace array {

  // To conveniently array-optimize an output archive X:
  //
  //   * Derive it from oarchive<X, Impl>, where Impl is an 
  //     archive implementation base class from 
  //     Boost.Serialization
  //
  //   * add a member function template that implements the
  //     procedure for serializing arrays of T (for appropriate T)
  //
  //       template <class T>
  //       load_array(T* p, size_t nelems, unsigned version)
  //
  //   * add a unary MPL lambda expression member called
  //     use_array_optimization whose result is convertible to
  //     mpl::true_ iff array elements of type T can be serialized
  //     with the load_array member function, and to mpl::false_ if
  //     the unoptimized procedure must be used. 

template <class Derived, class Base>
class oarchive
 : public Base
{
public:
  oarchive() {}
  
  // replace the forwarding constructors by preprocessor magic
  template <class T1>
  oarchive(T1 x1) : Base(x1) 
  {}

  template <class T1>
  oarchive(T1 & x1) : Base(x1) 
  {}

  template <class T1>
  oarchive(T1 const & x1) : Base(x1) 
  {}

  template <class T1, class T2>
  oarchive(T1& x1, T2 x2) : Base(x1,x2) 
  {}

  // to save a vector:
  // if the value type is trivially constructable and destructable, then
  // we can use either the default save_array function or an optimized overload

  template<class U, class Allocator>
  void save_optimized(
    const std::vector<U, Allocator> &t, const unsigned int version, mpl::true_)
  {
    const boost::archive::container_size_type count(t.size());
    * this->This() << BOOST_SERIALIZATION_NVP(count);
    serialization::save_array(* this->This(),serialization::detail::get_data(t),t.size(),version);
  }

  // otherwise use the default version
  template<class U, class Allocator>
  void save_optimized( const std::vector<U, Allocator> &t, const unsigned int, mpl::false_)
  {
    serialization::stl::save_collection<oarchive, std::vector<U, Allocator> >(* this->This(), t);
  }


  // overriding the std::vector serialization by dispaching to one of the two functions above
  template<class U, class Allocator>
  void save_override(std::vector<U,Allocator> const &x, unsigned int version)
  {
    save_optimized(x,version,
        typename mpl::and_<has_trivial_constructor<U>, has_trivial_destructor<U> >::type() );   
  }
  
  
  // override the builtin array serialization using save_array
  template<class T, std::size_t N>
  void save_override(T const(&x)[N], unsigned int version)
  {
    const container_size_type count(N);
    * this->This() << BOOST_SERIALIZATION_NVP(count);
    serialization::save_array(* this->This(),x,N,version);
  }

  // Load everything else in the usual way, forwarding on to the
  // Base class
  template<class T>
  void save_override(T const& x, unsigned BOOST_PFTO int version)
  {
    Base::save_override(x, static_cast<unsigned int>(version));
  }
private:
  Derived * This()
  {
    return static_cast<Derived*>(this);
  }
};


} } } // end namespace boost::archive::array


namespace boost { namespace serialization {


// Overload optimize for optimized archives
template <class Derived, class Base, class ValueType>
typename mpl::apply1<
    typename Derived::use_array_optimization
  , ValueType
>::type
optimize_array(archive::array::oarchive<Derived,Base>*, ValueType*)
{
    typedef typename mpl::apply1<
        BOOST_DEDUCED_TYPENAME Derived::use_array_optimization
      , ValueType
    >::type result;
    
    return result();
}

} } // end namespace boost::serialization


#endif // BOOST_ARCHIVE_ARRAY_OARCHIVE_HPP


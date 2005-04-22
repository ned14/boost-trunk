// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Contains the definition of the class template 
// boost::iostreams::detail::double_object, which is similar to compressed pair
// except that both members of the pair have the same type, and 
// compression occurs only if requested using a boolean template
// parameter.

#ifndef BOOST_IOSTREAMS_DETAIL_DOUBLE_OBJECT_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_DOUBLE_OBJECT_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              

#include <algorithm>              // swap.
#include <boost/call_traits.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace iostreams { namespace detail {

template<typename T>
class single_object_holder {
public:
    typedef typename boost::call_traits<T>::param_type       param_type;
    typedef typename boost::call_traits<T>::reference        reference;
    typedef typename boost::call_traits<T>::const_reference  const_reference;
    single_object_holder() { }
    single_object_holder(param_type t) : first_(t) { }
    reference first() { return first_; }
    const_reference first() const { return first_; }
    reference second() { return first_; }
    const_reference second() const { return first_; }
    void swap(single_object_holder& o)
    { swap(first_, o.first); }
private:
    T first_;
};

template<typename T>
struct double_object_holder {
public:
    typedef typename boost::call_traits<T>::param_type       param_type;
    typedef typename boost::call_traits<T>::reference        reference;
    typedef typename boost::call_traits<T>::const_reference  const_reference;
    double_object_holder() { }
    double_object_holder(param_type t1, param_type t2)
        : first_(t1), second_(t2) { }
    reference first() { return first_; }
    const_reference first() const { return first_; }
    reference second() { return second_; }
    const_reference second() const { return second_; }
    void swap(double_object_holder& d)
    { swap(first_, d.first); swap(second_, d.second_); }
private:
    T first_, second_;
};

template<typename T, typename IsDouble>
class double_object 
    : public mpl::if_<
                 IsDouble, 
                 double_object_holder<T>, 
                 single_object_holder<T>
             >::type
{
private:
    typedef typename 
            mpl::if_<
                IsDouble, 
                double_object_holder<T>, 
                single_object_holder<T>
            >::type                                   base_type;
public:
    typedef typename call_traits<T>::param_type       param_type;
    typedef typename call_traits<T>::reference        reference;
    typedef typename call_traits<T>::const_reference  const_reference;
    double_object() : base_type() {}
    double_object(param_type t1, param_type t2)
        : base_type(t1, t2) { }
    bool is_double() const { return IsDouble::value; }
};

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_DOUBLE_OBJECT_HPP_INCLUDED

#ifndef  BOOST_SERIALIZATION_VECTOR_HPP
#define BOOST_SERIALIZATION_VECTOR_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// vector.hpp: serialization for stl vector templates

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// fast array serialization (C) Copyright 2005 Matthias Troyer 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <vector>

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#include <boost/serialization/collections_save_imp.hpp>
#include <boost/serialization/collections_load_imp.hpp>
#include <boost/serialization/split_free.hpp>

#ifdef BOOST_ARRAY_SLIGHTLY_INTRUSIVE
#include <boost/type_traits/has_trivial_constructor.hpp>
#include <boost/type_traits/has_trivial_destructor.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/serialization/detail/get_data.hpp>
#endif

// function specializations must be defined in the appropriate
// namespace - boost::serialization
#if defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)
#define STD _STLP_STD
#else
#define STD std
#endif

namespace boost { 
namespace serialization {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// vector<T>


#ifndef BOOST_ARRAY_SLIGHTLY_INTRUSIVE
template<class Archive, class U, class Allocator>
inline void save(
    Archive & ar,
    const STD::vector<U, Allocator> &t,
    const unsigned int /* file_version */
){
    boost::serialization::stl::save_collection<Archive, STD::vector<U, Allocator> >(
        ar, t
    );
}
#else
// if the value type is not trivially constructable or destructable, then
// we have to use save_collection

template<class Archive, class U, class Allocator>
inline void save_optimized(
    Archive & ar,
    const STD::vector<U, Allocator> &t,
    const unsigned int /* file_version */,
    mpl::false_
){
    boost::serialization::stl::save_collection<Archive, STD::vector<U, Allocator> >(
        ar, t
    );
}

// if the value type is trivially constructable and destructable, then
// we can use either the default save_array function or an optimized overload

template<class Archive, class U, class Allocator>
inline void save_optimized(
    Archive & ar,
    const STD::vector<U, Allocator> &t,
    const unsigned int file_version,
    mpl::true_
){
    const boost::archive::container_size_type count(t.size());
    ar << BOOST_SERIALIZATION_NVP(count);
    save_array(ar,detail::get_data(t),t.size(),file_version);
}

// dispatch the save depending on whether save_collection or save_array should be used
template<class Archive, class U, class Allocator>
inline void save(
    Archive & ar,
    STD::vector<U, Allocator> const &t,
    const unsigned int file_version
)
{
    save_optimized(
        ar,t,file_version,
        typename mpl::and_<has_trivial_constructor<U>, has_trivial_destructor<U> >::type()
      );   
}
#endif

// if the value type is not trivially constructable or destructable, then
// we have to use load_collection

template<class Archive, class U, class Allocator>
inline void load_optimized(
    Archive & ar,
    STD::vector<U, Allocator> &t,
    const unsigned int /* file_version */,
    mpl::false_
){
    boost::serialization::stl::load_collection<
        Archive,
        STD::vector<U, Allocator>,
        boost::serialization::stl::archive_input_seq<
            Archive, STD::vector<U, Allocator> 
        >,
        boost::serialization::stl::reserve_imp<STD::vector<U, Allocator> >
    >(ar, t);
}


#ifndef BOOST_ARRAY_SLIGHTLY_INTRUSIVE

template<class Archive, class U, class Allocator>
inline void load(
    Archive & ar,
    STD::vector<U, Allocator> &t,
    const unsigned int /* file_version */
){
    boost::serialization::stl::load_collection<
        Archive,
        STD::vector<U, Allocator>,
        boost::serialization::stl::archive_input_seq<
            Archive, STD::vector<U, Allocator> 
        >,
        boost::serialization::stl::reserve_imp<STD::vector<U, Allocator> >
    >(ar, t);
}

#else

// if the value type is trivially constructable and destructable, then
// we can use either the default load_array function or an optimized overload

template<class Archive, class U, class Allocator>
inline void load_optimized(
    Archive & ar,
    STD::vector<U, Allocator> &t,
    const unsigned int file_version,
    mpl::true_
){
    t.clear();
    // retrieve number of elements
    boost::archive::container_size_type count;
    ar >> BOOST_SERIALIZATION_NVP(count);
    t.resize(count);
    serialization::load_array(ar,detail::get_data(t),t.size(),file_version);
}

// dispatch the load depending on whether load_collection or load_array should be used
template<class Archive, class U, class Allocator>
inline void load(
    Archive & ar,
    STD::vector<U, Allocator> &t,
    const unsigned int file_version
)
{
    load_optimized(
        ar,t,file_version,
        typename mpl::and_<has_trivial_constructor<U>, has_trivial_destructor<U> >::type()
      );   
}

#endif

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<class Archive, class U, class Allocator>
inline void serialize(
    Archive & ar,
    STD::vector<U, Allocator> & t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

#if ! BOOST_WORKAROUND(BOOST_MSVC, <= 1300)

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// vector<bool>
template<class Archive, class Allocator>
inline void save(
    Archive & ar,
    const STD::vector<bool, Allocator> &t,
    const unsigned int /* file_version */
){
    // record number of elements
    boost::archive::container_size_type count = t.size();
    ar << BOOST_SERIALIZATION_NVP(count);
    STD::vector<bool>::const_iterator it = t.begin();
    while(count-- > 0){
        bool tb = *it++;
        ar << boost::serialization::make_nvp("item", tb);
    }
}

template<class Archive, class Allocator>
inline void load(
    Archive & ar,
    STD::vector<bool, Allocator> &t,
    const unsigned int /* file_version */
){
    // retrieve number of elements
    boost::archive::container_size_type count;
    ar >> BOOST_SERIALIZATION_NVP(count);
    t.clear();
    while(count-- > 0){
        bool i;
        ar >> boost::serialization::make_nvp("item", i);
        t.push_back(i);
    }
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<class Archive, class Allocator>
inline void serialize(
    Archive & ar,
    STD::vector<bool, Allocator> & t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

#endif // BOOST_WORKAROUND

} // serialization
} // namespace boost

#include <boost/serialization/collection_traits.hpp>

BOOST_SERIALIZATION_COLLECTION_TRAITS(STD::vector)
#undef STD

#endif // BOOST_SERIALIZATION_VECTOR_HPP

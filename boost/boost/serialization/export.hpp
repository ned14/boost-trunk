#ifndef BOOST_SERIALIZATION_EXPORT_HPP
#define BOOST_SERIALIZATION_EXPORT_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// export.hpp: set traits of classes to be serialized

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// implementation of class export functionality.  This is an alternative to
// "forward declaration" method to provoke instantiation of derived classes
// that are to be serialized through pointers.

#include <utility>

#include <boost/config.hpp>

// if no archive headers have been included this is a no op
// this is to permit BOOST_EXPORT etc to be included in a
// file declaration header
#include <boost/static_assert.hpp>
#include <boost/preprocessor/stringize.hpp>

#include <boost/archive/detail/dynamically_initialized.hpp>
#include <boost/serialization/force_include.hpp>
#include <boost/serialization/type_info_implementation.hpp>
#include <boost/serialization/is_abstract.hpp>
#include <boost/archive/detail/register_archive.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/or.hpp>

#include <iostream>

namespace boost {
namespace archive {
namespace detail {

// forward template declarations
class basic_pointer_iserializer;
template<class Archive, class T>
BOOST_DLLEXPORT const basic_pointer_iserializer &
instantiate_pointer_iserializer(Archive * ar, T *) BOOST_USED;

class basic_pointer_oserializer;
template<class Archive, class T>
BOOST_DLLEXPORT const basic_pointer_oserializer &
instantiate_pointer_oserializer(Archive * ar, T *) BOOST_USED;

template <class Archive, class Serializable>
struct export_impl
{
    static void enable_load(mpl::true_)
    {
        instantiate_pointer_iserializer((Archive*)0,(Serializable*)0);
    }

    static void enable_save(mpl::true_)
    {
        instantiate_pointer_oserializer((Archive*)0,(Serializable*)0);
    }

    inline static void enable_load(mpl::false_) {}
    inline static void enable_save(mpl::false_) {}
};

template <class T, class IsConcrete>
inline int maybe_instantiate_ptr_serialization(IsConcrete)
{
    instantiate_ptr_serialization<T>(0);
    return 0;
}

template <class T>
inline int maybe_instantiate_ptr_serialization(mpl::false_)
{
    return 0;
}

// instantiation of this template creates a static object.
template<class T>
struct guid_initializer
{
    typedef BOOST_DEDUCED_TYPENAME boost::serialization::type_info_implementation<T>::type eti_type;
    static void export_register(const char *key)
    {
        eti_type::export_register(key);
    }
    
    static const guid_initializer& get_instance(char const* key)
    {
        static guid_initializer const instance(key);
        return instance;
    }
    
    BOOST_DLLEXPORT guid_initializer(const char *key = 0) BOOST_USED ;
};


template<class T>
BOOST_DLLEXPORT guid_initializer<T>::guid_initializer(const char *key)
{
    if(0 != key)
        export_register(key);

    // If T isn't abstract, instantiate the pointer serializers for T
    // with known archive types.
    maybe_instantiate_ptr_serialization<T>(mpl::not_<serialization::is_abstract<T> >());
}


// On many platforms, naming a specialization of this template is
// enough to cause its argument to be instantiated.
template <void(*)()>
struct instantiate_function {};

template <class Archive, class Serializable>
struct ptr_serialization_support
{
# ifdef BOOST_MSVC
    virtual void instantiate();
    
# elif defined(__BORLANDC__)
    
    static void instantiate();
    enum { x = sizeof(instantiate(),3) };
    
# else
    
    static void instantiate();
    typedef instantiate_function<
        &ptr_serialization_support::instantiate
    > x;

# endif
};

template <class Archive, class Serializable>
void ptr_serialization_support<Archive,Serializable>::instantiate()
{
    typedef typename Archive::is_saving is_saving;
    export_impl<Archive,Serializable>::enable_save(is_saving());

    typedef typename Archive::is_loading is_loading;
    export_impl<Archive,Serializable>::enable_load(is_loading());
}

} // namespace detail
} // namespace archive
} // namespace boost

#define BOOST_CLASS_EXPORT_GUID(T, K)                                               \
namespace                                                                           \
{                                                                                   \
    ::boost::archive::detail::guid_initializer<T> const&                            \
          BOOST_PP_CAT(boost_serialization_guid_initializer_, __LINE__)             \
          = ::boost::archive::detail::guid_initializer<T>::get_instance(K);         \
}

#if BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3205))

# define BOOST_SERIALIZATION_MWERKS_BASE_AND_DERIVED(Base,Derived)          \
namespace                                                                   \
{                                                                           \
  int BOOST_PP_CAT(boost_serialization_mwerks_init_, __LINE__) = (          \
      ::boost::archive::detail::instantiate_ptr_serialization<Derived>(0),3);   \
  int BOOST_PP_CAT(boost_serialization_mwerks_init2_, __LINE__) = (          \
      ::boost::serialization::void_cast_register((Derived*)0,(Base*)0)        \
    , 3);                                                                   \
}

#else

# define BOOST_SERIALIZATION_MWERKS_BASE_AND_DERIVED(Base,Derived)

#endif 

// check for unnecessary export.  T isn't polymorphic so there is no
// need to export it.
#define BOOST_CLASS_EXPORT_CHECK(T)                              \
    BOOST_STATIC_WARNING(                                        \
        boost::serialization::type_info_implementation< T >      \
            ::type::is_polymorphic::value                        \
    );                                                           \
    /**/

// the default exportable class identifier is the class name
// the default list of archives types for which code id generated
// are the originally included with this serialization system
#define BOOST_CLASS_EXPORT(T)                   \
    BOOST_CLASS_EXPORT_GUID(                    \
        T,                                      \
        BOOST_PP_STRINGIZE(T)                   \
    )                                           \
    /**/

#endif // BOOST_SERIALIZATION_EXPORT_HPP


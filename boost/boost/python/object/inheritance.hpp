// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef INHERITANCE_DWA200216_HPP
# define INHERITANCE_DWA200216_HPP

# include <boost/python/converter/type_id.hpp>
# include <boost/shared_ptr.hpp>

namespace boost { namespace python { namespace objects {

typedef converter::undecorated_type_id_t class_id;
using converter::undecorated_type_id;

// Types used to get address and id of most derived type
typedef std::pair<void*,class_id> dynamic_id_t;
typedef dynamic_id_t (*dynamic_id_function)(void*);

BOOST_PYTHON_DECL void register_dynamic_id_aux(
    class_id static_id, dynamic_id_function get_dynamic_id);

BOOST_PYTHON_DECL void add_cast(
    class_id src_t, class_id dst_t, void* (*cast)(void*), bool polymorphic);

BOOST_PYTHON_DECL void* find_static_type(void* p, class_id src, class_id dst);

BOOST_PYTHON_DECL void* find_dynamic_type(void* p, class_id src, class_id dst);

// is_polymorphic test from John Maddock
template <class T>
struct is_polymorphic
{
   struct d1 : public T
   {
      d1();
      char padding[256];
   };
   struct d2 : public T
   {
      d2();
      virtual ~d2();
      virtual void foo();
      char padding[256];
   };
   BOOST_STATIC_CONSTANT(bool, value = (sizeof(d2) == sizeof(d1)));
};

//
// a generator with an execute() function which, given a source type
// and a pointer to an object of that type, returns its most-derived
// /reachable/ type identifier and object pointer.
//

// first, the case where T has virtual functions
template <class T>
struct polymorphic_id_generator
{
    static dynamic_id_t execute(void* p_)
    {
        T* p = static_cast<T*>(p_);
        return std::make_pair(dynamic_cast<void*>(p), class_id(typeid(*p)));
    }
};

// now, the non-polymorphic case.
template <class T>
struct non_polymorphic_id_generator
{
    static dynamic_id_t execute(void* p_)
    {
        return std::make_pair(p_, converter::undecorated_type_id<T>());
    }
};

// Now the generalized selector
template <class T>
struct dynamic_id_generator
{
    typedef typename mpl::select_type<
        is_polymorphic<T>::value
        , polymorphic_id_generator<T>
        , non_polymorphic_id_generator<T> >::type type;
};

// Register the dynamic id function for T with the type-conversion
// system.
template <class T>
void register_dynamic_id(T* = 0)
{
    typedef typename dynamic_id_generator<T>::type generator;
    register_dynamic_id_aux(
        converter::undecorated_type_id<T>(), &generator::execute);
}

//
// a generator with an execute() function which, given a void*
// pointing to an object of type Source will attempt to convert it to
// an object of type Target.
//

template <class Source, class Target>
struct dynamic_cast_generator
{
    static void* execute(void* source)
    {
        return dynamic_cast<Target*>(
            static_cast<Source*>(source));
    }
        
};

template <class Source, class Target>
struct implicit_cast_generator
{
    static void* execute(void* source)
    {
        Target* result = static_cast<Source*>(source);
        return result;
    }
};

template <class Source, class Target>
struct cast_generator
{
    // CWPro7 will return false sometimes, but that's OK since we can
    // always cast up with dynamic_cast<>
    BOOST_STATIC_CONSTANT(
        bool, is_upcast = (
            is_base_and_derived<Target,Source>::value
            ));

    typedef typename mpl::select_type<
        is_upcast
# if defined(__MWERKS__) && __MWERKS__ <= 0x2406
        // grab a few more implicit_cast cases for CodeWarrior
        || !is_polymorphic<Source>::value
        || !is_polymorphic<Target>::value
# endif 
        , implicit_cast_generator<Source,Target>
        , dynamic_cast_generator<Source,Target>
    >::type type;
};

template <class Source, class Target>
inline void register_conversion(
    // We need this parameter because CWPro7 can't determine
    // which is the base reliably.
    bool is_downcast = !cast_generator<Source,Target>::is_upcast

    // These parameters shouldn't be used, they're an MSVC bug workaround
    , Source* = 0, Target* = 0)
{
    typedef typename cast_generator<Source,Target>::type generator;
    
    add_cast(converter::undecorated_type_id<Source>()
             , converter::undecorated_type_id<Target>()
             , &generator::execute
             , is_downcast);
}

}}} // namespace boost::python::object

#endif // INHERITANCE_DWA200216_HPP

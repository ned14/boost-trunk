// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef TYPE_FROM_PYTHON_DWA2002130_HPP
# define TYPE_FROM_PYTHON_DWA2002130_HPP

# include <boost/python/converter/registry.hpp>
# include <boost/python/detail/void_ptr.hpp>

namespace boost { namespace python {

namespace detail
{
  // Given a pointer-to-function of 1 parameter returning a reference
  // type, return the type_id of the function's return type.
  template <class T, class U>
  inline converter::undecorated_type_id_t extractor_type_id(T&(*)(U))
  {
      return converter::undecorated_type_id<T>();
  }

  // A function generator whose static execute() function is an lvalue
  // from_python converter using the given Extractor. U is expected to
  // be the actual type of the PyObject instance from which the result
  // is being extracted.
  template <class Extractor, class U>
  struct normalized_extractor
  {
      static inline void* execute(PyObject* op)
      {
          typedef typename boost::add_reference<U>::type param;
          return &Extractor::execute(
              boost::python::detail::void_ptr_to_reference(
                  op, (param(*)())0 )
              );
      }
  };

  // Given an Extractor type and a pointer to its execute function,
  // return a new object whose static execute function does the same
  // job but is a conforming lvalue from_python conversion function.
  //
  // usage: normalize<Extractor>(&Extractor::execute)
  template <class Extractor, class T, class U>
  inline normalized_extractor<Extractor,U>
  normalize(T(*)(U), Extractor* = 0)
  {
      return normalized_extractor<Extractor, U>();
  }
}

// An Extractor which extracts the given member from a Python object
// whose instances are stored as InstanceType.
template <class InstanceType, class MemberType, MemberType (InstanceType::*member)>
struct member_extractor
{
    static MemberType& execute(InstanceType& c)
    {
        (void)c.ob_type; // static assertion
        return c.*member;
    }
};

// An Extractor which simply extracts the entire python object
// instance of InstanceType.
template <class InstanceType>
struct identity_extractor
{
    static InstanceType& execute(InstanceType& c)
    {
        (void)c.ob_type; // static assertion
        return c;
    }
};

// Registers a from_python conversion which extracts lvalues using
// Extractor's static execute function from Python objects whose type
// object is python_type.
template <PyTypeObject const* python_type, class Extractor>
struct type_from_python
{
    type_from_python()
    {
        converter::registry::insert(
            &extract, detail::extractor_type_id(&Extractor::execute));
    }
    
    static void* extract(PyObject* op)
    {
        return PyObject_TypeCheck(op, const_cast<PyTypeObject*>(python_type))
            ? const_cast<void*>(
                static_cast<void const volatile*>(
                    detail::normalize<Extractor>(&Extractor::execute).execute(op)))
            : 0
            ;
    }
};

}} // namespace boost::python

#endif // TYPE_FROM_PYTHON_DWA2002130_HPP

// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef ARG_TO_PYTHON_DWA200265_HPP
# define ARG_TO_PYTHON_DWA200265_HPP

# include <boost/python/ptr.hpp>
# include <boost/python/converter/registered.hpp>
# include <boost/python/converter/registered_pointee.hpp>
# include <boost/python/converter/arg_to_python_base.hpp>
# include <boost/python/to_python_indirect.hpp>
# include <boost/type_traits/cv_traits.hpp>
# include <boost/type_traits/composite_traits.hpp>
# include <boost/type_traits/function_traits.hpp>
# include <boost/python/detail/indirect_traits.hpp>
# include <boost/python/detail/convertible.hpp>
# include <boost/python/detail/string_literal.hpp>
# include <boost/python/base_type_traits.hpp>
// Bring in specializations
# include <boost/python/converter/builtin_converters.hpp>
# include <boost/python/tag.hpp>
# include <boost/python/object/function_handle.hpp>

namespace boost { namespace python { namespace converter { 

template <class T> struct is_object_manager;

namespace detail
{
  template <class T>
  struct function_arg_to_python : handle<>
  {
      function_arg_to_python(T const& x);
  };

  template <class T>
  struct reference_arg_to_python : handle<>
  {
      reference_arg_to_python(T& x);
   private:
      static PyObject* get_object(T& x);
  };

  template <class T>
  struct value_arg_to_python : arg_to_python_base
  {
      // Throw an exception if the conversion can't succeed
      value_arg_to_python(T const&);
  };

  template <class Ptr>
  struct pointer_deep_arg_to_python : arg_to_python_base
  {
      // Throw an exception if the conversion can't succeed
      pointer_deep_arg_to_python(Ptr);
  };

  template <class Ptr>
  struct pointer_shallow_arg_to_python : handle<>
  {
      // Throw an exception if the conversion can't succeed
      pointer_shallow_arg_to_python(Ptr);
   private:
      static PyObject* get_object(Ptr p);
  };

  // Convert types that manage a Python object to_python
  template <class T>
  struct object_manager_arg_to_python
  {
      object_manager_arg_to_python(T const& x) : m_src(x) {}
      
      PyObject* get() const
      {
          return python::upcast<PyObject>(get_managed_object(m_src, tag));
      }
      
   private:
      T const& m_src;
  };

  template <class T>
  struct select_arg_to_python
  {
      // Special handling for char const[N]; interpret them as char
      // const* for the sake of conversion
      BOOST_STATIC_CONSTANT(
          bool, is_string = python::detail::is_string_literal<T const>::value);
      
      BOOST_STATIC_CONSTANT(
          bool, function = is_function<T>::value | python::detail::is_pointer_to_function<T>::value | is_member_function_pointer<T>::value);
      
      BOOST_STATIC_CONSTANT(
          bool, manager = is_object_manager<T>::value);
      
      BOOST_STATIC_CONSTANT(
          bool, ptr = is_pointer<T>::value);
      
      BOOST_STATIC_CONSTANT(
          bool, ref_wrapper = is_reference_wrapper<T>::value);

      BOOST_STATIC_CONSTANT(
          bool, ptr_wrapper = is_pointer_wrapper<T>::value);

      typedef typename unwrap_reference<T>::type unwrapped_referent;
      typedef typename unwrap_pointer<T>::type unwrapped_ptr;

      typedef typename mpl::if_c<
          is_string
          , arg_to_python<char const*>
          , typename mpl::if_c<
              function
              , function_arg_to_python<T>
              , typename mpl::if_c<
                  manager
                  , object_manager_arg_to_python<T>
                  , typename mpl::if_c<
                      ptr
                      , pointer_deep_arg_to_python<T>
                      , typename mpl::if_c<
                          ptr_wrapper
                          , pointer_shallow_arg_to_python<unwrapped_ptr>
                          , typename mpl::if_c<
                              ref_wrapper
                              , reference_arg_to_python<unwrapped_referent>
                              , value_arg_to_python<T>
                            >::type
                        >::type
                    >::type
                >::type
            >::type
        >::type
      type;
  };
}

template <class T>
struct arg_to_python
    : detail::select_arg_to_python<T>::type
{
    typedef typename detail::select_arg_to_python<T>::type base;
 public: // member functions
    // Throw an exception if the conversion can't succeed
    arg_to_python(T const& x);
};

//
// implementations
//
namespace detail
{
  // reject_raw_object_ptr -- cause a compile-time error if the user
  // should pass a raw Python object pointer
  using python::detail::yes_convertible;
  using python::detail::no_convertible;
  using python::detail::unspecialized;
  
  template <class T> struct cannot_convert_raw_PyObject;

  template <class T, class Convertibility>
  struct reject_raw_object_helper
  {
      static void error(Convertibility)
      {
          cannot_convert_raw_PyObject<T*>::to_python_use_handle_instead();
      }
      static void error(...) {}
  };
  
  template <class T>
  inline void reject_raw_object_ptr(T*)
  {
      reject_raw_object_helper<T,yes_convertible>::error(
          python::detail::convertible<PyObject const volatile*>::check((T*)0));
      
      typedef typename remove_cv<T>::type value_type;
      
      reject_raw_object_helper<T,no_convertible>::error(
          python::detail::convertible<unspecialized*>::check(
              (base_type_traits<value_type>*)0
              ));
  }
  // ---------
      
  template <class T>
  inline function_arg_to_python<T>::function_arg_to_python(T const& x)
      : handle<>(python::objects::make_function_handle(x))
  {
  }

  template <class T>
  inline value_arg_to_python<T>::value_arg_to_python(T const& x)
      : arg_to_python_base(&x, registered<T>::converters)
  {
  }

  template <class Ptr>
  inline pointer_deep_arg_to_python<Ptr>::pointer_deep_arg_to_python(Ptr x)
      : arg_to_python_base(x, registered_pointee<Ptr>::converters)
  {
      detail::reject_raw_object_ptr((Ptr)0);
  }

  template <class T>
  inline PyObject* reference_arg_to_python<T>::get_object(T& x)
  {
      to_python_indirect<T&,python::detail::make_reference_holder> convert;
      return convert(x);
  }

  template <class T>
  inline reference_arg_to_python<T>::reference_arg_to_python(T& x)
      : handle<>(reference_arg_to_python<T>::get_object(x))
  {
  }

  template <class Ptr>
  inline pointer_shallow_arg_to_python<Ptr>::pointer_shallow_arg_to_python(Ptr x)
      : handle<>(pointer_shallow_arg_to_python<Ptr>::get_object(x))
  {
      detail::reject_raw_object_ptr((Ptr)0);
  }

  template <class Ptr>
  inline PyObject* pointer_shallow_arg_to_python<Ptr>::get_object(Ptr x)
  {
      to_python_indirect<Ptr,python::detail::make_reference_holder> convert;
      return convert(x);
  }
}

template <class T>
inline arg_to_python<T>::arg_to_python(T const& x)
    : base(x)
{}

}}} // namespace boost::python::converter

#endif // ARG_TO_PYTHON_DWA200265_HPP

// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef FROM_PYTHON_DWA2002127_HPP
# define FROM_PYTHON_DWA2002127_HPP

# include <boost/python/detail/config.hpp>
# include <boost/python/converter/body.hpp>
# include <boost/python/converter/from_python_function.hpp>
# include <boost/python/converter/from_python_data.hpp>
# include <boost/python/converter/type_id.hpp>
# include <boost/python/converter/registry.hpp>
# include <boost/python/detail/wrap_python.hpp>

namespace boost { namespace python { namespace converter { 

// The type of convertibility checking functions
typedef void* (*from_python_check)(PyObject*);
typedef void (*from_python_destructor)(from_python_data&);

// forward declaration
template <class T> struct from_python_lookup;

// from_python --
//    A body class representing a conversion from python to C++.

struct BOOST_PYTHON_DECL from_python_converter_base : body
{
    from_python_converter_base(type_id_t, from_python_check); // registers

    // Must return non-null iff the conversion will be successful. Any
    // non-null pointer is acceptable, and will be passed on to the
    // convert() function, so useful data can be stored there.
    inline void* convertible(PyObject*) const;

    // Given the head of a from_python converter chain, find the
    // converter which can convert p, leaving its intermediate data in
    // data.
    inline static from_python_converter_base const*
    find(from_python_converter_base const*chain, PyObject* p, void*& data);
    
 private:
    from_python_check m_convertible;
    from_python_converter_base* m_next;
};


template <class T>
struct from_python_converter : from_python_converter_base
{
 public: // types
    typedef typename from_python_function<T>::type conversion_function;
    
 public: // member functions    
    from_python_converter(from_python_check, conversion_function, from_python_destructor = 0);
    T convert(PyObject*, from_python_data&) const;
    void destroy(from_python_data&) const;

    // Find a converter for converting p to a T.
    static from_python_converter<T> const* find(PyObject* p, void*& data);
    
 private: // data members
    conversion_function m_convert;
    from_python_destructor m_destroy;

    // Keeps the chain of converters which convert from PyObject* to T
    static from_python_converter_base*const& chain;
};

// Initialized to refer to a common place in the registry.
template <class T>
from_python_converter_base*const&
from_python_converter<T>::chain = registry::from_python_chain(type_id<T>());

// -------------------------------------------------------------------------

// A class which implements from_python with a registry lookup.
template <class T>
struct from_python_lookup // : from_python_base
{
 public: // types
    
 public: // member functions
    from_python_lookup(PyObject* source);
    ~from_python_lookup();

    bool convertible() const;
    T operator()(PyObject*);

 public: // functions for use by conversion implementations
    // Get the converter object
    from_python_converter<T> const* converter() const;
    
 private: // data members
    typedef typename from_python_intermediate_data<T>::type intermediate_t;
    mutable intermediate_t m_intermediate_data;
    from_python_converter<T> const* m_converter;
};

//
// implementations
//
inline void* from_python_converter_base::convertible(PyObject* o) const
{
    return m_convertible(o);
}

inline from_python_converter_base const*
from_python_converter_base::find(
    from_python_converter_base const* chain, PyObject* p, void*& data)
{
    for (from_python_converter_base const* q = chain; q != 0 ; q = q->m_next)
    {
        void* d = q->convertible(p);
        if (d != 0)
        {
            data = d;
            return q;
        }
    }
    return 0;
}

template <class T>
inline from_python_converter<T>::from_python_converter(
     from_python_check checker
    , conversion_function converter
    , from_python_destructor destructor // = 0
    )
    : from_python_converter_base(type_id<T>(), checker)
    , m_convert(converter)
    , m_destroy(destructor)
{
    
}

template <class T>
inline from_python_converter<T> const*
from_python_converter<T>::find(PyObject* p, void*& data)
{
    return static_cast<from_python_converter<T> const*>(
        from_python_converter_base::find(chain, p, data));
}

template <class T>
inline T from_python_converter<T>::convert(PyObject* src, from_python_data& data) const
{
    return this->m_convert(src, data);
}

template <class T>
inline void from_python_converter<T>::destroy(from_python_data& data) const
{
    if (this->m_destroy)
    {
        this->m_destroy(data);
    }
}

template <class T>
inline from_python_lookup<T>::from_python_lookup(PyObject* src)
    : m_converter(
        from_python_converter<T>::find(
            src, m_intermediate_data.stage1))
{
}

template <class T>
inline from_python_lookup<T>::~from_python_lookup()
{
    if (m_converter != 0)
        m_converter->destroy(m_intermediate_data);
}

template <class T>
inline bool from_python_lookup<T>::convertible() const
{
    return this->m_converter != 0;
}

template <class T>
inline T from_python_lookup<T>::operator()(PyObject* obj)
{
    return this->m_converter->convert(obj, m_intermediate_data);
}

template <class T>
inline from_python_converter<T> const*
from_python_lookup<T>::converter() const
{
    return this->m_converter;
}

}}} // namespace boost::python::converter

#endif // FROM_PYTHON_DWA2002127_HPP

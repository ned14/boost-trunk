// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#include <boost/python/module.hpp>
//#include <boost/python/returning.hpp>
#include <boost/python/class.hpp>
#include <boost/ref.hpp>
#include <boost/python/ptr.hpp>
#include <boost/python/return_value_policy.hpp>
#include <boost/python/reference_existing_object.hpp>
#include <boost/python/call.hpp>

using namespace boost::python;

int apply_int_int(PyObject* f, int x)
{
    return call<int>(f, x);
}

void apply_void_int(PyObject* f, int x)
{
    call<void>(f, x);
}

struct X
{
    explicit X(int x) : x(x), magic(7654321) { ++counter; }
    X(X const& rhs) : x(rhs.x), magic(7654321) { ++counter; }
    ~X() { assert(magic == 7654321); magic = 6666666; x = 9999; --counter; }

    void set(int x) { assert(magic == 7654321); this->x = x; }
    int value() const { assert(magic == 7654321); return x; }
    static int count() { return counter; }
 private:
    void operator=(X const&);
 private:
    int x;
    long magic;
    static int counter;
};

X apply_X_X(PyObject* f, X x)
{
    return call<X>(f, x);
}

void apply_void_X_ref(PyObject* f, X& x)
{
    call<void>(f, boost::ref(x));
}

X& apply_X_ref_pyobject(PyObject* f, PyObject* obj)
{
    return call<X&>(f, obj);
}

X* apply_X_ptr_pyobject(PyObject* f, PyObject* obj)
{
    return call<X*>(f, obj);
}

void apply_void_X_cref(PyObject* f, X const& x)
{
    call<void>(f, boost::cref(x));
}

void apply_void_X_ptr(PyObject* f, X* x)
{
    call<void>(f, ptr(x));
}

void apply_void_X_deep_ptr(PyObject* f, X* x)
{
    call<void>(f, x);
}

char const* apply_cstring_cstring(PyObject* f, char const* s)
{
    return call<char const*>(f, s);
}

char const* apply_cstring_pyobject(PyObject* f, PyObject* s)
{
    return call<char const*>(f, s);
}

char apply_char_char(PyObject* f, char c)
{
    return call<char>(f, c);
}

int X::counter;

BOOST_PYTHON_MODULE_INIT(callbacks_ext)
{
    boost::python::module("callbacks_ext")
        .def("apply_int_int", apply_int_int)
        .def("apply_void_int", apply_void_int)
        .def("apply_X_X", apply_X_X)
        .def("apply_void_X_ref", apply_void_X_ref)
        .def("apply_void_X_cref", apply_void_X_cref)
        .def("apply_void_X_ptr", apply_void_X_ptr)
        .def("apply_void_X_deep_ptr", apply_void_X_deep_ptr)
        
        .def("apply_X_ptr_pyobject", apply_X_ptr_pyobject
             , return_value_policy<reference_existing_object>())
        
        .def("apply_X_ref_pyobject", apply_X_ref_pyobject
             , return_value_policy<reference_existing_object>())
        
        .def("apply_cstring_cstring", apply_cstring_cstring)
        .def("apply_cstring_pyobject", apply_cstring_pyobject)
        .def("apply_char_char", apply_char_char)
        
        .add(
            class_<X>("X")
            .def_init(args<int>())
            .def_init(args<X const&>())
            .def("value", &X::value)
            .def("set", &X::set)
            )
        .def("x_count", &X::count)
        ;
}

#include "module_tail.cpp"

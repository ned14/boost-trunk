// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#include <boost/python/cast.hpp>

struct X { long x; };
struct Y : X, PyObject {};

int main()
{
    PyTypeObject o;
    Y y;
    assert(&boost::python::upcast<PyObject>(&o)->ob_refcnt == &o.ob_refcnt);
    assert(&boost::python::upcast<PyObject>(&y)->ob_refcnt == &y.ob_refcnt);
    return 0;
}


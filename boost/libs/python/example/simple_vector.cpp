// Example by Ralf W. Grosse-Kunstleve

#include <boost/python/class_builder.hpp>
namespace python = boost::python;

namespace { // Avoid cluttering the global namespace.

  // A wrapper is used to define additional constructors.
  //
  struct vector_double_wrapper: std::vector<double>
  {
    // Tell the compiler how to convert a base class object to
    // this wrapper object.
    vector_double_wrapper(PyObject*, const std::vector<double>& vd)
      : std::vector<double>(vd) {}

    vector_double_wrapper(PyObject* self)
      : std::vector<double>() {}

    vector_double_wrapper(PyObject* self, int n)
      : std::vector<double>(n) {}

    vector_double_wrapper(PyObject* self, python::tuple tuple)
      : std::vector<double>(tuple.size())
    {
      std::vector<double>::iterator vd = begin();
      for (int i = 0; i < tuple.size(); i++)
        vd[i] = BOOST_PYTHON_CONVERSION::from_python(tuple[i].get(),
          python::type<double>());
    }
  };

  void raise_vector_IndexError() {
    PyErr_SetString(PyExc_IndexError, "vector index out of range");
    throw python::error_already_set();
  }

  double getitem(const std::vector<double>& vd, std::size_t key) {
    if (key >= vd.size()) raise_vector_IndexError();
    return vd[key];
  }

  void setitem(std::vector<double>& vd, std::size_t key, double d) {
    if (key >= vd.size()) raise_vector_IndexError();
    std::vector<double>::iterator vditer = vd.begin();
    vditer[key] = d;
  }

  void delitem(std::vector<double>& vd, std::size_t key) {
    if (key >= vd.size()) raise_vector_IndexError();
    std::vector<double>::iterator vditer = vd.begin();
    vd.erase(vditer + key);
  }

  // Convert vector_double to a regular Python tuple.
  //
  python::tuple as_tuple(const std::vector<double>& vd)
  {
    python::tuple t(vd.size());
    for (int i = 0; i < vd.size(); i++) t.set_item(i,
      python::ref(BOOST_PYTHON_CONVERSION::to_python(vd[i])));
    return t;
  }

  // Function returning a vector_double object to Python.
  //
  std::vector<double> foo(int n)
  {
    std::vector<double> vd(n);
    std::vector<double>::iterator vditer = vd.begin();
    for (int i = 0; i < n; i++) vditer[i] = double(i);
    return vd;
  }

  // Same as foo(), but avoid copying on return.
  //
  std::auto_ptr<std::vector<double> > bar(int n)
  {
    std::auto_ptr<std::vector<double> > vdptr(new std::vector<double>(n));
    std::vector<double>::iterator vditer = vdptr->begin();
    for (int i = 0; i < n; i++) vditer[i] = double(10 * i);
    return vdptr;
  }
}

BOOST_PYTHON_MODULE_INIT(simple_vector)
{
  try
  {
    python::module_builder this_module("simple_vector");

    python::class_builder<std::vector<double>, vector_double_wrapper>
      vector_double(this_module, "vector_double");

    vector_double.def(python::constructor<>());
    vector_double.def(python::constructor<const int>());
    vector_double.def(python::constructor<python::tuple>());
    vector_double.def(&std::vector<double>::size, "__len__");
    vector_double.def(getitem, "__getitem__");
    vector_double.def(setitem, "__setitem__");
    vector_double.def(delitem, "__delitem__");
    vector_double.def(as_tuple, "as_tuple");

    this_module.def(foo, "foo");
    this_module.def(bar, "bar");
  }
  catch(...)
  {
    python::handle_exception(); // Deal with the exception for Python
  }
}

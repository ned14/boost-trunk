/* (C) Copyright Ralf W. Grosse-Kunstleve 2001. Permission to copy, use,
   modify, sell and distribute this software is granted provided this
   copyright notice appears in all copies. This software is provided
   "as is" without express or implied warranty, and with no claim as to
   its suitability for any purpose.

   Revision History:
     17 Apr 01 merged into boost CVS trunk (Ralf W. Grosse-Kunstleve)
*/

#define BOOST_PYTHON_SOURCE

# include <boost/python/cross_module.hpp>
namespace python = boost::python;
# include <stdio.h> // MSVC6.0SP4 does not know std::fprintf
# include <string.h> // MSVC6.0SP4 does not know std::strcmp

namespace
{

  PyObject* get_module_dict(const char* module_name)
  {
      python::ref module_obj(PyImport_ImportModule((char*) module_name));
      PyObject* module_dict = PyModule_GetDict(module_obj.get());
      if (module_dict == 0) python::throw_import_error();
      return module_dict;
  }
}

namespace boost { namespace python {

void BOOST_PYTHON_DECL throw_import_error()
{
    throw import_error();
}

void BOOST_PYTHON_DECL throw_export_error()
{
    throw export_error();
}

namespace detail
{
  BOOST_PYTHON_DECL const char* converters_attribute_name = "__converters__";

  BOOST_PYTHON_DECL void* import_converter_object(const std::string& module_name,
                                                  const std::string& py_class_name,
                                                  const std::string& attribute_name)
  {
      static std::string err;
      PyObject* module_dict = get_module_dict(const_cast<char*>(module_name.c_str()));
      PyObject* py_class = PyDict_GetItemString(module_dict, const_cast<char*>(py_class_name.c_str()));
      if (py_class == 0) {
          err = std::string("module ") + module_name + " has no attribute " + py_class_name;
          PyErr_SetString(PyExc_RuntimeError, const_cast<char*>(err.c_str()));
          python::throw_import_error();
      }
      python::ref c_obj(PyObject_GetAttrString(py_class, const_cast<char*>(attribute_name.c_str())), ref::null_ok);
      if (c_obj.get() == 0) {
          err = std::string("object ") + module_name + "." + py_class_name
              + " has no attribute " + attribute_name;
          PyErr_SetString(PyExc_RuntimeError, const_cast<char*>(err.c_str()));
          python::throw_import_error();
      }
      if (! PyCObject_Check(c_obj.get())) {
          err = std::string("object ") + module_name + "." + py_class_name + "."
              + attribute_name + " is not a PyCObject";
          PyErr_SetString(PyExc_RuntimeError, const_cast<char*>(err.c_str()));
          python::throw_import_error();
      }
      return PyCObject_AsVoidPtr(c_obj.get());
  }

  BOOST_PYTHON_DECL void check_export_converters_api(const int importing_major,
                                                     const int importing_minor,
                                                     const int imported_major,
                                                     const int imported_minor)
  {
      if (importing_major != imported_major) {
          // Python uses fprintf(stderr, ...) for API warnings.
          fprintf(stderr,
                  "Fatal: export_converters_api mismatch:"
                  " Importing module = %d.%d"
                  " Imported module = %d.%d\n",
                  importing_major, importing_minor,
                  imported_major, imported_minor);
          PyErr_SetString(PyExc_RuntimeError,
                          "Fatal: export_converters_api mismatch");
          throw_import_error();
      }
      if (importing_minor != imported_minor) {
          // Python uses fprintf(stderr, ...) for API warnings.
          fprintf(stderr,
                  "Warning: export_converters_api mismatch:"
                  " Importing module = %d.%d"
                  " Imported module = %d.%d\n",
                  importing_major, importing_minor,
                  imported_major, imported_minor);
      }
  }

}

}} // namespace boost::python::detail

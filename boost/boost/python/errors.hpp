//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#ifndef ERRORS_DWA052500_H_
# define ERRORS_DWA052500_H_

# include <boost/python/detail/config.hpp>
# include <boost/python/detail/wrap_python.hpp>
# include <boost/function.hpp>

namespace boost { namespace python {

struct BOOST_PYTHON_DECL error_already_set {};
struct BOOST_PYTHON_DECL argument_error : error_already_set {};

// Handles exceptions caught just before returning to Python code.
// Returns true iff an exception was caught.
BOOST_PYTHON_DECL bool handle_exception_impl(function0<void>);

template <class T>
bool handle_exception(T f)
{
    return handle_exception_impl(function0<void>(boost::ref(f)));
}

namespace detail { inline void rethrow() { throw; } }

inline void handle_exception()
{
    handle_exception(detail::rethrow);
}

BOOST_PYTHON_DECL PyObject* expect_non_null_impl(PyObject* x);

template <class T>
inline T* expect_non_null(T* x)
{
    return (T*)expect_non_null_impl((PyObject*)x);
}

BOOST_PYTHON_DECL void throw_argument_error();
BOOST_PYTHON_DECL void throw_error_already_set();

}} // namespace boost::python

#endif // ERRORS_DWA052500_H_

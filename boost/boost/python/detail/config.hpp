//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

//  Revision History:
//  04 Mar 01  Some fixes so it will compile with Intel C++ (Dave Abrahams)

#ifndef CONFIG_DWA052200_H_
# define CONFIG_DWA052200_H_

# include <boost/config.hpp>
# include <cstddef>

# ifdef BOOST_NO_OPERATORS_IN_NAMESPACE
   // A gcc bug forces some symbols into the global namespace
#  define BOOST_PYTHON_BEGIN_CONVERSION_NAMESPACE
#  define BOOST_PYTHON_END_CONVERSION_NAMESPACE
#  define BOOST_PYTHON_CONVERSION
#  define BOOST_PYTHON_IMPORT_CONVERSION(x) using ::x
# else
#  define BOOST_PYTHON_BEGIN_CONVERSION_NAMESPACE namespace boost { namespace python {
#  define BOOST_PYTHON_END_CONVERSION_NAMESPACE }} // namespace boost::python
#  define BOOST_PYTHON_CONVERSION boost::python
#  define BOOST_PYTHON_IMPORT_CONVERSION(x) void never_defined() // so we can follow the macro with a ';'
# endif

# if defined(BOOST_MSVC)
#  if _MSC_VER <= 1200
#   define BOOST_MSVC6_OR_EARLIER 1
#  endif

# pragma warning (disable : 4786)

# endif

// Work around the broken library implementation/strict ansi checking on some
// EDG-based compilers (e.g. alpha), which incorrectly warn that the result of
// offsetof() is not an integer constant expression.
# if defined(__DECCXX_VER) && __DECCXX_VER <= 60290024
#  define BOOST_OFFSETOF(s_name, s_member) \
        ((size_t)__INTADDR__(&(((s_name *)0)->s_member)))
# else
#  define BOOST_OFFSETOF(s_name, s_member) \
        offsetof(s_name, s_member)
# endif

// The STLport puts all of the standard 'C' library names in std (as far as the
// user is concerned), but without it you need a fix if you're using MSVC or
// Intel C++
# if defined(BOOST_MSVC_STD_ITERATOR)
#  define BOOST_CSTD_
# else
#  define BOOST_CSTD_ std
# endif

# ifndef BOOST_PYTHON_MODULE_INIT
#  if defined(_WIN32) || defined(__CYGWIN__)
#   define BOOST_PYTHON_MODULE_INIT(name) void init_module_##name(); extern "C" __declspec(dllexport) void init##name() { boost::python::handle_exception(&init_module_##name); } void init_module_##name()
#  else
#   define BOOST_PYTHON_MODULE_INIT(name) void init_module_##name(); extern "C" void init##name() { boost::python::handle_exception(&init_module_##name); } void init_module_##name()
#  endif
# endif 

/*****************************************************************************
 *
 *  Set up dll import/export options:
 *
 ****************************************************************************/

// backwards compatibility:
#ifdef BOOST_PYTHON_STATIC_LIB
#  define BOOST_PYTHON_STATIC_LINK
#endif

#if  defined(__MWERKS__) \
  || (defined(__DECCXX_VER) && __DECCXX_VER <= 60590002) \
  || (defined(__sgi) && defined(_COMPILER_VERSION) && _COMPILER_VERSION <= 730)
# define BOOST_PYTHON_NO_TEMPLATE_EXPORT
#endif

#if defined(__GNUC__)
# define BOOST_PYTHON_IMPORT_TEMPLATE_KEYWORD extern
# define BOOST_PYTHON_EXPORT_TEMPLATE_KEYWORD extern
#endif

// Handle default cases
#ifndef BOOST_PYTHON_IMPORT_TEMPLATE_KEYWORD
# ifdef _WIN32
#  define BOOST_PYTHON_IMPORT_TEMPLATE_KEYWORD extern
# else
#  define BOOST_PYTHON_IMPORT_TEMPLATE_KEYWORD
# endif 
#endif

#ifndef BOOST_PYTHON_EXPORT_TEMPLATE_KEYWORD
# define BOOST_PYTHON_EXPORT_TEMPLATE_KEYWORD
#endif 

#if defined(BOOST_PYTHON_DYNAMIC_LIB) && defined(_WIN32)
#  if defined(BOOST_PYTHON_SOURCE)
#     define BOOST_PYTHON_DECL __declspec(dllexport)
#     define BOOST_PYTHON_BUILD_DLL
#  else
#     define BOOST_PYTHON_DECL __declspec(dllimport)
#  endif
#endif

#ifndef BOOST_PYTHON_DECL
#  define BOOST_PYTHON_DECL
#endif

#ifndef BOOST_PYTHON_DECL_TEMPLATE
# ifndef BOOST_PYTHON_NO_TEMPLATE_EXPORT
#  define BOOST_PYTHON_DECL_TEMPLATE BOOST_PYTHON_DECL
# else
#  define BOOST_PYTHON_DECL_TEMPLATE
# endif
#endif

#if defined(BOOST_PYTHON_SOURCE)
# define BOOST_PYTHON_EXPORT BOOST_PYTHON_EXPORT_TEMPLATE_KEYWORD
#else
# define BOOST_PYTHON_EXPORT BOOST_PYTHON_IMPORT_TEMPLATE_KEYWORD
#endif

# ifndef BOOST_PYTHON_EXPORT_TEMPLATE
#  define  BOOST_PYTHON_EXPORT_TEMPLATE BOOST_PYTHON_EXPORT template
# endif

# define BOOST_PYTHON_EXPORT_TEMPLATE_CLASS BOOST_PYTHON_EXPORT template class BOOST_PYTHON_DECL

// Borland C++ Fix/error check:
#if defined(__BORLANDC__)
#  if (__BORLANDC__ == 0x550) || (__BORLANDC__ == 0x551)
      // problems with std::basic_string and dll RTL:
#     if defined(_RTLDLL) && defined(_RWSTD_COMPILE_INSTANTIATE)
#        ifdef BOOST_PYTHON_BUILD_DLL
#           error _RWSTD_COMPILE_INSTANTIATE must not be defined when building regex++ as a DLL
#        else
#           pragma warn defining _RWSTD_COMPILE_INSTANTIATE when linking to the DLL version of the RTL may produce memory corruption problems in std::basic_string, as a result of separate versions of basic_string's static data in the RTL and you're exe/dll: be warned!!
#        endif
#     endif
#     ifndef _RTLDLL
         // this is harmless for a static link:
#        define _RWSTD_COMPILE_INSTANTIATE
#     endif
#  endif
   //
   // VCL support:
   // if we're building a console app then there can't be any VCL (can there?)
#  if !defined(__CONSOLE__) && !defined(_NO_VCL)
#     define BOOST_PYTHON_USE_VCL
#  endif
#endif

#if defined(__sgi) && defined(_COMPILER_VERSION) && _COMPILER_VERSION <= 730
// Work around a compiler bug.
// boost::python::detail::function has to be seen by the compiler before the
// boost::function class template.
namespace boost { namespace python { namespace detail {
class function;
}}}
#endif

#endif // CONFIG_DWA052200_H_

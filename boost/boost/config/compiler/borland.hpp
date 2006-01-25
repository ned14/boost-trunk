//  (C) Copyright John Maddock 2001 - 2003.
//  (C) Copyright David Abrahams 2002 - 2003.
//  (C) Copyright Aleksey Gurtovoy 2002.
//  (C) Copyright Rene Rivera 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Borland C++ compiler setup:

#define BOOST_CXX_BORLANDC BOOST_VERSION_NUMBER(\
    (__BORLANDC__ & 0xFF00)>>8,\
    (__BORLANDC__ & 0xF0)>>4,\
    __BORLANDC__ & 0xF)

#if defined(_MSC_VER)
#   define BOOST_CXX_MSVC BOOST_VERSION_NUMBER(\
        _MSC_VER/100-6,\
        _MSC_VER-(_MSC_VER/100*100),\
        _MSC_FULL_VER-(_MSC_VER*10000))
#endif

// Version 5.0 and below:
#   if (BOOST_CXX_BORLANDC <= BOOST_VERSION_NUMBER(5,5,0))
// Borland C++Builder 4 and 5:
#     define BOOST_NO_MEMBER_TEMPLATE_FRIENDS
#     if (BOOST_CXX_BORLANDC == BOOST_VERSION_NUMBER(5,5,0))
// Borland C++Builder 5, command-line compiler 5.5:
#       define BOOST_NO_OPERATORS_IN_NAMESPACE
#     endif
#   endif

// Version 5.51 and below:
#if (BOOST_CXX_BORLANDC <= BOOST_VERSION_NUMBER(5,5,1))
#  define BOOST_NO_CV_SPECIALIZATIONS
#  define BOOST_NO_CV_VOID_SPECIALIZATIONS
#  define BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
#  define BOOST_NO_DEDUCED_TYPENAME
// workaround for missing WCHAR_MAX/WCHAR_MIN:
#include <climits>
#include <cwchar>
#ifndef WCHAR_MAX
#  define WCHAR_MAX 0xffff
#endif
#ifndef WCHAR_MIN
#  define WCHAR_MIN 0
#endif
#endif

// Version 7.0 (Kylix) and below:
#if (BOOST_CXX_BORLANDC <= BOOST_VERSION_NUMBER(5,7,0))
#  define BOOST_NO_SFINAE
#  define BOOST_NO_INTEGRAL_INT64_T
#  define BOOST_NO_DEPENDENT_NESTED_DERIVATIONS
#  define BOOST_NO_PRIVATE_IN_AGGREGATE
#  define BOOST_NO_USING_TEMPLATE
#  define BOOST_BCB_PARTIAL_SPECIALIZATION_BUG
#  define BOOST_NO_TEMPLATE_TEMPLATES
#  define BOOST_NO_USING_DECLARATION_OVERLOADS_FROM_TYPENAME_BASE
#  define BOOST_NO_MEMBER_TEMPLATE_FRIENDS
   // we shouldn't really need this - but too many things choke
   // without it, this needs more investigation:
#  define BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
#  define BOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL
#  define BOOST_NO_IS_ABSTRACT
#  ifdef NDEBUG
      // fix broken <cstring> so that Boost.test works:
#     include <cstring>
#     undef strcmp
#  endif
   // fix broken errno declaration:
#  include <errno.h>
#  ifndef errno
#     define errno errno
#  endif

//
// new bug in 5.61:
#if (BOOST_CXX_BORLANDC >= BOOST_VERSION_NUMBER(5,6,1)) && (BOOST_CXX_BORLANDC <= BOOST_VERSION_NUMBER(5,7,0))
   // this seems to be needed by the command line compiler, but not the IDE:
#  define BOOST_NO_MEMBER_FUNCTION_SPECIALIZATIONS
#endif

#  ifdef _WIN32
#     define BOOST_NO_SWPRINTF
#  elif defined(linux) || defined(__linux__) || defined(__linux)
      // we should really be able to do without this
      // but the wcs* functions aren't imported into std::
#     define BOOST_NO_STDC_NAMESPACE
      // _CPPUNWIND doesn't get automatically set for some reason:
#     pragma defineonoption BOOST_CPPUNWIND -x
#  endif
#endif

//
// Post 0x561 we have long long and stdint.h:
#if (BOOST_CXX_BORLANDC >= BOOST_VERSION_NUMBER(5,6,1))
#  ifndef __NO_LONG_LONG
#     define BOOST_HAS_LONG_LONG
#  endif
   // On non-Win32 platforms let the platform config figure this out:
#  ifdef _WIN32
#      define BOOST_HAS_STDINT_H
#  endif
#endif

// Borland C++Builder 6 defaults to using STLPort.  If _USE_OLD_RW_STL is
// defined, then we have 0x560 or greater with the Rogue Wave implementation
// which presumably has the std::DBL_MAX bug.
#if ((BOOST_CXX_BORLANDC >= BOOST_VERSION_NUMBER(5,5,0)) && (BOOST_CXX_BORLANDC < BOOST_VERSION_NUMBER(5,6,0)) || defined(_USE_OLD_RW_STL)
// <climits> is partly broken, some macros define symbols that are really in
// namespace std, so you end up having to use illegal constructs like
// std::DBL_MAX, as a fix we'll just include float.h and have done with:
#include <float.h>
#endif
//
// __int64:
//
#if (BOOST_CXX_BORLANDC >= BOOST_VERSION_NUMBER(5,3,0)) && !defined(__STRICT_ANSI__)
#  define BOOST_HAS_MS_INT64
#endif
//
// check for exception handling support:
//
#if !defined(_CPPUNWIND) && !defined(BOOST_CPPUNWIND) && !defined(__EXCEPTIONS)
#  define BOOST_NO_EXCEPTIONS
#endif
//
// all versions have a <dirent.h>:
//
#ifndef __STRICT_ANSI__
#  define BOOST_HAS_DIRENT_H
#endif
//
// all versions support __declspec:
//
#ifndef __STRICT_ANSI__
#  define BOOST_HAS_DECLSPEC
#endif
//
// ABI fixing headers:
//
#if (BOOST_CXX_BORLANDC < BOOST_VERSION_NUMBER(6,0,0))
// not implemented for version 6 compiler yet
#ifndef BOOST_ABI_PREFIX
#  define BOOST_ABI_PREFIX "boost/config/abi/borland_prefix.hpp"
#endif
#ifndef BOOST_ABI_SUFFIX
#  define BOOST_ABI_SUFFIX "boost/config/abi/borland_suffix.hpp"
#endif
#endif
//
// Disable Win32 support in ANSI mode:
//
#if (BOOST_CXX_BORLANDC < BOOST_VERSION_NUMBER(6,0,0))
#  pragma defineonoption BOOST_DISABLE_WIN32 -A
#elif defined(__STRICT_ANSI__)
#  define BOOST_DISABLE_WIN32
#endif
//
// MSVC compatibility mode does some nasty things:
// TODO: look up if this doesn't apply to the whole 12xx range
//
#if defined(BOOST_CXX_MSVC) && (BOOST_CXX_MSVC <= BOOST_VERSION_NUMBER(6,0,0))
#  define BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
#  define BOOST_NO_VOID_RETURNS
#endif

#define BOOST_COMPILER "Borland C++ version " BOOST_STRINGIZE(__BORLANDC__)

//
// versions check:
// we don't support Borland prior to version 5.4:
#if (BOOST_CXX_BORLANDC < BOOST_VERSION_NUMBER(5,4,0))
#  error "Compiler not supported or configured - please reconfigure"
#endif
//
// last known and checked version is 1536 (Builder X preview)
// Or 0x580 (Borland C++ Builder 6 2006 Preview):
#if (BOOST_CXX_BORLANDC > BOOST_VERSION_NUMBER(6,0,0)) \
    || ((BOOST_CXX_BORLANDC > BOOST_VERSION_NUMBER(5,8,0)) && (BOOST_CXX_BORLANDC < BOOST_VERSION_NUMBER(6,0,0)))
#  if defined(BOOST_ASSERT_CONFIG)
#     error "Unknown compiler version - please run the configure tests and report the results"
#  else
#     pragma message( "Unknown compiler version - please run the configure tests and report the results")
#  endif
#endif

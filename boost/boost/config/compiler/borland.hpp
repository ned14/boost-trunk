//  (C) Copyright Boost.org 2001. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version.

//  Borland C++ compiler setup:

// Version 5.0 and below:
#   if __BORLANDC__ <= 0x0550
// Borland C++Builder 4 and 5:
#     define BOOST_NO_MEMBER_TEMPLATE_FRIENDS
#     if __BORLANDC__ == 0x0550
// Borland C++Builder 5, command-line compiler 5.5:
#       define BOOST_NO_OPERATORS_IN_NAMESPACE
#     endif
#   endif

// Version 5.51 and below:
#if (__BORLANDC__ <= 0x551)
#  define BOOST_NO_CV_SPECIALIZATIONS
#  define BOOST_NO_CV_VOID_SPECIALIZATIONS
#  define BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
#endif

// Version 7.0 (Kylix) and below:
#if (__BORLANDC__ <= 0x570) || !defined(BOOST_STRICT_CONFIG)
#  define BOOST_NO_INTEGRAL_INT64_T
#  define BOOST_NO_DEPENDENT_NESTED_DERIVATIONS
#  define BOOST_NO_PRIVATE_IN_AGGREGATE
#  define BOOST_NO_USING_TEMPLATE
#  define BOOST_BCB_PARTIAL_SPECIALIZATION_BUG
#  define BOOST_NO_TEMPLATE_TEMPLATES
   // we shouldn't really need this - but too many things choke
   // without it, this needs more investigation:
#  define BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS

//
// new bug in 5.61:
#if __BORLANDC__ >= 0x561
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
#if __BORLANDC__ >= 0x561
#  define BOOST_HAS_LONG_LONG
#  define BOOST_HAS_STDINT_H
#endif

// Borland C++Builder 6 defaults to using STLPort.  If _USE_OLD_RW_STL is
// defined, then we have 0x560 or greater with the Rogue Wave implementation
// which presumably has the std::DBL_MAX bug.
#if ((__BORLANDC__ >= 0x550) && (__BORLANDC__ < 0x560)) || defined(_USE_OLD_RW_STL)
// <climits> is partly broken, some macros define symbols that are really in
// namespace std, so you end up having to use illegal constructs like
// std::DBL_MAX, as a fix we'll just include float.h and have done with:
#include <float.h>
#endif
//
// __int64:
//
#if __BORLANDC__ >= 0x530
#  define BOOST_HAS_MS_INT64
#endif
//
// check for exception handling support:
//
#if !defined(_CPPUNWIND) && !defined(BOOST_CPPUNWIND)
#  define BOOST_NO_EXCEPTIONS
#endif
//
// all versions have a <dirent.h>:
//
#define BOOST_HAS_DIRENT_H
//
// Disable Win32 support in ANSI mode:
//
#pragma defineonoption BOOST_DISABLE_WIN32 -A

#define BOOST_COMPILER "Borland C++ version " BOOST_STRINGIZE(__BORLANDC__)

//
// versions check:
// we don't support Borland prior to version 5.4:
#if __BORLANDC__ < 0x540
#  error "Compiler not supported or configured - please reconfigure"
#endif
//
// last known and checked version is 5.6:
#if (__BORLANDC__ > 0x570)
#  if defined(BOOST_ASSERT_CONFIG)
#     error "Unknown compiler version - please run the configure tests and report the results"
#  else
#     pragma message( "Unknown compiler version - please run the configure tests and report the results")
#  endif
#endif






//  (C) Copyright John Maddock 2001.
//  (C) Copyright Peter Dimov 2001.
//  (C) Copyright Jens Maurer 2001.
//  (C) Copyright David Abrahams 2002 - 2003.
//  (C) Copyright Aleksey Gurtovoy 2002 - 2003.
//  (C) Copyright Guillaume Melquiond 2002 - 2003.
//  (C) Copyright Beman Dawes 2003.
//  (C) Copyright Martin Wille 2003.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Intel compiler setup:
#if defined(__INTEL_COMPILER)
#   define BOOST_CXX_INTELC_ __INTEL_COMPILER
#elif defined(__ICL)
#   define BOOST_CXX_INTELC __ICL
#elif defined(__ICC)
#   define BOOST_CXX_INTELC __ICC
#elif defined(__ECC)
#   define BOOST_CXX_INTELC __ECC
#endif

#define BOOST_CXX_INTELC BOOST_VERSION_NUMBER(\
    BOOST_CXX_INTELC_/100,\
    (BOOST_CXX_INTELC_-BOOST_CXX_INTELC_/100*100)/10,\
    BOOST_CXX_INTELC_-BOOST_CXX_INTELC_/10*10)

#if defined(_MSC_VER)
#   define BOOST_CXX_MSVC BOOST_VERSION_NUMBER(\
        _MSC_VER/100-6,\
        _MSC_VER-(_MSC_VER/100*100),\
        _MSC_FULL_VER-(_MSC_VER*10000))
#endif

#if defined(__GNUC__)
#   define BOOST_CXX_GNUC BOOST_VERSION_NUMBER(__GNUC__,__GNUC_MINOR__,__GNUC_PATCHLEVEL__)
#endif

#include "boost/config/compiler/common_edg.hpp"

#define BOOST_COMPILER "Intel C++ version " BOOST_STRINGIZE(BOOST_CXX_INTELC_)

#undef BOOST_CXX_INTELC_

// === These should be removed when the BOOST_CXX_INTELC def is used...

#if defined(__INTEL_COMPILER)
#  define BOOST_INTEL_CXX_VERSION __INTEL_COMPILER
#elif defined(__ICL)
#  define BOOST_INTEL_CXX_VERSION __ICL
#elif defined(__ICC)
#  define BOOST_INTEL_CXX_VERSION __ICC
#elif defined(__ECC)
#  define BOOST_INTEL_CXX_VERSION __ECC
#endif

#define BOOST_INTEL BOOST_INTEL_CXX_VERSION

#if defined(_WIN32) || defined(_WIN64)
#  define BOOST_INTEL_WIN BOOST_INTEL
#else
#  define BOOST_INTEL_LINUX BOOST_INTEL
#endif

// ===

#if (BOOST_CXX_INTELC <= BOOST_VERSION_NUMBER(5,0,0)) && defined(BOOST_CXX_MSVC)
#  define BOOST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS
#  define BOOST_NO_TEMPLATE_TEMPLATES
#endif

#if (BOOST_CXX_INTELC <= BOOST_VERSION_NUMBER(6,0,0))

#  if defined(BOOST_CXX_MSVC) && (BOOST_CXX_MSVC <= BOOST_VERSION_NUMBER(7,0,0)) // added check for <= VC 7 (Peter Dimov)

// Boost libraries assume strong standard conformance unless otherwise
// indicated by a config macro. As configured by Intel, the EDG front-end
// requires certain compiler options be set to achieve that strong conformance.
// Particularly /Qoption,c,--arg_dep_lookup (reported by Kirk Klobe & Thomas Witt)
// and /Zc:wchar_t,forScope. See boost-root/tools/build/intel-win32-tools.jam for
// details as they apply to particular versions of the compiler. When the
// compiler does not predefine a macro indicating if an option has been set,
// this config file simply assumes the option has been set.
// Thus BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP will not be defined, even if
// the compiler option is not enabled.

#     define BOOST_NO_SWPRINTF
#  endif

// Void returns, 64 bit integrals don't work when emulating VC 6 (Peter Dimov)

#  if defined(BOOST_CXX_MSVC) && (BOOST_CXX_MSVC <= BOOST_VERSION_NUMBER(6,0,0))
#     define BOOST_NO_VOID_RETURNS
#     define BOOST_NO_INTEGRAL_INT64_T
#  endif

#endif

#if (BOOST_CXX_INTELC <= BOOST_VERSION_NUMBER(7,1,0)) && defined(_WIN32)
#  define BOOST_NO_POINTER_TO_MEMBER_TEMPLATE_PARAMETERS
#endif

// See http://aspn.activestate.com/ASPN/Mail/Message/boost/1614864
#if (BOOST_CXX_INTELC < BOOST_VERSION_NUMBER(6,0,0))
#  define BOOST_NO_INTRINSIC_WCHAR_T
#else
// We should test the macro _WCHAR_T_DEFINED to check if the compiler
// supports wchar_t natively. *BUT* there is a problem here: the standard
// headers define this macro if they typedef wchar_t. Anyway, we're lucky
// because they define it without a value, while Intel C++ defines it
// to 1. So we can check its value to see if the macro was defined natively
// or not.
// Under UNIX, the situation is exactly the same, but the macro _WCHAR_T
// is used instead.
#  if ((_WCHAR_T_DEFINED + 0) == 0) && ((_WCHAR_T + 0) == 0)
#    define BOOST_NO_INTRINSIC_WCHAR_T
#  endif
#endif

#if defined(BOOST_CXX_GNUC) && !defined(BOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL)
//
// Figure out when Intel is emulating this gcc bug
// (All Intel versions prior to 9.0.26, and versions
// later than that if they are set up to emulate gcc 3.2
// or earlier):
//
#  if (BOOST_CXX_GNUC <= BOOST_VERSION_NUMBER(3,2,0)) || (BOOST_CXX_INTELC < BOOST_VERSION_NUMBER(9,0,0)) || (__INTEL_COMPILER_BUILD_DATE < 20050912)
#     define BOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL
#  endif
#endif

//
// Verify that we have actually got BOOST_NO_INTRINSIC_WCHAR_T
// set correctly, if we don't do this now, we will get errors later
// in type_traits code among other things, getting this correct
// for the Intel compiler is actually remarkably fragile and tricky:
//
#if defined(BOOST_NO_INTRINSIC_WCHAR_T)
#include <cwchar>
template< typename T > struct assert_no_intrinsic_wchar_t;
template<> struct assert_no_intrinsic_wchar_t<wchar_t> { typedef void type; };
// if you see an error here then you need to unset BOOST_NO_INTRINSIC_WCHAR_T
// where it is defined above:
typedef assert_no_intrinsic_wchar_t<unsigned short>::type assert_no_intrinsic_wchar_t_;
#else
template< typename T > struct assert_intrinsic_wchar_t;
template<> struct assert_intrinsic_wchar_t<wchar_t> {};
// if you see an error here then define BOOST_NO_INTRINSIC_WCHAR_T on the command line:
template<> struct assert_intrinsic_wchar_t<unsigned short> {};
#endif

#if defined(BOOST_CXX_MSVC) && (BOOST_CXX_MSVC >= BOOST_VERSION_NUMBER(4,0,0))
#  if (BOOST_CXX_MSVC >= BOOST_VERSION_NUMBER(6,0,0))
#     define BOOST_HAS_MS_INT64
#  endif
#  define BOOST_NO_SWPRINTF
#elif defined(_WIN32)
#  define BOOST_DISABLE_WIN32
#endif

// I checked version 6.0 build 020312Z, it implements the NRVO.
// Correct this as you find out which version of the compiler
// implemented the NRVO first.  (Daniel Frey)
#if (BOOST_CXX_INTELC >= BOOST_VERSION_NUMBER(6,0,0))
#  define BOOST_HAS_NRVO
#endif

//
// versions check:
// we don't support Intel prior to version 5.0:
#if (BOOST_CXX_INTELC < BOOST_VERSION_NUMBER(5,0,0))
#  error "Compiler not supported or configured - please reconfigure"
#endif
//
// last known and checked version:
#if (BOOST_CXX_VERSION > BOOST_VERSION_NUMBER(9,1,0))
#  if defined(BOOST_ASSERT_CONFIG)
#     error "Unknown compiler version - please run the configure tests and report the results"
#  elif defined(BOOST_CXX_MSVC)
#     pragma message("Unknown compiler version - please run the configure tests and report the results")
#  endif
#endif

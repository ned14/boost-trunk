//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Darin Adler 2001 - 2002. 
//  (C) Copyright Jens Maurer 2001 - 2002. 
//  (C) Copyright Beman Dawes 2001 - 2003. 
//  (C) Copyright Douglas Gregor 2002. 
//  (C) Copyright David Abrahams 2002 - 2003. 
//  (C) Copyright Synge Todo 2003. 
//  (C) Copyright Rene Rivera 2006.
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  GNU C++ compiler setup:

#define BOOST_CXX_GNUC BOOST_VERSION_NUMBER(__GNUC__,__GNUC_MINOR__,__GNUC_PATCHLEVEL__)

#if (BOOST_CXX_GNUC < BOOST_VERSION_NUMBER(3,0,0))
#   if (BOOST_CXX_GNUC >= BOOST_VERSION(2,91,0)) (BOOST_CXX_GNUC <= BOOST_VERSION_NUMBER(2,92,0))
       // egcs 1.1 won't parse shared_ptr.hpp without this:
#      define BOOST_NO_AUTO_PTR
#   endif
#   if (BOOST_CXX_GNUC < BOOST_VERION_NUMBER(2,95,0))
      //
      // Prior to gcc 2.95 member templates only partly
      // work - define BOOST_MSVC6_MEMBER_TEMPLATES
      // instead since inline member templates mostly work.
      //
#     define BOOST_NO_MEMBER_TEMPLATES
#     if (BOOST_CXX_GNUC >= BOOST_VERSION_NUMBER(2,9,0))
#       define BOOST_MSVC6_MEMBER_TEMPLATES
#     endif
#   endif

#   if (BOOST_CXX_GNUC < BOOST_VERSION_NUMBER(2,96,0))
#     define BOOST_NO_SFINAE
#   endif

#   if (BOOST_CXX_GNUC < BOOST_VERSION_NUMBER(2,98,0))
#     define BOOST_NO_MEMBER_TEMPLATE_FRIENDS
#     define BOOST_NO_OPERATORS_IN_NAMESPACE
#   endif

#   define BOOST_NO_USING_DECLARATION_OVERLOADS_FROM_TYPENAME_BASE
#   define BOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL
#   define BOOST_NO_IS_ABSTRACT
#elif (BOOST_CXX_GNUC >= BOOST_VERSION_NUMBER(3,0,0)) && (BOOST_CXX_GNUC < BOOST_VERSION_NUMBER(4,0,0))
   //
   // gcc-3.x problems:
   //
   // Bug specific to gcc 3.1 and 3.2:
   //
#  if (BOOST_CXX_GNUC >= BOOST_VERSION_NUMBER(3,1,0)) && (BOOST_CXX_GNUC < BOOST_VERSION_NUMBER(3,3,0))
#     define BOOST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS
#  endif
#  if (BOOST_CXX_GNUC < BOOST_VERSION_NUMBER(3,4,0))
#     define BOOST_NO_IS_ABSTRACT
#  endif
#endif

#ifndef __EXCEPTIONS
# define BOOST_NO_EXCEPTIONS
#endif


//
// Threading support: Turn this on unconditionally here (except for
// those platforms where we can know for sure). It will get turned off again
// later if no threading API is detected.
//
#if !defined(__MINGW32__) && !defined(linux) && !defined(__linux) && !defined(__linux__)
# define BOOST_HAS_THREADS
#endif 

//
// gcc has "long long"
//
#define BOOST_HAS_LONG_LONG

//
// gcc implements the named return value optimization since version 3.1
//
#if (BOOST_CXX_GNUC >= BOOST_VERSION_NUMBER(3,1,0))
#define BOOST_HAS_NRVO
#endif

#define BOOST_COMPILER "GNU C++ version " __VERSION__

//
// versions check:
// we don't know gcc prior to version 2.90:
#if (BOOST_CXX_GNUC < BOOST_VERSION_NUMBER(2,90,0))
#  error "Compiler not configured - please reconfigure"
#endif
//
// last known and checked version is 4.0 (Pre-release):
#if (BOOST_CXX_GNUC >= BOOST_VERSION_NUMBER(4,1,0))
#  if defined(BOOST_ASSERT_CONFIG)
#     error "Unknown compiler version - please run the configure tests and report the results"
#  else
// we don't emit warnings here anymore since there are no defect macros defined for
// gcc post 3.4, so any failures are gcc regressions...
//#     warning "Unknown compiler version - please run the configure tests and report the results"
#  endif
#endif

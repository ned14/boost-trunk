//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Jens Maurer 2001. 
//  (C) Copyright David Abrahams 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Rogue Wave std lib:

#if !defined(__STD_RWCOMPILER_H__) && !defined(_RWSTD_VER)
#  include <utility>
#  if !defined(__STD_RWCOMPILER_H__) && !defined(_RWSTD_VER)
#     error This is not the Rogue Wave standard library
#  endif
#endif
//
// figure out a consistent version number:
//
#ifndef _RWSTD_VER
#  define BOOST_RWSTD_VER 0x010000
#elif _RWSTD_VER < 0x010000
#  define BOOST_RWSTD_VER (_RWSTD_VER << 8)
#else
#  define BOOST_RWSTD_VER _RWSTD_VER
#endif

#ifndef _RWSTD_VER
#  define BOOST_STDLIB "Rogue Wave standard library version (Unknown version)"
#else
#  define BOOST_STDLIB "Rogue Wave standard library version " BOOST_STRINGIZE(_RWSTD_VER)
#endif

//
// Prior to version 2.2.0 the primary template for std::numeric_limits
// does not have compile time constants, even though specializations of that
// template do:
//
#if BOOST_RWSTD_VER < 0x020200
#  define BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
#endif

// Sun CC 5.6 adds long long specialization, but does not change the
// library version number
#if BOOST_RWSTD_VER <= 0x020101 && (!defined(__SUNPRO_CC) || (__SUNPRO_CC < 0x560))
#  define BOOST_NO_LONG_LONG_NUMERIC_LIMITS
# endif

//
// Borland version of numeric_limits lacks __int64 specialisation:
//
#ifdef __BORLANDC__
#  define BOOST_NO_MS_INT64_NUMERIC_LIMITS
#endif

//
// No std::iterator if it can't figure out default template args:
//
#if defined(_RWSTD_NO_SIMPLE_DEFAULT_TEMPLATES) || defined(RWSTD_NO_SIMPLE_DEFAULT_TEMPLATES) || (BOOST_RWSTD_VER < 0x020000)
#  define BOOST_NO_STD_ITERATOR
#endif

//
// No iterator traits without partial specialization:
//
#if defined(_RWSTD_NO_CLASS_PARTIAL_SPEC) || defined(RWSTD_NO_CLASS_PARTIAL_SPEC)
#  define BOOST_NO_STD_ITERATOR_TRAITS
#endif

//
// Prior to version 2.0, std::auto_ptr was buggy, and there were no
// new-style iostreams, and no conformant std::allocator:
//
#if (BOOST_RWSTD_VER < 0x020000)
#  define BOOST_NO_AUTO_PTR
#  define BOOST_NO_STRINGSTREAM
#  define BOOST_NO_STD_ALLOCATOR
#  define BOOST_NO_STD_LOCALE
#endif

//
// No template iterator constructors without member template support:
//
#if defined(RWSTD_NO_MEMBER_TEMPLATES) || defined(_RWSTD_NO_MEMBER_TEMPLATES)
#  define BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS
#endif

//
// RW defines _RWSTD_ALLOCATOR if the allocator is conformant and in use
// (the or _HPACC_ part is a hack - the library seems to define _RWSTD_ALLOCATOR
// on HP aCC systems even though the allocator is in fact broken):
//
#if !defined(_RWSTD_ALLOCATOR) || (defined(__HP_aCC) && __HP_aCC <= 33100)
#  define BOOST_NO_STD_ALLOCATOR
#endif

//
// If we have a std::locale, we still may not have std::use_facet:
//
#if defined(_RWSTD_NO_TEMPLATE_ON_RETURN_TYPE) && !defined(BOOST_NO_STD_LOCALE)
#  define BOOST_NO_STD_USE_FACET
#  define BOOST_HAS_TWO_ARG_USE_FACET
#endif

//
// There's no std::distance prior to version 2, or without
// partial specialization support:
//
#if (BOOST_RWSTD_VER < 0x020000) || defined(_RWSTD_NO_CLASS_PARTIAL_SPEC)
    #define BOOST_NO_STD_DISTANCE
#endif

//
// Some versions of the rogue wave library don't have assignable
// OutputIterators:
//
#if BOOST_RWSTD_VER < 0x020100
#  define BOOST_NO_STD_OUTPUT_ITERATOR_ASSIGN
#endif




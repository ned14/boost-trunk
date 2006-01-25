//  (C) Copyright John Maddock 2001. 
//  (C) Copyright Douglas Gregor 2001. 
//  (C) Copyright Peter Dimov 2001. 
//  (C) Copyright Aleksey Gurtovoy 2003. 
//  (C) Copyright Beman Dawes 2003. 
//  (C) Copyright Jens Maurer 2003. 
//  Copyright Rene Rivera 2006.
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Comeau C++ compiler setup:

#define BOOST_CXX_COMO BOOST_VERSION_NUMBER(\
    (__COMO_VERSION__ & 0xF000)>>12,\
    (__COMO_VERSION__ & 0xF00)>>8,\
    __COMO_VERSION__ & 0xFF)

#if defined(_MSC_VER)
#   define BOOST_CXX_MSVC BOOST_VERSION_NUMBER(\
        _MSC_VER/100-6,\
        _MSC_VER-(_MSC_VER/100*100),\
        _MSC_FULL_VER-(_MSC_VER*10000))
#endif

#include "boost/config/compiler/common_edg.hpp"

#if (BOOST_CXX_COMO <= BOOST_VERSION_NUMBER(4,2,45))

#  if defined(BOOST_CXX_MSVC) && (BOOST_CXX_MSVC <= BOOST_VERSION_NUMBER(7,0,0))
#     if (BOOST_CXX_MSVC > BOOST_VERSION_NUMBER(0,1,0))
         // only set this in non-strict mode:
#        define BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
#     endif
#  endif

// Void returns don't work when emulating VC 6 (Peter Dimov)
// TODO: look up if this doesn't apply to the whole 12xx range
#  if defined(BOOST_CXX_MSVC) && (BOOST_CXX_MSVC < BOOST_VERSION_NUMBER(7,0,0))
#     define BOOST_NO_VOID_RETURNS
#  endif

#endif  // version 4.2.45

//
// enable __int64 support in VC emulation mode
//
#  if defined(BOOST_CXX_MSVC) && (BOOST_CXX_MSVC >= BOST_VERSION_NUMBER(6,0,0))
#     define BOOST_HAS_MS_INT64
#  endif

#define BOOST_COMPILER "Comeau compiler version " BOOST_STRINGIZE(__COMO_VERSION__)

//
// versions check:
// we don't know Comeau prior to version 4.2.45:
#if (BOOST_CXX_COMO < BOOST_VERSION_NUMBER(4,2,45))
#  error "Compiler not configured - please reconfigure"
#endif
//
// last known and checked version is 4.2.45:
#if (BOOST_CXX_COMO > BOOST_VERSION_NUMBER(4,2,45))
#  if defined(BOOST_ASSERT_CONFIG)
#     error "Unknown compiler version - please run the configure tests and report the results"
#  endif
#endif

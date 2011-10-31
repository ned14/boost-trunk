//  boost/chrono/config.hpp  -------------------------------------------------//

//  Copyright Beman Dawes 2003, 2006, 2008
//  Copyright 2009-2011 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/chrono for documentation.

#ifndef BOOST_CHRONO_CONFIG_HPP
#define BOOST_CHRONO_CONFIG_HPP

#include <boost/config.hpp>

#if defined(BOOST_CHRONO_SOURCE) && !defined(BOOST_USE_WINDOWS_H)
#define BOOST_USE_WINDOWS_H
#endif

//  BOOST_CHRONO_POSIX_API, BOOST_CHRONO_MAC_API, or BOOST_CHRONO_WINDOWS_API
//  can be defined by the user to specify which API should be used

#if defined(BOOST_CHRONO_WINDOWS_API)
# warning Boost.Chrono will use the Windows API
#elif defined(BOOST_CHRONO_MAC_API)
# warning Boost.Chrono will use the Mac API
#elif defined(BOOST_CHRONO_POSIX_API)
# warning Boost.Chrono will use the POSIX API
#endif

# if defined( BOOST_CHRONO_WINDOWS_API ) && defined( BOOST_CHRONO_POSIX_API )
#   error both BOOST_CHRONO_WINDOWS_API and BOOST_CHRONO_POSIX_API are defined
# elif defined( BOOST_CHRONO_WINDOWS_API ) && defined( BOOST_CHRONO_MAC_API )
#   error both BOOST_CHRONO_WINDOWS_API and BOOST_CHRONO_MAC_API are defined
# elif defined( BOOST_CHRONO_MAC_API ) && defined( BOOST_CHRONO_POSIX_API )
#   error both BOOST_CHRONO_MAC_API and BOOST_CHRONO_POSIX_API are defined
# elif !defined( BOOST_CHRONO_WINDOWS_API ) && !defined( BOOST_CHRONO_MAC_API ) && !defined( BOOST_CHRONO_POSIX_API )
#   if (defined(_WIN32) || defined(__WIN32__) || defined(WIN32))
#     define BOOST_CHRONO_WINDOWS_API
#   elif defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)
#     define BOOST_CHRONO_MAC_API
#   else
#     define BOOST_CHRONO_POSIX_API
#   endif
# endif

# if defined( BOOST_CHRONO_WINDOWS_API )
#   ifndef UNDER_CE
#     define BOOST_CHRONO_HAS_PROCESS_CLOCKS
#   endif
#   define BOOST_CHRONO_HAS_CLOCK_STEADY
#   define BOOST_CHRONO_HAS_THREAD_CLOCK
#   define BOOST_CHRONO_THREAD_CLOCK_IS_STEADY true
# endif

# if defined( BOOST_CHRONO_MAC_API )
#   define BOOST_CHRONO_HAS_PROCESS_CLOCKS
#   define BOOST_CHRONO_HAS_CLOCK_STEADY
#   define BOOST_CHRONO_THREAD_CLOCK_IS_STEADY true
# endif

# if defined( BOOST_CHRONO_POSIX_API )
#   define BOOST_CHRONO_HAS_PROCESS_CLOCKS
#   include <time.h>  //to check for CLOCK_REALTIME and CLOCK_MONOTONIC and _POSIX_THREAD_CPUTIME
#   if defined(CLOCK_REALTIME)
#     if defined(CLOCK_MONOTONIC)
#        define BOOST_CHRONO_HAS_CLOCK_STEADY
#     endif
#   else
#     error <time.h> does not supply CLOCK_REALTIME
#   endif
#   if defined(_POSIX_THREAD_CPUTIME) && !defined(BOOST_DISABLE_THREADS)
#     define BOOST_CHRONO_HAS_THREAD_CLOCK
#     define BOOST_CHRONO_THREAD_CLOCK_IS_STEADY true
#   endif
#   if defined(CLOCK_THREAD_CPUTIME_ID) && !defined(BOOST_DISABLE_THREADS)
#     define BOOST_CHRONO_HAS_THREAD_CLOCK
#     define BOOST_CHRONO_THREAD_CLOCK_IS_STEADY true
#   endif
#   if defined(sun) || defined(__sun)
#     undef BOOST_CHRONO_HAS_THREAD_CLOCK
#     undef BOOST_CHRONO_THREAD_CLOCK_IS_STEADY
#   endif
# endif

#if defined(BOOST_CHRONO_THREAD_DISABLED) && defined(BOOST_CHRONO_HAS_THREAD_CLOCK)
#undef BOOST_CHRONO_HAS_THREAD_CLOCK
#undef BOOST_CHRONO_THREAD_CLOCK_IS_STEADY
#endif

// deprecated i/o
#define BOOST_CHRONO_IO_V1_DONT_PROVIDE_DEPRECATED
#define BOOST_CHRONO_IO_USE_XALLOC
#define BOOST_CHRONO_USES_DURATION_PUT
//#define BOOST_CHRONO_IS_LOCALIZABLE_VIRTUAL
//#define BOOST_CHRONO_IS_LOCALIZABLE_TRANSLATE

// unicode support  ------------------------------//

#if defined(BOOST_NO_UNICODE_LITERALS) || defined(BOOST_NO_CHAR16_T) || defined(BOOST_NO_CHAR32_T)
//~ #define BOOST_CHRONO_HAS_UNICODE_SUPPORT
#else
#define BOOST_CHRONO_HAS_UNICODE_SUPPORT 1
#endif

#if ! defined BOOST_NOEXCEPT
#if defined(BOOST_NO_NOEXCEPT)
#define BOOST_NOEXCEPT
#else
#define BOOST_NOEXCEPT noexcept
#endif
#endif

#ifdef BOOST_CHRONO_HEADER_ONLY
#define BOOST_CHRONO_INLINE inline
#define BOOST_CHRONO_STATIC
#define BOOST_CHRONO_DECL

#else
#define BOOST_CHRONO_INLINE
#define BOOST_CHRONO_STATIC static

//  enable dynamic linking on Windows  ---------------------------------------//

// we need to import/export our code only if the user has specifically
// asked for it by defining either BOOST_ALL_DYN_LINK if they want all boost
// libraries to be dynamically linked, or BOOST_CHRONO_DYN_LINK
// if they want just this one to be dynamically liked:
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_CHRONO_DYN_LINK)
// export if this is our own source, otherwise import:
#ifdef BOOST_CHRONO_SOURCE
# define BOOST_CHRONO_DECL BOOST_SYMBOL_EXPORT
#else
# define BOOST_CHRONO_DECL BOOST_SYMBOL_IMPORT
#endif  // BOOST_CHRONO_SOURCE
#endif  // DYN_LINK
//
// if BOOST_CHRONO_DECL isn't defined yet define it now:
#ifndef BOOST_CHRONO_DECL
#define BOOST_CHRONO_DECL
#endif

//#define  BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING

//  enable automatic library variant selection  ------------------------------//

#if !defined(BOOST_CHRONO_SOURCE) && !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_CHRONO_NO_LIB)
//
// Set the name of our library; this will get undef'ed by auto_link.hpp
// once it's done with it:
//
#define BOOST_LIB_NAME boost_chrono
//
// If we're importing code from a dll, then tell auto_link.hpp about it:
//
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_CHRONO_DYN_LINK)
#  define BOOST_DYN_LINK
#endif
//
// And include the header that does the work:
//
#include <boost/config/auto_link.hpp>
#endif  // auto-linking disabled
#endif // BOOST_CHRONO_HEADER_ONLY
#endif // BOOST_CHRONO_CONFIG_HPP

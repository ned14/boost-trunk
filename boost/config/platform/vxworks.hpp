//  (C) Copyright Dustin Spicuzza 2009.
//      Adapted to vxWorks 6.9 by Peter Brockamp 2012.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Since WRS does not yet properly support boost under vxWorks
//  and this file was badly outdated, but I was keen on using it,
//  I patched boost myself to make things work. This has been tested
//  and adapted by me for vxWorks 6.9 *only*, as I'm lacking access
//  to earlier 6.X versions! The only thing I know for sure is that
//  very old versions of vxWorks (namely everything below 6.x) are
//  absolutely unable to use boost. This is mainly due to the completely
//  outdated libraries and ancient compiler (GCC 2.96 or worse). Do
//  not even think of getting this to work, a miserable failure will
//  be guaranteed!
//  Equally, this file has been tested for RTPs (Real Time Processes)
//  only, not for DKMs (Downloadable Kernel Modules). These two types
//  of executables differ largely in the available functionality of
//  the C-library, STL, and so on. A DKM uses a library similar to those
//  of vxWorks 5.X - with all its limitations and incompatibilities
//  in respect to ANSI C++ and STL. So probably there might be problems
//  with the usage of boost from DKMs. WRS or any voluteers are free to
//  prove the opposite!

// Block out all versions before vxWorks 6.x, as these don't work:
// Include header with the vxWorks version information and query them
#include <version.h>
#if !defined(_WRS_VXWORKS_MAJOR) || (_WRS_VXWORKS_MAJOR < 6)
#  error "The vxWorks version you're using is so badly outdated,\
          it doesn't work at all with boost, sorry, no chance!"
#endif

// Handle versions above 5.X but below 6.9
#if (_WRS_VXWORKS_MAJOR == 6) && (_WRS_VXWORKS_MINOR < 9)
// TODO: Starting from what version does vxWorks work with boost?
// We can't reasonably insert a #warning "" as a user hint here,
// as this will show up with every file including some boost header,
// badly bugging the user... So for the time being we just leave it.
#endif

// vxWorks specific config options:
// --------------------------------
#define BOOST_PLATFORM "vxWorks"

// Special behaviour for DKMs:
#ifdef _WRS_KERNEL
  // DKMs do not have the <cwchar>-header,
  // but apparently they do have an intrinsic wchar_t meanwhile!
#  define BOOST_NO_CWCHAR

  // Lots of wide-functions and -headers are unavailable for DKMs as well:
#  define BOOST_NO_CWCTYPE
#  define BOOST_NO_SWPRINTF
#  define BOOST_NO_STD_WSTRING
#  define BOOST_NO_STD_WSTREAMBUF
#endif

// Generally available headers:
#define BOOST_HAS_UNISTD_H
#define BOOST_HAS_STDINT_H
#define BOOST_HAS_DIRENT_H
#define BOOST_HAS_SLIST

// vxWorks does not have installed an iconv-library by default,
// so unfortunately no Unicode support from scratch is available!
// Thus, instead it is suggested to switch to ICU, as this seems
// to be the most complete and portable option...
#define BOOST_LOCALE_WITH_ICU

// Generally available functionality:
#define BOOST_HAS_THREADS
#define BOOST_HAS_NANOSLEEP
#define BOOST_HAS_CLOCK_GETTIME
#define BOOST_HAS_MACRO_USE_FACET

// Generally unavailable functionality, delivered by boost's test function:
//#define BOOST_NO_DEDUCED_TYPENAME // Commented this out, boost's test gives an errorneous result!
#define BOOST_NO_CXX11_EXTERN_TEMPLATE
#define BOOST_NO_CXX11_VARIADIC_MACROS

// Generally available threading API's:
#define BOOST_HAS_PTHREADS
#define BOOST_HAS_SCHED_YIELD
#define BOOST_HAS_SIGACTION

// Functionality available for RTPs only:
#ifdef __RTP__
//#  define BOOST_HAS_GETTIMEOFDAY
#  define BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE
#  define BOOST_HAS_LOG1P
#  define BOOST_HAS_EXPM1
#endif

// Functionality available for DKMs only:
#ifdef _WRS_KERNEL
  // Luckily, at the moment there seems to be none!
#endif

// These #defines allow posix_features to work, since vxWorks doesn't
// #define them itself for DKMs (for RTPs on the contrary it does):
#ifdef _WRS_KERNEL
#  ifndef _POSIX_TIMERS
#    define _POSIX_TIMERS  1
#  endif
#  ifndef _POSIX_THREADS
#    define _POSIX_THREADS 1
#  endif
#endif

// vxWorks doesn't work with asio serial ports:
#define BOOST_ASIO_DISABLE_SERIAL_PORT
// TODO: The problem here seems to bee that vxWorks uses its own, very specific
//       ways to handle serial ports, incompatible with POSIX or anything...
//       Maybe a specific implementation would be possible, but until the
//       straight need arises... This implementation would presumably consist
//       of some vxWorks specific ioctl-calls, etc. Any voluteers?

// vxWorks-around: <time.h> #defines CLOCKS_PER_SEC as sysClkRateGet() but
//                 miserably fails to #include the required <sysLib.h> to make
//                 sysClkRateGet() available! So we manually include it here.
#ifdef __RTP__
#  include <sysLib.h>
#endif

// vxWorks-around: In <stdint.h> the macros INT32_C(), UINT32_C(), INT64_C() and
//                 UINT64_C() are defined errorneously, yielding not a signed/
//                 unsigned long/long long type, but a signed/unsigned int/long
//                 type. Eventually this leads to compile errors in ratio_fwd.hpp,
//                 when trying to define several constants which do not fit into a
//                 long type! We correct them here by redefining.
#include <cstdint>

// Some macro-magic to do the job
#define VX_JOIN(X, Y)     VX_DO_JOIN(X, Y)
#define VX_DO_JOIN(X, Y)  VX_DO_JOIN2(X, Y)
#define VX_DO_JOIN2(X, Y) X##Y

// Correctly setup the macros
#undef  INT32_C
#undef  UINT32_C
#undef  INT64_C
#undef  UINT64_C
#define INT32_C(x)  VX_JOIN(x, L)
#define UINT32_C(x) VX_JOIN(x, UL)
#define INT64_C(x)  VX_JOIN(x, LL)
#define UINT64_C(x) VX_JOIN(x, ULL)

// #include Libraries required for the following function adaption
#include <ioLib.h>
#include <tickLib.h>

// Use C-linkage for the following helper functions
extern "C" {

// vxWorks-around: The required functions getrlimit() and getrlimit() are missing.
//                 But we have the similar functions getprlimit() and setprlimit(),
//                 which may serve the purpose.
//                 Problem: The vxWorks-documentation regarding these functions
//                 doesn't deserve its name! It isn't documented what the first two
//                 parameters idtype and id mean, so we must fall back to an educated
//                 guess - null, argh... :-/

// TODO: getprlimit() and setprlimit() do exist for RTPs only, for whatever reason.
//       Thus for DKMs there would have to be another implementation.
#ifdef __RTP__
  inline int getrlimit(int resource, struct rlimit *rlp){
    return getprlimit(0, 0, resource, rlp);
  }

  inline int setrlimit(int resource, const struct rlimit *rlp){
    return setprlimit(0, 0, resource, const_cast<struct rlimit*>(rlp));
  }
#endif

// vxWorks has ftruncate() only, so we do simulate truncate():
inline int truncate(const char *p, off_t l){
  int fd = open(p, O_WRONLY);
  if (fd == -1){
    errno = EACCES;
    return -1;
  }
  if (ftruncate(fd, l) == -1){
    close(fd);
    errno = EACCES;
    return -1;
  }
  return close(fd);
}

// Fake symlink handling by dummy functions:
inline int symlink(const char*, const char*){
  // vxWorks has no symlinks -> always return an error!
  errno = EACCES;
  return -1;
}

inline ssize_t readlink(const char*, char*, size_t){
  // vxWorks has no symlinks -> always return an error!
  errno = EACCES;
  return -1;
}

// vxWorks does provide neither struct tms nor function times()!
// We implement an empty dummy-function, simply setting the user
// and system time to the half of thew actual system ticks-value
// and the child user and system time to 0.
// Rather ugly but at least it suppresses compiler errors...
// Unfortunately, this of course *does* have an severe impact on
// dependant libraries, actually this is chrono only! Here it will
// not be possible to correctly use user and system times! But
// as vxWorks is lacking the ability to calculate user and system
// process times there seems to be no other possible solution.
struct tms{
  clock_t tms_utime;  // User CPU time
  clock_t tms_stime;  // System CPU time
  clock_t tms_cutime; // User CPU time of terminated child processes
  clock_t tms_cstime; // System CPU time of terminated child processes
};

inline clock_t times(struct tms *t){
  clock_t ticks = static_cast<clock_t>(tickGet());
  t->tms_utime  = ticks/2U;
  t->tms_stime  = ticks/2U;
  t->tms_cutime = 0;
  t->tms_cstime = 0;
  return ticks;
}

} // extern "C"

// Put the selfmade functions into the std-namespace, just in case
namespace std {
# ifdef __RTP__
    using ::getrlimit;
    using ::setrlimit;
# endif
  using ::truncate;
  using ::symlink;
  using ::readlink;
  using ::times;
}

// Some more macro-magic:
// vxWorks-around: Some functions are not present or broken in vxWorks
//                 but may be patched to life via helper macros...

// Include signal.h which contains a typo to be corrected here
#include <signal.h>

#define getpagesize()    sysconf(_SC_PAGESIZE)         // getpagesize is deprecated anyway!
#ifndef S_ISSOCK
#  define S_ISSOCK(mode) ((mode & S_IFMT) == S_IFSOCK) // Is file a socket?
#endif
#define lstat(p, b)      stat(p, b)                    // lstat() == stat(), as vxWorks has no symlinks!
#ifndef FPE_FLTINV
#  define FPE_FLTINV     (FPE_FLTSUB+1)                // vxWorks has no FPE_FLTINV, so define one as a dummy
#endif
#if !defined(BUS_ADRALN) && defined(BUS_ADRALNR)
#  define BUS_ADRALN     BUS_ADRALNR                   // Correct a supposed typo in vxWorks' <signal.h>?
#endif
//typedef int              locale_t;                     // locale_t is a POSIX-extension, currently unpresent in vxWorks!

// #include boilerplate code:
#include <boost/config/posix_features.hpp>

// vxWorks lies about XSI conformance, there is no nl_types.h:
#undef BOOST_HAS_NL_TYPES_H

// vxWorks blatantly lies about implementing gettimeofday:
// Though it even declares a prototype in sys/time.h, linking it fails!
#undef BOOST_HAS_GETTIMEOFDAY

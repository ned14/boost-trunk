//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2007. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_PTR_WRKRND_HPP
#define BOOST_INTERPROCESS_PTR_WRKRND_HPP

#include <boost/interprocess/detail/config_begin.hpp>

#if !(defined BOOST_WINDOWS) || (defined BOOST_DISABLE_WIN32)
   #if defined(_POSIX_THREAD_PROCESS_SHARED) && (_POSIX_THREAD_PROCESS_SHARED - 0 > 0)
   #if !defined(__CYGWIN__)
      #define BOOST_INTERPROCESS_POSIX_PROCESS_SHARED
   #endif
   #endif

   #if defined(_POSIX_BARRIERS) && (_POSIX_BARRIERS - 0 > 0)
      #define BOOST_INTERPROCESS_POSIX_BARRIERS
   #endif   //

   #if defined(_POSIX_SEMAPHORES) && (_POSIX_SEMAPHORES - 0 > 0)
      #define BOOST_INTERPROCESS_POSIX_SEMAPHORES
   #endif

   #if ((defined _V6_ILP32_OFFBIG)  &&(_V6_ILP32_OFFBIG   - 0 > 0)) ||\
       ((defined _V6_LP64_OFF64)    &&(_V6_LP64_OFF64     - 0 > 0)) ||\
       ((defined _V6_LPBIG_OFFBIG)  &&(_V6_LPBIG_OFFBIG   - 0 > 0)) ||\
       ((defined _XBS5_ILP32_OFFBIG)&&(_XBS5_ILP32_OFFBIG - 0 > 0)) ||\
       ((defined _XBS5_LP64_OFF64)  &&(_XBS5_LP64_OFF64   - 0 > 0)) ||\
       ((defined _XBS5_LPBIG_OFFBIG)&&(_XBS5_LPBIG_OFFBIG - 0 > 0)) ||\
       ((defined _FILE_OFFSET_BITS) &&(_FILE_OFFSET_BITS  - 0 >= 64))||\
       ((defined _FILE_OFFSET_BITS) &&(_FILE_OFFSET_BITS  - 0 >= 64))
      #define BOOST_INTERPROCESS_UNIX_64_BIT_OR_BIGGER_OFF_T
   #else
   #endif

   #if defined(_POSIX_SHARED_MEMORY_OBJECTS) && (_POSIX_SHARED_MEMORY_OBJECTS - 0 > 0)
      #define BOOST_INTERPROCESS_POSIX_SHARED_MEMORY_OBJECTS
   #endif

   #if defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS - 0 > 0)
      #define BOOST_INTERPROCESS_POSIX_TIMEOUTS
   #endif

#endif

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 2)
// C++0x features are only enabled when -std=c++0x or -std=gnu++0x are
// passed on the command line, which in turn defines
// __GXX_EXPERIMENTAL_CXX0X__. Note: __GXX_EXPERIMENTAL_CPP0X__ is
// defined by some very early development versions of GCC 4.3; we will
// remove this part of the check in the near future.
#  if defined(__GXX_EXPERIMENTAL_CPP0X__) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#    define BOOST_INTERPROCESS_RVALUE_REFERENCE
#    define BOOST_INTERPROCESS_VARIADIC_TEMPLATES
#  endif
#endif

#if defined(BOOST_INTERPROCESS_RVALUE_REFERENCE) || defined(BOOST_INTERPROCESS_VARIADIC_TEMPLATES)
#define BOOST_INTERPROCESS_PERFECT_FORWARDING
#endif
/*
namespace boost {
namespace interprocess {
namespace workaround{

//////////////////////////////////////////////////
//                                              //
//    We want generally const_shm_ptr to inherit//
//    from iterator class but for void this     //
//    doesn't work, so we must inherit from     //
//    other class.                              //
//                                              //
//////////////////////////////////////////////////

//Empty class
struct empty_type{};

template<class T>
struct random_it 
: public std::iterator<std::random_access_iterator_tag, 
                         T, std::ptrdiff_t, T*, T&> 
{
   typedef const T*           const_pointer;
   typedef const T&           const_reference;
};

template<> struct random_it<void>
{
   typedef void *             pointer;
   typedef const void *       const_pointer;
   typedef empty_type&        reference;
   typedef const empty_type&  const_reference;
   typedef void               value_type;
   typedef empty_type         difference_type;
   typedef empty_type         iterator_category;
};

template<> struct random_it<const void>
{
   typedef const void *       pointer;
   typedef const void *       const_pointer;
   typedef const empty_type & reference;
   typedef const empty_type & const_reference;
   typedef const void         value_type;
   typedef empty_type         difference_type;
   typedef empty_type         iterator_category;
};

template<> struct random_it<volatile void>
{
   typedef volatile void *       pointer;
   typedef const volatile void * const_pointer;
   typedef empty_type&           reference;
   typedef const empty_type&     const_reference;
   typedef volatile void         value_type;
   typedef empty_type            difference_type;
   typedef empty_type            iterator_category;
};

template<> struct random_it<const volatile void>
{
   typedef const volatile void *    pointer;
   typedef const volatile void *    const_pointer;
   typedef const empty_type &       reference;
   typedef const empty_type &       const_reference;
   typedef const volatile void      value_type;
   typedef empty_type               difference_type;
   typedef empty_type               iterator_category;
};

}  //namespace workaround
}  //namespace interprocess {
}  //namespace boost {
*/
#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_PTR_WRKRND_HPP

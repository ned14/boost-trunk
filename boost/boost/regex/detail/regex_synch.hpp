/*
 *
 * Copyright (c) 1998-2000
 * Dr John Maddock
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Dr John Maddock makes no representations
 * about the suitability of this software for any purpose.
 * It is provided "as is" without express or implied warranty.
 *
 */

 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         regex_synch.hpp
  *   VERSION      3.12
  *   DESCRIPTION: Thread synchronisation for regex code.
  *                Note this is an internal header file included
  *                by regex.hpp, do not include on its own.
  */

#ifndef BOOST_REGEX_SYNCH_HPP
#define BOOST_REGEX_SYNCH_HPP

#ifndef BOOST_REGEX_CONFIG_HPP
#include <boost/regex/detail/regex_config.hpp>
#endif

#if defined(BOOST_RE_PLATFORM_W32) && defined(BOOST_RE_THREADS)
#include <windows.h>
#endif

#if !defined(BOOST_RE_PLATFORM_W32) && defined(BOOST_RE_THREADS) 
#if defined(__BEOS__)
#include <OS.h>
#include <cassert>
#else
#include <pthread.h>
#endif
#endif


namespace boost{
   namespace re_detail{

#ifdef __BORLANDC__
   #pragma option push -a4 -b -Ve -pc
#endif

void BOOST_RE_CALL re_init_threads();
void BOOST_RE_CALL re_free_threads();

#ifdef BOOST_RE_THREADS

#ifndef BOOST_RE_PLATFORM_W32
#ifdef __BEOS__

typedef sem_id CRITICAL_SECTION;

inline void BOOST_RE_CALL InitializeCriticalSection(CRITICAL_SECTION* ps)
{
    *ps = create_sem(1, "regex++");
    assert(*ps > 0);
}

inline void BOOST_RE_CALL DeleteCriticalSection(CRITICAL_SECTION* ps)
{
    int t = delete_sem(*ps);
    assert(t == B_NO_ERROR);
}

inline void BOOST_RE_CALL EnterCriticalSection(CRITICAL_SECTION* ps)
{
   status_t t = acquire_sem(*ps);
   assert(t == B_NO_ERROR);
}

inline void BOOST_RE_CALL LeaveCriticalSection(CRITICAL_SECTION* ps)
{
    status_t t = release_sem(*ps);
    assert(t == B_NO_ERROR);
}

#else // __BEOS__

typedef pthread_mutex_t CRITICAL_SECTION;

inline void BOOST_RE_CALL InitializeCriticalSection(CRITICAL_SECTION* ps)
{
   pthread_mutex_init(ps, 0);
}

inline void BOOST_RE_CALL DeleteCriticalSection(CRITICAL_SECTION* ps)
{
   pthread_mutex_destroy(ps);
}

inline void BOOST_RE_CALL EnterCriticalSection(CRITICAL_SECTION* ps)
{
   pthread_mutex_lock(ps);
}

inline void BOOST_RE_CALL LeaveCriticalSection(CRITICAL_SECTION* ps)
{
   pthread_mutex_unlock(ps);
}
#endif // __BEOS__
#endif

template <class Lock>
class lock_guard
{
   typedef Lock lock_type;
public:
   lock_guard(lock_type& m, bool aq = true)
      : mut(m), owned(false){ acquire(aq); }

   ~lock_guard()
   { acquire(false); }

   void BOOST_RE_CALL acquire(bool aq = true)
   {
      if(aq && !owned)
      {
         mut.acquire(true);
         owned = true;
      }
      else if(!aq && owned)
      {
         mut.acquire(false);
         owned = false;
      }
   }
private:
   lock_type& mut;
   bool owned;
   // VC6 warning suppression:
   lock_guard& operator=(const lock_guard&);
};


class critical_section
{
public:
   critical_section()
   { InitializeCriticalSection(&hmutex);}

   critical_section(const critical_section&)
   { InitializeCriticalSection(&hmutex);}

   const critical_section& BOOST_RE_CALL operator=(const critical_section&)
   {return *this;}

   ~critical_section()
   {DeleteCriticalSection(&hmutex);}

private:

   void BOOST_RE_CALL acquire(bool aq)
   { if(aq) EnterCriticalSection(&hmutex);
      else LeaveCriticalSection(&hmutex);
   }

   CRITICAL_SECTION hmutex;

public:
   typedef lock_guard<critical_section> ro_guard;
   typedef lock_guard<critical_section> rw_guard;

   friend class lock_guard<critical_section>;
};

inline bool BOOST_RE_CALL operator==(const critical_section&, const critical_section&)
{
   return false;
}

inline bool BOOST_RE_CALL operator<(const critical_section&, const critical_section&)
{
   return true;
}

typedef lock_guard<critical_section> cs_guard;

BOOST_RE_IX_DECL extern critical_section* p_re_lock;
BOOST_RE_IX_DECL extern unsigned int re_lock_count;

#define BOOST_RE_GUARD(inst) boost::re_detail::critical_section::rw_guard g(inst);

#else  // BOOST_RE_THREADS

#define BOOST_RE_GUARD(inst)

#endif // BOOST_RE_THREADS

#ifdef __BORLANDC__
  #pragma option pop
#endif

} // namespace re_detail
} // namespace boost

#endif // sentry






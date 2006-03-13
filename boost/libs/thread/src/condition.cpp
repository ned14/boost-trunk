// Copyright (C) 2001-2003
// William E. Kempf
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation.  William E. Kempf makes no representations
// about the suitability of this software for any purpose.
// It is provided "as is" without express or implied warranty.

#include <boost/thread/detail/config.hpp>

#ifndef BOOST_HAS_WINTHREADS
#include <boost/thread/condition.hpp>
#include <boost/thread/xtime.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/exceptions.hpp>
#include <boost/limits.hpp>
#include <cassert>
#include "timeconv.inl"

#if defined(BOOST_HAS_PTHREADS)
#   include <errno.h>
#elif defined(BOOST_HAS_MPTASKS)
#   include <MacErrors.h>
#   include "mac/init.hpp"
#   include "mac/safe.hpp"
#endif

namespace boost {

namespace detail {

#if defined(BOOST_HAS_PTHREADS)
condition_impl::condition_impl()
{
    int res = 0;
    res = pthread_cond_init(&m_condition, 0);
    if (res != 0)
        throw thread_resource_error();
}

condition_impl::~condition_impl()
{
    int res = 0;
    res = pthread_cond_destroy(&m_condition);
    assert(res == 0);
}

void condition_impl::notify_one()
{
    int res = 0;
    res = pthread_cond_signal(&m_condition);
    assert(res == 0);
}

void condition_impl::notify_all()
{
    int res = 0;
    res = pthread_cond_broadcast(&m_condition);
    assert(res == 0);
}

void condition_impl::do_wait(pthread_mutex_t* pmutex)
{
    int res = 0;
    res = pthread_cond_wait(&m_condition, pmutex);
    assert(res == 0);
}

bool condition_impl::do_timed_wait(const xtime& xt, pthread_mutex_t* pmutex)
{
    timespec ts;
    to_timespec(xt, ts);

    int res = 0;
    res = pthread_cond_timedwait(&m_condition, pmutex, &ts);
    assert(res == 0 || res == ETIMEDOUT);

    return res != ETIMEDOUT;
}
#elif defined(BOOST_HAS_MPTASKS)

using threads::mac::detail::safe_enter_critical_region;
using threads::mac::detail::safe_wait_on_semaphore;

condition_impl::condition_impl()
    : m_gone(0), m_blocked(0), m_waiting(0)
{
    threads::mac::detail::thread_init();

    OSStatus lStatus = noErr;

    lStatus = MPCreateSemaphore(1, 1, &m_gate);
    if(lStatus == noErr)
        lStatus = MPCreateSemaphore(ULONG_MAX, 0, &m_queue);

    if(lStatus != noErr || !m_gate || !m_queue)
    {
        if (m_gate)
        {
            lStatus = MPDeleteSemaphore(m_gate);
            assert(lStatus == noErr);
        }
        if (m_queue)
        {
            lStatus = MPDeleteSemaphore(m_queue);
            assert(lStatus == noErr);
        }

        throw thread_resource_error();
    }
}

condition_impl::~condition_impl()
{
    OSStatus lStatus = noErr;
    lStatus = MPDeleteSemaphore(m_gate);
    assert(lStatus == noErr);
    lStatus = MPDeleteSemaphore(m_queue);
    assert(lStatus == noErr);
}

void condition_impl::notify_one()
{
    unsigned signals = 0;

    OSStatus lStatus = noErr;
    lStatus = safe_enter_critical_region(m_mutex, kDurationForever,
        m_mutex_mutex);
    assert(lStatus == noErr);

    if (m_waiting != 0) // the m_gate is already closed
    {
        if (m_blocked == 0)
        {
            lStatus = MPExitCriticalRegion(m_mutex);
            assert(lStatus == noErr);
            return;
        }

        ++m_waiting;
        --m_blocked;
    }
    else
    {
        lStatus = safe_wait_on_semaphore(m_gate, kDurationForever);
        assert(lStatus == noErr);
        if (m_blocked > m_gone)
        {
            if (m_gone != 0)
            {
                m_blocked -= m_gone;
                m_gone = 0;
            }
            signals = m_waiting = 1;
            --m_blocked;
        }
        else
        {
            lStatus = MPSignalSemaphore(m_gate);
            assert(lStatus == noErr);
        }

        lStatus = MPExitCriticalRegion(m_mutex);
        assert(lStatus == noErr);

        while (signals)
        {
            lStatus = MPSignalSemaphore(m_queue);
            assert(lStatus == noErr);
            --signals;
        }
    }
}

void condition_impl::notify_all()
{
    unsigned signals = 0;

    OSStatus lStatus = noErr;
    lStatus = safe_enter_critical_region(m_mutex, kDurationForever,
        m_mutex_mutex);
    assert(lStatus == noErr);

    if (m_waiting != 0) // the m_gate is already closed
    {
        if (m_blocked == 0)
        {
            lStatus = MPExitCriticalRegion(m_mutex);
            assert(lStatus == noErr);
            return;
        }

        m_waiting += (signals = m_blocked);
        m_blocked = 0;
    }
    else
    {
        lStatus = safe_wait_on_semaphore(m_gate, kDurationForever);
        assert(lStatus == noErr);
        if (m_blocked > m_gone)
        {
            if (m_gone != 0)
            {
                m_blocked -= m_gone;
                m_gone = 0;
            }
            signals = m_waiting = m_blocked;
            m_blocked = 0;
        }
        else
        {
            lStatus = MPSignalSemaphore(m_gate);
            assert(lStatus == noErr);
        }

        lStatus = MPExitCriticalRegion(m_mutex);
        assert(lStatus == noErr);

        while (signals)
        {
            lStatus = MPSignalSemaphore(m_queue);
            assert(lStatus == noErr);
            --signals;
        }
    }
}

void condition_impl::enter_wait()
{
    OSStatus lStatus = noErr;
    lStatus = safe_wait_on_semaphore(m_gate, kDurationForever);
    assert(lStatus == noErr);
    ++m_blocked;
    lStatus = MPSignalSemaphore(m_gate);
    assert(lStatus == noErr);
}

void condition_impl::do_wait()
{
    OSStatus lStatus = noErr;
    lStatus = safe_wait_on_semaphore(m_queue, kDurationForever);
    assert(lStatus == noErr);

    unsigned was_waiting=0;
    unsigned was_gone=0;

    lStatus = safe_enter_critical_region(m_mutex, kDurationForever,
        m_mutex_mutex);
    assert(lStatus == noErr);
    was_waiting = m_waiting;
    was_gone = m_gone;
    if (was_waiting != 0)
    {
        if (--m_waiting == 0)
        {
            if (m_blocked != 0)
            {
                lStatus = MPSignalSemaphore(m_gate); // open m_gate
                assert(lStatus == noErr);
                was_waiting = 0;
            }
            else if (m_gone != 0)
                m_gone = 0;
        }
    }
    else if (++m_gone == ((std::numeric_limits<unsigned>::max)() / 2))
    {
        // timeout occured, normalize the m_gone count
        // this may occur if many calls to wait with a timeout are made and
        // no call to notify_* is made
        lStatus = safe_wait_on_semaphore(m_gate, kDurationForever);
        assert(lStatus == noErr);
        m_blocked -= m_gone;
        lStatus = MPSignalSemaphore(m_gate);
        assert(lStatus == noErr);
        m_gone = 0;
    }
    lStatus = MPExitCriticalRegion(m_mutex);
    assert(lStatus == noErr);

    if (was_waiting == 1)
    {
        for (/**/ ; was_gone; --was_gone)
        {
            // better now than spurious later
            lStatus = safe_wait_on_semaphore(m_queue, kDurationForever);
            assert(lStatus == noErr);
        }
        lStatus = MPSignalSemaphore(m_gate);
        assert(lStatus == noErr);
    }
}

bool condition_impl::do_timed_wait(const xtime& xt)
{
    int milliseconds;
    to_duration(xt, milliseconds);

    OSStatus lStatus = noErr;
    lStatus = safe_wait_on_semaphore(m_queue, milliseconds);
    assert(lStatus == noErr || lStatus == kMPTimeoutErr);

    bool ret = (lStatus == noErr);

    unsigned was_waiting=0;
    unsigned was_gone=0;

    lStatus = safe_enter_critical_region(m_mutex, kDurationForever,
        m_mutex_mutex);
    assert(lStatus == noErr);
    was_waiting = m_waiting;
    was_gone = m_gone;
    if (was_waiting != 0)
    {
        if (!ret) // timeout
        {
            if (m_blocked != 0)
                --m_blocked;
            else
                ++m_gone; // count spurious wakeups
        }
        if (--m_waiting == 0)
        {
            if (m_blocked != 0)
            {
                lStatus = MPSignalSemaphore(m_gate); // open m_gate
                assert(lStatus == noErr);
                was_waiting = 0;
            }
            else if (m_gone != 0)
                m_gone = 0;
        }
    }
    else if (++m_gone == ((std::numeric_limits<unsigned>::max)() / 2))
    {
        // timeout occured, normalize the m_gone count
        // this may occur if many calls to wait with a timeout are made and
        // no call to notify_* is made
        lStatus = safe_wait_on_semaphore(m_gate, kDurationForever);
        assert(lStatus == noErr);
        m_blocked -= m_gone;
        lStatus = MPSignalSemaphore(m_gate);
        assert(lStatus == noErr);
        m_gone = 0;
    }
    lStatus = MPExitCriticalRegion(m_mutex);
    assert(lStatus == noErr);

    if (was_waiting == 1)
    {
        for (/**/ ; was_gone; --was_gone)
        {
            // better now than spurious later
            lStatus = safe_wait_on_semaphore(m_queue, kDurationForever);
            assert(lStatus == noErr);
        }
        lStatus = MPSignalSemaphore(m_gate);
        assert(lStatus == noErr);
    }

    return ret;
}
#endif

} // namespace detail

} // namespace boost

#endif

// Change Log:
//    8 Feb 01  WEKEMPF Initial version.
//   22 May 01  WEKEMPF Modified to use xtime for time outs.
//    3 Jan 03  WEKEMPF Modified for DLL implementation.

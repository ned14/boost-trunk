// autoreset event for generic semaphores
//
// Copyright (C) 2013 Tim Blechmann
// Copyright (C) 2013 Andrey Semashev
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SYNC_DETAIL_EVENT_EVENT_AUTORESET_SEMAPHORE_HPP
#define BOOST_SYNC_DETAIL_EVENT_EVENT_AUTORESET_SEMAPHORE_HPP

#include <cstddef>
#include <boost/cstdint.hpp>

#include <boost/sync/detail/config.hpp>
#include <boost/sync/detail/atomic.hpp>
#include <boost/sync/detail/pause.hpp>
#include <boost/sync/semaphore.hpp>

#include <boost/sync/detail/header.hpp>

namespace boost {

namespace sync {

BOOST_SYNC_DETAIL_OPEN_ABI_NAMESPACE {

class auto_reset_event
{
    BOOST_DELETED_FUNCTION(auto_reset_event(auto_reset_event const&))
    BOOST_DELETED_FUNCTION(auto_reset_event& operator= (auto_reset_event const&));

public:
    auto_reset_event() :
        m_state(0)
    {
    }

    void post() BOOST_NOEXCEPT
    {
        int32_t old_state = m_state.load(detail::atomic_ns::memory_order_acquire);
        if (old_state >= 0)
        {
            for (;;)
            {
                if (m_state.compare_exchange_weak(old_state, old_state - 1, detail::atomic_ns::memory_order_release, detail::atomic_ns::memory_order_acquire))
                {
                    m_sem.post();
                    return; // avoid unnecessary fence
                }

                if (old_state < 0)
                    break; // someone else has set the auto_reset_event with no waiters

                detail::pause();
            }
        }

        detail::atomic_ns::atomic_thread_fence(detail::atomic_ns::memory_order_release);
    }

    void wait()
    {
        m_state.fetch_add(1, detail::atomic_ns::memory_order_acquire);
        m_sem.wait();
    }

    bool try_wait()
    {
        m_state.fetch_add(1, detail::atomic_ns::memory_order_acquire);

        const bool wait_successful = m_sem.try_wait();
        if (wait_successful)
            return true;

        m_state.fetch_add(-1, detail::atomic_ns::memory_order_relaxed);
        return false;
    }

    template <typename Duration>
    bool try_wait_for(const Duration & duration)
    {
        m_state.fetch_add(1, detail::atomic_ns::memory_order_acquire);

        const bool wait_successful = m_sem.try_wait_for(duration);
        if (wait_successful)
            return true;

        m_state.fetch_add(-1, detail::atomic_ns::memory_order_relaxed);
        return false;
    }

    template <typename Timepoint>
    bool try_wait_until(const Timepoint & timeout )
    {
        m_state.fetch_add(1, detail::atomic_ns::memory_order_acquire);

        const bool wait_successful = m_sem.try_wait_until(timeout);
        if (wait_successful)
            return true;

        m_state.fetch_add(-1, detail::atomic_ns::memory_order_relaxed);
        return false;
    }

private:
    semaphore m_sem;
    detail::atomic_ns::atomic<int32_t> m_state;
};

} // namespace abi

} // namespace sync

} // namespace boost

#include <boost/sync/detail/footer.hpp>

#endif // BOOST_SYNC_DETAIL_EVENT_EVENT_AUTORESET_SEMAPHORE_HPP

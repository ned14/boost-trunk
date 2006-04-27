// (C) Copyright 2006 Anthony Williams
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/unit_test.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/xtime.hpp>
#include <boost/thread/read_write_mutex.hpp>
#include "util.inl"

#define CHECK_LOCKED_VALUE_EQUAL(mutex_name,value,expected_value)    \
    {                                                                \
        boost::mutex::scoped_lock lock(mutex_name);                  \
        BOOST_CHECK_EQUAL(value,expected_value);                     \
    }


namespace
{
    template<typename lock_type>
    class locking_thread
    {
        boost::read_write_mutex& rw_mutex;
        unsigned& unblocked_count;
        boost::mutex& unblocked_count_mutex;
        boost::mutex& finish_mutex;
    public:
        locking_thread(boost::read_write_mutex& rw_mutex_,
                       unsigned& unblocked_count_,
                       boost::mutex& unblocked_count_mutex_,
                       boost::mutex& finish_mutex_):
            rw_mutex(rw_mutex_),
            unblocked_count(unblocked_count_),
            unblocked_count_mutex(unblocked_count_mutex_),
            finish_mutex(finish_mutex_)
        {}
        
        void operator()()
        {
            // acquire lock
            lock_type lock(rw_mutex);
            
            // increment count to show we're unblocked
            {
                boost::mutex::scoped_lock ublock(unblocked_count_mutex);
                ++unblocked_count;
            }
            
            // wait to finish
            boost::mutex::scoped_lock finish_lock(finish_mutex);
        }
    };
    
}


void test_multiple_readers()
{
    unsigned const number_of_threads=100;
    
    boost::thread_group pool;

    boost::read_write_mutex rw_mutex;
    unsigned unblocked_count=0;
    boost::mutex unblocked_count_mutex;
    boost::mutex finish_mutex;
    boost::mutex::scoped_lock finish_lock(finish_mutex);
    
    for(unsigned i=0;i<number_of_threads;++i)
    {
        pool.create_thread(locking_thread<boost::read_write_mutex::scoped_read_lock>(rw_mutex,unblocked_count,unblocked_count_mutex,finish_mutex));
    }

    boost::thread::sleep(delay(1));

    CHECK_LOCKED_VALUE_EQUAL(unblocked_count_mutex,unblocked_count,number_of_threads);

    finish_lock.unlock();

    pool.join_all();
}


boost::unit_test_framework::test_suite* init_unit_test_suite(int, char*[])
{
    boost::unit_test_framework::test_suite* test =
        BOOST_TEST_SUITE("Boost.Threads: read_write_mutex test suite");

    test->add(BOOST_TEST_CASE(&test_multiple_readers));

    return test;
}

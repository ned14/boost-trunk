
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "bind_processor.hpp"

extern "C"
{
#include <sys/processor.h>
#include <sys/thread.h>
}

#include <boost/assert.hpp>
#include <boost/thread.hpp>
#include <boost/system/system_error.hpp>

#include <boost/config/abi_prefix.hpp>

void bind_to_processor( unsigned int n)
{
    BOOST_ASSERT( n >= 0);
    BOOST_ASSERT( n < boost::thread::hardware_concurrency() );

    if ( ::bindprocessor( BINDTHREAD, ::thread_self(), static_cast< cpu_t >( n) ) == -1)
        throw boost::system::system_error(
                boost::system::error_code(
                    errno,
                    boost::system::system_category() ) );
}

#include <boost/config/abi_suffix.hpp>

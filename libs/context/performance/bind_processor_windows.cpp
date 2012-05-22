
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "bind_processor.hpp"

extern "C"
{
#include <windows.h>
}

#include <boost/assert.hpp>
#include <boost/thread.hpp>
#include <boost/system/system_error.hpp>

#include <boost/config/abi_prefix.hpp>

void bind_to_processor( unsigned int n)
{
    BOOST_ASSERT( n >= 0);
    BOOST_ASSERT( n < boost::thread::hardware_concurrency() );

    if ( ::SetThreadAffinityMask( ::GetCurrentThread(), ( DWORD_PTR)1 << n) == 0)
        throw boost::system::system_error(
                boost::system::error_code(
                    ::GetLastError(),
                    boost::system::system_category() ) );
}

#include <boost/config/abi_suffix.hpp>

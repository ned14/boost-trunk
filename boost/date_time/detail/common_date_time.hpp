/*
 *          Copyright Andrey Semashev 2007 - 2010.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   common_date_time.hpp
 * \author Andrey Semashev
 * \date   08.06.2010
 *
 * The header contains implementation of a common date/time type for ABI purposes.
 */

#if (defined(_MSC_VER) && _MSC_VER > 1000)
#pragma once
#endif // _MSC_VER > 1000

#ifndef BOOST_DATE_TIME_DETAIL_COMMON_DATE_TIME_HPP_INCLUDED_
#define BOOST_DATE_TIME_DETAIL_COMMON_DATE_TIME_HPP_INCLUDED_

#include <ctime>
#include <boost/cstdint.hpp>
#include <boost/date_time/compiler_config.hpp>

namespace boost {

namespace date_time {

namespace aux {

class common_date_time
{
private:
    bool negative_;
    std::tm tm_;
    uint32_t fractional_;

public:
    template< typename T >
    explicit common_date_time(T const& t, uint32_t fractional, bool negative = false) :
        negative_(negative),
        tm_(to_tm(t)),
        fractional_(fractional)
    {
    }

    bool is_negative() const { return negative_; }
    std::tm const& get_tm() const { return tm_; }
    uint32_t fractional_seconds() const { return fractional_; }
};

} // namespace aux

} // namespace date_time

} // namespace boost

#endif // BOOST_DATE_TIME_DETAIL_COMMON_DATE_TIME_HPP_INCLUDED_

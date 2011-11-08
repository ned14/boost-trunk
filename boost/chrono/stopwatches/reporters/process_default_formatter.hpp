//  boost/chrono/stopwatches/stopwatch_reporter.hpp
//  Copyright 2011 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or
//   copy at http://www.boost.org/LICENSE_1_0.txt)
//  See http://www.boost.org/libs/chrono/stopwatches for documentation.

#ifndef BOOST_CHRONO_STOPWATCHES_REPORTERS_PROCESS_DEFAULT_FORMATTER_HPP
#define BOOST_CHRONO_STOPWATCHES_REPORTERS_PROCESS_DEFAULT_FORMATTER_HPP

#include <boost/chrono/config.hpp>

#include <boost/chrono/stopwatches/reporters/stopwatch_reporter_default_formatter.hpp>
#include <boost/chrono/stopwatches/reporters/clock_default_formatter.hpp>
#include <boost/chrono/stopwatches/formatters/elapsed_formatter.hpp>
#include <boost/chrono/stopwatches/formatters/times_formatter.hpp>
#include <boost/chrono/process_cpu_clocks.hpp>

#if defined(BOOST_CHRONO_HAS_PROCESS_CLOCKS)

namespace boost
{
  namespace chrono
  {

    template <typename CharT>
    struct basic_clock_default_formatter<CharT, process_cpu_clock>
    {
      typedef basic_times_formatter<milli, CharT> type;
    };

//    template<>
//    struct clock_default_formatter<process_cpu_clock>
//    {
//      typedef times_formatter type;
//    };
//
//    template<>
//    struct wclock_default_formatter<process_cpu_clock>
//    {
//      typedef wtimes_formatter type;
//    };

  } // namespace chrono
} // namespace boost


#endif

#endif


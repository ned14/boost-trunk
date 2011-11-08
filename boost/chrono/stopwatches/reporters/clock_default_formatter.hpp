//  boost/chrono/stopwatches/stopwatch_reporter.hpp
//  Copyright 2011 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or
//   copy at http://www.boost.org/LICENSE_1_0.txt)
//  See http://www.boost.org/libs/chrono/stopwatches for documentation.

#ifndef BOOST_CHRONO_STOPWATCHES_REPORTERS_CLOCK_DEFAULT_FORMATTER_HPP
#define BOOST_CHRONO_STOPWATCHES_REPORTERS_CLOCK_DEFAULT_FORMATTER_HPP

#include <boost/chrono/stopwatches/formatters/elapsed_formatter.hpp>

namespace boost
{
  namespace chrono
  {

    template<class CharT, class Clock>
    struct basic_clock_default_formatter
    {
      typedef basic_elapsed_formatter<milli, CharT> type;
    };

//    template<class Clock>
//    struct clock_default_formatter
//    {
//      typedef elapsed_formatter type;
//    };
//
//    template<class Clock>
//    struct wclock_default_formatter
//    {
//      typedef welapsed_formatter type;
//    };
  } // namespace chrono
} // namespace boost



#endif



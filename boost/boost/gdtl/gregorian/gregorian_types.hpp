#ifndef _GREGORIAN_TYPES_HPP__
#define _GREGORIAN_TYPES_HPP__
/* Copyright (c) 2002 CrystalClear Software, Inc.
 * Disclaimer & Full Copyright at end of file
 * Author: Jeff Garland 
 */
/*! @file gregorian_types.hpp
  Single file header that defines most of the types for the gregorian 
  date-time system.
*/


#include "boost/gdtl/date.hpp"
#include "boost/gdtl/period.hpp"
#include "boost/gdtl/gregorian/greg_calendar.hpp"
#include "boost/gdtl/gregorian/greg_duration.hpp"
#include "boost/gdtl/gregorian/greg_date.hpp"
#include "boost/gdtl/date_generators.hpp"
#include "boost/gdtl/date_clock_device.hpp"
#include "boost/gdtl/date_iterator.hpp"
#include "boost/gdtl/adjust_functors.hpp"

namespace boost {

//! Gregorian date system based on gdtl components
/*! This date system defines a full complement of types including
 *  a date, date_duration, date_period, day_clock, and a
 *  day_iterator.
 */
namespace gregorian {
  //! Date periods for the gregorian system
  /*!\ingroup date_basics
   */
  typedef gdtl::period<date, date_duration> date_period;  
  //! A date generation object type
  typedef gdtl::partial_date<date> partial_date;
  //! A clock to get the current day from the local computer
  /*!\ingroup date_basics
   */
  typedef gdtl::day_clock<date> day_clock;

  //! Base date_iterator type for gregorian types.
  /*!\ingroup date_basics
   */
  typedef gdtl::date_itr_base<date> date_iterator;

  //! A day level iterator
  /*!\ingroup date_basics
   */
  typedef gdtl::date_itr<gdtl::day_functor<date>,
			 date> day_iterator;
  //! A week level iterator
  /*!\ingroup date_basics
   */
  typedef gdtl::date_itr<gdtl::week_functor<date>,
			 date> week_iterator;
  //! A month level iterator
  /*!\ingroup date_basics
   */
  typedef gdtl::date_itr<gdtl::month_functor<date>,
			 date> month_iterator;
} } //namespace gregorian


/* Copyright (c) 2002
 * CrystalClear Software, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  CrystalClear Software makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

#endif



/* Copyright (c) 2000 CrystalClear Software, Inc.
 * Disclaimer & Full Copyright at end of file
 * Author: Jeff Garland, Bart Garst
 */

#ifndef BOOST_DATE_TIME_SOURCE
#define BOOST_DATE_TIME_SOURCE
#endif
#include "boost/date_time/gregorian/greg_month.hpp"
#include "boost/date_time/gregorian/greg_facet.hpp"
#include "boost/date_time/date_format_simple.hpp"
#include "boost/date_time/gregorian/formatters.hpp"
#include "boost/date_time/date_parsing.hpp"

namespace boost {
namespace gregorian {

  const char* const short_month_names[NumMonths]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec", "NAM"};
  const char* const long_month_names[NumMonths]={"January","February","March","April","May","June","July","August","September","October","November","December","NotAMonth"};
  unsigned short days_in_month[NumMonths] = {31,28,31,30,31,30,31,31,30,31,30,31};


  /*! Returns a shared pointer to a map of Month strings & numbers.
   * Strings are both full names and abbreviations.</br>
   * Ex. ("jan",1), ("february",2), etc...</br>
   * Note: All characters are lowercase - for case insensitivity</br> 
   */
  greg_month::month_map_ptr_type greg_month::get_month_map_ptr()
  {
    static month_map_ptr_type month_map_ptr(new greg_month::month_map_type())
;

    if(month_map_ptr->empty()) {
      std::string s("");
      for(unsigned short i = 1; i <= 12; ++i) {
        greg_month m(static_cast<month_enum>(i));
        s = m.as_long_string();
	s = date_time::convert_to_lower(s);
        month_map_ptr->insert(std::make_pair(s, i));
        
        s = m.as_short_string();
	s = date_time::convert_to_lower(s);
        month_map_ptr->insert(std::make_pair(s, i));
      }
    }
    return month_map_ptr;
  }
 


  //! Returns 3 char english string for the month ex: Jan, Feb, Mar, Apr
  const char*
  greg_month::as_short_string() const 
  {
    return short_month_names[value_-1];
  }
  
  //! Returns full name of month as string in english ex: January, February
  const char*
  greg_month::as_long_string()  const 
  {
    return long_month_names[value_-1];
  }

} } //namespace gregorian




/* Copyright (c) 2000
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



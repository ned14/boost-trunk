/* Copyright (c) 2002-2004 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE-1.0 or http://www.boost.org/LICENSE-1.0)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */



#ifndef BOOST_DATE_TIME_SOURCE
#define BOOST_DATE_TIME_SOURCE
#endif
#include "boost/date_time/gregorian/greg_month.hpp"
#include "boost/date_time/gregorian/greg_facet.hpp"
#include "boost/date_time/date_format_simple.hpp"
#include "boost/date_time/compiler_config.hpp"
#if defined(BOOST_DATE_TIME_NO_WSTRING_CONVERSIONS)
#include "boost/date_time/gregorian/formatters_limited.hpp"
#else
#include "boost/date_time/gregorian/formatters.hpp"
#endif
#include "boost/date_time/date_parsing.hpp"

#include "greg_names.hpp"
namespace boost {
namespace gregorian {

  /*! Returns a shared pointer to a map of Month strings & numbers.
   * Strings are both full names and abbreviations.
   * Ex. ("jan",1), ("february",2), etc...
   * Note: All characters are lowercase - for case insensitivity
   */
  greg_month::month_map_ptr_type greg_month::get_month_map_ptr()
  {
    static month_map_ptr_type month_map_ptr(new greg_month::month_map_type());

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


#ifndef BOOST_NO_CWCHAR
  //! Returns 3 wchar_t english string for the month ex: Jan, Feb, Mar, Apr
  const wchar_t*
  greg_month::as_short_wstring() const 
  {
    return w_short_month_names[value_-1];
  }
  
  //! Returns full name of month as wchar_t string in english ex: January, February
  const wchar_t*
  greg_month::as_long_wstring()  const 
  {
    return w_long_month_names[value_-1];
  }
#endif // BOOST_NO_CWCHAR
  
#ifndef BOOST_DATE_TIME_NO_LOCALE
  //! generates a locale with the set of gregorian name-strings of type char*
  BOOST_DATE_TIME_DECL std::locale generate_locale(std::locale& loc, char type){
    typedef boost::date_time::all_date_names_put<greg_facet_config, char> facet_def;
    return std::locale(loc, new facet_def(short_month_names,
					  long_month_names,
					  special_value_names,
					  short_weekday_names,
					  long_weekday_names)
	);
  }
  
#ifndef BOOST_NO_CWCHAR
  //! generates a locale with the set of gregorian name-strings of type wchar_t*
  BOOST_DATE_TIME_DECL std::locale generate_locale(std::locale& loc, wchar_t type){
    typedef boost::date_time::all_date_names_put<greg_facet_config, wchar_t> facet_def;
    return std::locale(loc, new facet_def(w_short_month_names,
					  w_long_month_names,
					  w_special_value_names,
					  w_short_weekday_names,
					  w_long_weekday_names)
	);
  }
#endif // BOOST_NO_CWCHAR
#endif // BOOST_DATE_TIME_NO_LOCALE

} } //namespace gregorian







//  boost/timer/timer.hpp  -------------------------------------------------------------//

//  Copyright Beman Dawes 1994-2007, 2011

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_TIMER_TIMER_HPP                  
#define BOOST_TIMER_TIMER_HPP

#include <boost/config/warning_disable.hpp>

#include <boost/timer/config.hpp>
#include <boost/chrono/chrono.hpp>
#include <boost/cstdint.hpp>
#include <string>
#include <cstring>
#include <ostream>

#include <boost/config/abi_prefix.hpp> // must be the last #include

#   if defined(_MSC_VER)
#     pragma warning(push)           // Save warning settings
#     pragma warning(disable : 4251) // disable warning: class 'std::basic_string<_Elem,_Traits,_Ax>'
#   endif                            // needs to have dll-interface...

//--------------------------------------------------------------------------------------//

//  TODO:
//  
//  * Add BOOST_NOEXCEPT where applicable

//--------------------------------------------------------------------------------------//

namespace boost
{
namespace timer
{
  class cpu_timer;
  class auto_cpu_timer;

  typedef boost::int_least64_t nanosecond_type;

  struct cpu_times
  {
    nanosecond_type wall;
    nanosecond_type user;
    nanosecond_type system;

    void clear() { wall = user = system = 0LL; }
  };
      
  const short         default_places = 6;

  BOOST_TIMER_DECL
  const std::string&  default_format();

  BOOST_TIMER_DECL
  std::string format(const cpu_times& times,
                     short places = default_places,
                     const std::string& fmt = default_format()); 

//  cpu_timer  ---------------------------------------------------------------------//

  class BOOST_TIMER_DECL cpu_timer
  {
  public:

    //  constructors, destructor
    cpu_timer()                                    { start(); }
   ~cpu_timer()                                    {}

    //  observers
    bool              is_stopped() const           { return m_is_stopped; }
    cpu_times         elapsed() const;  // does not stop()
    std::string       format(int places = default_places,
                             const std::string& format = default_format()) const
                                 { return timer::format(elapsed(), places, format); }
    //  actions
    void              start();
    const cpu_times&  stop();
    void              resume(); 

  private:
    cpu_times         m_times;
    bool              m_is_stopped;
  };

//  auto_cpu_timer  --------------------------------------------------------------------//

  class BOOST_TIMER_DECL auto_cpu_timer : public cpu_timer
  {
  public:

    //  Explicit defaults to std::cout are not supplied since such defaults would
    //  require including <iostream>, with its high costs, even when the standard
    //  streams are not actually used.

    explicit auto_cpu_timer(short places = default_places,
                            const std::string& format = default_format());
    explicit auto_cpu_timer(const std::string& format);
    explicit auto_cpu_timer(std::ostream& os,
                            short places = default_places,
                            const std::string& format = default_format())
                                   : m_places(places), m_os(os), m_format(format)
                                   { start(); }
    auto_cpu_timer(std::ostream& os, const std::string& format)
                                   : m_places(default_places), m_os(os), m_format(format)
                                   { start(); }

   ~auto_cpu_timer();

    void   report(); 

  private:
    int             m_places;
    std::ostream&   m_os;
    std::string     m_format;  
  };
   
} // namespace timer
} // namespace boost

#   if defined(_MSC_VER)
#     pragma warning(pop) // restore warning settings.
#   endif 

#include <boost/config/abi_suffix.hpp> // pops abi_prefix.hpp pragmas

#endif  // BOOST_TIMER_TIMER_HPP

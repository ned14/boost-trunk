#ifndef CAMERA_HPP
#define CAMERA_HPP
//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2002-2004
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/event.hpp>
#include <boost/fsm/state_machine.hpp>
#include <boost/fsm/simple_state.hpp>
#include <boost/fsm/custom_reaction.hpp>

#include <boost/config.hpp>

#ifdef BOOST_INTEL
#  pragma warning( disable: 304 ) // access control not specified
#endif



namespace fsm = boost::fsm;



struct EvShutterHalf : fsm::event< EvShutterHalf > {};
struct EvShutterFull : fsm::event< EvShutterFull > {};
struct EvShutterRelease : fsm::event< EvShutterRelease > {};
struct EvConfig : fsm::event< EvConfig > {};


struct NotShooting;
struct Camera : fsm::state_machine< Camera, NotShooting >
{
    bool IsMemoryAvailable() const { return true; }
    bool IsBatteryLow() const { return false; }
};


struct Idle;
struct NotShooting : fsm::simple_state< NotShooting, Camera,
  fsm::custom_reaction< EvShutterHalf >, Idle >
{
  NotShooting();
  ~NotShooting();

  fsm::result react( const EvShutterHalf & );
};

struct Idle : fsm::simple_state< Idle, NotShooting,
  fsm::custom_reaction< EvConfig > >
{
  Idle();
  ~Idle();

  fsm::result react( const EvConfig & );
};



#endif

//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2002-2004
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include "Precompiled.hpp"
#include "Shooting.hpp"
#include <iostream>

#include <boost/config.hpp>

#ifdef BOOST_INTEL
#  pragma warning( disable: 383 ) // reference to temporary used
#endif



Shooting::Shooting()
{
  std::cout << "Entering Shooting\n";
}

Shooting::~Shooting()
{
  std::cout << "Exiting Shooting\n";
}


struct Storing : fsm::simple_state< Storing, Shooting >
{
  Storing()
  {
    std::cout << "Picture taken!\n";
  }
};


struct Focused : fsm::simple_state< Focused, Shooting,
  fsm::custom_reaction< EvShutterFull > >
{
  fsm::result react( const EvShutterFull & );
};

fsm::result Focused::react( const EvShutterFull & )
{
  if ( context< Camera >().IsMemoryAvailable() )
  {
    return transit< Storing >();
  }
  else
  {
    std::cout << "Cache memory full. Please wait...\n";
    return discard_event();
  }
}


Focusing::Focusing( my_context ctx ) : my_base( ctx )
{
  post_event( boost::intrusive_ptr< EvInFocus >( new EvInFocus() ) );
}

fsm::result Focusing::react( const EvInFocus & evt )
{
  return transit< Focused >( &Shooting::DisplayFocused, evt );
}

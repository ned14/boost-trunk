#ifndef BOOST_FSM_CUSTOM_REACTION_HPP_INCLUDED
#define BOOST_FSM_CUSTOM_REACTION_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2002-2004
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/result.hpp>

#include <boost/cast.hpp> // boost::polymorphic_downcast



namespace boost
{
namespace fsm
{



//////////////////////////////////////////////////////////////////////////////
template< class Event >
struct custom_reaction
{
  template< class State, class EventBase, class IdType >
  static result react(
    State & stt, const EventBase & evt, const IdType & eventType )
  {
    if ( eventType == Event::static_type() )
    {
      return stt.react( *polymorphic_downcast< const Event * >( &evt ) );
    }
    else
    {
      return no_reaction;
    }
  }
};



} // namespace fsm
} // namespace boost



#endif

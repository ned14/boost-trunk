//////////////////////////////////////////////////////////////////////////////
// Copyright (c) Andreas Huber Doenni 2002-2004.
// Use, modification and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
// The following code implements the state-machine (this version details an
// alternative way of retrieving the elapsed time from the main program):
//
//  --------------------------------
// |                                |
// |           O     Active         |
// |           |                    |<----
// |           v                    |     | EvReset
// |  ----------------------------  |     |
// | |                            | |-----
// | |         Stopped            | |
// |  ----------------------------  |
// |  |              ^              |
// |  | EvStartStop  | EvStartStop  |<-----O
// |  v              |              |
// |  ----------------------------  |
// | |                            | |
// | |         Running            | |
// |  ----------------------------  |
//  --------------------------------



#include <boost/fsm/event.hpp>
#include <boost/fsm/state_machine.hpp>
#include <boost/fsm/simple_state.hpp>
#include <boost/fsm/transition.hpp>
#include <boost/fsm/custom_reaction.hpp>

#include <boost/mpl/list.hpp>

#include <boost/config.hpp>

#include <ctime>
#include <iostream>

#ifdef BOOST_INTEL
#  pragma warning( disable: 304 ) // access control not specified
#  pragma warning( disable: 444 ) // destructor for base is not virtual
#  pragma warning( disable: 981 ) // operands are evaluated in unspecified order
#endif



namespace fsm = boost::fsm;
namespace mpl = boost::mpl;



struct EvStartStop : fsm::event< EvStartStop > {};
struct EvReset : fsm::event< EvReset > {};
struct EvGetElapsedTime : fsm::event< EvGetElapsedTime >
{
  public:
    EvGetElapsedTime( double & time ) : time_( time ) {}

    void Assign( double time ) const
    {
      time_ = time;
    }

  private:
    double & time_;
};


struct Active;
struct StopWatch : fsm::state_machine< StopWatch, Active > {};


struct Stopped;
struct Active : fsm::simple_state< Active, StopWatch,
  fsm::transition< EvReset, Active >, Stopped >
{
  public:
    Active() : elapsedTime_( 0.0 ) {}

    double & ElapsedTime()
    {
      return elapsedTime_;
    }

    double ElapsedTime() const
    {
      return elapsedTime_;
    }

  private:
    double elapsedTime_;
};

struct Running :
  fsm::simple_state< Running, Active, mpl::list<
    fsm::custom_reaction< EvGetElapsedTime >,
    fsm::transition< EvStartStop, Stopped > > >
{
  public:
    Running() : startTime_( std::time( 0 ) ) {}

    ~Running()
    {
      context< Active >().ElapsedTime() = ElapsedTime();
    }

    fsm::result react( const EvGetElapsedTime & evt )
    {
      evt.Assign( ElapsedTime() );
      return discard_event();
    }

  private:
    double ElapsedTime() const
    {
      return context< Active >().ElapsedTime() +
        std::difftime( std::time( 0 ), startTime_ );
    }

    std::time_t startTime_;
};

struct Stopped :
  fsm::simple_state< Stopped, Active, mpl::list<
    fsm::custom_reaction< EvGetElapsedTime >,
    fsm::transition< EvStartStop, Running > > >
{
  fsm::result react( const EvGetElapsedTime & evt )
  {
    evt.Assign( context< Active >().ElapsedTime() );
    return discard_event();
  }
};


namespace
{
  char GetKey()
  {
    char key;
    std::cin >> key;
    return key;
  }
}

int main()
{
  std::cout << "boost::fsm StopWatch example\n\n";
  std::cout << "s<CR>: Starts/Stops stop watch\n";
  std::cout << "r<CR>: Resets stop watch\n";
  std::cout << "d<CR>: Displays the elapsed time in seconds\n";
  std::cout << "e<CR>: Exits the program\n\n";
  std::cout << "You may chain commands, e.g. rs<CR> resets and starts stop watch\n\n";
  
  StopWatch stopWatch;
  stopWatch.initiate();

  char key = GetKey();

  while ( key != 'e' )
  {
    switch( key )
    {
      case 'r':
      {
        stopWatch.process_event( EvReset() );
      }
      break;

      case 's':
      {
        stopWatch.process_event( EvStartStop() );
      }
      break;

      case 'd':
      {
        double elapsedTime = 0.0;
        stopWatch.process_event( EvGetElapsedTime( elapsedTime ) );
        std::cout << "Elapsed time: " << elapsedTime << "\n";
      }
      break;

      default:
      {
        std::cout << "Invalid key!\n";
      }
      break;
    }

    key = GetKey();
  }

  return 0;
}

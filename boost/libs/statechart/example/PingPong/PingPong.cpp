//////////////////////////////////////////////////////////////////////////////
// Copyright (c) Andreas Huber Doenni 2002-2004.
// Use, modification and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
#define USE_TWO_THREADS // ignored for single-threaded builds
#define CUSTOMIZE_MEMORY_MANAGEMENT
//////////////////////////////////////////////////////////////////////////////
// The following example program demonstrates the use of asynchronous state
// machines. First, it creates two objects of the same simple state machine
// mimicking a table tennis player. It then sends an event (the ball) to the
// first state machine. Upon reception, the first machine sends a similar
// event to the second state machine, which then sends the event back to the
// first machine. The two machines continue to bounce the event back and forth
// until one machine "has enough" and aborts the game. The two players don't
// "know" each other, they can only pass the ball back and forth because the
// event representing the ball also carries two boost::function objects.
// Both reference the fifo_scheduler<>::queue_event() function, binding the
// scheduler and the handle of the opponent. One can be used to return the ball
// to the opponent and the other can be used to abort the game.
// Depending on whether the program is compiled single-threaded or
// multi-threaded and the USE_TWO_THREADS define above, the two
// machines either run in the same thread without/with mutex locking or in two
// different threads with mutex locking.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/event.hpp>
#include <boost/fsm/asynchronous_state_machine.hpp>
#include <boost/fsm/state.hpp>
#include <boost/fsm/transition.hpp>
#include <boost/fsm/custom_reaction.hpp>
#include <boost/fsm/fifo_scheduler.hpp>
#include <boost/fsm/fifo_worker.hpp>

#include <boost/mpl/list.hpp>

#include <boost/config.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#ifdef BOOST_HAS_THREADS
#  include <boost/thread/thread.hpp>
#endif
#ifdef CUSTOMIZE_MEMORY_MANAGEMENT
#  ifdef BOOST_HAS_THREADS
     // for some reason the following is not automatically defined
#    ifdef BOOST_MSVC
#      define __WIN32__
#    endif
#  else
#    define BOOST_NO_MT
#  endif
#  include <boost/pool/pool_alloc.hpp>
#endif

#include <iostream>
#include <ctime>
#include <memory> // std::allocator

namespace fsm = boost::fsm;
namespace mpl = boost::mpl;


const unsigned int noOfEvents = 1000000;

template< class T >
boost::intrusive_ptr< T > MakeIntrusive( T * pObject )
{
  return boost::intrusive_ptr< T >( pObject );
}


struct BallReturned : fsm::event< BallReturned >
{
  boost::function1< void, const boost::intrusive_ptr< const BallReturned > & >
    returnToOpponent;
  boost::function0< void > abortGame;
};

struct GameAborted : fsm::event< GameAborted > {};

#ifdef CUSTOMIZE_MEMORY_MANAGEMENT
typedef boost::fast_pool_allocator< int > MyAllocator;
typedef fsm::fifo_scheduler< 
  fsm::fifo_worker< MyAllocator >, MyAllocator > MyScheduler;
#else
typedef std::allocator< void > MyAllocator;
typedef fsm::fifo_scheduler<> MyScheduler;
#endif

struct Waiting;
struct Player : fsm::asynchronous_state_machine<
  Player, Waiting, MyScheduler, MyAllocator >
{
  typedef fsm::asynchronous_state_machine< 
    Player, Waiting, MyScheduler, MyAllocator > BaseType;
  public:
    Player( 
      my_context ctx,
      unsigned int maxNoOfReturns
    ) :
      my_base( ctx ),
      maxNoOfReturns_( maxNoOfReturns )
    {
    }

    static unsigned int & TotalNoOfProcessedEvents()
    {
      return totalNoOfProcessedEvents_;
    }

    unsigned int GetMaxNoOfReturns() const
    {
      return maxNoOfReturns_;
    }

  private:
    static unsigned int totalNoOfProcessedEvents_;
    const unsigned int maxNoOfReturns_;
};

unsigned int Player::totalNoOfProcessedEvents_ = 0;


struct Waiting : fsm::state< Waiting, Player, mpl::list<
  fsm::custom_reaction< BallReturned >,
  fsm::custom_reaction< GameAborted > > >
{
    Waiting( my_context ctx ) :
      my_base( ctx ),
      noOfReturns_( 0 ),
      pBallReturned_( new BallReturned() )
    {
      outermost_context_type & machine = outermost_context();
      // as we will always return the same event to the opponent, we construct
      // and fill it here so that we can reuse it over and over
      pBallReturned_->returnToOpponent = boost::bind(
        &MyScheduler::queue_event,
        &machine.my_scheduler(), machine.my_handle(), _1 );
      pBallReturned_->abortGame = boost::bind(
        &MyScheduler::queue_event,
        &machine.my_scheduler(), machine.my_handle(),
        MakeIntrusive( new GameAborted() ) );
    }

    fsm::result react( const GameAborted & )
    {
      return DestroyMyself();
    }

    fsm::result react( const BallReturned & ballReturned )
    {
      outermost_context_type & machine = outermost_context();
      ++machine.TotalNoOfProcessedEvents();

      if ( noOfReturns_++ < machine.GetMaxNoOfReturns() )
      {
        ballReturned.returnToOpponent( pBallReturned_ );
        return discard_event();
      }
      else
      {
        ballReturned.abortGame();
        return DestroyMyself();
      }
    }

  private:
    fsm::result DestroyMyself()
    {
      outermost_context_type & machine = outermost_context();
      machine.my_scheduler().destroy_processor( machine.my_handle() );
      machine.my_scheduler().terminate();
      return terminate();
    }

    unsigned int noOfReturns_;
    const boost::intrusive_ptr< BallReturned > pBallReturned_;
};



char GetKey()
{
  char key;
  std::cin >> key;
  return key;
}

int main()
{
  std::cout << "boost::fsm PingPong example\n\n";
  std::cout << "Threading configuration:\n";
  #ifdef BOOST_HAS_THREADS
  std::cout << "Multi-threaded build with ";
  #ifdef USE_TWO_THREADS
  std::cout << 2;
  #else
  std::cout << 1;
  #endif
  std::cout << " thread(s).\n";
  #else
  std::cout << "Single-threaded build\n";
  #endif
  
  std::cout << "\np<CR>: Performance test\n";
  std::cout << "e<CR>: Exits the program\n\n";

  char key = GetKey();

  while ( key != 'e' )
  {
    switch( key )
    {
      case 'p':
      {
        MyScheduler scheduler1;

        #ifdef USE_TWO_THREADS
        #ifdef BOOST_HAS_THREADS
        MyScheduler scheduler2;
        #else
        MyScheduler & scheduler2 = scheduler1;
        #endif
        #else
        MyScheduler & scheduler2 = scheduler1;
        #endif

        MyScheduler::processor_handle player1 = 
          scheduler1.create_processor< Player >( noOfEvents / 2 );
        scheduler1.initiate_processor( player1 );
        MyScheduler::processor_handle player2 = 
          scheduler2.create_processor< Player >( noOfEvents / 2 );
        scheduler2.initiate_processor( player2 );

        boost::intrusive_ptr< BallReturned > pInitialBall = new BallReturned();
        pInitialBall->returnToOpponent = boost::bind( 
          &MyScheduler::queue_event, &scheduler1, player1, _1 );
        pInitialBall->abortGame = boost::bind(
          &MyScheduler::queue_event, 
          &scheduler1, player1, MakeIntrusive( new GameAborted() ) );

        scheduler2.queue_event( player2, pInitialBall );

        std::cout << "\nHaving players return the ball " <<
          noOfEvents << " times. Please wait...\n";

        const unsigned int prevCount = Player::TotalNoOfProcessedEvents();
        const std::clock_t startTime = std::clock();

        #ifdef USE_TWO_THREADS
        #ifdef BOOST_HAS_THREADS
        boost::thread otherThread(
          boost::bind( &MyScheduler::operator(), &scheduler2, 0 ) );
        scheduler1();
        otherThread.join();
        #else
        scheduler1();
        #endif
        #else
        scheduler1();
        #endif

        const std::clock_t elapsedTime = std::clock() - startTime;
        std::cout << "Time to send and dispatch one event and\n" <<
                     "perform the resulting transition: ";
        std::cout << elapsedTime / static_cast< double >( CLOCKS_PER_SEC ) *
          1000000.0 / ( Player::TotalNoOfProcessedEvents() - prevCount )
          << " microseconds\n\n";
      }
      break;

      default:
      {
        std::cout << "Invalid key!\n";
      }
    }

    key = GetKey();
  }

  return 0;
}

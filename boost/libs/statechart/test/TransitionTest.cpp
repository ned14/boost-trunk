//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2004
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include "OuterOrthogonal.hpp"
#include "InnermostDefault.hpp"

#include <boost/fsm/state_machine.hpp>
#include <boost/fsm/event.hpp>
#include <boost/fsm/transition.hpp>
#include <boost/fsm/custom_reaction.hpp>

#include <boost/mpl/list.hpp>

#include <boost/test/test_tools.hpp>

#include <typeinfo>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>



namespace fsm = boost::fsm;
namespace mpl = boost::mpl;



typedef std::string ActionDescription();
typedef ActionDescription * ActionDescriptionPtr;
typedef std::vector< ActionDescriptionPtr > ActionDescriptionSequence;
typedef ActionDescriptionSequence::const_iterator SequenceIterator;
typedef void Action( ActionDescriptionSequence & );
typedef Action * ActionPtr;

template< class State >
std::string EntryDescription()
{
  static const std::string entry = "Entry: ";
  return entry + typeid( State ).name() + "\n";
}

template< class State >
std::string ExitFnDescription()
{
  static const std::string exitFunction = "exit(): ";
  return exitFunction + typeid( State ).name() + "\n";
}

template< class State >
std::string DtorDescription()
{
  static const std::string destructor = "Destructor: ";
  return destructor + typeid( State ).name() + "\n";
}

template< class Context, class Event >
std::string TransDescription()
{
  static const std::string transition = "Transition: ";
  static const std::string event = " with Event: ";
  return transition + typeid( Context ).name() +
    event + typeid( Event ).name() + "\n";
}

template< ActionPtr pAction >
std::string ThrowDescription()
{
  static const std::string throwing = "Throwing exception in ";
  static ActionDescriptionSequence dummy;
  dummy.clear();
  pAction( dummy );
  return throwing + dummy.front()();
}


template< class State >
void Entry( ActionDescriptionSequence & sequence )
{
  sequence.push_back( EntryDescription< State > );
}

template< class State >
void ExitFn( ActionDescriptionSequence & sequence )
{
  sequence.push_back( ExitFnDescription< State > );
}

template< class State >
void Dtor( ActionDescriptionSequence & sequence )
{
  sequence.push_back( DtorDescription< State > );
}

template< class State >
void Exit( ActionDescriptionSequence & sequence )
{
  ExitFn< State >( sequence );
  Dtor< State >( sequence );
}

template< class Context, class Event >
void Trans( ActionDescriptionSequence & sequence )
{
  sequence.push_back( TransDescription< Context, Event > );
}

template< ActionPtr pAction >
void Throw( ActionDescriptionSequence & sequence )
{
  sequence.push_back( ThrowDescription< pAction > );
}

const int arrayLength = 30;
typedef ActionPtr ActionArray[ arrayLength ];


class TransitionTestException : public std::runtime_error
{
  public:
    TransitionTestException() : std::runtime_error( "Oh la la!" ) {}
};


// This test state machine is a beefed-up version of the one presented in
// "Practical Statecharts in C/C++" by Miro Samek, CMP Books 2002
struct A : fsm::event< A > {};
struct B : fsm::event< B > {};
struct C : fsm::event< C > {};
struct D : fsm::event< D > {};
struct E : fsm::event< E > {};
struct F : fsm::event< F > {};
struct G : fsm::event< G > {};
struct H : fsm::event< H > {};


struct S0;
struct TransitionTest : fsm::state_machine< TransitionTest, S0 >
{
  public:
    //////////////////////////////////////////////////////////////////////////
    TransitionTest() : pThrowAction_( 0 ) {}

    ~TransitionTest()
    {
      // Since state destructors access the state machine object, we need to
      // make sure that all states are destructed before this subclass
      // portion is destructed.
      terminate();
    }

    void CompareToExpectedActionSequence( ActionArray & actions )
    {
      expectedSequence_.clear();

      // Copy all non-null pointers in actions into expectedSequence_
      for ( ActionPtr * pCurrent = &actions[ 0 ];
        ( pCurrent != &actions[ arrayLength ] ) && ( *pCurrent != 0 );
        ++pCurrent )
      {
        ( *pCurrent )( expectedSequence_ );
      }

      if ( ( expectedSequence_.size() != actualSequence_.size() ) ||
        !std::equal( expectedSequence_.begin(),
          expectedSequence_.end(), actualSequence_.begin() ) )
      {
        std::string message = "\nExpected action sequence:\n";

        for ( SequenceIterator pExpected = expectedSequence_.begin();
          pExpected != expectedSequence_.end(); ++pExpected )
        {
          message += ( *pExpected )();
        }

        message += "\nActual action sequence:\n";

        for ( SequenceIterator pActual = actualSequence_.begin();
          pActual != actualSequence_.end(); ++pActual )
        {
          message += ( *pActual )();
        }

        BOOST_FAIL( message.c_str() );
      }

      actualSequence_.clear();
    }

    void ClearActualSequence()
    {
      actualSequence_.clear();
    }

    void ThrowAction( ActionPtr pThrowAction )
    {
      pThrowAction_ = pThrowAction;
    }

    template< class State >
    void ActualEntry()
    {
      StoreActualAction< &::Entry< State > >();
    }

    template< class State >
    void ActualExitFunction()
    {
      StoreActualAction< &::ExitFn< State > >();
    }
    
    template< class State >
    void ActualDestructor()
    {
      StoreActualAction< &::Dtor< State > >();
    }
    
    template< class Context, class Event >
    void ActualTransition()
    {
      StoreActualAction< &::Trans< Context, Event > >();
    }

  private:
    //////////////////////////////////////////////////////////////////////////
    template< ActionPtr pAction >
    void StoreActualAction()
    {
      if ( pAction == pThrowAction_ )
      {
        Throw< pAction >( actualSequence_ );
        throw TransitionTestException();
      }
      else
      {
        pAction( actualSequence_ );
      }
    }

    ActionPtr pThrowAction_;
    ActionDescriptionSequence actualSequence_;
    ActionDescriptionSequence expectedSequence_;
};

struct S1;
struct S211;
struct S0 : Orthogonal0< S0, TransitionTest, fsm::transition< E, S211 >, S1 >
{
  S0( my_context ctx ) : my_base( ctx ) {}

  template< class Event >
  void Transit( const Event & )
  {
    outermost_context().template ActualTransition< S0, Event >();
  }
};

  struct S11;
  struct S21;
  struct S2 : Orthogonal2< S2, S0, mpl::list<
    fsm::transition< C, S1, S0, &S0::Transit< C > >,
    fsm::transition< F, S11, S0, &S0::Transit< F > > >, S21 >
  {
    S2( my_context ctx ) : my_base( ctx ) {}
  };

    struct S21 : Orthogonal1< S21, S2::orthogonal< 2 >, mpl::list<
      fsm::transition< H, S21, S0, &S0::Transit< H > >,
      fsm::transition< B, S211, S0, &S0::Transit< B > > >, S211 >
    {
      S21( my_context ctx ) : my_base( ctx ) {}
    };

      struct S211 : InnermostDefault< S211, S21::orthogonal< 1 >, mpl::list<
        fsm::transition< D, S21, S0, &S0::Transit< D > >,
        fsm::transition< G, S0 > > >
      {
        S211( my_context ctx ) : my_base( ctx ) {}
      };

  struct S1 : Orthogonal1< S1, S0, mpl::list<
    fsm::transition< A, S1, S0, &S0::Transit< A > >,
    fsm::transition< B, S11, S0, &S0::Transit< B > >,
    fsm::transition< C, S2, S0, &S0::Transit< C > >,
    fsm::transition< D, S0 >,
    fsm::transition< F, S211, S0, &S0::Transit< F > > >, S11 >
  {
    S1( my_context ctx ) : my_base( ctx ) {}
  };

    struct S11 : InnermostDefault< S11, S1::orthogonal< 1 >, mpl::list<
      fsm::transition< G, S211, S0, &S0::Transit< G > >,
      fsm::custom_reaction< H > > >
    {
      S11( my_context ctx ) : my_base( ctx ) {}

      fsm::result react( const H & )
      {
        outermost_context().ActualTransition< S11, H >();
        return discard_event();
      }
    };


int test_main( int, char* [] )
{
  TransitionTest machine;

  machine.initiate();
  ActionArray init = 
  {
    Entry< S0 >,
    Entry< S1 >,
    Entry< Default0< S1 > >,
    Entry< S11 >,
    Entry< Default2< S1 > >,
    Entry< Default1< S0 > >,
    Entry< Default2< S0 > >
  };
  machine.CompareToExpectedActionSequence( init );

  machine.process_event( A() );
  ActionArray a1 =
  {
    Exit< Default2< S1 > >,
    Exit< S11 >,
    Exit< Default0< S1 > >,
    Exit< S1 >,
    Trans< S0, A >,
    Entry< S1 >,
    Entry< Default0< S1 > >,
    Entry< S11 >,
    Entry< Default2< S1 > >
  };
  machine.CompareToExpectedActionSequence( a1 );

  machine.process_event( B() );
  ActionArray b1 =
  {
    Exit< Default2< S1 > >,
    Exit< S11 >,
    Exit< Default0< S1 > >,
    Exit< S1 >,
    Trans< S0, B >,
    Entry< S1 >,
    Entry< Default0< S1 > >,
    Entry< S11 >,
    Entry< Default2< S1 > >
  };
  machine.CompareToExpectedActionSequence( b1 );

  machine.process_event( C() );
  ActionArray c1 =
  {
    Exit< Default2< S1 > >,
    Exit< S11 >,
    Exit< Default0< S1 > >,
    Exit< S1 >,
    Trans< S0, C >,
    Entry< S2 >,
    Entry< Default0< S2 > >,
    Entry< Default1< S2 > >,
    Entry< S21 >,
    Entry< Default0< S21 > >,
    Entry< S211 >,
    Entry< Default2< S21 > >
  };
  machine.CompareToExpectedActionSequence( c1 );

  machine.process_event( D() );
  ActionArray d2 =
  {
    Exit< Default2< S21 > >,
    Exit< S211 >,
    Exit< Default0< S21 > >,
    Exit< S21 >,
    Trans< S0, D >,
    Entry< S21 >,
    Entry< Default0< S21 > >,
    Entry< S211 >,
    Entry< Default2< S21 > >
  };
  machine.CompareToExpectedActionSequence( d2 );

  machine.process_event( E() );
  ActionArray e2 =
  {
    Exit< Default2< S0 > >,
    Exit< Default1< S0 > >,
    Exit< Default2< S21 > >,
    Exit< S211 >,
    Exit< Default0< S21 > >,
    Exit< S21 >,
    Exit< Default1< S2 > >,
    Exit< Default0< S2 > >,
    Exit< S2 >,
    Exit< S0 >,
    Entry< S0 >,
    Entry< S2 >,
    Entry< Default0< S2 > >,
    Entry< Default1< S2 > >,
    Entry< S21 >,
    Entry< Default0< S21 > >,
    Entry< S211 >,
    Entry< Default2< S21 > >,
    Entry< Default1< S0 > >,
    Entry< Default2< S0 > >
  };
  machine.CompareToExpectedActionSequence( e2 );

  machine.process_event( F() );
  ActionArray f2 =
  {
    Exit< Default2< S21 > >,
    Exit< S211 >,
    Exit< Default0< S21 > >,
    Exit< S21 >,
    Exit< Default1< S2 > >,
    Exit< Default0< S2 > >,
    Exit< S2 >,
    Trans< S0, F >,
    Entry< S1 >,
    Entry< Default0< S1 > >,
    Entry< S11 >,
    Entry< Default2< S1 > >
  };
  machine.CompareToExpectedActionSequence( f2 );

  machine.process_event( G() );
  ActionArray g1 =
  {
    Exit< Default2< S1 > >,
    Exit< S11 >,
    Exit< Default0< S1 > >,
    Exit< S1 >,
    Trans< S0, G >,
    Entry< S2 >,
    Entry< Default0< S2 > >,
    Entry< Default1< S2 > >,
    Entry< S21 >,
    Entry< Default0< S21 > >,
    Entry< S211 >,
    Entry< Default2< S21 > >
  };
  machine.CompareToExpectedActionSequence( g1 );

  machine.process_event( H() );
  ActionArray h2 =
  {
    Exit< Default2< S21 > >,
    Exit< S211 >,
    Exit< Default0< S21 > >,
    Exit< S21 >,
    Trans< S0, H >,
    Entry< S21 >,
    Entry< Default0< S21 > >,
    Entry< S211 >,
    Entry< Default2< S21 > >
  };
  machine.CompareToExpectedActionSequence( h2 );

  machine.process_event( A() );
  ActionArray a2 =
  {
  };
  machine.CompareToExpectedActionSequence( a2 );

  machine.process_event( B() );
  ActionArray b2 =
  {
    Exit< Default2< S21 > >,
    Exit< S211 >,
    Exit< Default0< S21 > >,
    Exit< S21 >,
    Trans< S0, B >,
    Entry< S21 >,
    Entry< Default0< S21 > >,
    Entry< S211 >,
    Entry< Default2< S21 > >
  };
  machine.CompareToExpectedActionSequence( b2 );

  machine.process_event( C() );
  ActionArray c2 =
  {
    Exit< Default2< S21 > >,
    Exit< S211 >,
    Exit< Default0< S21 > >,
    Exit< S21 >,
    Exit< Default1< S2 > >,
    Exit< Default0< S2 > >,
    Exit< S2 >,
    Trans< S0, C >,
    Entry< S1 >,
    Entry< Default0< S1 > >,
    Entry< S11 >,
    Entry< Default2< S1 > >
  };
  machine.CompareToExpectedActionSequence( c2 );

  machine.process_event( D() );
  ActionArray d1 = 
  {
    Exit< Default2< S0 > >,
    Exit< Default1< S0 > >,
    Exit< Default2< S1 > >,
    Exit< S11 >,
    Exit< Default0< S1 > >,
    Exit< S1 >,
    Exit< S0 >,
    Entry< S0 >,
    Entry< S1 >,
    Entry< Default0< S1 > >,
    Entry< S11 >,
    Entry< Default2< S1 > >,
    Entry< Default1< S0 > >,
    Entry< Default2< S0 > >
  };
  machine.CompareToExpectedActionSequence( d1 );

  machine.process_event( F() );
  ActionArray f1 =
  {
    Exit< Default2< S1 > >,
    Exit< S11 >,
    Exit< Default0< S1 > >,
    Exit< S1 >,
    Trans< S0, F >,
    Entry< S2 >,
    Entry< Default0< S2 > >,
    Entry< Default1< S2 > >,
    Entry< S21 >,
    Entry< Default0< S21 > >,
    Entry< S211 >,
    Entry< Default2< S21 > >
  };
  machine.CompareToExpectedActionSequence( f1 );

  machine.process_event( G() );
  ActionArray g2 =
  {
    Exit< Default2< S0 > >,
    Exit< Default1< S0 > >,
    Exit< Default2< S21 > >,
    Exit< S211 >,
    Exit< Default0< S21 > >,
    Exit< S21 >,
    Exit< Default1< S2 > >,
    Exit< Default0< S2 > >,
    Exit< S2 >,
    Exit< S0 >,
    Entry< S0 >,
    Entry< S1 >,
    Entry< Default0< S1 > >,
    Entry< S11 >,
    Entry< Default2< S1 > >,
    Entry< Default1< S0 > >,
    Entry< Default2< S0 > >
  };
  machine.CompareToExpectedActionSequence( g2 );

  machine.process_event( H() );
  ActionArray h1 =
  {
    Trans< S11, H >
  };
  machine.CompareToExpectedActionSequence( h1 );

  machine.process_event( E() );
  ActionArray e1 =
  {
    Exit< Default2< S0 > >,
    Exit< Default1< S0 > >,
    Exit< Default2< S1 > >,
    Exit< S11 >,
    Exit< Default0< S1 > >,
    Exit< S1 >,
    Exit< S0 >,
    Entry< S0 >,
    Entry< S2 >,
    Entry< Default0< S2 > >,
    Entry< Default1< S2 > >,
    Entry< S21 >,
    Entry< Default0< S21 > >,
    Entry< S211 >,
    Entry< Default2< S21 > >,
    Entry< Default1< S0 > >,
    Entry< Default2< S0 > >
  };
  machine.CompareToExpectedActionSequence( e1 );

  machine.terminate();
  ActionArray term =
  {
    Exit< Default2< S0 > >,
    Exit< Default1< S0 > >,
    Exit< Default2< S21 > >,
    Exit< S211 >,
    Exit< Default0< S21 > >,
    Exit< S21 >,
    Exit< Default1< S2 > >,
    Exit< Default0< S2 > >,
    Exit< S2 >,
    Exit< S0 >
  };
  machine.CompareToExpectedActionSequence( term );

  machine.ThrowAction( Entry< Default0< S1 > > );
  // TODO: Replace with BOOST_REQUIRE_THROW, as soon as available
  BOOST_CHECK_THROW( machine.initiate(), TransitionTestException );
  ActionArray initThrow1 = 
  {
    Entry< S0 >,
    Entry< S1 >,
    Throw< Entry< Default0< S1 > > >,
    Dtor< S1 >,
    Dtor< S0 >
  };
  machine.CompareToExpectedActionSequence( initThrow1 );
  BOOST_REQUIRE( machine.terminated() );

  machine.ThrowAction( Entry< S11 > );
  // TODO: Replace with BOOST_REQUIRE_THROW, as soon as available
  BOOST_CHECK_THROW( machine.initiate(), TransitionTestException );
  ActionArray initThrow2 = 
  {
    Entry< S0 >,
    Entry< S1 >,
    Entry< Default0< S1 > >,
    Throw< Entry< S11 > >,
    Dtor< Default0< S1 > >,
    Dtor< S1 >,
    Dtor< S0 >
  };
  machine.CompareToExpectedActionSequence( initThrow2 );
  BOOST_REQUIRE( machine.terminated() );

  machine.ThrowAction( Trans< S0, A > );
  machine.initiate();
  BOOST_CHECK_THROW( machine.process_event( A() ), TransitionTestException );
  ActionArray a1Throw1 =
  {
    Entry< S0 >,
    Entry< S1 >,
    Entry< Default0< S1 > >,
    Entry< S11 >,
    Entry< Default2< S1 > >,
    Entry< Default1< S0 > >,
    Entry< Default2< S0 > >,
    Exit< Default2< S1 > >,
    Exit< S11 >,
    Exit< Default0< S1 > >,
    Exit< S1 >,
    Throw< Trans< S0, A > >,
    Dtor< Default2< S0 > >,
    Dtor< Default1< S0 > >,
    Dtor< S0 >
  };
  machine.CompareToExpectedActionSequence( a1Throw1 );
  BOOST_REQUIRE( machine.terminated() );

  machine.ThrowAction( Entry< S211 > );
  machine.initiate();
  BOOST_CHECK_THROW( machine.process_event( C() ), TransitionTestException );
  ActionArray c1Throw1 =
  {
    Entry< S0 >,
    Entry< S1 >,
    Entry< Default0< S1 > >,
    Entry< S11 >,
    Entry< Default2< S1 > >,
    Entry< Default1< S0 > >,
    Entry< Default2< S0 > >,
    Exit< Default2< S1 > >,
    Exit< S11 >,
    Exit< Default0< S1 > >,
    Exit< S1 >,
    Trans< S0, C >,
    Entry< S2 >,
    Entry< Default0< S2 > >,
    Entry< Default1< S2 > >,
    Entry< S21 >,
    Entry< Default0< S21 > >,
    Throw< Entry< S211 > >,
    Dtor< Default2< S0 > >,
    Dtor< Default1< S0 > >,
    Dtor< Default0< S21 > >,
    Dtor< S21 >,
    Dtor< Default1< S2 > >,
    Dtor< Default0< S2 > >,
    Dtor< S2 >,
    Dtor< S0 >
  };
  machine.CompareToExpectedActionSequence( c1Throw1 );
  BOOST_REQUIRE( machine.terminated() );

  machine.ThrowAction( ExitFn< S11 > );
  machine.initiate();
  BOOST_CHECK_THROW( machine.process_event( C() ), TransitionTestException );
  ActionArray c1Throw2 =
  {
    Entry< S0 >,
    Entry< S1 >,
    Entry< Default0< S1 > >,
    Entry< S11 >,
    Entry< Default2< S1 > >,
    Entry< Default1< S0 > >,
    Entry< Default2< S0 > >,
    Exit< Default2< S1 > >,
    Throw< ExitFn< S11 > >,
    Dtor< S11 >,
    Dtor< Default2< S0 > >,
    Dtor< Default1< S0 > >,
    Dtor< Default0< S1 > >,
    Dtor< S1 >,
    Dtor< S0 >
  };
  machine.CompareToExpectedActionSequence( c1Throw2 );
  BOOST_REQUIRE( machine.terminated() );

  return 0;
}

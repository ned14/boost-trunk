//////////////////////////////////////////////////////////////////////////////
// (c) 2002 Andreas Huber, Zurich, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
// This program shows how a state machine can be spread over several
// translation units if necessary. A inner workings of a digital camera are
// modeled, the corresponding state chart looks as follows:
//
//  ---------------------------
// |                           |
// |      NotShooting          |
// |                           |
// |        -------------      |<---O
// |  O--->|   Idle      |     |                    --------------
// |        -------------      |   EvShutterHalf   |              |
// |          |  ^             |------------------>|   Shooting   |
// | EvConfig |  | EvConfig    |                   |              |
// |          v  |             |  EvShutterRelease |              |
// |        -------------      |<------------------|              |
// |       | Configuring |     |                   |              |
// |        -------------      |                    --------------
//  ---------------------------                              
//
// The states Configuring and Shooting will contain a large amount of logic,
// so they are implemented in their own translation units. This way one team
// could implement the Configuring mode while the other would work on the
// Shooting mode. Once the above state chart is implemented, the teams could
// work completely independently of each other.



#include "Precompiled.hpp"
#include "Camera.hpp"
#include <iostream>



char GetKey()
{
  char key;
  std::cin >> key;
  return key;
}

int main( int argc, char * argv[] )
{
  argc;
  argv;

  std::cout << "boost::fsm Camera example\n\n";

  std::cout << "h<CR>: Press shutter half-way\n";
  std::cout << "f<CR>: Press shutter fully\n";
  std::cout << "r<CR>: Release shutter\n";
  std::cout << "c<CR>: Enter/exit configuration\n";
  std::cout << "e<CR>: Exits the program\n\n";
  std::cout << "You may chain commands, e.g. hfr<CR> first presses the shutter half-way,\n";
  std::cout << "fully and then releases it.\n\n";


  Camera myCamera;
  myCamera.initiate();

  char key = GetKey();

  while ( key != 'e' )
  {
    switch( key )
    {
      case 'h':
      {
        myCamera.process_event( EvShutterHalf() );
      }
      break;

      case 'f':
      {
        myCamera.process_event( EvShutterFull() );
      }
      break;

      case 'r':
      {
        myCamera.process_event( EvShutterRelease() );
      }
      break;

      case 'c':
      {
        myCamera.process_event( EvConfig() );
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

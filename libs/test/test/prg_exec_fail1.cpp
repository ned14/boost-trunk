//  (C) Copyright Gennadiy Rozental 2001-2006.
//  (C) Copyright Beman Dawes 2001. 
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.
//
//  File        : $RCSfile$
//
//  Version     : $Revision$
//
//  Description : tests an ability of Program Execution Monitor to catch 
//  uncatched exceptions. Should fail during run.
// ***************************************************************************

#ifdef __MWERKS__
//  Metrowerks doesn't build knowledge of what runtime libraries to link with
//  into their compiler. Instead they depend on pragmas in their standard
//  library headers. That creates the odd situation that certain programs
//  won't link unless at least one standard header is included. Note that
//  this problem is highly dependent on enviroment variables and command
//  line options, so just because the problem doesn't show up on one
//  system doesn't mean it has been fixed. Remove this workaround only
//  when told by Metrowerks that it is safe to do so.
#include <cstddef> //Metrowerks linker needs at least one standard library
#endif

#include <boost/test/included/prg_exec_monitor.hpp>

int
cpp_main( int argc, char *[] )  // note the name
{
    if( argc > 0 ) // to prevent the unreachable return warning
        throw "Test error by throwing C-style string exception";

    return 0;
}

//____________________________________________________________________________//

// ***************************************************************************
//  Revision History :
//  
//  $Log$
//  Revision 1.16  2006/03/19 11:49:04  rogeeff
//  *** empty log message ***
//
//  Revision 1.15  2005/12/14 06:01:02  rogeeff
//  *** empty log message ***
//
//  Revision 1.14  2005/05/11 05:07:57  rogeeff
//  licence update
//
//  Revision 1.13  2005/05/21 06:26:10  rogeeff
//  licence update
//
//  Revision 1.12  2005/01/07 22:06:44  beman_dawes
//  Fix Metrowerks link failures for some compiler configurations. See comment in code. (fix from Ed Swartz of Metrowerks)
//
//  Revision 1.11  2003/12/01 00:42:38  rogeeff
//  prerelease cleaning
//

// ***************************************************************************

// EOF

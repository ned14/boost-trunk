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
//  system exceptions. Should fail during run.
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

#if defined(__IBMCPP__)
#pragma options check=divzero
#endif


int cpp_main( int, char *[] )  // note the name
{
    int div = 0;
    return 10 / div;
}

//____________________________________________________________________________//

// ***************************************************************************
//  Revision History :
//  
//  $Log$
//  Revision 1.15.2.1  2007/06/01 16:41:06  witt
//  Patch from Trac #583.
//
//  Revision 1.15  2006/03/19 11:49:04  rogeeff
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

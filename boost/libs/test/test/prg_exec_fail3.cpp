//  (C) Copyright Gennadiy Rozental 2002-2006.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.
//
//  File        : $RCSfile$
//
//  Version     : $Revision$
//
//  Description : tests an ability of the Program Execution Monitor to catch 
//  user fatal exceptions. Should fail during run. But not crash.
// ***************************************************************************

#include <cassert>

int cpp_main( int, char *[] )  // note the name
{
  int div = 0;

  assert( div != 0 );

  return 0;
}

//____________________________________________________________________________//

// ***************************************************************************
//  Revision History :
//  
//  $Log$
//  Revision 1.8  2006/03/19 11:49:04  rogeeff
//  *** empty log message ***
//
//  Revision 1.7  2005/05/11 05:07:57  rogeeff
//  licence update
//
//  Revision 1.6  2005/05/21 06:26:10  rogeeff
//  licence update
//
//  Revision 1.5  2003/12/01 00:42:38  rogeeff
//  prerelease cleaning
//

// ***************************************************************************

// EOF

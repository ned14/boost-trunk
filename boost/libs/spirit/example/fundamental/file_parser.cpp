/*=============================================================================
    Spirit v1.6.2
    Copyright (c) 2002 Jeff Westfahl
    http://spirit.sourceforge.net/

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at 
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
///////////////////////////////////////////////////////////////////////////////
//
//  A parser that echoes a file
//
//  [ JMW 8/05/2002 ]
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/spirit/core.hpp>
#include <boost/spirit/iterator/file_iterator.hpp>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////

using namespace boost::spirit;


////////////////////////////////////////////////////////////////////////////
//
//  Types
//
////////////////////////////////////////////////////////////////////////////

typedef char                  CharT;
typedef file_iterator <CharT> IteratorT;
typedef scanner <IteratorT>   ScannerT;
typedef rule <ScannerT>       RuleT;


////////////////////////////////////////////////////////////////////////////
//
//  Actions
//
////////////////////////////////////////////////////////////////////////////

void Echo (IteratorT const & rBegin, IteratorT const & rEnd)
{
   while (rBegin < rEnd)
   {
      std::cout << *rBegin++;
   }
}


////////////////////////////////////////////////////////////////////////////
//
//  Main program
//
////////////////////////////////////////////////////////////////////////////

int main (int argc, char * argv [])
{
   if (2 > argc)
   {
      std::cout << "Must specify a filename!\n";

      return -1;
   }

   // Create a file iterator for this file
   IteratorT _Start (argv [1]);

   if (!_Start)
   {
      std::cout << "Unable to open file!\n";

      return -1;
   }

   // Create an EOF iterator
   IteratorT _End = _Start.make_end ();

   // A simple rule
   RuleT _Rule = *(anychar_p);

   // Parse
   parse_info <IteratorT> _Info = parse (
      _Start,
      _End,
      _Rule [&Echo]
      );

   // This really shouldn't fail...
   if (_Info.full)
   {
      std::cout << "Parse succeeded!\n";
   }
   else
   {
      std::cout << "Parse failed!\n";
   }

   return 0;
}

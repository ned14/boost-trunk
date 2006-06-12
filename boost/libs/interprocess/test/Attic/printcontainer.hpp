//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gazta�aga 2004-2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PRINTCONTAINER_HPP
#define BOOST_PRINTCONTAINER_HPP

#include <functional>
#include <iostream>
#include <algorithm>
#include <boost/interprocess/detail/config_begin.hpp>

namespace boost{
namespace interprocess{
namespace test{

struct PrintValues : public std::unary_function<int, void>
{
   void operator() (int value) const
   {
      std::cout << value << " ";
   }
};

template<class Container>
void PrintContents(const Container &cont, const char *contName)
{
   std::cout<< "Printing contents of " << contName << std::endl;
   std::for_each(cont.begin(), cont.end(), PrintValues());
   std::cout<< std::endl << std::endl;
}

}  //namespace test{
}  //namespace interprocess{
}  //namespace boost{


#include <boost/interprocess/detail/config_end.hpp>

#endif //#ifndef BOOST_PRINTCONTAINER_HPP

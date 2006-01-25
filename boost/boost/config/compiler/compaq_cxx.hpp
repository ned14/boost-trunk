//  (C) Copyright John Maddock 2001 - 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Dec Alpha True64 C++ compiler setup:

#define BOOST_CXX_DEC BOOST_VERSION_NUMBER(\
    __DECCXX_VER/10000000,\
    (__DECCXX_VER-__DECCXX_VER/10000000*10000000)/100000,\
    __DECCXX_VER-__DECCXX_VER/10000*10000)

#define BOOST_COMPILER "Dec Alpha True64 " BOOST_STRINGIZE(__DECCXX_VER)

#include "boost/config/compiler/common_edg.hpp"

//
// versions check:
// Nothing to do here?




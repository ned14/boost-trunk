
// Copyright (c) Aleksey Gurtovoy 2000-2004
// Copyright (c) David Abrahams 2003-2004
//
// Use, modification and distribution are subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy 
// at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/transform.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/list_c.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/type_traits/add_pointer.hpp>

#include <boost/mpl/aux_/test/test.hpp>


MPL_TEST_CASE()
{
    typedef list<char,short,int,long,float,double> types;
    typedef list<char*,short*,int*,long*,float*,double*> pointers;
    
    typedef transform1< types,add_pointer<_1> >::type result;
    MPL_ASSERT(( equal<result,pointers>::value ));
}

MPL_TEST_CASE()
{
    typedef list_c<long,0,2,4,6,8,10> evens;
    typedef list_c<long,2,3,5,7,11,13> primes;
    typedef list_c<long,2,5,9,13,19,23> sums;

    typedef transform2< evens, primes, plus<> >::type result;
    MPL_ASSERT(( equal< result,sums,equal_to<_1,_2> >::value ));
    
    typedef transform< evens, primes, plus<> >::type result2;
    MPL_ASSERT_SAME(2,( result2,result ));
}


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
#include <boost/mpl/plus.hpp>
#include <boost/type_traits/add_pointer.hpp>

#include <boost/mpl/aux_/test/test.hpp>


MPL_TEST_CASE( copy_test )
{
    typedef list<char,short,int,long,float,double> types;
    typedef list<char*,short*,int*,long*,float*,double*> pointers;

//        typedef mpl::transform1< types,boost::add_pointer<_1> >::type result1;
//        BOOST_STATIC_ASSERT((mpl::equal<result1,pointers>::type::value));
    
    typedef transform< types,add_pointer<_1> >::type result;
    MPL_ASSERT(( mpl::equal<result,pointers>::value ));
}

#if 0    
    {
        typedef mpl::list_c<long,0,2,4,6,8,10> evens;
        typedef mpl::list_c<long,2,3,5,7,11,13> primes;
        typedef mpl::list_c<long,2,5,9,13,19,23> sums;

        typedef mpl::transform2< evens, primes, mpl::plus<> >::type result1;
        BOOST_STATIC_ASSERT((mpl::equal<result1::type,sums::type>::type::value));
        
        typedef mpl::transform< evens, primes, mpl::plus<> >::type result;
        BOOST_STATIC_ASSERT((mpl::equal<result::type,sums::type>::type::value));
    }
#endif

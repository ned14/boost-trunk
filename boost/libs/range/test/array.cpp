// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#include <boost/range.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <iostream>

using namespace boost;
using namespace std;

void check_array()
{
    const int sz = 9;
    typedef int   array_t[sz];
    int           my_array[sz]  = { 1,2,3,4,5,6,7,8,9 };
    const array_t ca           = { 1,2,3,4,5,6,7,8,10 };

#ifndef BOOST_CT_NO_STATIC_ASSERT 
    BOOST_STATIC_ASSERT(( is_same< value_type_of<array_t>::type, int >::value ));
    BOOST_STATIC_ASSERT(( is_same< iterator_of<array_t>::type, int* >::value ));
    BOOST_STATIC_ASSERT(( is_same< const_iterator_of<array_t>::type, const int* >::value ));
    BOOST_STATIC_ASSERT(( is_same< difference_type_of<array_t>::type, std::ptrdiff_t >::value ));
    BOOST_STATIC_ASSERT(( is_same< size_type_of<array_t>::type, std::size_t >::value ));
    BOOST_STATIC_ASSERT(( is_same< result_iterator_of<array_t>::type, int* >::value ));
    BOOST_STATIC_ASSERT(( is_same< result_iterator_of<const array_t>::type, const int* >::value ));
    
    BOOST_STATIC_ASSERT(( is_same< value_type_of<const array_t>::type, const int >::value ));
    BOOST_STATIC_ASSERT(( is_same< iterator_of<const array_t>::type, const int* >::value ));
    BOOST_STATIC_ASSERT(( is_same< const_iterator_of<const array_t>::type, const int* >::value ));
    BOOST_STATIC_ASSERT(( is_same< difference_type_of<const array_t>::type, std::ptrdiff_t >::value ));
    BOOST_STATIC_ASSERT(( is_same< size_type_of<const array_t>::type, std::size_t >::value ));
    BOOST_STATIC_ASSERT(( is_same< result_iterator_of<const array_t>::type, const int* >::value ));
    BOOST_STATIC_ASSERT(( is_same< result_iterator_of<const array_t>::type, const int* >::value ));
#endif
    //typedef container<const array_t>::result_iterator iter;
    //cout << typeid( iter() ).name() << endl;
    
    BOOST_CHECK_EQUAL( begin( my_array ), my_array );
    BOOST_CHECK_EQUAL( end( my_array ), my_array + size( my_array ) );
    BOOST_CHECK_EQUAL( empty( my_array ), false );
    //BOOST_CHECK( size( my_array ) == sizeof( sizer( my_array ) ) );

    BOOST_CHECK_EQUAL( begin( ca ), ca );
    BOOST_CHECK_EQUAL( end( ca ), ca + size( ca ) );
    BOOST_CHECK_EQUAL( empty( ca ),false );
    //BOOST_CHECK( size( ca ) == sizeof( sizer( ca ) ) );

}

#include <boost/test/included/unit_test_framework.hpp> 

using boost::unit_test_framework::test_suite;

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite* test = BOOST_TEST_SUITE( "Range Test Suite" );

    test->add( BOOST_TEST_CASE( &check_array ) );

    return test;
}






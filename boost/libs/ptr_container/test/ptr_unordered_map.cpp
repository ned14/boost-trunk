 
#include "associative_test_data.hpp"
#include "concept_check_data.hpp"
#include <boost/ptr_container/ptr_map.hpp>
#include <string>

using namespace std;

void test_unordered_map()
{
    typedef_test< ptr_map<int, Base>, Derived >();
    typedef_test< ptr_map<int, Value>, Value >();

    associative_container_test< ptr_map<int, Base>, Base, Derived >();
    associative_container_test< ptr_map<int, Value>, Value, Value >();
    
    typedef_test< ptr_multimap<int, Base>, Derived >();
    typedef_test< ptr_multimap<int, Value>, Value >();

    associative_container_test< ptr_multimap<int, Base>, Base, Derived >();
    associative_container_test< ptr_multimap<int, Value>, Value, Value >();
    
    string joe   = "joe";
    string brian = "brian";
    
    ptr_map<string,int> m;
    m.insert( joe, new int( 4 ) );
    m.insert( brian, new int( 6 ) );
    m[ joe ]   += 56;
    m[ brian ] += 10;

    try
    {
        m[ "hans" ] = 4;
    }
    catch( const bad_ptr_container_operation& )
    { }
}



#include <boost/test/included/unit_test_framework.hpp> 

using boost::unit_test_framework::test_suite;

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite* test = BOOST_TEST_SUITE( "Smart Container Test Suite" );

    test->add( BOOST_TEST_CASE( &test_unordered_map ) );

    return test;
}





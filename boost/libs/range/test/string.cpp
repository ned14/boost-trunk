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
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/config.hpp>
#include <vector>
#include <fstream>
#include <algorithm>

template< typename Container, typename T >
BOOST_DEDUCED_TYPENAME boost::iterator_of<Container>::type
find( Container& c,  T value )
{
    return std::find( boost::begin( c ), boost::end( c ), value );
}

template< typename Container, typename T >
BOOST_DEDUCED_TYPENAME boost::const_iterator_of<Container>::type
find( const Container& c, T value )
{
    return std::find( boost::begin( c ), boost::end( c ), value );
}

std::vector<char> 
check_rvalue_return()
{
    return std::vector<char>( 10, 'm' ); 
}

using namespace boost;


void check_char()
{
    typedef char*                  char_iterator_t;
    typedef char                   char_array_t[10];
    const char*      char_s       = "a string";
    char             my_string[]  = "another string";
    const unsigned        my_string_length = 14;

    
    BOOST_STATIC_ASSERT(( is_same<  value_type_of<char_iterator_t>::type, 
                                    detail::iterator_traits<char_iterator_t>::value_type>::value ));
    BOOST_STATIC_ASSERT(( is_same<  iterator_of<char_iterator_t>::type, char_iterator_t >::value ));
    BOOST_STATIC_ASSERT(( is_same<  const_iterator_of<char_iterator_t>::type, const char* >::value ));
    BOOST_STATIC_ASSERT(( is_same<  difference_type_of<char_iterator_t>::type,                           
		                            ::std::ptrdiff_t >::value ));
    BOOST_STATIC_ASSERT(( is_same<  size_type_of<char_iterator_t>::type, std::size_t >::value ));
    BOOST_STATIC_ASSERT(( is_same<  result_iterator_of<char_iterator_t>::type, char_iterator_t >::value ));
    BOOST_STATIC_ASSERT(( is_same<  result_iterator_of<const char*>::type, const char* >::value ));
    //
    // note: why does is_same<  result_iterator<const char_iterator_t>::type, const char* >::value
    // fail?!?
    
    BOOST_STATIC_ASSERT(( is_same<  value_type_of<char_array_t>::type, 
                                    char>::value ));
    BOOST_STATIC_ASSERT(( is_same<  iterator_of<char_array_t>::type, char* >::value ));
    BOOST_STATIC_ASSERT(( is_same<  const_iterator_of<char_array_t>::type, const char* >::value ));
    BOOST_STATIC_ASSERT(( is_same<  difference_type_of<char_array_t>::type,                           
		                            ::std::ptrdiff_t >::value ));
    BOOST_STATIC_ASSERT(( is_same<  size_type_of<char_array_t>::type, std::size_t >::value ));
    BOOST_STATIC_ASSERT(( is_same<  result_iterator_of<char_array_t>::type, char* >::value ));
    BOOST_STATIC_ASSERT(( is_same<  result_iterator_of<const char_array_t>::type, const char* >::value ));

    BOOST_CHECK_EQUAL( begin( char_s ), char_s );
	const char* end1 = begin( char_s ) + size( char_s );
    BOOST_CHECK_EQUAL( end( char_s ), end1 );
    BOOST_CHECK_EQUAL( empty( char_s ), (char_s == 0 || char_s[0] == char()) );
    BOOST_CHECK_EQUAL( size( char_s ), std::char_traits<char>::length( char_s ) );
    
	BOOST_CHECK_EQUAL( begin( my_string ), my_string );
	const char* end2 = begin( my_string ) + size( my_string );
    BOOST_CHECK_EQUAL( end( my_string ), end2 );
    BOOST_CHECK_EQUAL( empty( my_string ), (my_string == 0 || my_string[0] == char()) );
    BOOST_CHECK_EQUAL( size( my_string ), my_string_length );
    BOOST_CHECK_EQUAL( size( my_string ), std::char_traits<char>::length( my_string ) );


    char to_search = 'n';
    BOOST_CHECK( find( char_s, to_search ) != end( char_s ) );
    BOOST_CHECK( find( my_string, to_search ) != end( my_string ) );
}



void check_string()
{
    check_char();
//    check_char<volatile char>();
//    check_char<const char>();
//    check_char<const volatile char>();
    
#ifndef BOOST_NO_STD_WSTRING
    typedef wchar_t*               wchar_iterator_t;          
    const wchar_t*  char_ws      = L"a wide string";
    wchar_t         my_wstring[] = L"another wide string";
    
    BOOST_STATIC_ASSERT(( is_same< value_type_of<wchar_iterator_t>::type, 
                                   detail::iterator_traits<wchar_iterator_t>::value_type>::value ));
    BOOST_STATIC_ASSERT(( is_same< iterator_of<wchar_iterator_t>::type, wchar_iterator_t >::value ));
    BOOST_STATIC_ASSERT(( is_same< const_iterator_of<wchar_iterator_t>::type, const wchar_t* >::value ));
    BOOST_STATIC_ASSERT(( is_same< difference_type_of<wchar_iterator_t>::type,                           
                                   detail::iterator_traits<wchar_iterator_t>::difference_type >::value ));
    BOOST_STATIC_ASSERT(( is_same< size_type_of<wchar_iterator_t>::type, std::size_t >::value ));
    BOOST_STATIC_ASSERT(( is_same< result_iterator_of<wchar_iterator_t>::type, wchar_iterator_t >::value ));
    BOOST_STATIC_ASSERT(( is_same< result_iterator_of<const wchar_t*>::type, const wchar_t* >::value ));
    
    BOOST_CHECK_EQUAL( begin( char_ws ), char_ws );
    BOOST_CHECK_EQUAL( end( char_ws ), (begin( char_ws ) + size( char_ws )) );
    BOOST_CHECK_EQUAL( empty( char_ws ), (char_ws == 0 || char_ws[0] == wchar_t()) );
    BOOST_CHECK_EQUAL( size( char_ws ), std::char_traits<wchar_t>::length( char_ws ) );
        
    wchar_t to_search = L'n';
    BOOST_CHECK( find( char_ws, to_search ) != end( char_ws ) );    
    BOOST_CHECK( find( my_wstring, to_search ) != end( my_wstring ) );
#endif  
    
    find( check_rvalue_return(), 'n' );
	
}



#include <boost/test/included/unit_test_framework.hpp> 

using boost::unit_test_framework::test_suite;

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite* test = BOOST_TEST_SUITE( "Range Test Suite" );

    test->add( BOOST_TEST_CASE( &check_string ) );

    return test;
}







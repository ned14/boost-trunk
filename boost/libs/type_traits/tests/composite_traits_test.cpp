
//  (C) Copyright John Maddock 2000. Permission to copy, use, modify, sell and   
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

#include <boost/type_traits/composite_traits.hpp>
#include <boost/utility.hpp>
#include <boost/test/cpp_main.cpp>

#ifdef __BORLANDC__
#pragma hrdstop
#endif
#include "boost/type_traits/type_traits_test.hpp"

NESTED_DECL(is_array)
NESTED_DECL(is_pointer)
NESTED_DECL(is_reference)

int cpp_main(int argc, char* argv[])
{
   NESTED_TEST(is_array, int)
   NESTED_TEST(is_array, int[2])
   NESTED_TEST(is_array, int[3][4])
   NESTED_TEST(is_array, int const [5])
   NESTED_TEST(is_array, int(&)[2])
   NESTED_TEST(is_array, int (*)(double))
   NESTED_TEST(is_pointer, int)
   NESTED_TEST(is_pointer, int*)
   NESTED_TEST(is_reference, int)
   NESTED_TEST(is_reference, int&)

   value_test(false, boost::is_array<int>::value)
   value_test(false, boost::is_array<int*>::value)
   value_test(false, boost::is_array<const int*>::value)
   value_test(false, boost::is_array<const volatile int*>::value)
   value_test(false, boost::is_array<int*const>::value)
   value_test(false, boost::is_array<const int*volatile>::value)
   value_test(false, boost::is_array<const volatile int*const>::value)
   value_test(true, boost::is_array<int[2]>::value)
   value_test(true, boost::is_array<const int[2]>::value)
   value_test(true, boost::is_array<const volatile int[2]>::value)
   value_test(true, boost::is_array<int[2][3]>::value)
   value_test(true, boost::is_array<UDT[2]>::value)
   value_test(false, boost::is_array<int(&)[2]>::value)
   value_test(false, boost::is_array<f1>::value)
   value_test(false, boost::is_array<void>::value)
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
   value_test(false, boost::is_array<test_abc1>::value)
#endif

   value_test(false, boost::is_pointer<int>::value)
   value_test(false, boost::is_pointer<int&>::value)
   value_test(true, boost::is_pointer<int*>::value)
   value_test(true, boost::is_pointer<const int*>::value)
   value_test(true, boost::is_pointer<volatile int*>::value)
   value_test(true, boost::is_pointer<non_pointer*>::value)
   // these were false in previous versions (JM 20 Dec 2000):
   value_test(true, boost::is_pointer<int*const>::value)
   value_test(true, boost::is_pointer<int*volatile>::value)
   value_test(true, boost::is_pointer<int*const volatile>::value)
   // JM 02 Oct 2000:
   value_test(false, boost::is_pointer<non_pointer>::value)
   value_test(false, boost::is_pointer<int*&>::value)
   value_test(false, boost::is_pointer<int(&)[2]>::value)
   value_test(false, boost::is_pointer<int[2]>::value)
   value_test(false, boost::is_pointer<char[sizeof(void*)]>::value)
   value_test(false, boost::is_pointer<void>::value)

   value_test(true, boost::is_pointer<f1>::value)
   value_test(true, boost::is_pointer<f2>::value)
   value_test(true, boost::is_pointer<f3>::value)
   // Steve: was 'true', should be 'false', via 3.9.2p3
   value_test(false, boost::is_pointer<mf1>::value)
   value_test(false, boost::is_pointer<mf2>::value)
   value_test(false, boost::is_pointer<mf3>::value)
   value_test(false, boost::is_pointer<mf4>::value)
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
   value_test(false, boost::is_pointer<test_abc1>::value)
#endif

   value_test(false, boost::is_reference<bool>::value)
   value_test(true, boost::is_reference<int&>::value)
   value_test(true, boost::is_reference<const int&>::value)
   value_test(true, boost::is_reference<volatile int &>::value)
   value_test(true, boost::is_reference<const volatile int &>::value)
   value_test(true, boost::is_reference<r_type>::value)
   value_test(true, boost::is_reference<cr_type>::value)
   value_test(true, boost::is_reference<const UDT&>::value)
   value_test(false, boost::is_reference<void>::value)
#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) && !defined(BOOST_MSVC)
   value_test(false, boost::is_reference<test_abc1>::value)
#endif

   value_test(false, boost::is_member_pointer<f1>::value)
   value_test(false, boost::is_member_pointer<f2>::value)
   value_test(false, boost::is_member_pointer<f3>::value)
   value_test(false, boost::is_member_pointer<void*>::value)
   value_test(true, boost::is_member_pointer<mf1>::value)
   value_test(true, boost::is_member_pointer<mf2>::value)
   value_test(true, boost::is_member_pointer<mf3>::value)
   value_test(true, boost::is_member_pointer<mf4>::value)
   value_test(false, boost::is_member_pointer<void>::value)
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
   value_test(false, boost::is_member_pointer<test_abc1>::value)
#endif

   value_test(false, boost::is_enum<int>::value)
   value_test(true, boost::is_enum<enum_UDT>::value)
   value_test(false, boost::is_enum<int_convertible>::value)
   //value_test(false, boost::is_enum<int&>::value)
   value_test(false, boost::is_enum<void>::value)
#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) && !defined(BOOST_MSVC)
   value_test(false, boost::is_enum<test_abc1>::value)
#endif

   return check_result(argc, argv);
}

//
// define the number of failures expected for given compilers:
#ifdef __BORLANDC__
unsigned int expected_failures = 2;
#elif defined(__SUNPRO_CC)
unsigned int expected_failures = 11;
#elif defined(__GNUC__)
unsigned int expected_failures = 1; // can't handle cv-qualified references
#elif defined(BOOST_MSVC)
unsigned int expected_failures = 1;
#elif defined(__MWERKS__)
unsigned int expected_failures = 1; // is_enum doesn't work
#else
unsigned int expected_failures = 0;
#endif





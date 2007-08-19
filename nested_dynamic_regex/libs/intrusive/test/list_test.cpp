/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Olaf Krzikalla 2004-2006.
// (C) Copyright Ion Gaztanaga  2006-2007.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/list.hpp>
#include <boost/intrusive/detail/pointer_to_other.hpp>
#include "itestvalue.hpp"
#include "smart_ptr.hpp"
#include "common_functors.hpp"
#include <vector>
#include <boost/detail/lightweight_test.hpp>
#include "test_macros.hpp"
#include "test_container.hpp"

using namespace boost::intrusive;

template<class ValueTraits>
struct test_list 
{
   typedef typename ValueTraits::value_type value_type;
   static void test_all(std::vector<value_type>& values);
   static void test_front_back(std::vector<value_type>& values);
   static void test_sort(std::vector<value_type>& values);
   static void test_insert(std::vector<value_type>& values);
   static void test_shift(std::vector<value_type>& values);
   static void test_swap(std::vector<value_type>& values);
   static void test_clone(std::vector<value_type>& values);
};

template<class ValueTraits>
void test_list<ValueTraits>::test_all(std::vector<typename ValueTraits::value_type>& values)
{
   typedef boost::intrusive::list
      < ValueTraits
      , ValueTraits::value_type::constant_time_size
      , std::size_t 
      > list_type;

   {
      list_type list(values.begin(), values.end());
      test::test_container(list);
      list.clear();
      list.insert(list.end(), values.begin(), values.end());
      test::test_sequence_container(list, values);
   }

   test_front_back(values);
   test_sort(values);
   test_insert(values);
   test_shift(values);
   test_swap(values);
   test_clone(values);

   list_type testlist(values.begin(), values.end());
   list_type testlist2;
}

//test: push_front, pop_front, push_back, pop_back, front, back, size, empty:
template<class ValueTraits>
void test_list<ValueTraits>
   ::test_front_back(std::vector<typename ValueTraits::value_type>& values)
{
   typedef boost::intrusive::list
      < ValueTraits
      , ValueTraits::value_type::constant_time_size
      , std::size_t 
      > list_type;
   list_type testlist;
   BOOST_TEST (testlist.empty());

   testlist.push_back (values[0]);
   BOOST_TEST (testlist.size() == 1);
   BOOST_TEST (&testlist.front() == &values[0]);
   BOOST_TEST (&testlist.back() == &values[0]);

   testlist.push_front (values[1]);
   BOOST_TEST (testlist.size() == 2);
   BOOST_TEST (&testlist.front() == &values[1]);
   BOOST_TEST (&testlist.back() == &values[0]);

   testlist.pop_back();
   BOOST_TEST (testlist.size() == 1);
   const list_type &const_testlist = testlist;
   BOOST_TEST (&const_testlist.front() == &values[1]);
   BOOST_TEST (&const_testlist.back() == &values[1]);

   testlist.pop_front();
   BOOST_TEST (testlist.empty());
}  


//test: constructor, iterator, reverse_iterator, sort, reverse:
template<class ValueTraits>
void test_list<ValueTraits>
   ::test_sort(std::vector<typename ValueTraits::value_type>& values)
{
   typedef typename ValueTraits::value_type testvalue_t;
   std::vector<int> expected;
   typedef boost::intrusive::list
      < ValueTraits
      , ValueTraits::value_type::constant_time_size
      , std::size_t 
      > list_type;
   list_type testlist(values.begin(), values.end());

   {  int init_values [] = { 1, 2, 3, 4, 5 };
      TEST_INTRUSIVE_SEQUENCE( init_values, testlist.begin() );  }

   testlist.sort (even_odd());
   {  int init_values [] = { 5, 3, 1, 4, 2 };
      TEST_INTRUSIVE_SEQUENCE( init_values, testlist.rbegin() );  }

   testlist.reverse();
   {  int init_values [] = { 5, 3, 1, 4, 2 };
      TEST_INTRUSIVE_SEQUENCE( init_values, testlist.begin() );  }
}
  
//test: assign, insert, const_iterator, const_reverse_iterator, erase, iterator_to:
template<class ValueTraits>
void test_list<ValueTraits>
   ::test_insert(std::vector<typename ValueTraits::value_type>& values)
{
   typedef typename ValueTraits::value_type testvalue_t;
   std::vector<int> expected;
   typedef boost::intrusive::list
      < ValueTraits
      , ValueTraits::value_type::constant_time_size
      , std::size_t 
      > list_type;
   list_type testlist;
   testlist.assign (&values[0] + 2, &values[0] + 5);

   const list_type& const_testlist = testlist;
   {  int init_values [] = { 3, 4, 5 };
      TEST_INTRUSIVE_SEQUENCE( init_values, const_testlist.begin() );  }

   typename list_type::iterator i = ++testlist.begin();
   BOOST_TEST (i->value_ == 4);

   {
   typename list_type::const_iterator ci = typename list_type::iterator();
   //typename list_type::iterator i = typename list_type::const_iterator();
   }

   testlist.insert (i, values[0]);
   {  int init_values [] = { 5, 4, 1, 3 };
      TEST_INTRUSIVE_SEQUENCE( init_values, const_testlist.rbegin() );  }

   i = testlist.iterator_to (values[4]);
   BOOST_TEST (&*i == &values[4]);

   i = testlist.erase (i);
   BOOST_TEST (i == testlist.end());

   {  int init_values [] = { 3, 1, 4 };
      TEST_INTRUSIVE_SEQUENCE( init_values, const_testlist.begin() );  }
}

template<class ValueTraits>
void test_list<ValueTraits>
   ::test_shift(std::vector<typename ValueTraits::value_type>& values)
{
   typedef typename ValueTraits::value_type testvalue_t;
   typedef boost::intrusive::list
      < ValueTraits
      , ValueTraits::value_type::constant_time_size
      , std::size_t 
      > list_type;
   list_type testlist;
   std::vector<int> expected;

   const int num_values = (int)values.size();
   std::vector<int> expected_values(num_values);

   //Shift forward all possible positions 3 times
   for(int i = 0; i < num_values*3; ++i){
      testlist.assign(values.begin(), values.end());
      testlist.shift_forward(i);
      for(int j = 0; j < num_values; ++j){
         expected_values[(j + num_values - i%num_values) % num_values] = (j + 1);
      }
      TEST_INTRUSIVE_SEQUENCE_EXPECTED(expected_values, testlist.begin());
      testlist.clear();
   }

   //Shift backwards all possible positions
   for(int i = 0; i < num_values*3; ++i){
      testlist.assign(values.begin(), values.end());
      testlist.shift_backwards(i);
      for(int j = 0; j < num_values; ++j){
         expected_values[(j + i) % num_values] = (j + 1);
      }
      TEST_INTRUSIVE_SEQUENCE_EXPECTED(expected_values, testlist.begin());
      testlist.clear();
   }
} 

//test: insert (seq-version), swap, splice, erase (seq-version):
template<class ValueTraits>
void test_list<ValueTraits>
   ::test_swap(std::vector<typename ValueTraits::value_type>& values)
{
   typedef typename ValueTraits::value_type testvalue_t;
   typedef boost::intrusive::list
      <ValueTraits
      ,ValueTraits::value_type::constant_time_size, std::size_t 
      > list_type;
   std::vector<int> expected;
   {
      list_type testlist1 (&values[0], &values[0] + 2);
      list_type testlist2;
      testlist2.insert (testlist2.end(), &values[0] + 2, &values[0] + 5);
      testlist1.swap (testlist2);

      {  int init_values [] = { 3, 4, 5 };
         TEST_INTRUSIVE_SEQUENCE( init_values, testlist1.begin() );  }
      {  int init_values [] = { 1, 2 };
         TEST_INTRUSIVE_SEQUENCE( init_values, testlist2.begin() );  }

      testlist2.splice (++testlist2.begin(), testlist1);
      {  int init_values [] = { 1, 3, 4, 5, 2 };
         TEST_INTRUSIVE_SEQUENCE( init_values, testlist2.begin() );  }

      BOOST_TEST (testlist1.empty());

      testlist1.splice (testlist1.end(), testlist2, ++(++testlist2.begin()));
      {  int init_values [] = { 4 };
         TEST_INTRUSIVE_SEQUENCE( init_values, testlist1.begin() );  }

      {  int init_values [] = { 1, 3, 5, 2 };
         TEST_INTRUSIVE_SEQUENCE( init_values, testlist2.begin() );  }

      testlist1.splice (testlist1.end(), testlist2, 
                        testlist2.begin(), ----testlist2.end());
      {  int init_values [] = { 4, 1, 3 };
         TEST_INTRUSIVE_SEQUENCE( init_values, testlist1.begin() );  }
      {  int init_values [] = { 5, 2 };
         TEST_INTRUSIVE_SEQUENCE( init_values, testlist2.begin() );  }

      testlist1.erase (testlist1.iterator_to(values[0]), testlist1.end());
      BOOST_TEST (testlist1.size() == 1);
      BOOST_TEST (&testlist1.front() == &values[3]);
   }
   {
      list_type testlist1 (&values[0], &values[0] + 2);
      list_type testlist2 (&values[0] + 3, &values[0] + 5);

      values[0].swap_nodes(values[2]);
      {  int init_values [] = { 3, 2 };
         TEST_INTRUSIVE_SEQUENCE( init_values, testlist1.begin() );  }

      values[2].swap_nodes(values[4]);
      {  int init_values [] = { 5, 2 };
         TEST_INTRUSIVE_SEQUENCE( init_values, testlist1.begin() );  }
      {  int init_values [] = { 4, 3 };
         TEST_INTRUSIVE_SEQUENCE( init_values, testlist2.begin() );  }
   }
}

template<class ValueTraits>
void test_list<ValueTraits>
   ::test_clone(std::vector<typename ValueTraits::value_type>& values)
{
   typedef typename ValueTraits::value_type testvalue_t;
   std::vector<int> expected;
   typedef boost::intrusive::list
      <ValueTraits
      ,ValueTraits::value_type::constant_time_size, std::size_t 
      > list_type;

      list_type testlist1 (&values[0], &values[0] + values.size());
      list_type testlist2;

      testlist2.clone_from(testlist1, test::new_cloner(), test::delete_disposer());
      BOOST_TEST (testlist2 == testlist1);
      testlist2.clear_and_dispose(test::delete_disposer());
      BOOST_TEST (testlist2.empty());
}

template<class VoidPointer, bool constant_time_size>
class test_main_template
{
   public:
   int operator()()
   {
      typedef testvalue<VoidPointer, constant_time_size> testvalue_t;
      std::vector<testvalue_t> data (5);
      for (int i = 0; i < 5; ++i)
         data[i].value_ = i + 1; 

      test_list <typename testvalue_t::list_base_hook_t::template
         value_traits<testvalue_t> >::test_all(data);

      test_list <typename testvalue_t::list_member_hook_t::template
            value_traits<testvalue_t, &testvalue_t::list_node_> >::test_all(data);

      return 0;
   }
};

template<class VoidPointer>
class test_main_template<VoidPointer, false>
{
   public:
   int operator()()
   {
      typedef testvalue<VoidPointer, false> testvalue_t;
      std::vector<testvalue_t> data (5);
      for (int i = 0; i < 5; ++i)
         data[i].value_ = i + 1; 

      test_list <typename testvalue_t::list_base_hook_t::template
         value_traits<testvalue_t> >::test_all(data);

      test_list <typename testvalue_t::list_member_hook_t::template
            value_traits<testvalue_t, &testvalue_t::list_node_> >::test_all(data);

      test_list <typename testvalue_t::list_auto_base_hook_t::template
         value_traits<testvalue_t> >::test_all(data);

      test_list <typename testvalue_t::list_auto_member_hook_t::template
            value_traits<testvalue_t, &testvalue_t::list_auto_node_> >::test_all(data);
      return 0;
   }
};

//Explicit instantiations of non-counted classes
//template class boost::intrusive::list<list_base_raw, false>;
//template class boost::intrusive::list<list_member_raw, false>;
//template class boost::intrusive::list<list_auto_base_raw, false>;
//template class boost::intrusive::list<list_auto_member_raw, false>;
//template class boost::intrusive::list<list_base_smart, false>;
//template class boost::intrusive::list<list_member_smart, false>;
//template class boost::intrusive::list<list_auto_base_smart, false>;
//template class boost::intrusive::list<list_auto_member_smart, false>;

//Explicit instantiation of counted classes
//template class boost::intrusive::list<list_base_raw_t, true>;
//template class boost::intrusive::list<list_member_raw_t, true>;
//template class boost::intrusive::list<list_base_smart_t, true>;
//template class boost::intrusive::list<list_member_smart_t, true>;

int main( int, char* [] ) 
{
   test_main_template<void*, false>()();
   test_main_template<boost::intrusive::smart_ptr<void>, false>()();
   test_main_template<void*, true>()();
   test_main_template<boost::intrusive::smart_ptr<void>, true>()();
   return boost::report_errors();
}
#include <boost/intrusive/detail/config_end.hpp>

/* Boost.MultiIndex test for copying and assignment.
 *
 * Copyright 2003-2005 Joaqu�n M L�pez Mu�oz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#include "test_copy_assignment.hpp"

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <algorithm>
#include <list>
#include <numeric>
#include <vector>
#include "pre_multi_index.hpp"
#include "employee.hpp"
#include <boost/test/test_tools.hpp>

using namespace boost::multi_index;

void test_copy_assignment()
{
  employee_set es;
  employee_set es2(es);

  employee_set::allocator_type al=es.get_allocator();
  al=get<1>(es).get_allocator();
  al=get<2>(es).get_allocator();
  al=get<3>(es).get_allocator();
  al=get<4>(es).get_allocator();

  BOOST_CHECK(es2.empty());

  es2.insert(employee(0,"Joe",31,1123));
  es2.insert(employee(1,"Robert",27,5601));
  es2.insert(employee(2,"John",40,7889));
  es2.insert(employee(2,"Aristotle",2388,3357)); /* clash */
  es2.insert(employee(3,"Albert",20,9012));
  es2.insert(employee(4,"John",57,1002));
  es2.insert(employee(0,"Andrew",60,2302));      /* clash */

  employee_set es3(es2);

  BOOST_CHECK(es2==es3);
  BOOST_CHECK(get<2>(es2)==get<2>(es3));
  BOOST_CHECK(get<3>(es2)==get<3>(es3));

  employee_set es4;
  employee_set_by_name& i1=get<name>(es4);
  i1=get<1>(es2);

  BOOST_CHECK(es4==es2);

  employee_set es5;
  employee_set_by_age& i2=get<age>(es5);
  i2=get<2>(es2);

  BOOST_CHECK(i2==get<2>(es2));

  employee_set es6;
  employee_set_as_inserted& i3=get<as_inserted>(es6);
  i3=get<3>(es2);

  BOOST_CHECK(i3==get<3>(es2));

  std::list<employee> l;
  l.push_back(employee(3,"Anna",31,5388));
  l.push_back(employee(1,"Rachel",27,9012));
  l.push_back(employee(2,"Agatha",40,1520));

#if BOOST_WORKAROUND(BOOST_MSVC,<1300)
  employee_set es7;
  es7.insert(l.begin(),l.end());
#else
  employee_set es7(l.begin(),l.end());
#endif

  l.sort();

  BOOST_CHECK(es7.size()==l.size()&&
              std::equal(es7.begin(),es7.end(),l.begin()));

  multi_index_container<int,indexed_by<sequenced<> > > ss;

  int a[]={0,1,2,3,4,5};
  std::size_t sa=sizeof(a)/sizeof(a[0]);

  ss.assign(&a[0],&a[sa]);

  BOOST_CHECK(ss.size()==sa&&std::equal(ss.begin(),ss.end(),&a[0]));

  ss.assign(&a[0],&a[sa]);

  BOOST_CHECK(ss.size()==sa&&std::equal(ss.begin(),ss.end(),&a[0]));

  ss.assign((std::size_t)18,37);
  BOOST_CHECK(ss.size()==18&&std::accumulate(ss.begin(),ss.end(),0)==666);

  ss.assign((std::size_t)12,167);
  BOOST_CHECK(ss.size()==12&&std::accumulate(ss.begin(),ss.end(),0)==2004);
}

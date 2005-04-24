// Copyright David Abrahams, Daniel Wallin 2003. Use, modification and 
// distribution is subject to the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/parameter.hpp>
#include <cassert>
#include <string.h>
#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include <boost/static_assert.hpp>

#include "basics.hpp"

namespace test
{
 
  template<class Params>
  int f_impl(const Params& p)
  { 
      p[tester](
          p[name]
        , p[value || boost::bind(&value_default) ]
        , p[index | 999 ]
      );
      return 1;
  }

  template<class Tester, class Name, class Value, class Index>
  int f(Tester const& t, const Name& name_, 
      const Value& value_, const Index& index_)
  {
      return f_impl(f_parameters()(t, name_, value_, index_));
  }

  template<class Tester, class Name, class Value>
  int f(Tester const& t, const Name& name_, const Value& value_)
  {
      return f_impl(f_parameters()(t, name_, value_));
  }

  template<class Tester, class Name>
  int f(Tester const& t, const Name& name_)
  {
      return f_impl(f_parameters()(t, name_));
  }

  template<class Params>
  int f_list(Params const& params)
  {
      return f_impl(params);
  }

}

int main()
{
   using test::f;
   using test::f_list;
   using test::name;
   using test::value;
   using test::index;
   using test::tester;

   f(
       test::values(S("foo"), S("bar"), S("baz"))
     , S("foo"), S("bar"), S("baz")
   );

   int x = 56;
   f(
       test::values("foo", 666.222, 56)
     , index = boost::ref(x), name = "foo"
   );

   f_list((
       tester = test::values("foo", 666.222, 56)
     , index = boost::ref(x)
     , name = "foo"
   ));
   
   //f(index = 56, name = 55); // won't compile
   return 0;
}


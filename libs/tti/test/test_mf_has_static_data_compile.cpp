
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include "test_mf_has_static_data.hpp"
#include <boost/mpl/assert.hpp>
#include <boost/mpl/quote.hpp>

int main()
  {
  
  using namespace boost::mpl::placeholders;
  
  // You can always instantiate without compiler errors
  
  boost::tti::mf_has_static_member_data
    <
    BOOST_TTI_HAS_STATIC_MEMBER_DATA_GEN(SomeStaticData)<_,_>,
    boost::mpl::identity<AnotherType>,
    boost::mpl::identity<double>
    > aVar;
  
  // Compile time asserts
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_static_member_data
                      <
                      BOOST_TTI_HAS_STATIC_MEMBER_DATA_GEN(DSMember)<_,_>,
                      boost::mpl::identity<AType>,
                      boost::mpl::identity<short>
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_static_member_data
                      <
                      boost::mpl::quote2<BOOST_TTI_HAS_STATIC_MEMBER_DATA_GEN(DSMember)>,
                      boost::mpl::identity<AType>,
                      boost::mpl::identity<short>
                      >
                  ));
  
  return 0;

  }


//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include "test_mf_mem_type.hpp"
#include <boost/mpl/assert.hpp>
#include <boost/mpl/quote.hpp>

int main()
  {
  
  using namespace boost::mpl::placeholders;
  
  BOOST_MPL_ASSERT((boost::tti::mf_valid_member_type
                      <
                      boost::tti::mf_member_type
                        <
                        BOOST_TTI_MEMBER_TYPE_GEN(AnIntType)<_>,
                        boost::mpl::identity<AType>
                        >
                      >
                  ));
            
  BOOST_MPL_ASSERT((boost::tti::mf_valid_member_type
                      <
                      boost::tti::mf_member_type
                        <
                        NameStruct<_>,
                        boost::mpl::identity<AType>
                        >
                      >
                  ));
            
  BOOST_MPL_ASSERT((boost::tti::mf_valid_member_type
                      <
                      boost::tti::mf_member_type
                        <
                        BOOST_TTI_MEMBER_TYPE_GEN(AnIntTypeReference)<_>,
                        boost::mpl::identity<AType>
                        >
                      >
                  ));
            
  BOOST_MPL_ASSERT((boost::tti::mf_valid_member_type
                      <
                      boost::tti::mf_member_type
                        <
                        BOOST_TTI_MEMBER_TYPE_GEN(BType)<_>,
                        boost::mpl::identity<AType>
                        >
                      >
                  ));
            
  BOOST_MPL_ASSERT((boost::tti::mf_valid_member_type
                      <
                      boost::tti::mf_member_type
                        <
                        TheInteger<_>,
                        BOOST_TTI_MEMBER_TYPE_GEN(BType)<AType>
                        >
                      >
                  ));
            
  BOOST_MPL_ASSERT((boost::tti::mf_valid_member_type
                      <
                      boost::tti::mf_member_type
                        <
                        BOOST_TTI_MEMBER_TYPE_GEN(CType)<_>,
                        BOOST_TTI_MEMBER_TYPE_GEN(BType)<AType>
                        >
                      >
                  ));
            
  BOOST_MPL_ASSERT((boost::tti::mf_valid_member_type
                      <
                      boost::tti::mf_member_type
                        <
                        BOOST_TTI_MEMBER_TYPE_GEN(AnotherIntegerType)<_>,
                        boost::tti::mf_member_type
                          <
                          BOOST_TTI_MEMBER_TYPE_GEN(CType)<_>,
                          BOOST_TTI_MEMBER_TYPE_GEN(BType)<AType>
                          >
                        >
                      >
                  ));
            
  BOOST_MPL_ASSERT((boost::tti::mf_valid_member_type
                      <
                      boost::tti::mf_member_type
                        <
                        SomethingElse<_>,
                        boost::mpl::identity<AnotherType>
                        >
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_valid_member_type
                      <
                      boost::tti::mf_member_type
                        <
                        boost::mpl::quote1<BOOST_TTI_MEMBER_TYPE_GEN(AnIntType)>,
                        boost::mpl::identity<AType>
                        >
                      >
                  ));
            
  BOOST_MPL_ASSERT((boost::tti::mf_valid_member_type
                      <
                      boost::tti::mf_member_type
                        <
                        boost::mpl::quote1<NameStruct>,
                        boost::mpl::identity<AType>
                        >
                      >
                  ));
            
  BOOST_MPL_ASSERT((boost::tti::mf_valid_member_type
                      <
                      boost::tti::mf_member_type
                        <
                        boost::mpl::quote1<BOOST_TTI_MEMBER_TYPE_GEN(AnIntTypeReference)>,
                        boost::mpl::identity<AType>
                        >
                      >
                  ));
            
  BOOST_MPL_ASSERT((boost::tti::mf_valid_member_type
                      <
                      boost::tti::mf_member_type
                        <
                        boost::mpl::quote1<BOOST_TTI_MEMBER_TYPE_GEN(BType)>,
                        boost::mpl::identity<AType>
                        >
                      >
                  ));
            
  BOOST_MPL_ASSERT((boost::tti::mf_valid_member_type
                      <
                      boost::tti::mf_member_type
                        <
                        boost::mpl::quote1<TheInteger>,
                        BOOST_TTI_MEMBER_TYPE_GEN(BType)<AType>
                        >
                      >
                  ));
            
  BOOST_MPL_ASSERT((boost::tti::mf_valid_member_type
                      <
                      boost::tti::mf_member_type
                        <
                        boost::mpl::quote1<BOOST_TTI_MEMBER_TYPE_GEN(CType)>,
                        BOOST_TTI_MEMBER_TYPE_GEN(BType)<AType>
                        >
                      >
                  ));
            
  BOOST_MPL_ASSERT((boost::tti::mf_valid_member_type
                      <
                      boost::tti::mf_member_type
                        <
                        boost::mpl::quote1<BOOST_TTI_MEMBER_TYPE_GEN(AnotherIntegerType)>,
                        boost::tti::mf_member_type
                          <
                          boost::mpl::quote1<BOOST_TTI_MEMBER_TYPE_GEN(CType)>,
                          BOOST_TTI_MEMBER_TYPE_GEN(BType)<AType>
                          >
                        >
                      >
                  ));
            
  BOOST_MPL_ASSERT((boost::tti::mf_valid_member_type
                      <
                      boost::tti::mf_member_type
                        <
                        boost::mpl::quote1<SomethingElse>,
                        boost::mpl::identity<AnotherType>
                        >
                      >
                  ));
  
  return 0;

  }

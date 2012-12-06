
//  (C) Copyright Edward Diener 2011,2012
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(BOOST_TTI_HAS_STATIC_MEMBER_DATA_HPP)
#define BOOST_TTI_HAS_STATIC_MEMBER_DATA_HPP

#include <boost/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/tti/gen/has_static_member_data_gen.hpp>
#include <boost/tti/detail/dstatic_mem_data.hpp>

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/// Expands to a metafunction which tests whether a static member data with a particular name and type exists.
/**

    trait = the name of the metafunction within the tti namespace.
    
    name  = the name of the inner member.

    generates a metafunction called "trait" where 'trait' is the macro parameter.
    
              The metafunction types and return:
    
                TTI_T    = the enclosing type.
                
                TTI_Type = the static member data type,
                           in the form of a data type,
                           in which to look for our 'name'.
                       
                returns = 'value' is true if the 'name' exists,
                          with the TTI_Type type,
                          within the enclosing TTI_T type,
                          otherwise 'value' is false.
                          
*/
#define BOOST_TTI_TRAIT_HAS_STATIC_MEMBER_DATA(trait,name) \
  BOOST_TTI_DETAIL_TRAIT_HAS_STATIC_MEMBER_DATA(trait,name) \
  template<class TTI_T,class TTI_Type> \
  struct trait : \
    BOOST_PP_CAT(trait,_detail_hsd)<TTI_T,TTI_Type> \
    { \
    }; \
/**/

/// Expands to a metafunction which tests whether a static member data with a particular name and type exists.
/**

    name  = the name of the inner member.

    generates a metafunction called "has_static_member_name" where 'name' is the macro parameter.
    
              The metafunction types and return:
    
                TTI_T    = the enclosing type.
                
                TTI_Type = the static member data type,
                           in the form of a data type,
                           in which to look for our 'name'.
                       
                returns = 'value' is true if the 'name' exists,
                          with the appropriate TTI_Type type,
                          within the enclosing TTI_T type,
                          otherwise 'value' is false.
                          
*/
#define BOOST_TTI_HAS_STATIC_MEMBER_DATA(name) \
  BOOST_TTI_TRAIT_HAS_STATIC_MEMBER_DATA \
  ( \
  BOOST_TTI_HAS_STATIC_MEMBER_DATA_GEN(name), \
  name \
  ) \
/**/

#endif // BOOST_TTI_HAS_STATIC_MEMBER_DATA_HPP


//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(TTI_STATIC_MEMBER_FUNCTION_HPP)
#define TTI_STATIC_MEMBER_FUNCTION_HPP

#include <boost/config.hpp>
#include <boost/function_types/property_tags.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/preprocessor/cat.hpp>
#include "mf/mf_static_mem_fun.hpp"
#include "gen/static_mem_fun_gen.hpp"
#include "detail/dstatic_mem_fun.hpp"
#include "detail/dtfunction.hpp"

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/// Expands to a metafunction which tests whether a static member function with a particular name and signature exists.
/**

    trait = the name of the metafunction within the tti namespace.
    
    name  = the name of the inner member.

    returns = a metafunction called "boost::tti::trait" where 'trait' is the macro parameter.<br />
    
              The metafunction types and return:
    
                T   = the enclosing type in which to look for our 'name'.
                
                R   = the return type of the static member function.
                
                FS  = an optional parameter which are the parameters of the static member function as a boost::mpl forward sequence.
                
                TAG = an optional parameter which is a boost::function_types tag to apply to the static member function.
                
                returns = 'value' is true if the 'name' exists, with the appropriate type,
                          otherwise 'value' is false.
                          
*/
#define BOOST_TTI_TRAIT_HAS_STATIC_MEMBER_FUNCTION(trait,name) \
  TTI_DETAIL_TRAIT_HAS_STATIC_MEMBER_FUNCTION(trait,name) \
  template<class T,class R,class FS = boost::mpl::vector<>,class TAG = boost::function_types::null_tag> \
  struct trait : \
    BOOST_PP_CAT(trait,_detail)<T,typename BOOST_TTI_NAMESPACE::detail::tfunction_seq<R,FS,TAG>::type> \
    { \
    }; \
/**/

/// Expands to a metafunction which tests whether a static member function with a particular name and signature exists.
/**

    name  = the name of the inner member.

    returns = a metafunction called "boost::tti::has_static_member_function_name" where 'name' is the macro parameter.
    
              The metafunction types and return:
    
                T   = the enclosing type in which to look for our 'name'.
                
                R   = the return type of the static member function.
                
                FS  = an optional parameter which are the parameters of the static member function as a boost::mpl forward sequence.
                
                TAG = an optional parameter which is a boost::function_types tag to apply to the static member function.
                
                returns = 'value' is true if the 'name' exists, with the appropriate type,
                          otherwise 'value' is false.
                          
*/
#define BOOST_TTI_HAS_STATIC_MEMBER_FUNCTION(name) \
  BOOST_TTI_TRAIT_HAS_STATIC_MEMBER_FUNCTION \
  ( \
  BOOST_TTI_HAS_STATIC_MEMBER_FUNCTION_GEN(name), \
  name \
  ) \
/**/

#endif // TTI_STATIC_MEMBER_FUNCTION_HPP


//  (C) Copyright Edward Diener 2011,2012
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(BOOST_TTI_DETAIL_COMP_STATIC_MEM_FUN_HPP)
#define BOOST_TTI_DETAIL_COMP_STATIC_MEM_FUN_HPP

#include <boost/config.hpp>
#include <boost/function_types/is_function.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/type_traits/detail/yes_no_type.hpp>
#include <boost/tti/detail/dnullptr.hpp>

#define BOOST_TTI_DETAIL_TRAIT_HAS_COMP_STATIC_MEMBER_FUNCTION(trait,name) \
  template<class T,class Type> \
  struct BOOST_PP_CAT(trait,_detail) \
    { \
    template<Type *> \
    struct helper; \
    \
    template<class U> \
    static ::boost::type_traits::yes_type check(helper<&U::name> *); \
    \
    template<class U> \
    static ::boost::type_traits::no_type check(...); \
    \
    BOOST_STATIC_CONSTANT(bool,value=(boost::function_types::is_function<Type>::value) && (sizeof(check<T>(BOOST_TTI_DETAIL_NULLPTR))==sizeof(::boost::type_traits::yes_type))); \
    \
    typedef boost::mpl::bool_<value> type; \
    }; \
/**/

#endif // BOOST_TTI_DETAIL_COMP_STATIC_MEM_FUN_HPP


//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(TTI_VM_DETAIL_TEMPLATE_PARAMS_HPP)
#define TTI_VM_DETAIL_TEMPLATE_PARAMS_HPP

#include <boost/config.hpp>
#include <boost/preprocessor/config/config.hpp>

#if BOOST_PP_VARIADICS

#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/variadic/size.hpp>
#include "dtemplate_params.hpp"

#if !defined(BOOST_TTI_VERSION_1_5)

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/detail/is_binary.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/variadic/elem.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include "dtemplate.hpp"

#endif

#if !defined(BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE)
#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1400)

#define TTI_VM_DETAIL_TRAIT_HAS_TEMPLATE_CHECK_PARAMS(trait,name,...) \
  TTI_DETAIL_HAS_MEMBER_WITH_FUNCTION_SFINAE \
    (  \
      ( BOOST_PP_ADD(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__),4), ( trait, name, 1, false, __VA_ARGS__ ) )  \
    )  \
/**/

#else // !!BOOST_WORKAROUND(BOOST_MSVC, <= 1400)

#define TTI_VM_DETAIL_TRAIT_HAS_TEMPLATE_CHECK_PARAMS(trait,name,...) \
  TTI_DETAIL_HAS_MEMBER_WITH_TEMPLATE_SFINAE \
    ( \
      ( BOOST_PP_ADD(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__),4), ( trait, name, 1, false, __VA_ARGS__ ) )  \
    ) \
/**/

#endif // !BOOST_WORKAROUND(BOOST_MSVC, <= 1400)
#else // defined(BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE)

#define TTI_VM_DETAIL_TRAIT_HAS_TEMPLATE_CHECK_PARAMS(trait,name,...) \
  TTI_DETAIL_SAME(trait,name) \
/**/

#endif // !defined(BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE)

#if !defined(BOOST_TTI_VERSION_1_5)

#define TTI_VM_DETAIL_CHECK_MORE_THAN_TWO(trait,...) \
  BOOST_PP_IIF \
    ( \
    BOOST_PP_EQUAL \
      ( \
      BOOST_PP_VARIADIC_SIZE(__VA_ARGS__), \
      2 \
      ), \
    TTI_VM_DETAIL_TRAIT_CHOOSE_FROM_TWO, \
    TTI_VM_DETAIL_TRAIT_EXPAND_ARGUMENTS \
    ) \
    (trait,__VA_ARGS__) \
/**/

#define TTI_VM_DETAIL_TRAIT_CHOOSE_FROM_TWO(trait,...) \
  BOOST_PP_IIF \
    ( \
    BOOST_PP_IS_BINARY \
      ( \
      BOOST_PP_VARIADIC_ELEM(1,__VA_ARGS__) \
      ), \
    TTI_TRAIT_HAS_TEMPLATE_CHECK_PARAMS, \
    TTI_VM_DETAIL_TRAIT_CHOOSE_IF_NIL \
    ) \
  ( \
  trait, \
  BOOST_PP_VARIADIC_ELEM(0,__VA_ARGS__), \
  BOOST_PP_VARIADIC_ELEM(1,__VA_ARGS__) \
  ) \
/**/

#define TTI_VM_DETAIL_IS_NIL(param) \
  BOOST_PP_IS_EMPTY \
    ( \
    BOOST_PP_CAT(TTI_DETAIL_IS_HELPER_,param) \
    ) \
/**/

#define TTI_VM_DETAIL_TRAIT_CHOOSE_IF_NIL(trait,name,param) \
  BOOST_PP_IIF \
    ( \
    TTI_VM_DETAIL_IS_NIL(param), \
    TTI_DETAIL_TRAIT_HAS_TEMPLATE, \
    TTI_VM_DETAIL_CALL_TRAIT_HAS_TEMPLATE_CHECK_PARAMS \
    ) \
  (trait,name,param) \
/**/

#define TTI_VM_DETAIL_VARIADIC_TAIL(...) \
  BOOST_PP_SEQ_ENUM \
    ( \
    BOOST_PP_SEQ_TAIL \
      ( \
      BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__) \
      ) \
    ) \
/**/

#define TTI_VM_DETAIL_TRAIT_EXPAND_ARGUMENTS(trait,...) \
  TTI_VM_DETAIL_CALL_TRAIT_HAS_TEMPLATE_CHECK_PARAMS \
    ( \
    trait, \
    BOOST_PP_VARIADIC_ELEM(0,__VA_ARGS__), \
    TTI_VM_DETAIL_VARIADIC_TAIL(__VA_ARGS__) \
    ) \
/**/

#define TTI_VM_DETAIL_TRAIT_HAS_TEMPLATE(trait,...) \
  TTI_DETAIL_TRAIT_HAS_TEMPLATE \
    ( \
    trait, \
    BOOST_PP_VARIADIC_ELEM(0,__VA_ARGS__), \
    BOOST_PP_NIL \
    ) \
/**/

#define TTI_VM_DETAIL_CALL_TRAIT_HAS_TEMPLATE_CHECK_PARAMS(trait,name,...) \
  TTI_VM_DETAIL_TRAIT_HAS_TEMPLATE_CHECK_PARAMS(BOOST_PP_CAT(trait,_detail),name,__VA_ARGS__) \
  template<class TTI_T> \
  struct trait \
    { \
    typedef typename BOOST_PP_CAT(trait,_detail)<TTI_T>::type type; \
    \
    BOOST_STATIC_CONSTANT(bool,value=type::value); \
    }; \
/**/

#endif // !BOOST_TTI_VERSION_1_5

#endif // BOOST_PP_VARIADICS

#endif // TTI_VM_DETAIL_TEMPLATE_PARAMS_HPP

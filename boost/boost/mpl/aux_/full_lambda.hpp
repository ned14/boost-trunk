
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_AUX_FULL_LAMBDA_HPP_INCLUDED
#define BOOST_MPL_AUX_FULL_LAMBDA_HPP_INCLUDED

// Copyright (c) Aleksey Gurtovoy 2001-2004
//
// Use, modification and distribution are subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy 
// at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/lambda_fwd.hpp>
#   include <boost/mpl/bind.hpp>
#   include <boost/mpl/protect.hpp>
#   include <boost/mpl/quote.hpp>
#   include <boost/mpl/bool.hpp>
#   include <boost/mpl/int_fwd.hpp>
#   include <boost/mpl/aux_/template_arity.hpp>
#   include <boost/mpl/aux_/config/ttp.hpp>
#   if defined(BOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING)
#       include <boost/mpl/if.hpp>
#   endif
#endif

#include <boost/mpl/aux_/lambda_expr.hpp>
#include <boost/mpl/aux_/lambda_arity_param.hpp>
#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER full_lambda.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/arity.hpp>
#   include <boost/mpl/aux_/na_spec.hpp>
#   include <boost/mpl/aux_/preprocessor/default_params.hpp>
#   include <boost/mpl/aux_/preprocessor/params.hpp>
#   include <boost/mpl/aux_/preprocessor/enum.hpp>
#   include <boost/mpl/aux_/preprocessor/repeat.hpp>

#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/comma_if.hpp>
#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>

namespace boost { namespace mpl {

// local macros, #undef-ined at the end of the header
#   define AUX778076_LAMBDA_PARAMS(i_, param) \
    BOOST_MPL_PP_PARAMS(i_, param) \
    /**/

#   define AUX778076_LAMBDA_BIND_PARAMS(param) \
    BOOST_MPL_PP_PARAMS( \
          BOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        , param \
        ) \
    /**/

#   define AUX778076_LAMBDA_BIND_N_PARAMS(i_, param) \
    BOOST_PP_COMMA_IF(i_) \
    BOOST_MPL_PP_PARAMS(i_, param) \
    /**/

#   define AUX778076_ARITY_PARAM(param) \
    BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(param) \
    /**/

template<
      typename T
    , typename Tag
    AUX778076_ARITY_PARAM(typename Arity)
    >
struct lambda
{
    BOOST_MPL_AUX_IS_LAMBDA_EXPR(false_)
    typedef T result_;
    typedef T type;
};

#if !defined(BOOST_MPL_CFG_NO_LAMBDA_HEURISTIC)

#define n_ BOOST_MPL_LIMIT_METAFUNCTION_ARITY
namespace aux {

template<
      BOOST_MPL_PP_DEFAULT_PARAMS(n_,bool C,false)
    >
struct lambda_or
    : true_
{
};

template<>
struct lambda_or< BOOST_MPL_PP_ENUM(n_,false) >
    : false_
{
};

} // namespace aux
#undef n_

template< int N, typename Tag >
struct lambda< arg<N>,Tag AUX778076_ARITY_PARAM(int_<-1>) >
{
    BOOST_MPL_AUX_IS_LAMBDA_EXPR(true_)
    typedef mpl::arg<N> result_; // qualified for the sake of MIPSpro 7.41
    typedef protect<result_> type; 
};

#endif // BOOST_MPL_CFG_NO_LAMBDA_HEURISTIC

#define BOOST_PP_ITERATION_LIMITS (0, BOOST_MPL_LIMIT_METAFUNCTION_ARITY)
#define BOOST_PP_FILENAME_1 <boost/mpl/aux_/full_lambda.hpp>
#include BOOST_PP_ITERATE()

//: special case for 'protect'
template< typename T, typename Tag >
struct lambda< protect<T>,Tag AUX778076_ARITY_PARAM(int_<1>) >
{
    BOOST_MPL_AUX_IS_LAMBDA_EXPR(false_)
    typedef protect<T> result_;
    typedef result_ type;
};

//: specializations for the main 'bind' form
template<
      typename F, AUX778076_LAMBDA_BIND_PARAMS(typename T)
    , typename Tag
    >
struct lambda<
          bind<F,AUX778076_LAMBDA_BIND_PARAMS(T)>
        , Tag
        AUX778076_ARITY_PARAM(int_<BOOST_PP_INC(BOOST_MPL_LIMIT_METAFUNCTION_ARITY)>)
        >
{
    BOOST_MPL_AUX_IS_LAMBDA_EXPR(false_)
    typedef bind<F, AUX778076_LAMBDA_BIND_PARAMS(T)> result_;
    typedef result_ type;
};


#if defined(BOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING) \
    && !defined(BOOST_MPL_CFG_NO_LAMBDA_HEURISTIC)

template<
      typename F
    , typename Tag1
    , typename Tag2
    , typename Arity
    >
struct lambda<
          lambda<F,Tag1,Arity>
        , Tag2
        , int_<3>
        >
{
    typedef lambda< F,Tag2 > l1;
    typedef lambda< Tag1,Tag2 > l2;

    typedef typename l1::is_le is_le;
    typedef bind1< quote1<aux::template_arity>, typename l1::result_ > arity_;
    typedef lambda< typename if_<is_le,arity_,Arity>::type,Tag2 > l3;
    
    typedef aux::le_result3<is_le, Tag2, mpl::lambda, l1, l2, l3> le_result_;
    typedef typename le_result_::result_ result_;
    typedef typename le_result_::type type;
};

#elif 1 // BOOST_WORKAROUND(__MWERKS__,BOOST_TESTED_AT(0x3003)) 
//    || BOOST_WORKAROUND(__EDG_VERSION__,< 303) 

template<
      typename F, typename Tag1, typename Tag2
    >
struct lambda<
          lambda< F,Tag1 >
        , Tag2
        >
{
    typedef lambda< F,Tag2 > l1;
    typedef lambda< Tag1,Tag2 > l2;
    
    typedef typename l1::is_le is_le;
    typedef aux::le_result2<is_le, Tag2, mpl::lambda, l1, l2> le_result_;
    typedef typename le_result_::result_ result_;
    typedef typename le_result_::type type;
};

#endif

#   undef AUX778076_ARITY_PARAM
#   undef AUX778076_LAMBDA_BIND_N_PARAMS
#   undef AUX778076_LAMBDA_BIND_PARAMS
#   undef AUX778076_LAMBDA_PARAMS

#if !defined(BOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING)
//BOOST_MPL_AUX_NA_SPEC(2, lambda)
#else
//BOOST_MPL_AUX_NA_SPEC2(2, 3, lambda)
#endif

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_AUX_FULL_LAMBDA_HPP_INCLUDED

///// iteration, depth == 1

#elif BOOST_PP_ITERATION_DEPTH() == 1
#define i_ BOOST_PP_FRAME_ITERATION(1)

#if i_ > 0

#if defined(BOOST_MPL_CFG_NO_LAMBDA_HEURISTIC)

#   define AUX778076_LAMBDA_INVOCATION(unused, i_, T) \
    BOOST_PP_COMMA_IF(i_) \
    typename lambda< BOOST_PP_CAT(T, BOOST_PP_INC(i_)),Tag >::type \
    /**/

template<
      template< AUX778076_LAMBDA_PARAMS(i_, typename P) > class F
    , AUX778076_LAMBDA_PARAMS(i_, typename T)
    , typename Tag
    >
struct lambda< 
          F<AUX778076_LAMBDA_PARAMS(i_, T)>, Tag AUX778076_ARITY_PARAM(int_<i_>)
        >
{
    typedef BOOST_PP_CAT(bind,i_)<
          BOOST_PP_CAT(quote,i_)<F,Tag>
        , BOOST_MPL_PP_REPEAT(i_, AUX778076_LAMBDA_INVOCATION, T)
        > result_;

    typedef protect<result_> type;

#   undef AUX778076_LAMBDA_INVOCATION
};

#else // BOOST_MPL_CFG_NO_LAMBDA_HEURISTIC

#   define AUX778076_RESULT(unused, i_, T) \
    BOOST_PP_COMMA_IF(i_) \
    typename BOOST_PP_CAT(T, BOOST_PP_INC(i_))::result_ \
    /**/

#   define AUX778076_TYPE(unused, i_, T) \
    BOOST_PP_COMMA_IF(i_) \
    typename BOOST_PP_CAT(T, BOOST_PP_INC(i_))::type \
    /**/

namespace aux {

template<
      typename IsLE, typename Tag
    , template< AUX778076_LAMBDA_PARAMS(i_, typename P) > class F
    , AUX778076_LAMBDA_PARAMS(i_, typename L)
    >
struct BOOST_PP_CAT(le_result,i_)
{
    typedef F<
          BOOST_MPL_PP_REPEAT(i_, AUX778076_TYPE, L)
        > result_;
    
    typedef result_ type;
};

template<
      typename Tag
    , template< AUX778076_LAMBDA_PARAMS(i_, typename P) > class F
    , AUX778076_LAMBDA_PARAMS(i_, typename L)
    >
struct BOOST_PP_CAT(le_result,i_)< true_,Tag,F,AUX778076_LAMBDA_PARAMS(i_, L) >
{
    typedef BOOST_PP_CAT(bind,i_)<
          BOOST_PP_CAT(quote,i_)<F,Tag>
        , BOOST_MPL_PP_REPEAT(i_, AUX778076_RESULT, L)
        > result_;

    typedef protect<result_> type;
};

#   undef AUX778076_TYPE
#   undef AUX778076_RESULT

} // namespace aux


#   define AUX778076_LAMBDA_INVOCATION(unused, i_, T) \
    typedef lambda< BOOST_PP_CAT(T, BOOST_PP_INC(i_)), Tag > \
        BOOST_PP_CAT(l,BOOST_PP_INC(i_)); \
    /**/

#   define AUX778076_IS_LAMBDA_EXPR(unused, i_, unused2) \
    BOOST_PP_COMMA_IF(i_) \
    BOOST_PP_CAT(l,BOOST_PP_INC(i_))::is_le::value \
    /**/

template<
      template< AUX778076_LAMBDA_PARAMS(i_, typename P) > class F
    , AUX778076_LAMBDA_PARAMS(i_, typename T)
    , typename Tag
    >
struct lambda< 
          F<AUX778076_LAMBDA_PARAMS(i_, T)>
        , Tag
        AUX778076_ARITY_PARAM(int_<i_>)
        >
{
    BOOST_MPL_PP_REPEAT(i_, AUX778076_LAMBDA_INVOCATION, T)
    typedef typename aux::lambda_or<
          BOOST_MPL_PP_REPEAT(i_, AUX778076_IS_LAMBDA_EXPR, unused)
        >::type is_le;

    typedef aux::BOOST_PP_CAT(le_result,i_)<
          is_le, Tag, F, AUX778076_LAMBDA_PARAMS(i_, l)
        > le_result_;
    
    typedef typename le_result_::result_ result_;
    typedef typename le_result_::type type;
};


#   undef AUX778076_IS_LAMBDA_EXPR
#   undef AUX778076_LAMBDA_INVOCATION

#endif // BOOST_MPL_CFG_NO_LAMBDA_HEURISTIC
#endif // i_ > 0

template<
      typename F AUX778076_LAMBDA_BIND_N_PARAMS(i_, typename T)
    , typename Tag
    >
struct lambda<
          BOOST_PP_CAT(bind,i_)<F AUX778076_LAMBDA_BIND_N_PARAMS(i_, T)>
        , Tag
        AUX778076_ARITY_PARAM(int_<BOOST_PP_INC(i_)>)
        >
{
    BOOST_MPL_AUX_IS_LAMBDA_EXPR(false_)
    typedef BOOST_PP_CAT(bind,i_)<
          F
        AUX778076_LAMBDA_BIND_N_PARAMS(i_, T)
        > result_;
        
    typedef result_ type;
};

#undef i_
#endif // BOOST_PP_IS_ITERATING

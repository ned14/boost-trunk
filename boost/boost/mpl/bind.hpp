
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_BIND_HPP_INCLUDED
#define BOOST_MPL_BIND_HPP_INCLUDED

// Copyright (c) Peter Dimov 2001
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

#include <boost/mpl/aux_/config/bind.hpp>
#include <boost/mpl/aux_/config/lambda.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/apply.hpp>
#   include <boost/mpl/placeholders.hpp>
#   include <boost/mpl/protect.hpp>
#   include <boost/mpl/limits/arity.hpp>
#   include <boost/mpl/aux_/na.hpp>
#   include <boost/mpl/aux_/arity_spec.hpp>
#   include <boost/mpl/aux_/type_wrapper.hpp>
#   include <boost/mpl/aux_/yes_no.hpp>
#   include <boost/mpl/aux_/common_name_wknd.hpp>
#   if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#       include <boost/type_traits/is_reference.hpp>
#   endif 
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   if defined(BOOST_MPL_CFG_NO_UNNAMED_PLACEHOLDER_SUPPORT)
#       define BOOST_MPL_PREPROCESSED_HEADER basic_bind.hpp
#   else
#       define BOOST_MPL_PREPROCESSED_HEADER bind.hpp
#   endif
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/aux_/preprocessor/params.hpp>
#   include <boost/mpl/aux_/preprocessor/default_params.hpp>
#   include <boost/mpl/aux_/preprocessor/def_params_tail.hpp>
#   include <boost/mpl/aux_/preprocessor/partial_spec_params.hpp>
#   include <boost/mpl/aux_/preprocessor/enum.hpp>
#   include <boost/mpl/aux_/preprocessor/add.hpp>
#   include <boost/mpl/aux_/config/dtp.hpp>
#   include <boost/mpl/aux_/config/nttp.hpp>

#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/comma_if.hpp>
#   include <boost/preprocessor/cat.hpp>
#   include <boost/preprocessor/inc.hpp>

namespace boost { namespace mpl {

BOOST_MPL_AUX_COMMON_NAME_WKND(bind1st)
BOOST_MPL_AUX_COMMON_NAME_WKND(bind2nd)

// local macros, #undef-ined at the end of the header
#   define AUX778076_APPLY \
    BOOST_PP_CAT(apply,BOOST_MPL_LIMIT_METAFUNCTION_ARITY) \
    /**/

#   define AUX778076_BIND_PARAMS(param) \
    BOOST_MPL_PP_PARAMS( \
          BOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        , param \
        ) \
    /**/

#   define AUX778076_BIND_DEFAULT_PARAMS(param, value) \
    BOOST_MPL_PP_DEFAULT_PARAMS( \
          BOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        , param \
        , value \
        ) \
    /**/

#   define AUX778076_BIND_N_PARAMS(n, param) \
    BOOST_PP_COMMA_IF(n) \
    BOOST_MPL_PP_PARAMS(n, param) \
    /**/

#   define AUX778076_BIND_N_SPEC_PARAMS(n, param, def) \
    BOOST_PP_COMMA_IF(n) \
    BOOST_MPL_PP_PARTIAL_SPEC_PARAMS(n, param, def) \
    /**/

#if !defined(BOOST_MPL_CFG_NO_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
#   define AUX778076_BIND_NESTED_DEFAULT_PARAMS(param, value) \
    AUX778076_BIND_DEFAULT_PARAMS(param, value) \
    /**/
#else
#   define AUX778076_BIND_NESTED_DEFAULT_PARAMS(param, value) \
    AUX778076_BIND_PARAMS(param) \
    /**/
#endif

namespace aux {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<
      typename T, AUX778076_BIND_PARAMS(typename U)
    >
struct resolve_bind_arg
{
    typedef T type;
};

#   if !defined(BOOST_MPL_CFG_NO_UNNAMED_PLACEHOLDER_SUPPORT)

template<
      typename T
    , typename Arg
    >
struct replace_unnamed_arg
{
    typedef Arg next_arg;
    typedef T type;
};

template<
      typename Arg
    >
struct replace_unnamed_arg< arg<-1>,Arg >
{
    typedef typename Arg::next next_arg;
    typedef Arg type;
};

#   endif // BOOST_MPL_CFG_NO_UNNAMED_PLACEHOLDER_SUPPORT

#else

// agurt, 15/jan/02: it's not a intended to be used as a function class, and 
// MSVC6.5 has problems with 'apply' name here (the code compiles, but doesn't
// work), so I went with the 'result_' here, and in all other similar cases
template< bool >
struct resolve_arg_impl
{
    template< typename T, AUX778076_BIND_PARAMS(typename U) > struct result_
    {
        typedef T type;
    };
};

template<> 
struct resolve_arg_impl<true>
{
    template< typename T, AUX778076_BIND_PARAMS(typename U) > struct result_
    {
        typedef typename AUX778076_APPLY<
              T
            , AUX778076_BIND_PARAMS(U)
            >::type type;
    };
};

// for 'resolve_bind_arg'
template< typename T > struct is_bind_template;

template< 
      typename T, AUX778076_BIND_PARAMS(typename U)
    >
struct resolve_bind_arg
    : resolve_arg_impl< is_bind_template<T>::value >
            ::template result_< T,AUX778076_BIND_PARAMS(U) >
{
};

#   if !defined(BOOST_MPL_CFG_NO_UNNAMED_PLACEHOLDER_SUPPORT)

template< typename T > 
struct replace_unnamed_arg_impl
{
    template< typename Arg > struct result_
    {
        typedef Arg next_arg;
        typedef T type;
    };
};

template<> 
struct replace_unnamed_arg_impl< arg<-1> >
{
    template< typename Arg > struct result_
    {
        typedef typename Arg::next next_arg;
        typedef Arg type;
    };
};

template< typename T, typename Arg > 
struct replace_unnamed_arg
    : replace_unnamed_arg_impl<T>::template result_<Arg>
{
};

#   endif // BOOST_MPL_CFG_NO_UNNAMED_PLACEHOLDER_SUPPORT

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

} // namespace aux

#if !defined(BOOST_MPL_CFG_NO_BIND_TEMPLATE)
// forward declaration
template<
      typename F, AUX778076_BIND_DEFAULT_PARAMS(typename T, na)
    >
struct bind;
#endif

// fwd, for 'resolve_bind_arg'/'is_bind_template' specializations
template< typename F, typename T > struct bind1st;
template< typename F, typename T > struct bind2nd;

namespace aux {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
template<
      BOOST_MPL_AUX_NTTP_DECL(int, N), AUX778076_BIND_PARAMS(typename U)
    >
struct resolve_bind_arg< arg<N>,AUX778076_BIND_PARAMS(U) >
{
    typedef typename AUX778076_APPLY<mpl::arg<N>, AUX778076_BIND_PARAMS(U)>::type type;
};

#if !defined(BOOST_MPL_CFG_NO_BIND_TEMPLATE)
template<
      typename F, AUX778076_BIND_PARAMS(typename T), AUX778076_BIND_PARAMS(typename U)
    >
struct resolve_bind_arg< bind<F,AUX778076_BIND_PARAMS(T)>,AUX778076_BIND_PARAMS(U) >
{
    typedef bind<F,AUX778076_BIND_PARAMS(T)> f_;
    typedef typename AUX778076_APPLY<f_, AUX778076_BIND_PARAMS(U)>::type type;
};
#endif

template<
      typename F, typename T, AUX778076_BIND_PARAMS(typename U)
    >
struct resolve_bind_arg< bind1st<F,T>, AUX778076_BIND_PARAMS(U) >
{
    typedef bind1st<F,T> f_;
    typedef typename AUX778076_APPLY<f_, AUX778076_BIND_PARAMS(U)>::type type;
};

template<
      typename F, typename T, AUX778076_BIND_PARAMS(typename U)
    >
struct resolve_bind_arg< bind2nd<F,T>, AUX778076_BIND_PARAMS(U) >
{
    typedef bind2nd<F,T> f_;
    typedef typename AUX778076_APPLY<f_, AUX778076_BIND_PARAMS(U)>::type type;
};

#else
// agurt, 10/mar/02: the forward declaration has to appear before any of
// 'is_bind_helper' overloads, otherwise MSVC6.5 issues an ICE on it
template< BOOST_MPL_AUX_NTTP_DECL(int, arity_) > struct bind_chooser;

aux::no_tag is_bind_helper(...);
template< typename T > aux::no_tag is_bind_helper(protect<T>*);

// overload for "main" form
// agurt, 15/mar/02: MSVC 6.5 fails to properly resolve the overload 
// in case if we use 'aux::type_wrapper< bind<...> >' here, and all 
// 'bind' instantiations form a complete type anyway
#if !defined(BOOST_MPL_CFG_NO_BIND_TEMPLATE)
template<
      typename F, AUX778076_BIND_PARAMS(typename T)
    >
aux::yes_tag is_bind_helper(bind<F,AUX778076_BIND_PARAMS(T)>*);
#endif

template< BOOST_MPL_AUX_NTTP_DECL(int, N) >
aux::yes_tag is_bind_helper(arg<N>*);

template< typename F, typename T > aux::yes_tag is_bind_helper(bind1st<F,T>*);
template< typename F, typename T > aux::yes_tag is_bind_helper(bind2nd<F,T>*);

template< bool is_ref_ = true >
struct is_bind_template_impl
{
    template< typename T > struct result_
    {
        BOOST_STATIC_CONSTANT(bool, value = false);
    };
};

template<>
struct is_bind_template_impl<false>
{
    template< typename T > struct result_
    {
        BOOST_STATIC_CONSTANT(bool, value = 
              sizeof(aux::is_bind_helper(static_cast<T*>(0))) 
                == sizeof(aux::yes_tag)
            );
    };
};

template< typename T > struct is_bind_template
    : is_bind_template_impl< ::boost::detail::is_reference_impl<T>::value >
        ::template result_<T>
{
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

} // namespace aux

#if !defined(BOOST_MPL_CFG_NO_BIND_TEMPLATE)
BOOST_MPL_AUX_ARITY_SPEC(
      BOOST_PP_INC(BOOST_MPL_LIMIT_METAFUNCTION_ARITY)
    , bind
    )
#endif

BOOST_MPL_AUX_ARITY_SPEC(2,bind1st)
BOOST_MPL_AUX_ARITY_SPEC(2,bind2nd)

#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, <boost/mpl/bind.hpp>))
#include BOOST_PP_ITERATE()

// real C++ version is already taken care of
#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
 && !defined(BOOST_MPL_CFG_NO_BIND_TEMPLATE)

namespace aux {
// apply_count_args
#define AUX778076_COUNT_ARGS_PREFIX bind
#define AUX778076_COUNT_ARGS_DEFAULT na
#define AUX778076_COUNT_ARGS_ARITY BOOST_MPL_LIMIT_METAFUNCTION_ARITY
#include <boost/mpl/aux_/count_args.hpp>
}

// bind
template<
      typename F, AUX778076_BIND_PARAMS(typename T)
    >
struct bind
    : aux::bind_chooser<
          aux::bind_count_args<AUX778076_BIND_PARAMS(T)>::value
        >::template result_< F,AUX778076_BIND_PARAMS(T) >::type
{
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

// bind1st/bind2nd, lightweight, for simple cases/backward compatibility

template< typename F, typename T >
struct bind1st
{
    template<
          typename U
        , BOOST_MPL_PP_NESTED_DEF_PARAMS_TAIL(1, typename U, na)
        >
    struct apply
        : apply2<F,T,U>
    {
    };
};

template< typename F, typename T >
struct bind2nd
{
    template<
          typename U
        , BOOST_MPL_PP_NESTED_DEF_PARAMS_TAIL(1, typename U, na)
        >
    struct apply
        : apply2<F,T,U>
    {
    };
};

#   undef AUX778076_BIND_NESTED_DEFAULT_PARAMS
#   undef AUX778076_BIND_N_SPEC_PARAMS
#   undef AUX778076_BIND_N_PARAMS
#   undef AUX778076_BIND_DEFAULT_PARAMS
#   undef AUX778076_BIND_PARAMS
#   undef AUX778076_APPLY

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_BIND_HPP_INCLUDED

///// iteration, depth == 1

#elif BOOST_PP_ITERATION_DEPTH() == 1

#   define i_ BOOST_PP_FRAME_ITERATION(1)

template<
      typename F AUX778076_BIND_N_PARAMS(i_, typename T)
    >
struct BOOST_PP_CAT(bind,i_)
{
    template<
          AUX778076_BIND_NESTED_DEFAULT_PARAMS(typename U, na)
        >
    struct apply
    {
     private:
#   if !defined(BOOST_MPL_CFG_NO_UNNAMED_PLACEHOLDER_SUPPORT)

        typedef aux::replace_unnamed_arg< F,mpl::arg<1> > r0;
        typedef typename r0::type a0;
        typedef typename r0::next_arg n1;
        typedef typename aux::resolve_bind_arg<a0,AUX778076_BIND_PARAMS(U)>::type f_;
        //:
#   else
        typedef typename aux::resolve_bind_arg<F,AUX778076_BIND_PARAMS(U)>::type f_;

#   endif // BOOST_MPL_CFG_NO_UNNAMED_PLACEHOLDER_SUPPORT

#   if i_ > 0
#       define BOOST_PP_ITERATION_PARAMS_2 (3,(1, i_, <boost/mpl/bind.hpp>))
#       include BOOST_PP_ITERATE()
#   endif

     public:
        typedef typename BOOST_PP_CAT(apply,i_)<
              f_ 
            AUX778076_BIND_N_PARAMS(i_,t)
            >::type type;
    };
};


namespace aux {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<
      typename F AUX778076_BIND_N_PARAMS(i_, typename T), AUX778076_BIND_PARAMS(typename U)
    >
struct resolve_bind_arg<
      BOOST_PP_CAT(bind,i_)<F AUX778076_BIND_N_PARAMS(i_,T)>,AUX778076_BIND_PARAMS(U)
    >
{
    typedef BOOST_PP_CAT(bind,i_)<F AUX778076_BIND_N_PARAMS(i_,T)> f_;
    typedef typename AUX778076_APPLY<f_, AUX778076_BIND_PARAMS(U)>::type type;
};

#else

template<
      typename F AUX778076_BIND_N_PARAMS(i_, typename T)
    >
aux::yes_tag
is_bind_helper(BOOST_PP_CAT(bind,i_)<F AUX778076_BIND_N_PARAMS(i_,T)>*);

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(BOOST_PP_INC(i_), BOOST_PP_CAT(bind,i_))


#   if !defined(BOOST_MPL_CFG_NO_BIND_TEMPLATE)
#   if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    
#if i_ == BOOST_MPL_LIMIT_METAFUNCTION_ARITY

//: primary template (not a specialization!)
template<
      typename F AUX778076_BIND_N_PARAMS(i_, typename T)
    >
struct bind
    : BOOST_PP_CAT(bind,i_)<F AUX778076_BIND_N_PARAMS(i_,T) >
{
};

#else

template<
      typename F AUX778076_BIND_N_PARAMS(i_, typename T)
    >
struct bind< F AUX778076_BIND_N_SPEC_PARAMS(i_, T, na) >
    : BOOST_PP_CAT(bind,i_)<F AUX778076_BIND_N_PARAMS(i_,T) >
{
};

#endif // i_ == BOOST_MPL_LIMIT_METAFUNCTION_ARITY

#   else

namespace aux {

template<>
struct bind_chooser<i_>
{
    template<
          typename F, AUX778076_BIND_PARAMS(typename T)
        >
    struct result_
    {
        typedef BOOST_PP_CAT(bind,i_)< F AUX778076_BIND_N_PARAMS(i_,T) > type;
    };
};

} // namespace aux

#   endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#   endif // BOOST_MPL_CFG_NO_BIND_TEMPLATE

#   undef i_

///// iteration, depth == 2

#elif BOOST_PP_ITERATION_DEPTH() == 2

#   define j_ BOOST_PP_FRAME_ITERATION(2)
#   if !defined(BOOST_MPL_CFG_NO_UNNAMED_PLACEHOLDER_SUPPORT)

        typedef aux::replace_unnamed_arg< BOOST_PP_CAT(T,j_),BOOST_PP_CAT(n,j_) > BOOST_PP_CAT(r,j_);
        typedef typename BOOST_PP_CAT(r,j_)::type BOOST_PP_CAT(a,j_);
        typedef typename BOOST_PP_CAT(r,j_)::next_arg BOOST_PP_CAT(n,BOOST_PP_INC(j_));
        typedef typename aux::resolve_bind_arg<BOOST_PP_CAT(a,j_), AUX778076_BIND_PARAMS(U)>::type BOOST_PP_CAT(t,j_);
        //:
#   else
        typedef typename aux::resolve_bind_arg< BOOST_PP_CAT(T,j_),AUX778076_BIND_PARAMS(U)>::type BOOST_PP_CAT(t,j_);

#   endif
#   undef j_

#endif // BOOST_PP_IS_ITERATING

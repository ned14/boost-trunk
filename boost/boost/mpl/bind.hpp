//-----------------------------------------------------------------------------
// boost mpl/bind.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Peter Dimov, Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MPL_BIND_HPP_INCLUDED
#define BOOST_MPL_BIND_HPP_INCLUDED

#include "boost/mpl/aux_/config/use_preprocessed.hpp"

#if defined(BOOST_MPL_USE_PREPROCESSED_HEADERS)
#   include "boost/mpl/aux_/preprocessed/bind.hpp"
#else

#include "boost/mpl/apply.hpp"
#include "boost/mpl/placeholder.hpp"
#include "boost/mpl/limits/arity.hpp"
#include "boost/mpl/aux_/arity.hpp"
#include "boost/mpl/aux_/count_if_not.hpp"
#include "boost/mpl/aux_/preprocessor/params.hpp"
#include "boost/mpl/aux_/preprocessor/default_params.hpp"
#include "boost/mpl/aux_/preprocessor/def_params_tail.hpp"
#include "boost/mpl/aux_/type_wrapper.hpp"
#include "boost/mpl/aux_/yes_no.hpp"
#include "boost/mpl/aux_/none.hpp"
#include "boost/mpl/aux_/config/dtp.hpp"

#include "boost/preprocessor/repeat_2nd.hpp"
#include "boost/preprocessor/repeat_3rd.hpp"
#include "boost/preprocessor/comma_if.hpp"
#include "boost/preprocessor/if.hpp"
#include "boost/preprocessor/inc.hpp"
#include "boost/preprocessor/cat.hpp"
#include "boost/config.hpp"

namespace boost {
namespace mpl {

// local macros, #undef-ined at the end of the header
#define AUX_APPLY \
    BOOST_PP_CAT( \
          apply \
        , BOOST_MPL_METAFUNCTION_MAX_ARITY \
        ) \
/**/

#define AUX_BIND_PARAMS(param) \
    BOOST_MPL_PP_PARAMS( \
          1 \
        , BOOST_PP_INC(BOOST_MPL_METAFUNCTION_MAX_ARITY) \
        , param \
        ) \
/**/

#define AUX_BIND_DEFAULT_PARAMS(param, value) \
    BOOST_MPL_PP_DEFAULT_PARAMS( \
          1 \
        , BOOST_PP_INC(BOOST_MPL_METAFUNCTION_MAX_ARITY) \
        , param \
        , value \
        ) \
/**/

#define AUX_BIND_N_PARAMS(i, param) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_MPL_PP_PARAMS(1, BOOST_PP_INC(i), param) \
/**/

namespace aux {

// agurt, 15/jan/02: it's not a intended to be used as a function class, and 
// MSVC6.5 has problems with 'apply' name here (the code compiles, but doesn't
// work), so i went with the 'result_' here, and in all other similar cases
template< bool >
struct resolve_argument_impl
{
    template< typename T, AUX_BIND_PARAMS(typename U) > struct result_
    {
        typedef T type;
    };
};

template<> 
struct resolve_argument_impl<true>
{
    template< typename T, AUX_BIND_PARAMS(typename U) > struct result_
    {
        typedef typename AUX_APPLY<
              T
            , AUX_BIND_PARAMS(U)
            >::type type;
    };
};

// for 'resolve_bind_argument'
template< typename T > struct is_bind_template;

template< typename T >
struct resolve_bind_argument
{
    template< AUX_BIND_PARAMS(typename U) > struct result_
    {
        typedef typename resolve_argument_impl< is_bind_template<T>::value >
            ::template result_< T, AUX_BIND_PARAMS(U) >::type type;
    };
};

} // namespace aux

#define AUX_RESOLVE_BIND_ARGUMENT_0_SPEC(unused)
#define AUX_RESOLVE_BIND_ARGUMENT_N_SPEC(i) \
namespace aux { \
template<> \
struct resolve_bind_argument< arg<i> > \
{ \
    template< AUX_BIND_PARAMS(typename U) > struct result_ \
    { \
        typedef U##i type; \
        typedef char arity_constraint[sizeof(aux::reject_if_none<type>)]; \
    }; \
}; \
} \
/**/

#define AUX_RESOLVE_BIND_ARGUMENT_SPEC(i) \
    BOOST_PP_IF( \
          i \
        , AUX_RESOLVE_BIND_ARGUMENT_N_SPEC \
        , AUX_RESOLVE_BIND_ARGUMENT_0_SPEC \
        )(i) \
/**/

#define AUX_RESOLVE_ARGUMENT_INVOCATION(i, unused) \
typedef typename aux::resolve_bind_argument< \
      BOOST_PP_CAT(T, BOOST_PP_INC(i)) \
    >::template result_< AUX_BIND_PARAMS(U) >::type \
        BOOST_PP_CAT(t, BOOST_PP_INC(i)); \
/**/

#define AUX_BIND_N_TEMPLATE_DEF(i) \
template< typename F AUX_BIND_N_PARAMS(i, typename T) > \
struct bind##i \
{ \
    template< AUX_BIND_PARAMS(typename U) > struct apply_ \
    { \
        typedef typename aux::resolve_bind_argument<F> \
            ::template result_< AUX_BIND_PARAMS(U) >::type f_;\
        BOOST_PP_REPEAT_3RD( \
              i \
            , AUX_RESOLVE_ARGUMENT_INVOCATION \
            , unused \
            ) \
        \
        typedef apply##i< \
              f_ \
              AUX_BIND_N_PARAMS(i, t) \
            > type; \
    }; \
 \
    template< AUX_BIND_DEFAULT_PARAMS(typename U, aux::none) > \
    struct apply : apply_< AUX_BIND_PARAMS(U) >::type \
    { \
    }; \
}; \
/**/

// for 'is_bind_template' specializations
template< typename F, AUX_BIND_PARAMS(typename T) > struct bind;
template< typename F, typename T > struct bind1st;
template< typename F, typename T > struct bind2nd;

namespace aux {

// to be able to define specializations
// agurt, 10/mar/02: the forward declaration has to appear before any of
// 'is_bind_helper' overloads, otherwise MSVC6.5 issues an ICE on it
template< int > struct bind_impl_chooser;

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< typename T >
struct is_bind_template
{
    BOOST_STATIC_CONSTANT(bool, value = false);
};

// specialization for "main" forms
template< typename F, AUX_BIND_PARAMS(typename T) >
struct is_bind_template< bind<F,AUX_BIND_PARAMS(T)> >
{
    BOOST_STATIC_CONSTANT(bool, value = true);
};

template< typename F, typename T >
struct is_bind_template< bind1st<F,T> >
{
    BOOST_STATIC_CONSTANT(bool, value = true);
};

template< typename F, typename T >
struct is_bind_template< bind2nd<F,T> >
{
    BOOST_STATIC_CONSTANT(bool, value = true);
};

// macro to generate specializations for numbered forms
#   define AUX_IS_NESTED_BIND_DEF(i) \
namespace aux { \
template< typename F AUX_BIND_N_PARAMS(i, typename T) > \
struct is_bind_template< \
      bind##i<F AUX_BIND_N_PARAMS(i, T)> \
    > \
{ \
    BOOST_STATIC_CONSTANT(bool, value = true); \
}; \
} \
/**/

#else // #if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

aux::no_tag is_bind_helper(...);

// overload for "main" form
// agurt, 15/mar/02: MSVC 6.5 fails to properly resolve the overload 
// in case if we use 'aux::type_wrapper< bind<...> >' here, and all 
// 'bind' instantiations form a complete type anyway
template< typename F, AUX_BIND_PARAMS(typename T) >
aux::yes_tag is_bind_helper(bind<F, AUX_BIND_PARAMS(T)>*);

template< typename F, typename T >
aux::yes_tag is_bind_helper(bind1st<F,T>*);

template< typename F, typename T >
aux::yes_tag is_bind_helper(bind2nd<F,T>*);

// macro to generate overloads for numbered forms
#   define AUX_IS_NESTED_BIND_DEF(i) \
namespace aux { \
template< typename F AUX_BIND_N_PARAMS(i, typename T) > \
aux::yes_tag \
is_bind_helper(bind##i<F AUX_BIND_N_PARAMS(i, T)>*); \
} \
/**/

template< typename T > struct is_bind_template
{
    BOOST_STATIC_CONSTANT(bool, value =
        sizeof(aux::is_bind_helper(static_cast<T*>(0)))
            == sizeof(aux::yes_tag)
        );
};

#endif // #if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)


#if defined(BOOST_NO_DEFAULT_TEMPLATE_PARAMETERS_IN_NESTED_TEMPLATES)

template< typename F, AUX_BIND_PARAMS(typename T), long N >
struct arity< bind<F, AUX_BIND_PARAMS(T)>,N >
{
    BOOST_STATIC_CONSTANT(long
        , value = BOOST_MPL_METAFUNCTION_MAX_ARITY
        );
};

template< typename F, typename T, long N >
struct arity< bind1st<F,T>,N >
{
    BOOST_STATIC_CONSTANT(long
        , value = BOOST_MPL_METAFUNCTION_MAX_ARITY
        );
};

template< typename F, typename T, long N >
struct arity< bind2nd<F,T>,N >
{
    BOOST_STATIC_CONSTANT(long
        , value = BOOST_MPL_METAFUNCTION_MAX_ARITY
        );
};

#   define AUX_ARITY_TEMPLATE_SPEC(i) \
namespace aux { \
template< typename F AUX_BIND_N_PARAMS(i, typename T), long N > \
struct arity< \
      bind##i<F AUX_BIND_N_PARAMS(i, T)> \
    , N \
    > \
{ \
    BOOST_STATIC_CONSTANT(long \
        , value = BOOST_MPL_METAFUNCTION_MAX_ARITY \
        ); \
}; \
} \
/**/

#else

#   define AUX_ARITY_TEMPLATE_SPEC(i) /**/

#endif // #if defined(BOOST_NO_DEFAULT_TEMPLATE_PARAMETERS_IN_NESTED_TEMPLATES)

} // namespace aux


#define AUX_BIND_IMPL_CHOOSER_SPEC(i) \
namespace aux { \
template<> \
struct bind_impl_chooser<i> \
{ \
    template< typename F, AUX_BIND_PARAMS(typename T) > \
    struct result_ \
    { \
        typedef bind##i< \
              F AUX_BIND_N_PARAMS(i, T) \
            > type; \
    }; \
}; \
} \
/**/

#define AUX_BIND_TEMPLATE_DEF(i, unused) \
    AUX_RESOLVE_BIND_ARGUMENT_SPEC(i) \
    AUX_BIND_N_TEMPLATE_DEF(i) \
    AUX_IS_NESTED_BIND_DEF(i) \
    AUX_ARITY_TEMPLATE_SPEC(i) \
    AUX_BIND_IMPL_CHOOSER_SPEC(i) \
/**/

// bind# 
BOOST_PP_REPEAT_2ND(
      BOOST_PP_INC(BOOST_MPL_METAFUNCTION_MAX_ARITY)
    , AUX_BIND_TEMPLATE_DEF
    , unused
    )

BOOST_MPL_AUX_COUNT_IF_NOT(bind, BOOST_MPL_METAFUNCTION_MAX_ARITY)

// bind
template<
      typename F
    , AUX_BIND_DEFAULT_PARAMS(typename T, aux::none)
    >
struct bind
    : aux::bind_impl_chooser<
          aux::bind_count_if_not<aux::none, AUX_BIND_PARAMS(T)>::value
        >::template result_< F, AUX_BIND_PARAMS(T) >::type
{
};

// bind1st/bind2nd, lightweight, for simple cases/backward compatibility
template< typename F, typename T >
struct bind1st
{
    template<
          typename U
        BOOST_MPL_AUX_DEF_PARAMS_TAIL(1, typename U)
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
        BOOST_MPL_AUX_DEF_PARAMS_TAIL(1, typename U)
        >
    struct apply
        : apply2<F,U,T>
    {
    };
};

#undef AUX_BIND_TEMPLATE_DEF
#undef AUX_BIND_IMPL_CHOOSER_SPEC
#undef AUX_ARITY_TEMPLATE_SPEC
#undef AUX_IS_NESTED_BIND_DEF
#undef AUX_BIND_N_TEMPLATE_DEF
#undef AUX_RESOLVE_ARGUMENT_INVOCATION
#undef AUX_RESOLVE_BIND_ARGUMENT_N_SPEC
#undef AUX_RESOLVE_BIND_ARGUMENT_0_SPEC
#undef AUX_RESOLVE_BIND_ARGUMENT_SPEC
#undef AUX_BIND_N_PARAMS
#undef AUX_BIND_DEFAULT_PARAMS
#undef AUX_BIND_PARAMS
#undef AUX_APPLY

} // namespace mpl
} // namespace boost

#endif // #if defined(BOOST_MPL_USE_PREPROCESSED_HEADERS)

#endif // #ifndef BOOST_MPL_BIND_HPP_INCLUDED

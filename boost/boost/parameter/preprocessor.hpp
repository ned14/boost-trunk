// Copyright Daniel Wallin 2006. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_PREPROCESSOR_060206_HPP
# define BOOST_PARAMETER_PREPROCESSOR_060206_HPP

# include <boost/parameter/parameters.hpp>
# include <boost/parameter/binding.hpp>
# include <boost/parameter/match.hpp>

# include <boost/parameter/aux_/parenthesized_type.hpp>
# include <boost/parameter/aux_/preprocessor/flatten.hpp>

# include <boost/preprocessor/repetition/repeat_from_to.hpp>
# include <boost/preprocessor/control/if.hpp>
# include <boost/preprocessor/control/expr_if.hpp>
# include <boost/preprocessor/repetition/enum_params.hpp>
# include <boost/preprocessor/repetition/enum_binary_params.hpp>
# include <boost/preprocessor/repetition/enum_trailing.hpp>
# include <boost/preprocessor/seq/first_n.hpp>
# include <boost/preprocessor/seq/for_each_product.hpp>
# include <boost/preprocessor/seq/for_each_i.hpp> 
# include <boost/preprocessor/tuple/elem.hpp> 
# include <boost/preprocessor/seq/fold_left.hpp>
# include <boost/preprocessor/seq/size.hpp>
# include <boost/preprocessor/seq/enum.hpp>

# include <boost/mpl/always.hpp>
# include <boost/mpl/apply_wrap.hpp>

namespace boost { namespace parameter { namespace aux {

#  ifndef BOOST_NO_SFINAE

// Given Match, which is "void x" where x is an argument matching
// criterion, extract a corresponding MPL predicate.
template <class Match>
struct unwrap_predicate;

// Match anything
template <>
struct unwrap_predicate<void*>
{
    typedef mpl::always<mpl::true_> type;
};

// A matching predicate is explicitly specified
template <class Predicate>
struct unwrap_predicate<void *(Predicate)>
{
    typedef Predicate type;
};

// A type to which the argument is supposed to be convertible is
// specified
template <class Target>
struct unwrap_predicate<void (Target)>
{
    typedef is_convertible<mpl::_, T> type;
};

// Recast the ParameterSpec's nested match metafunction as a free metafunction
template <
    class Parameters
  , BOOST_PP_ENUM_BINARY_PARAMS(
        BOOST_PARAMETER_MAX_ARITY, class A, = boost::parameter::void_ BOOST_PP_INTERCEPT
    )
>
struct match
  : Parameters::template match<
        BOOST_PP_ENUM_PARAMS(BOOST_PARAMETER_MAX_ARITY, A)
    >
{};
# endif 

template <
    class Parameters
  , BOOST_PP_ENUM_BINARY_PARAMS(
        BOOST_PARAMETER_MAX_ARITY, class A, = boost::parameter::void_ BOOST_PP_INTERCEPT
    )
>
struct argument_pack
{
    typedef typename mpl::apply_wrap1<
        BOOST_PARAMETER_build_arg_list(
            BOOST_PARAMETER_MAX_ARITY, aux::make_partial_arg_list, typename Parameters::parameter_spec, A
          , aux::tag_keyword_arg
        )
      , typename Parameters::unnamed_list
    >::type type;
    
};

}}} // namespace boost::parameter::aux

// Calculates [begin, end) arity range.

# define BOOST_PARAMETER_ARITY_RANGE_M_optional(state) state
# define BOOST_PARAMETER_ARITY_RANGE_M_required(state) BOOST_PP_INC(state)

# define BOOST_PARAMETER_ARITY_RANGE_M(s, state, x) \
    BOOST_PP_CAT( \
        BOOST_PARAMETER_ARITY_RANGE_M_ \
      , BOOST_PARAMETER_FN_ARG_QUALIFIER(x) \
    )(state)
/**/

# define BOOST_PARAMETER_ARITY_RANGE(args) \
    ( \
        BOOST_PP_SEQ_FOLD_LEFT(BOOST_PARAMETER_ARITY_RANGE_M, 0, args) \
      , BOOST_PP_INC(BOOST_PP_SEQ_SIZE(args)) \
    )
/**/

# define BOOST_PARAMETER_FN_ARG_QUALIFIER(x) \
    BOOST_PP_TUPLE_ELEM(3,0,x)
/**/

# define BOOST_PARAMETER_FN_ARG_NAME(x) \
    BOOST_PP_TUPLE_ELEM(3,1,x)
/**/

# define BOOST_PARAMETER_FN_ARG_PRED(x) \
    BOOST_PP_TUPLE_ELEM(3,2,x)
/**/

# define BOOST_PARAMETETER_FUNCTION_EAT_KEYWORD_QUALIFIER_out(x)
# define BOOST_PARAMETETER_FUNCTION_EAT_KEYWORD_QUALIFIER_in_out(x)
# define BOOST_PARAMETER_FUNCTION_IS_KEYWORD_QUALIFIER(x) \
    BOOST_PP_IS_EMPTY( \
        BOOST_PP_CAT(BOOST_PARAMETETER_FUNCTION_EAT_KEYWORD_QUALIFIER_, x) \
    ) \
/**/

# define BOOST_PARAMETETER_FUNCTION_GET_KEYWORD_QUALIFIER_out(x) x
# define BOOST_PARAMETETER_FUNCTION_GET_KEYWORD_QUALIFIER_in_out(x) x
# define BOOST_PARAMETER_FUNCTION_KEYWORD_GET(x) \
    BOOST_PP_CAT(BOOST_PARAMETETER_FUNCTION_GET_KEYWORD_QUALIFIER_, x)
/**/

# define BOOST_PARAMETER_FUNCTION_KEYWORD(x) \
    BOOST_PP_IF( \
        BOOST_PARAMETER_FUNCTION_IS_KEYWORD_QUALIFIER(x) \
      , BOOST_PARAMETER_FUNCTION_KEYWORD_GET \
      , x BOOST_PP_TUPLE_EAT(1) \
    )(x)
/**/

// Builds forwarding functions.

# define BOOST_PARAMETER_FUNCTION_FWD_FUNCTION_TEMPLATE_Z(z, n) \
    template<BOOST_PP_ENUM_PARAMS_Z(z, n, class ParameterArgumentType)>
/**/

# ifndef BOOST_NO_SFINAE
#  define BOOST_PARAMETER_FUNCTION_FWD_MATCH_Z(z, name, parameters, n) \
    , typename boost::parameter::aux::match< \
          parameters, BOOST_PP_ENUM_PARAMS(n, ParameterArgumentType) \
      >::type boost_parameter_enabler_argument = parameters()
# else
#  define BOOST_PARAMETER_FUNCTION_FWD_MATCH_Z(z, name, parameters, n)
# endif
/**/

# define BOOST_PARAMETER_FUNCTION_PARAMETERS_NAME(base) \
    BOOST_PP_CAT(boost_param_parameters_, BOOST_PP_CAT(__LINE__, base))

// Produce a name for a result type metafunction for the function
// named base
# define BOOST_PARAMETER_FUNCTION_RESULT_NAME(base) \
    BOOST_PP_CAT(boost_param_result_, BOOST_PP_CAT(__LINE__,base))

// Can't do boost_param_impl_ ## basee because base might start with an underscore
# define BOOST_PARAMETER_IMPL(base) \
    BOOST_PP_CAT(boost_param_impl,base)

# define BOOST_PARAMETER_FUNCTION_FWD_FUNCTION00(z, n, r, data, elem) \
    BOOST_PP_IF( \
        n \
      , BOOST_PARAMETER_FUNCTION_FWD_FUNCTION_TEMPLATE_Z, BOOST_PP_TUPLE_EAT(2) \
    )(z,n) \
    inline \
    BOOST_PP_EXPR_IF(n, typename) \
        BOOST_PARAMETER_FUNCTION_RESULT_NAME(BOOST_PP_TUPLE_ELEM(7,3,data))<   \
        BOOST_PP_EXPR_IF(n, typename) \
        boost::parameter::aux::argument_pack< \
            BOOST_PARAMETER_FUNCTION_PARAMETERS_NAME(BOOST_PP_TUPLE_ELEM(7,3,data)) \
            BOOST_PP_COMMA_IF(n) \
            BOOST_PP_IF( \
                n, BOOST_PP_SEQ_ENUM, BOOST_PP_TUPLE_EAT(1) \
            )(elem) \
        >::type \
    >::type \
    BOOST_PP_TUPLE_ELEM(7,3,data)( \
        BOOST_PP_IF( \
            n \
          , BOOST_PP_SEQ_FOR_EACH_I_R \
          , BOOST_PP_TUPLE_EAT(4) \
        )( \
            r \
          , BOOST_PARAMETER_FUNCTION_ARGUMENT \
          , ~ \
          , elem \
        ) \
        BOOST_PP_IF(n, BOOST_PARAMETER_FUNCTION_FWD_MATCH_Z, BOOST_PP_TUPLE_EAT(4))( \
            z \
          , BOOST_PP_TUPLE_ELEM(7,3,data) \
          , BOOST_PARAMETER_FUNCTION_PARAMETERS_NAME(BOOST_PP_TUPLE_ELEM(7,3,data)) \
          , n \
        ) \
    ) BOOST_PP_EXPR_IF(BOOST_PP_TUPLE_ELEM(7,4,data), const) \
    { \
        return BOOST_PARAMETER_IMPL(BOOST_PP_TUPLE_ELEM(7,3,data))( \
            BOOST_PARAMETER_FUNCTION_PARAMETERS_NAME(BOOST_PP_TUPLE_ELEM(7,3,data))()( \
                BOOST_PP_ENUM_PARAMS_Z(z, n, a) \
            ) \
        ); \
    }
/**/

# define BOOST_PARAMETER_FUNCTION_FWD_FUNCTION0(r, data, elem) \
    BOOST_PARAMETER_FUNCTION_FWD_FUNCTION00( \
        BOOST_PP_TUPLE_ELEM(7,0,data) \
      , BOOST_PP_TUPLE_ELEM(7,1,data) \
      , r \
      , data \
      , elem \
    )
/**/

# define BOOST_PARAMETER_FUNCTION_FWD_FUNCTION_ARITY_0(z, n, data) \
    BOOST_PARAMETER_FUNCTION_FWD_FUNCTION00( \
        z, n, BOOST_PP_DEDUCE_R() \
      , (z, n, BOOST_PP_TUPLE_REM(5) data) \
      , ~ \
    )
/**/

# define BOOST_PARAMETER_FUNCTION_FWD_FUNCTION_ARITY_N(z, n, data) \
    BOOST_PP_SEQ_FOR_EACH( \
        BOOST_PARAMETER_FUNCTION_FWD_FUNCTION0 \
      , (z, n, BOOST_PP_TUPLE_REM(5) data) \
      , BOOST_PP_SEQ_FOR_EACH_PRODUCT( \
            BOOST_PARAMETER_FUNCTION_FWD_PRODUCT \
          , BOOST_PP_SEQ_FIRST_N( \
                n, BOOST_PP_TUPLE_ELEM(5,3,data) \
            ) \
        ) \
    )
/**/

# define BOOST_PARAMETER_FUNCTION_FWD_FUNCTION(z, n, data) \
    BOOST_PP_IF( \
        n \
      , BOOST_PARAMETER_FUNCTION_FWD_FUNCTION_ARITY_N \
      , BOOST_PARAMETER_FUNCTION_FWD_FUNCTION_ARITY_0 \
    )(z,n,data) \
/**/

# define BOOST_PARAMETER_FUNCTION_FWD_FUNCTIONS0( \
    result,name,args,const_,combinations,range \
) \
    BOOST_PP_REPEAT_FROM_TO( \
        BOOST_PP_TUPLE_ELEM(2,0,range), BOOST_PP_TUPLE_ELEM(2,1,range) \
      , BOOST_PARAMETER_FUNCTION_FWD_FUNCTION \
      , (result,name,const_,combinations,BOOST_PP_TUPLE_ELEM(2,1,range)) \
    )
/**/

# define BOOST_PARAMETER_FUNCTION_FWD_FUNCTIONS(result,name,args, const_, combinations) \
    BOOST_PARAMETER_FUNCTION_FWD_FUNCTIONS0( \
        result, name, args, const_, combinations, BOOST_PARAMETER_ARITY_RANGE(args) \
    )
/**/

// Builds boost::parameter::parameters<> specialization
# if !BOOST_WORKAROUND(BOOST_MSVC, <= 1300) && !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#  define BOOST_PARAMETER_FUNCTION_PARAMETERS_M(r,tag_namespace,i,elem) \
    BOOST_PP_COMMA_IF(i) \
    boost::parameter::BOOST_PARAMETER_FN_ARG_QUALIFIER(elem)< \
        tag_namespace::BOOST_PARAMETER_FUNCTION_KEYWORD( \
            BOOST_PARAMETER_FN_ARG_NAME(elem) \
        ) \
      , typename boost::parameter::aux::unwrap_predicate< \
            void BOOST_PARAMETER_FN_ARG_PRED(elem) \
        >::type \
    >
# else
#  define BOOST_PARAMETER_FUNCTION_PARAMETERS_M(r,tag_namespace,i,elem) \
    BOOST_PP_COMMA_IF(i) \
    boost::parameter::BOOST_PARAMETER_FN_ARG_QUALIFIER(elem)< \
        tag_namespace::BOOST_PARAMETER_FUNCTION_KEYWORD( \
            BOOST_PARAMETER_FN_ARG_NAME(elem) \
        ) \
      , boost::mpl::always<boost::mpl::true_> \
    >
# endif
/**/

# define BOOST_PARAMETER_FUNCTION_PARAMETERS(tag_namespace, base, args)             \
    template <class BoostParameterDummy>                                      \
    struct BOOST_PP_CAT(BOOST_PP_CAT(boost_param_params_, __LINE__), base)          \
      : boost::parameter::parameters<                                               \
            BOOST_PP_SEQ_FOR_EACH_I(                                                \
                BOOST_PARAMETER_FUNCTION_PARAMETERS_M, tag_namespace, args          \
            )                                                                       \
        >                                                                           \
    {};                                                                             \
                                                                                    \
    typedef BOOST_PP_CAT(BOOST_PP_CAT(boost_param_params_, __LINE__), base)<int>

// Defines result type metafunction
# define BOOST_PARAMETER_FUNCTION_RESULT_ARG(z, _, i, x) \
    BOOST_PP_COMMA_IF(i) class BOOST_PP_TUPLE_ELEM(3,1,x)
/**/

# define BOOST_PARAMETER_FUNCTION_RESULT_(result, name, args)                                   \
    template <class Args>                                                                       \
    struct BOOST_PARAMETER_FUNCTION_RESULT_NAME(name)                                           \
    {                                                                                           \
        typedef typename BOOST_PARAMETER_PARENTHESIZED_TYPE(result) type;                       \
    };

# if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)

#  define BOOST_PARAMETER_FUNCTION_RESULT(result, name, args)  \
    BOOST_PARAMETER_FUNCTION_RESULT_(result, name, args)        \
    template <>                                                 \
    struct BOOST_PARAMETER_FUNCTION_RESULT_NAME(name)<int>      \
    { typedef int type; };

# else

#  define BOOST_PARAMETER_FUNCTION_RESULT(result, name, args)  \
    BOOST_PARAMETER_FUNCTION_RESULT_(result, name, args)

# endif

// Defines implementation function
# define BOOST_PARAMETER_FUNCTION_IMPL_HEAD(name)           \
    template <class Args>                                   \
    typename BOOST_PARAMETER_FUNCTION_RESULT_NAME(name)<    \
       Args                                                 \
    >::type BOOST_PARAMETER_IMPL(name)(Args const& args)

# define BOOST_PARAMETER_FUNCTION_IMPL_FWD(name) \
    BOOST_PARAMETER_FUNCTION_IMPL_HEAD(name);
/**/

# define BOOST_PARAMETER_FUNCTION_HEAD(result, name, tag_namespace, args)   \
      BOOST_PARAMETER_FUNCTION_RESULT(result, name, args)                   \
                                                                            \
          BOOST_PARAMETER_FUNCTION_PARAMETERS(tag_namespace, name, args)    \
          BOOST_PARAMETER_FUNCTION_PARAMETERS_NAME(name);                   \
                                                                            
// Defines a Boost.Parameter enabled function.
# define BOOST_PARAMETER_FUNCTION_AUX(result, name, tag_namespace, args)    \
    BOOST_PARAMETER_FUNCTION_HEAD(result, name, tag_namespace, args)        \
                                                                            \
    BOOST_PARAMETER_FUNCTION_IMPL_FWD(name)                                 \
                                                                            \
    BOOST_PARAMETER_FUNCTION_FWD_FUNCTIONS(                                 \
        result, name, args, 0                                               \
      , BOOST_PARAMETER_FUNCTION_FWD_COMBINATIONS(args)                     \
    )                                                                       \
                                                                            \
    BOOST_PARAMETER_FUNCTION_IMPL_HEAD(name)

# define BOOST_PARAMETER_FUNCTION(result, name, tag_namespace, args)    \
    BOOST_PARAMETER_FUNCTION_AUX(                                       \
        result, name, tag_namespace                                     \
      , BOOST_PARAMETER_FLATTEN(2, 2, args)                             \
    )                                                                   \
/**/

// Defines a Boost.Parameter enabled member function.
# define BOOST_PARAMETER_MEMBER_FUNCTION_AUX(result, name, tag_namespace, args, const_) \
    BOOST_PARAMETER_FUNCTION_HEAD(result, name, tag_namespace, args)                    \
                                                                                        \
    BOOST_PARAMETER_FUNCTION_FWD_FUNCTIONS(                                             \
        result, name, args, const_                                                      \
      , BOOST_PARAMETER_FUNCTION_FWD_COMBINATIONS(args)                                 \
    )                                                                                   \
                                                                                        \
    BOOST_PARAMETER_FUNCTION_IMPL_HEAD(name) BOOST_PP_EXPR_IF(const_, const)            \
/**/

# define BOOST_PARAMETER_MEMBER_FUNCTION(result, name, tag_namespace, args) \
    BOOST_PARAMETER_MEMBER_FUNCTION_AUX( \
        result, name, tag_namespace \
      , BOOST_PARAMETER_FLATTEN(2, 2, args) \
      , 0 \
    )
/**/

# define BOOST_PARAMETER_CONST_MEMBER_FUNCTION(result, name, tag_namespace, args) \
    BOOST_PARAMETER_MEMBER_FUNCTION_AUX( \
        result, name, tag_namespace \
      , BOOST_PARAMETER_FLATTEN(2, 2, args) \
      , 1 \
    )
/**/

// Defines a Boost.Parameter enabled constructor.

# define BOOST_PARAMETER_FUNCTION_ARGUMENT(r, _, i, elem) \
    BOOST_PP_COMMA_IF(i) elem& BOOST_PP_CAT(a, i)
/**/

# if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)

// Older MSVC can't do what's necessary to handle commas in base names; just
// use a typedef instead if you have a base name that contains commas.
#  define BOOST_PARAMETER_PARENTHESIZED_BASE(x) BOOST_PP_SEQ_HEAD(x)

# else

#  define BOOST_PARAMETER_PARENTHESIZED_BASE(x) BOOST_PARAMETER_PARENTHESIZED_TYPE(x)

# endif

# define BOOST_PARAMETER_FUNCTION_FWD_CONSTRUCTOR00(z, n, r, data, elem) \
    BOOST_PP_IF( \
        n \
      , BOOST_PARAMETER_FUNCTION_FWD_FUNCTION_TEMPLATE_Z, BOOST_PP_TUPLE_EAT(2) \
    )(z, n) \
    BOOST_PP_EXPR_IF(BOOST_PP_EQUAL(n,1), explicit) \
    BOOST_PP_TUPLE_ELEM(6,2,data)( \
        BOOST_PP_IF( \
            n \
          , BOOST_PP_SEQ_FOR_EACH_I_R \
          , BOOST_PP_TUPLE_EAT(4) \
        )( \
            r \
          , BOOST_PARAMETER_FUNCTION_ARGUMENT \
          , ~ \
          , elem \
        ) \
        BOOST_PP_IF(n, BOOST_PARAMETER_FUNCTION_FWD_MATCH_Z, BOOST_PP_TUPLE_EAT(4))( \
            z \
          , BOOST_PP_TUPLE_ELEM(6,3,data) \
          , BOOST_PP_CAT(constructor_parameters, __LINE__) \
          , n \
        ) \
    ) \
      : BOOST_PARAMETER_PARENTHESIZED_BASE(BOOST_PP_TUPLE_ELEM(6,3,data)) ( \
            BOOST_PP_CAT(constructor_parameters, __LINE__)()( \
                BOOST_PP_ENUM_PARAMS_Z(z, n, a) \
            ) \
        ) \
    {}
/**/

# define BOOST_PARAMETER_FUNCTION_FWD_CONSTRUCTOR0(r, data, elem) \
    BOOST_PARAMETER_FUNCTION_FWD_CONSTRUCTOR00( \
        BOOST_PP_TUPLE_ELEM(6,0,data) \
      , BOOST_PP_TUPLE_ELEM(6,1,data) \
      , r \
      , data \
      , elem \
    )
/**/

# define BOOST_PARAMETER_FUNCTION_FWD_PRODUCT(r, product) \
    (product)
/**/

# define BOOST_PARAMETER_FUNCTION_FWD_CONSTRUCTOR_ARITY_0(z, n, data) \
    BOOST_PARAMETER_FUNCTION_FWD_CONSTRUCTOR00( \
        z, n, BOOST_PP_DEDUCE_R() \
      , (z, n, BOOST_PP_TUPLE_REM(4) data) \
      , ~ \
    )
/**/

# define BOOST_PARAMETER_FUNCTION_FWD_CONSTRUCTOR_ARITY_N(z, n, data) \
    BOOST_PP_SEQ_FOR_EACH( \
        BOOST_PARAMETER_FUNCTION_FWD_CONSTRUCTOR0 \
      , (z, n, BOOST_PP_TUPLE_REM(4) data) \
      , BOOST_PP_SEQ_FOR_EACH_PRODUCT( \
            BOOST_PARAMETER_FUNCTION_FWD_PRODUCT \
          , BOOST_PP_SEQ_FIRST_N( \
                n, BOOST_PP_TUPLE_ELEM(4,2,data) \
            ) \
        ) \
    )
/**/

# define BOOST_PARAMETER_FUNCTION_FWD_CONSTRUCTOR(z, n, data) \
    BOOST_PP_IF( \
        n \
      , BOOST_PARAMETER_FUNCTION_FWD_CONSTRUCTOR_ARITY_N \
      , BOOST_PARAMETER_FUNCTION_FWD_CONSTRUCTOR_ARITY_0 \
    )(z,n,data) \
/**/

# define BOOST_PARAMETER_FUNCTION_FWD_CONSTRUCTORS0(class_,base,args,combinations,range) \
    BOOST_PP_REPEAT_FROM_TO( \
        BOOST_PP_TUPLE_ELEM(2,0,range), BOOST_PP_TUPLE_ELEM(2,1,range) \
      , BOOST_PARAMETER_FUNCTION_FWD_CONSTRUCTOR \
      , (class_,base,combinations,BOOST_PP_TUPLE_ELEM(2,1,range)) \
    )
/**/

# define BOOST_PARAMETER_FUNCTION_FWD_CONSTRUCTORS(class_,base,args,combinations) \
    BOOST_PARAMETER_FUNCTION_FWD_CONSTRUCTORS0( \
        class_, base, args, combinations, BOOST_PARAMETER_ARITY_RANGE(args) \
    )
/**/

# define BOOST_PARAMETER_CONSTRUCTOR_AUX(class_, base, tag_namespace, args) \
    BOOST_PARAMETER_FUNCTION_PARAMETERS(tag_namespace, ctor, args)          \
        BOOST_PP_CAT(constructor_parameters, __LINE__); \
\
    BOOST_PARAMETER_FUNCTION_FWD_CONSTRUCTORS( \
        class_, base, args \
      , BOOST_PARAMETER_FUNCTION_FWD_COMBINATIONS(args) \
    ) \
/**/

# define BOOST_PARAMETER_CONSTRUCTOR(class_, base, tag_namespace, args) \
    BOOST_PARAMETER_CONSTRUCTOR_AUX( \
        class_, base, tag_namespace \
      , BOOST_PARAMETER_FLATTEN(2, 2, args) \
    )
/**/

# ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
#  define BOOST_PARAMETER_FUNCTION_FWD_COMBINATION(r, _, i, elem) \
    (BOOST_PP_IF( \
        BOOST_PARAMETER_FUNCTION_IS_KEYWORD_QUALIFIER( \
            BOOST_PP_TUPLE_ELEM(3,1,elem) \
        ) \
      , (const ParameterArgumentType ## i)(ParameterArgumentType ## i) \
      , (const ParameterArgumentType ## i) \
    ))
# else
#  define BOOST_PARAMETER_FUNCTION_FWD_COMBINATION(r, _, i, elem) \
    (BOOST_PP_IF( \
        BOOST_PARAMETER_FUNCTION_IS_KEYWORD_QUALIFIER( \
            BOOST_PP_TUPLE_ELEM(3,1,elem) \
        ) \
      , (ParameterArgumentType ## i) \
      , (const ParameterArgumentType ## i) \
    ))
# endif

# define BOOST_PARAMETER_FUNCTION_FWD_COMBINATIONS(args) \
    BOOST_PP_SEQ_FOR_EACH_I(BOOST_PARAMETER_FUNCTION_FWD_COMBINATION, ~, args)

#endif // BOOST_PARAMETER_PREPROCESSOR_060206_HPP


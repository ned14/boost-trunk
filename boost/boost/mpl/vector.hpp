
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_VECTOR_HPP_INCLUDED
#define BOOST_MPL_VECTOR_HPP_INCLUDED

// Copyright (c) Aleksey Gurtovoy 2000-2004
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
#   include <boost/mpl/limits/vector.hpp>
#   include <boost/mpl/aux_/na.hpp>
#   include <boost/mpl/aux_/config/preprocessor.hpp>

#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>
#   include <boost/preprocessor/stringize.hpp>

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_VECTOR_HEADER \
    BOOST_PP_CAT(vector, BOOST_MPL_LIMIT_VECTOR_SIZE).hpp \
    /**/
#else
#   define AUX778076_VECTOR_HEADER \
    BOOST_PP_CAT(vector, BOOST_MPL_LIMIT_VECTOR_SIZE)##.hpp \
    /**/
#endif

#   include BOOST_PP_STRINGIZE(boost/mpl/vector/AUX778076_VECTOR_HEADER)
#   undef AUX778076_VECTOR_HEADER
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER vector.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/vector.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   include <boost/mpl/aux_/config/nttp.hpp>

#   include <boost/preprocessor/arithmetic/sub.hpp>
#   include <boost/preprocessor/tuple/elem.hpp>
#   include <boost/preprocessor/enum_params_with_a_default.hpp>
#   include <boost/preprocessor/enum_params.hpp>
#   include <boost/preprocessor/enum.hpp>
#   include <boost/preprocessor/repeat.hpp>
#   include <boost/preprocessor/comma_if.hpp>
#   include <boost/preprocessor/iterate.hpp>

namespace boost { namespace mpl {

#   define AUX778076_VECTOR_PARAMS(param) \
    BOOST_PP_ENUM_PARAMS( \
          BOOST_MPL_LIMIT_VECTOR_SIZE \
        , param \
        ) \
    /**/

#   define AUX778076_VECTOR_DEFAULT_PARAMS(param, value) \
     BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT( \
          BOOST_MPL_LIMIT_VECTOR_SIZE \
        , param \
        , value \
        ) \
    /**/

#   define AUX778076_VECTOR_N_PARAMS(n, param) \
    BOOST_PP_ENUM_PARAMS(n, param) \
    /**/

#   define AUX778076_VECTOR_N_PARTIAL_SPEC_PARAMS(n, param, def) \
    BOOST_PP_ENUM_PARAMS(n, param) \
    BOOST_PP_COMMA_IF(n) \
    BOOST_PP_ENUM( \
          BOOST_PP_SUB_D(1,BOOST_MPL_LIMIT_VECTOR_SIZE,n) \
        , BOOST_PP_TUPLE_ELEM_3_2 \
        , def \
        ) \
    /**/

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
// forward declaration
template<
      AUX778076_VECTOR_DEFAULT_PARAMS(typename T, na)
    >
struct vector;
#else
namespace aux {
template< AUX778076_NTTP_DECL(int, N) > struct vector_chooser;
}
#endif

#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, BOOST_MPL_LIMIT_VECTOR_SIZE, <boost/mpl/vector.hpp>))
#include BOOST_PP_ITERATE()

// real C++ version is already taken care of
#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

namespace aux {
// vector_count_args
#define AUX778076_COUNT_ARGS_PREFIX vector
#define AUX778076_COUNT_ARGS_DEFAULT na
#define AUX778076_COUNT_ARGS_ARITY BOOST_MPL_LIMIT_VECTOR_SIZE
#define AUX778076_COUNT_ARGS_USE_STANDARD_PP_PRIMITIVES
#include <boost/mpl/aux_/count_args.hpp>

template<
      AUX778076_VECTOR_PARAMS(typename T)
    >
struct vector_impl
{
    typedef aux::vector_count_args< AUX778076_VECTOR_PARAMS(T) > arg_num_;
    typedef typename aux::vector_chooser< arg_num_::value >
        ::template result_< AUX778076_VECTOR_PARAMS(T) >::type type;
};

} // namespace aux

template<
      AUX778076_VECTOR_DEFAULT_PARAMS(typename T, na)
    >
struct vector
    : aux::vector_impl< AUX778076_VECTOR_PARAMS(T) >::type
{
    typedef typename aux::vector_impl<
          AUX778076_VECTOR_PARAMS(T)
        >::type type;
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#   undef AUX778076_VECTOR_N_PARTIAL_SPEC_PARAMS
#   undef AUX778076_VECTOR_N_PARAMS
#   undef AUX778076_VECTOR_DEFAULT_PARAMS
#   undef AUX778076_VECTOR_PARAMS

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_VECTOR_HPP_INCLUDED

///// iteration

#else
#define i_ BOOST_PP_FRAME_ITERATION(1)

#   if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

#if i_ == BOOST_MPL_LIMIT_VECTOR_SIZE

//: primary template (not a specialization!)
template<
      AUX778076_VECTOR_N_PARAMS(i_, typename T)
    >
struct vector
    : BOOST_PP_CAT(vector,i_)< AUX778076_VECTOR_N_PARAMS(i_, T) >
{
    typedef BOOST_PP_CAT(vector,i_)< AUX778076_VECTOR_N_PARAMS(i_, T) > type;
};

#else

template<
      AUX778076_VECTOR_N_PARAMS(i_, typename T)
    >
struct vector< AUX778076_VECTOR_N_PARTIAL_SPEC_PARAMS(i_, T, na) >
    : BOOST_PP_CAT(vector,i_)< AUX778076_VECTOR_N_PARAMS(i_, T) >
{
    typedef BOOST_PP_CAT(vector,i_)< AUX778076_VECTOR_N_PARAMS(i_, T) > type;
};

#endif // i_ == BOOST_MPL_LIMIT_VECTOR_SIZE

#   else

namespace aux {

template<>
struct vector_chooser<i_>
{
    template<
          AUX778076_VECTOR_PARAMS(typename T)
        >
    struct result_
    {
        typedef BOOST_PP_CAT(vector,i_)<
              AUX778076_VECTOR_N_PARAMS(i_, T)
            > type;
    };
};

} // namespace aux

#   endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#undef i_
#endif // BOOST_PP_IS_ITERATING

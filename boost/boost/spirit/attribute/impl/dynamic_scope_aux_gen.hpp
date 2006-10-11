/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#ifndef SPIRIT_ATTRIBUTE_DYNAMIC_SCOPE_AUX_GEN_HPP
#define SPIRIT_ATTRIBUTE_DYNAMIC_SCOPE_AUX_GEN_HPP

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

#define BOOST_SPIRIT_AS_ACTOR(z, n, data)                                       \
    typename phoenix::as_actor<U##n>::type

#define BOOST_SPIRIT_CONVERT_ACTOR(z, n, data)                                  \
    phoenix::as_actor<U##n>::convert(_##n)

#define BOOST_PP_FILENAME_1 \
    <boost/spirit/attribute/impl/dynamic_scope_aux_gen.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, BOOST_SPIRIT_DYNAMIC_SCOPE_LIMIT)
#include BOOST_PP_ITERATE()

#undef BOOST_SPIRIT_AS_ACTOR
#undef BOOST_SPIRIT_CONVERT_ACTOR
#endif

///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////
#else // defined(BOOST_PP_IS_ITERATING)

#define N BOOST_PP_ITERATION()

    template <BOOST_PP_ENUM_PARAMS(N, typename U)>
    init_dynamic_scope_parser<
        Derived2,
        fusion::vector<BOOST_PP_ENUM(N, BOOST_SPIRIT_AS_ACTOR, _)>
    >
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(N, U, const& _)) const
    {
        typedef 
            fusion::vector<BOOST_PP_ENUM(N, BOOST_SPIRIT_AS_ACTOR, _)> 
        actor_tuple_t;

        return init_dynamic_scope_parser<Derived2, actor_tuple_t>(
                aux_derived(),
                actor_tuple_t(BOOST_PP_ENUM(N, BOOST_SPIRIT_CONVERT_ACTOR, _))
            );
    }  

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)



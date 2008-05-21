#ifndef BOOST_PP_IS_ITERATING
    /*=============================================================================
        Copyright (c) 2001-2007 Joel de Guzman
        Copyright (c) 2008 Eric Niebler

        Distributed under the Boost Software License, Version 1.0. (See accompanying
        file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    ==============================================================================*/
    #ifndef BOOST_PHOENIX_BIND_BIND_HPP_EAN_2008_05_21
    #define BOOST_PHOENIX_BIND_BIND_HPP_EAN_2008_05_21

    #include <boost/preprocessor.hpp>
    #include <boost/mpl/if.hpp>
    #include <boost/proto/proto.hpp>
    #include <boost/phoenix/core/actor.hpp>
    #include <boost/type_traits/is_member_pointer.hpp>

    namespace boost { namespace phoenix
    {
        template<typename Fun>
        actor<
            typename proto::result_of::make_expr<
                proto::tag::function
              , proto::default_domain
              , Fun
            >::type
        > const
        bind(Fun const &fun)
        {
            return proto::implicit_expr(fun);
        }

        #define BOOST_PP_ITERATION_PARAMS_1                                             \
            (3, (1, BOOST_PP_SUB(PHOENIX_LIMIT, 2), <boost/phoenix/bind/bind.hpp>))
        #include BOOST_PP_ITERATE()

    }}

    #endif

#else

    #define N BOOST_PP_ITERATION()

        template<
            typename Fun
          , typename A0
            BOOST_PP_COMMA_IF(BOOST_PP_DEC(N))
            BOOST_PP_ENUM_SHIFTED_PARAMS(N, typename A)
        >
        actor<
            typename proto::result_of::make_expr<
                proto::tag::function
              , proto::default_domain
              , Fun
              , typename mpl::if_<
                    is_member_pointer<Fun>
                  , A0 &
                  , A0
                >::type
                BOOST_PP_COMMA_IF(BOOST_PP_DEC(N))
                BOOST_PP_ENUM_SHIFTED_PARAMS(N, A)
            >::type
        > const
        bind(
            Fun const &fun
          , A0 &a0
            BOOST_PP_COMMA_IF(BOOST_PP_DEC(N))
            BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS(N, A, const &a)
        )
        {
            return proto::implicit_expr(fun BOOST_PP_ENUM_TRAILING_PARAMS(N, a));
        }

        template<
            typename Fun
          , typename A0
            BOOST_PP_COMMA_IF(BOOST_PP_DEC(N))
            BOOST_PP_ENUM_SHIFTED_PARAMS(N, typename A)
        >
        actor<
            typename proto::result_of::make_expr<
                proto::tag::function
              , proto::default_domain
              , Fun
              , typename mpl::if_<
                    is_member_pointer<Fun>
                  , A0 const &
                  , A0
                >::type
                BOOST_PP_COMMA_IF(BOOST_PP_DEC(N))
                BOOST_PP_ENUM_SHIFTED_PARAMS(N, A)
            >::type
        > const
        bind(
            Fun const &fun
          , A0 const &a0 
            BOOST_PP_COMMA_IF(BOOST_PP_DEC(N))
            BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS(N, A, const &a)
        )
        {
            return proto::implicit_expr(fun BOOST_PP_ENUM_TRAILING_PARAMS(N, a));
        }

    #undef N

#endif

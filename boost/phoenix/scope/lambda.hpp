#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)

#ifndef BOOST_PHOENIX_SCOPE_LAMBDA_HPP
#define BOOST_PHOENIX_SCOPE_LAMBDA_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/mpl/int.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/scope/local_variable.hpp>
#include <boost/phoenix/scope/scoped_environment.hpp>

#include <boost/phoenix/scope/preprocessed/lambda.hpp>

#endif
#else

#ifndef BOOST_PHOENIX_SCOPE_LAMBDA_HPP
#define BOOST_PHOENIX_SCOPE_LAMBDA_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/mpl/int.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/scope/local_variable.hpp>
#include <boost/phoenix/scope/scoped_environment.hpp>

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/lambda_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif
/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2004 Daniel Wallin
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

    
BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(lambda)
  , (proto::terminal<proto::_>) // OuterEnv 
    (proto::terminal<proto::_>) // Locals
    (meta_grammar)              // Lambda
)

namespace boost { namespace phoenix
{

    struct lambda_eval
    {
        BOOST_PROTO_CALLABLE()

        template <typename Sig>
        struct result;

        template <
            typename This
          , typename OuterEnv
          , typename Locals
          , typename Lambda
          , typename Context
        >
        struct result<This(OuterEnv &, Locals &, Lambda &, Context)>
        {
            typedef
                typename result_of::env<Context>::type
                env_type;

            typedef
                typename result_of::actions<Context>::type
                actions_type;

            typedef
                typename proto::result_of::value<Locals>::type
                locals_type;

            typedef
                typename proto::result_of::value<OuterEnv>::type
                outer_env_type;

            typedef
                scoped_environment<env_type, outer_env_type, locals_type>
                scoped_env;

            typedef
                typename result_of::context<scoped_env, actions_type>::type
                ctx_type;

            typedef
                typename evaluator::impl<Lambda const &, ctx_type const&, int>::result_type
                type;
        };
        
        template <
            typename OuterEnv
          , typename Locals
          , typename Lambda
          , typename Context
        >
        typename result<
            lambda_eval(OuterEnv const&, Locals const&, Lambda const&, Context &)
        >::type
        operator()(
            OuterEnv const & outer_env
          , Locals const& locals
          , Lambda const& lambda
          , Context & ctx
        ) const
        {
            typedef
                typename result_of::env<Context>::type
                env_type;

            typedef
                typename result_of::actions<Context>::type
                actions_type;

            typedef
                typename proto::result_of::value<Locals>::type
                locals_type;

            typedef
                typename proto::result_of::value<OuterEnv>::type
                outer_env_type;

            typedef
                scoped_environment<env_type, outer_env_type, locals_type>
                scoped_env_type;

            env_type e(env(ctx));

            scoped_env_type
                scoped_env(
                    e
                  , proto::value(outer_env)
                  , proto::value(locals)
                );

            return boost::phoenix::eval(lambda, context(scoped_env, actions(ctx)));
        }
    };

    template <typename Dummy>
    struct default_actions::when<rule::lambda, Dummy>
        : call<lambda_eval, Dummy>
    {};

    template <typename Dummy>
    struct is_nullary::when<rule::lambda, Dummy>
        : proto::call<
            evaluator(
                proto::_child_c<2>
              , proto::call<
                    functional::context(
                        proto::make<
                            mpl::true_()
                        >
                      , proto::make<
                            detail::scope_is_nullary_actions()
                        >
                    )
                >
              , proto::make<
                    int()
                >
            )
        >
    {};

    namespace tag
    {
        struct lambda_actor {};
    }

    namespace expression
    {
        template <typename A0 = void, typename A1 = void, typename Dummy = void>
        struct lambda_actor;

        template <typename A0>
        struct lambda_actor<A0>
            : expr<tag::lambda_actor, A0>
        {};

        template <typename A0, typename A1>
        struct lambda_actor<A0, A1>
            : expr< tag::lambda_actor, A0, A1>
        {};
    }

    namespace rule
    {
        struct lambda_actor
            : proto::or_<
                expression::lambda_actor<meta_grammar>
              , expression::lambda_actor<proto::terminal<proto::_>, meta_grammar>
            >
        {};
    }

    template <typename Dummy>
    struct is_nullary::when<rule::lambda_actor, Dummy>
        : proto::or_<
            proto::when<
                expression::lambda_actor<meta_grammar>
              , mpl::true_()
            >
          , proto::when<
                expression::lambda_actor<
                    proto::terminal<proto::_>
                  , meta_grammar
                >
              , detail::local_var_def_is_nullary<proto::_value(proto::_child_c<0>), _context>()
            >
        >
    {};

    template <typename Dummy>
    struct meta_grammar::case_<tag::lambda_actor, Dummy>
        : enable_rule<rule::lambda_actor, Dummy>
    {};

    struct lambda_actor_eval
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Lambda, typename Context>
        struct result<This(Lambda, Context)>
            : result<This(Lambda const &, Context)>
        {};

        template <typename This, typename Lambda, typename Context>
        struct result<This(Lambda &, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename result_of::env<Context>::type
                >::type
                env_type;

            typedef
                typename expression::lambda<
                    env_type
                  , mpl::void_
                  , Lambda
                >::type
                type;
        };
        
        template <typename This, typename Locals, typename Lambda, typename Context>
        struct result<This(Locals, Lambda, Context)>
            : result<This(Locals const &, Lambda const &, Context)>
        {};

        template <typename This, typename Locals, typename Lambda, typename Context>
        struct result<This(Locals&, Lambda&, Context)>
        {
            typedef
                typename 
                    boost::result_of<
                        detail::local_var_def_eval(
                            typename proto::result_of::value<
                                Locals&
                            >::type
                          , Context
                        )
                    >::type
                locals_type;

            typedef
                typename proto::detail::uncvref<
                    typename result_of::env<Context>::type
                >::type
                env_type;

            typedef
                typename expression::lambda<
                    env_type
                  , locals_type
                  , Lambda
                >::type const
                type;
        };

        template <typename Lambda, typename Context>
        typename result<lambda_actor_eval(Lambda const&, Context &)>::type
        operator()(Lambda const& lambda, Context & ctx) const
        {
            typedef
                typename proto::detail::uncvref<
                    typename result_of::env<Context>::type
                >::type
                env_type;

            mpl::void_ t;
            return
                expression::
                    lambda<env_type, mpl::void_, Lambda>::
                        make(env(ctx), t, lambda);
        }

        template <
            typename Locals
          , typename Lambda
          , typename Context
        >
        typename result<
            lambda_actor_eval(Locals const&, Lambda const&, Context &)
        >::type
        operator()(Locals const& locals, Lambda const& lambda, Context & ctx) const
        {
            typedef
                typename 
                    boost::result_of<
                        detail::local_var_def_eval(
                            typename proto::result_of::value<
                                Locals const &
                            >::type
                          , Context &
                        )
                    >::type
                locals_type;

            locals_type l
                = detail::local_var_def_eval()(proto::value(locals), ctx);

            typedef
                typename proto::detail::uncvref<
                    typename result_of::env<Context>::type
                >::type
                env_type;

            return
                expression::
                    lambda<env_type, locals_type, Lambda>::
                        make(env(ctx), l, lambda);
        }
    };

    template <typename Dummy>
    struct default_actions::when<rule::lambda_actor, Dummy>
        : call<lambda_actor_eval, Dummy>
    {};
    
    template <typename Locals = void, typename Dummy = void>
    struct lambda_actor_gen;

    template <>
    struct lambda_actor_gen<void, void>
    {
        template <typename Expr>
        typename expression::lambda_actor<Expr>::type const
        operator[](Expr const & expr) const
        {
            return expression::lambda_actor<Expr>::make(expr);
        }
    };

    template <typename Locals>
    struct lambda_actor_gen<Locals>
    {
        lambda_actor_gen(Locals const & locals)
            : locals(locals)
        {}

        template <typename Expr>
        typename expression::lambda_actor<
            Locals
          , Expr
        >::type const
        operator[](Expr const & expr) const
        {
            return expression::lambda_actor<Locals, Expr>::make(locals, expr);
        }

        Locals locals;
    };

    struct lambda_local_gen
        : lambda_actor_gen<>
    {
        lambda_actor_gen<> const
        operator()() const
        {
            return lambda_actor_gen<>();
        }

    #define BOOST_PHOENIX_LAMBDA_LOCAL_GEN(Z, N, DATA)                          \
        template <BOOST_PHOENIX_typename_A(N)>                                  \
        lambda_actor_gen<                                                       \
            typename detail::make_locals<BOOST_PHOENIX_A(N)>::type              \
        > const                                                                 \
        operator()(BOOST_PHOENIX_A_const_ref_a(N)) const                        \
        {                                                                       \
            return                                                              \
                detail::make_locals<BOOST_PHOENIX_A(N)>                         \
                    ::make(BOOST_PHOENIX_a(N));                                 \
        }                                                                       \
    /**/
        BOOST_PP_REPEAT_FROM_TO(
            1
          , BOOST_PHOENIX_LOCAL_LIMIT
          , BOOST_PHOENIX_LAMBDA_LOCAL_GEN
          , _
        )
    #undef BOOST_PHOENIX_LAMBDA_LOCAL_GEN
    };

    typedef lambda_local_gen lambda_type;
    lambda_local_gen const lambda = lambda_local_gen();

}}

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#endif

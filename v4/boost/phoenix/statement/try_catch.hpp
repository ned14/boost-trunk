/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman
    Copyright (c) 2008 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_TRY_CATCH_HPP_EAN_2008_05_18
#define BOOST_PHOENIX_TRY_CATCH_HPP_EAN_2008_05_18

#include <boost/preprocessor.hpp>
#include <boost/ref.hpp>
#include <boost/proto/proto.hpp>
#include <boost/phoenix/core/actor.hpp>

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable: 4355) // 'this' : used in base member initializer list
#endif

namespace boost { namespace phoenix
{
    ////////////////////////////////////////////////////////////////////////////////////////////
    namespace tag
    {
        struct try_ {};
        struct catch_all {};
        template<typename E>
        struct catch_
        {
            typedef E exception_type;
        };
    }

    namespace detail
    {
        ////////////////////////////////////////////////////////////////////////////////////////
        struct Try
          : proto::unary_expr<tag::try_, evaluator>
        {};

        ////////////////////////////////////////////////////////////////////////////////////////
        struct Catch
          : proto::switch_<struct CatchCases>
        {};

        struct CatchCases
        {
            template<typename Tag>
            struct case_
              : proto::not_<proto::_>
            {};

            template<typename E>
            struct case_<tag::catch_<E> >
              : proto::binary_expr<tag::catch_<E>, proto::or_<Try, Catch>, evaluator>
            {};
        };

        ////////////////////////////////////////////////////////////////////////////////////////
        struct CatchAll
          : proto::binary_expr<tag::catch_all, proto::or_<Try, Catch>, evaluator>
        {};

        ////////////////////////////////////////////////////////////////////////////////////////
        template<typename Expr>
        struct catch_all_generator
        {
            explicit catch_all_generator(Expr const &expr)
              : expr(expr)
            {}

            template<typename Body>
            typename proto::result_of::make_expr<
                tag::catch_all
              , domain
              , Expr const &
              , Body const &
            >::type const
            operator[](Body const &body) const
            {
                return proto::implicit_expr(this->expr, body);
            }

        private:
            catch_all_generator &operator =(catch_all_generator const &);
            Expr const &expr;
        };

        ////////////////////////////////////////////////////////////////////////////////////////
        template<typename Expr>
        struct actor_with_catch : Expr
        {
            actor_with_catch(Expr const &expr)
              : Expr(expr)
              , catch_all(*this)
            {}

            actor_with_catch(actor_with_catch const &that)
              : Expr(that)
              , catch_all(*this)
            {}

            catch_all_generator<Expr> catch_all;

            template<typename E>
            actor_with_catch<
                typename proto::result_of::make_expr<
                    tag::catch_<E>
                  , domain
                  , Expr const &
                >::type const
            > const
            catch_() const
            {
                boost::reference_wrapper<Expr const> that(*this);
                return proto::make_expr<tag::catch_<E>, domain>(that);
            }

            template<typename Body>
            actor_with_catch<
                typename proto::result_of::make_expr<
                    typename proto::tag_of<Expr>::type
                  , domain
                  , typename proto::result_of::child<Expr const &>::type
                  , Body const &
                >::type const
            > const
            operator[](Body const &body) const
            {
                typedef typename proto::tag_of<Expr>::type tag_type;
                return proto::make_expr<tag_type, domain>(boost::ref(proto::child(*this)), boost::ref(body));
            }

        private:
            actor_with_catch &operator=(actor_with_catch const &);
        };

        ////////////////////////////////////////////////////////////////////////////////////////
        struct try_generator
        {
            template<typename Body>
            actor_with_catch<
                typename proto::result_of::make_expr<
                    tag::try_
                  , domain
                  , Body const &
                >::type
            > const
            operator[](Body const &body) const
            {
                return proto::make_expr<tag::try_, domain>(boost::ref(body));
            }
        };

        ////////////////////////////////////////////////////////////////////////////////////////
        struct catch_all_evaluator
          : proto::transform<catch_all_evaluator>
        {
            template<typename Expr, typename State, typename Data>
            struct impl
              : proto::transform_impl<Expr, State, Data>
            {
                typedef void result_type;

                void operator()(
                    typename impl::expr_param expr
                  , typename impl::state_param state
                  , typename impl::data_param data
                ) const
                {
                    try
                    {
                        evaluator()(proto::child_c<0>(expr), state, data);
                    }
                    catch(...)
                    {
                        evaluator()(proto::child_c<1>(expr), state, data);
                    }
                }
            };
        };

        ////////////////////////////////////////////////////////////////////////////////////////
        template<typename E>
        struct catch_evaluator
          : proto::transform<catch_evaluator<E> >
        {
            template<typename Expr, typename State, typename Data>
            struct impl
              : proto::transform_impl<Expr, State, Data>
            {
                typedef void result_type;

                void operator()(
                    typename impl::expr_param expr
                  , typename impl::state_param state
                  , typename impl::data_param data
                ) const
                {
                    try
                    {
                        evaluator()(proto::child_c<0>(expr), state, data);
                    }
                    catch(E const &)
                    {
                        evaluator()(proto::child_c<1>(expr), state, data);
                    }
                }
            };
        };
    }

    ////////////////////////////////////////////////////////////////////////////////////////
    detail::try_generator const try_ = {};

    ////////////////////////////////////////////////////////////////////////////////////////
    template<>
    struct extension<tag::try_>
      : proto::when<detail::Try, evaluator(proto::_child)>
    {};

    ////////////////////////////////////////////////////////////////////////////////////////
    template<>
    struct extension<tag::catch_all>
      : proto::when<detail::CatchAll, detail::catch_all_evaluator>
    {};

    ////////////////////////////////////////////////////////////////////////////////////////
    template<typename E>
    struct extension<tag::catch_<E> >
      : proto::when<detail::Catch, detail::catch_evaluator<E> >
    {};

}}

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#endif

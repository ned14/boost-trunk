///////////////////////////////////////////////////////////////////////////////
/// \file as_expr.hpp
/// Contains definition of the as_expr\<\> and as_child\<\> helper class
/// templates used to implement proto::domain's as_expr\<\> and as_child\<\>
/// member templates.
//
//  Copyright 2010 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DETAIL_AS_EXPR_HPP_EAN_06_09_2010
#define BOOST_PROTO_DETAIL_AS_EXPR_HPP_EAN_06_09_2010

#include <boost/type_traits/is_same.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/args.hpp>

namespace boost { namespace proto { namespace detail
{
    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<
        typename T
      , typename Generator
      , bool IsExpr = is_expr<T>::value
      , bool WantsBasicExpr = wants_basic_expr<Generator>::value
    >
    struct as_expr;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<
        typename T
      , typename Generator
      , bool IsExpr = is_expr<T>::value
      , bool WantsBasicExpr = wants_basic_expr<Generator>::value
    >
    struct as_child;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename Expr, typename Generator, bool SameGenerator>
    struct already_expr
    {
        typedef typename Expr::proto_derived_expr uncv_expr_type;
        typedef typename Generator::template result<Generator(uncv_expr_type)>::type result_type;

        result_type operator()(Expr &e) const
        {
            return Generator()(e);
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename Expr, typename Generator>
    struct already_expr<Expr, Generator, true>
    {
        typedef typename Expr::proto_derived_expr result_type;

        result_type operator()(Expr &e) const
        {
            return e;
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename Expr, typename Generator, bool SameGenerator>
    struct already_child
    {
        typedef typename Expr::proto_derived_expr uncv_expr_type;
        typedef typename Generator::template result<Generator(uncv_expr_type)>::type result_type;

        result_type operator()(Expr &e) const
        {
            return Generator()(e);
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename Expr, typename Generator>
    struct already_child<Expr, Generator, true>
    {
        typedef Expr &result_type;

        result_type operator()(Expr &e) const
        {
            return e;
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, typename Generator>
    struct as_expr<T, Generator, false, false>
    {
        typedef typename term_traits<T &>::value_type value_type;
        typedef proto::expr<proto::tag::terminal, term<value_type>, 0> expr_type;
        typedef typename Generator::template result<Generator(expr_type)>::type result_type;

        result_type operator()(T &t) const
        {
            return Generator()(expr_type::make(t));
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, typename Generator>
    struct as_expr<T, Generator, false, true>
    {
        typedef typename term_traits<T &>::value_type value_type;
        typedef proto::basic_expr<proto::tag::terminal, term<value_type>, 0> expr_type;
        typedef typename Generator::template result<Generator(expr_type)>::type result_type;

        result_type operator()(T &t) const
        {
            return Generator()(expr_type::make(t));
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, typename Generator>
    struct as_expr<T, Generator, true, false>
      : already_expr<
            T
          , Generator
          , is_same<
                typename Generator::proto_base_generator
              , typename T::proto_generator::proto_base_generator
            >::value
        >
    {};

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, typename Generator>
    struct as_expr<T, Generator, true, true>
      : already_expr<
            T
          , Generator
          , is_same<
                typename Generator::proto_base_generator
              , typename T::proto_generator::proto_base_generator
            >::value
        >
    {};

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    struct as_expr<T, proto::_, false, false>
    {
        typedef typename term_traits<T &>::value_type value_type;
        typedef proto::expr<proto::tag::terminal, term<value_type>, 0> result_type;

        result_type operator()(T &t) const
        {
            return result_type::make(t);
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    struct as_expr<T, proto::_, false, true>
    {
        typedef typename term_traits<T &>::value_type value_type;
        typedef proto::basic_expr<proto::tag::terminal, term<value_type>, 0> result_type;

        result_type operator()(T &t) const
        {
            return result_type::make(t);
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    struct as_expr<T, proto::_, true, false>
      : already_expr<T, proto::_, true>
    {};

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    struct as_expr<T, proto::_, true, true>
      : already_expr<T, proto::_, true>
    {};


    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, typename Generator>
    struct as_child<T, Generator, false, false>
    {
        typedef proto::expr<proto::tag::terminal, term<T &>, 0> expr_type;
        typedef typename Generator::template result<Generator(expr_type)>::type result_type;

        result_type operator()(T &t) const
        {
            return Generator()(expr_type::make(t));
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, typename Generator>
    struct as_child<T, Generator, false, true>
    {
        typedef proto::basic_expr<proto::tag::terminal, term<T &>, 0> expr_type;
        typedef typename Generator::template result<Generator(expr_type)>::type result_type;

        result_type operator()(T &t) const
        {
            return Generator()(expr_type::make(t));
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, typename Generator>
    struct as_child<T, Generator, true, false>
      : already_child<
            T
          , Generator
          , is_same<
                typename Generator::proto_base_generator
              , typename T::proto_generator::proto_base_generator
            >::value
        >
    {};

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, typename Generator>
    struct as_child<T, Generator, true, true>
      : already_child<
            T
          , Generator
          , is_same<
                typename Generator::proto_base_generator
              , typename T::proto_generator::proto_base_generator
            >::value
        >
    {};

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    struct as_child<T, proto::_, false, false>
    {
        typedef proto::expr<proto::tag::terminal, term<T &>, 0> result_type;

        result_type operator()(T &t) const
        {
            return result_type::make(t);
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    struct as_child<T, proto::_, false, true>
    {
        typedef proto::basic_expr<proto::tag::terminal, term<T &>, 0> result_type;

        result_type operator()(T &t) const
        {
            return result_type::make(t);
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    struct as_child<T, proto::_, true, false>
      : already_child<T, proto::_, true>
    {};

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    struct as_child<T, proto::_, true, true>
      : already_child<T, proto::_, true>
    {};

}}}

#endif

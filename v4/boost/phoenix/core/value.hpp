/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_VALUE_HPP_EAN_2008_05_10
#define BOOST_PHOENIX_VALUE_HPP_EAN_2008_05_10

#include <cstddef>
#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/actor.hpp>
#include <boost/phoenix/core/reference.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost { namespace phoenix
{
    ////////////////////////////////////////////////////////////////////////////////////////////
    namespace tag
    {
        struct byval {};
    }

    ////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    struct value
      : proto::terminal<T>::type
    {
        explicit value(T const &t)
          : proto::terminal<T>::type(proto::terminal<T>::type::make(t))
        {}

        operator actor<value<T> >() const
        {
            actor<value<T> > that = {*this};
            return that;
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    actor<value<T> > const
    val(T const &t)
    {
        return value<T>(t);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, std::size_t N>
    actor<reference<T[N]> > const
    val(T (&t)[N])
    {
        return reference<T[N]>(t);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, std::size_t N>
    actor<reference<T const[N]> > const
    val(T const (&t)[N])
    {
        return reference<T const[N]>(t);
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////
    template<typename Expr>
    actor<typename proto::unary_expr<tag::byval, actor<Expr> const &>::type> const
    val(actor<Expr> const &expr)
    {
        actor<typename proto::unary_expr<tag::byval, actor<Expr> const &>::type> that = {{expr}};
        return that;
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////
    template<>
    struct extension<tag::byval>
      : proto::when<
            proto::unary_expr<tag::byval, evaluator>
          , remove_reference<evaluator(proto::_child)>(evaluator(proto::_child))
        >
    {};

}}

#endif

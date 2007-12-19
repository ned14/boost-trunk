//[ Calc3
//  Copyright 2007 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// This example enhances the arithmetic expression evaluator
// in calc2.cpp by using a proto transform to calculate the
// number of arguments an expression requires and using a
// compile-time assert to guarantee that the right number of
// arguments are actually specified.

#include <iostream>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/min_max.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/context.hpp>
#include <boost/xpressive/proto/transform.hpp>
using namespace boost;

// Will be used to define the placeholders _1 and _2
template<typename I> struct arg : I {};

using proto::_;
using namespace proto::transform;

// This grammar basically says that a calculator expression is one of:
//   - A placeholder terminal
//   - Some other terminal
//   - Some non-terminal whose children are calculator expressions
// In addition, it has transforms that say how to calculate the
// expression arity for each of the three cases.
struct CalculatorGrammar
  : proto::or_<

        // placeholders have a non-zero arity ...
        when< proto::terminal< arg<_> >, _arg >

        // Any other terminals have arity 0 ...
      , when< proto::terminal<_>, mpl::int_<0>() >

        // For any non-terminals, find the arity of the children and
        // take the maximum. This is recursive.
      , when< proto::nary_expr<_, proto::vararg<_> >
             , fold<_, mpl::int_<0>(), mpl::max<CalculatorGrammar, _state>() > >

    >
{};

// Simple wrapper for calculating a calculator expression's arity.
// It specifies mpl::int_<0> as the initial state. The visitor, which
// is not used, is mpl::void_.
template<typename Expr>
struct calculator_arity
  : boost::result_of<CalculatorGrammar(Expr, mpl::int_<0>, mpl::void_)>
{};

// For expressions in the calculator domain, operator()
// will be special; it will evaluate the expression.
struct calculator_domain;

// Define a calculator context, for evaluating arithmetic expressions
// (This is as before, in calc1.cpp and calc2.cpp)
struct calculator_context
  : proto::callable_context< calculator_context const >
{
    // The values bound to the placeholders
    double d[2];

    // The result of evaluating arithmetic expressions
    typedef double result_type;

    explicit calculator_context(double d1 = 0., double d2 = 0.)
    {
        d[0] = d1;
        d[1] = d2;
    }

    // Handle the evaluation of the placeholder terminals
    template<typename I>
    double operator()(proto::tag::terminal, arg<I>) const
    {
        return d[ I() - 1 ];
    }
};

// Wrap all calculator expressions in this type, which defines
// operator() to evaluate the expression.
template<typename Expr>
struct calculator_expression
  : proto::extends<Expr, calculator_expression<Expr>, calculator_domain>
{
    typedef
        proto::extends<Expr, calculator_expression<Expr>, calculator_domain>
    base_type;

    explicit calculator_expression(Expr const &expr = Expr())
      : base_type(expr)
    {}

    using base_type::operator=;

    // Override operator() to evaluate the expression
    double operator()() const
    {
        // Assert that the expression has arity 0
        BOOST_MPL_ASSERT_RELATION(0, ==, calculator_arity<Expr>::type::value);
        calculator_context const ctx;
        return proto::eval(*this, ctx);
    }

    double operator()(double d1) const
    {
        // Assert that the expression has arity 1
        BOOST_MPL_ASSERT_RELATION(1, ==, calculator_arity<Expr>::type::value);
        calculator_context const ctx(d1);
        return proto::eval(*this, ctx);
    }

    double operator()(double d1, double d2) const
    {
        // Assert that the expression has arity 2
        BOOST_MPL_ASSERT_RELATION(2, ==, calculator_arity<Expr>::type::value);
        calculator_context const ctx(d1, d2);
        return proto::eval(*this, ctx);
    }
};

// Tell proto how to generate expressions in the calculator_domain
struct calculator_domain
  : proto::domain<proto::generator<calculator_expression> >
{};

// Define some placeholders (notice they're wrapped in calculator_expression<>)
calculator_expression<proto::terminal< arg< mpl::int_<1> > >::type> const _1;
calculator_expression<proto::terminal< arg< mpl::int_<2> > >::type> const _2;

// Now, our arithmetic expressions are immediately executable function objects:
int main()
{
    // Displays "5"
    std::cout << (_1 + 2.0)( 3.0 ) << std::endl;

    // Displays "6"
    std::cout << ( _1 * _2 )( 3.0, 2.0 ) << std::endl;

    // Displays "0.5"
    std::cout << ( (_1 - _2) / _2 )( 3.0, 2.0 ) << std::endl;

    // This won't compile because the arity of the
    // expression doesn't match the number of arguments
    // ( (_1 - _2) / _2 )( 3.0 );

    return 0;
}
//]

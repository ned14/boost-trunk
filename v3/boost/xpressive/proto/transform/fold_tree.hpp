///////////////////////////////////////////////////////////////////////////////
/// \file fold.hpp
/// Contains definition of the fold_tree<> and reverse_fold_tree<> transforms.
//
//  Copyright 2007 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_TRANSFORM_FOLD_TREE_HPP_EAN_11_05_2007
#define BOOST_PROTO_TRANSFORM_FOLD_TREE_HPP_EAN_11_05_2007

#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits.hpp>
#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/traits.hpp>
#include <boost/xpressive/proto/transform/fold.hpp>
#include <boost/xpressive/proto/detail/define.hpp>

namespace boost { namespace proto
{

    namespace transform
    {

        namespace detail
        {

            template<typename Grammar, typename Fun>
            struct fold_tree_
              : or_<
                    when<Grammar, fold<_, _state, fold_tree_<Grammar, Fun> > >
                  , when<_, Fun>
                >
            {};

            template<typename Grammar, typename Fun>
            struct reverse_fold_tree_
              : or_<
                    when<Grammar, reverse_fold<_, _state, reverse_fold_tree_<Grammar, Fun> > >
                  , when<_, Fun>
                >
            {};
        }

        template<typename Sequence, typename State0, typename Fun>
        struct fold_tree
          : callable
        {
            template<typename Sig>
            struct result;

            template<typename This, typename Expr, typename State, typename Visitor>
            struct result<This(Expr, State, Visitor)>
            {
                typedef fold<
                    Sequence
                  , State0
                  , detail::fold_tree_<
                        nary_expr<UNREF(Expr)::proto_tag, vararg<_> >
                      , Fun
                    >
                > impl;

                typedef typename boost::result_of<impl(Expr, State, Visitor)>::type type;
            };

            template<typename Expr, typename State, typename Visitor>
            typename result<fold_tree(Expr const &, State const &, Visitor &)>::type
            operator()(Expr const &expr, State const &state, Visitor &visitor) const
            {
                typedef typename result<fold_tree(Expr const &, State const &, Visitor &)>::impl impl;
                return impl()(expr, state, visitor);
            }
        };

        template<typename Sequence, typename State0, typename Fun>
        struct reverse_fold_tree
          : callable
        {
            template<typename Sig>
            struct result;

            template<typename This, typename Expr, typename State, typename Visitor>
            struct result<This(Expr, State, Visitor)>
            {
                typedef reverse_fold<
                    Sequence
                  , State0
                  , detail::reverse_fold_tree_<
                        nary_expr<UNREF(Expr)::proto_tag, vararg<_> >
                      , Fun
                    >
                > impl;

                typedef typename boost::result_of<impl(Expr, State, Visitor)>::type type;
            };

            template<typename Expr, typename State, typename Visitor>
            typename result<reverse_fold_tree(Expr const &, State const &, Visitor &)>::type
            operator()(Expr const &expr, State const &state, Visitor &visitor) const
            {
                typedef typename result<reverse_fold_tree(Expr const &, State const &, Visitor &)>::impl impl;
                return impl()(expr, state, visitor);
            }
        };
    }

    template<typename Sequence, typename State0, typename Fun>
    struct is_callable<transform::fold_tree<Sequence, State0, Fun> >
      : mpl::true_
    {};

    template<typename Sequence, typename State0, typename Fun>
    struct is_callable<transform::reverse_fold_tree<Sequence, State0, Fun> >
      : mpl::true_
    {};
}}

#include <boost/xpressive/proto/detail/undef.hpp>

#endif

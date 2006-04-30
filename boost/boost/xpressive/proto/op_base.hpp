///////////////////////////////////////////////////////////////////////////////
/// \file op_base.hpp
/// Contains definitions of unary_op\<\>, binary_op\<\> and nary_op\<\>,
/// as well as the is_op\<\> and the make_op() helper function.
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_OP_BASE_HPP_EAN_04_01_2005
#define BOOST_PROTO_OP_BASE_HPP_EAN_04_01_2005

#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/spirit/fusion/sequence/tuple.hpp>
#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/arg_traits.hpp>
#include <boost/spirit/fusion/sequence/detail/sequence_base.hpp>

namespace boost { namespace proto
{

    ///////////////////////////////////////////////////////////////////////////////
    // op_root
    struct op_root : fusion::sequence_root
    {
    };

    ///////////////////////////////////////////////////////////////////////////////
    // is_proxy
    template<typename T>
    struct is_proxy
      : mpl::false_
    {
    };

    template<typename Node, typename Param>
    struct is_proxy<op_proxy<Node, Param> >
      : mpl::true_
    {
    };

    ///////////////////////////////////////////////////////////////////////////////
    // is_op
    template<typename T>
    struct is_op
      : mpl::or_<is_proxy<T>, is_base_and_derived<op_root, T> >
    {
    };

    ///////////////////////////////////////////////////////////////////////////////
    // as_op
    template<typename Node>
    struct as_op<Node, true>
    {
        typedef typename Node::type type;

        static typename Node::const_reference make(Node const &node)
        {
            return node.cast();
        }
    };

    template<typename T>
    struct as_op<T, false>
    {
        typedef unary_op<T, noop_tag> type;

        static type const make(T const &t)
        {
            return noop(t);
        }
    };

// These operators must be members.
#define BOOST_PROTO_DEFINE_MEMBER_OPS()                                                         \
    template<typename Arg>                                                                      \
    binary_op<Node, typename as_op<Arg>::type, assign_tag> const                                  \
    operator =(Arg const &arg) const                                                            \
    {                                                                                           \
        return make_op<assign_tag>(this->cast(), as_op<Arg>::make(arg));                        \
    }                                                                                           \
    template<typename Arg>                                                                      \
    binary_op<Node, typename as_op<Arg>::type, subscript_tag> const                               \
    operator [](Arg const &arg) const                                                           \
    {                                                                                           \
        return make_op<subscript_tag>(this->cast(), as_op<Arg>::make(arg));                     \
    }                                                                                           \
    nary_op<Node> operator ()() const                                                             \
    {                                                                                           \
        return nary_op<Node>(this->cast());                                                       \
    }                                                                                           \
    BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(BOOST_PROTO_MAX_ARITY), BOOST_PROTO_FUN_OP, _)

#define BOOST_PROTO_FUN_OP(z, n, _)                                                             \
    template<BOOST_PP_ENUM_PARAMS_Z(z, n, typename A)>                                          \
    nary_op<Node BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, A)>                                        \
    operator ()(BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, A, const &a)) const                         \
    {                                                                                           \
        return nary_op<Node BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, A)>                             \
            (this->cast() BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, a));                            \
    }

    template<typename Tag>
    struct tag
    {};

    ///////////////////////////////////////////////////////////////////////////////
    // op_base
    template<typename Node>
    struct op_base : op_root
    {
        typedef Node type;
        typedef type const &const_reference;

        Node &cast()
        {
            return *static_cast<Node *>(this);
        }

        Node const &cast() const
        {
            return *static_cast<Node const *>(this);
        }

        BOOST_PROTO_DEFINE_MEMBER_OPS()
    };

    ///////////////////////////////////////////////////////////////////////////////
    // unary_op
    template<typename Arg, typename Tag>
    struct unary_op : op_base<unary_op<Arg, Tag> >
    {
        typedef typename value_type<Arg>::type arg_type;
        typedef Tag tag_type;
        typedef tag<Tag> tag; // for Fusion-1 compatibility

        arg_type arg;

        unary_op()
          : arg()
        {}

        explicit unary_op(typename call_traits<Arg>::param_type arg_)
          : arg(arg_)
        {}

        using op_base<unary_op>::operator =;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // binary_op
    template<typename Left, typename Right, typename Tag>
    struct binary_op : op_base<binary_op<Left, Right, Tag> >
    {
        typedef typename value_type<Left>::type left_type;
        typedef typename value_type<Right>::type right_type;
        typedef Tag tag_type;
        typedef tag<Tag> tag; // for Fusion-1 compatibility

        left_type left;
        right_type right;

        binary_op()
          : left()
          , right()
        {}

        binary_op(
            typename call_traits<Left>::param_type left_
          , typename call_traits<Right>::param_type right_
        )
          : left(left_)
          , right(right_)
        {}

        using op_base<binary_op>::operator =;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // nary_op
    template<typename Fun, BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_ARITY, typename A)>
    struct nary_op
      : op_base<nary_op<Fun, BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_ARITY, A)> >
    {
        typedef function_tag tag_type;
        typedef tag<function_tag> tag; // for Fusion-1 compatibility
        typedef Fun functor_type;
        typedef fusion::tuple<
            BOOST_PP_ENUM_BINARY_PARAMS(
                BOOST_PROTO_MAX_ARITY, typename value_type<A, >::type BOOST_PP_INTERCEPT)
        > args_type;

        functor_type functor;
        args_type args;

        nary_op()
          : functor()
          , args()
        {}

    #define BOOST_PROTO_NARY_OP_CTOR(z, n, _)                                                   \
        nary_op(                                                                                \
            typename call_traits<Fun>::param_type fun                                           \
            BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(z, n, typename call_traits<A, >::param_type a))\
          : functor(fun)                                                                        \
          , args(BOOST_PP_ENUM_PARAMS_Z(z, n, a))                                               \
        {}

        BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_PROTO_MAX_ARITY), BOOST_PROTO_NARY_OP_CTOR, _)

    #undef BOOST_PROTO_NARY_OP_CTOR

        using op_base<nary_op>::operator =;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // op_proxy
    template<typename Node, typename Param>
    struct op_proxy
    {
        typedef Node type;
        typedef type const const_reference;
        Param param_;

        Node const cast() const
        {
            return Node(this->param_);
        }

        operator Node const() const
        {
            return this->cast();
        }

        BOOST_PROTO_DEFINE_MEMBER_OPS()
    };

    template<typename Node>
    struct op_proxy<Node, void>
    {
        typedef Node type;
        typedef type const const_reference;

        Node const cast() const
        {
            return Node();
        }

        operator Node const() const
        {
            return this->cast();
        }

        BOOST_PROTO_DEFINE_MEMBER_OPS()
    };

    ///////////////////////////////////////////////////////////////////////////////
    // make_op
    template<typename Node, typename Arg>
    unary_op<Arg, Node> const
    make_op(Arg const &arg)
    {
        return unary_op<Arg, Node>(arg);
    }

    ///////////////////////////////////////////////////////////////////////////////
    // make_op
    template<typename Node, typename Left, typename Right>
    binary_op<Left, Right, Node> const
    make_op(Left const &left, Right const &right)
    {
        return binary_op<Left, Right, Node>(left, right);
    }

}}

#endif

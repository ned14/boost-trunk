///////////////////////////////////////////////////////////////////////////////
// noop_compiler.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_NOOP_COMPILER_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_NOOP_COMPILER_HPP_EAN_10_04_2005

#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/static/productions/independent_compiler.hpp>
#include <boost/xpressive/detail/static/productions/domain_tags.hpp>

namespace boost { namespace xpressive { namespace detail
{

    ///////////////////////////////////////////////////////////////////////////////
    // regex compiler productions
    struct noop_compiler
    {
        ///////////////////////////////////////////////////////////////////////////////
        // transformation that happens to leaf nodes in the parse tree
        template<typename OpT, typename StateT, typename VisitorT>
        struct apply
        {
            typedef typename as_matcher_type<typename proto::arg_type<OpT>::type>::type matcher1;
            typedef typename VisitorT::BOOST_NESTED_TEMPLATE apply<matcher1>::type matcher2;
            typedef static_xpression<matcher2, StateT> type;
        };

        template<typename OpT, typename StateT, typename VisitorT>
        static typename apply<OpT, StateT, VisitorT>::type
        call(OpT const &op, StateT const &state, VisitorT &visitor)
        {
            typedef typename proto::arg_type<OpT>::type arg_type;
            return make_static_xpression(visitor.call(as_matcher_type<arg_type>::call(proto::arg(op))), state);
        }
    };

}}}

namespace boost { namespace proto
{

    // production for terminals in sequence
    template<>
    struct compiler<noop_tag, xpressive::detail::seq_tag>
      : xpressive::detail::noop_compiler
    {
    };

}}

#endif

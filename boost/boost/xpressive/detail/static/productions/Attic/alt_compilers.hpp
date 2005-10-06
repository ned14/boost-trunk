///////////////////////////////////////////////////////////////////////////////
// alt_compilers.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_ALT_COMPILERS_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_ALT_COMPILERS_HPP_EAN_10_04_2005

#include <boost/spirit/fusion/sequence/cons.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/compiler/fold.hpp>
#include <boost/xpressive/proto/compiler/branch.hpp>
#include <boost/xpressive/detail/utility/dont_care.hpp>
#include <boost/xpressive/detail/static/productions/domain_tags.hpp>

namespace boost { namespace xpressive { namespace detail
{

    ///////////////////////////////////////////////////////////////////////////////
    // alt_branch
    //   Describes how to construct an alternate xpression
    struct alt_branch
    {
        typedef boost::fusion::nil state_type;

        template<typename OpT, typename StateT, typename VisitorT>
        struct apply
        {
            typedef static_xpression
            <
                alternate_matcher<alternates_list<OpT>, typename VisitorT::traits_type>
              , StateT
            > type;
        };

        template<typename OpT, typename StateT, typename VisitorT>
        static typename apply<OpT, StateT, VisitorT>::type
        call(OpT const &op, StateT const &state, VisitorT &visitor)
        {
            typedef alternate_matcher<alternates_list<OpT>, typename VisitorT::traits_type> alt_matcher;
            return make_static_xpression(alt_matcher(op), state);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // alt_list_branch
    struct alt_list_branch
    {
        typedef alternate_end_xpression state_type;

        template<typename OpT, typename StateT, typename>
        struct apply
        {
            typedef boost::fusion::cons<OpT, StateT> type;
        };

        template<typename OpT, typename StateT>
        static boost::fusion::cons<OpT, StateT>
        call(OpT const &op, StateT const &state, dont_care)
        {
            return boost::fusion::make_cons(op, state);
        }
    };

}}}

namespace boost { namespace proto
{
    // production for alternates in sequence
    template<>
    struct compiler<bitor_tag, xpressive::detail::seq_tag>
      : branch_compiler<xpressive::detail::alt_branch, xpressive::detail::alt_tag>
    {
    };

    // handle alternates with the alt branch compiler
    template<typename OpTagT>
    struct compiler<OpTagT, xpressive::detail::alt_tag>
      : branch_compiler<xpressive::detail::alt_list_branch, xpressive::detail::seq_tag>
    {
    };

    // production for alternates in alternate
    template<>
    struct compiler<bitor_tag, xpressive::detail::alt_tag>
      : fold_compiler<bitor_tag, xpressive::detail::alt_tag>
    {
    };

}}

#endif

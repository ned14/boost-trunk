///////////////////////////////////////////////////////////////////////////////
// quant_transforms.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_QUANT_TRANSFORMS_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_QUANT_TRANSFORMS_HPP_EAN_10_04_2005

#include <limits.h>
#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/not_equal_to.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/static/width_of.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/detail/utility/dont_care.hpp>
#include <boost/xpressive/detail/static/productions/quant_traits.hpp>
#include <boost/xpressive/detail/static/productions/marker_transform.hpp>

namespace boost { namespace xpressive { namespace detail
{

    ///////////////////////////////////////////////////////////////////////////////
    // plus_no_mark_transform
    //   Unary plus becomes a quantifier by wrapping arg in begin/end quantifiers
    template<bool Greedy = true, uint_t Min = 1, uint_t Max = UINT_MAX-1>
    struct plus_no_mark_transform
    {
        template<typename Op, typename, typename>
        struct apply
        {
            BOOST_MPL_ASSERT((mpl::not_equal_to<mpl::size_t<0>, width_of<typename proto::arg_type<Op>::type> >));

            typedef proto::binary_op
            <
                proto::binary_op
                <
                    proto::unary_op<repeat_begin_matcher, proto::noop_tag>
                  , typename proto::arg_type<Op>::type // skip the "plus" node
                  , proto::right_shift_tag
                >
              , proto::unary_op<repeat_end_matcher<Greedy>, proto::noop_tag>
              , proto::right_shift_tag
            > type;
        };

        template<typename Op, typename State, typename Visitor>
        static typename apply<Op, State, Visitor>::type
        call(Op const &op, State const &, Visitor &, int mark_number = -1, uint_t min = Min, uint_t max = Max)
        {
            return proto::noop(repeat_begin_matcher(mark_number))
                >> proto::arg(op)
                >> proto::noop(repeat_end_matcher<Greedy>(mark_number, min, max));
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // plus_mark_transform
    //   compose the quant and mark transforms
    template<bool Greedy = true, uint_t Min = 1, uint_t Max = UINT_MAX-1>
    struct plus_mark_transform
    {
        template<typename Op, typename State, typename Visitor>
        struct apply
        {
            BOOST_MPL_ASSERT((mpl::not_equal_to<mpl::size_t<0>, width_of<typename proto::arg_type<Op>::type> >));

            typedef typename marker_transform::apply
            <
                typename proto::arg_type<Op>::type
              , State
              , Visitor
            >::type marker_type;

            typedef typename plus_no_mark_transform<Greedy, Min, Max>::BOOST_NESTED_TEMPLATE apply
            <
                proto::unary_op<marker_type, typename proto::tag_type<Op>::type>
              , State
              , Visitor
            >::type type;
        };

        template<typename Op, typename State, typename Visitor>
        static typename apply<Op, State, Visitor>::type
        call(Op const &op, State const &state, Visitor &visitor, int mark_number = -1, uint_t min = Min, uint_t max = Max)
        {
            return plus_no_mark_transform<Greedy, Min, Max>::call
            (
                proto::make_op<typename proto::tag_type<Op>::type>
                (
                    marker_transform::call(proto::arg(op), state, visitor, mark_number)
                )
              , state
              , visitor
              , mark_number
              , min
              , max
            );
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // optional_transform_impl
    //   An optional expression gets the following transformation:
    template<bool Greedy, typename Epsilon>
    struct optional_transform_impl
    {
        template<typename Op, typename, typename>
        struct apply
        {
            BOOST_MPL_ASSERT((mpl::not_equal_to<mpl::size_t<0>, width_of<typename proto::arg_type<Op>::type> >));

            typedef proto::binary_op
            <
                typename proto::arg_type<Op>::type
              , proto::unary_op<Epsilon, proto::noop_tag>
              , proto::bitor_tag
            > type;
        };

        template<typename Op, typename State, typename Visitor>
        static typename apply<Op, State, Visitor>::type
        call(Op const &op, State const &, Visitor &, Epsilon eps = Epsilon())
        {
            return proto::arg(op) | proto::noop(eps);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // non-greedy optional transform
    template<typename Epsilon>
    struct optional_transform_impl<false, Epsilon>
    {
        template<typename Op, typename, typename>
        struct apply
        {
            BOOST_MPL_ASSERT((mpl::not_equal_to<mpl::size_t<0>, width_of<typename proto::arg_type<Op>::type> >));

            typedef proto::binary_op
            <
                proto::unary_op<Epsilon, proto::noop_tag>
              , typename proto::arg_type<Op>::type
              , proto::bitor_tag
            > type;
        };

        template<typename Op, typename State, typename Visitor>
        static typename apply<Op, State, Visitor>::type
        call(Op const &op, State const &, Visitor &, Epsilon eps = Epsilon())
        {
            return proto::noop(eps) | proto::arg(op);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // optional_transform
    //   An optional expression gets the following transformation:
    template<bool Greedy>
    struct optional_transform
    {
        template<typename Op, typename State, typename Visitor>
        struct apply
        {
            // If Op is of the form !(s1= ...), then the epsilon matcher must
            // zero out the s1 sub-match.
            typedef typename mpl::if_
            <
                is_marker<typename proto::arg_type<Op>::type>
              , epsilon_mark_matcher
              , epsilon_matcher
            >::type epsilon_type;

            typedef optional_transform_impl<Greedy, epsilon_type> transform;
            typedef typename transform::BOOST_NESTED_TEMPLATE apply<Op, State, Visitor>::type type;
        };

        template<typename Op, typename State, typename Visitor>
        static typename apply<Op, State, Visitor>::type
        call(Op const &op, State const &state, Visitor &visitor)
        {
            typedef typename apply<Op, State, Visitor>::epsilon_type epsilon_type;
            typedef typename apply<Op, State, Visitor>::transform transform;
            typedef is_marker<typename proto::arg_type<Op>::type> is_marker;
            return transform::call(op, state, visitor, make_eps(proto::arg(op), is_marker()));
        }

    private:
        template<typename Op>
        static epsilon_mark_matcher make_eps(Op const &op, mpl::true_)
        {
            return epsilon_mark_matcher(proto::arg(proto::left(op)).mark_number_);
        }

        static epsilon_matcher make_eps(dont_care, mpl::false_)
        {
            return epsilon_matcher();
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // simple_repeat_branch
    template<bool Greedy = true, uint_t Min = 0, uint_t Max = UINT_MAX-1>
    struct simple_repeat_branch
    {
        typedef true_xpression state_type;

        template<typename Op, typename State, typename>
        struct apply
        {
            BOOST_MPL_ASSERT((mpl::not_equal_to<mpl::size_t<0>, width_of<Op> >));
            typedef static_xpression<simple_repeat_matcher<Op, Greedy>, State> type;
        };

        template<typename Op, typename State, typename Visitor>
        static typename apply<Op, State, Visitor>::type
        call(Op const &op, State const &state, Visitor &, uint_t min = Min, uint_t max = Max)
        {
            return make_static_xpression(simple_repeat_matcher<Op, Greedy>(op, min, max), state);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // plus_transform
    //   Optimization: don't insert a hidden mark if we already have a visible one
    template<bool Greedy = true, uint_t Min = 1, uint_t Max = UINT_MAX-1>
    struct plus_transform
    {
        template<typename Op, typename State, typename Visitor>
        struct apply
        {
            typedef typename mpl::if_
            <
                is_marker<typename proto::arg_type<Op>::type>
              , plus_no_mark_transform<Greedy, Min, Max>
              , plus_mark_transform<Greedy, Min, Max>
            >::type transform;

            typedef typename transform::BOOST_NESTED_TEMPLATE apply<Op, State, Visitor>::type type;
        };

        template<typename Op, typename State, typename Visitor>
        static typename apply<Op, State, Visitor>::type
        call(Op const &op, State const &state, Visitor &visitor, uint_t min = Min, uint_t max = Max)
        {
            int mark_nbr = mark_number(proto::arg(op), visitor);
            return apply<Op, State, Visitor>::transform::call(op, state, visitor, mark_nbr, min, max);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // star_transform
    template<bool Greedy = true, uint_t Max = UINT_MAX-1>
    struct star_transform
    {
        template<typename Op, typename State, typename Visitor>
        struct apply
        {
            typedef typename plus_transform<Greedy, 1, Max>::BOOST_NESTED_TEMPLATE apply
            <
                Op
              , State
              , Visitor
            >::type plus_type;

            typedef optional_transform_impl<Greedy, epsilon_mark_matcher> optional_transform;
            typedef typename optional_transform::BOOST_NESTED_TEMPLATE apply
            <
                proto::unary_op<plus_type, proto::unary_plus_tag>
              , State
              , Visitor
            >::type type;
        };

        template<typename Op, typename State, typename Visitor>
        static typename apply<Op, State, Visitor>::type
        call(Op const &op, State const &state, Visitor &visitor, uint_t max = Max)
        {
            typedef typename apply<Op, State, Visitor>::plus_type plus_type;
            typedef typename apply<Op, State, Visitor>::optional_transform optional_transform;
            plus_type plus = plus_transform<Greedy, 1, Max>::call(op, state, visitor, 1, max);
            int mark_nbr = proto::arg(proto::left(proto::left(plus))).mark_number_;
            return optional_transform::call(+plus, state, visitor, epsilon_mark_matcher(mark_nbr));
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // epsilon_transform
    struct epsilon_transform
    {
        template<typename, typename, typename>
        struct apply
        {
            typedef proto::unary_op<epsilon_matcher, proto::noop_tag> type;
        };

        static proto::unary_op<epsilon_matcher, proto::noop_tag> 
        call(dont_care, dont_care, dont_care)
        {
            return proto::noop(epsilon_matcher());
        }
    };

}}}

#endif

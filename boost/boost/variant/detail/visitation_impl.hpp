//-----------------------------------------------------------------------------
// boost variant/detail/visitation_impl.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2003
// Eric Friedman
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_VARIANT_DETAIL_VISITATION_IMPL_HPP
#define BOOST_VARIANT_DETAIL_VISITATION_IMPL_HPP

#include "boost/config.hpp"
#include "boost/mpl/aux_/deref_wknd.hpp"

#include "boost/variant/detail/cast_storage.hpp"
#include "boost/variant/detail/forced_return.hpp"
#include "boost/variant/detail/generic_result_type.hpp"

#include "boost/assert.hpp"
#include "boost/mpl/apply_if.hpp"
#include "boost/mpl/bool.hpp"
#include "boost/mpl/identity.hpp"
#include "boost/mpl/int.hpp"
#include "boost/mpl/next.hpp"
#include "boost/preprocessor/cat.hpp"
#include "boost/preprocessor/inc.hpp"
#include "boost/preprocessor/repeat.hpp"
#include "boost/type_traits.hpp"


///////////////////////////////////////////////////////////////////////////////
// BOOST_VARIANT_VISITATION_UNROLLING_LIMIT
//
// Unrolls variant's visitation mechanism to reduce template instantiation
// and potentially increase runtime performance. (TODO: Investigate further.)
//
#if !defined(BOOST_VARIANT_VISITATION_UNROLLING_LIMIT)
#   define BOOST_VARIANT_VISITATION_UNROLLING_LIMIT   \
        BOOST_VARIANT_LIMIT_TYPES
#endif

namespace boost {
namespace detail { namespace variant {

///////////////////////////////////////////////////////////////////////////////
// (detail) class visitation_impl
//
// Tag type indicates when visitation_impl is unrolled.
//
struct apply_visitor_unrolled {};

///////////////////////////////////////////////////////////////////////////////
// (detail) class template visitation_impl_step
//
// "Never ending" iterator range facilitates visitation_impl unrolling.
//

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template <typename Iter, typename LastIter>
struct visitation_impl_step
{
    typedef typename BOOST_MPL_AUX_DEREF_WNKD(Iter) type;

    typedef typename mpl::next<Iter>::type next_iter;
    typedef visitation_impl_step<
          next_iter, LastIter
        > next;
};

template <typename LastIter>
struct visitation_impl_step< LastIter,LastIter >
{
    typedef apply_visitor_unrolled type;
    typedef visitation_impl_step next;
};

#else // defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template <typename Iter, typename LastIter>
struct visitation_impl_step
{
    typedef typename mpl::apply_if<
          is_same<Iter, LastIter>
        , mpl::identity<apply_visitor_unrolled>
        , Iter
        >::type type;

    typedef typename mpl::apply_if<
          is_same<type, apply_visitor_unrolled> //is_same<Iter, LastIter>
        , mpl::identity<LastIter>
        , mpl::next<Iter>
        >::type next_iter;

    typedef visitation_impl_step<
          next_iter, LastIter
        > next;
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION workaround

///////////////////////////////////////////////////////////////////////////////
// (detail) function template visitation_impl_invoke
//
// Invokes the given visitor on the specified type in the given storage.
//

template <typename Visitor, typename VoidPtrCV, typename T>
inline
    BOOST_VARIANT_AUX_GENERIC_RESULT_TYPE(typename Visitor::result_type)
visitation_impl_invoke(Visitor& visitor, VoidPtrCV operand, T*, int)
{
    return visitor( cast_storage<T>(operand) );
}

template <typename Visitor, typename VoidPtrCV>
inline
    BOOST_VARIANT_AUX_GENERIC_RESULT_TYPE(typename Visitor::result_type)
visitation_impl_invoke(Visitor&, VoidPtrCV, apply_visitor_unrolled*, long)
{
    // should never be here at runtime:
    BOOST_ASSERT(false);
    typedef typename Visitor::result_type result_type;
    return ::boost::detail::variant::forced_return< result_type >();
}

///////////////////////////////////////////////////////////////////////////////
// (detail) function template visitation_impl
//
// Invokes the given visitor on the type in the given variant storage.
//

template <
      typename W, typename S
    , typename Visitor, typename VPCV
    >
inline
    BOOST_VARIANT_AUX_GENERIC_RESULT_TYPE(typename Visitor::result_type)
visitation_impl(
      const int, Visitor&, VPCV
    , mpl::true_ // is_apply_visitor_unrolled
    , W* = 0, S* = 0
    )
{
    // should never be here at runtime:
    BOOST_ASSERT(false);
    typedef typename Visitor::result_type result_type;
    return ::boost::detail::variant::forced_return< result_type >();
}

template <
      typename Which, typename step0
    , typename Visitor, typename VoidPtrCV
    >
inline
    BOOST_VARIANT_AUX_GENERIC_RESULT_TYPE(typename Visitor::result_type)
visitation_impl(
      const int var_which, Visitor& visitor, VoidPtrCV storage
    , mpl::false_ // is_apply_visitor_unrolled
    , Which* = 0, step0* = 0
    )
{
    // Typedef apply_visitor_unrolled steps and associated types...
#   define BOOST_VARIANT_AUX_APPLY_VISITOR_STEP_TYPEDEF(z, N, _)    \
    typedef typename BOOST_PP_CAT(step,N)::type BOOST_PP_CAT(T,N);  \
    typedef typename BOOST_PP_CAT(step,N)::next                     \
        BOOST_PP_CAT(step, BOOST_PP_INC(N));                        \
    /**/

    BOOST_PP_REPEAT(
          BOOST_VARIANT_VISITATION_UNROLLING_LIMIT
        , BOOST_VARIANT_AUX_APPLY_VISITOR_STEP_TYPEDEF
        , _
        )

#   undef BOOST_VARIANT_AUX_APPLY_VISITOR_STEP_TYPEDEF

    // ...switch on the target which-index value...
    switch (var_which)
    {

    // ...applying the appropriate case:
#   define BOOST_VARIANT_AUX_APPLY_VISITOR_STEP_CASE(z, N, _)           \
    case (Which::value + (N)):                                          \
        return visitation_impl_invoke(                               \
              visitor, storage, static_cast<BOOST_PP_CAT(T,N)*>(0), 1L  \
            );                                                          \
    /**/

    BOOST_PP_REPEAT(
          BOOST_VARIANT_VISITATION_UNROLLING_LIMIT
        , BOOST_VARIANT_AUX_APPLY_VISITOR_STEP_CASE
        , _
        )

#   undef BOOST_VARIANT_AUX_APPLY_VISITOR_STEP_CASE

    }

    // If not handled in this iteration, continue unrolling:
    typedef mpl::int_<
          Which::value + (BOOST_VARIANT_VISITATION_UNROLLING_LIMIT)
        > next_which;

    typedef BOOST_PP_CAT(step, BOOST_VARIANT_VISITATION_UNROLLING_LIMIT)
        next_step;

    typedef typename next_step::type next_type;
    typedef typename is_same< next_type,apply_visitor_unrolled >::type
        is_apply_visitor_unrolled;

    return visitation_impl(
          var_which, visitor, storage
        , is_apply_visitor_unrolled()
        , static_cast<next_which*>(0), static_cast<next_step*>(0)
        );
}

}} // namespace detail::variant
} // namespace boost

#endif // BOOST_VARIANT_DETAIL_VISITATION_IMPL_HPP

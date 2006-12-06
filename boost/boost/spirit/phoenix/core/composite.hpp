/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef PHOENIX_CORE_COMPOSITE_HPP
#define PHOENIX_CORE_COMPOSITE_HPP

#include <boost/spirit/phoenix/core/actor.hpp>
#include <boost/spirit/phoenix/core/is_actor.hpp>
#include <boost/fusion/sequence/container/vector.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/intrinsic/mpl.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/or.hpp>

#if !defined(PHOENIX_COMPOSITE_LIMIT)
# define PHOENIX_COMPOSITE_LIMIT PHOENIX_LIMIT
#endif

namespace boost { namespace phoenix
{
    namespace detail
    {
        template <int N>
        struct composite_eval;
        
        struct compute_no_nullary
        {
            template <typename State, typename T>
            struct apply
            {
                typedef typename 
                    mpl::or_<typename T::no_nullary, State>::type
                type;
            };
        };
    }

    template <typename EvalPolicy, typename EvalTuple>
    struct composite
    {
        typedef EvalTuple eval_tuple_type;
        typedef composite<EvalPolicy, EvalTuple> self_type;
        typedef EvalPolicy eval_policy_type;
        
        typedef typename
            mpl::fold<
                EvalTuple
              , mpl::false_
              , detail::compute_no_nullary
            >::type
        no_nullary;

        template <typename Env>
        struct result
        {
            typedef
                typename detail::composite_eval<
                    fusion::result_of::size<eval_tuple_type>::value>::
                template result<self_type, Env>::type
            type;
        };

        composite()
            : eval_tuple() {}

        composite(eval_tuple_type const& eval_tuple)
            : eval_tuple(eval_tuple) {}

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1400)
        template <typename U0>
        composite(U0& _0)
            : eval_tuple(ctor_helper(_0, is_base_of<composite, U0>())) {}
#else
        template <typename U0>
        composite(U0& _0)
            : eval_tuple(_0) {}
#endif

        template <typename U0, typename U1>
        composite(U0& _0, U1& _1)
            : eval_tuple(_0, _1) {}

        template <typename Env>
        typename result<Env>::type
        eval(Env const& env) const
        {
            typedef typename result<Env>::type return_type;
            return detail::
                composite_eval<fusion::result_of::size<eval_tuple_type>::value>::template
                    call<return_type>(*this, env);
        }

        //  Bring in the rest of the constructors
        #include <boost/spirit/phoenix/core/detail/composite.hpp>
        
        EvalTuple eval_tuple;

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1400)
        static EvalTuple const& 
        ctor_helper(composite const& rhs, mpl::true_)
        {
            return rhs.eval_tuple;
        }

        template <typename T>
        static T const& 
        ctor_helper(T const& rhs, mpl::false_)
        {
            return rhs;
        }
#endif
    };

    //  Bring in the detail::composite_eval<0..N> definitions
    #include <boost/spirit/phoenix/core/detail/composite_eval.hpp>
}}

#endif

/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_AS_SET_0932005_1341)
#define FUSION_AS_SET_0932005_1341

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/fusion/container/set/set.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <int size>
    struct as_set;

    template <>
    struct as_set<0>
    {
        template <typename Iterator>
        struct apply
        {
            typedef set<> type;
        };

        template <typename Iterator>
        static typename apply<Iterator>::type
        call(Iterator)
        {
            return set<>();
        }
    };

#define BOOST_FUSION_NEXT_ITERATOR(z, n, data)                                  \
    typedef typename fusion::result_of::next<BOOST_PP_CAT(I, n)>::type          \
        BOOST_PP_CAT(I, BOOST_PP_INC(n));

#define BOOST_FUSION_NEXT_CALL_ITERATOR(z, n, data)                             \
    typename gen::BOOST_PP_CAT(I, BOOST_PP_INC(n))                              \
        BOOST_PP_CAT(i, BOOST_PP_INC(n)) = fusion::next(BOOST_PP_CAT(i, n));

#define BOOST_FUSION_VALUE_OF_ITERATOR(z, n, data)                              \
    typedef typename fusion::result_of::value_of<BOOST_PP_CAT(I, n)>::type      \
        BOOST_PP_CAT(T, n);

#define BOOST_PP_FILENAME_1 <boost/fusion/container/set/detail/as_set.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_SET_SIZE)
#include BOOST_PP_ITERATE()

#undef BOOST_FUSION_NEXT_ITERATOR
#undef BOOST_FUSION_NEXT_CALL_ITERATOR
#undef BOOST_FUSION_VALUE_OF_ITERATOR

}}}

#endif
#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////

#define N BOOST_PP_ITERATION()

    template <>
    struct as_set<N>
    {
        template <typename I0>
        struct apply
        {
            BOOST_PP_REPEAT(N, BOOST_FUSION_NEXT_ITERATOR, _)
            BOOST_PP_REPEAT(N, BOOST_FUSION_VALUE_OF_ITERATOR, _)
            typedef set<BOOST_PP_ENUM_PARAMS(N, T)> type;
        };

        template <typename Iterator>
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            BOOST_PP_REPEAT(BOOST_PP_DEC(N), BOOST_FUSION_NEXT_CALL_ITERATOR, _)
            return result(BOOST_PP_ENUM_PARAMS(N, *i));
        }
    };

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


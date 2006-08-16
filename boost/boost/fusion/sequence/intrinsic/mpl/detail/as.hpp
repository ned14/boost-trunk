/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_AS_10022005_1442)
#define FUSION_AS_10022005_1442

#include <boost/fusion/sequence/conversion.hpp>

namespace boost { namespace fusion { namespace detail 
{
    template <typename Tag>
    struct as_impl;

    template <>
    struct as_impl<cons_tag>
    {
        template <typename Sequence>
        struct apply : result_of::as_list<Sequence> {};
    };

    template <>
    struct as_impl<map_tag>
    {
        template <typename Sequence>
        struct apply : result_of::as_map<Sequence> {};
    };

    template <>
    struct as_impl<set_tag>
    {
        template <typename Sequence>
        struct apply : result_of::as_set<Sequence> {};
    };

    template <>
    struct as_impl<vector_tag>
    {
        template <typename Sequence>
        struct apply : result_of::as_vector<Sequence> {};
    };

    template <typename Tag, typename Sequence>
    struct as
    {
        typedef typename
            as_impl<Tag>::template apply<Sequence>::type
        type;
    };

}}}

#endif

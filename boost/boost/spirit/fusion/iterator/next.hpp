/*=============================================================================
    Copyright (c) 2003 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ITERATOR_NEXT_HPP)
#define FUSION_ITERATOR_NEXT_HPP

#include <boost/spirit/fusion/detail/config.hpp>

namespace boost { namespace fusion
{
    template <typename Tag>
    struct next_impl
    {
        template <typename Iterator>
        struct apply
        {
            // VC6 needs this
            typedef int type;
        };
    };

    template <typename Iterator>
    struct result_of_next
    {
        typedef typename
            next_impl<FUSION_GET_TAG(Iterator)>::
                template apply<Iterator>::type
        type;
    };

    template <typename Iterator>
    inline typename result_of_next<Iterator>::type
    next(Iterator const& i)
    {
        return next_impl<FUSION_GET_TAG(Iterator)>::
            template apply<Iterator>::call(i);
    }
}}

#endif

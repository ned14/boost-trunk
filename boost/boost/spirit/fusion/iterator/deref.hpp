/*=============================================================================
    Copyright (c) 2003 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ITERATOR_DEREF_HPP)
#define FUSION_ITERATOR_DEREF_HPP

#include <boost/spirit/fusion/detail/config.hpp>
#include <boost/spirit/fusion/iterator/detail/iterator_base.hpp>

namespace boost { namespace fusion
{
    template <typename Tag>
    struct deref_impl
    {
        template <typename Iterator>
        struct apply {};
    };

    template <typename Iterator>
    struct result_of_deref
    {
        typedef typename
            deref_impl<FUSION_GET_TAG(Iterator)>::
                template apply<Iterator>::type
        type;
    };

    template <typename Iterator>
    inline typename result_of_deref<Iterator>::type
    operator*(iterator_base<Iterator> const& i)
    {
        typename result_of_deref<Iterator>::type result =
            deref_impl<FUSION_GET_TAG(Iterator)>::
                template apply<Iterator>::call(i.cast());
        return result;
    }

    template <typename Iterator>
    inline typename result_of_deref<Iterator>::type
    operator*(iterator_base<Iterator>& i)
    {
        typename result_of_deref<Iterator>::type result =
            deref_impl<FUSION_GET_TAG(Iterator)>::
                template apply<Iterator>::call(i.cast());
        return result;
    }

    // Note: VC7.1 has a problem when we pass the return value directly.
    // Try removing the named temporary. This only happens on debug builds.
    // It seems to be a return value optimization bug.
}}

#endif

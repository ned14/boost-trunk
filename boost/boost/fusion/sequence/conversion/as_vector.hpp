/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_AS_VECTOR_09222005_1104)
#define FUSION_AS_VECTOR_09222005_1104

#include <boost/fusion/sequence/conversion/detail/as_vector.hpp>
#include <boost/fusion/sequence/container/vector/vector.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion 
{
    namespace result_of
    {
        template <typename Sequence>
        struct as_vector
        {
            typedef typename detail::as_vector<result_of::size<Sequence>::value> gen;
            typedef typename gen::
                template apply<typename result_of::begin<Sequence>::type>::type
            type;
        };
    }

    template <typename Sequence>
    inline typename result_of::as_vector<Sequence>::type
    as_vector(Sequence& seq)
    {
        typedef typename result_of::as_vector<Sequence>::gen gen;
        return gen::call(fusion::begin(seq));
    }

    template <typename Sequence>
    inline typename result_of::as_vector<Sequence const>::type
    as_vector(Sequence const& seq)
    {
        typedef typename result_of::as_vector<Sequence const>::gen gen;
        return gen::call(fusion::begin(seq));
    }
}}

#endif

/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_AT_IMPL_20060124_1933)
#define FUSION_AT_IMPL_20060124_1933

#include <boost/fusion/sequence/container/vector.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/sequence/conversion/as_vector.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/mpl/assert.hpp>

namespace boost { namespace fusion 
{
    struct zip_view_tag;

    namespace detail
    {
        template<typename N>
        struct poly_at
        {
            template<typename SeqRef>
            struct result
                : result_of::at<typename remove_reference<SeqRef>::type, N>
            {
                BOOST_MPL_ASSERT((is_reference<SeqRef>));
            };

            template<typename Seq>
            typename result<Seq&>::type
            operator()(Seq& seq) const
            {
                return fusion::at<N>(seq);
            }

            template<typename Seq>
            typename result<Seq const&>::type
            operator()(Seq const& seq) const
            {
                return fusion::at<N>(seq);
            }
        };
    }

    namespace extension
    {
        template<typename Tag>
        struct at_impl;

        template<>
        struct at_impl<zip_view_tag>
        {
            template<typename Seq, typename N>
            struct apply
            {
                typedef typename result_of::as_vector<
                    typename result_of::transform<
                    typename Seq::sequences, detail::poly_at<N> >::type>::type type;

                static type
                call(Seq& seq)
                {
                    return type(
                        fusion::transform(seq.sequences_, detail::poly_at<N>()));
                }
            };
        };
    }
}}

#endif

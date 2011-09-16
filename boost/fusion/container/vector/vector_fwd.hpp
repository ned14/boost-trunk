/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VECTOR_FORWARD_07072005_0125)
#define FUSION_VECTOR_FORWARD_07072005_0125

#include <boost/fusion/container/vector/limits.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

#include <boost/fusion/container/vector/vector10.hpp>
#if (FUSION_MAX_VECTOR_SIZE > 10)
#include <boost/fusion/container/vector/vector20.hpp>
#endif
#if (FUSION_MAX_VECTOR_SIZE > 20)
#include <boost/fusion/container/vector/vector30.hpp>
#endif
#if (FUSION_MAX_VECTOR_SIZE > 30)
#include <boost/fusion/container/vector/vector40.hpp>
#endif
#if (FUSION_MAX_VECTOR_SIZE > 40)
#include <boost/fusion/container/vector/vector50.hpp>
#endif

namespace boost { namespace fusion
{
    struct void_;

    template <
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
            FUSION_MAX_VECTOR_SIZE, typename T, void_)
    >
    struct vector;
}}

#endif

/*=============================================================================
    Copyright (c) 2006 Tobias Schwinger
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_GRAMMAR_DEF_FWD_HPP)
#define BOOST_SPIRIT_GRAMMAR_DEF_FWD_HPP

#include <boost/fusion/sequence/container/vector.hpp>
#include <boost/spirit/phoenix/core/limits.hpp>
#include <boost/spirit/phoenix/core/limits.hpp>

#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>

#if !defined(BOOST_SPIRIT_GRAMMAR_STARTRULE_TYPE_LIMIT)
#define BOOST_SPIRIT_GRAMMAR_STARTRULE_TYPE_LIMIT PHOENIX_LIMIT
#endif

namespace boost { namespace fusion 
{    
    struct void_;
}}

namespace boost { namespace phoenix 
{    
    typedef fusion::void_ void_;
}}

namespace boost { namespace spirit {

    template <
        typename T,
        BOOST_PP_ENUM_BINARY_PARAMS(
            BOOST_PP_DEC(BOOST_SPIRIT_GRAMMAR_STARTRULE_TYPE_LIMIT),
            typename T, = phoenix::void_ BOOST_PP_INTERCEPT
        )
    >
    class grammar_def;

}} // namespace boost::spirit

#endif


/*=============================================================================
    Copyright (c) 2006 Tobias Schwinger
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_CLOSURE_FWD_HPP)
#define BOOST_SPIRIT_CLOSURE_FWD_HPP

#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

#if !defined(PHOENIX_DYNAMIC_LIMIT)
# define PHOENIX_DYNAMIC_LIMIT 10
#endif

#if !defined(BOOST_SPIRIT_DYNAMIC_SCOPE_LIMIT)
# define BOOST_SPIRIT_DYNAMIC_SCOPE_LIMIT PHOENIX_DYNAMIC_LIMIT
#endif

namespace boost { namespace fusion 
{    
    struct void_;
}}

namespace boost { namespace phoenix 
{    
    typedef fusion::void_ void_;
}}

namespace boost { namespace spirit 
{
    template<typename ClosureT>
    class dynamic_scope_context;

    template <typename Closure>
    class init_dynamic_scope_context;

    template <typename Parser, typename ActorTuple>
    struct init_dynamic_scope_parser;

    template <
        typename DerivedT
      , BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
            BOOST_SPIRIT_DYNAMIC_SCOPE_LIMIT, typename T, phoenix::void_)
    >
    struct dynamic_scope;

}} // namespace boost::spirit

#endif


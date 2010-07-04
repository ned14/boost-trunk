//  Copyright (c) 2001-2010 Hartmut Kaiser
//  Copyright (c) 2001-2010 Joel de Guzman
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_DEBUG_HANDLER_APR_21_2010_0148PM)
#define BOOST_SPIRIT_KARMA_DEBUG_HANDLER_APR_21_2010_0148PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/karma/nonterminal/rule.hpp>
#include <boost/spirit/home/karma/nonterminal/debug_handler_state.hpp>
#include <boost/function.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/out.hpp>
#include <iostream>

namespace boost { namespace spirit { namespace karma
{
    template <
        typename OutputIterator, typename Context, typename Delimiter
      , typename Properties, typename F>
    struct debug_handler
    {
        typedef detail::output_iterator<OutputIterator, Properties> 
            output_iterator;
        typedef detail::enable_buffering<output_iterator> buffer_type;

        typedef function<bool(output_iterator&, Context&, Delimiter const&)>
            function_type;

        debug_handler(function_type subject, F f, std::string const& rule_name)
          : subject(subject)
          , f(f)
          , rule_name(rule_name)
        {}

        bool operator()(output_iterator& sink, Context& context
          , Delimiter const& delim) const
        {
            buffer_type buffer(sink);
            bool r = false;

            f (sink, context, pre_generate, rule_name, buffer);
            {
                detail::disable_counting<output_iterator> nocount(sink);
                r = subject(sink, context, delim);
            }

            if (r) 
            {
                f (sink, context, successful_generate, rule_name, buffer);
                buffer.buffer_copy();
                return true;
            }
            f (sink, context, failed_generate, rule_name, buffer);
            return false;
        }

        function_type subject;
        F f;
        std::string rule_name;
    };

    template <
        typename OutputIterator, typename T0, typename T1, typename T2
      , typename F>
    void debug(rule<OutputIterator, T0, T1, T2>& r, F f)
    {
        typedef rule<OutputIterator, T0, T1, T2> rule_type;

        typedef
            debug_handler<
                OutputIterator
              , typename rule_type::context_type
              , typename rule_type::delimiter_type
              , typename rule_type::properties
              , F>
        debug_handler;
        r.f = debug_handler(r.f, f, r.name());
    }

    struct simple_trace;

    template <typename OutputIterator, typename T0, typename T1, typename T2>
    void debug(rule<OutputIterator, T0, T1, T2>& r)
    {
        typedef rule<OutputIterator, T0, T1, T2> rule_type;

        typedef
            debug_handler<
                OutputIterator
              , typename rule_type::context_type
              , typename rule_type::delimiter_type
              , typename rule_type::properties
              , simple_trace>
        debug_handler;
        r.f = debug_handler(r.f, simple_trace(), r.name());
    }

}}}

///////////////////////////////////////////////////////////////////////////////
//  Utility macro for easy enabling of rule and grammar debugging
#if !defined(BOOST_SPIRIT_DEBUG_NODE)
  #if defined(BOOST_SPIRIT_KARMA_DEBUG)
    #define BOOST_SPIRIT_DEBUG_NODE(r)  r.name(#r); debug(r)
  #else
    #define BOOST_SPIRIT_DEBUG_NODE(r)
  #endif
#endif

#endif

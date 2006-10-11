/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef PHOENIX_CORE_REFERENCE_HPP
#define PHOENIX_CORE_REFERENCE_HPP

#include <boost/spirit/phoenix/core/actor.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace phoenix
{
    template <typename T>
    struct reference
    {
        // $$$ TODO: a better (user friendly) static assert
        BOOST_STATIC_ASSERT(
            mpl::not_<is_reference<T> >::value != 0);

        typedef mpl::false_ no_nullary;

        template <typename Env>
        struct result
        {
            typedef T& type;
        };

        reference(T& arg)
            : ref(arg) {}

        template <typename Env>
        T& eval(Env const&) const
        {
            return ref;
        }

        T& ref;
    };

    template <typename T>
    inline actor<reference<T> > const
    ref(T& v)
    {
        return reference<T>(v);
    }

    template <typename T>
    inline actor<reference<T const> > const
    cref(T const& v)
    {
        return reference<T const>(v);
    }

    namespace detail
    {
        struct error_attempting_to_convert_an_actor_to_a_reference {};
    }

    template <typename Base>
    void
    ref(actor<Base> const& v
        , detail::error_attempting_to_convert_an_actor_to_a_reference
            = detail::error_attempting_to_convert_an_actor_to_a_reference());

    template <typename Base>
    void
    cref(actor<Base> const& v
        , detail::error_attempting_to_convert_an_actor_to_a_reference
            = detail::error_attempting_to_convert_an_actor_to_a_reference());
}}

#endif

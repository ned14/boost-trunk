/*=============================================================================
    Copyright (c) 2001-2009 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(SPIRIT_PASS_CONTAINER_JANUARY_06_2009_0802PM)
#define SPIRIT_PASS_CONTAINER_JANUARY_06_2009_0802PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/attributes.hpp>
#include <boost/spirit/home/support/container.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace spirit { namespace qi { namespace detail
{
    // has_same_elements: utility to check if the RHS attribute
    // is an STL container and that its value_type is convertible
    // to the LHS.

    template <typename LHS, typename RHSAttribute
      , bool IsContainer = traits::is_container<RHSAttribute>::value>
    struct has_same_elements : mpl::false_ {};

    template <typename LHS, typename RHSAttribute>
    struct has_same_elements<LHS, RHSAttribute, true>
        : is_convertible<
            typename RHSAttribute::value_type
          , LHS> {};

    // This function handles the case where the attribute (Attr) given
    // the sequence is an STL container. This is a wrapper around F.
    // The function F does the actual parsing.
    template <typename F, typename Attr>
    struct pass_container
    {
        pass_container(F const& f, Attr& attr)
          : f(f), attr(attr) {}

        // this is for the case when the current element exposes an attribute
        // which is pushed back onto the container
        template <typename Component>
        bool dispatch_attribute(Component const& component, mpl::true_) const
        {
            typename traits::result_of::value<Attr>::type val;
            bool r = f(component, val);
            if (!r)
            {
                // push the parsed value into our attribute
                traits::push_back(attr, val);
            }
            return r;
        }

        // this is for the case when the current element doesn't expect an 
        // attribute
        template <typename Component>
        bool dispatch_attribute(Component const& component, mpl::false_) const
        {
            return f(component, unused);
        }

        // This handles the case where the attribute of the component
        // is not an STL container or its element is not convertible
        // to the target attribute's (Attr) value_type.
        template <typename Component>
        bool dispatch_main(Component const& component, mpl::false_) const
        {
            // we need to dispatch again depending on the type of the attribute
            // of the current element (component). If this is has no attribute
            // we shouldn't push an element into the container.
            typedef typename F::context_type context_type;
            typedef traits::is_not_unused<
                typename traits::attribute_of<Component, context_type>::type
            > predicate;

            return dispatch_attribute(component, predicate());
        }

        // This handles the case where the attribute of the component is
        // an STL container *and* its value_type is convertible to the
        // target attribute's (Attr) value_type.
        template <typename Component>
        bool dispatch_main(Component const& component, mpl::true_) const
        {
            return f(component, attr);
        }

        // Dispachtes to dispatch_main depending on the attribute type
        // of the Component
        template <typename Component>
        bool operator()(Component const& component) const
        {
            typedef typename traits::result_of::value<Attr>::type lhs;
            typedef typename F::iterator_type iterator_type;
            typedef typename F::context_type context_type;
            typedef typename traits::attribute_of<
                Component, context_type, iterator_type>::type
            rhs_attribute;

            return dispatch_main(component
              , has_same_elements<lhs, rhs_attribute>());
        }

        F f;
        Attr& attr;
    };

    // Utility function to make a pass_container
    template <typename F, typename Attr>
    pass_container<F, Attr>
    inline make_pass_container(F const& f, Attr& attr)
    {
        return pass_container<F, Attr>(f, attr);
    }
}}}}

#endif

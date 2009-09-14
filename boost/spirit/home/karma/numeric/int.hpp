//  Copyright (c) 2001-2009 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_INT_FEB_23_2007_0840PM)
#define BOOST_SPIRIT_KARMA_INT_FEB_23_2007_0840PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <limits>

#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/string_traits.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/char_class.hpp>
#include <boost/spirit/home/support/detail/get_encoding.hpp>
#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/delimit_out.hpp>
#include <boost/spirit/home/karma/auxiliary/lazy.hpp>
#include <boost/spirit/home/karma/detail/get_casetag.hpp>
#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/numeric/detail/numeric_utils.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/value_at.hpp>
#include <boost/fusion/include/vector.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit
{
    namespace tag
    {
        template <typename T, unsigned Radix, bool force_sign>
        struct int_tag {};
    }

    namespace karma
    {
        ///////////////////////////////////////////////////////////////////////
        // This one is the class that the user can instantiate directly in 
        // order to create a customized int generator
        template <typename T = int, unsigned Radix = 10, bool force_sign = false>
        struct int_generator
          : spirit::terminal<tag::int_tag<T, Radix, force_sign> > 
        {};
    }

    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct use_terminal<karma::domain, tag::short_>    // enables short_
      : mpl::true_ {};

    template <>
    struct use_terminal<karma::domain, tag::int_>      // enables int_
      : mpl::true_ {};

    template <>
    struct use_terminal<karma::domain, tag::long_>     // enables long_
      : mpl::true_ {};

#ifdef BOOST_HAS_LONG_LONG
    template <>
    struct use_terminal<karma::domain, tag::long_long> // enables long_long
      : mpl::true_ {};
#endif

    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct use_terminal<karma::domain, short>      // enables lit(short(0))
      : mpl::true_ {};

    template <>
    struct use_terminal<karma::domain, int>      // enables lit(0)
      : mpl::true_ {};

    template <>
    struct use_terminal<karma::domain, long>     // enables lit(0L)
      : mpl::true_ {};

#ifdef BOOST_HAS_LONG_LONG
    template <>
    struct use_terminal<karma::domain, boost::long_long_type> // enables lit(0LL)
      : mpl::true_ {};
#endif

    ///////////////////////////////////////////////////////////////////////////
    template <typename A0>
    struct use_terminal<karma::domain         // enables short_(...)
      , terminal_ex<tag::short_, fusion::vector1<A0> >
    > : mpl::true_ {};

    template <typename A0>
    struct use_terminal<karma::domain         // enables int_(...)
      , terminal_ex<tag::int_, fusion::vector1<A0> >
    > : mpl::true_ {};

    template <typename A0>
    struct use_terminal<karma::domain         // enables long_(...)
      , terminal_ex<tag::long_, fusion::vector1<A0> >
    > : mpl::true_ {};

#ifdef BOOST_HAS_LONG_LONG
    template <typename A0>
    struct use_terminal<karma::domain         // enables long_long(...)
      , terminal_ex<tag::long_long, fusion::vector1<A0> >
    > : mpl::true_ {};
#endif

    ///////////////////////////////////////////////////////////////////////////
    template <>                               // enables *lazy* short_(...)
    struct use_lazy_terminal<karma::domain, tag::short_, 1> 
      : mpl::true_ {};

    template <>                               // enables *lazy* int_(...)
    struct use_lazy_terminal<karma::domain, tag::int_, 1> 
      : mpl::true_ {};

    template <>                               // enables *lazy* long_(...)
    struct use_lazy_terminal<karma::domain, tag::long_, 1> 
      : mpl::true_ {};

#ifdef BOOST_HAS_LONG_LONG
    template <>                               // enables *lazy* long_long(...)
    struct use_lazy_terminal<karma::domain, tag::long_long, 1> 
      : mpl::true_ {};
#endif

    ///////////////////////////////////////////////////////////////////////////
    // enables any custom int_generator
    template <typename T, unsigned Radix, bool force_sign>
    struct use_terminal<karma::domain, tag::int_tag<T, Radix, force_sign> >
      : mpl::true_ {};

    // enables any custom int_generator(...)
    template <typename T, unsigned Radix, bool force_sign, typename A0>
    struct use_terminal<karma::domain
      , terminal_ex<tag::int_tag<T, Radix, force_sign>, fusion::vector1<A0> >
    > : mpl::true_ {};

    // enables *lazy* custom int_generator
    template <typename T, unsigned Radix, bool force_sign>
    struct use_lazy_terminal<
        karma::domain
      , tag::int_tag<T, Radix, force_sign>
      , 1 // arity
    > : mpl::true_ {};

}} 

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma
{
    using spirit::short_;
    using spirit::short__type;
    using spirit::int_;
    using spirit::int__type;
    using spirit::long_;
    using spirit::long__type;
#ifdef BOOST_HAS_LONG_LONG
    using spirit::long_long;
    using spirit::long_long_type;
#endif

    using spirit::lit;    // lit(1) is equivalent to 1

    ///////////////////////////////////////////////////////////////////////////
    //  This specialization is used for int generators not having a direct
    //  initializer: int_, long_ etc. These generators must be used in
    //  conjunction with an Attribute.
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename T, typename CharEncoding, typename Tag, unsigned Radix
      , bool force_sign>
    struct any_int_generator
      : primitive_generator<any_int_generator<T, CharEncoding, Tag, Radix
          , force_sign> >
    {
        template <typename Context, typename Unused>
        struct attribute
        {
            typedef T type;
        };

        // check template Attribute 'Radix' for validity
        BOOST_SPIRIT_ASSERT_MSG(
            Radix == 2 || Radix == 8 || Radix == 10 || Radix == 16,
            not_supported_radix, ());

        BOOST_SPIRIT_ASSERT_MSG(std::numeric_limits<T>::is_signed,
            signed_unsigned_mismatch, ());

        // int has a Attribute attached
        template <typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        static bool
        generate(OutputIterator& sink, Context&, Delimiter const& d
          , Attribute const& attr)
        {
            return sign_inserter::call(sink, detail::is_zero(attr)
                      , detail::is_negative(attr), force_sign) &&
                   int_inserter<Radix, CharEncoding, Tag>::call(sink
                      , detail::absolute_value(attr)) &&
                   karma::delimit_out(sink, d);      // always do post-delimiting
        }

        // this int has no Attribute attached, it needs to have been
        // initialized from a direct literal
        template <typename OutputIterator, typename Context, typename Delimiter>
        static bool
        generate(OutputIterator&, Context&, Delimiter const&, unused_type)
        {
            BOOST_SPIRIT_ASSERT_MSG(false, int_not_usable_without_attribute, ());
            return false;
        }

        template <typename Context>
        static info what(Context const& ctx)
        {
            return info("integer");
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    //  This specialization is used for int generators having a direct
    //  initializer: int_(10), long_(20) etc.
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename T, typename CharEncoding, typename Tag, unsigned Radix
      , bool force_sign, bool no_attribute>
    struct literal_int_generator
      : primitive_generator<literal_int_generator<T, CharEncoding, Tag, Radix
          , force_sign, no_attribute> >
    {
        template <typename Context, typename Unused>
        struct attribute
          : mpl::if_c<no_attribute, unused_type, T>
        {};

        literal_int_generator(typename add_const<T>::type n)
          : n_(n) {}

        // check template Attribute 'Radix' for validity
        BOOST_SPIRIT_ASSERT_MSG(
            Radix == 2 || Radix == 8 || Radix == 10 || Radix == 16,
            not_supported_radix, ());

        BOOST_SPIRIT_ASSERT_MSG(std::numeric_limits<T>::is_signed,
            signed_unsigned_mismatch, ());

        // A int_(1) which additionally has an associated attribute emits
        // its immediate literal only if it matches the attribute, otherwise
        // it fails.
        template <typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context&, Delimiter const& d
          , Attribute const& attr) const
        {
            if (n_ != attr)
                return false;

            return sign_inserter::call(sink, detail::is_zero(n_)
                      , detail::is_negative(n_), force_sign) &&
                   int_inserter<Radix, CharEncoding, Tag>::call(sink
                      , detail::absolute_value(n_)) &&
                   karma::delimit_out(sink, d);      // always do post-delimiting
        }

        // A int_(1) without any associated attribute just emits its 
        // immediate literal
        template <typename OutputIterator, typename Context, typename Delimiter>
        bool generate(OutputIterator& sink, Context&, Delimiter const& d
          , unused_type) const
        {
            return sign_inserter::call(sink, detail::is_zero(n_)
                      , detail::is_negative(n_), force_sign) &&
                   int_inserter<Radix, CharEncoding, Tag>::call(sink
                      , detail::absolute_value(n_)) &&
                   karma::delimit_out(sink, d);      // always do post-delimiting
        }

        template <typename Context>
        static info what(Context const& ctx)
        {
            return info("integer");
        }

        T n_;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename T, typename Modifiers, unsigned Radix = 10
      , bool force_sign = false>
    struct make_int
    {
        static bool const lower = 
            has_modifier<Modifiers, tag::char_code_base<tag::lower> >::value;
        static bool const upper = 
            has_modifier<Modifiers, tag::char_code_base<tag::upper> >::value;

        typedef any_int_generator<
            T
          , typename spirit::detail::get_encoding<
                Modifiers, unused_type, lower || upper>::type
          , typename detail::get_casetag<Modifiers, lower || upper>::type
          , Radix
          , force_sign
        > result_type;

        result_type operator()(unused_type, unused_type) const
        {
            return result_type();
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename Modifiers>
    struct make_primitive<tag::short_, Modifiers> 
      : make_int<short, Modifiers> {};

    template <typename Modifiers>
    struct make_primitive<tag::int_, Modifiers> 
      : make_int<int, Modifiers> {};

    template <typename Modifiers>
    struct make_primitive<tag::long_, Modifiers> 
      : make_int<long, Modifiers> {};

#ifdef BOOST_HAS_LONG_LONG
    template <typename Modifiers>
    struct make_primitive<tag::long_long, Modifiers> 
      : make_int<boost::long_long_type, Modifiers> {};
#endif

    template <typename T, unsigned Radix, bool force_sign, typename Modifiers>
    struct make_primitive<tag::int_tag<T, Radix, force_sign>, Modifiers>
      : make_int<T, Modifiers, Radix, force_sign> {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename T, typename Modifiers, unsigned Radix = 10
      , bool force_sign = false>
    struct make_int_direct
    {
        static bool const lower = 
            has_modifier<Modifiers, tag::char_code_base<tag::lower> >::value;
        static bool const upper = 
            has_modifier<Modifiers, tag::char_code_base<tag::upper> >::value;

        typedef literal_int_generator<
            T
          , typename spirit::detail::get_encoding<
                Modifiers, unused_type, lower || upper>::type
          , typename detail::get_casetag<Modifiers, lower || upper>::type
          , Radix, force_sign, false
        > result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, unused_type) const
        {
            return result_type(fusion::at_c<0>(term.args));
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename Modifiers, typename A0>
    struct make_primitive<
        terminal_ex<tag::short_, fusion::vector1<A0> >, Modifiers>
      : make_int_direct<short, Modifiers> {};

    template <typename Modifiers, typename A0>
    struct make_primitive<
        terminal_ex<tag::int_, fusion::vector1<A0> >, Modifiers>
      : make_int_direct<int, Modifiers> {};

    template <typename Modifiers, typename A0>
    struct make_primitive<
        terminal_ex<tag::long_, fusion::vector1<A0> >, Modifiers>
      : make_int_direct<long, Modifiers> {};

#ifdef BOOST_HAS_LONG_LONG
    template <typename Modifiers, typename A0>
    struct make_primitive<
        terminal_ex<tag::long_long, fusion::vector1<A0> >, Modifiers>
      : make_int_direct<boost::long_long_type, Modifiers> {};
#endif

    template <typename T, unsigned Radix, bool force_sign, typename A0
      , typename Modifiers>
    struct make_primitive<
        terminal_ex<tag::int_tag<T, Radix, force_sign>, fusion::vector1<A0> >
          , Modifiers>
      : make_int_direct<T, Modifiers, Radix, force_sign> {};

    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename T, typename Modifiers>
        struct basic_int_literal
        {
            static bool const lower =
                has_modifier<Modifiers, tag::char_code_base<tag::lower> >::value;
            static bool const upper =
                has_modifier<Modifiers, tag::char_code_base<tag::upper> >::value;

            typedef literal_int_generator<
                T
              , typename spirit::detail::get_encoding<
                    Modifiers, unused_type, lower || upper>::type
              , typename detail::get_casetag<Modifiers, lower || upper>::type
              , 10, false, true
            > result_type;

            template <typename T_>
            result_type operator()(T_ i, unused_type) const
            {
                return result_type(i);
            }
        };
    }

    template <typename Modifiers>
    struct make_primitive<short, Modifiers> 
      : detail::basic_int_literal<int, Modifiers> {};

    template <typename Modifiers>
    struct make_primitive<int, Modifiers> 
      : detail::basic_int_literal<int, Modifiers> {};

    template <typename Modifiers>
    struct make_primitive<long, Modifiers> 
      : detail::basic_int_literal<long, Modifiers> {};

#ifdef BOOST_HAS_LONG_LONG
    template <typename Modifiers>
    struct make_primitive<boost::long_long_type, Modifiers> 
      : detail::basic_int_literal<boost::long_long_type, Modifiers> {};
#endif

}}}

#endif

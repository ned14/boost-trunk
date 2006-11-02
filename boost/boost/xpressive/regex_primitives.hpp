///////////////////////////////////////////////////////////////////////////////
/// \file regex_primitives.hpp
/// Contains the syntax elements for writing static regular expressions.
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_REGEX_PRIMITIVES_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_REGEX_PRIMITIVES_HPP_EAN_10_04_2005

#include <climits>
#include <boost/mpl/assert.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/core/icase.hpp>
#include <boost/xpressive/detail/core/action.hpp>
#include <boost/xpressive/detail/core/matchers.hpp>
#include <boost/xpressive/detail/static/as_xpr.hpp>
#include <boost/xpressive/detail/static/compile.hpp>
#include <boost/xpressive/detail/static/modifier.hpp>
#include <boost/xpressive/detail/utility/ignore_unused.hpp>
#include <boost/xpressive/detail/static/regex_operators.hpp>
#include <boost/xpressive/detail/static/productions/productions.hpp>

namespace boost { namespace xpressive { namespace detail
{

    typedef assert_word_placeholder<word_boundary<true> > assert_word_boundary;
    typedef assert_word_placeholder<word_begin> assert_word_begin;
    typedef assert_word_placeholder<word_end> assert_word_end;

    struct mark_tag_extension
      : proto::extends<basic_mark_tag>
    {
        mark_tag_extension(int mark_nbr)
        {
            basic_mark_tag that = {{mark_nbr}};
            this->assign(that);
        }
    };

/*
///////////////////////////////////////////////////////////////////////////////
/// INTERNAL ONLY
// BOOST_XPRESSIVE_GLOBAL
//  for defining globals that neither violate the One Definition Rule nor
//  lead to undefined behavior due to global object initialization order.
//#define BOOST_XPRESSIVE_GLOBAL(type, name, init)                                        \
//    namespace detail                                                                    \
//    {                                                                                   \
//        template<int Dummy>                                                             \
//        struct BOOST_PP_CAT(global_pod_, name)                                          \
//        {                                                                               \
//            static type const value;                                                    \
//        private:                                                                        \
//            union type_must_be_pod                                                      \
//            {                                                                           \
//                type t;                                                                 \
//                char ch;                                                                \
//            } u;                                                                        \
//        };                                                                              \
//        template<int Dummy>                                                             \
//        type const BOOST_PP_CAT(global_pod_, name)<Dummy>::value = init;                \
//    }                                                                                   \
//    type const &name = detail::BOOST_PP_CAT(global_pod_, name)<0>::value
*/


} // namespace detail

/// INTERNAL ONLY (for backwards compatibility)
unsigned int const repeat_max = UINT_MAX-1;

///////////////////////////////////////////////////////////////////////////////
/// \brief For infinite repetition of a sub-expression.
///
/// Magic value used with the repeat\<\>() function template
/// to specify an unbounded repeat. Use as: repeat<17, inf>('a').
/// The equivalent in perl is /a{17,}/.
unsigned int const inf = UINT_MAX-1;

/// INTERNAL ONLY (for backwards compatibility)
proto::meta::terminal<detail::epsilon_matcher>::type const epsilon = {};

///////////////////////////////////////////////////////////////////////////////
/// \brief Successfully matches nothing.
///
/// Successfully matches a zero-width sequence. nil always succeeds and
/// never consumes any characters.
proto::meta::terminal<detail::epsilon_matcher>::type const nil = {};

///////////////////////////////////////////////////////////////////////////////
/// \brief Matches an alpha-numeric character.
///
/// The regex traits are used to determine which characters are alpha-numeric.
/// To match any character that is not alpha-numeric, use ~alnum.
///
/// \attention alnum is equivalent to /[[:alnum:]]/ in perl. ~alnum is equivalent
/// to /[[:^alnum:]]/ in perl.
proto::meta::terminal<detail::posix_charset_placeholder>::type const alnum = {{"alnum", false}};

///////////////////////////////////////////////////////////////////////////////
/// \brief Matches an alphabetic character.
///
/// The regex traits are used to determine which characters are alphabetic.
/// To match any character that is not alphabetic, use ~alpha.
///
/// \attention alpha is equivalent to /[[:alpha:]]/ in perl. ~alpha is equivalent
/// to /[[:^alpha:]]/ in perl.
proto::meta::terminal<detail::posix_charset_placeholder>::type const alpha = {{"alpha", false}};

///////////////////////////////////////////////////////////////////////////////
/// \brief Matches a blank (horizonal white-space) character.
///
/// The regex traits are used to determine which characters are blank characters.
/// To match any character that is not blank, use ~blank.
///
/// \attention blank is equivalent to /[[:blank:]]/ in perl. ~blank is equivalent
/// to /[[:^blank:]]/ in perl.
proto::meta::terminal<detail::posix_charset_placeholder>::type const blank = {{"blank", false}};

///////////////////////////////////////////////////////////////////////////////
/// \brief Matches a control character.
///
/// The regex traits are used to determine which characters are control characters.
/// To match any character that is not a control character, use ~cntrl.
///
/// \attention cntrl is equivalent to /[[:cntrl:]]/ in perl. ~cntrl is equivalent
/// to /[[:^cntrl:]]/ in perl.
proto::meta::terminal<detail::posix_charset_placeholder>::type const cntrl = {{"cntrl", false}};

///////////////////////////////////////////////////////////////////////////////
/// \brief Matches a digit character.
///
/// The regex traits are used to determine which characters are digits.
/// To match any character that is not a digit, use ~digit.
///
/// \attention digit is equivalent to /[[:digit:]]/ in perl. ~digit is equivalent
/// to /[[:^digit:]]/ in perl.
proto::meta::terminal<detail::posix_charset_placeholder>::type const digit = {{"digit", false}};

///////////////////////////////////////////////////////////////////////////////
/// \brief Matches a graph character.
///
/// The regex traits are used to determine which characters are graphable.
/// To match any character that is not graphable, use ~graph.
///
/// \attention graph is equivalent to /[[:graph:]]/ in perl. ~graph is equivalent
/// to /[[:^graph:]]/ in perl.
proto::meta::terminal<detail::posix_charset_placeholder>::type const graph = {{"graph", false}};

///////////////////////////////////////////////////////////////////////////////
/// \brief Matches a lower-case character.
///
/// The regex traits are used to determine which characters are lower-case.
/// To match any character that is not a lower-case character, use ~lower.
///
/// \attention lower is equivalent to /[[:lower:]]/ in perl. ~lower is equivalent
/// to /[[:^lower:]]/ in perl.
proto::meta::terminal<detail::posix_charset_placeholder>::type const lower = {{"lower", false}};

///////////////////////////////////////////////////////////////////////////////
/// \brief Matches a printable character.
///
/// The regex traits are used to determine which characters are printable.
/// To match any character that is not printable, use ~print.
///
/// \attention print is equivalent to /[[:print:]]/ in perl. ~print is equivalent
/// to /[[:^print:]]/ in perl.
proto::meta::terminal<detail::posix_charset_placeholder>::type const print = {{"print", false}};

///////////////////////////////////////////////////////////////////////////////
/// \brief Matches a punctuation character.
///
/// The regex traits are used to determine which characters are punctuation.
/// To match any character that is not punctuation, use ~punct.
///
/// \attention punct is equivalent to /[[:punct:]]/ in perl. ~punct is equivalent
/// to /[[:^punct:]]/ in perl.
proto::meta::terminal<detail::posix_charset_placeholder>::type const punct = {{"punct", false}};

///////////////////////////////////////////////////////////////////////////////
/// \brief Matches a space character.
///
/// The regex traits are used to determine which characters are space characters.
/// To match any character that is not white-space, use ~space.
///
/// \attention space is equivalent to /[[:space:]]/ in perl. ~space is equivalent
/// to /[[:^space:]]/ in perl.
proto::meta::terminal<detail::posix_charset_placeholder>::type const space = {{"space", false}};

///////////////////////////////////////////////////////////////////////////////
/// \brief Matches an upper-case character.
///
/// The regex traits are used to determine which characters are upper-case.
/// To match any character that is not upper-case, use ~upper.
///
/// \attention upper is equivalent to /[[:upper:]]/ in perl. ~upper is equivalent
/// to /[[:^upper:]]/ in perl.
proto::meta::terminal<detail::posix_charset_placeholder>::type const upper = {{"upper", false}};

///////////////////////////////////////////////////////////////////////////////
/// \brief Matches a hexadecimal digit character.
///
/// The regex traits are used to determine which characters are hex digits.
/// To match any character that is not a hex digit, use ~xdigit.
///
/// \attention xdigit is equivalent to /[[:xdigit:]]/ in perl. ~xdigit is equivalent
/// to /[[:^xdigit:]]/ in perl.
proto::meta::terminal<detail::posix_charset_placeholder>::type const xdigit = {{"xdigit", false}};

///////////////////////////////////////////////////////////////////////////////
/// \brief Beginning of sequence assertion.
///
/// For the character sequence [begin, end), 'bos' matches the
/// zero-width sub-sequence [begin, begin).
proto::meta::terminal<detail::assert_bos_matcher>::type const bos = {};

///////////////////////////////////////////////////////////////////////////////
/// \brief End of sequence assertion. 
///
/// For the character sequence [begin, end),
/// 'eos' matches the zero-width sub-sequence [end, end).
///
/// \attention Unlike the perl end of sequence assertion \$, 'eos' will
/// not match at the position [end-1, end-1) if *(end-1) is '\\n'. To
/// get that behavior, use (!_n >> eos).
proto::meta::terminal<detail::assert_eos_matcher>::type const eos = {};

///////////////////////////////////////////////////////////////////////////////
/// \brief Beginning of line assertion. 
///
/// 'bol' matches the zero-width sub-sequence
/// immediately following a logical newline sequence. The regex traits
/// is used to determine what constitutes a logical newline sequence.
proto::meta::terminal<detail::assert_bol_placeholder>::type const bol = {};

///////////////////////////////////////////////////////////////////////////////
/// \brief End of line assertion.
///
/// 'eol' matches the zero-width sub-sequence
/// immediately preceeding a logical newline sequence. The regex traits
/// is used to determine what constitutes a logical newline sequence.
proto::meta::terminal<detail::assert_eol_placeholder>::type const eol = {};

///////////////////////////////////////////////////////////////////////////////
/// \brief Beginning of word assertion. 
///
/// 'bow' matches the zero-width sub-sequence
/// immediately following a non-word character and preceeding a word character.
/// The regex traits are used to determine what constitutes a word character.
proto::meta::terminal<detail::assert_word_begin>::type const bow = {};

///////////////////////////////////////////////////////////////////////////////
/// \brief End of word assertion. 
///
/// 'eow' matches the zero-width sub-sequence
/// immediately following a word character and preceeding a non-word character.
/// The regex traits are used to determine what constitutes a word character.
proto::meta::terminal<detail::assert_word_end>::type const eow = {};

///////////////////////////////////////////////////////////////////////////////
/// \brief Word boundary assertion.
///
/// '_b' matches the zero-width sub-sequence at the beginning or the end of a word.
/// It is equivalent to (bow | eow). The regex traits are used to determine what
/// constitutes a word character. To match a non-word boundary, use ~_b.
///
/// \attention _b is like \\b in perl. ~_b is like \\B in perl.
proto::meta::terminal<detail::assert_word_boundary>::type const _b = {};

///////////////////////////////////////////////////////////////////////////////
/// \brief Matches a word character.
///
/// '_w' matches a single word character. The regex traits are used to determine which
/// characters are word characters. Use ~_w to match a character that is not a word
/// character.
///
/// \attention _w is like \\w in perl. ~_w is like \\W in perl.
proto::meta::terminal<detail::posix_charset_placeholder>::type const _w = {{"w", false}};

///////////////////////////////////////////////////////////////////////////////
/// \brief Matches a digit character.
///
/// '_d' matches a single digit character. The regex traits are used to determine which
/// characters are digits. Use ~_d to match a character that is not a digit
/// character.
///
/// \attention _d is like \\d in perl. ~_d is like \\D in perl.
proto::meta::terminal<detail::posix_charset_placeholder>::type const _d = {{"d", false}};

///////////////////////////////////////////////////////////////////////////////
/// \brief Matches a space character.
///
/// '_s' matches a single space character. The regex traits are used to determine which
/// characters are space characters. Use ~_s to match a character that is not a space
/// character.
///
/// \attention _s is like \\s in perl. ~_s is like \\S in perl.
proto::meta::terminal<detail::posix_charset_placeholder>::type const _s = {{"s", false}};

///////////////////////////////////////////////////////////////////////////////
/// \brief Matches a literal newline character, '\\n'.
///
/// '_n' matches a single newline character, '\\n'. Use ~_n to match a character
/// that is not a newline.
///
/// \attention ~_n is like '.' in perl without the /s modifier.
proto::meta::terminal<detail::literal_placeholder<char> >::type const _n = {{'\n'}};

///////////////////////////////////////////////////////////////////////////////
/// \brief Matches a logical newline sequence.
///
/// '_ln' matches a logical newline sequence. This can be any character in the
/// line separator class, as determined by the regex traits, or the '\\r\\n' sequence.
/// For the purpose of back-tracking, '\\r\\n' is treated as a unit.
/// To match any one character that is not a logical newline, use ~_ln.
detail::logical_newline_xpression const _ln = {};

///////////////////////////////////////////////////////////////////////////////
/// \brief Matches any one character.
///
/// Match any character, similar to '.' in perl syntax with the /s modifier.
/// '_' matches any one character, including the newline.
///
/// \attention To match any character except the newline, use ~_n
proto::meta::terminal<detail::any_matcher>::type const _ = {};

///////////////////////////////////////////////////////////////////////////////
/// \brief Reference to the current regex object
///
/// Useful when constructing recursive regular expression objects. The 'self'
/// identifier is a short-hand for the current regex object. For instance,
/// sregex rx = '(' >> (self | nil) >> ')'; will create a regex object that
/// matches balanced parens such as "((()))".
proto::meta::terminal<detail::self_placeholder>::type const self = {};

///////////////////////////////////////////////////////////////////////////////
/// \brief Used to create character sets.
///
/// There are two ways to create character sets with the 'set' identifier. The
/// easiest is to create a comma-separated list of the characters in the set,
/// as in (set= 'a','b','c'). This set will match 'a', 'b', or 'c'. The other
/// way is to define the set as an argument to the set subscript operator.
/// For instance, set[ 'a' | range('b','c') | digit ] will match an 'a', 'b',
/// 'c' or a digit character.
///
/// To complement a set, apply the '~' operator. For instance, ~(set= 'a','b','c')
/// will match any character that is not an 'a', 'b', or 'c'.
///
/// Sets can be composed of other, possibly complemented, sets. For instance,
/// set[ ~digit | ~(set= 'a','b','c') ].
detail::set_initializer_type const set = {};

///////////////////////////////////////////////////////////////////////////////
/// \brief Sub-match placeholder, like $& in Perl
mark_tag::type const s0 = {{0}};

///////////////////////////////////////////////////////////////////////////////
/// \brief Sub-match placeholder, like $1 in perl.
///
/// To create a sub-match, assign a sub-expression to the sub-match placeholder.
/// For instance, (s1= _) will match any one character and remember which
/// character was matched in the 1st sub-match. Later in the pattern, you can
/// refer back to the sub-match. For instance,  (s1= _) >> s1  will match any
/// character, and then match the same character again.
///
/// After a successful regex_match() or regex_search(), the sub-match placeholders
/// can be used to index into the match_results\<\> object to retrieve the Nth
/// sub-match.
mark_tag::type const s1 = {{1}};
mark_tag::type const s2 = {{2}};
mark_tag::type const s3 = {{3}};
mark_tag::type const s4 = {{4}};
mark_tag::type const s5 = {{5}};
mark_tag::type const s6 = {{6}};
mark_tag::type const s7 = {{7}};
mark_tag::type const s8 = {{8}};
mark_tag::type const s9 = {{9}};

// NOTE: For the purpose of xpressive's documentation, make icase() look like an
// ordinary function. In reality, it is a function object defined in detail/icase.hpp
// so that it can serve double-duty as regex_constants::icase, the syntax_option_type.
// Do the same for as_xpr(), which is actually defined in detail/static/as_xpr.hpp
#ifdef BOOST_XPRESSIVE_DOXYGEN_INVOKED
///////////////////////////////////////////////////////////////////////////////
/// \brief Makes a literal into a regular expression.
///
/// Use as_xpr() to turn a literal into a regular expression. For instance,
/// "foo" >> "bar" will not compile because both operands to the right-shift
/// operator are const char*, and no such operator exists. Use as_xpr("foo") >> "bar"
/// instead.
///
/// You can use as_xpr() with character literals in addition to string literals.
/// For instance, as_xpr('a') will match an 'a'. You can also complement a
/// character literal, as with ~as_xpr('a'). This will match any one character
/// that is not an 'a'.
template<typename Literal>
inline typename detail::as_xpr_type<Literal>::type
as_xpr(Literal const &literal)
{
    return detail::as_xpr_type<Literal>::call(expr);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Makes a sub-expression case-insensitive.
///
/// Use icase() to make a sub-expression case-insensitive. For instance,
/// "foo" >> icase(set['b'] >> "ar") will match "foo" exactly followed by
/// "bar" irrespective of case.
template<typename Expr>
inline typename proto::meta::binary_expr<
    modifier_tag
  , detail::icase_modifier
  , typename detail::as_xpr_type<Expr>::type
>::type const
icase(Expr const &expr)
{
    detail::icase_modifier mod;
    typename proto::meta::binary_expr<
        modifier_tag
      , detail::icase_modifier
      , typename detail::as_xpr_type<Expr>::type
    >::type that = {mod, as_xpr(expr)};
    return that;
}
#endif

///////////////////////////////////////////////////////////////////////////////
/// \brief Embed a regex object by reference.
///
/// \param rex The basic_regex object to embed by reference.
template<typename BidiIter>
inline typename proto::meta::terminal<detail::regex_placeholder<BidiIter, true> >::type const
by_ref(basic_regex<BidiIter> const &rex)
{
    typedef detail::core_access<BidiIter> access;
    shared_ptr<detail::regex_impl<BidiIter> > impl = access::get_regex_impl(rex);
    return proto::make_terminal(detail::regex_placeholder<BidiIter, true>(impl));
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Match a range of characters.
///
/// Match any character in the range [ch_min, ch_max].
///
/// \param ch_min The lower end of the range to match.
/// \param ch_max The upper end of the range to match.
template<typename Char>
inline typename proto::meta::terminal<detail::range_placeholder<Char> >::type const
range(Char ch_min, Char ch_max)
{
    typename proto::meta::terminal<detail::range_placeholder<Char> >::type that = {{ch_min, ch_max, false}};
    return that;
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Make a sub-expression optional. Equivalent to !as_xpr(expr).
///
/// \param expr The sub-expression to make optional.
template<typename Expr>
inline typename proto::meta::unary_expr<
    proto::logical_not_tag
  , typename detail::as_xpr_type<Expr>::type
>::type const
optional(Expr const &expr)
{
    typename proto::meta::unary_expr<
        proto::logical_not_tag
      , typename detail::as_xpr_type<Expr>::type
    >::type that = {as_xpr(expr)};
    return that;
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Repeat a sub-expression multiple times.
///
/// There are two forms of the repeat\<\>() function template. To match a
/// sub-expression N times, use repeat\<N\>(expr). To match a sub-expression
/// from M to N times, use repeat\<M,N\>(expr).
///
/// The repeat\<\>() function creates a greedy quantifier. To make the quantifier
/// non-greedy, apply the unary minus operator, as in -repeat\<M,N\>(expr).
///
/// \param expr The sub-expression to repeat.
template<unsigned int Min, unsigned int Max, typename Expr>
inline typename proto::meta::unary_expr
<
    detail::generic_quant_tag<Min, Max>
  , typename detail::as_xpr_type<Expr>::type
>::type const
repeat(Expr const &expr)
{
    typename proto::meta::unary_expr
    <
        detail::generic_quant_tag<Min, Max>
      , typename detail::as_xpr_type<Expr>::type
    >::type that = {as_xpr(expr)};
    return that;
}

/// \overload
///
template<unsigned int Count, typename Xpr2>
inline typename proto::meta::unary_expr
<
    detail::generic_quant_tag<Count, Count>
  , typename detail::as_xpr_type<Xpr2>::type
>::type const
repeat(Xpr2 const &expr)
{
    typename proto::meta::unary_expr
    <
        detail::generic_quant_tag<Count, Count>
      , typename detail::as_xpr_type<Xpr2>::type
    >::type that = {as_xpr(expr)};
    return that;
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Create an independent sub-expression.
///
/// Turn off back-tracking for a sub-expression. Any branches or repeats within
/// the sub-expression will match only one way, and no other alternatives are
/// tried.
///
/// \attention keep(expr) is equivalent to the perl (?>...) extension.
///
/// \param expr The sub-expression to modify.
template<typename Expr>
inline typename proto::meta::unary_expr
<
    detail::keeper_tag
  , typename detail::as_xpr_type<Expr>::type
>::type const
keep(Expr const &expr)
{
    typename proto::meta::unary_expr
    <
        detail::keeper_tag
      , typename detail::as_xpr_type<Expr>::type
    >::type that = {as_xpr(expr)};
    return that;
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Look-ahead assertion.
///
/// before(expr) succeeds if the expr sub-expression would match at the current
/// position in the sequence, but expr is not included in the match. For instance,
/// before("foo") succeeds if we are before a "foo". Look-ahead assertions can be
/// negated with the bit-compliment operator.
///
/// \attention before(expr) is equivalent to the perl (?=...) extension.
/// ~before(expr) is a negative look-ahead assertion, equivalent to the
/// perl (?!...) extension.
///
/// \param expr The sub-expression to put in the look-ahead assertion.
template<typename Expr>
inline typename proto::meta::unary_expr
<
    detail::lookahead_tag<true>
  , typename detail::as_xpr_type<Expr>::type
>::type const
before(Expr const &expr)
{
    typename proto::meta::unary_expr
    <
        detail::lookahead_tag<true>
      , typename detail::as_xpr_type<Expr>::type
    >::type that = {as_xpr(expr)};
    return that;
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Look-behind assertion.
///
/// after(expr) succeeds if the expr sub-expression would match at the current
/// position minus N in the sequence, where N is the width of expr. expr is not included in
/// the match. For instance,  after("foo") succeeds if we are after a "foo". Look-behind
/// assertions can be negated with the bit-complement operator.
///
/// \attention after(expr) is equivalent to the perl (?<=...) extension.
/// ~after(expr) is a negative look-behind assertion, equivalent to the
/// perl (?<!...) extension.
///
/// \param expr The sub-expression to put in the look-ahead assertion.
///
/// \pre expr cannot match a variable number of characters.
template<typename Expr>
inline typename proto::meta::unary_expr
<
    detail::lookbehind_tag<true>
  , typename detail::as_xpr_type<Expr>::type
>::type const
after(Expr const &expr)
{
    typename proto::meta::unary_expr
    <
        detail::lookbehind_tag<true>
      , typename detail::as_xpr_type<Expr>::type
    >::type that = {as_xpr(expr)};
    return that;
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Specify a regex traits or a std::locale.
///
/// imbue() instructs the regex engine to use the specified traits or locale
/// when matching the regex. The entire expression must use the same traits/locale.
/// For instance, the following specifies a locale for use with a regex:
///   std::locale loc;
///   sregex rx = imbue(loc)(+digit);
///
/// \param loc The std::locale or regex traits object.
template<typename Locale>
inline detail::modifier_op<detail::locale_modifier<Locale> > const
imbue(Locale const &loc)
{
    detail::modifier_op<detail::locale_modifier<Locale> > mod =
    {
        detail::locale_modifier<Locale>(loc)
      , regex_constants::ECMAScript
    };
    return mod;
}


namespace detail
{
    inline void ignore_unused_regex_primitives()
    {
        ignore_unused(repeat_max);
        ignore_unused(inf);
        ignore_unused(epsilon);
        ignore_unused(nil);
        ignore_unused(alnum);
        ignore_unused(bos);
        ignore_unused(eos);
        ignore_unused(bol);
        ignore_unused(eol);
        ignore_unused(bow);
        ignore_unused(eow);
        ignore_unused(_b);
        ignore_unused(_w);
        ignore_unused(_d);
        ignore_unused(_s);
        ignore_unused(_n);
        ignore_unused(_ln);
        ignore_unused(_);
        ignore_unused(self);
        ignore_unused(set);
        ignore_unused(s0);
        ignore_unused(s1);
        ignore_unused(s2);
        ignore_unused(s3);
        ignore_unused(s4);
        ignore_unused(s5);
        ignore_unused(s6);
        ignore_unused(s7);
        ignore_unused(s8);
        ignore_unused(s9);
    }
}

}} // namespace boost::xpressive

#endif

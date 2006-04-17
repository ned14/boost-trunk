///////////////////////////////////////////////////////////////////////////////
/// \file regex_compiler.hpp
/// Contains the definition of regex_compiler, a factory for building regex objects
/// from strings.
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_REGEX_COMPILER_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_REGEX_COMPILER_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/xpressive/basic_regex.hpp>
#include <boost/xpressive/detail/dynamic/parser.hpp>
#include <boost/xpressive/detail/dynamic/parse_charset.hpp>
#include <boost/xpressive/detail/dynamic/parser_enum.hpp>
#include <boost/xpressive/detail/dynamic/parser_traits.hpp>
#include <boost/xpressive/detail/core/linker.hpp>
#include <boost/xpressive/detail/core/optimize.hpp>

namespace boost { namespace xpressive
{

///////////////////////////////////////////////////////////////////////////////
// regex_compiler
//
/// \brief Class template regex_compiler is a factory for building basic_regex objects from a string.
///
/// Class template regex_compiler is used to construct a basic_regex object from a string. The string
/// should contain a valid regular expression. You can imbue a regex_compiler object with a locale,
/// after which all basic_regex objects created with that regex_compiler object will use that locale.
/// After creating a regex_compiler object, and optionally imbueing it with a locale, you can call the
/// compile() method to construct a basic_regex object, passing it the string representing the regular
/// expression. You can call compile() multiple times on the same regex_compiler object. Two basic_regex
/// objects compiled from the same string will have different regex_id's.
template<typename BidiIter, typename RegexTraits, typename CompilerTraits>
struct regex_compiler
{
    typedef BidiIter iterator_type;
    typedef typename iterator_value<BidiIter>::type char_type;
    typedef std::basic_string<char_type> string_type;
    typedef regex_constants::syntax_option_type flag_type;
    typedef RegexTraits traits_type;
    typedef typename traits_type::char_class_type char_class_type;
    typedef typename traits_type::locale_type locale_type;

    explicit regex_compiler(RegexTraits const &traits = RegexTraits())
      : mark_count_(0)
      , hidden_mark_count_(0)
      , traits_(traits)
      , upper_(0)
    {
        this->upper_ = lookup_classname(this->rxtraits(), "upper");
        BOOST_ASSERT(0 != this->upper_);
    }

    ///////////////////////////////////////////////////////////////////////////
    // imbue
    /// Specify the locale to be used by a regex_compiler.
    ///
    /// \param loc The locale that this regex_compiler should use.
    /// \return The previous locale.
    locale_type imbue(locale_type loc)
    {
        locale_type oldloc = this->traits_.imbue(loc);
        this->upper_ = lookup_classname(this->rxtraits(), "upper");
        BOOST_ASSERT(0 != this->upper_);
        return oldloc;
    }

    ///////////////////////////////////////////////////////////////////////////
    // getloc
    /// Get the locale used by a regex_compiler.
    ///
    /// \param loc The locale that this regex_compiler uses.
    locale_type getloc() const
    {
        return this->traits_.getloc();
    }

    ///////////////////////////////////////////////////////////////////////////
    // compile
    /// Builds a basic_regex object from a std::string.
    ///
    /// \param  pat A std::string containing the regular expression pattern.
    /// \param  flags Optional bitmask that determines how the pat string is interpreted. (See syntax_option_type.)
    /// \return A basic_regex object corresponding to the regular expression represented by the string.
    /// \pre    The std::string pat contains a valid string-based representation of a regular expression.
    /// \throw  regex_error when the string has invalid regular expression syntax.
    basic_regex<BidiIter> compile(string_type pat, flag_type flags = regex_constants::ECMAScript)
    {
        this->reset();
        this->traits_.flags(flags);

        string_iterator begin = pat.begin(), end = pat.end();

        // at the top level, a regex is a sequence of alternates
        detail::sequence<BidiIter> seq = this->parse_alternates(begin, end);
        detail::ensure(begin == end, regex_constants::error_paren, "mismatched parenthesis");

        // terminate the sequence
        seq += detail::make_dynamic<BidiIter>(detail::end_matcher());

        // bundle the regex information into a regex_impl object
        basic_regex<BidiIter> rex;
        shared_ptr<detail::regex_impl<BidiIter> > const &impl = detail::core_access<BidiIter>::get_regex_impl(rex);
        detail::common_compile(seq.xpr().matchable(), *impl, this->rxtraits());

        impl->traits_.reset(new RegexTraits(this->rxtraits()));
        impl->mark_count_ = this->mark_count_;
        impl->hidden_mark_count_ = this->hidden_mark_count_;

        return rex;
    }

private:

    typedef typename string_type::const_iterator string_iterator;
    typedef detail::escape_value<char_type, char_class_type> escape_value;
    typedef detail::alternate_matcher<detail::alternates_vector<BidiIter>, RegexTraits> alternate_matcher;

    ///////////////////////////////////////////////////////////////////////////
    // reset
    /// INTERNAL ONLY
    void reset()
    {
        this->mark_count_ = 0;
        this->hidden_mark_count_ = 0;
        this->traits_.flags(regex_constants::ECMAScript);
    }

    ///////////////////////////////////////////////////////////////////////////
    // regex_traits
    /// INTERNAL ONLY
    traits_type &rxtraits()
    {
        return this->traits_.traits();
    }

    ///////////////////////////////////////////////////////////////////////////
    // regex_traits
    /// INTERNAL ONLY
    traits_type const &rxtraits() const
    {
        return this->traits_.traits();
    }

    ///////////////////////////////////////////////////////////////////////////
    // parse_alternates
    /// INTERNAL ONLY
    detail::sequence<BidiIter> parse_alternates(string_iterator &begin, string_iterator end)
    {
        using namespace regex_constants;
        int count = 0;
        string_iterator tmp = begin;
        detail::sequence<BidiIter> seq;

        do switch(++count)
        {
        case 1:
            seq = this->parse_sequence(tmp, end);
            break;
        case 2:
            seq = detail::make_dynamic<BidiIter>(alternate_matcher()) | seq;
            // fall-through
        default:
            seq |= this->parse_sequence(tmp, end);
        }
        while((begin = tmp) != end && token_alternate == this->traits_.get_token(tmp, end));

        return seq;
    }

    ///////////////////////////////////////////////////////////////////////////
    // parse_group
    /// INTERNAL ONLY
    detail::sequence<BidiIter> parse_group(string_iterator &begin, string_iterator end)
    {
        using namespace regex_constants;
        int mark_nbr = 0;
        bool keeper = false;
        bool lookahead = false;
        bool lookbehind = false;
        bool negative = false;

        detail::sequence<BidiIter> seq, seq_end;
        string_iterator tmp = string_iterator();

        syntax_option_type old_flags = this->traits_.flags();

        switch(this->traits_.get_group_type(begin, end))
        {
        case token_no_mark:
            // Don't process empty groups like (?:) or (?i)
            // BUGBUG this doesn't handle the degenerate (?:)+ correctly
            if(token_group_end == this->traits_.get_token(tmp = begin, end))
            {
                return this->parse_atom(begin = tmp, end);
            }
            break;

        case token_negative_lookahead:
            negative = true; // fall-through
        case token_positive_lookahead:
            lookahead = true;
            seq_end = detail::make_dynamic<BidiIter>(detail::true_matcher());
            break;

        case token_negative_lookbehind:
            negative = true; // fall-through
        case token_positive_lookbehind:
            lookbehind = true;
            seq_end = detail::make_dynamic<BidiIter>(detail::true_matcher());
            break;

        case token_independent_sub_expression:
            keeper = true;
            seq_end = detail::make_dynamic<BidiIter>(detail::true_matcher());
            break;

        case token_comment:
            while(detail::ensure(begin != end, error_paren, "mismatched parenthesis"))
            {
                switch(this->traits_.get_token(begin, end))
                {
                case token_group_end: return this->parse_atom(begin, end);
                case token_escape: detail::ensure(begin != end, error_escape, "incomplete escape sequence");
                case token_literal: ++begin;
                default:;
                }
            }
            break;

        default:
            mark_nbr = static_cast<int>(++this->mark_count_);
            seq = detail::make_dynamic<BidiIter>(detail::mark_begin_matcher(mark_nbr));
            seq_end = detail::make_dynamic<BidiIter>(detail::mark_end_matcher(mark_nbr));
            break;
        }

        // alternates
        seq += this->parse_alternates(begin, end);
        seq += seq_end;
        detail::ensure
        (
            begin != end && token_group_end == this->traits_.get_token(begin, end)
          , error_paren
          , "mismatched parenthesis"
        );

        typedef detail::shared_matchable<BidiIter> xpr_type;
        if(lookahead)
        {
            detail::lookahead_matcher<xpr_type> lookahead(seq.xpr(), negative, seq.pure());
            seq = detail::make_dynamic<BidiIter>(lookahead);
        }
        else if(lookbehind)
        {
            detail::lookbehind_matcher<xpr_type> lookbehind(seq.xpr(), seq.width().value(), negative, seq.pure());
            seq = detail::make_dynamic<BidiIter>(lookbehind);
        }
        else if(keeper) // independent sub-expression
        {
            detail::keeper_matcher<xpr_type> keeper(seq.xpr(), seq.pure());
            seq = detail::make_dynamic<BidiIter>(keeper);
        }

        // restore the modifiers
        this->traits_.flags(old_flags);
        return seq;
    }

    ///////////////////////////////////////////////////////////////////////////
    // parse_charset
    /// INTERNAL ONLY
    detail::sequence<BidiIter> parse_charset(string_iterator &begin, string_iterator end)
    {
        detail::compound_charset<traits_type> chset;

        // call out to a helper to actually parse the character set
        detail::parse_charset(begin, end, chset, this->traits_);

        return detail::make_charset_xpression<BidiIter>
        (
            chset
          , this->rxtraits()
          , this->traits_.flags()
        );
    }

    ///////////////////////////////////////////////////////////////////////////
    // parse_atom
    /// INTERNAL ONLY
    detail::sequence<BidiIter> parse_atom(string_iterator &begin, string_iterator end)
    {
        using namespace regex_constants;
        escape_value esc = { 0, 0, 0, detail::escape_char };
        string_iterator old_begin = begin;

        switch(this->traits_.get_token(begin, end))
        {
        case token_literal:
            return detail::make_literal_xpression<BidiIter>
            (
                this->parse_literal(begin, end), this->traits_.flags(), this->rxtraits()
            );

        case token_any:
            return detail::make_any_xpression<BidiIter>(this->traits_.flags(), this->rxtraits());

        case token_assert_begin_sequence:
            return detail::make_dynamic<BidiIter>(detail::assert_bos_matcher());

        case token_assert_end_sequence:
            return detail::make_dynamic<BidiIter>(detail::assert_eos_matcher());

        case token_assert_begin_line:
            return detail::make_assert_begin_line<BidiIter>(this->traits_.flags(), this->rxtraits());

        case token_assert_end_line:
            return detail::make_assert_end_line<BidiIter>(this->traits_.flags(), this->rxtraits());

        case token_assert_word_boundary:
            return detail::make_assert_word<BidiIter>(detail::word_boundary<true>(), this->rxtraits());

        case token_assert_not_word_boundary:
            return detail::make_assert_word<BidiIter>(detail::word_boundary<false>(), this->rxtraits());

        case token_assert_word_begin:
            return detail::make_assert_word<BidiIter>(detail::word_begin(), this->rxtraits());

        case token_assert_word_end:
            return detail::make_assert_word<BidiIter>(detail::word_end(), this->rxtraits());

        case token_escape:
            esc = this->parse_escape(begin, end);
            switch(esc.type_)
            {
            case detail::escape_mark:
                return detail::make_backref_xpression<BidiIter>
                (
                    esc.mark_nbr_, this->traits_.flags(), this->rxtraits()
                );
            case detail::escape_char:
                return detail::make_char_xpression<BidiIter>
                (
                    esc.ch_, this->traits_.flags(), this->rxtraits()
                );
            case detail::escape_class:
                return detail::make_posix_charset_xpression<BidiIter>
                (
                    esc.class_
                  , this->rxtraits().isctype(*begin++, this->upper_)
                  , this->traits_.flags()
                  , this->rxtraits()
                );
            }

        case token_group_begin:
            return this->parse_group(begin, end);

        case token_charset_begin:
            return this->parse_charset(begin, end);

        case token_invalid_quantifier:
            throw regex_error(error_badrepeat, "quantifier not expected");

        case token_quote_meta_begin:
            return detail::make_literal_xpression<BidiIter>
            (
                this->parse_quote_meta(begin, end), this->traits_.flags(), this->rxtraits()
            );

        case token_quote_meta_end:
            throw regex_error
            (
                error_escape
              , "found quote-meta end without corresponding quote-meta begin"
            );

        case token_end_of_pattern:
            break;

        default:
            begin = old_begin;
            break;
        }

        return detail::sequence<BidiIter>();
    }

    ///////////////////////////////////////////////////////////////////////////
    // parse_quant
    /// INTERNAL ONLY
    detail::sequence<BidiIter> parse_quant(string_iterator &begin, string_iterator end)
    {
        BOOST_ASSERT(begin != end);
        detail::quant_spec spec = { 0, 0, false, &this->hidden_mark_count_ };
        detail::sequence<BidiIter> seq = this->parse_atom(begin, end);

        // BUGBUG this doesn't handle the degenerate (?:)+ correctly
        if(!seq.empty() && begin != end && detail::quant_none != seq.quant())
        {
            if(this->traits_.get_quant_spec(begin, end, spec))
            {
                BOOST_ASSERT(spec.min_ <= spec.max_);

                if(0 == spec.max_) // quant {0,0} is degenerate -- matches nothing.
                {
                    seq = this->parse_quant(begin, end);
                }
                else
                {
                    seq.repeat(spec);
                }
            }
        }

        return seq;
    }

    ///////////////////////////////////////////////////////////////////////////
    // parse_sequence
    /// INTERNAL ONLY
    detail::sequence<BidiIter> parse_sequence(string_iterator &begin, string_iterator end)
    {
        detail::sequence<BidiIter> seq;

        while(begin != end)
        {
            detail::sequence<BidiIter> seq_quant = this->parse_quant(begin, end);

            // did we find a quantified atom?
            if(seq_quant.empty())
                break;

            // chain it to the end of the xpression sequence
            seq += seq_quant;
        }

        return seq;
    }

    ///////////////////////////////////////////////////////////////////////////
    // parse_literal
    //  scan ahead looking for char literals to be globbed together into a string literal
    /// INTERNAL ONLY
    string_type parse_literal(string_iterator &begin, string_iterator end)
    {
        using namespace regex_constants;
        BOOST_ASSERT(begin != end);
        BOOST_ASSERT(token_literal == this->traits_.get_token(begin, end));
        escape_value esc = { 0, 0, 0, detail::escape_char };
        string_type literal(1, *begin);

        for(string_iterator prev = begin, tmp = ++begin; begin != end; prev = begin, begin = tmp)
        {
            detail::quant_spec spec = { 0, 0, false, &this->hidden_mark_count_ };
            if(this->traits_.get_quant_spec(tmp, end, spec))
            {
                if(literal.size() != 1)
                {
                    begin = prev;
                    literal.erase(literal.size() - 1);
                }
                return literal;
            }
            else switch(this->traits_.get_token(tmp, end))
            {
            case token_escape:
                esc = this->parse_escape(tmp, end);
                if(detail::escape_char != esc.type_) return literal;
                literal += esc.ch_;
                break;
            case token_literal:
                literal += *tmp++;
                break;
            default:
                return literal;
            }
        }

        return literal;
    }

    ///////////////////////////////////////////////////////////////////////////
    // parse_quote_meta
    //  scan ahead looking for char literals to be globbed together into a string literal
    /// INTERNAL ONLY
    string_type parse_quote_meta(string_iterator &begin, string_iterator end)
    {
        using namespace regex_constants;
        string_iterator old_begin = begin, old_end;
        while(end != (old_end = begin))
        {
            switch(this->traits_.get_token(begin, end))
            {
            case token_quote_meta_end: return string_type(old_begin, old_end);
            case token_escape: detail::ensure(begin != end, error_escape, "incomplete escape sequence");
            case token_literal: ++begin;
            default:;
            }
        }
        return string_type(old_begin, begin);
    }

    ///////////////////////////////////////////////////////////////////////////////
    // parse_escape
    /// INTERNAL ONLY
    escape_value parse_escape(string_iterator &begin, string_iterator end)
    {
        detail::ensure(begin != end, regex_constants::error_escape, "incomplete escape sequence");

        // first, check to see if this can be a backreference
        if(0 < this->rxtraits().value(*begin, 10))
        {
            // Parse at most 3 decimal digits.
            string_iterator tmp = begin;
            int mark_nbr = detail::toi(tmp, end, this->rxtraits(), 10, 999);

            // If the resulting number could conceivably be a backref, then it is.
            if(10 > mark_nbr || mark_nbr < static_cast<int>(this->mark_count_))
            {
                begin = tmp;
                escape_value esc = {0, mark_nbr, 0, detail::escape_mark};
                return esc;
            }
        }

        // Not a backreference, defer to the parse_escape helper
        return detail::parse_escape(begin, end, this->traits_);
    }

    std::size_t mark_count_;
    std::size_t hidden_mark_count_;
    CompilerTraits traits_;
    typename RegexTraits::char_class_type upper_;
};

}} // namespace boost::xpressive

#endif

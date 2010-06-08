/*
 *          Copyright Andrey Semashev 2007 - 2010.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#include <memory>
#include <limits>
#include <vector>
#include <iterator>
#include <stdexcept>
#include <boost/throw_exception.hpp>
#include <boost/checked_delete.hpp>
#include <boost/intrusive/slist.hpp>
#include <boost/intrusive/slist_hook.hpp>
#include <boost/intrusive/options.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma_uint.hpp>
#include <boost/spirit/include/karma_generate.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/date_time/detail/formatter.hpp>
#include <boost/date_time/string_convert.hpp>

namespace boost {

namespace date_time {

namespace aux {

namespace qi = boost::spirit::qi;
namespace karma = boost::spirit::karma;

namespace {

    //! A simple trait that allows to use charset-specific Qi parsers in a generic way
    template< typename CharT >
    struct charset_parsers;

#define BOOST_DATE_TIME_CHARSET_PARSERS\
    ((char_type, char_))\
    ((string_type, string))\
    ((alnum_type, alnum))\
    ((alpha_type, alpha))\
    ((blank_type, blank))\
    ((cntrl_type, cntrl))\
    ((digit_type, digit))\
    ((graph_type, graph))\
    ((print_type, print))\
    ((punct_type, punct))\
    ((space_type, space))\
    ((xdigit_type, xdigit))\
    ((no_case_type, no_case))\
    ((lower_type, lower))\
    ((upper_type, upper))\
    ((lowernum_type, lowernum))\
    ((uppernum_type, uppernum))

#define BOOST_DATE_TIME_DECLARE_CHARSET_PARSER(r, charset, parser)\
    static spirit::charset::BOOST_PP_TUPLE_ELEM(2, 0, parser) const& BOOST_PP_TUPLE_ELEM(2, 1, parser);

#define BOOST_DATE_TIME_DECLARE_CHARSET_PARSERS(charset)\
    BOOST_PP_SEQ_FOR_EACH(BOOST_DATE_TIME_DECLARE_CHARSET_PARSER, charset, BOOST_DATE_TIME_CHARSET_PARSERS)

#define BOOST_DATE_TIME_DEFINE_CHARSET_PARSER(r, params, parser)\
    spirit::BOOST_PP_TUPLE_ELEM(2, 1, params)::BOOST_PP_TUPLE_ELEM(2, 0, parser) const&\
        charset_parsers< BOOST_PP_TUPLE_ELEM(2, 0, params) >::BOOST_PP_TUPLE_ELEM(2, 1, parser) =\
            spirit::BOOST_PP_TUPLE_ELEM(2, 1, params)::BOOST_PP_TUPLE_ELEM(2, 1, parser);

#define BOOST_DATE_TIME_DEFINE_CHARSET_PARSERS(char_type, charset)\
    BOOST_PP_SEQ_FOR_EACH(BOOST_DATE_TIME_DEFINE_CHARSET_PARSER, (char_type, charset), BOOST_DATE_TIME_CHARSET_PARSERS)

    template< >
    struct charset_parsers< char >
    {
        BOOST_DATE_TIME_DECLARE_CHARSET_PARSERS(standard)
    };
    BOOST_DATE_TIME_DEFINE_CHARSET_PARSERS(char, standard)

#ifndef BOOST_NO_STD_WSTRING
    template< >
    struct charset_parsers< wchar_t >
    {
        BOOST_DATE_TIME_DECLARE_CHARSET_PARSERS(standard_wide)
    };
    BOOST_DATE_TIME_DEFINE_CHARSET_PARSERS(wchar_t, standard_wide)
#endif // BOOST_NO_STD_WSTRING

#undef BOOST_DATE_TIME_DEFINE_CHARSET_PARSERS
#undef BOOST_DATE_TIME_DEFINE_CHARSET_PARSER
#undef BOOST_DATE_TIME_DECLARE_CHARSET_PARSERS
#undef BOOST_DATE_TIME_DECLARE_CHARSET_PARSER
#undef BOOST_DATE_TIME_CHARSET_PARSERS

    //! The function appends a formatted integer to the end of the string
    template< typename CharT >
    inline void put(
        uint32_t val,
        unsigned int width,
        CharT leading_char,
        std::basic_string< CharT >& target)
    {
        CharT buf[std::numeric_limits< uint32_t >::digits10 + 2];
        CharT* p = buf;

        typedef karma::uint_generator< uint32_t, 10 > uint_gen;
        karma::generate(p, uint_gen(), val);
        const std::size_t len = p - buf;
        if (len < width)
            target.insert(target.end(), width - len, leading_char);
        target.append(buf, p);
    }

} // namespace

template< typename CharT >
struct formatter< CharT >::implementation
{
public:
    //! Base interface for formatter steps
    struct step_base :
        public intrusive::slist_base_hook< intrusive::tag< step_base > >
    {
        step_base() {}
        virtual ~step_base() {}
        virtual step_base* clone() const = 0;
        virtual void operator()(
            common_date_time const& dt,
            std::locale const& loc,
            string_type& target) = 0;

    private:
        step_base(step_base const&);
        step_base& operator= (step_base const&);
    };

    //! Final class of formatting steps
    template< typename T >
    class step :
        public step_base,
        public T
    {
    public:
        step() {}
        step(step const& that) : step_base(), T(static_cast< T const& >(that)) {}
        template< typename T1 >
        explicit step(T1 const& arg1) : step_base(), T(arg1) {}
        template< typename T1, typename T2 >
        explicit step(T1 const& arg1, T2 const& arg2) : step_base(), T(arg1, arg2) {}

        step_base* clone() const
        {
            return new step< T >(*this);
        }
        void operator()(common_date_time const& dt, std::locale const& loc, string_type& target)
        {
            T::operator() (dt, loc, target);
        }
    };

    //! A composite step that sequentially executes 3 steps interleaving with a delimiter character
    template< typename StepT1, typename StepT2, typename StepT3, char_type DelimiterV = 0 >
    struct delimited3
    {
        void operator()(common_date_time const& dt, std::locale const& loc, string_type& target)
        {
            StepT1()(dt, loc, target);
            if (DelimiterV)
                target.push_back(DelimiterV);
            StepT2()(dt, loc, target);
            if (DelimiterV)
                target.push_back(DelimiterV);
            StepT3()(dt, loc, target);
        }
    };

    //! The formatter appends a single character to the target string
    struct constant_char
    {
        explicit constant_char(char_type c) : m_Char(c)
        {
        }
        void operator()(common_date_time const&, std::locale const&, string_type& target)
        {
            target.push_back(m_Char);
        }

        char_type m_Char;
    };

    //! The formatter appends a fixed string to the target string
    struct constant
    {
        explicit constant(std::vector< char_type > const& lit) : m_Str(lit.begin(), lit.end())
        {
        }
        void operator()(common_date_time const&, std::locale const&, string_type& target)
        {
            target.append(m_Str);
        }

        string_type m_Str;
    };

    //! Formatter for year without the century
    struct short_year
    {
        void operator()(common_date_time const& dt, std::locale const&, string_type& target)
        {
            put(dt.get_tm().tm_year % 100, 2U, static_cast< char_type >('0'), target);
        }
    };

    //! Formatter for year
    struct long_year
    {
        void operator()(common_date_time const& dt, std::locale const&, string_type& target)
        {
            typedef karma::uint_generator< uint32_t, 10 > uint_gen;
            std::back_insert_iterator< string_type > it(target);
            karma::generate(
                it,
                uint_gen(),
                static_cast< uint32_t >(dt.get_tm().tm_year + 1900));
        }
    };

    //! Formatter for numeric month
    struct numeric_month
    {
        void operator()(common_date_time const& dt, std::locale const&, string_type& target)
        {
            put(dt.get_tm().tm_mon + 1, 2U, static_cast< char_type >('0'), target);
        }
    };

    //! Formatter for the day of month
    struct day
    {
        void operator()(common_date_time const& dt, std::locale const&, string_type& target)
        {
            put(dt.get_tm().tm_mday, 2U, static_cast< char_type >('0'), target);
        }
    };

    //! Formatter for the day of month with leading space
    struct day_leading_space
    {
        void operator()(common_date_time const& dt, std::locale const&, string_type& target)
        {
            put(dt.get_tm().tm_mday, 2U, static_cast< char_type >(' '), target);
        }
    };

    //  Various types of american date formats
    typedef delimited3< numeric_month, day, short_year, '/' > short_american_date;
    typedef delimited3< numeric_month, day, long_year, '/' > long_american_date;
    typedef delimited3< numeric_month, day, short_year, '.' > short_dotted_american_date;
    typedef delimited3< numeric_month, day, long_year, '.' > long_dotted_american_date;

    //  Various types of european date formats
    typedef delimited3< day, numeric_month, short_year, '.' > short_dotted_european_date;
    typedef delimited3< day, numeric_month, long_year, '.' > long_dotted_european_date;

    //  Various types of ISO date formats
    typedef delimited3< long_year, numeric_month, day > iso_date;
    typedef delimited3< long_year, numeric_month, day, '-' > iso_extended_date;

    //! Formatter for hours in 24-hour format
    struct hours24
    {
        void operator()(common_date_time const& dt, std::locale const&, string_type& target)
        {
            put(dt.get_tm().tm_hour % 24, 2U, static_cast< char_type >('0'), target);
        }
    };

    //! Formatter for hours in 12-hour format
    struct hours12
    {
        void operator()(common_date_time const& dt, std::locale const&, string_type& target)
        {
            uint32_t h = (dt.get_tm().tm_hour % 12) + 1;
            put(h, 2U, static_cast< char_type >('0'), target);
        }
    };

    //! Formatter for hours for time durations
    struct unrestricted_hours
    {
        void operator()(common_date_time const& dt, std::locale const&, string_type& target)
        {
            put(dt.get_tm().tm_hour, 2U, static_cast< char_type >('0'), target);
        }
    };

    //! Formatter for minutes
    struct minutes
    {
        void operator()(common_date_time const& dt, std::locale const&, string_type& target)
        {
            put(dt.get_tm().tm_min, 2U, static_cast< char_type >('0'), target);
        }
    };

    //! Formatter for seconds
    struct seconds
    {
        void operator()(common_date_time const& dt, std::locale const&, string_type& target)
        {
            put(dt.get_tm().tm_sec, 2U, static_cast< char_type >('0'), target);
        }
    };

    //! Formatter for fractional seconds
    struct fractional_seconds
    {
        void operator()(common_date_time const& dt, std::locale const&, string_type& target)
        {
            put(dt.fractional_seconds(), 6U, static_cast< char_type >('0'), target);
        }
    };

    //! Formatter for the AM/PM sign
    struct am_pm
    {
        void operator()(common_date_time const& dt, std::locale const&, string_type& target)
        {
            static const char_type am[3] = { 'A', 'M', 0 };
            static const char_type pm[3] = { 'P', 'M', 0 };
            target.append((dt.get_tm().tm_hour > 11) ? pm : am, 2U);
        }
    };

    //  Various time formats
    typedef delimited3< hours24, minutes, seconds, ':' > h24ms_time;
    typedef delimited3< hours12, minutes, seconds, ':' > h12ms_time;
    typedef delimited3< unrestricted_hours, minutes, seconds, ':' > default_duration;

    //! Sequence of elementary formatters
    typedef intrusive::slist<
        step_base,
        intrusive::base_hook< intrusive::slist_base_hook< intrusive::tag< step_base > > >,
        intrusive::constant_time_size< false >,
        intrusive::cache_last< true >
    > step_list;

private:
    step_list m_Steps;

public:
    implementation()
    {
    }
    implementation(implementation const& that)
    {
        try
        {
            typename step_list::const_iterator it = that.m_Steps.begin(), end = that.m_Steps.end();
            for (; it != end; ++it)
                m_Steps.push_back(*it->clone());
        }
        catch (...)
        {
            m_Steps.clear_and_dispose(checked_deleter< step_base >());
            throw;
        }
    }
    ~implementation()
    {
        m_Steps.clear_and_dispose(checked_deleter< step_base >());
    }

    void format(common_date_time const& dt, string_type& str, std::locale const& loc)
    {
        typename step_list::iterator it = m_Steps.begin(), end = m_Steps.end();
        for (; it != end; ++it)
            (*it)(dt, loc, str);
    }

    void add_string_literal(std::vector< char_type > const& lit)
    {
        step_base* p;
        if (lit.size() > 1)
            p = new step< constant >(lit);
        else
            p = new step< constant_char >(lit[0]);
        m_Steps.push_back(*p);
    }

    void add_percent()
    {
        m_Steps.push_back(*new step< constant_char >('%'));
    }

    template< typename T >
    void add()
    {
        m_Steps.push_back(*new step< T >());
    }

private:
    implementation& operator= (implementation const&);
};

namespace {

    //! String constants with format placeholders
    template< typename CharT >
    struct format_placeholders;

    template< >
    struct format_placeholders< char >
    {
        typedef char char_type;

        static const char_type* iso_date() { return "%Y%m%d"; }
        static const char_type* iso_extended_date() { return "%Y-%m-%d"; }
        static const char_type* explicit_short_american_date() { return "%m/%d/%y"; }
        static const char_type* explicit_short_dotted_american_date() { return "%m.%d.%y"; }
        static const char_type* explicit_long_american_date() { return "%m/%d/%Y"; }
        static const char_type* explicit_long_dotted_american_date() { return "%m.%d.%Y"; }
        static const char_type* explicit_short_dotted_european_date() { return "%d.%m.%y"; }
        static const char_type* explicit_long_dotted_european_date() { return "%d.%m.%Y"; }
        static const char_type* h24ms_time() { return "%H:%M:%S"; }
        static const char_type* h12ms_time() { return "%I:%M:%S"; }
        static const char_type* default_duration() { return "%O:%M:%S"; }

        static const char_type* percent() { return "%%"; }
        static const char_type* short_year() { return "%y"; }
        static const char_type* long_year() { return "%Y"; }
        static const char_type* numeric_month() { return "%m"; }
        static const char_type* day() { return "%d"; }
        static const char_type* day_leading_space() { return "%e"; }
        static const char_type* american_date() { return "%D"; }
        static const char_type* unrestricted_hours() { return "%O"; }
        static const char_type* hours24() { return "%H"; }
        static const char_type* hours12() { return "%I"; }
        static const char_type* minutes() { return "%M"; }
        static const char_type* seconds() { return "%S"; }
        static const char_type* fractional_seconds() { return "%f"; }
        static const char_type* am_pm() { return "%p"; }
    };

#ifndef BOOST_NO_STD_WSTRING
    template< >
    struct format_placeholders< wchar_t >
    {
        typedef wchar_t char_type;

        static const char_type* iso_date() { return L"%Y%m%d"; }
        static const char_type* iso_extended_date() { return L"%Y-%m-%d"; }
        static const char_type* explicit_short_american_date() { return L"%m/%d/%y"; }
        static const char_type* explicit_short_dotted_american_date() { return L"%m.%d.%y"; }
        static const char_type* explicit_long_american_date() { return L"%m/%d/%Y"; }
        static const char_type* explicit_long_dotted_american_date() { return L"%m.%d.%Y"; }
        static const char_type* explicit_short_dotted_european_date() { return L"%d.%m.%y"; }
        static const char_type* explicit_long_dotted_european_date() { return L"%d.%m.%Y"; }
        static const char_type* h24ms_time() { return L"%H:%M:%S"; }
        static const char_type* h12ms_time() { return L"%I:%M:%S"; }
        static const char_type* default_duration() { return L"%O:%M:%S"; }

        static const char_type* percent() { return L"%%"; }
        static const char_type* short_year() { return L"%y"; }
        static const char_type* long_year() { return L"%Y"; }
        static const char_type* numeric_month() { return L"%m"; }
        static const char_type* day() { return L"%d"; }
        static const char_type* day_leading_space() { return L"%e"; }
        static const char_type* american_date() { return L"%D"; }
        static const char_type* unrestricted_hours() { return L"%O"; }
        static const char_type* hours24() { return L"%H"; }
        static const char_type* hours12() { return L"%I"; }
        static const char_type* minutes() { return L"%M"; }
        static const char_type* seconds() { return L"%S"; }
        static const char_type* fractional_seconds() { return L"%f"; }
        static const char_type* am_pm() { return L"%p"; }
    };
#endif // BOOST_NO_STD_WSTRING

    //! Date and time format grammar
    template< typename CharT >
    struct date_time_grammar :
        public qi::grammar< const CharT* >
    {
        typedef CharT char_type;
        typedef typename formatter< char_type >::implementation collector;
        typedef qi::rule< const char_type* > rule_type;
        typedef void (collector::*callback_type)();
        typedef qi::symbols< char_type, callback_type > symbols_type;

        //! A simple mem_fun wrapper compatible with Boost.Phoenix
        struct mem_fun
        {
            template< typename, typename >
            struct result
            {
                typedef void type;
            };

            void operator() (callback_type fun, collector* p) const
            {
                (p->*fun)();
            }
        };

#define BOOST_DATE_TIME_FORMAT_PLACEHOLDERS\
    (short_year)\
    (long_year)\
    (numeric_month)\
    (day)\
    (day_leading_space)\
    (unrestricted_hours)\
    (hours24)\
    (hours12)\
    (minutes)\
    (seconds)\
    (fractional_seconds)\
    (am_pm)

#define BOOST_DATE_TIME_ADD_STEP(r, data, step)\
    (constants::step (), &collector::BOOST_NESTED_TEMPLATE add< typename collector::step >)

        explicit date_time_grammar(collector* p, bool& is_complete) :
            date_time_grammar::base_type(m_Start)
        {
            typedef charset_parsers< char_type > charset;
            typedef format_placeholders< char_type > constants;
            namespace args = phoenix::arg_names;

            // These templates are used often, so for sake of performance
            // they are recognized and replaced with a single formatting step
            m_PredefinedTemplates.add
                (constants::explicit_short_american_date(),
                    &collector::BOOST_NESTED_TEMPLATE add< typename collector::short_american_date >)
                (constants::explicit_long_american_date(),
                    &collector::BOOST_NESTED_TEMPLATE add< typename collector::long_american_date >)
                (constants::explicit_short_dotted_american_date(),
                    &collector::BOOST_NESTED_TEMPLATE add< typename collector::short_dotted_american_date >)
                (constants::explicit_long_dotted_american_date(),
                    &collector::BOOST_NESTED_TEMPLATE add< typename collector::long_dotted_american_date >)
                (constants::explicit_short_dotted_european_date(),
                    &collector::BOOST_NESTED_TEMPLATE add< typename collector::short_dotted_european_date >)
                (constants::explicit_long_dotted_european_date(),
                    &collector::BOOST_NESTED_TEMPLATE add< typename collector::long_dotted_european_date >)
                (constants::iso_date(),
                    &collector::BOOST_NESTED_TEMPLATE add< typename collector::iso_date >)
                (constants::iso_extended_date(),
                    &collector::BOOST_NESTED_TEMPLATE add< typename collector::iso_extended_date >)
                (constants::h24ms_time(),
                    &collector::BOOST_NESTED_TEMPLATE add< typename collector::h24ms_time >)
                (constants::h12ms_time(),
                    &collector::BOOST_NESTED_TEMPLATE add< typename collector::h12ms_time >)
                (constants::default_duration(),
                    &collector::BOOST_NESTED_TEMPLATE add< typename collector::default_duration >)
                ;

            m_Placeholders.add
                (constants::percent(), &collector::add_percent)
                (constants::american_date(),
                    &collector::BOOST_NESTED_TEMPLATE add< typename collector::short_american_date >)
                BOOST_PP_SEQ_FOR_EACH(BOOST_DATE_TIME_ADD_STEP, ~, BOOST_DATE_TIME_FORMAT_PLACEHOLDERS)
                ;

            m_Start =
            *(
                m_PredefinedTemplates[phoenix::bind(mem_fun(), phoenix::at_c< 0 >(args::_1), p)] |
                m_Placeholders[phoenix::bind(mem_fun(), phoenix::at_c< 0 >(args::_1), p)] |
                (+(charset::char_ - charset::char_(static_cast< char_type >('%'))))
                    [phoenix::bind(&collector::add_string_literal, p, phoenix::at_c< 0 >(args::_1))] |
                // If it comes to this, then some placeholder is not recognized
                charset::char_(static_cast< char_type >('%'))
                    [phoenix::ref(is_complete) = false, phoenix::bind(&collector::add_percent, p)]
            );
        }

#undef BOOST_DATE_TIME_ADD_STEP
#undef BOOST_DATE_TIME_FORMAT_PLACEHOLDERS

    private:
        //! Starting rule for the parser
        rule_type m_Start;
        //! Formatting placeholders
        symbols_type m_Placeholders;
        //! Predefined date/time formats
        symbols_type m_PredefinedTemplates;
    };

} // namespace

//! Default constructor. Creates an empty formatter that does nothing.
template< typename CharT >
formatter< CharT >::formatter() : m_pImpl(new implementation())
{
}

//! Copy constructor. Performs a deep copying.
template< typename CharT >
formatter< CharT >::formatter(formatter const& that) :
    m_pImpl(new implementation(*that.m_pImpl))
{
}

//! Destructor
template< typename CharT >
formatter< CharT >::~formatter()
{
    delete m_pImpl;
}

//! Assignment
template< typename CharT >
formatter< CharT >& formatter< CharT >::operator= (formatter const& that)
{
    implementation* p = new implementation(*that.m_pImpl);
    delete m_pImpl;
    m_pImpl = p;
    return *this;
}

//! Formatting operator
template< typename CharT >
void formatter< CharT >::operator()(
    common_date_time const& dt, string_type& str, std::locale const& loc) const
{
    m_pImpl->format(dt, str, loc);
}

//! Parses the format string and constructs the formatter
template< typename CharT >
formatter< CharT > formatter< CharT >::parse(const char_type* b, const char_type* e)
{
    formatter< CharT > formatter;
    bool is_complete = true;
    date_time_grammar< CharT > grammar(formatter.m_pImpl, is_complete);

    const char_type* p = b;
    if (!qi::parse(p, e, grammar) || p != e)
    {
        std::string descr = "Could not parse date/time format specification \"";
        descr.append(date_time::convert_string_type< char_type, char >(string_type(b, e)));
        descr.append("\", stopped at position ");
        std::back_insert_iterator< std::string > it(descr);
        karma::generate(it, karma::uint_, static_cast< std::size_t >(p - b));
        BOOST_THROW_EXCEPTION(std::runtime_error(descr));
    }

    if (!is_complete)
    {
        // The parser did not recognize all placeholders. We'll have to pass
        // the formatter output to the standard facet to complete the formatting.
    }

    return formatter;
}

template class BOOST_DATE_TIME_DECL formatter< char >;

#ifndef BOOST_NO_STD_WSTRING
template class BOOST_DATE_TIME_DECL formatter< wchar_t >;
#endif

} // namespace aux

} // namespace date_time

} // namespace boost

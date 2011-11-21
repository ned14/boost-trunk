//
//  (C) Copyright Howard Hinnant
//  (C) Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//

#ifndef BOOST_CHRONO_IO_DURATION_UNITS_HPP
#define BOOST_CHRONO_IO_DURATION_UNITS_HPP

#include <boost/chrono/config.hpp>
#include <boost/ratio/ratio_io.hpp>
#include <boost/chrono/duration.hpp>
#include <boost/chrono/io/duration_style.hpp>
#include <boost/chrono/io/ios_base_state.hpp>
#include <string>
#include <ios>
#include <locale>
#include <algorithm>

namespace boost
{
  namespace chrono
  {
    class rt_ratio
    {
    public:
      template <typename Period>
      rt_ratio(Period const&) :
        num(Period::type::num), den(Period::type::den)
      {
      }

      rt_ratio(intmax_t n = 0, intmax_t d = 0) :
        num(n), den(d)
      {
      }

      intmax_t num;
      intmax_t den;
    };

    /**
     * @c duration_units facet gives useful information about the duration units,
     * as the number of plural forms, the plural form associated to a duration,
     * the text associated to a plural form and a duration's period,
     */
    template <typename CharT = char>
    class duration_units: public std::locale::facet
    {
    public:
      /**
       * Type of character the facet is instantiated on.
       */
      typedef CharT char_type;
      /**
       * Type of character string passed to member functions.
       */
      typedef std::basic_string<CharT> string_type;

      /**
       * Unique identifier for this type of facet.
       */
      static std::locale::id id;

      /**
       * Construct a @c duration_units facet.
       * @param refs
       * @Effects Construct a @c duration_units facet.
       * If the @c refs argument is @c 0 then destruction of the object is
       * delegated to the @c locale, or locales, containing it. This allows
       * the user to ignore lifetime management issues. On the other had,
       * if @c refs is @c 1 then the object must be explicitly deleted;
       * the @c locale will not do so. In this case, the object can be
       * maintained across the lifetime of multiple locales.
       */
      explicit duration_units(size_t refs = 0) :
        std::locale::facet(refs)
      {
      }

      /**
       * @effect calls the do_...
       * @return pointer to the start of valid [N/D] units.
       */
      const string_type* get_n_d_valid_units_start() const
      {
        return do_get_n_d_valid_units_start();
      }
      /**
       * @effect calls the do_...
       * @return pointer to the end of valid [N/D] units.
       */
      const string_type* get_n_d_valid_units_end() const
      {
        return do_get_n_d_valid_units_end();
      }

      /**
       * @effect calls the do_...
       * @return pointer to the start of valid units, symbol or prefix with its different plural forms.
       */
      const string_type* get_valid_units_start() const
      {
        return do_get_valid_units_start();
      }
      /**
       * @effect calls the do_...
       * @return pointer to the end of valid units.
       */
      const string_type* get_valid_units_end() const
      {
        return do_get_valid_units_end();
      }

      /**
       * @effect calls the do_...
       * @param k the found pointer to the [N/D] unit.
       * @return true if @c k matches a valid unit.
       */
      bool match_n_d_valid_unit(const string_type* k) const
      {
        return do_match_n_d_valid_unit(k);
      }
      /**
       * @param k the found pointer to the unit.
       * @effect calls the do_...
       * @Effects @c rt is set to the valid Period when the @c k matches a valid unit.
       * @return true if @c k matches a valid unit.
       */
      bool match_valid_unit(const string_type* k, rt_ratio& rt) const
      {
        return do_match_valid_unit(k, rt);
      }

      /**
       * @effect calls the do_...
       * @return the pattern to be used by default.
       */
      string_type get_pattern() const
      {
        return do_get_pattern();
      }
      /**
       * @effect calls the do_...
       * @return the unit associated to this duration.
       */
      template <typename Rep, typename Period>
      string_type get_unit(duration_style::type style, duration<Rep, Period> const& d) const
      {
        return do_get_unit(style, rt_ratio(Period()), static_cast<intmax_t>(d.count()));
      }
      /**
       * @effect calls the do_...
       * @return the [N/D] suffix unit associated to this duration.
       */
      template <typename Rep, typename Period>
      string_type get_n_d_unit(duration_style::type style, duration<Rep, Period> const& d) const
      {
        return do_get_n_d_unit(style, rt_ratio(Period()), static_cast<intmax_t>(d.count()));
      }

      /**
       * @effect calls the do_...
       * @return true if the unit associated to the given Period is named, false otherwise.
       */
      template <typename Period>
      bool is_named_unit() const
      {
        return do_is_named_unit(rt_ratio(Period()));
      }


    protected:

      /**
       * @Effects Destroys the facet
       */
      virtual ~duration_units()
      {
      }
      /**
       * @return the pattern to be used by default.
       */
      virtual string_type do_get_pattern() const=0;
      /**
       * @return pointer to the start of valid [N/D] units.
       */
      virtual const string_type* do_get_n_d_valid_units_start() const = 0;
      /**
       * @return pointer to the end of valid [N/D] units.
       */
      virtual const string_type* do_get_n_d_valid_units_end() const = 0;
      /**
       * @return pointer to the start of valid units, symbol or prefix with its different plural forms.
       */
      virtual const string_type* do_get_valid_units_start() const = 0;
      /**
       * @return pointer to the end of valid units.
       */
      virtual const string_type* do_get_valid_units_end() const = 0;
      /**
       * @param k the found pointer to the [N/D] unit.
       * @return true if @c k matches a valid unit.
       */
      virtual bool do_match_n_d_valid_unit(const string_type* k) const = 0;
      /**
       * @param k the found pointer to the unit.
       * @effect calls the do_...
       * @Effects @c rt is set to the valid Period when the @c k matches a valid unit.
       * @return true if @c k matches a valid unit.
       */
      virtual bool do_match_valid_unit(const string_type* k, rt_ratio& rt) const = 0;
      /**
       * @return the [N/D] suffix unit associated to this duration.
       */
      virtual string_type do_get_n_d_unit(duration_style::type style, rt_ratio rt, intmax_t v) const = 0;
      /**
       * @return the unit associated to this duration.
       */
      virtual string_type do_get_unit(duration_style::type style,rt_ratio rt, intmax_t v) const = 0;
      /**
       * @return true if the unit associated to the given Period is named, false otherwise.
       */
      virtual bool do_is_named_unit(rt_ratio rt) const =0;

    };

    template <typename CharT>
    std::locale::id duration_units<CharT>::id;

    /**
     * This class is used to define the strings for the default English
     *
     */
    template <typename CharT = char>
    class duration_units_default: public duration_units<CharT>
    {
    protected:
      static const std::size_t pfs_ = 2;

    public:
      /**
       * Type of character the facet is instantiated on.
       */
      typedef CharT char_type;
      /**
       * Type of character string passed to member functions.
       */
      typedef std::basic_string<CharT> string_type;

      /**
       * Construct a @c duration_units_default facet.
       * @param refs
       * @Effects Construct a @c duration_units_default facet.
       * If the @c refs argument is @c 0 then destruction of the object is
       * delegated to the @c locale, or locales, containing it. This allows
       * the user to ignore lifetime management issues. On the other had,
       * if @c refs is @c 1 then the object must be explicitly deleted;
       * the @c locale will not do so. In this case, the object can be
       * maintained across the lifetime of multiple locales.
       */
      explicit duration_units_default(size_t refs = 0) :
        duration_units<CharT> (refs)
      {
        string_type* it = n_d_valid_units_;
        it = fill_units(it, ratio<1> ());
        it = init_valid_units(valid_units_);
      }

      /**
       * Destroys the facet.
       */
      ~duration_units_default()
      {
      }

    protected:

      explicit duration_units_default(string_type*, size_t refs = 0) :
        duration_units<CharT> (refs)
      {
        string_type* it = n_d_valid_units_;
        it = fill_units(it, ratio<1> ());
        //it = init_valid_units(valid_units);
      }

      string_type* init_valid_units(string_type* it)
      {
        it = fill_units(it, atto());
        it = fill_units(it, femto());
        it = fill_units(it, pico());
        it = fill_units(it, nano());
        it = fill_units(it, micro());
        it = fill_units(it, milli());
        it = fill_units(it, centi());
        it = fill_units(it, deci());
        it = fill_units(it, deca());
        it = fill_units(it, hecto());
        it = fill_units(it, kilo());
        it = fill_units(it, mega());
        it = fill_units(it, giga());
        it = fill_units(it, tera());
        it = fill_units(it, peta());
        it = fill_units(it, exa());
        it = fill_units(it, ratio<1> ());
        it = fill_units(it, ratio<60> ());
        it = fill_units(it, ratio<3600> ());
        return it;
      }

      /**
       * @param k the found pointer to the [N/D] unit.
       * @return true if @c k matches a valid unit.
       */
      bool do_match_n_d_valid_unit(const string_type* k) const
      {
        std::size_t index = (k - n_d_valid_units_) / (pfs_ + 1);
        switch (index)
        {
        case 0:
          break;
        default:
          return false;
        }
        return true;
      }
      /**
       * @param k the found pointer to the unit.
       * @Effects @c rt is set to the valid Period when the @c k matches a valid unit.
       * @return true if @c k matches a valid unit.
       */
      bool do_match_valid_unit(const string_type* k, rt_ratio& rt) const
      {
        std::size_t index = (k - valid_units_) / (pfs_ + 1);
        switch (index)
        {
        case 0:
          rt = rt_ratio(atto());
          break;
        case 1:
          rt = rt_ratio(femto());
          break;
        case 2:
          rt = rt_ratio(pico());
          break;
        case 3:
          rt = rt_ratio(nano());
          break;
        case 4:
          rt = rt_ratio(micro());
          break;
        case 5:
          rt = rt_ratio(milli());
          break;
        case 6:
          rt = rt_ratio(centi());
          break;
        case 7:
          rt = rt_ratio(deci());
          break;
        case 8:
          rt = rt_ratio(deca());
          break;
        case 9:
          rt = rt_ratio(hecto());
          break;
        case 10:
          rt = rt_ratio(kilo());
          break;
        case 11:
          rt = rt_ratio(mega());
          break;
        case 12:
          rt = rt_ratio(giga());
          break;
        case 13:
          rt = rt_ratio(tera());
          break;
        case 14:
          rt = rt_ratio(peta());
          break;
        case 15:
          rt = rt_ratio(exa());
          break;
        case 16:
          rt = rt_ratio(ratio<1> ());
          break;
        case 17:
          rt = rt_ratio(ratio<60> ());
          break;
        case 18:
          rt = rt_ratio(ratio<3600> ());
          break;
        default:
          return false;
        }
        return true;
      }

      /**
       * @return pointer to the start of valid [N/D] units.
       */
      const string_type* do_get_n_d_valid_units_start() const
      {
        return n_d_valid_units_;
      }
      /**
       * @return pointer to the end of valid [N/D] units.
       */
      const string_type* do_get_n_d_valid_units_end() const
      {
        return n_d_valid_units_ + (pfs_ + 1);
      }

      /**
       * @return pointer to the start of valid units.
       */
      const string_type* do_get_valid_units_start() const
      {
        return valid_units_;
      }
      /**
       * @return pointer to the end of valid units.
       */
      const string_type* do_get_valid_units_end() const
      {
        return valid_units_ + 19 * (pfs_ + 1);
      }

      /**
       *
       * This facet names the units associated to the following periods:
       * atto,femto,pico,nano,micro,milli,centi,deci,ratio<1>,deca,hecto,kilo,mega,giga,tera,peta,exa,ratio<60> and ratio<3600>.
       * @return true if the unit associated to the given Period is named, false otherwise.
       */
      bool do_is_named_unit(rt_ratio rt) const
      {
        if (rt.num==1) {
          switch (rt.den)
          {
          case BOOST_RATIO_INTMAX_C(1):
          case BOOST_RATIO_INTMAX_C(10):
          case BOOST_RATIO_INTMAX_C(100):
          case BOOST_RATIO_INTMAX_C(1000):
          case BOOST_RATIO_INTMAX_C(1000000):
          case BOOST_RATIO_INTMAX_C(1000000000):
          case BOOST_RATIO_INTMAX_C(1000000000000):
          case BOOST_RATIO_INTMAX_C(1000000000000000):
          case BOOST_RATIO_INTMAX_C(1000000000000000000):
            return true;
          default:
            return false;
          }
        } else if (rt.den==1) {
          switch (rt.num)
          {
          case BOOST_RATIO_INTMAX_C(10):
          case BOOST_RATIO_INTMAX_C(60):
          case BOOST_RATIO_INTMAX_C(100):
          case BOOST_RATIO_INTMAX_C(1000):
          case BOOST_RATIO_INTMAX_C(3600):
          case BOOST_RATIO_INTMAX_C(1000000):
          case BOOST_RATIO_INTMAX_C(1000000000):
          case BOOST_RATIO_INTMAX_C(1000000000000):
          case BOOST_RATIO_INTMAX_C(1000000000000000):
          case BOOST_RATIO_INTMAX_C(1000000000000000000):
            return true;
          default:
            return false;
          }
        }
        return false;

      }

      /**
       * In English the suffix used after [N/D] is the one associated to the period ratio<1>.
       * @return the [N/D] suffix unit associated to this duration.
       */
      std::string do_get_n_d_unit(duration_style::type style, rt_ratio, intmax_t v) const
      {
        return do_get_unit(style, ratio<1>(), do_get_plural_form(v));
      }

      /**
       * @return the unit associated to this duration if it is named, "" otherwise.
       */
      std::string do_get_unit(duration_style::type style, rt_ratio rt, intmax_t v) const
      {
        if (rt.num==1) {
          switch (rt.den)
          {
          case BOOST_RATIO_INTMAX_C(1):
            return do_get_unit(style, ratio<1>(), do_get_plural_form(v));
          case BOOST_RATIO_INTMAX_C(10):
            return do_get_unit(style, deci(), do_get_plural_form(v));
          case BOOST_RATIO_INTMAX_C(100):
            return do_get_unit(style, centi(), do_get_plural_form(v));
          case BOOST_RATIO_INTMAX_C(1000):
            return do_get_unit(style, milli(), do_get_plural_form(v));
          case BOOST_RATIO_INTMAX_C(1000000):
            return do_get_unit(style, micro(), do_get_plural_form(v));
          case BOOST_RATIO_INTMAX_C(1000000000):
            return do_get_unit(style, nano(), do_get_plural_form(v));
          case BOOST_RATIO_INTMAX_C(1000000000000):
            return do_get_unit(style, pico(), do_get_plural_form(v));
          case BOOST_RATIO_INTMAX_C(1000000000000000):
            return do_get_unit(style, femto(), do_get_plural_form(v));
          case BOOST_RATIO_INTMAX_C(1000000000000000000):
            return do_get_unit(style, atto(), do_get_plural_form(v));
          default:
            ;
          }
        } else if (rt.den==1) {
          switch (rt.num)
          {
          case BOOST_RATIO_INTMAX_C(10):
             return do_get_unit(style, deca(), do_get_plural_form(v));
          case BOOST_RATIO_INTMAX_C(60):
            return do_get_unit(style, ratio<60>(), do_get_plural_form(v));
          case BOOST_RATIO_INTMAX_C(100):
             return do_get_unit(style, hecto(), do_get_plural_form(v));
           case BOOST_RATIO_INTMAX_C(1000):
             return do_get_unit(style, kilo(), do_get_plural_form(v));
           case BOOST_RATIO_INTMAX_C(3600):
             return do_get_unit(style, ratio<3600>(), do_get_plural_form(v));
           case BOOST_RATIO_INTMAX_C(1000000):
             return do_get_unit(style, mega(), do_get_plural_form(v));
           case BOOST_RATIO_INTMAX_C(1000000000):
             return do_get_unit(style, giga(), do_get_plural_form(v));
           case BOOST_RATIO_INTMAX_C(1000000000000):
             return do_get_unit(style, tera(), do_get_plural_form(v));
           case BOOST_RATIO_INTMAX_C(1000000000000000):
             return do_get_unit(style, peta(), do_get_plural_form(v));
           case BOOST_RATIO_INTMAX_C(1000000000000000000):
             return do_get_unit(style, exa(), do_get_plural_form(v));
           default:
             ;
           }
        }

        return "";

      }

      string_type do_get_pattern() const
      {
        static const CharT t[] =
        { '%', 'v', ' ', '%', 'u' };
        static const string_type pattern(t, t + sizeof (t) / sizeof (t[0]));

        return pattern;
      }

    protected:
      /**
       * @return the number of associated plural forms this facet manages.
       */
      virtual std::size_t do_get_plural_forms() const
      {
        return pfs_;
      }
      /**
       * Gets the associated plural form.
       * @param value the duration representation
       * @return the plural form associated to the @c value parameter. In English there are 2 plural forms
       * 0 singular (-1 or 1)
       * 1 plural for all others
       */
      virtual std::size_t do_get_plural_form(int_least64_t value) const
      {
        return (value == -1 || value == 1) ? 0 : 1;
      }

      /**
       * @param style the duration style.
       * @param period the period associated to the duration seconds.
       * @param pf the requested plural form.
       * @return if style is symbol returns "s", otherwise if pf is 0 return "second", if pf is 1 "seconds"
       */
      virtual string_type do_get_unit(duration_style_type style, ratio<1> , std::size_t pf) const
      {
        static const CharT t[] =
        { 's' };
        static const string_type symbol(t, t + sizeof (t) / sizeof (t[0]));
        static const CharT u[] =
        { 's', 'e', 'c', 'o', 'n', 'd' };
        static const string_type singular(u, u + sizeof (u) / sizeof (u[0]));
        static const CharT v[] =
        { 's', 'e', 'c', 'o', 'n', 'd', 's' };
        static const string_type plural(v, v + sizeof (v) / sizeof (v[0]));

        if (style == duration_style::symbol)
        {
          return symbol;
        }
        if (pf == 0)
        {
          return singular;
        }
        if (pf == 1)
        {
          return plural;
        }
        // assert
        throw "exception";
      }

      /**
       * @param style the duration style.
       * @param period the period associated to the duration minutes.
       * @param pf the requested plural form.
       * @return if style is symbol returns "min", otherwise if pf is 0 return "minute", if pf is 1 "minutes"
       */
      virtual string_type do_get_unit(duration_style_type style, ratio<60> , std::size_t pf) const
      {
        static const CharT t[] =
        { 'm', 'i', 'n' };
        static const string_type symbol(t, t + sizeof (t) / sizeof (t[0]));

        static const CharT u[] =
        { 'm', 'i', 'n', 'u', 't', 'e' };
        static const string_type singular(u, u + sizeof (u) / sizeof (u[0]));
        static const CharT v[] =
        { 'm', 'i', 'n', 'u', 't', 'e', 's' };
        static const string_type plural(v, v + sizeof (v) / sizeof (v[0]));

        if (style == duration_style::symbol) return symbol;
        if (pf == 0) return singular;
        if (pf == 1) return plural;
        // assert
        throw "exception";
      }

      /**
       * @param style the duration style.
       * @param period the period associated to the duration hours.
       * @param pf the requested plural form.
       * @return if style is symbol returns "h", otherwise if pf is 0 return "hour", if pf is 1 "hours"
       */
      virtual string_type do_get_unit(duration_style_type style, ratio<3600> , std::size_t pf) const
      {
        static const CharT t[] =
        { 'h' };
        static const string_type symbol(t, t + sizeof (t) / sizeof (t[0]));
        static const CharT u[] =
        { 'h', 'o', 'u', 'r' };
        static const string_type singular(u, u + sizeof (u) / sizeof (u[0]));
        static const CharT v[] =
        { 'h', 'o', 'u', 'r', 's' };
        static const string_type plural(v, v + sizeof (v) / sizeof (v[0]));

        if (style == duration_style::symbol) return symbol;
        if (pf == 0) return singular;
        if (pf == 1) return plural;
        // assert
        throw "exception";
      }
      /**
       * @param style the duration style.
       * @param u the period tag atto.
       * @param pf the requested plural form.
       * @return the concatenation of the prefix associated to @c period + the one associated to seconds.
       */
      virtual string_type do_get_unit(duration_style_type style, atto u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_unit(style, ratio<1> (), pf);
      }
      /**
       * @param style the duration style.
       * @param u the period tag femto.
       * @param pf the requested plural form.
       * @return the concatenation of the prefix associated to period @c u + the one associated to seconds.
       */
      virtual string_type do_get_unit(duration_style_type style, femto u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_unit(style, ratio<1> (), pf);
      }
      /**
       * @param style the duration style.
       * @param u the period tag femto.
       * @param pf the requested plural form.
       * @return the concatenation of the prefix associated to period @c u + the one associated to seconds.
       */
      virtual string_type do_get_unit(duration_style_type style, pico u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_unit(style, ratio<1> (), pf);
      }
      virtual string_type do_get_unit(duration_style_type style, nano u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_unit(style, ratio<1> (), pf);
      }
      virtual string_type do_get_unit(duration_style_type style, micro u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_unit(style, ratio<1> (), pf);
      }
      virtual string_type do_get_unit(duration_style_type style, milli u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_unit(style, ratio<1> (), pf);
      }
      virtual string_type do_get_unit(duration_style_type style, centi u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_unit(style, ratio<1> (), pf);
      }
      virtual string_type do_get_unit(duration_style_type style, deci u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_unit(style, ratio<1> (), pf);
      }
      virtual string_type do_get_unit(duration_style_type style, deca u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_unit(style, ratio<1> (), pf);
      }
      virtual string_type do_get_unit(duration_style_type style, hecto u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_unit(style, ratio<1> (), pf);
      }
      virtual string_type do_get_unit(duration_style_type style, kilo u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_unit(style, ratio<1> (), pf);
      }
      virtual string_type do_get_unit(duration_style_type style, mega u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_unit(style, ratio<1> (), pf);
      }
      virtual string_type do_get_unit(duration_style_type style, giga u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_unit(style, ratio<1> (), pf);
      }
      virtual string_type do_get_unit(duration_style_type style, tera u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_unit(style, ratio<1> (), pf);
      }
      virtual string_type do_get_unit(duration_style_type style, peta u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_unit(style, ratio<1> (), pf);
      }
      virtual string_type do_get_unit(duration_style_type style, exa u, std::size_t pf) const
      {
        return do_get_ratio_prefix(style, u) + do_get_unit(style, ratio<1> (), pf);
      }

    protected:

      /**
       * @param style the duration style.
       * @param u the period tag atto.
       * @return depending on the value of @c style return the ratio_string symbol or prefix.
       */
      virtual string_type do_get_ratio_prefix(duration_style_type style, atto) const
      {
        if (style == duration_style::symbol) return ratio_string<atto, CharT>::symbol();
        return ratio_string<atto, CharT>::prefix();
      }
      virtual string_type do_get_ratio_prefix(duration_style_type style, femto) const
      {
        if (style == duration_style::symbol) return ratio_string<femto, CharT>::symbol();
        return ratio_string<femto, CharT>::prefix();
      }
      virtual string_type do_get_ratio_prefix(duration_style_type style, pico) const
      {
        if (style == duration_style::symbol) return ratio_string<pico, CharT>::symbol();
        return ratio_string<pico, CharT>::prefix();
      }
      virtual string_type do_get_ratio_prefix(duration_style_type style, nano) const
      {
        if (style == duration_style::symbol) return ratio_string<nano, CharT>::symbol();
        return ratio_string<nano, CharT>::prefix();
      }
      virtual string_type do_get_ratio_prefix(duration_style_type style, micro) const
      {
        if (style == duration_style::symbol) return ratio_string<micro, CharT>::symbol();
        return ratio_string<micro, CharT>::prefix();
      }
      virtual string_type do_get_ratio_prefix(duration_style_type style, milli) const
      {
        if (style == duration_style::symbol) return ratio_string<milli, CharT>::symbol();
        return ratio_string<milli, CharT>::prefix();
      }
      virtual string_type do_get_ratio_prefix(duration_style_type style, centi) const
      {
        if (style == duration_style::symbol) return ratio_string<centi, CharT>::symbol();
        return ratio_string<centi, CharT>::prefix();
      }
      virtual string_type do_get_ratio_prefix(duration_style_type style, deci) const
      {
        if (style == duration_style::symbol) return ratio_string<deci, CharT>::symbol();
        return ratio_string<deci, CharT>::prefix();
      }
      virtual string_type do_get_ratio_prefix(duration_style_type style, deca) const
      {
        if (style == duration_style::symbol) return ratio_string<deca, CharT>::symbol();
        return ratio_string<deca, CharT>::prefix();
      }
      virtual string_type do_get_ratio_prefix(duration_style_type style, hecto) const
      {
        if (style == duration_style::symbol) return ratio_string<hecto, CharT>::symbol();
        return ratio_string<hecto, CharT>::prefix();
      }
      virtual string_type do_get_ratio_prefix(duration_style_type style, kilo) const
      {
        if (style == duration_style::symbol) return ratio_string<kilo, CharT>::symbol();
        return ratio_string<kilo, CharT>::prefix();
      }
      virtual string_type do_get_ratio_prefix(duration_style_type style, mega) const
      {
        if (style == duration_style::symbol) return ratio_string<mega, CharT>::symbol();
        return ratio_string<mega, CharT>::prefix();
      }
      virtual string_type do_get_ratio_prefix(duration_style_type style, giga) const
      {
        if (style == duration_style::symbol) return ratio_string<giga, CharT>::symbol();
        return ratio_string<giga, CharT>::prefix();
      }
      virtual string_type do_get_ratio_prefix(duration_style_type style, tera) const
      {
        if (style == duration_style::symbol) return ratio_string<tera, CharT>::symbol();
        return ratio_string<tera, CharT>::prefix();
      }
      virtual string_type do_get_ratio_prefix(duration_style_type style, peta) const
      {
        if (style == duration_style::symbol) return ratio_string<peta, CharT>::symbol();
        return ratio_string<peta, CharT>::prefix();
      }
      virtual string_type do_get_ratio_prefix(duration_style_type style, exa) const
      {
        if (style == duration_style::symbol) return ratio_string<exa, CharT>::symbol();
        return ratio_string<exa, CharT>::prefix();
      }

//      /**
//       *
//       * @param style
//       * @param pf
//       * @return the translation associated to the plural form given as parameter.
//       */
//      template <typename Period>
//      typename enable_if<detail::is_localizable<Period>, string_type>::type get_unit(duration_style_type style,
//          std::size_t pf) const
//      {
//        return do_get_unit(style, Period(), pf);
//      }

    protected:
      template <typename Period>
      string_type* fill_units(string_type* it, Period) const
      {
        std::size_t pfs = do_get_plural_forms();
        for (std::size_t pf = 0; pf < pfs; ++pf)
        {
          *it++ = do_get_unit(duration_style::prefix, Period(), pf);
        }
        *it++ = do_get_unit(duration_style::symbol, Period(), 0);
        return it;
      }

      string_type n_d_valid_units_[3];
      string_type valid_units_[19 * 3];

    };

  } // chrono

} // boost

#endif  // header

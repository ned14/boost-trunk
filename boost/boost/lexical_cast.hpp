#ifndef BOOST_LEXICAL_CAST_INCLUDED
#define BOOST_LEXICAL_CAST_INCLUDED

// Boost lexical_cast.hpp header  -------------------------------------------//
//
// See http://www.boost.org/ for most recent version including documentation.
// See end of this header for rights and permissions.
//
// what:  lexical_cast custom keyword cast
// who:   contributed by Kevlin Henney,
//        enhanced with contributions from Terje Slettebo,
//        with additional fixes and suggestions from Gennaro Prota,
//        Beman Dawes, Dave Abrahams, Daryle Walker, Peter Dimov,
//        Alexander Nasonov and other Boosters
// when:  November 2000, March 2003, June 2005, June 2006

#include <climits>
#include <cstddef>
#include <istream>
#include <locale>
#include <string>
#include <typeinfo>
#include <boost/config.hpp>
#include <boost/limits.hpp>
#include <boost/mpl/if.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/call_traits.hpp>
#include <boost/static_assert.hpp>

#ifdef BOOST_NO_STRINGSTREAM
#include <strstream>
#else
#include <sstream>
#endif

#if defined(BOOST_NO_STRINGSTREAM) || \
    defined(BOOST_NO_STD_WSTRING) || \
    defined(BOOST_NO_STD_LOCALE) 
#define DISABLE_WIDE_CHAR_SUPPORT
#endif

namespace boost
{
    // exception used to indicate runtime lexical_cast failure
    class bad_lexical_cast : public std::bad_cast
    {
    public:
        bad_lexical_cast() :
        source(&typeid(void)), target(&typeid(void))
        {
        }
        bad_lexical_cast(
            const std::type_info &source_type,
            const std::type_info &target_type) :
            source(&source_type), target(&target_type)
        {
        }
        const std::type_info &source_type() const
        {
            return *source;
        }
        const std::type_info &target_type() const
        {
            return *target;
        }
        virtual const char *what() const throw()
        {
            return "bad lexical cast: "
                   "source type value could not be interpreted as target";
        }
        virtual ~bad_lexical_cast() throw()
        {
        }
    private:
        const std::type_info *source;
        const std::type_info *target;
    };

    namespace detail // selectors for choosing stream character type
    {
        template<typename Type>
        struct stream_char
        {
            typedef char type;
        };

#ifndef DISABLE_WIDE_CHAR_SUPPORT
#ifndef BOOST_NO_INTRINSIC_WCHAR_T
        template<>
        struct stream_char<wchar_t>
        {
            typedef wchar_t type;
        };
#endif

        template<>
        struct stream_char<wchar_t *>
        {
            typedef wchar_t type;
        };

        template<>
        struct stream_char<const wchar_t *>
        {
            typedef wchar_t type;
        };

        template<>
        struct stream_char<std::wstring>
        {
            typedef wchar_t type;
        };
#endif

        template<typename TargetChar, typename SourceChar>
        struct widest_char
        {
            typedef TargetChar type;
        };

        template<>
        struct widest_char<char, wchar_t>
        {
            typedef wchar_t type;
        };
    }

    namespace detail // lcast_src_length
    {
        // Return max. length of string representation of Source;
        // 0 if unlimited (with exceptions for some types, see below).
        // Values with limited string representation are placed to
        // the buffer locally defined in lexical_cast function.
        // 1 is returned for few types such as CharT const* or
        // std::basic_string<CharT> that already have an internal
        // buffer ready to be reused by lexical_stream_limited_src.
        // Each specialization should have a correspondent operator<<
        // defined in lexical_stream_limited_src.
        template< class CharT  // A result of widest_char transformation.
                , class Source // Source type of lexical_cast.
                >
        struct lcast_src_length
        {
            BOOST_STATIC_CONSTANT(std::size_t, value = 0);
            // To check coverage, build the test with
            // bjam --v2 profile optimization=off
            static void check_coverage() {}
        };

        template<>
        struct lcast_src_length<char, bool>
        {
            BOOST_STATIC_CONSTANT(std::size_t, value = 1);
            static void check_coverage() {}
        };

        template<>
        struct lcast_src_length<char, char>
        {
            BOOST_STATIC_CONSTANT(std::size_t, value = 1);
            static void check_coverage() {}
        };

        // No specializations for:
        // lcast_src_length<char, signed char>
        // lcast_src_length<char, unsigned char>
        // lcast_src_length<char, signed char*>
        // lcast_src_length<char, unsigned char*>
        // lcast_src_length<char, signed char const*>
        // lcast_src_length<char, unsigned char const*>

#ifndef DISABLE_WIDE_CHAR_SUPPORT
        template<>
        struct lcast_src_length<wchar_t, bool>
        {
            BOOST_STATIC_CONSTANT(std::size_t, value = 1);
            static void check_coverage() {}
        };

        template<>
        struct lcast_src_length<wchar_t, char>
        {
            BOOST_STATIC_CONSTANT(std::size_t, value = 1);
            static void check_coverage() {}
        };

#ifndef BOOST_NO_INTRINSIC_WCHAR_T
        template<>
        struct lcast_src_length<wchar_t, wchar_t>
        {
            BOOST_STATIC_CONSTANT(std::size_t, value = 1);
            static void check_coverage() {}
        };
#endif
#endif

        template<>
        struct lcast_src_length<char, char const*>
        {
            BOOST_STATIC_CONSTANT(std::size_t, value = 1);
            static void check_coverage() {}
        };

        template<>
        struct lcast_src_length<char, char*>
        {
            BOOST_STATIC_CONSTANT(std::size_t, value = 1);
            static void check_coverage() {}
        };

#ifndef DISABLE_WIDE_CHAR_SUPPORT
        template<>
        struct lcast_src_length<wchar_t, wchar_t const*>
        {
            BOOST_STATIC_CONSTANT(std::size_t, value = 1);
            static void check_coverage() {}
        };

        template<>
        struct lcast_src_length<wchar_t, wchar_t*>
        {
            BOOST_STATIC_CONSTANT(std::size_t, value = 1);
            static void check_coverage() {}
        };
#endif

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        template<class CharT, class Traits, class Alloc>
        struct lcast_src_length< CharT, std::basic_string<CharT,Traits,Alloc> >
        {
            BOOST_STATIC_CONSTANT(std::size_t, value = 1);
            static void check_coverage() {}
        };
#else
        template<>
        struct lcast_src_length< char, std::basic_string<char> >
        {
            BOOST_STATIC_CONSTANT(std::size_t, value = 1);
            static void check_coverage() {}
        };

#ifndef DISABLE_WIDE_CHAR_SUPPORT
        template<>
        struct lcast_src_length< wchar_t, std::basic_string<wchar_t> >
        {
            BOOST_STATIC_CONSTANT(std::size_t, value = 1);
            static void check_coverage() {}
        };
#endif
#endif

        // Helper for integral types.
        // Notes on length calculation:
        // Max length for 32bit int with grouping "\1" and thousands_sep ',':
        // "-2,1,4,7,4,8,3,6,4,7"
        //  ^                    - is_signed
        //   ^                   - 1 digit not counted by digits10
        //    ^^^^^^^^^^^^^^^^^^ - digits10 * 2
        //
        // Constant is_specialized is used instead of constant 1
        // to prevent buffer overflow in a rare case when
        // <boost/limits.hpp> doesn't add missing specialization for
        // numeric_limits<T> for some integral type T.
        // When is_specialized is false, the whole expression is 0.
        template<class Source>
        struct lcast_src_length_integral
        {
#if !defined(__BORLANDC__) || __BORLANDC__ >= 0x581
            BOOST_STATIC_CONSTANT(std::size_t, value =
                  std::numeric_limits<Source>::is_signed +
                  std::numeric_limits<Source>::is_specialized + // == 1
                  std::numeric_limits<Source>::digits10 * 2
              );
#else
            BOOST_STATIC_CONSTANT(std::size_t, value = 156); // 256bit integers
#endif
        };

#define BOOST_AUX_LEXICAL_CAST_DEF1(CharT, T) template<>             \
    struct lcast_src_length<CharT, T> : lcast_src_length_integral<T> \
    { static void check_coverage() {} };

#ifdef DISABLE_WIDE_CHAR_SUPPORT
#define BOOST_AUX_LEXICAL_CAST_DEF(T) BOOST_AUX_LEXICAL_CAST_DEF1(char, T)
#else
#define BOOST_AUX_LEXICAL_CAST_DEF(T)          \
        BOOST_AUX_LEXICAL_CAST_DEF1(char, T)   \
        BOOST_AUX_LEXICAL_CAST_DEF1(wchar_t, T)
#endif

        BOOST_AUX_LEXICAL_CAST_DEF(short)
        BOOST_AUX_LEXICAL_CAST_DEF(unsigned short)
        BOOST_AUX_LEXICAL_CAST_DEF(int)
        BOOST_AUX_LEXICAL_CAST_DEF(unsigned int)
        BOOST_AUX_LEXICAL_CAST_DEF(long)
        BOOST_AUX_LEXICAL_CAST_DEF(unsigned long)
#if defined(BOOST_HAS_LONG_LONG)
        BOOST_AUX_LEXICAL_CAST_DEF(boost::ulong_long_type)
        BOOST_AUX_LEXICAL_CAST_DEF(boost::long_long_type )
#elif defined(BOOST_HAS_MS_INT64)
        BOOST_AUX_LEXICAL_CAST_DEF(unsigned __int64)
        BOOST_AUX_LEXICAL_CAST_DEF(         __int64)
#endif

#undef BOOST_AUX_LEXICAL_CAST_DEF
#undef BOOST_AUX_LEXICAL_CAST_DEF1

    }

    namespace detail // '0' and '-' constants
    {
        template<typename CharT> struct lcast_char_constants;

        template<>
        struct lcast_char_constants<char>
        {
            BOOST_STATIC_CONSTANT(char, zero  = '0');
            BOOST_STATIC_CONSTANT(char, minus = '-');
        };

#ifndef DISABLE_WIDE_CHAR_SUPPORT
        template<>
        struct lcast_char_constants<wchar_t>
        {
            BOOST_STATIC_CONSTANT(wchar_t, zero  = L'0');
            BOOST_STATIC_CONSTANT(wchar_t, minus = L'-');
        };
#endif
    }

    namespace detail // public access to basic_streambuf<CharT>::setg
    {
        template<typename CharT>
        class lexical_streambuf : public std::basic_streambuf<CharT>
        {
        public:
            void setbuf(CharT* start, CharT* finish)
            {
                this->setg(start, start, finish);
            }
        };
    }

    namespace detail // lcast_to_unsigned
    {
#if (defined _MSC_VER)
# pragma warning( push )
// C4146: unary minus operator applied to unsigned type, result still unsigned
# pragma warning( disable : 4146 )
#endif

        inline unsigned int lcast_to_unsigned(int value)
        {
            unsigned int uval = value;
            return value < 0 ? -uval : uval;
        }

        inline unsigned long lcast_to_unsigned(long value)
        {
            unsigned long uval = value;
            return value < 0 ? -uval : uval;
        }

#if defined(BOOST_HAS_LONG_LONG)
        inline boost::ulong_long_type lcast_to_unsigned(boost::long_long_type v)
        {
            boost::ulong_long_type uval = v;
            return v < 0 ? -uval : uval;
        }
#elif defined(BOOST_HAS_MS_INT64)
        inline unsigned __int64 lcast_to_unsigned(__int64 value)
        {
            unsigned __int64 uval = value;
            return value < 0 ? -uval : uval;
        }
#endif

#if (defined _MSC_VER)
# pragma warning( pop ) // C4146: unary minus operator applied to unsigned type, result still unsigned
#endif
    }

    namespace detail // lcast_put_unsigned
    {
        // I'd personally put lcast_put_unsigned in .cpp file if not
        // boost practice for header-only libraries (Alexander Nasonov).
        template<typename T, typename CharT>
        CharT* lcast_put_unsigned(T n, CharT* finish)
        {
            typedef std::numpunct<CharT> numpunct;

            CharT thousands_sep = 0;

#if !defined(MEASURE_LEXICAL_CAST_PERFORMANCE_WITHOUT_LOCALE_OVERHEAD)
            std::locale loc;
            numpunct const& np = BOOST_USE_FACET(numpunct, loc);
            std::string const& grouping = np.grouping();
            std::string::size_type const grouping_size = grouping.size();

            if(grouping_size)
                thousands_sep = np.thousands_sep();
#else // dead branch in production code
            char const* grouping = "";
            std::size_t grouping_size = 0;
#endif

            std::string::size_type group = 0; // current group number
            char last_grp_size = grouping[0] <= 0 ? CHAR_MAX : grouping[0];
            // a) Since grouping is const, grouping[grouping.size()] returns 0.
            // b) It's safe to assume here and below that CHAR_MAX
            //    is equivalent to unlimited grouping:
#if !defined(__BORLANDC__) || __BORLANDC__ >= 0x581
            BOOST_STATIC_ASSERT(std::numeric_limits<T>::digits10 < CHAR_MAX);
#endif

            char left = last_grp_size;

            do
            {
                if(left == 0)
                {
                    ++group;
                    if(group < grouping_size)
                    {
                        char const grp_size = grouping[group];
                        last_grp_size = grp_size <= 0 ? CHAR_MAX : grp_size;
                    }

                    left = last_grp_size;
                    --finish;
                    *finish = thousands_sep;
                }

                --left;
                --finish;
                int const digit = n % 10;
                int const cdigit = digit + lcast_char_constants<CharT>::zero;
                *finish = static_cast<char>(cdigit);
                n /= 10;
            } while(n);

            return finish;
        }
    }

    namespace detail // stream wrapper for handling lexical conversions
    {
        template<typename Target, typename Source>
        class lexical_stream
        {
        private:
            typedef typename widest_char<
                typename stream_char<Target>::type,
                typename stream_char<Source>::type>::type char_type;

        public:
            lexical_stream(char_type* = 0, char_type* = 0)
            {
                stream.unsetf(std::ios::skipws);

#if (defined _MSC_VER)
# pragma warning( push )
  // conditional expression is constant
# pragma warning( disable : 4127 )
#endif

                typedef std::numeric_limits<Target> t;
                typedef std::numeric_limits<Source> s;

                if(t::is_specialized)
                    stream.precision(1 + t::digits10);
                else if(s::is_specialized)
                    stream.precision(1 + s::digits10);

#if (defined _MSC_VER)
# pragma warning( pop )
#endif

            }
            ~lexical_stream()
            {
                #if defined(BOOST_NO_STRINGSTREAM)
                stream.freeze(false);
                #endif
            }
            bool operator<<(const Source &input)
            {
                return !(stream << input).fail();
            }
            template<typename InputStreamable>
            bool operator>>(InputStreamable &output)
            {
                return !is_pointer<InputStreamable>::value &&
                       stream >> output &&
                       stream.get() ==
#if defined(__GNUC__) && (__GNUC__<3) && defined(BOOST_NO_STD_WSTRING)
// GCC 2.9x lacks std::char_traits<>::eof().
// We use BOOST_NO_STD_WSTRING to filter out STLport and libstdc++-v3
// configurations, which do provide std::char_traits<>::eof().
    
                           EOF;
#else
                           std::char_traits<char_type>::eof();
#endif
            }
            bool operator>>(std::string &output)
            {
                #if defined(BOOST_NO_STRINGSTREAM)
                stream << '\0';
                #endif
                stream.str().swap(output);
                return true;
            }
            #ifndef DISABLE_WIDE_CHAR_SUPPORT
            bool operator>>(std::wstring &output)
            {
                stream.str().swap(output);
                return true;
            }
            #endif
        private:
            #if defined(BOOST_NO_STRINGSTREAM)
            std::strstream stream;
            #elif defined(BOOST_NO_STD_LOCALE)
            std::stringstream stream;
            #else
            std::basic_stringstream<char_type> stream;
            #endif
        };
    }

    namespace detail // optimized stream wrapper
    {
        // String representation of Source has an upper limit.
        template<typename CharT>
        class lexical_stream_limited_src
        {
            // A string representation of Source is written to [start, finish).
            // Currently, it is assumed that [start, finish) is big enough
            // to hold a string representation of any Source value.
            CharT* start;
            CharT* finish;

        private:

            static void widen_and_assign(char*p, char ch)
            {
                *p = ch;
            }

#ifndef DISABLE_WIDE_CHAR_SUPPORT
            static void widen_and_assign(wchar_t* p, char ch)
            {
                std::locale loc;
                *p = BOOST_USE_FACET(std::ctype<wchar_t>, loc).widen(ch);
            }

            static void widen_and_assign(wchar_t* p, wchar_t ch)
            {
                *p = ch;
            }

            static void widen_and_assign(char*, wchar_t ch); // undefined
#endif

            // Undefined:
            lexical_stream_limited_src(lexical_stream_limited_src const&);
            void operator=(lexical_stream_limited_src const&);

        public:

            lexical_stream_limited_src(CharT* start, CharT* finish)
              : start(start)
              , finish(finish)
            {}

        public: // output

            template<class Traits, class Alloc>
            bool operator<<(std::basic_string<CharT, Traits, Alloc> const& str)
            {
                start = const_cast<CharT*>(str.data());
                finish = start + str.length();
                return true;
            }

            bool operator<<(bool);
            bool operator<<(char);
#if !defined(DISABLE_WIDE_CHAR_SUPPORT) && !defined(BOOST_NO_INTRINSIC_WCHAR_T)
            bool operator<<(wchar_t);
#endif
            bool operator<<(CharT const*);
            bool operator<<(short);
            bool operator<<(int);
            bool operator<<(long);
            bool operator<<(unsigned short);
            bool operator<<(unsigned int);
            bool operator<<(unsigned long);
#if defined(BOOST_HAS_LONG_LONG)
            bool operator<<(boost::ulong_long_type);
            bool operator<<(boost::long_long_type );
#elif defined(BOOST_HAS_MS_INT64)
            bool operator<<(unsigned __int64);
            bool operator<<(         __int64);
#endif

        public: // input

            template<typename InputStreamable>
            bool operator>>(InputStreamable& output)
            {
#if (defined _MSC_VER)
# pragma warning( push )
  // conditional expression is constant
# pragma warning( disable : 4127 )
#endif
                if(is_pointer<InputStreamable>::value)
                    return false;

                lexical_streambuf<CharT> sb;
                sb.setbuf(start, finish);

                std::basic_istream<CharT> stream(&sb);
                stream.unsetf(std::ios::skipws);

                typedef std::numeric_limits<InputStreamable> limits;

                if(limits::is_specialized)
                    stream.precision(limits::digits10 + 1);
#if (defined _MSC_VER)
# pragma warning( pop )
#endif
                return stream >> output &&
                    stream.get() ==
#if defined(__GNUC__) && (__GNUC__<3) && defined(BOOST_NO_STD_WSTRING)
        // GCC 2.9x lacks std::char_traits<>::eof().
        // We use BOOST_NO_STD_WSTRING to filter out STLport and libstdc++-v3
        // configurations, which do provide std::char_traits<>::eof().

                    EOF;
#else
                std::char_traits<CharT>::eof();
#endif
            }

            bool operator>>(CharT&);
            bool operator>>(std::string&);

            #ifndef DISABLE_WIDE_CHAR_SUPPORT
            bool operator>>(std::wstring&);
            #endif
        };

        template<typename CharT>
        inline bool lexical_stream_limited_src<CharT>::operator<<(bool value)
        {
            *start = value + lcast_char_constants<CharT>::zero;
            finish = start + 1;
            return true;
        }

        template<typename CharT>
        inline bool lexical_stream_limited_src<CharT>::operator<<(char ch)
        {
            widen_and_assign(start, ch);
            finish = start + 1;
            return true;
        }

#if !defined(DISABLE_WIDE_CHAR_SUPPORT) && !defined(BOOST_NO_INTRINSIC_WCHAR_T)
        template<typename CharT>
        inline bool lexical_stream_limited_src<CharT>::operator<<(wchar_t ch)
        {
            widen_and_assign(start, ch);
            finish = start + 1;
            return true;
        }
#endif

        template<typename CharT>
        inline bool lexical_stream_limited_src<CharT>::operator<<(short n)
        {
            start = lcast_put_unsigned(lcast_to_unsigned(n), finish);
            if(n < 0)
                *--start = lcast_char_constants<CharT>::minus;
            return true;
        }

        template<typename CharT>
        inline bool lexical_stream_limited_src<CharT>::operator<<(int n)
        {
            start = lcast_put_unsigned(lcast_to_unsigned(n), finish);
            if(n < 0)
                *--start = lcast_char_constants<CharT>::minus;
            return true;
        }

        template<typename CharT>
        inline bool lexical_stream_limited_src<CharT>::operator<<(long n)
        {
            start = lcast_put_unsigned(lcast_to_unsigned(n), finish);
            if(n < 0)
                *--start = lcast_char_constants<CharT>::minus;
            return true;
        }

#if defined(BOOST_HAS_LONG_LONG)
        template<typename CharT>
        inline bool lexical_stream_limited_src<CharT>::operator<<(
                boost::long_long_type n)
        {
            start = lcast_put_unsigned(lcast_to_unsigned(n), finish);
            if(n < 0)
                *--start = lcast_char_constants<CharT>::minus;
            return true;
        }
#elif defined(BOOST_HAS_MS_INT64)
        template<typename CharT>
        inline bool lexical_stream_limited_src<CharT>::operator<<(__int64 n)
        {
            start = lcast_put_unsigned(lcast_to_unsigned(n), finish);
            if(n < 0)
                *--start = lcast_char_constants<CharT>::minus;
            return true;
        }
#endif

        template<typename CharT>
        inline bool lexical_stream_limited_src<CharT>::operator<<(
                unsigned short n)
        {
            start = lcast_put_unsigned(+n, finish);
            return true;
        }

        template<typename CharT>
        inline bool lexical_stream_limited_src<CharT>::operator<<(
                unsigned int n)
        {
            start = lcast_put_unsigned(n, finish);
            return true;
        }

        template<typename CharT>
        inline bool lexical_stream_limited_src<CharT>::operator<<(
                unsigned long n)
        {
            start = lcast_put_unsigned(n, finish);
            return true;
        }

#if defined(BOOST_HAS_LONG_LONG)
        template<typename CharT>
        inline bool lexical_stream_limited_src<CharT>::operator<<(
                boost::ulong_long_type n)
        {
            start = lcast_put_unsigned(n, finish);
            return true;
        }
#elif defined(BOOST_HAS_MS_INT64)
        template<typename CharT>
        inline bool lexical_stream_limited_src<CharT>::operator<<(
                unsigned __int64 n)
        {
            start = lcast_put_unsigned(n, finish);
            return true;
        }
#endif

        template<typename CharT>
        inline bool lexical_stream_limited_src<CharT>::operator<<(
                CharT const* str)
        {
            start = const_cast<CharT*>(str);
            finish = start + std::char_traits<CharT>::length(str);
            return true;
        }

        template<typename CharT>
        inline bool lexical_stream_limited_src<CharT>::operator>>(CharT& output)
        {
            bool const ok = (finish - start == 1);
            if(ok)
                output = *start;
            return ok;
        }

        template<typename CharT>
        inline bool lexical_stream_limited_src<CharT>::operator>>(
                std::string& str)
        {
            str.assign(start, finish);
            return true;
        }

        #ifndef DISABLE_WIDE_CHAR_SUPPORT
        template<typename CharT>
        inline bool lexical_stream_limited_src<CharT>::operator>>(
                std::wstring& str)
        {
            str.assign(start, finish);
            return true;
        }
        #endif
    }

    #ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

    // call-by-const reference version

    namespace detail
    {
        template<class T>
        struct array_to_pointer_decay
        {
            typedef T type;
        };

        template<class T, std::size_t N>
        struct array_to_pointer_decay<T[N]>
        {
            typedef const T * type;
        };

        template< typename Target
                , typename Source
                , bool Unlimited // string representation of Source is unlimited
                , typename CharT
                >
        Target lexical_cast(
            BOOST_DEDUCED_TYPENAME boost::call_traits<Source>::value_type arg,
            CharT* buf, std::size_t src_len)
        {
            BOOST_DEDUCED_TYPENAME mpl::if_c<
                Unlimited
              , detail::lexical_stream<Target, Source>
              , detail::lexical_stream_limited_src<CharT>
              >::type interpreter(buf, buf + src_len);

            // The original form, reproduced below, is more elegant
            // but yields a spurious C4701 warning ("possible use of
            // "result" before initialization") with VC7.1 (/W4).
//
//            Target result;
//
//            if(!(interpreter << arg && interpreter >> result))
//                throw_exception(bad_lexical_cast(typeid(Source), typeid(Target)));
//            return result;

            if(interpreter << arg) {
                Target result;
                if (interpreter >> result)
                    return result;
            }
            throw_exception(bad_lexical_cast(typeid(Source), typeid(Target)));
            return Target(); // normally never reached (throw_exception)
        }
    }

    template<typename Target, typename Source>
    inline Target lexical_cast(const Source &arg)
    {
        typedef typename detail::array_to_pointer_decay<Source>::type src;

        typedef typename detail::widest_char<
            typename detail::stream_char<Target>::type
          , typename detail::stream_char<src>::type
          >::type char_type;

        typedef detail::lcast_src_length<char_type, src> lcast_src_length;
        std::size_t const src_len = lcast_src_length::value;
        char_type buf[src_len + 1];
        lcast_src_length::check_coverage();
        return detail::lexical_cast<Target, src, !src_len>(arg, buf, src_len);
    }

    #else

    // call-by-value fallback version (deprecated)

    template<typename Target, typename Source>
    Target lexical_cast(Source arg)
    {
        detail::lexical_stream<Target, Source> interpreter;
        Target result;

        if(!(interpreter << arg && interpreter >> result))
            throw_exception(bad_lexical_cast(typeid(Source), typeid(Target)));
        return result;
    }

    #endif
}

// Copyright Kevlin Henney, 2000-2005.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#undef DISABLE_WIDE_CHAR_SUPPORT
#endif

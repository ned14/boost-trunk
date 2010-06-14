/*
 *          Copyright Andrey Semashev 2007 - 2010.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#include <cstddef>
#include <locale>
#include <stdexcept>
#include <boost/throw_exception.hpp>
#include <boost/date_time/detail/code_convert.hpp>

#if !defined(BOOST_NO_STD_WSTRING)

namespace boost {

namespace date_time {

namespace aux {

namespace {

    //! The function performs character conversion with the specified facet
    inline std::codecvt_base::result convert(
        std::codecvt< wchar_t, char, std::mbstate_t > const& fac,
        std::mbstate_t& state,
        const char*& pSrcBegin,
        const char* pSrcEnd,
        wchar_t*& pDstBegin,
        wchar_t* pDstEnd)
    {
        return fac.in(state, pSrcBegin, pSrcEnd, pSrcBegin, pDstBegin, pDstEnd, pDstBegin);
    }

    //! The function performs character conversion with the specified facet
    inline std::codecvt_base::result convert(
        std::codecvt< wchar_t, char, std::mbstate_t > const& fac,
        std::mbstate_t& state,
        const wchar_t*& pSrcBegin,
        const wchar_t* pSrcEnd,
        char*& pDstBegin,
        char* pDstEnd)
    {
        return fac.out(state, pSrcBegin, pSrcEnd, pSrcBegin, pDstBegin, pDstEnd, pDstBegin);
    }

    //! The function actually converts encodings
    template< typename ToCharT, typename FromCharT >
    inline void do_code_convert(
        std::basic_string< FromCharT > const& from,
        std::basic_string< ToCharT >& to,
        std::locale const& loc)
    {
        typedef std::codecvt< wchar_t, char, std::mbstate_t > facet_t;
        facet_t const& fac = std::use_facet< facet_t >(loc);
        std::mbstate_t state = {};

        to.resize(from.size());
        const FromCharT* from_p = from.data(), *from_e = from_p + from.size();
        ToCharT* to_p = const_cast< ToCharT* >(to.data()), *to_e = to_p + to.size();

        std::codecvt_base::result res = std::codecvt_base::error;
        do
        {
            res = convert(fac, state, from_p, from_e, to_p, to_e);
            switch (res)
            {
            case std::codecvt_base::partial:
                {
                    // The converted data does not fit in the resulting buffer.
                    std::size_t index = to_p - to.data();
                    to.resize(to.size() + to.size() / 2);
                    to_p = const_cast< ToCharT* >(to.data()) + index;
                    to_e = to_p + to.size();
                }
                break;

            case std::codecvt_base::error:
                BOOST_THROW_EXCEPTION(std::runtime_error("Could not perform character encoding conversion"));
                break;

            default:
                break;
            }
        }
        while (res != std::codecvt_base::ok && res != std::codecvt_base::noconv);

        // Correct the target buffer size
        to.resize(to_p - to.data());
    }

} // namespace

//! Widens the string, according to the specified locale
BOOST_DATE_TIME_DECL void code_convert(
    std::string const& from, std::wstring& to, std::locale const& loc)
{
    do_code_convert(from, to, loc);
}

//! Narrows the string, according to the specified locale
BOOST_DATE_TIME_DECL void code_convert(
    std::wstring const& from, std::string& to, std::locale const& loc)
{
    do_code_convert(from, to, loc);
}

} // namespace aux

} // namespace date_time

} // namespace boost

#endif // !defined(BOOST_NO_STD_WSTRING)

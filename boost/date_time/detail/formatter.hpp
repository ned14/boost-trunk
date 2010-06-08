/*
 *          Copyright Andrey Semashev 2007 - 2010.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   common_date_time.hpp
 * \author Andrey Semashev
 * \date   08.06.2010
 *
 * The header contains implementation of a common date/time type for ABI purposes.
 */

#if (defined(_MSC_VER) && _MSC_VER > 1000)
#pragma once
#endif // _MSC_VER > 1000

#ifndef BOOST_DATE_TIME_DETAIL_FORMATTER_HPP_INCLUDED_
#define BOOST_DATE_TIME_DETAIL_FORMATTER_HPP_INCLUDED_

#include <locale>
#include <string>
#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/detail/common_date_time.hpp>

namespace boost {

namespace date_time {

namespace aux {

template< typename CharT >
class BOOST_DATE_TIME_DECL formatter
{
public:
    struct implementation;

    typedef CharT char_type;
    typedef std::basic_string< char_type > string_type;

private:
    implementation* m_pImpl;

public:
    //! Default constructor. Creates an empty formatter that does nothing.
    formatter();
    //! Copy constructor. Performs a deep copying.
    formatter(formatter const& that);
    //! Destructor
    ~formatter();
    //! Assignment
    formatter& operator= (formatter const& that);

    //! Formatting operator
    void operator()(
        common_date_time const& dt,
        string_type& out,
        std::locale const& loc = std::locale()) const;

    //! Parses the format string and constructs the formatter
    static formatter parse(const char_type* b, const char_type* e);
};

} // namespace aux

} // namespace date_time

} // namespace boost

#endif // BOOST_DATE_TIME_DETAIL_FORMATTER_HPP_INCLUDED_

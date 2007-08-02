/*=============================================================================
    Copyright (c) 2002 2004 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_QUICKBOOK_UTILS_HPP)
#define BOOST_SPIRIT_QUICKBOOK_UTILS_HPP

#include <string>
#include <iostream>
#include <cctype>
#include <boost/ref.hpp>
#include <boost/assert.hpp>

namespace quickbook { namespace detail
{
    void
    print_char(char ch, std::ostream& out);

    void
    print_string(std::basic_string<char> const& str, std::ostream& out);

    void
    print_space(char ch, std::ostream& out);

    void
    convert_nbsp(std::basic_string<char>& str);

    char
    filter_identifier_char(char ch);

    template <typename Iterator>
    inline std::string
    make_identifier(Iterator const& first, Iterator const& last)
    {
        std::string out_name;
        for (Iterator i = first; i != last; ++i)
            out_name += filter_identifier_char(*i);
        return out_name;
    }

    template <typename T>
    struct var_wrapper
        : public ::boost::reference_wrapper<T>
    {
        typedef ::boost::reference_wrapper<T> parent;

        explicit inline var_wrapper(T& t) : parent(t) {}

        inline T& operator()() const { return parent::get(); }
    };

    template <typename T>
    inline var_wrapper<T>
    var(T& t)
    {
        return var_wrapper<T>(t);
    }

    // un-indent a code segment
    void unindent(std::string& program);

    // remove the extension from a filename
    std::string
    remove_extension(std::string const& filename);
    
    std::string escape_uri(std::string uri);
}}

#endif // BOOST_SPIRIT_QUICKBOOK_UTILS_HPP


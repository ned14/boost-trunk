// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.


#ifndef BOOST_IOSTREAMS_TEST_VERIFICATION_HPP_INCLUDED
#define BOOST_IOSTREAMS_TEST_VERIFICATION_HPP_INCLUDED

#include <exception>
#include <string>
#include <string.h>
#include <fstream>
#ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
# include <istream>
# include <ostream>
#else
# include <iostream.h>
#endif

#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/config/wide_streams.hpp>
#include "./constants.hpp"

// Included only by tests; no need to #undef.
#ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
# define BOOST_TEMPLATE_DECL template<typename Ch, typename Tr>
# define BOOST_CHAR Ch
# define BOOST_ISTREAM std::basic_istream<Ch, Tr>
# define BOOST_OSTREAM std::basic_ostream<Ch, Tr>
#else
# define BOOST_TEMPLATE_DECL
# define BOOST_CHAR char
# define BOOST_ISTREAM std::istream
# define BOOST_OSTREAM std::ostream
#endif

namespace boost { namespace iostreams { namespace test {

BOOST_TEMPLATE_DECL
bool compare_streams_in_chars(BOOST_ISTREAM& first, BOOST_ISTREAM& second)
{
    for (int z = 0; z < 10; ++z)
        for (int w = 0; w < data_length(); ++w)
            if (first.eof() != second.eof() || first.get() != second.get())
                return false;
    return true;
}

BOOST_TEMPLATE_DECL
bool compare_streams_in_chunks(BOOST_ISTREAM& first, BOOST_ISTREAM& second)
{
    int i = 0;
    do {
        BOOST_CHAR buf_one[chunk_size];
        BOOST_CHAR buf_two[chunk_size];
        first.read(buf_one, chunk_size);
        second.read(buf_two, chunk_size);
        std::streamsize amt = first.gcount();
        if ( amt != static_cast<std::streamsize>(second.gcount()) ||
             BOOST_IOSTREAMS_CHAR_TRAITS(BOOST_CHAR)::
                compare(buf_one, buf_two, amt) != 0 )
            return false;
        ++i;
    } while (!first.eof());
    return true;
}

bool compare_files(const std::string& first, const std::string& second)
{
    using namespace std;
    ifstream one(first.c_str(), BOOST_IOS::in | BOOST_IOS::binary);
    ifstream two(second.c_str(), BOOST_IOS::in | BOOST_IOS::binary);
    return compare_streams_in_chunks(one, two);
}

#ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
    template<typename Container, typename Ch, typename Tr>
#else
    template<typename Container>
#endif
bool compare_container_and_stream(Container& cnt, BOOST_ISTREAM& is)
{
    typename Container::iterator first = cnt.begin();
    typename Container::iterator last = cnt.end();
    do  {
        if ((first == last) != is.eof()) return false;
        if (first != last && *first++ != is.get()) return false;
    } while (first != last);
    return true;
}

BOOST_TEMPLATE_DECL
void write_data_in_chars(BOOST_OSTREAM& os)
{
    for (int z = 0; z < data_reps; ++z) 
        for (int w = 0; w < data_length(); ++w) 
            os.put(detail::data((BOOST_CHAR*)0)[w]);
    os.flush();
}

BOOST_TEMPLATE_DECL
void write_data_in_chunks(BOOST_OSTREAM& os)
{
    const BOOST_CHAR* buf = detail::data((BOOST_CHAR*)0);
    for (int z = 0; z < data_reps; ++z)
        os.write(buf, data_length());
    os.flush();
}

bool test_seekable_in_chars(std::iostream& io)
{
    for (int i = 0; i < data_reps; ++i) {
        int j;
        for (j = 0; j < chunk_size; ++j)
            io.put(narrow_data()[j]);
        io.seekp(-chunk_size, BOOST_IOS::cur);
        for (j = 0; j < chunk_size; ++j)
            if (io.get() != narrow_data()[j])
               return false;
        io.seekp(-chunk_size, BOOST_IOS::cur);
        for (j = 0; j < chunk_size; ++j)
            io.put(narrow_data()[j]);
    }
    return true;
}

bool test_seekable_in_chunks(std::iostream& io)
{
    for (int i = 0; i < data_reps; ++i) {
        io.write(narrow_data(), chunk_size);
        io.seekp(-chunk_size, BOOST_IOS::cur);
        char buf[chunk_size];
        io.read(buf, chunk_size);
        if (strncmp(buf, narrow_data(), chunk_size) != 0)
            return false;
        io.seekp(-chunk_size, BOOST_IOS::cur);
        io.write(narrow_data(), chunk_size);
    }
    return true;
}

bool unbuffered_putback_test(std::istream& is)
{
    try {
        do {
            char buf[chunk_size];
            is.read(buf, chunk_size);
            if (is.gcount() < static_cast<std::streamsize>(chunk_size))
                break;
            is.putback('a');
            if (is.get() != 'a')
                return false;
        } while (!is.eof());
        return true;
    } catch (std::exception&) { return false; }
}

bool buffered_putback_test(std::istream& is)
{
    try {
        do {
            char buf[chunk_size];
            is.read(buf, chunk_size);
            if (is.gcount() < static_cast<std::streamsize>(chunk_size))
                break;
            is.putback('a');
            is.putback('b');
            is.putback('c');
            is.putback('d');
            if ( is.get() != 'd' || is.get() != 'c' ||
                 is.get() != 'b' || is.get() != 'a' )
            {
                return false;
            }
        } while (!is.eof());
        return true;
    } catch (std::exception&) { return false; }
}

} } } // End namespaces test, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_TEST_VERIFICATION_HPP_INCLUDED

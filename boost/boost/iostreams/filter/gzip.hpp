// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Contains the definitions of the class templates gzip_compressor and
// gzip_decompressor for reading and writing files in the gzip file format
// (RFC 1952). Based in part on work of Jonathan de Halleux; see [...]

#ifndef BOOST_IOSTREAMS_GZIP_HPP_INCLUDED
#define BOOST_IOSTREAMS_GZIP_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/config.hpp>               // STATIC_CONSTANT, STDC_NAMESPACE.
#include <algorithm>                      // min.
#include <cstdio>                         // EOF.
#include <ctime>                          // std::time_t.
#include <memory>                         // allocator.
#include <sstream>                        // allocator.
#include <boost/iostreams/constants.hpp>  // buffer size.
#include <boost/iostreams/operations.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/pipable.hpp>      

// Must come last.
#if defined(BOOST_MSVC)
# pragma warning(push)
# pragma warning(disable: 4309)    // Truncation of constant value.
#endif

#ifdef BOOST_NO_STDC_NAMESPACE
namespace std { using ::time_t; }
#endif

namespace boost { namespace iostreams {

namespace gzip {

using namespace boost::iostreams::zlib;

    // Error codes used by gzip_error.

const int zlib_error        = 1;
const int bad_crc           = 2; // Recorded crc doesn't match data.
const int bad_length        = 3; // Recorded length doesn't match data.
const int bad_header        = 4; // Malformed header.
const int bad_footer        = 5; // Malformed footer.


namespace magic {

    // Magic numbers used by gzip header.

const int id1               = 0x1f;
const int id2               = 0x8b;

} // End namespace magic.

namespace method {

    // Codes used for the 'CM' byte of the gzip header.

const int deflate           = 8;

} // End namespace method.

namespace flags {

    // Codes used for the 'FLG' byte of the gzip header.

const int text              = 1;
const int header_crc        = 2;
const int extra             = 4;
const int name              = 8;
const int comment           = 16;

} // End namespace flags.

namespace extra_flags {

    // Codes used for the 'XFL' byte of the gzip header.

const int best_compression  = 2;
const int best_speed        = 4;

} // End namespace extra_flags.

    // Codes used for the 'OS' byte of the gzip header.

const int os_fat            = 0;
const int os_amiga          = 1;
const int os_vms            = 2;
const int os_unix           = 3;
const int os_vm_cms         = 4;
const int os_atari          = 5;
const int os_hpfs           = 6;
const int os_macintosh      = 7;
const int os_z_system       = 8;
const int os_cp_m           = 9;
const int os_tops_20        = 10;
const int os_ntfs           = 11;
const int os_qdos           = 12;
const int os_acorn          = 13;
const int os_unknown        = 255;

} // End namespace gzip.

//
// Class name: gzip_params.
// Description: Subclass of zlib_params with an additional field
//      representing a file name.
//
struct gzip_params : zlib_params {

    // Non-explicit constructor.
    gzip_params( int level              = gzip::default_compression,
                 int method             = gzip::deflated,
                 int window_bits        = gzip::default_window_bits,
                 int mem_level          = gzip::default_mem_level,
                 int strategy           = gzip::default_strategy,
                 std::string file_name  = "",
                 std::string comment    = "",
                 std::time_t mtime      = 0 )
        : zlib_params(level, method, window_bits, mem_level, strategy),
          file_name(file_name), mtime(mtime)
        { }
    std::string  file_name;
    std::string  comment;
    std::time_t  mtime;
};

//
// Class name: gzip_error.
// Description: Subclass of std::ios_base::failure thrown to indicate
//     zlib errors other than out-of-memory conditions.
//
class gzip_error : public std::ios_base::failure {
public:
    gzip_error(int error)
        : std::ios_base::failure("gzip error"),
          error_(error), zlib_error_code_(zlib::okay) { }
    gzip_error(const zlib_error& e)
        : std::ios_base::failure("gzip error"),
          error_(gzip::zlib_error), zlib_error_code_(e.error())
        { }
    int error() const { return error_; }
    int zlib_error_code() const { return zlib_error_code_; }
private:
    int error_;
    int zlib_error_code_;
};

//
// Template name: gzip_compressor
// Description: Model of OutputFilter implementing compression in the
//      gzip format.
//
template<typename Alloc = std::allocator<char> >
class basic_gzip_compressor : basic_zlib_compressor<Alloc> {
private:
    typedef basic_zlib_compressor<Alloc>  base_type;
public:
    typedef char char_type;
    struct io_category
        : dual_use,
          filter_tag,
          multichar_tag,
          closable_tag
        { };
    basic_gzip_compressor( const gzip_params& = gzip::default_compression,
                           std::streamsize buffer_size = default_buffer_size );

    template<typename Source>
    std::streamsize read(Source& src, char_type* s, std::streamsize n)
        {
            using namespace std;
            streamsize result = 0;

            // Read header.
            if (!(flags_ & f_header_done))
                result += read_string(s, n, header_);

            // Read body.
            if (!(flags_ & f_body_done)) {

                // Read from basic_zlib_filter.
                streamsize amt = base_type::read(src, s + result, n - result);
                if (amt < n - result)
                    prepare_footer();
                result += amt;
            }

            // Read footer.
            if (flags_ & f_body_done && result < n)
                result += read_string(s + result, n - result, footer_);

            return result;
        }

    template<typename Sink>
    void write(Sink& snk, const char_type* s, std::streamsize n)
        {
            if (!(flags_ & f_header_done)) {
                boost::iostreams::write(
                    snk,
                    header_.data(),
                    static_cast<std::streamsize>(header_.size())
                );
                flags_ |= f_header_done;
            }
            base_type::write(snk, s, n);
        }

    template<typename Sink>
    void close(Sink& snk, std::ios::openmode m)
        {
            if (m & std::ios::out) {

                // Close zlib compressor.
                base_type::close(snk, std::ios::out);

                // Write final fields of gzip file format.
                write_long(this->crc(), snk);
                write_long(this->total_in(), snk);
            }
            footer_.clear();
            offset_ = 0;
            flags_ = 0;
        }
private:
    static gzip_params normalize_params(gzip_params p);

    void prepare_footer()
        {
            write_long(this->crc(), footer_);
            write_long(this->total_in(), footer_);
            flags_ |= f_body_done;
            offset_ = 0;
        }

    std::streamsize read_string(char* s, std::streamsize n, std::string& str)
        {
            using namespace std;
            streamsize avail =
                static_cast<streamsize>(str.size() - offset_);
            streamsize amt = std::min(avail, n);
            std::copy( str.data() + offset_,
                       str.data() + offset_ + amt,
                       s );
            offset_ += amt;
            if ( !(flags_ & f_header_done) &&
                 offset_ == static_cast<int>(str.size()) )
            {
                flags_ |= f_header_done;
            }
            return amt;
        }

    static void write_long(long n, std::string& str)
        {
            str += static_cast<char>(0xFF & n);
            str += static_cast<char>(0xFF & (n >> 8));
            str += static_cast<char>(0xFF & (n >> 16));
            str += static_cast<char>(0xFF & (n >> 24));
        }

    template<typename Sink>
    static void write_long(long n, Sink& next)
        {
            boost::iostreams::put(next, static_cast<char>(0xFF & n));
            boost::iostreams::put(next, static_cast<char>(0xFF & (n >> 8)));
            boost::iostreams::put(next, static_cast<char>(0xFF & (n >> 16)));
            boost::iostreams::put(next, static_cast<char>(0xFF & (n >> 24)));
        }

    enum {
        f_header_done = 1,
        f_body_done = f_header_done << 1,
        f_footer_done = f_body_done << 1
    };
    std::string  header_;
    std::string  footer_;
    int          offset_;
    int          flags_;
};
BOOST_IOSTREAMS_PIPABLE(basic_gzip_compressor, 1)

typedef basic_gzip_compressor<> gzip_compressor;

//
// Template name: gzip_compressor
// Description: Model of InputFilter implementing compression in the
//      gzip format.
//
template<typename Alloc = std::allocator<char> >
class basic_gzip_decompressor : basic_zlib_decompressor<Alloc> {
public:
    typedef char char_type;
    struct io_category
        : multichar_input_filter_tag,
          closable_tag
        { };
    basic_gzip_decompressor( int window_bits = gzip::default_window_bits,
                             std::streamsize buffer_size =
                                  default_buffer_size );
    template<typename Source>
    std::streamsize read(Source& src, char_type* s, std::streamsize n)
        {
            if (!header_read()) {
                read_header(src);
                flags_ |= f_header_read;
            }
            try {
                std::streamsize result = base_type::read(src, s, n);
                if (result < n)
                    read_footer(src);
                return result;
            } catch (const zlib_error& e) {
                throw gzip_error(e);
            }
        }

    template<typename Source>
    void close(Source& src)
        {
            try {
                base_type::close(src, std::ios::in);
                flags_ = 0;
            } catch (const zlib_error& e) {
                throw gzip_error(e);
            }
        }

    bool header_read() const { return (flags_ & f_header_read) != 0; }
    std::string file_name() const { return file_name_; }
    std::string comment() const { return comment_; }
    bool text() const { return (flags_ & gzip::flags::text) != 0; }
    int os() const { return os_; }
    std::time_t mtime() const { return mtime_; }
private:
    typedef basic_zlib_decompressor<Alloc>        base_type;
    typedef typename std::char_traits<char_type>  traits_type;
    static bool is_eof(int c) { return traits_type::eq_int_type(c, EOF); }
    static gzip_params make_params(int window_bits);

    template<typename Source>
    static int read_byte(Source& src, int error)
        {
            int c;
            if (traits_type::eq_int_type(c = boost::iostreams::get(src), EOF))
                throw gzip_error(error);
            return static_cast<unsigned char>(traits_type::to_char_type(c));
        }

    template<typename Source>
    static long read_long(Source& src, int error)
        {
            int b1 = read_byte(src, error);
            int b2 = read_byte(src, error);
            int b3 = read_byte(src, error);
            int b4 = read_byte(src, error);
            return b1 + (b2 << 8) + (b3 << 16) + (b4 << 24);
        }

    template<typename Source>
    std::string read_string(Source& src)
        {
            std::string result;
            while (true) {
                int c;
                if (is_eof(c = boost::iostreams::get(src)))
                    throw gzip_error(gzip::bad_header);
                else if (c == 0)
                    return result;
                else
                    result += static_cast<char>(c);
            }
        }

    template<typename Source>
    void read_header(Source& src)
        {
            // Reset saved values.
            file_name_.clear();
            comment_.clear();
            os_ = gzip::os_unknown;
            mtime_ = 0;

            int flags;

            // Read header, without checking header crc.
            if ( boost::iostreams::get(src) != gzip::magic::id1 ||   // ID1.
                 boost::iostreams::get(src) != gzip::magic::id2 ||   // ID2.
                is_eof(boost::iostreams::get(src)) ||                // CM.
                is_eof(flags = boost::iostreams::get(src)) )         // FLG.
            {
                throw gzip_error(gzip::bad_header);
            }
            mtime_ = read_long(src, gzip::bad_header);        // MTIME.
            read_byte(src, gzip::bad_header);                 // XFL.
            os_ = read_byte(src, gzip::bad_header);           // OS.
            if (flags & boost::iostreams::gzip::flags::text)
                flags_ |= f_text;

            // Skip extra field. (From J. Halleaux; see note at top.)
            if (flags & gzip::flags::extra) {
                int length = read_byte(src, gzip::bad_header) +
                            (read_byte(src, gzip::bad_header) << 8);
                // length is garbage if EOF but the loop below will quit anyway.
                do { }
                while (length-- != 0 && !is_eof(boost::iostreams::get(src)));
            }

            if (flags & gzip::flags::name)          // Read file name.
                file_name_ = read_string(src);
            if (flags & gzip::flags::comment)       // Read comment.
                comment_ = read_string(src);
            if (flags & gzip::flags::header_crc) {  // Skip header crc.
                read_byte(src, gzip::bad_header);
                read_byte(src, gzip::bad_header);
            }
        }

    template<typename Source>
    void read_footer(Source& src)
        {
            std::basic_string<char_type, traits_type, Alloc> footer =
                this->unconsumed_input();
            int c;
            while (!is_eof(c = boost::iostreams::get(src)))
                footer += c;
            std::basic_stringbuf<char_type, traits_type, Alloc> in(footer);
            if ( static_cast<unsigned long>(read_long(in, gzip::bad_footer))
                    !=
                 this->crc() )
            {
                throw gzip_error(gzip::bad_crc);
            }
            if (read_long(in, gzip::bad_footer) != this->total_out())
                throw gzip_error(gzip::bad_length);
        }
    enum {
        f_header_read = 1,
        f_text = f_header_read << 1
    };
    std::string  file_name_;
    std::string  comment_;
    int          os_;
    std::time_t  mtime_;
    int          flags_;
};
BOOST_IOSTREAMS_PIPABLE(basic_gzip_decompressor, 1)

typedef basic_gzip_decompressor<> gzip_decompressor;

//------------------Implementation of gzip_compressor-------------------------//

template<typename Alloc>
basic_gzip_compressor<Alloc>::basic_gzip_compressor
    (const gzip_params& p, std::streamsize buffer_size)
    : base_type(normalize_params(p), buffer_size),
      offset_(0), flags_(0)
{
    // Calculate gzip header.
    bool has_name = !p.file_name.empty();
    bool has_comment = !p.comment.empty();

    std::string::size_type length =
        10 +
        (has_name ? p.file_name.size() + 1 : 0) +
        (has_comment ? p.comment.size() + 1 : 0);
        // + 2; // Header crc confuses gunzip.
    int flags =
        //gzip::flags::header_crc +
        (has_name ? gzip::flags::name : 0) +
        (has_comment ? gzip::flags::comment : 0);
    int extra_flags =
        ( p.level == zlib::best_compression ?
              gzip::extra_flags::best_compression :
              0 ) +
        ( p.level == zlib::best_speed ?
              gzip::extra_flags::best_speed :
              0 );
    header_.reserve(length);
    header_ += gzip::magic::id1;                         // ID1.
    header_ += gzip::magic::id2;                         // ID2.
    header_ += gzip::method::deflate;                    // CM.
    header_ += static_cast<char>(flags);                 // FLG.
    header_ += static_cast<char>(0xFF & p.mtime);        // MTIME.
    header_ += static_cast<char>(0xFF & (p.mtime >> 8));
    header_ += static_cast<char>(0xFF & (p.mtime >> 16));
    header_ += static_cast<char>(0xFF & (p.mtime >> 24));
    header_ += static_cast<char>(extra_flags);           // XFL.
    header_ += static_cast<char>(gzip::os_unknown);      // OS.
    if (has_name) {
        header_ += p.file_name;
        header_ += '\0';
    }
    if (has_comment) {
        header_ += p.comment;
        header_ += '\0';
    }
}

template<typename Alloc>
gzip_params basic_gzip_compressor<Alloc>::normalize_params(gzip_params p)
{
    p.noheader = true;
    p.calculate_crc = true;
    return p;
}

//------------------Implementation of gzip_decompressor-----------------------//

template<typename Alloc>
basic_gzip_decompressor<Alloc>::basic_gzip_decompressor
    (int window_bits, std::streamsize buffer_size)
    : base_type(make_params(window_bits), buffer_size),
      os_(gzip::os_unknown), mtime_(0), flags_(0)
    { }

template<typename Alloc>
gzip_params basic_gzip_decompressor<Alloc>::make_params(int window_bits)
{
    gzip_params p;
    p.window_bits = window_bits;
    p.noheader = true;
    p.calculate_crc = true;
    return p;
}

//----------------------------------------------------------------------------//

} } // End namespaces iostreams, boost.

#if defined(BOOST_MSVC)
# pragma warning(pop)
#endif

#endif // #ifndef BOOST_IOSTREAMS_GZIP_HPP_INCLUDED

// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Define BOOST_IOSTREAMS_SOURCE so that <boost/iostreams/detail/config.hpp>
// knows that we are building the library (possibly exporting code), rather
// than using it (possibly importing code).
#define BOOST_IOSTREAMS_SOURCE

#include <cassert>
#include <cerrno>
#include <cstdio>                                 // SEEK_SET, etc.
#include <boost/config.hpp>                       // BOOST_JOIN
#include <boost/iostreams/detail/error.hpp>
#include <boost/iostreams/detail/config/dyn_link.hpp>
#include <boost/iostreams/detail/config/rtl.hpp>  // BOOST_IOSTREAMS_FD_XXX
#include <boost/iostreams/detail/config/windows_posix.hpp>
#include <boost/iostreams/detail/system_failure.hpp>
#include <boost/iostreams/detail/ios.hpp>         // openmodes, failure.
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/integer_traits.hpp>

    // OS-specific headers for low-level i/o.

#include <fcntl.h>       // file opening flags.
#include <sys/stat.h>    // file access permissions.
#ifdef BOOST_IOSTREAMS_WINDOWS
# include <io.h>         // low-level file i/o.
# define WINDOWS_LEAN_AND_MEAN
# include <windows.h>
# ifndef INVALID_SET_FILE_POINTER
#  define INVALID_SET_FILE_POINTER ((DWORD)-1)
# endif
#else
# include <sys/types.h>  // mode_t.
# include <unistd.h>     // low-level file i/o.
#endif

namespace boost { namespace iostreams {

//------------------Definition of file_descriptor_impl------------------------//

namespace detail {

// Contains the platform dependant implementation
struct file_descriptor_impl {
    file_descriptor_impl();
    ~file_descriptor_impl();
    void open(file_handle fd, bool close_on_exit);
#ifdef BOOST_IOSTREAMS_WINDOWS
    void open(int fd, bool close_on_exit);
#endif
    void open(const detail::path&, BOOST_IOS::openmode);
    bool is_open() const;
    void close();
    std::streamsize read(char* s, std::streamsize n);
    std::streamsize write(const char* s, std::streamsize n);
    std::streampos seek(stream_offset off, BOOST_IOS::seekdir way);
    static file_handle invalid_handle();
    enum flags {
        close_on_exit = 1,
        append = 4
    };
    file_handle  handle_;
    int          flags_;
};

//------------------Implementation of file_descriptor_impl--------------------//

file_descriptor_impl::file_descriptor_impl() 
    : handle_(invalid_handle()), flags_(0) 
    { }

file_descriptor_impl::~file_descriptor_impl() 
{ 
    if (flags_ & close_on_exit) {
        try { 
            close(); 
        } catch (...) { }  
    }
}

void file_descriptor_impl::open(file_handle fd, bool close_on_exit)
{
    handle_ = fd;
    flags_ = close_on_exit ? 
        file_descriptor_impl::close_on_exit : 
        0;
}

#ifdef BOOST_IOSTREAMS_WINDOWS //---------------------------------------------//

void file_descriptor_impl::open(int fd, bool close_on_exit)
{ open(reinterpret_cast<file_handle>(_get_osfhandle(fd)), close_on_exit); }

#endif // #ifdef BOOST_IOSTREAMS_WINDOWS //-----------------------------------//

void file_descriptor_impl::open(const detail::path& p, BOOST_IOS::openmode mode)
{
#ifdef BOOST_IOSTREAMS_WINDOWS //---------------------------------------------//
    DWORD dwDesiredAccess;
    DWORD dwCreationDisposition;
    if ( (mode & (BOOST_IOS::in | BOOST_IOS::out))
             ==
         (BOOST_IOS::in | BOOST_IOS::out) )
    {
        if (mode & BOOST_IOS::app)
            throw BOOST_IOSTREAMS_FAILURE("bad open mode");
        dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
        dwCreationDisposition =
            (mode & BOOST_IOS::trunc) ?
                OPEN_ALWAYS :
                OPEN_EXISTING;
    } else if (mode & BOOST_IOS::in) {
        if (mode & (BOOST_IOS::app |BOOST_IOS::trunc))
            throw BOOST_IOSTREAMS_FAILURE("bad open mode");
        dwDesiredAccess = GENERIC_READ;
        dwCreationDisposition = OPEN_EXISTING;
    } else if (mode & BOOST_IOS::out) {
        dwDesiredAccess = GENERIC_WRITE;
        dwCreationDisposition = OPEN_ALWAYS;
        if (mode & BOOST_IOS::app)
            flags_ |= append;
    } else {
        throw BOOST_IOSTREAMS_FAILURE("bad open mode");
    }

    HANDLE handle = p.is_wide() ?
        ::CreateFileW( p.c_wstr(),
                       dwDesiredAccess,
                       FILE_SHARE_READ | FILE_SHARE_WRITE,
                       NULL,                   // lpSecurityAttributes
                       dwCreationDisposition,
                       FILE_ATTRIBUTE_NORMAL,
                       NULL ) :                // hTemplateFile
        ::CreateFileA( p.c_str(),
                       dwDesiredAccess,
                       FILE_SHARE_READ | FILE_SHARE_WRITE,
                       NULL,                   // lpSecurityAttributes
                       dwCreationDisposition,
                       FILE_ATTRIBUTE_NORMAL,
                       NULL );                 // hTemplateFile
    if (handle != INVALID_HANDLE_VALUE) {
        handle_ = handle;
        flags_ |= close_on_exit;
    } else {
        flags_ = 0;
        throw_system_failure("failed opening file");
    }
#else // #ifdef BOOST_IOSTREAMS_WINDOWS //------------------------------------//

        // Calculate oflag argument to open.

    int oflag = 0;
    if ( (mode & (BOOST_IOS::in | BOOST_IOS::out))
             ==
         (BOOST_IOS::in | BOOST_IOS::out) )
    {
        assert(!(mode & BOOST_IOS::app));
        oflag |= O_RDWR;
    } else if (mode & BOOST_IOS::in) {
        assert(!(mode & (BOOST_IOS::app |BOOST_IOS::trunc)));
        oflag |= O_RDONLY;
    } else if (mode & BOOST_IOS::out) {
        oflag |= O_WRONLY;
        mode |= BOOST_IOS::trunc;
        if (mode & BOOST_IOS::app)
            oflag |= O_APPEND;
    }
    if (mode & BOOST_IOS::trunc)
        oflag |= O_CREAT;
    #ifdef _LARGEFILE64_SOURCE
        oflag |= O_LARGEFILE;
    #endif

        // Calculate pmode argument to open.

    mode_t pmode = S_IRUSR | S_IWUSR |
                   S_IRGRP | S_IWGRP |
                   S_IROTH | S_IWOTH;

        // Open file.

    int fd = BOOST_IOSTREAMS_FD_OPEN(p.c_str(), oflag, pmode);
    if (fd == -1) {
        throw system_failure("failed opening file");
    } else {
        handle_ = fd;
        flags_ = close_on_exit;
    }
#endif // #ifndef BOOST_IOSTREAMS_WINDOWS //----------------------------------//
}

bool file_descriptor_impl::is_open() const
{ return handle_ != invalid_handle(); }

void file_descriptor_impl::close()
{
    if (handle_ != invalid_handle()) {
        bool success = 
            #ifdef BOOST_IOSTREAMS_WINDOWS
                ::CloseHandle(handle_) == 1;
            #else
                BOOST_IOSTREAMS_FD_CLOSE(handle_) != -1;
            #endif
        if (!success)
            throw_system_failure("failed closing file");
        handle_ = invalid_handle();
        flags_ = 0;
    }
}

std::streamsize file_descriptor_impl::read(char* s, std::streamsize n)
{
#ifdef BOOST_IOSTREAMS_WINDOWS
    DWORD result;
    if (!::ReadFile(handle_, s, n, &result, NULL))
        throw_system_failure("failed reading");
    return result == 0 ? -1 : static_cast<std::streamsize>(result);
#else // #ifdef BOOST_IOSTREAMS_WINDOWS
    errno = 0;
    std::streamsize result = BOOST_IOSTREAMS_FD_READ(handle_, s, n);
    if (errno != 0)
        throw_system_failure("failed reading");
    return result == 0 ? -1 : result;
#endif // #ifdef BOOST_IOSTREAMS_WINDOWS
}

std::streamsize file_descriptor_impl::write(const char* s, std::streamsize n)
{
#ifdef BOOST_IOSTREAMS_WINDOWS
    if (flags_ & append) {
        DWORD const dwResult =
            ::SetFilePointer(handle_, 0, NULL, FILE_END);
        if ( dwResult == INVALID_SET_FILE_POINTER &&
             ::GetLastError() != NO_ERROR )
        {
            throw_system_failure("failed seeking within file");
        }
    }
    DWORD ignore;
    if (!::WriteFile(handle_, s, n, &ignore, NULL))
        throw_system_failure("failed writing");
    return n;
#else // #ifdef BOOST_IOSTREAMS_WINDOWS
    int amt = BOOST_IOSTREAMS_FD_WRITE(handle_, s, n);
    if (amt < n) // Handles blocking fd's only.
        throw_system_failure("failed writing");
    return n;
#endif // #ifdef BOOST_IOSTREAMS_WINDOWS
}

std::streampos file_descriptor_impl::seek
    (stream_offset off, BOOST_IOS::seekdir way)
{
#ifdef BOOST_IOSTREAMS_WINDOWS
    LONG lDistanceToMove = static_cast<LONG>(off & 0xffffffff);
    LONG lDistanceToMoveHigh = static_cast<LONG>(off >> 32);
    DWORD dwResultLow =
        ::SetFilePointer( handle_,
                          lDistanceToMove,
                          &lDistanceToMoveHigh,
                          way == BOOST_IOS::beg ?
                              FILE_BEGIN :
                              way == BOOST_IOS::cur ?
                                FILE_CURRENT :
                                FILE_END );
    if ( dwResultLow == INVALID_SET_FILE_POINTER &&
         ::GetLastError() != NO_ERROR )
    {
        throw system_failure("failed seeking");
    } else {
       return offset_to_position(
                  (stream_offset(lDistanceToMoveHigh) << 32) + dwResultLow
              );
    }
#else // #ifdef BOOST_IOSTREAMS_WINDOWS
    if ( off > integer_traits<BOOST_IOSTREAMS_FD_OFFSET>::const_max ||
         off < integer_traits<BOOST_IOSTREAMS_FD_OFFSET>::const_min )
    {
        throw BOOST_IOSTREAMS_FAILURE("bad offset");
    }
    stream_offset result =
        BOOST_IOSTREAMS_FD_SEEK(
            handle_,
            static_cast<BOOST_IOSTREAMS_FD_OFFSET>(off),
            ( way == BOOST_IOS::beg ?
                  SEEK_SET :
                  way == BOOST_IOS::cur ?
                      SEEK_CUR :
                      SEEK_END ) 
        );
    if (result == -1)
        throw system_failure("failed seeking");
    return offset_to_position(result);
#endif // #ifdef BOOST_IOSTREAMS_WINDOWS
}

// Returns the value stored in a file_handle variable when no file is open
file_handle file_descriptor_impl::invalid_handle()
{
#ifdef BOOST_IOSTREAMS_WINDOWS
    return INVALID_HANDLE_VALUE;
#else
    return -1;
#endif
}

} // End namespace detail.

//------------------Implementation of file_descriptor-------------------------//

file_descriptor::file_descriptor() : pimpl_(new impl_type) { }

file_descriptor::file_descriptor(handle_type fd, bool close_on_exit)
    : pimpl_(new impl_type)
{ open(fd, close_on_exit); }

#ifdef BOOST_IOSTREAMS_WINDOWS //---------------------------------------------//

file_descriptor::file_descriptor(int fd, bool close_on_exit)
    : pimpl_(new impl_type)
{ open(fd, close_on_exit); }

#endif // #ifdef BOOST_IOSTREAMS_WINDOWS //-----------------------------------//

file_descriptor::file_descriptor( const std::string& path,
                                  BOOST_IOS::openmode mode )
    : pimpl_(new impl_type)
{ open(path, mode); }

file_descriptor::file_descriptor( const char* path,
                                  BOOST_IOS::openmode mode )
    : pimpl_(new impl_type)
{ open(path, mode); }

file_descriptor::file_descriptor(const file_descriptor& other) 
    : pimpl_(other.pimpl_) 
    { }

void file_descriptor::open(handle_type fd, bool close_on_exit)
{ pimpl_->open(fd, close_on_exit); }

#ifdef BOOST_IOSTREAMS_WINDOWS //---------------------------------------------//

void file_descriptor::open(int fd, bool close_on_exit)
{ pimpl_->open(fd, close_on_exit); }

#endif // #ifdef BOOST_IOSTREAMS_WINDOWS //-----------------------------------//

void file_descriptor::open(const std::string& path, BOOST_IOS::openmode mode)
{ open(detail::path(path), mode); }

void file_descriptor::open(const char* path, BOOST_IOS::openmode mode)
{ open(detail::path(path), mode); }

bool file_descriptor::is_open() const { return pimpl_->is_open(); }

void file_descriptor::close() { pimpl_->close(); }

std::streamsize file_descriptor::read(char_type* s, std::streamsize n)
{ return pimpl_->read(s, n); }

std::streamsize file_descriptor::write(const char_type* s, std::streamsize n)
{ return pimpl_->write(s, n); }

std::streampos file_descriptor::seek(stream_offset off, BOOST_IOS::seekdir way)
{ return pimpl_->seek(off, way); }

detail::file_handle file_descriptor::handle() const { return pimpl_->handle_; }

void file_descriptor::init() { pimpl_.reset(new impl_type); }

void file_descriptor::open(
    const detail::path& path, 
    BOOST_IOS::openmode mode, 
    BOOST_IOS::openmode base )
{
    mode |= base;
    pimpl_->open(path, mode);
}
                    
//------------------Implementation of file_descriptor_source------------------//

file_descriptor_source::file_descriptor_source(
    handle_type fd, bool close_on_exit)
{ open(fd, close_on_exit); }

#ifdef BOOST_IOSTREAMS_WINDOWS //---------------------------------------------//

file_descriptor_source::file_descriptor_source(int fd, bool close_on_exit)
{ open(fd, close_on_exit); }

#endif // #ifdef BOOST_IOSTREAMS_WINDOWS //-----------------------------------//

file_descriptor_source::file_descriptor_source(
    const std::string& path, BOOST_IOS::openmode mode)
{ open(path, mode); }

file_descriptor_source::file_descriptor_source(
    const char* path, BOOST_IOS::openmode mode)
{ open(path, mode); }

file_descriptor_source::file_descriptor_source(
    const file_descriptor_source& other) 
        : file_descriptor(static_cast<const file_descriptor&>(other)) 
    { }

void file_descriptor_source::open(handle_type fd, bool close_on_exit)
{ file_descriptor::open(fd, close_on_exit);  }

#ifdef BOOST_IOSTREAMS_WINDOWS //---------------------------------------------//

void file_descriptor_source::open(int fd, bool close_on_exit)
{ file_descriptor::open(fd, close_on_exit); }

#endif // #ifdef BOOST_IOSTREAMS_WINDOWS //-----------------------------------//

void file_descriptor_source::open(
    const std::string& path, BOOST_IOS::openmode mode)
{ open(detail::path(path), mode); }

void file_descriptor_source::open(
    const char* path, BOOST_IOS::openmode mode)
{ open(detail::path(path), mode); }

void file_descriptor_source::open(
    const detail::path& path, BOOST_IOS::openmode mode)
{ 
    if (mode & (BOOST_IOS::out | BOOST_IOS::app | BOOST_IOS::trunc))
        throw BOOST_IOSTREAMS_FAILURE("invalid mode");
    file_descriptor::open(path, mode, BOOST_IOS::in); 
}
                    
//------------------Implementation of file_descriptor_sink--------------------//

file_descriptor_sink::file_descriptor_sink(
    handle_type fd, bool close_on_exit)
{ open(fd, close_on_exit); }

#ifdef BOOST_IOSTREAMS_WINDOWS //---------------------------------------------//

file_descriptor_sink::file_descriptor_sink(int fd, bool close_on_exit)
{ open(fd, close_on_exit); }

#endif // #ifdef BOOST_IOSTREAMS_WINDOWS //-----------------------------------//

file_descriptor_sink::file_descriptor_sink(
    const std::string& path, BOOST_IOS::openmode mode)
{ open(path, mode); }

file_descriptor_sink::file_descriptor_sink(
    const char* path, BOOST_IOS::openmode mode)
{ open(path, mode); }

file_descriptor_sink::file_descriptor_sink(const file_descriptor_sink& other) 
    : file_descriptor(static_cast<const file_descriptor&>(other)) 
    { }

void file_descriptor_sink::open(handle_type fd, bool close_on_exit)
{ file_descriptor::open(fd, close_on_exit);  }

#ifdef BOOST_IOSTREAMS_WINDOWS //---------------------------------------------//

void file_descriptor_sink::open(int fd, bool close_on_exit)
{ file_descriptor::open(fd, close_on_exit); }

#endif // #ifdef BOOST_IOSTREAMS_WINDOWS //-----------------------------------//

void file_descriptor_sink::open(
    const std::string& path, BOOST_IOS::openmode mode)
{ open(detail::path(path), mode); }

void file_descriptor_sink::open(
    const char* path, BOOST_IOS::openmode mode)
{ open(detail::path(path), mode); }

void file_descriptor_sink::open(
    const detail::path& path, BOOST_IOS::openmode mode)
{ 
    if (mode & BOOST_IOS::in)
        throw BOOST_IOSTREAMS_FAILURE("invalid mode");
    file_descriptor::open(path, mode, BOOST_IOS::out); 
}

} } // End namespaces iostreams, boost.

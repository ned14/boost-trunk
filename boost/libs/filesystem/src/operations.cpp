//  operations.cpp  ----------------------------------------------------------//

//  Copyright � 2002 Beman Dawes
//  Copyright � 2001 Dietmar K�hl
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
//  at http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/filesystem

//----------------------------------------------------------------------------// 

// define BOOST_FILESYSTEM_SOURCE so that <boost/filesystem/config.hpp> knows
// the library is being built (possibly exporting rather than importing code)
#define BOOST_FILESYSTEM_SOURCE 

#define _USE_FILE_OFFSET_BITS 64 // at worst, these defines may have no effect,
#define __USE_FILE_OFFSET64 // but that is harmless on Windows and on POSIX
      // 64-bit systems or on 32-bit systems which don't have files larger 
      // than can be represented by a traditional POSIX/UNIX off_t type. 
      // OTOH, defining them should kick in 64-bit off_t's (and thus 
      // st_size) on 32-bit systems that provide the Large File
      // Support (LFS) interface, such as Linux, Solaris, and IRIX.
      // The defines are given before any headers are included to
      // ensure that they are available to all included headers.
      // That is required at least on Solaris, and possibly on other
      // systems as well.

#include <boost/filesystem/operations.hpp>
#include <boost/scoped_array.hpp>
#include <boost/throw_exception.hpp>
#include <boost/detail/workaround.hpp>

namespace fs = boost::filesystem;

# if defined(BOOST_WINDOWS_API)
#   include "windows.h"
#   if defined(__BORLANDC__) || defined(__MWERKS__)
#     if defined(__BORLANDC__)
        using std::time_t;
#     endif
#     include "utime.h"
#   else
#     include "sys/utime.h"
#   endif

// For Windows, the xxxA form of various function names is used to avoid
// inadvertently getting wide forms of the functions. (The undecorated
// forms are actually macros, so can misfire if the user has various
// other macros defined. There was a bug report of this happening.)

# else // BOOST_POSIX_API
#   include <sys/types.h>
#   include "dirent.h"
#   include "unistd.h"
#   include "fcntl.h"
#   include "utime.h"
# endif

#include <sys/stat.h>  // even on Windows some functions use stat()
#include <string>
#include <cstring>
#include <cstdio>      // for remove, rename
#include <cerrno>
#include <cassert>
//#include <iostream>    // for debugging only; comment out when not in use

#ifdef BOOST_NO_STDC_NAMESPACE
namespace std { using ::strcmp; using ::remove; using ::rename; }
#endif

//  helpers  -----------------------------------------------------------------//

namespace
{
  static const fs::directory_iterator end_itr;
  bool is_empty_directory( const std::string & dir_path )
  {
    return fs::directory_iterator(fs::path(dir_path)) == end_itr;
  }

#ifdef BOOST_WINDOWS_API
  
  DWORD get_file_attributes( const char * ph )
    { return ::GetFileAttributesA( ph ); }

  DWORD get_file_attributes( const wchar_t * ph )
    { return ::GetFileAttributesW( ph ); }

  template< class String >
  inline bool exists_template( const String & ph )
  {
    if ( get_file_attributes( ph.c_str() ) == 0xFFFFFFFF )
    {
        UINT err = ::GetLastError();
        if((err == ERROR_FILE_NOT_FOUND)
          || (err == ERROR_INVALID_PARAMETER)
          || (err == ERROR_PATH_NOT_FOUND)
          || (err == ERROR_INVALID_NAME)
          || (err == ERROR_BAD_NETPATH ))
          return false; // GetFileAttributes failed because the path does not exist
        // for any other error we assume the file does exist and fall through,
        // this may not be the best policy though...  (JM 20040330)
        return true;
    }
    return true;
  }

  template< class String >
  inline bool is_accessible_template( const String & ph )
  {
    return get_file_attributes( ph.c_str() ) != 0xFFFFFFFF;
  }

  template< class String >
  boost::filesystem::detail::query_pair
  is_directory_template( const String & ph )
  {
    DWORD attributes = get_file_attributes( ph.c_str() );
    return std::make_pair(
      attributes == 0xFFFFFFFF ? ::GetLastError() : 0,
      (attributes & FILE_ATTRIBUTE_DIRECTORY) != 0 );
  }

  static const fs::wdirectory_iterator wend_itr;
  bool is_empty_directory( const std::wstring & dir_path )
  {
    return fs::wdirectory_iterator(fs::wpath(dir_path)) == wend_itr;
  }

  BOOL get_file_attributes_ex( const char * ph,
    WIN32_FILE_ATTRIBUTE_DATA & fad )
  { return ::GetFileAttributesExA( ph, ::GetFileExInfoStandard, &fad ); }

  BOOL get_file_attributes_ex( const wchar_t * ph,
    WIN32_FILE_ATTRIBUTE_DATA & fad )
  { return ::GetFileAttributesExW( ph, ::GetFileExInfoStandard, &fad ); }
      
  template< class String >
  boost::filesystem::detail::query_pair
  is_empty_template( const String & ph )
  {
    WIN32_FILE_ATTRIBUTE_DATA fad;
    if ( get_file_attributes_ex( ph.c_str(), fad ) == 0 )
      return std::make_pair( ::GetLastError(), false );    
    return std::make_pair( 0,
      ( fad.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
        ? is_empty_directory( ph )
        :( !fad.nFileSizeHigh && !fad.nFileSizeLow ) );
  }

  HANDLE create_file( const char * ph, DWORD dwDesiredAccess,
    DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes,
    HANDLE hTemplateFile )
  {
    return ::CreateFileA( ph, dwDesiredAccess, dwShareMode,
      lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes,
      hTemplateFile );
  }

  HANDLE create_file( const wchar_t * ph, DWORD dwDesiredAccess,
    DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes,
    HANDLE hTemplateFile )
  {
    return ::CreateFileW( ph, dwDesiredAccess, dwShareMode,
      lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes,
      hTemplateFile );
  }

  // Thanks to Jeremy Maitin-Shepard for much help and for permission to
  // base the equivalent() implementation on portions of his 
  // file-equivalence-win32.cpp experimental code.
  struct handle_wrapper
  {
    HANDLE handle;
    handle_wrapper( HANDLE h )
      : handle(h) {}
    ~handle_wrapper()
    {
      if ( handle != INVALID_HANDLE_VALUE )
        ::CloseHandle(handle);
    }
  };

  template< class String >
  boost::filesystem::detail::query_pair
  equivalent_template( const String & ph1, const String & ph2 )
  {
    // Note well: Physical location on external media is part of the
    // equivalence criteria. If there are no open handles, physical location
    // can change due to defragmentation or other relocations. Thus handles
    // must be held open until location information for both paths has
    // been retrieved.
    handle_wrapper p1(
      create_file(
          ph1.c_str(),
          0,
          FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
          0,
          OPEN_EXISTING,
          FILE_FLAG_BACKUP_SEMANTICS,
          0 ) );
    int error1(0); // save error code in case we have to throw
    if ( p1.handle == INVALID_HANDLE_VALUE )
      error1 = ::GetLastError();
    handle_wrapper p2(
      create_file(
          ph2.c_str(),
          0,
          FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
          0,
          OPEN_EXISTING,
          FILE_FLAG_BACKUP_SEMANTICS,
          0 ) );
    if ( p1.handle == INVALID_HANDLE_VALUE
      || p2.handle == INVALID_HANDLE_VALUE )
    {
      if ( p1.handle != INVALID_HANDLE_VALUE
        || p2.handle != INVALID_HANDLE_VALUE )
        { return std::make_pair( 0, false ); }
      assert( p1.handle == INVALID_HANDLE_VALUE
        && p2.handle == INVALID_HANDLE_VALUE );
        { return std::make_pair( error1, false ); }
    }
    // at this point, both handles are known to be valid
    BY_HANDLE_FILE_INFORMATION info1, info2;
    if ( !::GetFileInformationByHandle( p1.handle, &info1 ) )
      { return std::make_pair( ::GetLastError(), false ); }
    if ( !::GetFileInformationByHandle( p2.handle, &info2 ) )
      { return std::make_pair( ::GetLastError(), false ); }
    // In theory, volume serial numbers are sufficient to distinguish between
    // devices, but in practice VSN's are sometimes duplicated, so last write
    // time and file size are also checked.
      return std::make_pair( 0,
        info1.dwVolumeSerialNumber == info2.dwVolumeSerialNumber
        && info1.nFileIndexHigh == info2.nFileIndexHigh
        && info1.nFileIndexLow == info2.nFileIndexLow
        && info1.nFileSizeHigh == info2.nFileSizeHigh
        && info1.nFileSizeLow == info2.nFileSizeLow
        && info1.ftLastWriteTime.dwLowDateTime
          == info2.ftLastWriteTime.dwLowDateTime
        && info1.ftLastWriteTime.dwHighDateTime
          == info2.ftLastWriteTime.dwHighDateTime );
  }

  template< class String >
  boost::filesystem::detail::intmax_pair
  file_size_template( const String & ph )
  {
    WIN32_FILE_ATTRIBUTE_DATA fad;
    // by now, intmax_t is 64-bits on all Windows compilers
    if ( get_file_attributes_ex( ph.c_str(), fad ) == 0 )
      return std::make_pair( ::GetLastError(), 0 );    
    if ( (fad.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) !=0 )
      return std::make_pair( ERROR_FILE_NOT_FOUND, 0 );
    return std::make_pair( 0,
      (static_cast<boost::intmax_t>(fad.nFileSizeHigh)
        << (sizeof(fad.nFileSizeLow)*8))
      + fad.nFileSizeLow );
  }

  inline DWORD get_current_directory( DWORD sz, char * buf )
    { return ::GetCurrentDirectoryA( sz, buf ); } 

  inline DWORD get_current_directory( DWORD sz, wchar_t * buf )
    { return ::GetCurrentDirectoryW( sz, buf ); } 

  template< class String >
  boost::filesystem::system_error_type
  get_current_path_template( String & ph )
  {
    DWORD sz;
    if ( (sz = get_current_directory( 0,
      static_cast<typename String::value_type*>(0) )) == 0 )
      { sz = 1; }
    boost::scoped_array<typename String::value_type>
      buf( new typename String::value_type[sz] );
    if ( get_current_directory( sz, buf.get() ) == 0 )
      return ::GetLastError();
    ph = buf.get();
    return 0;
  }

  std::size_t get_full_path_name(
    const std::string & ph, std::size_t len, char * buf, char ** p )
  {
    return static_cast<std::size_t>(
      ::GetFullPathNameA( ph.c_str(),
        static_cast<DWORD>(len), buf, p ));
  } 

  std::size_t get_full_path_name(
    const std::wstring & ph, std::size_t len, wchar_t * buf, wchar_t ** p )
  {
    return static_cast<std::size_t>(
      ::GetFullPathNameW( ph.c_str(),
        static_cast<DWORD>(len), buf, p ));
  } 

  const std::size_t buf_size( 128 );

  template<class String>
  boost::filesystem::system_error_type
  get_full_path_name_template( const String & ph, String & target )
  {
    typename String::value_type buf[buf_size];
    typename String::value_type * pfn;
    std::size_t len = get_full_path_name( ph,
      sizeof(buf) , buf, &pfn );
    if ( len == 0 ) return ::GetLastError();
    if ( len > buf_size )
    {
      boost::scoped_array<typename String::value_type>
        big_buf( new typename String::value_type[len] );
      if ( (len=get_full_path_name( ph, len , big_buf.get(), &pfn ))
        == 0 ) return ::GetLastError();
      big_buf[len] = '\0';
      target = big_buf.get();
      return 0;
    }
    buf[len] = '\0';
    target = buf;
    return 0;
  }

  template<class String>
  boost::filesystem::system_error_type
  get_file_write_time( const String & ph, FILETIME & last_write_time )
  {
    handle_wrapper hw(
      create_file( ph.c_str(), 0,
        FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
        OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, 0 ) );
    if ( hw.handle == INVALID_HANDLE_VALUE )
      return ::GetLastError();
    return ::GetFileTime( hw.handle, 0, 0, &last_write_time ) != 0
      ? 0 : ::GetLastError();
  }

  template<class String>
  boost::filesystem::system_error_type
  set_file_write_time( const String & ph, const FILETIME & last_write_time )
  {
    handle_wrapper hw(
      create_file( ph.c_str(), FILE_WRITE_ATTRIBUTES,
        FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
        OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, 0 ) );
    if ( hw.handle == INVALID_HANDLE_VALUE )
      return ::GetLastError();
    return ::SetFileTime( hw.handle, 0, 0, &last_write_time ) != 0
      ? 0 : ::GetLastError();
  }

  // these constants come from inspecting some Microsoft sample code
  std::time_t to_time_t( const FILETIME & ft )
  {
    __int64 t = (static_cast<__int64>( ft.dwHighDateTime ) << 32)
      + ft.dwLowDateTime;
    t -= 116444736000000000;
    t /= 10000000;
    return static_cast<std::time_t>( t );
  }

  void to_FILETIME( std::time_t t, FILETIME & ft )
  {
    __int64 temp = t;
    temp *= 10000000;
    temp += 116444736000000000;
    ft.dwLowDateTime = static_cast<DWORD>( temp );
    ft.dwHighDateTime = static_cast<DWORD>( temp >> 32 );
  }

  template<class String>
  boost::filesystem::detail::time_pair
  last_write_time_template( const String & ph )
  {
    FILETIME lwt;
    boost::filesystem::system_error_type result
      = get_file_write_time( ph, lwt );
    return std::make_pair( result, to_time_t( lwt ) );
  }

  template<class String>
  boost::filesystem::system_error_type
  last_write_time_template( const String & ph, const std::time_t new_time )
  {
    FILETIME lwt;
    to_FILETIME( new_time, lwt );
    return set_file_write_time( ph, lwt );
  }

  bool remove_directory( const std::string & ph )
    { return ::RemoveDirectoryA( ph.c_str() ) != 0; }
  bool remove_directory( const std::wstring & ph )
    { return ::RemoveDirectoryW( ph.c_str() ) != 0; }
  
  bool delete_file( const std::string & ph )
    { return ::DeleteFileA( ph.c_str() ) != 0; }
  bool delete_file( const std::wstring & ph )
    { return ::DeleteFileW( ph.c_str() ) != 0; }
  
  template<class String>
  boost::filesystem::system_error_type
  remove_template( const String & ph )
  {
    fs::detail::query_pair result( fs::detail::is_directory_api( ph ) );
    if ( result.first != 0 ) return result.first;
    if ( result.second )
    {
      if ( !remove_directory( ph ) )
        return ::GetLastError();
    }
    else
    {
      if ( !delete_file( ph ) ) return ::GetLastError();
    }
    return 0;
  }

  inline boost::filesystem::system_error_type
  move_file( const char * from, const char * to )
   { return ::MoveFileA( from, to ); }

  inline boost::filesystem::system_error_type
  move_file( const wchar_t * from, const wchar_t * to )
   { return ::MoveFileW( from, to ); }

    template<class String>
  boost::filesystem::system_error_type
  inline rename_template( const String & from, const String & to )
  {
    return move_file( from.c_str(), to.c_str() )
      ? 0 : ::GetLastError();
  }

  inline bool create_directory( const std::string & dir )
    {  return ::CreateDirectoryA( dir.c_str(), 0 ) != 0; }
  inline bool create_directory( const std::wstring & dir )
    {  return ::CreateDirectoryW( dir.c_str(), 0 ) != 0; }
         
  template<class String>
  boost::filesystem::detail::query_pair
  create_directory_template( const String & dir_ph )
  {
    boost::filesystem::system_error_type error(0);
    if ( create_directory( dir_ph ) ) return std::make_pair( error, true );
    error = ::GetLastError();
    if ( error != ERROR_ALREADY_EXISTS 
      || !fs::detail::is_directory_api( dir_ph ).second )
      return std::make_pair( error, false );
    return std::make_pair( 0, false );
  }

#endif
} // unnamed namespace

namespace boost
{
  namespace filesystem
  {
    namespace detail
    {

//  free functions  ----------------------------------------------------------//

      BOOST_FILESYSTEM_DECL bool possible_large_file_size_support()
      {
#   ifdef BOOST_POSIX_API
        struct stat lcl_stat;
        return sizeof( lcl_stat.st_size ) > 4;
#   else
        return true;
#   endif
      }

#   ifdef BOOST_WINDOWS_API

      BOOST_FILESYSTEM_DECL bool exists_api( const std::string & ph )
        { return exists_template( ph ); }

      BOOST_FILESYSTEM_DECL bool exists_api( const std::wstring & ph )
        { return exists_template( ph ); }

      BOOST_FILESYSTEM_DECL bool is_accessible_api( const std::string & ph )
        { return is_accessible_template( ph ); }

      BOOST_FILESYSTEM_DECL bool is_accessible_api( const std::wstring & ph )
        { return is_accessible_template( ph ); }

      // suggested by Walter Landry
      BOOST_FILESYSTEM_DECL bool symbolic_link_exists_api( const std::string & )
        { return false; }

      BOOST_FILESYSTEM_DECL bool symbolic_link_exists_api( const std::wstring & )
        { return false; }

      BOOST_FILESYSTEM_DECL
      fs::detail::query_pair is_directory_api( const std::string & ph )
        { return is_directory_template( ph ); }

      BOOST_FILESYSTEM_DECL
      fs::detail::query_pair is_directory_api( const std::wstring & ph )
        { return is_directory_template( ph ); }

      BOOST_FILESYSTEM_DECL
      fs::detail::query_pair is_empty_api( const std::string & ph )
        { return is_empty_template( ph ); }

      BOOST_FILESYSTEM_DECL
      fs::detail::query_pair is_empty_api( const std::wstring & ph )
        { return is_empty_template( ph ); }

      BOOST_FILESYSTEM_DECL
      fs::detail::query_pair
      equivalent_api( const std::string & ph1, const std::string & ph2 )
        { return equivalent_template( ph1, ph2 ); }

      BOOST_FILESYSTEM_DECL
      fs::detail::query_pair
      equivalent_api( const std::wstring & ph1, const std::wstring & ph2 )
        { return equivalent_template( ph1, ph2 ); }

      BOOST_FILESYSTEM_DECL
      fs::detail::intmax_pair file_size_api( const std::string & ph )
        { return file_size_template( ph ); }

      BOOST_FILESYSTEM_DECL
      fs::detail::intmax_pair file_size_api( const std::wstring & ph )
        { return file_size_template( ph ); }

      BOOST_FILESYSTEM_DECL
      boost::filesystem::system_error_type 
      get_current_path_api( std::string & ph )
        { return get_current_path_template( ph ); }

      BOOST_FILESYSTEM_DECL
      boost::filesystem::system_error_type 
      get_current_path_api( std::wstring & ph )
        { return get_current_path_template( ph ); }

      BOOST_FILESYSTEM_DECL boost::filesystem::system_error_type
        get_full_path_name_api( const std::string & ph, std::string & target )
         { return get_full_path_name_template( ph, target ); }

      BOOST_FILESYSTEM_DECL boost::filesystem::system_error_type
        get_full_path_name_api( const std::wstring & ph, std::wstring & target )
         { return get_full_path_name_template( ph, target ); }

      BOOST_FILESYSTEM_DECL time_pair
        last_write_time_api( const std::string & ph )
          { return last_write_time_template( ph ); }
 
      BOOST_FILESYSTEM_DECL time_pair
        last_write_time_api( const std::wstring & ph )
          { return last_write_time_template( ph ); }
 
      BOOST_FILESYSTEM_DECL boost::filesystem::system_error_type
        last_write_time_api( const std::string & ph, std::time_t new_value )
          { return last_write_time_template( ph, new_value ); }

      BOOST_FILESYSTEM_DECL boost::filesystem::system_error_type
        last_write_time_api( const std::wstring & ph, std::time_t new_value )
          { return last_write_time_template( ph, new_value ); }

      BOOST_FILESYSTEM_DECL fs::detail::query_pair
      create_directory_api( const std::string & ph )
        { return create_directory_template( ph ); }

      BOOST_FILESYSTEM_DECL fs::detail::query_pair
      create_directory_api( const std::wstring & ph )
        { return create_directory_template( ph ); }

      BOOST_FILESYSTEM_DECL boost::filesystem::system_error_type
      remove_api( const std::string & ph ) { return remove_template( ph ); }

      BOOST_FILESYSTEM_DECL boost::filesystem::system_error_type
      remove_api( const std::wstring & ph ) { return remove_template( ph ); }

      BOOST_FILESYSTEM_DECL boost::filesystem::system_error_type
      rename_api( const std::string & from, const std::string & to )
        { return rename_template( from, to ); }

      BOOST_FILESYSTEM_DECL boost::filesystem::system_error_type
      rename_api( const std::wstring & from, const std::wstring & to )
        { return rename_template( from, to ); }

      BOOST_FILESYSTEM_DECL bool create_file_api( const std::wstring & ph,
        std::ios_base::openmode mode ) // true if succeeds
      {
        DWORD access(
          ((mode & std::ios_base::in) == 0 ? 0 : GENERIC_READ)
          | ((mode & std::ios_base::out) == 0 ? 0 : GENERIC_WRITE) );

        DWORD disposition(0); // see 27.8.1.3 Table 92
        if ( (mode&~std::ios_base::binary)
          == (std::ios_base::out|std::ios_base::app) )
          disposition = OPEN_ALWAYS;
        else if ( (mode&~(std::ios_base::binary|std::ios_base::out))
          == std::ios_base::in ) disposition = OPEN_EXISTING;
        else if ( ((mode&~(std::ios_base::binary|std::ios_base::trunc))
          == std::ios_base::out )
          || ((mode&~std::ios_base::binary)
          == (std::ios_base::in|std::ios_base::out|std::ios_base::trunc)) )
          disposition = CREATE_ALWAYS;
        else assert( 0 && "invalid mode argument" );

        HANDLE handle ( ::CreateFileW( ph.c_str(), access,
          FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
          disposition, (mode &std::ios_base::out) != 0
          ? FILE_ATTRIBUTE_ARCHIVE : FILE_ATTRIBUTE_NORMAL, 0 ) );
        if ( handle == INVALID_HANDLE_VALUE ) return false;
        ::CloseHandle( handle );
        return true;
      }

      BOOST_FILESYSTEM_DECL std::string narrow_path_api(
        const std::wstring & ph ) // return is empty if fails
      {
        std::string narrow_short_form;
        std::wstring short_form;
        for ( DWORD buf_sz( static_cast<DWORD>( ph.size()+1 ));; )
        {
          boost::scoped_array<wchar_t> buf( new wchar_t[buf_sz] );
          DWORD sz( ::GetShortPathNameW( ph.c_str(), buf.get(), buf_sz ) );
          if ( sz == 0 ) return narrow_short_form;
          if ( sz <= buf_sz )
          {
            short_form += buf.get();
            break;
          }
          buf_sz = sz + 1;
        }
        for ( std::wstring::iterator it( short_form.begin() );
          it != short_form.end(); ++it )
        {
          // my expectation is that Unicode characters in long names will be
          // converted to 8-bit characters in the short 8.3 form names; this
          // expectation is based on observation rather than Windows API
          // documentation.
          assert( (*it & 0xFF) == *it || "program logic error; see program comments" );
          if ( (*it & 0xFF) != *it )
            boost::throw_exception( "program logic error" );
          narrow_short_form += static_cast<char>( *it );
        }
        return narrow_short_form;
      }

      BOOST_FILESYSTEM_DECL boost::filesystem::system_error_type
      dir_itr_first(
        void *& handle, const std::string & dir, std::string & target )
      // Note: an empty root directory has no "." or ".." entries, so this
      // causes a ERROR_FILE_NOT_FOUND error which we do not considered an
      // error. It is treated as eof instead.
      {
        std::string dirpath( dir + "/*" );
        WIN32_FIND_DATAA data;
        if ( (handle = ::FindFirstFileA( dirpath.c_str(), &data ))
          == INVALID_HANDLE_VALUE )
        { 
          handle = 0;
          return ::GetLastError() == ERROR_FILE_NOT_FOUND
            ? 0 : ::GetLastError();
        }
        target = data.cFileName;
        return 0;
      }

      BOOST_FILESYSTEM_DECL boost::filesystem::system_error_type
      dir_itr_first(
        void *& handle, const std::wstring & dir, std::wstring & target )
      {
        std::wstring dirpath( dir + L"/*" );
        WIN32_FIND_DATAW data;
        if ( (handle = ::FindFirstFileW( dirpath.c_str(), &data ))
          == INVALID_HANDLE_VALUE )
        { 
          handle = 0;
          return ::GetLastError() == ERROR_FILE_NOT_FOUND
            ? 0 : ::GetLastError();
        }
        target = data.cFileName;
        return 0;
      }  

      BOOST_FILESYSTEM_DECL boost::filesystem::system_error_type
      dir_itr_close( void *& handle )
      {
        if ( handle != 0 )
        {
          bool ok = ::FindClose( handle ) != 0;
          handle = 0;
          return ok ? 0 : ::GetLastError();
        }
        return 0;
      }

      BOOST_FILESYSTEM_DECL boost::filesystem::system_error_type
      dir_itr_increment( void *& handle, std::string & target )
      {
        WIN32_FIND_DATAA data;
        if ( ::FindNextFileA( handle, &data ) == 0 ) // fails
        {
          int error = ::GetLastError();
          dir_itr_close( handle );
          return error == ERROR_NO_MORE_FILES ? 0 : error;
        }
        target = data.cFileName;
        return 0;
      }

      BOOST_FILESYSTEM_DECL boost::filesystem::system_error_type
      dir_itr_increment( void *& handle, std::wstring & target )
      {
        WIN32_FIND_DATAW data;
        if ( ::FindNextFileW( handle, &data ) == 0 ) // fails
        {
          int error = ::GetLastError();
          dir_itr_close( handle );
          return error == ERROR_NO_MORE_FILES ? 0 : error;
        }
        target = data.cFileName;
        return 0;
      }

#   else // BOOST_POSIX_API

      BOOST_FILESYSTEM_DECL bool
      exists_api( const std::string & ph )
      {
        struct stat path_stat;
        if ( ::stat( ph.c_str(), &path_stat ) != 0 )
        {
          if ( ( errno == ENOENT ) || ( errno == ENOTDIR ) )
              return false;  // stat failed because the path does not exist
          // for any other error we assume the file does exist and fall through,
          // this may not be the best policy though...  (JM 20040330)
        }
        return true;
      }

      BOOST_FILESYSTEM_DECL bool
      is_accessible_api( const std::string & ph )
      {
        struct stat path_stat;
        return ::stat( ph.c_str(), &path_stat ) == 0;
      }

      // suggested by Walter Landry
      BOOST_FILESYSTEM_DECL bool
      symbolic_link_exists_api( const std::string & ph )
      {
        struct stat path_stat;
        return ::lstat( ph.c_str(), &path_stat ) == 0
          && S_ISLNK( path_stat.st_mode );
      }

      BOOST_FILESYSTEM_DECL query_pair
      is_directory_api( const std::string & ph )
      {
        struct stat ph_stat;
        if ( ::stat( ph.c_str(), &ph_stat ) != 0 )
          return std::make_pair( errno, false );
        return std::make_pair( 0, S_ISDIR( ph_stat.st_mode ) );
      }

      BOOST_FILESYSTEM_DECL query_pair
      is_empty_api( const std::string & ph )
      {
        struct stat path_stat;
        if ( (::stat( ph.c_str(), &path_stat )) != 0 )
          return std::make_pair( errno, false );        
        return std::make_pair( 0, S_ISDIR( path_stat.st_mode )
          ? is_empty_directory( ph )
          : path_stat.st_size == 0 );
      }

      BOOST_FILESYSTEM_DECL query_pair
      equivalent_api( const std::string & ph1, const std::string & ph2 )
      {
        struct stat s2;
        int e2( ::stat( ph2.c_str(), &s2 ) );
        struct stat s1;
        int e1( ::stat( ph1.c_str(), &s1 ) );
        if ( e1 != 0 || e2 != 0 )
          return std::make_pair( e1 != 0 && e2 != 0 ? errno : 0, false );
        // at this point, both stats are known to be valid
        return std::make_pair( 0,
            s1.st_dev == s2.st_dev
            && s1.st_ino == s2.st_ino
            // According to the POSIX stat specs, "The st_ino and st_dev fields
            // taken together uniquely identify the file within the system."
            // Just to be sure, size and mod time are also checked.
            && s1.st_size == s2.st_size
            && s1.st_mtime == s2.st_mtime );
      }
 
      BOOST_FILESYSTEM_DECL intmax_pair
      file_size_api( const std::string & ph )
      {
        struct stat path_stat;
        if ( ::stat( ph.c_str(), &path_stat ) != 0 )
          return std::make_pair( errno, 0 );
        if ( S_ISDIR( path_stat.st_mode ) )
          return std::make_pair( EISDIR, 0 ); 
        return std::make_pair( 0,
          static_cast<boost::intmax_t>(path_stat.st_size) );
      }

      BOOST_FILESYSTEM_DECL time_pair 
      last_write_time_api( const std::string & ph )
      {
        struct stat path_stat;
        if ( ::stat( ph.c_str(), &path_stat ) != 0 )
          return std::make_pair( errno, 0 );
        return std::make_pair( 0, path_stat.st_mtime );
      }

      BOOST_FILESYSTEM_DECL fs::system_error_type
      last_write_time_api( const std::string & ph, std::time_t new_value )
      {
        struct stat path_stat;
        if ( ::stat( ph.c_str(), &path_stat ) != 0 ) return errno;
        ::utimbuf buf;
        buf.actime = path_stat.st_atime; // utime() updates access time too:-(
        buf.modtime = new_value;
        return ::utime( ph.c_str(), &buf ) != 0 ? errno : 0;
      }

      BOOST_FILESYSTEM_DECL fs::system_error_type 
      get_current_path_api( std::string & ph )
      {
        for ( long path_max = 32;; path_max *=2 ) // loop 'til buffer large enough
        {
          boost::scoped_array<char>
            buf( new char[static_cast<std::size_t>(path_max)] );
          if ( ::getcwd( buf.get(), static_cast<std::size_t>(path_max) ) == 0 )
          {
            if ( errno != ERANGE ) return errno;
          }
          else
          {
            ph = buf.get();
            break;
          }
        }
        return 0;
      }

      BOOST_FILESYSTEM_DECL query_pair
      create_directory_api( const std::string & dir_ph )
      {
        if ( ::mkdir( dir_ph.c_str(), S_IRWXU|S_IRWXG|S_IRWXO ) == 0 )
          return std::make_pair( 0, true );
        if ( errno != EEXIST ) return std::make_pair( errno, false );
        if ( !is_directory_api( dir_ph ).second )
          return std::make_pair( ENOTDIR, false );
        return std::make_pair( 0, false );
      }

      BOOST_FILESYSTEM_DECL boost::filesystem::system_error_type
      remove_api( const std::string & ph )
      {
        // note that the POSIX behavior for symbolic links is what we want;
        // the link rather than what it points to is deleted
        if ( std::remove( ph.c_str() ) != 0 )
        {
          int error = errno;
          // POSIX says "If the directory is not an empty directory, rmdir()
          // shall fail and set errno to EEXIST or ENOTEMPTY."
          // Linux uses ENOTEMPTY, Solaris uses EEXIST.
          if ( error == EEXIST ) error = ENOTEMPTY;
          return error;
        }
        return 0;
      }

      BOOST_FILESYSTEM_DECL boost::filesystem::system_error_type
      rename_api( const std::string & from, const std::string & to )
      {
        if ( exists_api( to ) ) // POSIX is too permissive so must check
          return EEXIST;
        return std::rename( from.c_str(), to.c_str() ) != 0 
          ? errno : 0;
      }

      BOOST_FILESYSTEM_DECL boost::filesystem::system_error_type
      dir_itr_first(
        void *& handle, const std::string & dir, std::string & target )
      {
        static const std::string dummy_first_name( "." );
        if ( (handle = ::opendir( dir.c_str() )) == 0 ) return errno;
        target = dummy_first_name;
        return 0;
      }  

      BOOST_FILESYSTEM_DECL boost::filesystem::system_error_type
      dir_itr_close( void *& handle )
      {
        if ( handle == 0 ) return 0;
        DIR * h( static_cast<DIR*>(handle) );
        handle = 0;
        return ::closedir( h ) == 0 ? 0 : errno;
      }

      // warning: the only dirent member updated is d_name
      inline int readdir_r_simulator( DIR * dirp, struct dirent * entry,
        struct dirent ** result ) // *result set to 0 on end of directory
        {
    #     if defined(_POSIX_THREAD_SAFE_FUNCTIONS) \
          && defined(_SC_THREAD_SAFE_FUNCTIONS) \
          && _POSIX_THREAD_SAFE_FUNCTIONS >= 0
          if ( ::sysconf( _SC_THREAD_SAFE_FUNCTIONS ) >= 0 )
            { return ::readdir_r( dirp, entry, result ); }
    #     endif

          struct dirent * p;
          errno = 0;
          *result = 0;
          if ( (p = ::readdir( dirp )) == 0 )
            return errno;
          // POSIX specs require entry->d_name be large enough:
          std::strcpy( entry->d_name, p->d_name );
          *result = entry;
          return 0;
        }

      BOOST_FILESYSTEM_DECL boost::filesystem::system_error_type
      dir_itr_increment( void *& handle, std::string & target )
      {
        struct dirent entry, * result;
        int return_code;
        if ( (return_code = readdir_r_simulator( static_cast<DIR*>(handle),
          &entry, &result )) != 0 ) return errno;
        if ( result == 0 ) return dir_itr_close( handle );
        target = entry.d_name;
        return 0;
      }

#   endif
    } // namespace detail
  } // namespace filesystem
} // namespace boost

#if 0
  
namespace boost
{
  namespace filesystem
  {


    BOOST_FILESYSTEM_DECL void copy_file( const path & from_file_ph,
                    const path & to_file_ph )
    {
#   ifdef BOOST_POSIX_API
      // TODO: Ask POSIX experts if this is the best way to copy a file

      const std::size_t buf_sz = 32768;
      boost::scoped_array<char> buf( new char [buf_sz] );
      int infile=0, outfile=0;  // init quiets compiler warning
      struct stat from_stat;

      if ( ::stat( from_file_ph.string().c_str(), &from_stat ) != 0
        || (infile = ::open( from_file_ph.string().c_str(),
                             O_RDONLY )) < 0
        || (outfile = ::open( to_file_ph.string().c_str(),
                              O_WRONLY | O_CREAT | O_EXCL,
                              from_stat.st_mode )) < 0 )
      {
        if ( infile != 0 ) ::close( infile );
        boost::throw_exception( filesystem_error(
          "boost::filesystem::copy_file",
          from_file_ph, to_file_ph, fs::detail::system_error_code() ) );
      }

      ssize_t sz;
      while ( (sz = ::read( infile, buf.get(), buf_sz )) > 0
        && (sz = ::write( outfile, buf.get(), sz )) > 0 ) {}

      ::close( infile );
      ::close( outfile );

      if ( sz != 0 )
#   else
      if ( !::CopyFileA( from_file_ph.string().c_str(),
                      to_file_ph.string().c_str(), /*fail_if_exists=*/true ) )
#   endif
        boost::throw_exception( filesystem_error(
          "boost::filesystem::copy_file",
          from_file_ph, to_file_ph, fs::detail::system_error_code() ) );
    }

  } // namespace filesystem
} // namespace boost
#endif

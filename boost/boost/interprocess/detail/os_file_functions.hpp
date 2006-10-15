//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztañaga 2005-2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_OS_FILE_FUNCTIONS_HPP
#define BOOST_INTERPROCESS_DETAIL_OS_FILE_FUNCTIONS_HPP

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/detail/utilities.hpp>

#if (defined BOOST_WINDOWS) && !(defined BOOST_DISABLE_WIN32)
#  include <boost/interprocess/detail/win32_api.hpp>
#else
#  ifdef BOOST_HAS_UNISTD_H
#     include <fcntl.h>
#     include <unistd.h>
#     include <sys/types.h>
#     include <sys/stat.h>
#     include <errno.h>
#  else
#    error Unknown platform
#  endif
#endif

#include <cstring>
#include <cstdlib>

namespace boost {
namespace interprocess {

#if (defined BOOST_WINDOWS) && !(defined BOOST_DISABLE_WIN32)

typedef void *    handle_t;
typedef long long offset_t;

typedef enum { read_only      = winapi::generic_read
             , read_write     = winapi::generic_read | winapi::generic_write
             , copy_on_write
             , invalid_mode   = 0xffff 
             } mode_t;

typedef enum { file_begin     = winapi::file_begin
             , file_end       = winapi::file_end
             , file_current   = winapi::file_current
             } file_pos_t;

namespace detail{

inline bool create_directory(const char *path)
{  return winapi::create_directory(path, 0); }

inline const char *get_temporary_path()
{  return std::getenv("TMP"); }

inline handle_t create_new_file
   (const char *name, mode_t mode = read_write, bool temporary = false)
{  
   unsigned long attr = temporary ? winapi::file_attribute_temporary : 0;
   return winapi::create_file
      (name, (unsigned int)mode, winapi::create_new, attr);  
}

inline handle_t create_or_open_file
   (const char *name, mode_t mode = read_write, bool temporary = false)
{  
   unsigned long attr = temporary ? winapi::file_attribute_temporary : 0;
   return winapi::create_file
      (name, (unsigned int)mode, winapi::open_always, attr);  
}

inline handle_t open_existing_file
   (const char *name, mode_t mode = read_write, bool temporary = false)
{  
   unsigned long attr = temporary ? winapi::file_attribute_temporary : 0;
   return winapi::create_file
      (name, (unsigned int)mode, winapi::open_existing, attr);  
}

inline bool delete_file(const char *name)
{  return winapi::delete_file(name);   }

inline bool truncate_file (handle_t hnd, std::size_t size)
{  
   if(!winapi::set_file_pointer_ex(hnd, size, 0, winapi::file_begin)){
      return false;
   }

   if(!winapi::set_end_of_file(hnd)){
      return false;
   }
   return true;
}

inline bool get_file_size(handle_t hnd, offset_t &size)
{  return winapi::get_file_size(hnd, size);  }

inline bool set_file_pointer(handle_t hnd, offset_t off, file_pos_t pos)
{  return winapi::set_file_pointer_ex(hnd, off, 0, (unsigned long) pos); }

inline bool get_file_pointer(handle_t hnd, offset_t &off)
{  return winapi::set_file_pointer_ex(hnd, 0, &off, winapi::file_current); }

inline bool write_file(handle_t hnd, const void *data, std::size_t numdata)
{  
   unsigned long written;
   return 0 != WriteFile(hnd, data, (unsigned long)numdata, &written, 0);
}

inline handle_t invalid_file()
{  return winapi::invalid_handle_value;  }

inline bool close_file(handle_t hnd)
{  return 0 != winapi::close_handle(hnd);   }

inline bool acquire_file_lock(handle_t hnd)
{  
   static winapi::interprocess_overlapped overlapped;
   const unsigned long len = 0xffffffff;
//   winapi::interprocess_overlapped overlapped;
//   std::memset(&overlapped, 0, sizeof(overlapped));
   return winapi::lock_file_ex
      (hnd, winapi::lockfile_exclusive_lock, 0, len, len, &overlapped);
}

inline bool try_acquire_file_lock(handle_t hnd, bool &acquired)
{  
   const unsigned long len = 0xffffffff;
   winapi::interprocess_overlapped overlapped;
   std::memset(&overlapped, 0, sizeof(overlapped));
   if(!winapi::lock_file_ex
      (hnd, winapi::lockfile_exclusive_lock | winapi::lockfile_fail_immediately, 
       0, len, len, &overlapped)){
      return winapi::get_last_error() == winapi::error_lock_violation ? 
               acquired = false, true : false;
   
   }
   return (acquired = true);
}

inline bool timed_acquire_file_lock
   (handle_t hnd, bool &acquired, const boost::posix_time::ptime &abs_time)
{  
   //Obtain current count and target time
   boost::posix_time::ptime now = 
      boost::posix_time::microsec_clock::universal_time();
   using namespace boost::detail;

   if(now >= abs_time) return false;

   do{
      if(!try_acquire_file_lock(hnd, acquired))
         return false;

      if(acquired)
         return true;
      else{
         now = boost::posix_time::microsec_clock::universal_time();

         if(now >= abs_time){
            acquired = false;
            return true;
         }
         // relinquish current time slice
         winapi::sched_yield();
      }
   }while (true);
}

inline bool release_file_lock(handle_t hnd)
{  
   const unsigned long len = 0xffffffff;
   winapi::interprocess_overlapped overlapped;
   std::memset(&overlapped, 0, sizeof(overlapped));
   return winapi::unlock_file_ex(hnd, 0, len, len, &overlapped);
}

inline bool acquire_file_lock_sharable(handle_t hnd)
{  
   const unsigned long len = 0xffffffff;
   winapi::interprocess_overlapped overlapped;
   std::memset(&overlapped, 0, sizeof(overlapped));
   return winapi::lock_file_ex(hnd, 0, 0, len, len, &overlapped);
}

inline bool try_acquire_file_lock_sharable(handle_t hnd, bool &acquired)
{  
   const unsigned long len = 0xffffffff;
   winapi::interprocess_overlapped overlapped;
   std::memset(&overlapped, 0, sizeof(overlapped));
   if(!winapi::lock_file_ex
      (hnd, winapi::lockfile_fail_immediately, 0, len, len, &overlapped)){
      return winapi::get_last_error() == winapi::error_lock_violation ? 
               acquired = false, true : false;
   }
   return (acquired = true);
}

inline bool timed_acquire_file_lock_sharable
   (handle_t hnd, bool &acquired, const boost::posix_time::ptime &abs_time)
{  
   //Obtain current count and target time
   boost::posix_time::ptime now = 
      boost::posix_time::microsec_clock::universal_time();
   using namespace boost::detail;

   if(now >= abs_time) return false;

   do{
      if(!try_acquire_file_lock_sharable(hnd, acquired))
         return false;

      if(acquired)
         return true;
      else{
         now = boost::posix_time::microsec_clock::universal_time();

         if(now >= abs_time){
            acquired = false;
            return true;
         }
         // relinquish current time slice
         winapi::sched_yield();
      }
   }while (true);
}

inline bool release_file_lock_sharable(handle_t hnd)
{  return release_file_lock(hnd);   }

#else    //#if (defined BOOST_WINDOWS) && !(defined BOOST_DISABLE_WIN32)

typedef int    handle_t;
typedef off_t  offset_t;
typedef enum { read_only      = O_RDONLY
             , read_write     = O_RDWR
             , copy_on_write
             , invalid_mode   = 0xffff 
             } mode_t;

typedef enum { file_begin     = SEEK_SET
             , file_end       = SEEK_END
             , file_current   = SEEK_CUR
             } file_pos_t;

namespace detail{

inline bool create_directory(const char *path)
{  return ::mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0; }

inline const char *get_temporary_path()
{  
   const char *dir = std::getenv("TMPDIR"); 
   if(!dir){
      dir = std::getenv("TMP");
      if(!dir){
         return std::getenv("TEMP");
      }
   }
   return dir;
}

inline handle_t create_new_file
   (const char *name, mode_t mode = read_write, bool temporary = false)
{  
   (void)temporary;
   return ::open(name, ((int)mode) | O_EXCL | O_CREAT, S_IRWXG | S_IRWXO | S_IRWXU); 
}

inline handle_t create_or_open_file
   (const char *name, mode_t mode = read_write, bool temporary = false)
{  
   (void)temporary;
   return ::open(name, ((int)mode) | O_CREAT, S_IRWXG | S_IRWXO | S_IRWXU); 
}

inline handle_t open_existing_file
   (const char *name, mode_t mode = read_write, bool temporary = false)
{  
   (void)temporary;
   return ::open(name, (int)mode, S_IRWXG | S_IRWXO | S_IRWXU); 
}

inline bool delete_file(const char *name)
{  return ::unlink(name);   }

inline bool truncate_file (handle_t hnd, std::size_t size)
{  return 0 == ::ftruncate(hnd, size);   }

inline bool get_file_size(handle_t hnd, offset_t &size)
{  
   struct stat data;
   bool ret = 0 == ::fstat(hnd, &data);
   if(ret){
      size = data.st_size;
   }
   return ret;
}

inline bool set_file_pointer(handle_t hnd, offset_t off, file_pos_t pos)
{  return off == lseek(hnd, off, (int)pos); }

inline bool get_file_pointer(handle_t hnd, offset_t &off)
{  
   off = lseek(hnd, 0, SEEK_CUR);
   return off != ((off_t)-1);
}

inline bool write_file(handle_t hnd, const void *data, std::size_t numdata)
{  return (ssize_t(numdata)) == ::write(hnd, data, numdata);  }

inline handle_t invalid_file()
{  return -1;  }

inline bool close_file(handle_t hnd)
{  return ::close(hnd) == 0;   }

inline bool acquire_file_lock(handle_t hnd)
{
   struct ::flock lock;
   lock.l_type    = F_WRLCK;
   lock.l_whence  = SEEK_SET;
   lock.l_start   = 0;
   lock.l_len     = 0;
   return -1 != ::fcntl(hnd, F_SETLKW, &lock);
}

inline bool try_acquire_file_lock(handle_t hnd, bool &acquired)
{
   struct ::flock lock;
   lock.l_type    = F_WRLCK;
   lock.l_whence  = SEEK_SET;
   lock.l_start   = 0;
   lock.l_len     = 0;
   int ret = ::fcntl(hnd, F_SETLK, &lock);
   if(ret == -1){
      return (errno != EAGAIN && errno != EACCES) ?
               acquired = false, true : false;
   }
   return (acquired = true);
}

inline bool timed_acquire_file_lock
   (handle_t hnd, bool &acquired, const boost::posix_time::ptime &abs_time)
{
   //Obtain current count and target time
   boost::posix_time::ptime now = 
      boost::posix_time::microsec_clock::universal_time();
   using namespace boost::detail;

   if(now >= abs_time) return false;

   do{
      if(!try_acquire_file_lock(hnd, acquired))
         return false;

      if(acquired)
         return true;
      else{
         now = boost::posix_time::microsec_clock::universal_time();

         if(now >= abs_time){
            acquired = false;
            return true;
         }
         // relinquish current time slice
         sleep(0);
      }
   }while (true);
}

inline bool release_file_lock(handle_t hnd)
{
   struct ::flock lock;
   lock.l_type    = F_UNLCK;
   lock.l_whence  = SEEK_SET;
   lock.l_start   = 0;
   lock.l_len     = 0;
   return -1 != ::fcntl(hnd, F_SETLK, &lock);
}

inline bool acquire_file_lock_sharable(handle_t hnd)
{  
   struct ::flock lock;
   lock.l_type    = F_RDLCK;
   lock.l_whence  = SEEK_SET;
   lock.l_start   = 0;
   lock.l_len     = 0;
   return -1 != ::fcntl(hnd, F_SETLKW, &lock);
}

inline bool try_acquire_file_lock_sharable(handle_t hnd, bool &acquired)
{  
   struct flock lock;
   lock.l_type    = F_RDLCK;
   lock.l_whence  = SEEK_SET;
   lock.l_start   = 0;
   lock.l_len     = 0;
   int ret = ::fcntl(hnd, F_SETLK, &lock);
   if(ret == -1){
      return (errno != EAGAIN && errno != EACCES) ? 
               acquired = false, true : false;
   }
   return (acquired = true);
}

inline bool timed_acquire_file_lock_sharable
   (handle_t hnd, bool &acquired, const boost::posix_time::ptime &abs_time)
{  
   //Obtain current count and target time
   boost::posix_time::ptime now = 
      boost::posix_time::microsec_clock::universal_time();
   using namespace boost::detail;

   if(now >= abs_time) return false;

   do{
      if(!try_acquire_file_lock_sharable(hnd, acquired))
         return false;

      if(acquired)
         return true;
      else{
         now = boost::posix_time::microsec_clock::universal_time();

         if(now >= abs_time){
            acquired = false;
            return true;
         }
         // relinquish current time slice
         ::sleep(0);
      }
   }while (true);
}

inline bool release_file_lock_sharable(handle_t hnd)
{  return release_file_lock(hnd);   }

#endif   //#if (defined BOOST_WINDOWS) && !(defined BOOST_DISABLE_WIN32)

}  //namespace detail{
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_OS_FILE_FUNCTIONS_HPP

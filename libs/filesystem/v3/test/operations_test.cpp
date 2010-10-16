//  Boost operations_test.cpp  ---------------------------------------------------------//

//  Copyright Beman Dawes 2002, 2009.

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  Library home page: http://www.boost.org/libs/filesystem

#define BOOST_FILESYSTEM_VERSION 3

#include <boost/config.hpp>

# if defined( BOOST_NO_STD_WSTRING )
#   error Configuration not supported: Boost.Filesystem V3 and later requires std::wstring support
# endif

#include <boost/config/warning_disable.hpp>

//  See deprecated_test for tests of deprecated features
#ifndef BOOST_FILESYSTEM_NO_DEPRECATED 
#  define BOOST_FILESYSTEM_NO_DEPRECATED
#endif
#ifndef BOOST_SYSTEM_NO_DEPRECATED 
#  define BOOST_SYSTEM_NO_DEPRECATED
#endif

#include <boost/filesystem/operations.hpp>
#include <boost/cerrno.hpp>
namespace fs = boost::filesystem;

#include <boost/detail/lightweight_test.hpp>

using boost::system::error_code;
using boost::system::system_category;
using boost::system::system_error;

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring> // for strncmp, etc.
#include <ctime>
#include <cstdlib> // for system(), getenv(), etc.

#ifdef BOOST_WINDOWS_API
# include <windows.h>
#endif

//  on Windows, except for standard libaries known to have wchar_t overloads for
//  file stream I/O, use path::string() to get a narrow character c_str()
#if defined(BOOST_WINDOWS_API) \
  && !(defined(_CPPLIB_VER) && _CPPLIB_VER >= 405)  // not (Dinkumware with overloads)
# define BOOST_FILESYSTEM_C_STR string().c_str()  // use narrow, since wide not available
#else  // use the native c_str, which will be narrow on POSIX, wide on Windows
# define BOOST_FILESYSTEM_C_STR c_str()
#endif

#define CHECK_EXCEPTION(Functor,Expect) throws_fs_error(Functor,Expect,__LINE__)

namespace
{
  typedef int errno_t;
  std::string platform(BOOST_PLATFORM);
  bool report_throws;
  bool cleanup = true;
  fs::path init_path(fs::current_path());
  fs::directory_iterator end_itr;
  fs::path dir;
  fs::path d1;
  fs::path d2;
  fs::path f0;
  fs::path f1;
  fs::path d1f1;

  bool create_symlink_ok(true);
  fs::path ng(" no-way, Jose");

  unsigned short language_id;  // 0 except for Windows

  const char* temp_dir_name = "temp_fs_test_dir";

  void create_file(const fs::path & ph, const std::string & contents)
  {
    std::ofstream f(ph.BOOST_FILESYSTEM_C_STR);
    if (!f)
      throw fs::filesystem_error("operations_test create_file",
      ph, error_code(errno, system_category()));
    if (!contents.empty()) f << contents;
  }

  void verify_file(const fs::path & ph, const std::string & expected)
  {
    std::ifstream f(ph.BOOST_FILESYSTEM_C_STR);
    if (!f)
      throw fs::filesystem_error("operations_test verify_file",
        ph, error_code(errno, system_category()));
    std::string contents;
    f >> contents;
    if (contents != expected)
      throw fs::filesystem_error("operations_test verify_file contents \""
        + contents  + "\" != \"" + expected + "\"", ph, error_code());
  }

  template< typename F >
    bool throws_fs_error(F func, errno_t en, int line)
  {
    try { func(); }

    catch (const fs::filesystem_error & ex)
    {
      if (report_throws)
      {
        // use the what() convenience function to display exceptions
        std::cout << "\n" << ex.what() << "\n";
      }
      if (en == 0
        || en == ex.code().default_error_condition().value()) return true;
      std::cout
        << "\nWarning: line " << line
        << " exception reports default_error_condition().value() "
        << ex.code().default_error_condition().value()
        << ", should be " << en
        << "\n value() is " << ex.code().value()
        << std::endl;
      return true;
    }
    return false;
  }

  boost::system::error_category* poison_category_aux() { return 0; }
  boost::system::error_category& poison_category()     { return *poison_category_aux(); }

  // compile-only two argument "do-the-right-thing" tests
  //   verifies that all overload combinations compile without error
  void do_not_call()
  {
    fs::path p;
    std::string s;
    const char* a = 0;
    fs::copy_file(p, p);
    fs::copy_file(s, p);
    fs::copy_file(a, p);
    fs::copy_file(p, s);
    fs::copy_file(p, a);
    fs::copy_file(s, s);
    fs::copy_file(a, s);
    fs::copy_file(s, a);
    fs::copy_file(a, a);
  }

  void bad_file_size()
  {
    fs::file_size(" No way, Jose");
  }
  
  void bad_directory_size()
  {
    fs::file_size(fs::current_path());
  }
  
  fs::path bad_create_directory_path;
  void bad_create_directory()
  {
    fs::create_directory(bad_create_directory_path);
  }
  
  void bad_equivalent()
  {
    fs::equivalent("no-such-path", "another-not-present-path");
  }

  fs::path bad_remove_dir;
  void bad_remove()
  {
    fs::remove(bad_remove_dir);
  }

  class renamer
  {
  public:
    renamer(const fs::path & p1, const fs::path & p2)
      : from(p1), to(p2) {}
    void operator()()
    {
      fs::rename(from, to);
    }
  private:
    fs::path from;
    fs::path to;
  };

  //  exception_tests()  ---------------------------------------------------------------//

  void exception_tests()
  {
    std::cout << "exception_tests..." << std::endl;
    bool exception_thrown;

    //  catch runtime_error by value

    std::cout << "  catch runtime_error by value" << std::endl;
    exception_thrown = false;
    try
    {
      fs::create_directory("no-such-dir/foo/bar");
    }
    catch (std::runtime_error x)
    {
      exception_thrown = true;
      if (report_throws) std::cout << x.what() << std::endl;
      if (platform == "Windows" && language_id == 0x0409) // English (United States)
        // the stdcxx standard library apparently appends additional info
        // to what(), so check only the initial portion: 
        BOOST_TEST(std::strncmp(x.what(),
          "boost::filesystem::create_directory",
          sizeof("boost::filesystem::create_directory")-1) == 0);
    }
    BOOST_TEST(exception_thrown);

    //  catch system_error by value

    std::cout << "  catch system_error by value" << std::endl;
    exception_thrown = false;
    try
    {
      fs::create_directory("no-such-dir/foo/bar");
    }
    catch (system_error x)
    {
      exception_thrown = true;
      if (report_throws) std::cout << x.what() << std::endl;
      if (platform == "Windows" && language_id == 0x0409) // English (United States)
        BOOST_TEST(std::strcmp(x.what(),
          "boost::filesystem::create_directory: The system cannot find the path specified") == 0);
    }
    BOOST_TEST(exception_thrown);

    //  catch filesystem_error by value

    std::cout << "  catch filesystem_error by value" << std::endl;
    exception_thrown = false;
    try
    {
      fs::create_directory("no-such-dir/foo/bar");
    }
    catch (fs::filesystem_error x)
    {
      exception_thrown = true;
      if (report_throws) std::cout << x.what() << std::endl;
      if (platform == "Windows" && language_id == 0x0409) // English (United States)
      {
        bool ok (std::strcmp(x.what(),
          "boost::filesystem::create_directory: The system cannot find the path specified: \"no-such-dir/foo/bar\"") == 0);
        BOOST_TEST(ok);
        if (!ok)
        {
          std::cout << "what returns \"" << x.what() << "\"" << std::endl;
        }
      }
    }
    BOOST_TEST(exception_thrown);

    //  catch filesystem_error by const reference

    std::cout << "  catch filesystem_error by const reference" << std::endl;
    exception_thrown = false;
    try
    {
      fs::create_directory("no-such-dir/foo/bar");
    }
    catch (const fs::filesystem_error & x)
    {
      exception_thrown = true;
      if (report_throws) std::cout << x.what() << std::endl;
      if (platform == "Windows" && language_id == 0x0409) // English (United States)
      {
        bool ok (std::strcmp(x.what(),
          "boost::filesystem::create_directory: The system cannot find the path specified: \"no-such-dir/foo/bar\"") == 0);
        BOOST_TEST(ok);
        if (!ok)
        {
          std::cout << "what returns \"" << x.what() << "\"" << std::endl;
        }
      }
    }
    BOOST_TEST(exception_thrown);

    // the bound functions should throw, so CHECK_EXCEPTION() should return true

    BOOST_TEST(CHECK_EXCEPTION(bad_file_size, ENOENT));

    if (platform == "Windows")
      BOOST_TEST(CHECK_EXCEPTION(bad_directory_size, ENOENT));
    else
      BOOST_TEST(CHECK_EXCEPTION(bad_directory_size, 0));

    // test path::exception members
    try { fs::file_size(ng); } // will throw

    catch (const fs::filesystem_error & ex)
    {
      BOOST_TEST(ex.path1().string() == " no-way, Jose");
    }

    std::cout << "  exception_tests complete" << std::endl;
  }

  // create a directory tree that can be used by subsequent tests  ---------------------//
  //
  //    dir
  //      d1
  //        d1f1       // an empty file
  //      f0           // an empty file
  //      f1           // a file containing "file-f1"
 
  void create_tree()
  {

  // create directory d1
  BOOST_TEST(!fs::create_directory(dir));
  BOOST_TEST(!fs::is_symlink(dir));
  BOOST_TEST(!fs::is_symlink("nosuchfileordirectory"));
  d1 = dir / "d1";
  BOOST_TEST(fs::create_directory(d1));
  BOOST_TEST(fs::exists(d1));
  BOOST_TEST(fs::is_directory(d1));
  BOOST_TEST(fs::is_empty(d1));

  // create an empty file named "d1f1"
  d1f1 = d1 / "d1f1";
  create_file(d1f1, "");
  BOOST_TEST(fs::exists(d1f1));
  BOOST_TEST(!fs::is_directory(d1f1));
  BOOST_TEST(fs::is_regular_file(d1f1));
  BOOST_TEST(fs::is_empty(d1f1));
  BOOST_TEST(fs::file_size(d1f1) == 0);
  BOOST_TEST(fs::hard_link_count(d1f1) == 1);

  // create an empty file named "f0"
  f0 = dir / "f0";
  create_file(f0, "");
  BOOST_TEST(fs::exists(f0));
  BOOST_TEST(!fs::is_directory(f0));
  BOOST_TEST(fs::is_regular_file(f0));
  BOOST_TEST(fs::is_empty(f0));
  BOOST_TEST(fs::file_size(f0) == 0);
  BOOST_TEST(fs::hard_link_count(f0) == 1);

  // create a file named "f1"
  f1 = dir / "f1";
  create_file(f1, "file-f1");
  BOOST_TEST(fs::exists(f1));
  BOOST_TEST(!fs::is_directory(f1));
  BOOST_TEST(fs::is_regular_file(f1));
  BOOST_TEST(fs::file_size(f1) == 7);
  verify_file(f1, "file-f1");
  }

  //  directory_iterator_tests  --------------------------------------------------------//

  void directory_iterator_tests()
  {
    std::cout << "directory_iterator_tests..." << std::endl;

    bool dir_itr_exception(false);
    try { fs::directory_iterator it(""); }
    catch (const fs::filesystem_error &) { dir_itr_exception = true; }
    BOOST_TEST(dir_itr_exception);

    error_code ec;

    BOOST_TEST(!ec);
    fs::directory_iterator it("", ec);
    BOOST_TEST(ec);

    dir_itr_exception = false;
    try { fs::directory_iterator it("nosuchdirectory"); }
    catch (const fs::filesystem_error &) { dir_itr_exception = true; }
    BOOST_TEST(dir_itr_exception);

    ec.clear();
    fs::directory_iterator it2("nosuchdirectory", ec);
    BOOST_TEST(ec);

    dir_itr_exception = false;
    try
    {
      error_code ec;
      fs::directory_iterator it("nosuchdirectory", ec);
      BOOST_TEST(ec);
      BOOST_TEST(ec == boost::system::errc::no_such_file_or_directory);
    }
    catch (const fs::filesystem_error &) { dir_itr_exception = true; }
    BOOST_TEST(!dir_itr_exception);
    
    {
      // probe query function overloads
      fs::directory_iterator dir_itr(dir);
  //    BOOST_TEST(fs::is_directory(*dir_itr));
      BOOST_TEST(fs::is_directory(dir_itr->status())
        || fs::is_regular_file(dir_itr->status()));
  //    BOOST_TEST(fs::is_directory(fs::symlink_status(*dir_itr)));
      BOOST_TEST(fs::is_directory(dir_itr->symlink_status())
        || fs::is_regular_file(dir_itr->symlink_status()));
      BOOST_TEST(dir_itr->path().filename() == "d1"
        || dir_itr->path().filename() == "d2" || dir_itr->path().filename() == "f0"
        || dir_itr->path().filename() == "f1");
    }
  
    // create a second directory named d2
    d2 = dir / "d2";
    fs::create_directory(d2);
    BOOST_TEST(fs::exists(d2));
    BOOST_TEST(fs::is_directory(d2));

    // test the basic operation of directory_iterators, and test that
    // stepping one iterator doesn't affect a different iterator.
    {
      typedef std::vector<fs::directory_entry> vec_type;
      vec_type vec;

      fs::directory_iterator it1(dir);
      BOOST_TEST(it1 != fs::directory_iterator());
      BOOST_TEST(fs::exists(it1->status()));
      vec.push_back(*it1);
      BOOST_TEST(*it1 == vec[0]);

      fs::directory_iterator it2(dir);
      BOOST_TEST(it2 != fs::directory_iterator());
      BOOST_TEST(*it1 == *it2);

      ++it1;
      BOOST_TEST(it1 != fs::directory_iterator());
      BOOST_TEST(fs::exists(it1->status()));
      BOOST_TEST(it1 != it2);
      BOOST_TEST(*it1 != vec[0]);
      BOOST_TEST(*it2 == vec[0]);
      vec.push_back(*it1);

      ++it1;
      BOOST_TEST(it1 != fs::directory_iterator());
      BOOST_TEST(fs::exists(it1->status()));
      BOOST_TEST(it1 != it2);
      BOOST_TEST(*it2 == vec[0]);
      vec.push_back(*it1);

      ++it1;
      BOOST_TEST(it1 != fs::directory_iterator());
      BOOST_TEST(fs::exists(it1->status()));
      BOOST_TEST(it1 != it2);
      BOOST_TEST(*it2 == vec[0]);
      vec.push_back(*it1);

      ++it1;
      BOOST_TEST(it1 == fs::directory_iterator());

      BOOST_TEST(*it2 == vec[0]);
      ec.clear();
      it2.increment(ec);
      BOOST_TEST(!ec);
      BOOST_TEST(it2 != fs::directory_iterator());
      BOOST_TEST(it1 == fs::directory_iterator());
      BOOST_TEST(*it2 == vec[1]);
      ++it2;
      BOOST_TEST(*it2 == vec[2]);
      BOOST_TEST(it1 == fs::directory_iterator());
      ++it2;
      BOOST_TEST(*it2 == vec[3]);
      ++it2;
      BOOST_TEST(it1 == fs::directory_iterator());
      BOOST_TEST(it2 == fs::directory_iterator());

      // sort vec and check that the right directory entries were found
      std::sort(vec.begin(), vec.end());

      BOOST_TEST_EQ(vec[0].path().filename().string(), std::string("d1"));
      BOOST_TEST_EQ(vec[1].path().filename().string(), std::string("d2"));
      BOOST_TEST_EQ(vec[2].path().filename().string(), std::string("f0"));
      BOOST_TEST_EQ(vec[3].path().filename().string(), std::string("f1"));
    }

    { // *i++ must meet the standard's InputIterator requirements
      fs::directory_iterator dir_itr(dir);
      BOOST_TEST(dir_itr != fs::directory_iterator());
      fs::path p = dir_itr->path();
      BOOST_TEST((*dir_itr++).path() == p);
      BOOST_TEST(dir_itr != fs::directory_iterator());
      BOOST_TEST(dir_itr->path() != p);

      // test case reported in comment to SourceForge bug tracker [937606]
      fs::directory_iterator it(dir);
      const fs::path p1 = (*it++).path();
      BOOST_TEST(it != fs::directory_iterator());
      const fs::path p2 = (*it++).path();
      BOOST_TEST(p1 != p2);
      ++it;
      ++it;
      BOOST_TEST(it == fs::directory_iterator());
    }

    //  Windows has a tricky special case when just the root-name is given,
    //  causing the rest of the path to default to the current directory.
    //  Reported as S/F bug [ 1259176 ]
    if (platform == "Windows")
    {
      fs::path root_name_path(fs::current_path().root_name());
      fs::directory_iterator it(root_name_path);
      BOOST_TEST(it != fs::directory_iterator());
//      BOOST_TEST(fs::exists((*it).path()));
      BOOST_TEST(fs::exists(it->path()));
      BOOST_TEST(it->path().parent_path() == root_name_path);
      bool found(false);
      do
      {
        if (it->path().filename() == temp_dir_name) found = true;
      } while (++it != fs::directory_iterator());
      BOOST_TEST(found);
    }

    // there was an inital bug in directory_iterator that caused premature
    // close of an OS handle. This block will detect regression.
    {
      fs::directory_iterator di;
      { 
        di = fs::directory_iterator(dir);
      }
      BOOST_TEST(++di != fs::directory_iterator());
    }

    std::cout << "  directory_iterator_tests complete" << std::endl;
  }
  
  //  create_hard_link_tests  ----------------------------------------------------------//

  void create_hard_link_tests()
  {
    std::cout << "create_hard_link_tests..." << std::endl;

    fs::path from_ph(dir / "f3");
    fs::path f1(dir / "f1");

    BOOST_TEST(!fs::exists(from_ph));
    BOOST_TEST(fs::exists(f1));
    bool create_hard_link_ok(true);
    try { fs::create_hard_link(f1, from_ph); }
    catch (const fs::filesystem_error & ex)
    {
      create_hard_link_ok = false;
      std::cout
        << "     *** For information only ***\n"
           "     create_hard_link() attempt failed\n"
           "     filesystem_error.what() reports: " << ex.what() << "\n"
           "     create_hard_link() may not be supported on this file system\n";
    }

    if (create_hard_link_ok)
    {
      std::cout
        << "     *** For information only ***\n"
           "     create_hard_link() succeeded\n";
      BOOST_TEST(fs::exists(from_ph));
      BOOST_TEST(fs::exists(f1));
      BOOST_TEST(fs::equivalent(from_ph, f1));
      BOOST_TEST(fs::hard_link_count(from_ph) == 2);
      BOOST_TEST(fs::hard_link_count(f1) == 2);
    }

    //  Although tests may be running on a FAT or other file system that does
    //  not support hard links, that is unusual enough that it is considered
    //  a test failure.
    BOOST_TEST(create_hard_link_ok);

    error_code ec;
    fs::create_hard_link(fs::path("doesnotexist"),
      fs::path("shouldnotwork"), ec);
    BOOST_TEST(ec);
  }
  
  //  create_symlink_tests  ------------------------------------------------------------//

  void create_symlink_tests()
  {
    std::cout << "create_symlink_tests..." << std::endl;

    fs::path from_ph(dir / "f4");
    fs::path f1(dir / "f1");
    BOOST_TEST(!fs::exists(from_ph));
    BOOST_TEST(fs::exists(f1));
    try { fs::create_symlink(f1, from_ph); }
    catch (const fs::filesystem_error & ex)
    {
      create_symlink_ok = false;
      std::cout                             
        << "     *** For information only ***\n"
           "     create_symlink() attempt failed\n"
           "     filesystem_error.what() reports: " << ex.what() << "\n"
           "     create_symlink() may not be supported on this operating system or file system\n";
    }

    if (create_symlink_ok)
    {
      std::cout
        << "     *** For information only ***\n"
           "     create_symlink() succeeded\n";
      BOOST_TEST(fs::exists(from_ph));
      BOOST_TEST(fs::is_symlink(from_ph));
      BOOST_TEST(fs::exists(f1));
      BOOST_TEST(fs::equivalent(from_ph, f1));
		  BOOST_TEST(fs::read_symlink(from_ph) == f1);

      fs::file_status stat = fs::symlink_status(from_ph);
      BOOST_TEST(fs::exists(stat));
      BOOST_TEST(!fs::is_directory(stat));
      BOOST_TEST(!fs::is_regular_file(stat));
      BOOST_TEST(!fs::is_other(stat));
      BOOST_TEST(fs::is_symlink(stat));

      stat = fs::status(from_ph);
      BOOST_TEST(fs::exists(stat));
      BOOST_TEST(!fs::is_directory(stat));
      BOOST_TEST(fs::is_regular_file(stat));
      BOOST_TEST(!fs::is_other(stat));
      BOOST_TEST(!fs::is_symlink(stat));
       
	  // since create_symlink worked, copy_symlink should also work
      fs::path symlink2_ph(dir / "symlink2");
	    fs::copy_symlink(from_ph, symlink2_ph);
      stat = fs::symlink_status(symlink2_ph);
      BOOST_TEST(fs::is_symlink(stat));
      BOOST_TEST(fs::exists(stat));
      BOOST_TEST(!fs::is_directory(stat));
      BOOST_TEST(!fs::is_regular_file(stat));
      BOOST_TEST(!fs::is_other(stat));
    }

    error_code ec = error_code();
    fs::create_symlink("doesnotexist", "", ec);
    BOOST_TEST(ec);
  }
  
  //  rename_tests  --------------------------------------------------------------------//

  void rename_tests()
  {
    std::cout << "rename_tests..." << std::endl;

    fs::path f1(dir / "f1");
    BOOST_TEST(fs::exists(f1));

    // error: rename a non-existent old file
    BOOST_TEST(!fs::exists(d1 / "f99"));
    BOOST_TEST(!fs::exists(d1 / "f98"));
    renamer n1a(d1 / "f99", d1 / "f98");
    BOOST_TEST(CHECK_EXCEPTION(n1a, ENOENT));
    renamer n1b(fs::path(""), d1 / "f98");
    BOOST_TEST(CHECK_EXCEPTION(n1b, ENOENT));

    // error: rename an existing file to ""
    renamer n2(f1, "");
    BOOST_TEST(CHECK_EXCEPTION(n2, ENOENT));

    // rename an existing file to an existent file
    create_file(dir / "ff1", "ff1");
    create_file(dir / "ff2", "ff2");
    fs::rename(dir / "ff2", dir / "ff1");
    BOOST_TEST(fs::exists(dir / "ff1"));
    verify_file(dir / "ff1", "ff2");
    BOOST_TEST(!fs::exists(dir / "ff2"));

    // rename an existing file to itself
    BOOST_TEST(fs::exists(dir / "f1"));
    fs::rename(dir / "f1", dir / "f1");
    BOOST_TEST(fs::exists(dir / "f1"));

    // error: rename an existing directory to an existing non-empty directory
    BOOST_TEST(fs::exists(dir / "f1"));
    BOOST_TEST(fs::exists(d1 / "f2"));
    // several POSIX implementations (cygwin, openBSD) report ENOENT instead of EEXIST,
    // so we don't verify error type on the following test.
    renamer n3b(dir, d1);
    BOOST_TEST(CHECK_EXCEPTION(n3b, 0));

    //  error: move existing file to a nonexistent parent directory
    BOOST_TEST(!fs::is_directory(dir / "f1"));
    BOOST_TEST(!fs::exists(dir / "d3/f3"));
    renamer n4a(dir / "f1", dir / "d3/f3");
    BOOST_TEST(CHECK_EXCEPTION(n4a, ENOENT));

    // rename existing file in same directory
    BOOST_TEST(fs::exists(d1 / "f2"));
    BOOST_TEST(!fs::exists(d1 / "f50"));
    fs::rename(d1 / "f2", d1 / "f50");
    BOOST_TEST(!fs::exists(d1 / "f2"));
    BOOST_TEST(fs::exists(d1 / "f50"));
    fs::rename(d1 / "f50", d1 / "f2");
    BOOST_TEST(fs::exists(d1 / "f2"));
    BOOST_TEST(!fs::exists(d1 / "f50"));

    // move and rename an existing file to a different directory
    fs::rename(d1 / "f2", d2 / "f3");
    BOOST_TEST(!fs::exists(d1 / "f2"));
    BOOST_TEST(!fs::exists(d2 / "f2"));
    BOOST_TEST(fs::exists(d2 / "f3"));
    BOOST_TEST(!fs::is_directory(d2 / "f3"));
    verify_file(d2 / "f3", "file-f1");
    fs::rename(d2 / "f3", d1 / "f2");
    BOOST_TEST(fs::exists(d1 / "f2"));

    // error: move existing directory to nonexistent parent directory
    BOOST_TEST(fs::exists(d1));
    BOOST_TEST(!fs::exists(dir / "d3/d5"));
    BOOST_TEST(!fs::exists(dir / "d3"));
    renamer n5a(d1, dir / "d3/d5");
    BOOST_TEST(CHECK_EXCEPTION(n5a, ENOENT));

    // rename existing directory
    fs::path d3(dir / "d3");
    BOOST_TEST(fs::exists(d1));
    BOOST_TEST(fs::exists(d1 / "f2"));
    BOOST_TEST(!fs::exists(d3));
    fs::rename(d1, d3);
    BOOST_TEST(!fs::exists(d1));
    BOOST_TEST(fs::exists(d3));
    BOOST_TEST(fs::is_directory(d3));
    BOOST_TEST(!fs::exists(d1 / "f2"));
    BOOST_TEST(fs::exists(d3 / "f2"));
    fs::rename(d3, d1);
    BOOST_TEST(fs::exists(d1));
    BOOST_TEST(fs::exists(d1 / "f2"));
    BOOST_TEST(!fs::exists(d3));

    // rename and move d1 to d2 / "d20"
    BOOST_TEST(fs::exists(d1));
    BOOST_TEST(!fs::exists(d2 / "d20"));
    BOOST_TEST(fs::exists(d1 / "f2"));
    fs::rename(d1, d2 / "d20");
    BOOST_TEST(!fs::exists(d1));
    BOOST_TEST(fs::exists(d2 / "d20"));
    BOOST_TEST(fs::exists(d2 / "d20" / "f2"));
    fs::rename(d2 / "d20", d1);
    BOOST_TEST(fs::exists(d1));
    BOOST_TEST(!fs::exists(d2 / "d20"));
    BOOST_TEST(fs::exists(d1 / "f2"));
  }
  
  //  predicate_and_status_tests  ------------------------------------------------------//

  void predicate_and_status_tests()
  {
    std::cout << "predicate_and_status_tests..." << std::endl;

    BOOST_TEST(!fs::exists(ng));
    BOOST_TEST(!fs::is_directory(ng));
    BOOST_TEST(!fs::is_regular_file(ng));
    BOOST_TEST(!fs::is_symlink(ng));
    fs::file_status stat(fs::status(ng));
    BOOST_TEST(fs::status_known(stat));
    BOOST_TEST(!fs::exists(stat));
    BOOST_TEST(!fs::is_directory(stat));
    BOOST_TEST(!fs::is_regular_file(stat));
    BOOST_TEST(!fs::is_other(stat));
    BOOST_TEST(!fs::is_symlink(stat));
    stat = fs::status("");
    BOOST_TEST(fs::status_known(stat));
    BOOST_TEST(!fs::exists(stat));
    BOOST_TEST(!fs::is_directory(stat));
    BOOST_TEST(!fs::is_regular_file(stat));
    BOOST_TEST(!fs::is_other(stat));
    BOOST_TEST(!fs::is_symlink(stat));
  }
  
  //  create_directory_tests  ----------------------------------------------------------//

  void create_directory_tests()
  {
    std::cout << "create_directory_tests..." << std::endl;

    // create a directory, then check it for consistency
    //   take extra care to report problems, since if this fails
    //   many subsequent tests will fail
    try
    {
      fs::create_directory(dir);
    }

    catch (const fs::filesystem_error & x)
    {
      std::cout << x.what() << "\n\n"
         "***** Creating directory " << dir << " failed.   *****\n"
         "***** This is a serious error that will prevent further tests    *****\n"
         "***** from returning useful results. Further testing is aborted. *****\n\n";
      std::exit(1);
    }

    catch (...)
    {
      std::cout << "\n\n"
         "***** Creating directory " << dir << " failed.   *****\n"
         "***** This is a serious error that will prevent further tests    *****\n"
         "***** from returning useful results. Further testing is aborted. *****\n\n";
      std::exit(1);
    }

    BOOST_TEST(fs::exists(dir));
    BOOST_TEST(fs::is_empty(dir));
    BOOST_TEST(fs::is_directory(dir));
    BOOST_TEST(!fs::is_regular_file(dir));
    BOOST_TEST(!fs::is_other(dir));
    BOOST_TEST(!fs::is_symlink(dir));
    fs::file_status stat = fs::status(dir);
    BOOST_TEST(fs::exists(stat));
    BOOST_TEST(fs::is_directory(stat));
    BOOST_TEST(!fs::is_regular_file(stat));
    BOOST_TEST(!fs::is_other(stat));
    BOOST_TEST(!fs::is_symlink(stat));

    std::cout << "  create_directory_tests complete" << std::endl;
  }
  
  //  current_directory_tests  ---------------------------------------------------------//

  void current_directory_tests()
  {
    std::cout << "current_directory_tests..." << std::endl;

    // set the current directory, then check it for consistency
    fs::path original_dir = fs::current_path();
    BOOST_TEST(dir != original_dir);
    fs::current_path(dir);
    BOOST_TEST(fs::current_path() == dir);
    BOOST_TEST(fs::current_path() != original_dir);
    fs::current_path(original_dir);
    BOOST_TEST(fs::current_path() == original_dir);
    BOOST_TEST(fs::current_path() != dir);

    // make sure the overloads work
    fs::current_path(dir.c_str());
    BOOST_TEST(fs::current_path() == dir);
    BOOST_TEST(fs::current_path() != original_dir);
    fs::current_path(original_dir.string());
    BOOST_TEST(fs::current_path() == original_dir);
    BOOST_TEST(fs::current_path() != dir);
  }

  //  create_directories_tests  --------------------------------------------------------//

  void create_directories_tests()
  {
    std::cout << "create_directories_tests..." << std::endl;

    fs::path p = dir / "level1" / "level2";

    BOOST_TEST(!fs::exists(p));
    BOOST_TEST(fs::create_directories(p));
    BOOST_TEST(fs::exists(p));
    BOOST_TEST(fs::is_directory(p));
  }

  //  resize_file_tests  ---------------------------------------------------------------//

  void resize_file_tests()
  {
    std::cout << "resize_file_tests..." << std::endl;

    fs::path p(dir / "resize_file_test.txt");

    fs::remove(p);
    create_file(p, "1234567890");

    BOOST_TEST(fs::exists(p));
    BOOST_TEST_EQ(fs::file_size(p), 10U);
    fs::resize_file(p, 5);
    BOOST_TEST(fs::exists(p));
    BOOST_TEST_EQ(fs::file_size(p), 5U);
    fs::resize_file(p, 15);
    BOOST_TEST(fs::exists(p));
    BOOST_TEST_EQ(fs::file_size(p), 15U);

    error_code ec;
    fs::resize_file("no such file", 15, ec);
    BOOST_TEST(ec);
  }

  //  status_of_nonexistent_tests  -----------------------------------------------------//

  void status_of_nonexistent_tests()
  {
    std::cout << "status_of_nonexistent_tests..." << std::endl;
    fs::path p ("nosuch");
    BOOST_TEST(!fs::exists(p));
    BOOST_TEST(!fs::is_regular_file(p));
    BOOST_TEST(!fs::is_directory(p));
    BOOST_TEST(!fs::is_symlink(p));
    BOOST_TEST(!fs::is_other(p));

    fs::file_status s = fs::status(p);
    BOOST_TEST(!fs::exists(s));
    BOOST_TEST_EQ(s.type(), fs::file_not_found);
    BOOST_TEST(fs::status_known(s));
    BOOST_TEST(!fs::is_regular_file(s));
    BOOST_TEST(!fs::is_directory(s));
    BOOST_TEST(!fs::is_symlink(s));
    BOOST_TEST(!fs::is_other(s));
  }

  //  status_error_reporting_tests  ----------------------------------------------------//

  void status_error_reporting_tests()
  {
    std::cout << "status_error_reporting_tests..." << std::endl;

    error_code ec;

    // test status, ec, for existing file
    ec.assign(-1,poison_category());
    BOOST_TEST(ec.value() == -1);
    BOOST_TEST(&ec.category() == &poison_category()); 
    fs::file_status s = fs::status(".",ec);
    BOOST_TEST(ec.value() == 0);
    BOOST_TEST(ec.category() == system_category()); 
    BOOST_TEST(fs::exists(s));
    BOOST_TEST(fs::is_directory(s));

    // test status, ec, for non-existing file
    fs::path p ("nosuch");
    ec.assign(-1,poison_category());
    s = fs::status(p,ec);
    BOOST_TEST(ec.value() != 0);
    BOOST_TEST(ec.category() == system_category()); 

    BOOST_TEST(!fs::exists(s));
    BOOST_TEST_EQ(s.type(), fs::file_not_found);
    BOOST_TEST(fs::status_known(s));
    BOOST_TEST(!fs::is_regular_file(s));
    BOOST_TEST(!fs::is_directory(s));
    BOOST_TEST(!fs::is_symlink(s));
    BOOST_TEST(!fs::is_other(s));

    // test queries, ec, for existing file
    ec.assign(-1,poison_category());
    BOOST_TEST(fs::exists(".", ec));
    BOOST_TEST(ec.value() == 0);
    BOOST_TEST(ec.category() == system_category()); 
    ec.assign(-1,poison_category());
    BOOST_TEST(!fs::is_regular_file(".", ec));
    BOOST_TEST(ec.value() == 0);
    BOOST_TEST(ec.category() == system_category()); 
    ec.assign(-1,poison_category());
    BOOST_TEST(fs::is_directory(".", ec));
    BOOST_TEST(ec.value() == 0);
    BOOST_TEST(ec.category() == system_category()); 

    // test queries, ec, for non-existing file
    ec.assign(-1,poison_category());
    BOOST_TEST(!fs::exists(p, ec));
    BOOST_TEST(ec.value() != 0);
    BOOST_TEST(ec.category() == system_category()); 
    ec.assign(-1,poison_category());
    BOOST_TEST(!fs::is_regular_file(p, ec));
    BOOST_TEST(ec.value() != 0);
    BOOST_TEST(ec.category() == system_category()); 
    ec.assign(-1,poison_category());
    BOOST_TEST(!fs::is_directory(p, ec));
    BOOST_TEST(ec.value() != 0);
    BOOST_TEST(ec.category() == system_category()); 
  }

  //  remove_tests  --------------------------------------------------------------------//

  void remove_tests(const fs::path& dir)
  {
    std::cout << "remove_tests..." << std::endl;

    // remove() file
    fs::path f1 = dir / "shortlife";
    BOOST_TEST(!fs::exists(f1));
    create_file(f1, "");
    BOOST_TEST(fs::exists(f1));
    BOOST_TEST(!fs::is_directory(f1));
    BOOST_TEST(fs::remove(f1));
    BOOST_TEST(!fs::exists(f1));
    BOOST_TEST(!fs::remove("no-such-file"));
    BOOST_TEST(!fs::remove("no-such-directory/no-such-file"));

    // remove() directory
    fs::path d1 = dir / "shortlife_dir";
    BOOST_TEST(!fs::exists(d1));
    fs::create_directory(d1);
    BOOST_TEST(fs::exists(d1));
    BOOST_TEST(fs::is_directory(d1));
    BOOST_TEST(fs::is_empty(d1));
    bad_remove_dir = dir;
    BOOST_TEST(CHECK_EXCEPTION(bad_remove, ENOTEMPTY));
    BOOST_TEST(fs::remove(d1));
    BOOST_TEST(!fs::exists(d1));
  }

  //  remove_symlink_tests  ------------------------------------------------------------//
      
  void remove_symlink_tests()
  {
    std::cout << "remove_symlink_tests..." << std::endl;

    // remove() dangling symbolic link
    fs::path link("dangling_link");
    fs::remove(link);  // remove any residue from past tests
    BOOST_TEST(!fs::is_symlink(link));
    BOOST_TEST(!fs::exists(link));
    fs::create_symlink("nowhere", link);
    BOOST_TEST(!fs::exists(link));
    BOOST_TEST(fs::is_symlink(link));
    BOOST_TEST(fs::remove(link));
    BOOST_TEST(!fs::is_symlink(link));

    // remove() self-refering symbolic link
    link = "link_to_self";
    fs::remove(link);  // remove any residue from past tests
    BOOST_TEST(!fs::is_symlink(link));
    BOOST_TEST(!fs::exists(link));
    fs::create_symlink(link, link);
    BOOST_TEST(fs::remove(link));
    BOOST_TEST(!fs::exists(link));
    BOOST_TEST(!fs::is_symlink(link));

    // remove() cyclic symbolic link
    link = "link_to_a";
    fs::path link2("link_to_b");
    fs::remove(link);   // remove any residue from past tests
    fs::remove(link2);  // remove any residue from past tests
    BOOST_TEST(!fs::is_symlink(link));
    BOOST_TEST(!fs::exists(link));
    fs::create_symlink(link, link2);
    fs::create_symlink(link2, link);
    BOOST_TEST(fs::remove(link));
    BOOST_TEST(fs::remove(link2));
    BOOST_TEST(!fs::exists(link));
    BOOST_TEST(!fs::exists(link2));
    BOOST_TEST(!fs::is_symlink(link));

    // remove() symbolic link to file
    fs::path f1 = "link_target";
    fs::remove(f1);  // remove any residue from past tests
    BOOST_TEST(!fs::exists(f1));
    create_file(f1, "");
    BOOST_TEST(fs::exists(f1));
    BOOST_TEST(!fs::is_directory(f1));
    BOOST_TEST(fs::is_regular_file(f1));
    link = "non_dangling_link";
    fs::create_symlink(f1, link);
    BOOST_TEST(fs::exists(link));
    BOOST_TEST(!fs::is_directory(link));
    BOOST_TEST(fs::is_regular_file(link));
    BOOST_TEST(fs::is_symlink(link));
    BOOST_TEST(fs::remove(link));
    BOOST_TEST(fs::exists(f1));
    BOOST_TEST(!fs::exists(link));
    BOOST_TEST(!fs::is_symlink(link));
    BOOST_TEST(fs::remove(f1));
    BOOST_TEST(!fs::exists(f1));
  }

  //  absolute_tests  -----------------------------------------------------------------//

  void absolute_tests()
  {
    std::cout << "absolute_tests..." << std::endl;

    BOOST_TEST_EQ(fs::absolute(""), fs::current_path() );
    BOOST_TEST_EQ(fs::absolute(fs::current_path() / "foo/bar"), fs::current_path() / "foo/bar");
    BOOST_TEST_EQ(fs::absolute("foo"), fs::current_path() / "foo");
    BOOST_TEST_EQ(fs::absolute("foo", fs::current_path()), fs::current_path() / "foo");
    BOOST_TEST_EQ(fs::absolute("bar", "foo"), fs::current_path() / "foo" / "bar");
    BOOST_TEST_EQ(fs::absolute("/foo"), fs::current_path().root_name().string() + "/foo");

#  ifdef BOOST_WINDOWS_API
    BOOST_TEST_EQ(fs::absolute("a:foo", "b:/bar"), "a:/bar/foo");
#  endif

    // these tests were moved from elsewhere, so may duplicate some of the above tests

    // p.empty()
      BOOST_TEST_EQ(fs::absolute(fs::path(), "//foo/bar"), "//foo/bar");
      if (platform == "Windows")
      {
        BOOST_TEST_EQ(fs::absolute(fs::path(), "a:/bar"), "a:/bar");
      }

    // p.has_root_name()
      //   p.has_root_directory()
        BOOST_TEST_EQ(fs::absolute(fs::path("//foo/bar"), "//uvw/xyz"), "//foo/bar");
        if (platform == "Windows")
        {
          BOOST_TEST_EQ(fs::absolute(fs::path("a:/bar"), "b:/xyz"), "a:/bar");
        }
      //   !p.has_root_directory()
        BOOST_TEST_EQ(fs::absolute(fs::path("//net"), "//xyz/"), "//net/");
        BOOST_TEST_EQ(fs::absolute(fs::path("//net"), "//xyz/abc"), "//net/abc");
        BOOST_TEST_EQ(fs::absolute(fs::path("//net"), "//xyz/abc/def"), "//net/abc/def");
        if (platform == "Windows")
        {
          BOOST_TEST_EQ(fs::absolute(fs::path("a:"), "b:/"), "a:/");
          BOOST_TEST_EQ(fs::absolute(fs::path("a:"),"b:/abc"), "a:/abc");
          BOOST_TEST_EQ(fs::absolute(fs::path("a:"),"b:/abc/def"), "a:/abc/def");
          BOOST_TEST_EQ(fs::absolute(fs::path("a:foo"), "b:/"), "a:/foo");
          BOOST_TEST_EQ(fs::absolute(fs::path("a:foo"), "b:/abc"), "a:/abc/foo");
          BOOST_TEST_EQ(fs::absolute(fs::path("a:foo"), "b:/abc/def"), "a:/abc/def/foo");
          BOOST_TEST_EQ(fs::absolute(fs::path("a:foo/bar"), "b:/"), "a:/foo/bar");
          BOOST_TEST_EQ(fs::absolute(fs::path("a:foo/bar"), "b:/abc"), "a:/abc/foo/bar");
          BOOST_TEST_EQ(fs::absolute(fs::path("a:foo/bar"), "b:/abc/def"), "a:/abc/def/foo/bar");
        }
    // !p.has_root_name()
      //   p.has_root_directory()
        BOOST_TEST_EQ(fs::absolute(fs::path("/"), "//xyz/"), "//xyz/");
        BOOST_TEST_EQ(fs::absolute(fs::path("/"), "//xyz/abc"), "//xyz/");
        BOOST_TEST_EQ(fs::absolute(fs::path("/foo"), "//xyz/"), "//xyz/foo");
        BOOST_TEST_EQ(fs::absolute(fs::path("/foo"), "//xyz/abc"), "//xyz/foo");
      //   !p.has_root_directory()
        BOOST_TEST_EQ(fs::absolute(fs::path("foo"), "//xyz/abc"), "//xyz/abc/foo");
        BOOST_TEST_EQ(fs::absolute(fs::path("foo/bar"), "//xyz/abc"), "//xyz/abc/foo/bar");
        BOOST_TEST_EQ(fs::absolute(fs::path("."), "//xyz/abc"), "//xyz/abc/.");
        BOOST_TEST_EQ(fs::absolute(fs::path(".."), "//xyz/abc"), "//xyz/abc/..");
        BOOST_TEST_EQ(fs::absolute(fs::path("./foo"), "//xyz/abc"), "//xyz/abc/./foo");
        BOOST_TEST_EQ(fs::absolute(fs::path("../foo"), "//xyz/abc"), "//xyz/abc/../foo");
        if (platform == "POSIX")
        {
          BOOST_TEST_EQ(fs::absolute(fs::path("foo"), "/abc"), "/abc/foo");
          BOOST_TEST_EQ(fs::absolute(fs::path("foo/bar"), "/abc"), "/abc/foo/bar");
          BOOST_TEST_EQ(fs::absolute(fs::path("."), "/abc"), "/abc/.");
          BOOST_TEST_EQ(fs::absolute(fs::path(".."), "/abc"), "/abc/..");
          BOOST_TEST_EQ(fs::absolute(fs::path("./foo"), "/abc"), "/abc/./foo");
          BOOST_TEST_EQ(fs::absolute(fs::path("../foo"), "/abc"), "/abc/../foo");
        }

  }

 //  copy_file_tests  -----------------------------------------------------------------//

  void copy_file_tests(const fs::path& f1, const fs::path& d1)
  {
    std::cout << "copy_file_tests..." << std::endl;

    BOOST_TEST(fs::exists(f1));
    fs::remove(d1 / "f2");  // remove possible residue from prior testing
    BOOST_TEST(fs::exists(d1));
    BOOST_TEST(!fs::exists(d1 / "f2"));
    std::cout << " copy " << f1 << " to " << d1 / "f2" << std::endl;
    fs::copy_file(f1, d1 / "f2");
    std::cout << " copy complete" << std::endl;
    BOOST_TEST(fs::exists(f1));
    BOOST_TEST(fs::exists(d1 / "f2"));
    BOOST_TEST(!fs::is_directory(d1 / "f2"));
    verify_file(d1 / "f2", "file-f1");

    bool copy_ex_ok = false;
    try { fs::copy_file(f1, d1 / "f2"); }
    catch (const fs::filesystem_error &) { copy_ex_ok = true; }
    BOOST_TEST(copy_ex_ok);

    copy_ex_ok = false;
    try { fs::copy_file(f1, d1 / "f2", fs::copy_option::fail_if_exists); }
    catch (const fs::filesystem_error &) { copy_ex_ok = true; }
    BOOST_TEST(copy_ex_ok);

    copy_ex_ok = true;
    try { fs::copy_file(f1, d1 / "f2", fs::copy_option::overwrite_if_exists); }
    catch (const fs::filesystem_error &) { copy_ex_ok = false; }
    BOOST_TEST(copy_ex_ok);
  }

 //  symlink_status_tests  -------------------------------------------------------------//

  void symlink_status_tests()
  {
    std::cout << "symlink_status_tests..." << std::endl;

    boost::system::error_code ec;

    fs::path dangling_sym(dir / "dangling-sym");
    fs::path dangling_directory_sym(dir / "dangling-directory-sym");
    fs::path sym_d1(dir / "sym-d1");
    fs::path symsym_d1(dir / "symsym-d1");
    fs::path sym_f1(dir / "sym-f1");
    fs::path symsym_f1(dir / "symsym-f1");
    fs::create_symlink("does not exist", dangling_sym);
    fs::create_directory_symlink("does not exist", dangling_directory_sym);
    fs::create_directory_symlink(d1, sym_d1);
    fs::create_directory_symlink(sym_d1, symsym_d1);
    fs::create_symlink(f1, sym_f1);
    fs::create_symlink(sym_f1, symsym_f1);

    //  verify all cases detected as symlinks
    BOOST_TEST_EQ(fs::symlink_status(dangling_sym, ec).type(), fs::symlink_file);
    BOOST_TEST_EQ(fs::symlink_status(dangling_directory_sym, ec).type(), fs::symlink_file);
    BOOST_TEST_EQ(fs::symlink_status(sym_d1, ec).type(), fs::symlink_file);
    BOOST_TEST_EQ(fs::symlink_status(symsym_d1, ec).type(), fs::symlink_file);
    BOOST_TEST_EQ(fs::symlink_status(sym_f1, ec).type(), fs::symlink_file);
    BOOST_TEST_EQ(fs::symlink_status(symsym_f1, ec).type(), fs::symlink_file);

    //  verify all cases resolve to the (possibly recursive) symlink target
    BOOST_TEST_EQ(fs::status(dangling_sym, ec).type(), fs::file_not_found);
    BOOST_TEST_EQ(fs::status(dangling_directory_sym, ec).type(), fs::file_not_found);

    BOOST_TEST_EQ(fs::status(sym_d1, ec).type(), fs::directory_file);
    BOOST_TEST_EQ(fs::status(sym_d1 / "d1f1", ec).type(), fs::regular_file);
    BOOST_TEST_EQ(fs::status(symsym_d1, ec).type(), fs::directory_file);
    BOOST_TEST_EQ(fs::status(symsym_d1 / "d1f1", ec).type(), fs::regular_file);
    BOOST_TEST_EQ(fs::status(sym_f1, ec).type(), fs::regular_file);
    BOOST_TEST_EQ(fs::status(symsym_f1, ec).type(), fs::regular_file);

#ifdef BOOST_WINDOWS_API

    //  On Windows, telling if a filesystem entry is a symlink, rather than some other
    //  kind of reparse point such as a junction, requires some truely baroque code.
    //  See ticket #4663, filesystem objects falsely identified as symlinks.
    //  This test checks two directory entries created by Windows itself to verify
    //  is_symlink() works correctly. Try "dir /A %HOMEPATH%\.." from the command line to
    //  verify this test is valid on your version of Windows. It only works on Vista and
    //  later.

    fs::path users(getenv("HOMEDRIVE"));
    BOOST_TEST(!users.empty());
    users /= "\\Users";
    BOOST_TEST(fs::exists(users));
    BOOST_TEST(fs::exists(users/"All Users"));
    BOOST_TEST(fs::exists(users/"Default User"));
    BOOST_TEST(fs::is_symlink(users/"All Users"));       // dir /A reports <SYMLINKD>
    BOOST_TEST(!fs::is_symlink(users/"Default User"));   // dir /A reports <JUNCTION>                  <JUNCTION>

#endif
  }

 //  copy_symlink_tests  ---------------------------------------------------------------//

  void copy_symlink_tests(const fs::path& f1, const fs::path& d1)
  {
    std::cout << "copy_symlink_tests..." << std::endl;

    BOOST_TEST(fs::exists(f1));
    BOOST_TEST(fs::exists(d1));
    fs::path sym1(d1 / "symlink1");
    fs::remove(sym1);  // remove possible residue from prior testing
    fs::create_symlink(f1, sym1);
    BOOST_TEST(fs::exists(sym1));
    BOOST_TEST(fs::is_symlink(sym1));
    fs::path sym2(d1 / "symlink2");
    fs::copy_symlink(sym1, sym2);
    BOOST_TEST(fs::exists(sym2));
    BOOST_TEST(fs::is_symlink(sym2));
    //fs::path sym3(d1 / "symlink3");
    //fs::copy(sym1, sym3);
    //BOOST_TEST(fs::exists(sym3));
    //BOOST_TEST(fs::is_symlink(sym3));

    bool copy_ex_ok = false;
    try { fs::copy_symlink("no-such-file", "new-symlink1"); }
    catch (const fs::filesystem_error &) { copy_ex_ok = true; }
    BOOST_TEST(copy_ex_ok);

    copy_ex_ok = false;
    try { fs::copy_symlink(f1, "new-symlink2"); } // should fail; f1 not symlink
    catch (const fs::filesystem_error &) { copy_ex_ok = true; }
    BOOST_TEST(copy_ex_ok);
  }

  //  write_time_tests  ----------------------------------------------------------------//

  void write_time_tests(const fs::path& dir)
  {    
    std::cout << "write_time_tests..." << std::endl;

    fs::path f1 = dir / "foobar2";
    create_file(f1, "foobar2");
    BOOST_TEST(fs::exists(f1));
    BOOST_TEST(!fs::is_directory(f1));
    BOOST_TEST(fs::is_regular_file(f1));
    BOOST_TEST(fs::file_size(f1) == 7);
    verify_file(f1, "foobar2");

    // Some file system report last write time as local (FAT), while
    // others (NTFS) report it as UTC. The C standard does not specify
    // if time_t is local or UTC. 

    std::time_t ft = fs::last_write_time(f1);
    std::cout << "\n  UTC last_write_time() for a file just created is "
      << std::asctime(std::gmtime(&ft)) << std::endl;

    std::tm * tmp = std::localtime(&ft);
    std::cout << "\n  Year is " << tmp->tm_year << std::endl;
    --tmp->tm_year;
    std::cout << "  Change year to " << tmp->tm_year << std::endl;
    fs::last_write_time(f1, std::mktime(tmp));
    std::time_t ft2 = fs::last_write_time(f1);
    std::cout << "  last_write_time() for the file is now "
      << std::asctime(std::gmtime(&ft2)) << std::endl;
    BOOST_TEST(ft != fs::last_write_time(f1));

    std::cout << "\n  Reset to current time" << std::endl;
    fs::last_write_time(f1, ft);
    double time_diff = std::difftime(ft, fs::last_write_time(f1));
    std::cout 
      << "  original last_write_time() - current last_write_time() is "
      << time_diff << " seconds" << std::endl;
    BOOST_TEST(time_diff >= -60.0 && time_diff <= 60.0);
  }

  //  platform_specific_tests  ---------------------------------------------------------//

  void platform_specific_tests()
  {
    // Windows only tests
    if (platform == "Windows")
    {
      std::cout << "Window specific tests..."
        "\n (may take several seconds)" << std::endl;

      BOOST_TEST(!fs::exists(fs::path("//share-not")));
      BOOST_TEST(!fs::exists(fs::path("//share-not/")));
      BOOST_TEST(!fs::exists(fs::path("//share-not/foo")));
      BOOST_TEST(!fs::exists("tools/jam/src/:sys:stat.h")); // !exists() if ERROR_INVALID_NAME
      BOOST_TEST(!fs::exists(":sys:stat.h")); // !exists() if ERROR_INVALID_PARAMETER
      BOOST_TEST(dir.string().size() > 1
        && dir.string()[1] == ':'); // verify path includes drive

      BOOST_TEST(fs::system_complete("").empty());
      BOOST_TEST(fs::system_complete("/") == init_path.root_path());
      BOOST_TEST(fs::system_complete("foo")
        == init_path / "foo");

      fs::path p1(fs::system_complete("/foo"));
      BOOST_TEST_EQ(p1.string().size(), 6U);  // this failed during v3 development due to bug
      std::string s1(p1.string() );
      std::string s2(init_path.root_path().string()+"foo");
      BOOST_TEST_EQ(s1, s2);

      BOOST_TEST(fs::system_complete(fs::path(init_path.root_name()))
        == init_path);
      BOOST_TEST(fs::system_complete(fs::path(init_path.root_name().string()
        + "foo")).string() == init_path / "foo");
      BOOST_TEST(fs::system_complete(fs::path("c:/")).generic_string()
        == "c:/");
      BOOST_TEST(fs::system_complete(fs::path("c:/foo")).generic_string()
        ==  "c:/foo");
      BOOST_TEST(fs::system_complete(fs::path("//share")).generic_string()
        ==  "//share");
    } // Windows

    else if (platform == "POSIX")
    {
      std::cout << "POSIX specific tests..." << std::endl;
      BOOST_TEST(fs::system_complete("").empty());
      BOOST_TEST(init_path.root_path().string() == "/");
      BOOST_TEST(fs::system_complete("/").string() == "/");
      BOOST_TEST(fs::system_complete("foo").string()
        == init_path.string()+"/foo");
      BOOST_TEST(fs::system_complete("/foo").string()
        == init_path.root_path().string()+"foo");
    } // POSIX
  }

  //  initial_tests  -------------------------------------------------------------------//

  void initial_tests()
  {
    std::cout << "initial_tests..." << std::endl;

    std::cout << "  current_path().string() is\n  \""
              << init_path.string()
              << "\"\n\n";
    BOOST_TEST(init_path.is_absolute());
    BOOST_TEST(fs::current_path().is_absolute());
    BOOST_TEST(init_path.string()
      == fs::current_path().string());
  }

  //  space_tests  ---------------------------------------------------------------------//

  void space_tests()
  {
    std::cout << "space_tests..." << std::endl;

    // make some reasonable assuptions for testing purposes
    fs::space_info spi(fs::space(dir));
    BOOST_TEST(spi.capacity > 1000000);
    BOOST_TEST(spi.free > 1000);
    BOOST_TEST(spi.capacity > spi.free);
    BOOST_TEST(spi.free >= spi.available);

    // it is convenient to display space, but older VC++ versions choke 
#   if !defined(BOOST_MSVC) || _MSC_VER >= 1300  // 1300 == VC++ 7.0
      std::cout << "   capacity = " << spi.capacity << '\n';
      std::cout << "       free = " << spi.free << '\n';
      std::cout << "  available = " << spi.available << '\n';
#   endif
  }

  //  equivalent_tests  ----------------------------------------------------------------//

  void equivalent_tests(const fs::path& f1)
  {
    std::cout << "equivalent_tests..." << std::endl;

    BOOST_TEST(CHECK_EXCEPTION(bad_equivalent, ENOENT));
    BOOST_TEST(fs::equivalent(f1, dir / "f1"));
    BOOST_TEST(fs::equivalent(dir, d1 / ".."));
    BOOST_TEST(!fs::equivalent(f1, dir));
    BOOST_TEST(!fs::equivalent(dir, f1));
    BOOST_TEST(!fs::equivalent(d1, d2));
    BOOST_TEST(!fs::equivalent(dir, ng));
    BOOST_TEST(!fs::equivalent(ng, dir));
    BOOST_TEST(!fs::equivalent(f1, ng));
    BOOST_TEST(!fs::equivalent(ng, f1));
  }

  //  _tests  --------------------------------------------------------------------------//

  void _tests()
  {
    std::cout << "_tests..." << std::endl;
  }
  
} // unnamed namespace

  //------------------------------------------------------------------------------------//
  //                                                                                    //
  //                                    main                                            //
  //                                                                                    //
  //------------------------------------------------------------------------------------//

int main(int argc, char* argv[])
{
// document state of critical macros
#ifdef BOOST_POSIX_API
  std::cout << "BOOST_POSIX_API is defined\n";
#endif
#ifdef BOOST_WINDOWS_API
  std::cout << "BOOST_WINDOWS_API is defined\n";
#endif

  if (argc > 1 && *argv[1]=='-' && *(argv[1]+1)=='t') report_throws = true;
  if (argc > 1 && *argv[1]=='-' && *(argv[1]+1)=='x') cleanup = false;

  // The choice of platform to test is make at runtime rather than compile-time
  // so that compile errors for all platforms will be detected even though
  // only the current platform is runtime tested.
# if defined(BOOST_POSIX_API)
    platform = "POSIX";
# elif defined(BOOST_WINDOWS_API)
    platform = "Windows";
#   if !defined(__MINGW32__) && !defined(__CYGWIN__)
      language_id = ::GetUserDefaultUILanguage();
#   else
      language_id = 0x0409; // Assume US English
#   endif
# else
#   error neither BOOST_POSIX_API nor BOOST_WINDOWS_API is defined. See boost/system/api_config.hpp
# endif
  std::cout << "API is " << platform << std::endl;

  dir = init_path / temp_dir_name;

  if (fs::exists(dir))
  {
    std::cout << "remove residue from prior failed tests..." << std::endl;
    fs::remove_all(dir);
  }
  BOOST_TEST(!fs::exists(dir));

  // several functions give unreasonable results if uintmax_t isn't 64-bits
  std::cout << "sizeof(boost::uintmax_t) = " << sizeof(boost::uintmax_t) << '\n';
  BOOST_TEST(sizeof(boost::uintmax_t) >= 8);

  initial_tests();
  predicate_and_status_tests();
  exception_tests();
  platform_specific_tests();
  create_directory_tests();
  current_directory_tests();
  space_tests();

  // create a directory tree that can be used by subsequent tests
  //
  //    dir
  //      d1
  //        d1f1       // an empty file
  //      f0           // an empty file
  //      f1           // a file containing "file f1"
  //
  create_tree();

  status_of_nonexistent_tests();
  status_error_reporting_tests();
  directory_iterator_tests();
  create_directories_tests();  // must run AFTER directory_iterator_tests

  bad_create_directory_path = f1;
  BOOST_TEST(CHECK_EXCEPTION(bad_create_directory, EEXIST));
  fs::file_status stat = fs::status(f1);
  BOOST_TEST(fs::status_known(stat));
  BOOST_TEST(fs::exists(stat));
  BOOST_TEST(!fs::is_directory(stat));
  BOOST_TEST(fs::is_regular_file(stat));
  BOOST_TEST(!fs::is_other(stat));
  BOOST_TEST(!fs::is_symlink(stat));
  
  equivalent_tests(f1);
  create_hard_link_tests();
  create_symlink_tests();
  resize_file_tests();
  absolute_tests();
  copy_file_tests(f1, d1);
  if (create_symlink_ok)  // only if symlinks supported
  {
    symlink_status_tests();
    copy_symlink_tests(f1, d1);
  }
  rename_tests();
  remove_tests(dir);
  if (create_symlink_ok)  // only if symlinks supported
    remove_symlink_tests();
  write_time_tests(dir);

  std::cout << "testing complete" << std::endl;

  // post-test cleanup
  if (cleanup)
  {
    std::cout << "post-test removal of " << dir << std::endl;
    BOOST_TEST(fs::remove_all(dir) != 0);
    // above was added just to simplify testing, but it ended up detecting
    // a bug (failure to close an internal search handle). 
    std::cout << "post-test removal complete" << std::endl;
    BOOST_TEST(!fs::exists(dir));
    BOOST_TEST(fs::remove_all(dir) == 0);
  }

  std::cout << "returning from main()" << std::endl;
  return ::boost::report_errors();
} // main

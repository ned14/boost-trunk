//  link_check header  -------------------------------------------------------//

//  Copyright Beman Dawes 2002
//  Copyright Rene Rivera 2004.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LINK_CHECK_HPP
#define BOOST_LINK_CHECK_HPP

#include <map>

#include "inspector.hpp"

namespace boost
{
  namespace inspect
  {
    const int m_linked_to = 1;
    const int m_present = 2;

    class link_check : public hypertext_inspector
    {
      long m_broken_errors;
      long m_unlinked_errors;
      long m_invalid_errors;
      long m_bookmark_errors;

      typedef std::map< string, int > m_path_map;
      m_path_map m_paths; // first() is relative initial_path()

      void do_url( const string & url,
        const string & library_name, const path & full_source_path );
    public:

      link_check();
      virtual const char * name() const { return "*A*"; }
      virtual const char * desc() const { return "invalid bookmarks, invalid urls, broken links, unlinked files"; }

      virtual void inspect(
        const std::string & library_name,
        const path & full_path );

      virtual void inspect(
        const std::string & library_name,
        const path & full_path,
        const std::string & contents );

      virtual void close();

      virtual ~link_check()
        {
          std::cout << "  " << m_bookmark_errors << " bookmarks with invalid characters\n";
          std::cout << "  " << m_invalid_errors << " invalid urls\n";
          std::cout << "  " << m_broken_errors << " broken links\n";
          std::cout << "  " << m_unlinked_errors << " unlinked files\n";
        }
    };
  }
}

#endif // BOOST_LINK_CHECK_HPP

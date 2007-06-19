/*=============================================================================
    Spirit v1.6.2
    Copyright (c) 2003 2003 Vaclav Vesely
    http://spirit.sourceforge.net/

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at 
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
// see https://sourceforge.net/tracker/index.php?func=detail&aid=718903&group_id=28447&atid=393386

#ifdef BOOST_MSVC
#pragma warning(disable:4786)
#endif

#include <boost/cstdlib.hpp>
#include <boost/spirit/core.hpp>
#include <boost/spirit/utility/chset.hpp>

using namespace std;
using namespace boost;
using namespace spirit;

int main(int, char *[])
{
        empty_match_parser<chset<char> >
                e(epsilon_p(chset_p("abc")));

    return exit_success;
}

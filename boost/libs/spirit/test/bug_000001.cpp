/*=============================================================================
  Spirit V1.6.2
  Copyright (c) 2003 Giovanni Bajo
  http://spirit.sourceforge.net/

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at 
    http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/
// access_node_d[] and access_match_d[] iterator bug
// http://sf.net/mailarchive/forum.php?thread_id=1963157&forum_id=1595
// http://sf.net/mailarchive/forum.php?thread_id=1966224&forum_id=1595

#include <boost/spirit/tree/ast.hpp>
#include <assert.h>

using namespace boost::spirit;

struct my_action
{
    template <typename TreeT, typename IterT>
    void operator()(TreeT& t, IterT begin, IterT end) const
    {
        assert(*begin == '1');
        assert(*end == '2');
    }
};

int main(void)
{
    const char* text = "123";
        
    ast_parse(text, text+3, access_node_d[chlit<>('1')][my_action()]);
    ast_parse(text, text+3, access_match_d[chlit<>('1')][my_action()]);

    return 0;
}

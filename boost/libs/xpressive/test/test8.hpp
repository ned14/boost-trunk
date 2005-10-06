///////////////////////////////////////////////////////////////////////////////
// test8.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "./test.hpp"

///////////////////////////////////////////////////////////////////////////////
// get_test_cases
//
template<typename BidiIterT>
boost::iterator_range<test_case<BidiIterT> const *> get_test_cases()
{
    typedef typename boost::iterator_value<BidiIterT>::type char_type;
    typedef test_case<BidiIterT> test_case;
    typedef basic_regex<BidiIterT> regex_type;

    static char_type const *nil = 0;
    static test_case const test_cases[] =
    {
        test_case // test141
        (
            L("bbbc")
          , L("^(b?){2}bc$")
          , regex_type(bos >> repeat<2>(s1= optional(L('b'))) >> L("bc") >> eos)
          , L("")
          , backrefs(L("bbbc"), L("b"), nil)
        )
      , test_case // test142
        (
            L("bbbbc")
          , L("^(b?){2}bc$")
          , regex_type(bos >> repeat<2>(s1= optional(L('b'))) >> L("bc") >> eos)
          , L("")
          , no_match
        )
      , test_case // test143
        (
            L("bbbbc")
          , L("^(b?)*d$")
          , regex_type(bos >> *(s1= optional(L('b'))) >> L('d') >> eos)
          , L("")
          , no_match
        )
      , test_case // test144
        (
            L("bc")
          , L("^(b?){2}?bc$")
          , regex_type(bos >> -repeat<2>(s1= optional(L('b'))) >> L("bc") >> eos)
          , L("")
          , backrefs(L("bc"), L(""), nil)
        )
      , test_case // test145
        (
            L("bbc")
          , L("^(b?){2}?bc$")
          , regex_type(bos >> -repeat<2>(s1= optional(L('b'))) >> L("bc") >> eos)
          , L("")
          , backrefs(L("bbc"), L(""), nil)
        )
      , test_case // test146
        (
            L("bbbc")
          , L("^(b?){2}?bc$")
          , regex_type(bos >> -repeat<2>(s1= optional(L('b'))) >> L("bc") >> eos)
          , L("")
          , backrefs(L("bbbc"), L("b"), nil)
        )
      , test_case // test147
        (
            L("bbbbc")
          , L("^(b?){2}?bc$")
          , regex_type(bos >> -repeat<2>(s1= optional(L('b'))) >> L("bc") >> eos)
          , L("")
          , no_match
        )
      , test_case // test148
        (
            L("bbbbc")
          , L("^(b?)*?d$")
          , regex_type(bos >> -*(s1= optional(L('b'))) >> L('d') >> eos)
          , L("")
          , no_match
        )
      , test_case // test149
        (
            L("bc")
          , L("^(b?\?){2}bc$")
          , regex_type(bos >> repeat<2>(s1= -optional(L('b'))) >> L("bc") >> eos)
          , L("")
          , backrefs(L("bc"), L(""), nil)
        )
      , test_case // test150
        (
            L("bbc")
          , L("^(b?\?){2}bc$")
          , regex_type(bos >> repeat<2>(s1= -optional(L('b'))) >> L("bc") >> eos)
          , L("")
          , backrefs(L("bbc"), L("b"), nil)
        )
    };

    return boost::make_iterator_range(test_cases);
}

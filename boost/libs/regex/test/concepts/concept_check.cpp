/*
 *
 * Copyright (c) 2003
 * Dr John Maddock
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Dr John Maddock makes no representations
 * about the suitability of this software for any purpose.
 * It is provided "as is" without express or implied warranty.
 *
 */


#include <boost/regex.hpp>
#include <boost/concept_archetype.hpp>
#if defined(BOOST_MSVC)
// this lets us compile at warning level 4 without seeing concept-check related warnings
#  pragma warning(disable:4100)
#endif
#include <boost/concept_check.hpp>
#include <boost/detail/workaround.hpp>


int main()
{
   // VC6 and VC7 can't cope with the iterator architypes, 
   // don't bother testing as it doesn't work:
#if !BOOST_WORKAROUND(BOOST_MSVC, < 1310)
   typedef boost::bidirectional_iterator_archetype<char> iterator_type;
   boost::regex r;
   iterator_type a, b;
   boost::detail::dummy_constructor dummy;
   boost::output_iterator_archetype<char> out(dummy);
   std::string s;
   boost::match_results<iterator_type> what;

   boost::regex_match(a, b, r);
   boost::regex_match(a, b, what, r);
   boost::regex_search(a, b, r);
   boost::regex_search(a, b, what, r);
   out = boost::regex_replace(out, a, b, r, s, boost::match_default);
   s = boost::regex_replace(s, r, s, boost::match_default);

   out = what.format(out, s, boost::format_default);
   s = what.format(s, boost::format_default);

   boost::function_requires<
      boost::ForwardIteratorConcept<
         boost::regex_iterator<iterator_type>
      >
   >();
   // this fails with glibc++v2 :
#if !BOOST_WORKAROUND(__GNUC__, < 3) && !BOOST_WORKAROUND(BOOST_MSVC, <1300)
   boost::function_requires<
      boost::ForwardIteratorConcept<
         boost::regex_token_iterator<iterator_type>
      >
   >();
#endif
#endif
   return 0;
}


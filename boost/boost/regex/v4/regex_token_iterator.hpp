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

 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         regex_token_iterator.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Provides regex_token_iterator implementation.
  */

#ifndef BOOST_REGEX_V4_REGEX_TOKEN_ITERATOR_HPP
#define BOOST_REGEX_V4_REGEX_TOKEN_ITERATOR_HPP

#include <boost/shared_ptr.hpp>
#include <boost/detail/workaround.hpp>

namespace boost{

template <class BidirectionalIterator, 
          class charT,
          class traits,
          class Allocator>
class regex_token_iterator_implementation 
{
   typedef basic_regex<charT, traits, Allocator> regex_type;
   typedef std::basic_string<charT>              value_type;

   match_results<BidirectionalIterator> what;   // current match
   BidirectionalIterator                end;    // end of search area
   const regex_type*                    pre;    // the expression
   match_flag_type                      flags;  // match flags
   std::basic_string<charT>             result; // the current string result
   int                                  N;      // the current sub-expression being enumerated
   std::vector<int>                     subs;   // the sub-expressions to enumerate

public:
   regex_token_iterator_implementation(const regex_type* p, BidirectionalIterator last, int sub, match_flag_type f)
      : end(last), pre(p), flags(f){ subs.push_back(sub); }
   regex_token_iterator_implementation(const regex_type* p, BidirectionalIterator last, const std::vector<int>& v, match_flag_type f)
      : end(last), pre(p), subs(v), flags(f){}
#if !BOOST_WORKAROUND(BOOST_MSVC, < 1300)
   template <std::size_t CN>
   regex_token_iterator_implementation(const regex_type* p, BidirectionalIterator last, const int (&submatches)[CN], match_flag_type f)
      : end(last), pre(p), flags(f)
   { 
      for(std::size_t i = 0; i < CN; ++i)
         subs.push_back(submatches[i]); 
   }
#endif

   bool init(BidirectionalIterator first)
   {
      if(regex_search(first, end, what, *pre, flags) == true)
      {
         N = 0;
         result = ((subs[N] == -1) ? value_type(what.prefix().str()) : value_type(what[(int)subs[N]].str()));
         return true;
      }
      else if((N == -1) && (first != end))
      {
         result = value_type(first, end);
         return true;
      }
      return false;
   }
   bool compare(const regex_token_iterator_implementation& that)
   {
      if(this == &that) return true;
      return (pre == that.pre) 
         && (end == that.end) 
         && (flags == that.flags) 
         && (N == that.N) 
         && (what[0].first == that.what[0].first) 
         && (what[0].second == that.what[0].second);
   }
   const std::basic_string<charT>& get()
   { return result; }
   bool next()
   {
      if(N == -1)
         return false;
      if(N+1 < (int)subs.size())
      {
         ++N;
         result =((subs[N] == -1) ? value_type(what.prefix().str()) : value_type(what[subs[N]].str()));
         return true;
      }
      if(what.prefix().first != what[0].second)
         flags |= match_prev_avail;
      BidirectionalIterator last_end = what[0].second;
      if(regex_search(what[0].second, end, what, *pre, ((what[0].first == what[0].second) ? flags | regex_constants::match_not_initial_null : flags)))
      {
         N =0;
         result =((subs[N] == -1) ? value_type(what.prefix().str()) : value_type(what[subs[N]].str()));
         return true;
      }
      else if((last_end != end) && (subs[0] == -1))
      {
         N =-1;
         result =value_type(last_end, end);
         return true;
      }
      return false;
   }
};

template <class BidirectionalIterator, 
          class charT = typename re_detail::regex_iterator_traits<BidirectionalIterator>::value_type,
          class traits = regex_traits<charT>,
          class Allocator = BOOST_DEFAULT_ALLOCATOR(charT) >
class regex_token_iterator 
{
private:
   typedef regex_token_iterator_implementation<BidirectionalIterator, charT, traits, Allocator> impl;
   typedef shared_ptr<impl> pimpl;
public:
   typedef          basic_regex<charT, traits, Allocator>                   regex_type;
   typedef          std::basic_string<charT>                                value_type;
   typedef typename re_detail::regex_iterator_traits<BidirectionalIterator>::difference_type 
                                                                            difference_type;
   typedef          const value_type*                                       pointer;
   typedef          const value_type&                                       reference; 
   typedef          std::forward_iterator_tag                               iterator_category;
   
   regex_token_iterator(){}
   regex_token_iterator(BidirectionalIterator a, BidirectionalIterator b, const regex_type& re, 
                        int submatch = 0, match_flag_type m = match_default)
                        : pdata(new impl(&re, b, submatch, m))
   {
      if(!pdata->init(a))
         pdata.reset();
   }
   regex_token_iterator(BidirectionalIterator a, BidirectionalIterator b, const regex_type& re, 
                        const std::vector<int>& submatches, match_flag_type m = match_default)
                        : pdata(new impl(&re, b, submatches, m))
   {
      if(!pdata->init(a))
         pdata.reset();
   }
#if !BOOST_WORKAROUND(BOOST_MSVC, < 1300)
   template <std::size_t N>
   regex_token_iterator(BidirectionalIterator a, BidirectionalIterator b, const regex_type& re, 
                        const int (&submatches)[N], match_flag_type m = match_default)
                        : pdata(new impl(&re, b, submatches, m))
   {
      if(!pdata->init(a))
         pdata.reset();
   }
#endif
   regex_token_iterator(const regex_token_iterator& that)
      : pdata(that.pdata) {}
   regex_token_iterator& operator=(const regex_token_iterator& that)
   {
      pdata = that.pdata;
      return *this;
   }
   bool operator==(const regex_token_iterator& that)
   { 
      if((pdata.get() == 0) || (that.pdata.get() == 0))
         return pdata.get() == that.pdata.get();
      return pdata->compare(*(that.pdata.get())); 
   }
   bool operator!=(const regex_token_iterator& that)
   { return !(*this == that); }
   const value_type& operator*()
   { return pdata->get(); }
   const value_type* operator->()
   { return &(pdata->get()); }
   regex_token_iterator& operator++()
   {
      cow();
      if(0 == pdata->next())
      {
         pdata.reset();
      }
      return *this;
   }
   regex_token_iterator operator++(int)
   {
      regex_token_iterator result(*this);
      ++(*this);
      return result;
   }
private:

   pimpl pdata;

   void cow()
   {
      // copy-on-write
      if(pdata.get() && !pdata.unique())
      {
         pdata.reset(new impl(*(pdata.get())));
      }
   }
};


} // namespace boost

#endif // BOOST_REGEX_V4_REGEX_TOKEN_ITERATOR_HPP



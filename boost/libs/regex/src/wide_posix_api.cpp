/*
 *
 * Copyright (c) 1998-2000
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
  *   FILE:        wide_posix_api.cpp
  *   VERSION:     3.10
  *   DESCRIPTION: Implements the wide character POSIX API wrappers.
  */

#include <boost/regex/detail/regex_config.hpp>

#ifndef BOOST_RE_NO_WCSTRING

#include <boost/regex.hpp>

#ifndef BOOST_RE_NO_WCHAR_H
#include <cwchar>
#endif
#include <cstring>
#include <cstdio>

namespace boost{

namespace {

unsigned int wmagic_value = 28631;

const wchar_t* wnames[] = {L"REG_NOERROR", L"REG_NOMATCH", L"REG_BADPAT", L"REG_ECOLLATE",
                        L"REG_ECTYPE", L"REG_EESCAPE", L"REG_ESUBREG", L"REG_EBRACK",
                        L"REG_EPAREN", L"REG_EBRACE", L"REG_BADBR", L"REG_ERANGE",
                        L"REG_ESPACE", L"REG_BADRPT", L"REG_EMPTY", L"REG_E_UNKNOWN"};

}

BOOST_RE_IX_DECL int BOOST_RE_CCALL regcompW(regex_tW* expression, const wchar_t* ptr, int f)
{
   BOOST_RE_GUARD_STACK
   if(expression->re_magic != wmagic_value)
   {
      expression->guts = 0;
      try{
      expression->guts = new wregex();
      } catch(...)
      {
         return REG_ESPACE;
      }
   }
   // set default flags:
   jm_uintfast32_t flags = (f & REG_EXTENDED) ? regbase::extended : regbase::basic;
   expression->eflags = (f & REG_NEWLINE) ? match_not_dot_newline : 0;

   // and translate those that are actually set:
   if(f & REG_NOCOLLATE)
      flags |= regbase::nocollate;

   if(f & REG_NOSUB)
      expression->eflags |= match_any;

   if(f & REG_NOSPEC)
      flags |= regbase::literal;
   if(f & REG_ICASE)
      flags |= regbase::icase;
   if(f & REG_ESCAPE_IN_LISTS)
      flags |= regbase::escape_in_lists;
   if(f & REG_NEWLINE_ALT)
      flags |= regbase::newline_alt;

   const wchar_t* p2;
   if(f & REG_PEND)
      p2 = expression->re_endp;
   else p2 = ptr + std::wcslen(ptr);

   int result;

   try{
      expression->re_magic = wmagic_value;
      ((wregex*)(expression->guts))->set_expression(ptr, p2, flags);
      expression->re_nsub = ((wregex*)(expression->guts))->mark_count() - 1;
      result = ((wregex*)(expression->guts))->error_code();
   } catch(...)
   {
      result = REG_E_UNKNOWN;
   }
   if(result)
      regfreeW(expression);
   return result;

}

BOOST_RE_IX_DECL unsigned int BOOST_RE_CCALL regerrorW(int code, const regex_tW* e, wchar_t* buf, unsigned int buf_size)
{
   BOOST_RE_GUARD_STACK
   unsigned int result = 0;
   if(code & REG_ITOA)
   {
      code &= ~REG_ITOA;
      if(code <= REG_E_UNKNOWN)
      {
         result = std::wcslen(wnames[code]) + 1;
         if(buf_size >= result)
            std::wcscpy(buf, wnames[code]);
         return result;
      }
      return result;
   }
#if !defined(BOOST_RE_NO_SWPRINTF)
   if(code == REG_ATOI)
   {
      wchar_t localbuf[5];
      if(e == 0)
         return 0;
      for(int i = 0; i <= REG_E_UNKNOWN; ++i)
      {
         if(std::wcscmp(e->re_endp, wnames[i]) == 0)
         {
            std::swprintf(localbuf, 5, L"%d", i);
            if(std::wcslen(localbuf) < buf_size)
               std::wcscpy(buf, localbuf);
            return std::wcslen(localbuf) + 1;
         }
      }
      std::swprintf(localbuf, 5, L"%d", 0);
      if(std::wcslen(localbuf) < buf_size)
         std::wcscpy(buf, localbuf);
      return std::wcslen(localbuf) + 1;
   }
#endif
   if(code <= REG_E_UNKNOWN)
   {
      regex_traits<wchar_t> rt;
      const regex_traits<wchar_t>* pt = &rt;
      if(e && (e->re_magic == wmagic_value))
         pt = &((wregex*)(e->guts))->get_traits();
      (void)pt; // warning suppression
      std::string p = pt->error_string(code);
      unsigned int len = pt->strwiden((wchar_t*)0, 0, p.c_str());
      if(len < buf_size)
      {
         pt->strwiden(buf, buf_size, p.c_str());
      }
      return len + 1;
   }
   if(buf_size)
      *buf = 0;
   return 0;
}

BOOST_RE_IX_DECL int BOOST_RE_CCALL regexecW(const regex_tW* expression, const wchar_t* buf, unsigned int n, regmatch_t* array, int eflags)
{
   BOOST_RE_GUARD_STACK
   bool result = false;
   jm_uintfast32_t flags = match_default | expression->eflags;
   const wchar_t* end;
   const wchar_t* start;
   wcmatch m;
   
   if(eflags & REG_NOTBOL)
      flags |= match_not_bol;
   if(eflags & REG_NOTEOL)
      flags |= match_not_eol;
   if(eflags & REG_STARTEND)
   {
      start = buf + array[0].rm_so;
      end = buf + array[0].rm_eo;
   }
   else
   {
      start = buf;
      end = buf + std::wcslen(buf);
   }

   try{
   if(expression->re_magic == wmagic_value)
   {
      result = regex_search(start, end, m, *(wregex*)(expression->guts), flags);
   }
   else
      return result;
   } catch(...)
   {
      return REG_E_UNKNOWN;
   }

   if(result)
   {
      // extract what matched:
     unsigned int i;
      for(i = 0; (i < n) && (i < expression->re_nsub + 1); ++i)
      {
         array[i].rm_so = (m[i].matched == false) ? -1 : (m[i].first - buf);
         array[i].rm_eo = (m[i].matched == false) ? -1 : (m[i].second - buf);
      }
      // and set anything else to -1:
      for(i = expression->re_nsub + 1; i < n; ++i)
      {
         array[i].rm_so = -1;
         array[i].rm_eo = -1;
      }
      return 0;
   }
   return REG_NOMATCH;
}

BOOST_RE_IX_DECL void BOOST_RE_CCALL regfreeW(regex_tW* expression)
{
   BOOST_RE_GUARD_STACK
   if(expression->re_magic == wmagic_value)
   {
      delete (wregex*)(expression->guts);
   }
   expression->re_magic = 0;
}

} // namespace boost;

#endif



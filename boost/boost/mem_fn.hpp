#ifndef BOOST_MEM_FN_HPP_INCLUDED
#define BOOST_MEM_FN_HPP_INCLUDED

#if _MSC_VER+0 >= 1020
#pragma once
#endif

//
//  mem_fn.hpp - a generalization of std::mem_fun[_ref]
//
//  Copyright (c) 2001, 2002 Peter Dimov and Multi Media Ltd.
//  Copyright (c) 2001 David Abrahams
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  See http://www.boost.org/libs/bind/mem_fn.html for documentation.
//

#include <boost/config.hpp>
#include <boost/get_pointer.hpp>
#include <boost/detail/workaround.hpp>

namespace boost
{

#if defined(BOOST_NO_VOID_RETURNS)

#define BOOST_MEM_FN_CLASS_F , class F
#define BOOST_MEM_FN_TYPEDEF(X)

namespace _mfi // mem_fun_impl
{

template<class V> struct mf
{

#define BOOST_MEM_FN_RETURN return

#define BOOST_MEM_FN_NAME(X) inner_##X
#define BOOST_MEM_FN_CC

#include <boost/bind/mem_fn_template.hpp>

#undef BOOST_MEM_FN_CC
#undef BOOST_MEM_FN_NAME

#ifdef BOOST_MEM_FN_ENABLE_STDCALL

#define BOOST_MEM_FN_NAME(X) inner_##X##_stdcall
#define BOOST_MEM_FN_CC __stdcall

#include <boost/bind/mem_fn_template.hpp>

#undef BOOST_MEM_FN_CC
#undef BOOST_MEM_FN_NAME

#endif

#ifdef BOOST_MEM_FN_ENABLE_FASTCALL

#define BOOST_MEM_FN_NAME(X) inner_##X##_fastcall
#define BOOST_MEM_FN_CC __fastcall

#include <boost/bind/mem_fn_template.hpp>

#undef BOOST_MEM_FN_CC
#undef BOOST_MEM_FN_NAME

#endif

#undef BOOST_MEM_FN_RETURN

}; // struct mf<V>

template<> struct mf<void>
{

#define BOOST_MEM_FN_RETURN

#define BOOST_MEM_FN_NAME(X) inner_##X
#define BOOST_MEM_FN_CC

#include <boost/bind/mem_fn_template.hpp>

#undef BOOST_MEM_FN_CC
#undef BOOST_MEM_FN_NAME

#ifdef BOOST_MEM_FN_ENABLE_STDCALL

#define BOOST_MEM_FN_NAME(X) inner_##X##_stdcall
#define BOOST_MEM_FN_CC __stdcall

#include <boost/bind/mem_fn_template.hpp>

#undef BOOST_MEM_FN_CC
#undef BOOST_MEM_FN_NAME

#endif

#ifdef BOOST_MEM_FN_ENABLE_FASTCALL

#define BOOST_MEM_FN_NAME(X) inner_##X##_fastcall
#define BOOST_MEM_FN_CC __fastcall

#include <boost/bind/mem_fn_template.hpp>

#undef BOOST_MEM_FN_CC
#undef BOOST_MEM_FN_NAME

#endif

#undef BOOST_MEM_FN_RETURN

}; // struct mf<void>

#undef BOOST_MEM_FN_CLASS_F
#undef BOOST_MEM_FN_TYPEDEF_F

#define BOOST_MEM_FN_NAME(X) X
#define BOOST_MEM_FN_NAME2(X) inner_##X
#define BOOST_MEM_FN_CC

#include <boost/bind/mem_fn_vw.hpp>

#undef BOOST_MEM_FN_NAME
#undef BOOST_MEM_FN_NAME2
#undef BOOST_MEM_FN_CC

#ifdef BOOST_MEM_FN_ENABLE_STDCALL

#define BOOST_MEM_FN_NAME(X) X##_stdcall
#define BOOST_MEM_FN_NAME2(X) inner_##X##_stdcall
#define BOOST_MEM_FN_CC __stdcall

#include <boost/bind/mem_fn_vw.hpp>

#undef BOOST_MEM_FN_NAME
#undef BOOST_MEM_FN_NAME2
#undef BOOST_MEM_FN_CC

#endif

#ifdef BOOST_MEM_FN_ENABLE_FASTCALL

#define BOOST_MEM_FN_NAME(X) X##_fastcall
#define BOOST_MEM_FN_NAME2(X) inner_##X##_fastcall
#define BOOST_MEM_FN_CC __fastcall

#include <boost/bind/mem_fn_vw.hpp>

#undef BOOST_MEM_FN_NAME
#undef BOOST_MEM_FN_NAME2
#undef BOOST_MEM_FN_CC

#endif

} // namespace _mfi

#else // #ifdef BOOST_NO_VOID_RETURNS

#define BOOST_MEM_FN_CLASS_F
#define BOOST_MEM_FN_TYPEDEF(X) typedef X;

namespace _mfi
{

#define BOOST_MEM_FN_RETURN return

#define BOOST_MEM_FN_NAME(X) X
#define BOOST_MEM_FN_CC

#include <boost/bind/mem_fn_template.hpp>

#undef BOOST_MEM_FN_CC
#undef BOOST_MEM_FN_NAME

#ifdef BOOST_MEM_FN_ENABLE_STDCALL

#define BOOST_MEM_FN_NAME(X) X##_stdcall
#define BOOST_MEM_FN_CC __stdcall

#include <boost/bind/mem_fn_template.hpp>

#undef BOOST_MEM_FN_CC
#undef BOOST_MEM_FN_NAME

#endif

#ifdef BOOST_MEM_FN_ENABLE_FASTCALL

#define BOOST_MEM_FN_NAME(X) X##_fastcall
#define BOOST_MEM_FN_CC __fastcall

#include <boost/bind/mem_fn_template.hpp>

#undef BOOST_MEM_FN_CC
#undef BOOST_MEM_FN_NAME

#endif

#undef BOOST_MEM_FN_RETURN

} // namespace _mfi

#undef BOOST_MEM_FN_CLASS_F
#undef BOOST_MEM_FN_TYPEDEF

#endif // #ifdef BOOST_NO_VOID_RETURNS

#define BOOST_MEM_FN_NAME(X) X
#define BOOST_MEM_FN_CC

#include <boost/bind/mem_fn_cc.hpp>

#undef BOOST_MEM_FN_NAME
#undef BOOST_MEM_FN_CC

#ifdef BOOST_MEM_FN_ENABLE_STDCALL

#define BOOST_MEM_FN_NAME(X) X##_stdcall
#define BOOST_MEM_FN_CC __stdcall

#include <boost/bind/mem_fn_cc.hpp>

#undef BOOST_MEM_FN_NAME
#undef BOOST_MEM_FN_CC

#endif

#ifdef BOOST_MEM_FN_ENABLE_FASTCALL

#define BOOST_MEM_FN_NAME(X) X##_fastcall
#define BOOST_MEM_FN_CC __fastcall

#include <boost/bind/mem_fn_cc.hpp>

#undef BOOST_MEM_FN_NAME
#undef BOOST_MEM_FN_CC

#endif

// data member support

namespace _mfi
{

template<class R, class T> class dm
{
public:

    typedef R const & result_type;
    typedef T const * argument_type;

private:
    
    typedef R (T::*F);
    F f_;

    template<class U> R const & call(U & u, T const *) const
    {
        return (u.*f_);
    }

    template<class U> R & call(U & u, T *) const
    {
        return (u.*f_);
    }

    template<class U> R const & call(U & u, void const *) const
    {
        return (get_pointer(u)->*f_);
    }

public:
    
    explicit dm(F f): f_(f) {}

    R & operator()(T * p) const
    {
        return (p->*f_);
    }

    R const & operator()(T const * p) const
    {
        return (p->*f_);
    }

    template<class U> R const & operator()(U & u) const
    {
        return call(u, &u);
    }

#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1300) && !BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3003))

    R & operator()(T & t) const
    {
        return (t.*f_);
    }

#endif

    R const & operator()(T const & t) const
    {
        return (t.*f_);
    }
};

} // namespace _mfi

template<class R, class T> _mfi::dm<R, T> mem_fn(R T::*f)
{
    return _mfi::dm<R, T>(f);
}

} // namespace boost

#endif // #ifndef BOOST_MEM_FN_HPP_INCLUDED

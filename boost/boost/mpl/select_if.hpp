//-----------------------------------------------------------------------------
// boost/mpl/select_if_if.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02 Boost.org
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MPL_SELECT_IF_HPP_INCLUDED
#define BOOST_MPL_SELECT_IF_HPP_INCLUDED

#include "boost/mpl/aux_/lambda_spec.hpp"
#include "boost/config.hpp"

namespace boost {
namespace mpl {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<
      bool C
    , typename T1
    , typename T2
    >
struct select_if_c
{
    typedef T1 type;
};

template<
      typename T1
    , typename T2
    >
struct select_if_c<false,T1,T2>
{
    typedef T2 type;
};

template<
      typename C
    , typename T1
    , typename T2
    >
struct select_if
{
    typedef typename select_if_c<
          C::value
        , T1
        , T2
        >::type type;
};

#elif defined(BOOST_MSVC) && (BOOST_MSVC <= 1200)

// MSVC6.5-specific version

template<
      bool C
    , typename T1
    , typename T2
    >
struct select_if_c
{
 private:
    template<bool> struct answer        { typedef T1 type; };
    template<>     struct answer<false>	{ typedef T2 type; };
 
 public:
    typedef typename answer< C >::type type;
};

// (almost) copy & paste in order to save one more 
// recursively nested template instantiation to user
template<
      typename C
    , typename T1
    , typename T2
    >
struct select_if
{
 private:
    template<bool> struct answer        { typedef T1 type; };
    template<>     struct answer<false>	{ typedef T2 type; };
 
 public:
    typedef typename answer< C::value >::type type;
};

#else

// no partial class template specialization

namespace aux {

template< bool C >
struct select_if_impl
{
    template< typename T1, typename T2 > struct result_
    {
        typedef T1 type;
    };
};

template<>
struct select_if_impl<false>
{
    template< typename T1, typename T2 > struct result_
    { 
        typedef T2 type;
    };
};

} // namespace aux

template<
      bool C
    , typename T1
    , typename T2
    >
struct select_if_c
{
    typedef typename aux::select_if_impl< C >
        ::template result_<T1,T2>::type type;
};

// (almost) copy & paste in order to save one more 
// recursively nested template instantiation to user
template<
      typename C
    , typename T1
    , typename T2
    >
struct select_if
{
    typedef typename aux::select_if_impl< C::value >
        ::template result_<T1,T2>::type type;
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

BOOST_MPL_AUX_LAMBDA_SPEC(3, select_if)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_SELECT_IF_HPP_INCLUDED

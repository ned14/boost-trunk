//-----------------------------------------------------------------------------
// boost mpl/at.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MPL_AT_HPP_INCLUDED
#define BOOST_MPL_AT_HPP_INCLUDED

#include "boost/mpl/begin_end.hpp"
#include "boost/mpl/advance.hpp"
#include "boost/mpl/aux_/msvc_workarounds.hpp"
#include "boost/mpl/aux_/lambda_spec.hpp"

namespace boost {
namespace mpl {

template<
      typename N
    , typename Sequence
    >
struct at
{
 private:
    typedef typename begin<Sequence>::type first_;
    typedef typename advance<first_,N>::type iter_;

 public:
#if defined(BOOST_MSVC) && (BOOST_MSVC < 1300)
    typedef typename apply0<iter_>::type type;
#else
    typedef typename iter_::type type;
#endif
};

template<
      long N
    , typename Sequence
    >
struct at_c
{
 private:
    typedef typename begin<Sequence>::type first_;
    typedef typename advance_c<first_,N>::type iter_;

 public:
#if defined(BOOST_MSVC) && (BOOST_MSVC < 1300)
    typedef typename apply0<iter_>::type type;
#else
    typedef typename iter_::type type;
#endif
};

BOOST_MPL_AUX_LAMBDA_SPEC(2, at)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_AT_HPP_INCLUDED

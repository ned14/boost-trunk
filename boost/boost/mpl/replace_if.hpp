
#ifndef BOOST_MPL_REPLACE_IF_HPP_INCLUDED
#define BOOST_MPL_REPLACE_IF_HPP_INCLUDED

// Copyright (c) Aleksey Gurtovoy 2000-2004
// Copyright (c) John R. Bandela 2000-2002
// Copyright (c) David Abrahams 2003-2004
//
// Use, modification and distribution are subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy 
// at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/transform.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/protect.hpp>
#include <boost/mpl/aux_/common_name_wknd.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

BOOST_MPL_AUX_COMMON_NAME_WKND(replace_if)

namespace aux {

template< typename Predicate, typename T >
struct replace_if_op
{
    template< typename U > struct apply
    {
        typedef typename if_<
              typename apply1<Predicate,U>::type
            , T
            , U
            >::type type;
    };
};

} // namespace aux

BOOST_MPL_AUX_AGLORITHM_NAMESPACE_BEGIN

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Predicate)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    , typename BOOST_MPL_AUX_NA_PARAM(Inserter)
    >
struct replace_if
    : transform1<
          Sequence
        , protect< aux::replace_if_op<pred_,T> >
        , Inserter
        >
{
};

BOOST_MPL_AUX_AGLORITHM_NAMESPACE_END

BOOST_MPL_AUX_NA_ALGORITHM_SPEC(3, replace_if)

}}

#endif // BOOST_MPL_REPLACE_IF_HPP_INCLUDED


#ifndef BOOST_MPL_REPLACE_HPP_INCLUDED
#define BOOST_MPL_REPLACE_HPP_INCLUDED

// Copyright (c) Aleksey Gurtovoy 2000-2004
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

#include <boost/mpl/replace_if.hpp>
#include <boost/mpl/protect.hpp>
#include <boost/mpl/same_as.hpp>
#include <boost/mpl/aux_/common_name_wknd.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

BOOST_MPL_AUX_COMMON_NAME_WKND(replace)

BOOST_MPL_AUX_AGLORITHM_NAMESPACE_BEGIN

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(OldType)
    , typename BOOST_MPL_AUX_NA_PARAM(NewType)
    >
struct replace
    : replace_if< Sequence, protect< same_as<OldType> >, NewType >
{
};

BOOST_MPL_AUX_AGLORITHM_NAMESPACE_END

BOOST_MPL_AUX_NA_ALGORITHM_SPEC(3, replace)

}}

#endif // BOOST_MPL_REPLACE_HPP_INCLUDED

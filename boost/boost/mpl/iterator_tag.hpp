
#ifndef BOOST_MPL_ITERATOR_TAG_HPP_INCLUDED
#define BOOST_MPL_ITERATOR_TAG_HPP_INCLUDED

// Copyright (c) Aleksey Gurtovoy 2000-2004
//
// Use, modification and distribution are subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy 
// at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/integral_c.hpp>

namespace boost { namespace mpl {

enum iter_cat_ { fw_iter_, bi_iter_, ra_iter_ };

typedef integral_c<iter_cat_,fw_iter_> forward_iterator_tag;
typedef integral_c<iter_cat_,bi_iter_> bidirectional_iterator_tag;
typedef integral_c<iter_cat_,ra_iter_> random_access_iterator_tag;

}}

#endif // BOOST_MPL_ITERATOR_TAG_HPP_INCLUDED

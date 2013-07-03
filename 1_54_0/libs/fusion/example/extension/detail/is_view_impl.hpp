/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_VIEW_IMPL_200604227_2150)
#define BOOST_FUSION_IS_VIEW_IMPL_200604227_2150

#include <boost/mpl/bool.hpp>

namespace example
{
  struct example_sequence_tag;
}

namespace boost { namespace fusion 
{
  namespace extension
  {
    template<typename Tag>
    struct is_view_impl;

    template<>
    struct is_view_impl<example::example_sequence_tag>
      : boost::mpl::false_
    {};
  }
}}

#endif

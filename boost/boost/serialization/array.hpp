#ifndef BOOST_SERIALIZATION_ARRAY_HPP
#define BOOST_SERIALIZATION_ARRAY_HPP

// (C) Copyright 2005 Matthias Troyer and Dave Abrahams
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/bool.hpp>

namespace boost { namespace serialization {


// When passed an archive pointer and a data pointer, returns a tag
// indicating whether optimization should be applied.

inline mpl::false_ optimize_array(...)
{
    return mpl::false_();
}

} } // end namespace boost::serialization

#endif //BOOST_SERIALIZATION_ARRAY_HPP

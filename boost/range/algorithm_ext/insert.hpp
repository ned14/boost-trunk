// Boost.Range library
//
//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_EXT_INSERT_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_EXT_INSERT_HPP_INCLUDED

#include <boost/range/config.hpp>
#include <boost/range/difference_type.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/assert.hpp>

namespace boost
{
	template< class Container, class Range >
	inline void insert( Container& on, 
						BOOST_DEDUCED_TYPENAME Container::iterator before, 
						const Range& from )
	{
		BOOST_ASSERT( (void*)&on != (void*)&from && 
					  "cannot copy from a container to itself" );
		on.insert( before, boost::begin(from), boost::end(from) );
	}
}

#endif // include guard

//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_ROTATE_COPY_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_ROTATE_COPY_HPP_INCLUDED

#include <boost/concept_check.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/iterator.hpp>
#include <algorithm>

namespace boost
{
    /// \brief template function rotate
    ///
    /// range-based version of the rotate std algorithm
    ///
    /// \pre Rng meets the requirements for a Forward range
    template<typename ForwardRange, typename OutputIterator>
    inline OutputIterator rotate_copy(
        const ForwardRange&                                 rng,
        typename range_iterator<const ForwardRange>::type   middle,
        OutputIterator                                      target
        )
    {
        BOOST_CONCEPT_ASSERT((ForwardRangeConcept<ForwardRange>));
        return std::rotate_copy(boost::begin(rng), middle, boost::end(rng), target);
    }
}

#endif // include guard

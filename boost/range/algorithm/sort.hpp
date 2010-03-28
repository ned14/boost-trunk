//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_SORT_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_SORT_HPP_INCLUDED

#include <boost/concept_check.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/concepts.hpp>
#include <algorithm>

namespace boost
{
    /// \brief template function sort
    ///
    /// range-based version of the sort std algorithm
    ///
    /// \pre RandomAccessRange is a model of the RandomAccessRangeConcept
    /// \pre BinaryPredicate is a model of the BinaryPredicateConcept
    template<class RandomAccessRange>
    inline RandomAccessRange& sort(RandomAccessRange& rng)
    {
        boost::function_requires< RandomAccessRangeConcept<RandomAccessRange> >();
         std::sort(boost::begin(rng), boost::end(rng));

         return rng;
    }

    /// \overload
    template<class RandomAccessRange>
    inline const RandomAccessRange& sort(const RandomAccessRange& rng)
    {
        boost::function_requires< RandomAccessRangeConcept<RandomAccessRange> >();
        std::sort(boost::begin(rng),boost::end(rng));
        return rng;
    }

    /// \overload
    template<class RandomAccessRange, class BinaryPredicate>
    inline RandomAccessRange& sort(RandomAccessRange& rng, BinaryPredicate pred)
    {
        boost::function_requires< RandomAccessRangeConcept<RandomAccessRange> >();
        std::sort(boost::begin(rng), boost::end(rng), pred);
        return rng;
	}

    /// \overload
    template<class RandomAccessRange, class BinaryPredicate>
    inline const RandomAccessRange& sort(const RandomAccessRange& rng, BinaryPredicate pred)
    {
        boost::function_requires< RandomAccessRangeConcept<RandomAccessRange> >();
        std::sort(boost::begin(rng), boost::end(rng), pred);
        return rng;
    }
}

#endif // include guard

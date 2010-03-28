//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_PARTIAL_SORT_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_PARTIAL_SORT_HPP_INCLUDED

#include <boost/concept_check.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/concepts.hpp>
#include <algorithm>

namespace boost
{
    /// \brief template function partial_sort
    ///
    /// range-based version of the partial_sort std algorithm
    ///
    /// \pre RandomAccessRange is a model of the RandomAccessRangeConcept
    /// \pre BinaryPredicate is a model of the BinaryPredicateConcept
    template<class RandomAccessRange>
    inline void partial_sort(RandomAccessRange& rng,
        BOOST_DEDUCED_TYPENAME range_iterator<RandomAccessRange>::type middle)
    {
        boost::function_requires< RandomAccessRangeConcept<RandomAccessRange> >();
        std::partial_sort(boost::begin(rng), middle, boost::end(rng));
    }

    /// \overload
    template<class RandomAccessRange>
    inline void partial_sort(const RandomAccessRange& rng,
        BOOST_DEDUCED_TYPENAME range_iterator<const RandomAccessRange>::type middle)
    {
        boost::function_requires< RandomAccessRangeConcept<RandomAccessRange> >();
        std::partial_sort(boost::begin(rng), middle, boost::end(rng));
    }

    /// \overload
    template<class RandomAccessRange, class BinaryPredicate>
    inline void partial_sort(RandomAccessRange& rng,
        BOOST_DEDUCED_TYPENAME range_iterator<RandomAccessRange>::type middle,
        BinaryPredicate sort_pred)
    {
        boost::function_requires< RandomAccessRangeConcept<RandomAccessRange> >();
        std::partial_sort(boost::begin(rng), middle, boost::end(rng),
                            sort_pred);
    }

    /// \overload
    template<class RandomAccessRange, class BinaryPredicate>
    inline void partial_sort(const RandomAccessRange& rng,
        BOOST_DEDUCED_TYPENAME range_iterator<const RandomAccessRange>::type middle,
        BinaryPredicate sort_pred)
    {
        boost::function_requires< RandomAccessRangeConcept<RandomAccessRange> >();
        std::partial_sort(boost::begin(rng), middle, boost::end(rng), sort_pred);
    }
}

#endif // include guard

//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_EXT_IS_SORTED_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_EXT_IS_SORTED_HPP_INCLUDED

#include <boost/concept_check.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/value_type.hpp>
#include <algorithm>

namespace boost
{
    namespace range_detail
    {
        template<typename ForwardIterator>
        inline bool is_sorted(ForwardIterator first, ForwardIterator last)
        {
            for (ForwardIterator next = first; first != last && ++next != last; ++first)
                if (*next < *first)
                    return false;
            return true;
        }

        template<typename ForwardIterator, typename BinaryPredicate>
        inline bool is_sorted(ForwardIterator first, ForwardIterator last, BinaryPredicate pred)
        {
            for (ForwardIterator next = first; first != last && ++next != last; ++first)
                if (pred(*next, *first))
                    return false;
            return true;
        }
    }

    /// \brief template function count
    ///
    /// range-based version of the count std algorithm
    ///
    /// \pre SinglePassRange is a model of the SinglePassRangeConcept
    template<typename SinglePassRange>
    inline bool is_sorted(const SinglePassRange& rng)
    {
        BOOST_RANGE_CONCEPT_ASSERT((SinglePassRangeConcept<SinglePassRange>));
        BOOST_RANGE_CONCEPT_ASSERT((LessThanComparableConcept<typename range_value<SinglePassRange>::type>));
        return range_detail::is_sorted(boost::begin(rng), boost::end(rng));
    }

    /// \overload
    template<typename SinglePassRange, typename BinaryPredicate>
    inline bool is_sorted(const SinglePassRange& rng, BinaryPredicate pred)
    {
        BOOST_RANGE_CONCEPT_ASSERT((SinglePassRangeConcept<SinglePassRange>));
        BOOST_RANGE_CONCEPT_ASSERT((BinaryPredicateConcept<BinaryPredicate, typename range_value<SinglePassRange>::type, typename range_value<SinglePassRange>::type>));
        return range_detail::is_sorted(boost::begin(rng), boost::end(rng), pred);
    }
}

#endif // include guard

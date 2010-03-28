// Boost.Range library concept checks
//
//  Copyright Neil Groves 2009. Use, modification and distribution
//  are subject to the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  Copyright Daniel Walker 2006. Use, modification and distribution
//  are subject to the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_CONCEPTS_HPP
#define BOOST_RANGE_CONCEPTS_HPP

#include <boost/concept_check.hpp>
#include <boost/iterator/iterator_concepts.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/value_type.hpp>
#include <boost/range/detail/misc_concept.hpp>

/*!
 * \file
 * \brief Concept checks for the Boost Range library.
 *
 * The structures in this file may be used in conjunction with the
 * Boost Concept Check library to insure that the type of a function
 * parameter is compatible with a range concept. If not, a meaningful
 * compile time error is generated. Checks are provided for the range
 * concepts related to iterator traversal categories. For example, the
 * following line checks that the type T models the ForwardRange
 * concept.
 *
 * \code
 * BOOST_CONCEPT_ASSERT((ForwardRangeConcept<T>));
 * \endcode
 *
 * A different concept check is required to ensure writeable value
 * access. For example to check for a ForwardRange that can be written
 * to, the following code is required.
 *
 * \code
 * BOOST_CONCEPT_ASSERT((WriteableForwardRangeConcept<T>));
 * \endcode
 *
 * \see http://www.boost.org/libs/range/doc/range.html for details
 * about range concepts.
 * \see http://www.boost.org/libs/iterator/doc/iterator_concepts.html
 * for details about iterator concepts.
 * \see http://www.boost.org/libs/concept_check/concept_check.htm for
 * details about concept checks.
 */

namespace boost {

    namespace range_detail {

        // Rationale for the inclusion of redefined iterator concept
        // classes:
        //
        // The Range algorithms often do not require that the iterators are
        // Assignable, but the correct standard conformant iterators
        // do require the iterators to be a model of the Assignable concept.
        // Iterators that contains a functor that is not assignable therefore
        // are not correct models of the standard iterator concepts,
        // despite being adequate for most algorithms. An example of this
        // use case is the combination of the boost::adaptors::filtered
        // class with a boost::lambda::bind generated functor.
        // Ultimately modeling the range concepts using composition
        // with the Boost.Iterator concepts would render the library
        // incompatible with many common Boost.Lambda expressions.
        template<typename Iterator>
        struct IncrementableIteratorConcept : CopyConstructible<Iterator>
        {
            typedef typename iterator_traversal<Iterator>::type traversal_category;

            BOOST_CONCEPT_ASSERT((
                Convertible<
                    traversal_category,
                    incrementable_traversal_tag
                >));

            BOOST_CONCEPT_USAGE(IncrementableIteratorConcept)
            {
                ++i;
                (void)i++;
            }
        private:
            Iterator i;
        };

        template<typename Iterator>
        struct SinglePassIteratorConcept
            : IncrementableIteratorConcept<Iterator>
            , EqualityComparable<Iterator>
        {
            BOOST_CONCEPT_ASSERT((
                Convertible<
                    typename SinglePassIteratorConcept::traversal_category,
                    single_pass_traversal_tag
                >));
        };

        template<typename Iterator>
        struct ForwardIteratorConcept
            : SinglePassIteratorConcept<Iterator>
            , DefaultConstructible<Iterator>
        {
            typedef typename boost::detail::iterator_traits<Iterator>::difference_type difference_type;

            BOOST_MPL_ASSERT((is_integral<difference_type>));
            BOOST_MPL_ASSERT_RELATION(std::numeric_limits<difference_type>::is_signed, ==, true);

            BOOST_CONCEPT_ASSERT((
                Convertible<
                    typename ForwardIteratorConcept::traversal_category,
                    forward_traversal_tag
                >));
         };

         template<typename Iterator>
         struct BidirectionalIteratorConcept
             : ForwardIteratorConcept<Iterator>
         {
             BOOST_CONCEPT_ASSERT((
                 Convertible<
                     typename BidirectionalIteratorConcept::traversal_category,
                     bidirectional_traversal_tag
                 >));

             BOOST_CONCEPT_USAGE(BidirectionalIteratorConcept)
             {
                 --i;
                 (void)i--;
             }
         private:
             Iterator i;
         };

         template<typename Iterator>
         struct RandomAccessIteratorConcept
             : BidirectionalIteratorConcept<Iterator>
         {
             BOOST_CONCEPT_ASSERT((
                 Convertible<
                     typename RandomAccessIteratorConcept::traversal_category,
                     random_access_traversal_tag
                 >));

             BOOST_CONCEPT_USAGE(RandomAccessIteratorConcept)
             {
                 i += n;
                 i = i + n;
                 i = n + i;
                 i -= n;
                 i = i - n;
                 n = i - j;
             }
         private:
             typename RandomAccessIteratorConcept::difference_type n;
             Iterator i;
             Iterator j;
         };

    } // namespace range_detail

    //! Check if a type T models the SinglePassRange range concept.
    template<typename T>
    struct SinglePassRangeConcept
    {
         typedef typename range_iterator<T const>::type  const_iterator;
         typedef typename range_iterator<T>::type        iterator;

         BOOST_CONCEPT_ASSERT((range_detail::SinglePassIteratorConcept<iterator>));
         BOOST_CONCEPT_ASSERT((range_detail::SinglePassIteratorConcept<const_iterator>));

         BOOST_CONCEPT_USAGE(SinglePassRangeConcept)
         {
            // This has been modified from assigning to this->i
            // (where i was a member variable) to improve
            // compatibility with Boost.Lambda
            iterator i1 = boost::begin(*m_range);
            iterator i2 = boost::end(*m_range);

            ignore_unused_variable_warning(i1);
            ignore_unused_variable_warning(i2);

            const_constraints(*m_range);
        }

    private:
        void const_constraints(const T& const_range)
        {
            const_iterator ci1 = boost::begin(const_range);
            const_iterator ci2 = boost::end(const_range);

            ignore_unused_variable_warning(ci1);
            ignore_unused_variable_warning(ci2);
        }

       // Rationale:
       // The type of m_range is T* rather than T because it allows
       // T to be an abstract class. The other obvious alternative of
       // T& produces a warning on some compilers.
       T* m_range;
    };

    //! Check if a type T models the ForwardRange range concept.
    template<typename T>
    struct ForwardRangeConcept : SinglePassRangeConcept<T>
    {
        BOOST_CONCEPT_ASSERT((range_detail::ForwardIteratorConcept<typename ForwardRangeConcept::iterator>));
        BOOST_CONCEPT_ASSERT((range_detail::ForwardIteratorConcept<typename ForwardRangeConcept::const_iterator>));
    };

    template<typename Range>
    struct WriteableRangeConcept
    {
        typedef typename range_iterator<Range>::type iterator;

        BOOST_CONCEPT_USAGE(WriteableRangeConcept)
        {
            *i = v;
        }
    private:
        iterator i;
        typename range_value<Range>::type v;
    };

    //! Check if a type T models the WriteableForwardRange range concept.
    template<typename T>
    struct WriteableForwardRangeConcept
        : ForwardRangeConcept<T>
        , WriteableRangeConcept<T>
    {
    };

    //! Check if a type T models the BidirectionalRange range concept.
    template<typename T>
    struct BidirectionalRangeConcept : ForwardRangeConcept<T>
    {
        BOOST_CONCEPT_ASSERT((BidirectionalIteratorConcept<typename BidirectionalRangeConcept::iterator>));
	BOOST_CONCEPT_ASSERT((BidirectionalIteratorConcept<typename BidirectionalRangeConcept::const_iterator>));
    };

    //! Check if a type T models the WriteableBidirectionalRange range concept.
    template<typename T>
    struct WriteableBidirectionalRangeConcept
        : BidirectionalRangeConcept<T>
        , WriteableRangeConcept<T>
    {
    };

    //! Check if a type T models the RandomAccessRange range concept.
    template<typename T>
    struct RandomAccessRangeConcept : BidirectionalRangeConcept<T>
    {
        BOOST_CONCEPT_ASSERT((RandomAccessIteratorConcept<typename RandomAccessRangeConcept::iterator>));
        BOOST_CONCEPT_ASSERT((RandomAccessIteratorConcept<typename RandomAccessRangeConcept::const_iterator>));
    };

    //! Check if a type T models the WriteableRandomAccessRange range concept.
    template<typename T>
    struct WriteableRandomAccessRangeConcept
        : RandomAccessRangeConcept<T>
        , WriteableRangeConcept<T>
    {
    };

} // namespace boost

#endif // BOOST_RANGE_CONCEPTS_HPP

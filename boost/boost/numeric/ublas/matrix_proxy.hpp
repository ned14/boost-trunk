//
//  Copyright (c) 2000-2002
//  Joerg Walter, Mathias Koch
//
//  Permission to use, copy, modify, distribute and sell this software
//  and its documentation for any purpose is hereby granted without fee,
//  provided that the above copyright notice appear in all copies and
//  that both that copyright notice and this permission notice appear
//  in supporting documentation.  The authors make no representations
//  about the suitability of this software for any purpose.
//  It is provided "as is" without express or implied warranty.
//
//  The authors gratefully acknowledge the support of
//  GeNeSys mbH & Co. KG in producing this work.
//

#ifndef BOOST_UBLAS_MATRIX_PROXY_H
#define BOOST_UBLAS_MATRIX_PROXY_H

#include <boost/numeric/ublas/config.hpp>
#include <boost/numeric/ublas/vector_expression.hpp>
#include <boost/numeric/ublas/matrix_expression.hpp>

// Iterators based on ideas of Jeremy Siek

namespace boost { namespace numeric { namespace ublas {

    // Matrix based row vector class
    template<class M>
    class matrix_row:
        public vector_expression<matrix_row<M> > {
    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        BOOST_UBLAS_USING vector_expression<matrix_row<M> >::operator ();
#endif
        typedef const M const_matrix_type;
        typedef M matrix_type;
        typedef typename M::size_type size_type;
        typedef typename M::difference_type difference_type;
        typedef typename M::value_type value_type;
        typedef typename M::const_reference const_reference;
        typedef typename M::reference reference;
        typedef typename M::const_pointer const_pointer;
        typedef typename M::pointer pointer;
#ifdef BOOST_UBLAS_ET_CLOSURE_REFERENCE
        typedef const vector_const_reference<const matrix_row<matrix_type> > const_closure_type;
        typedef vector_reference<matrix_row<matrix_type> > closure_type;
#endif
#ifdef BOOST_UBLAS_ET_CLOSURE_VALUE
        typedef const matrix_row<matrix_type> const_closure_type;
        typedef matrix_row<matrix_type> closure_type;
#endif
        typedef typename M::const_iterator2 const_iterator_type;
        typedef typename M::iterator2 iterator_type;
        typedef typename storage_restrict_traits<typename M::storage_category,
                                                 dense_proxy_tag>::storage_category storage_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        matrix_row ():
            data_ (nil_), i_ () {}
        BOOST_UBLAS_INLINE
        matrix_row (matrix_type &data, size_type i):
            data_ (data), i_ (i) {}

        // Accessors
        BOOST_UBLAS_INLINE
        size_type size () const {
            return data_.size2 ();
        }
        BOOST_UBLAS_INLINE
        const_matrix_type &data () const {
            return data_;
        }
        BOOST_UBLAS_INLINE
        matrix_type &data () {
            return data_;
        }

#ifdef BOOST_UBLAS_DEPRECATED
        // Resetting
        BOOST_UBLAS_INLINE
        void reset (matrix_type &data) {
            // data_ = data;
            data_.reset (data);
        }
        BOOST_UBLAS_INLINE
        void reset (matrix_type &data, size_type i) {
            // data_ = data;
            data_.reset (data);
            i_ = i;
        }
#endif

        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type j) const {
            return data () (i_, j);
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type j) {
            return data () (i_, j);
        }

        BOOST_UBLAS_INLINE
        const_reference operator [] (size_type j) const {
            return (*this) (j);
        }
        BOOST_UBLAS_INLINE
        reference operator [] (size_type j) {
            return (*this) (j);
        }

        // Assignment
        BOOST_UBLAS_INLINE
        matrix_row &operator = (const matrix_row &mr) {
            // FIXME: the rows could be differently sized.
            // std::copy (mr.begin (), mr.end (), begin ());
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vector<value_type> (mr));
            return *this;
        }
        BOOST_UBLAS_INLINE
        matrix_row &assign_temporary (matrix_row &mr) {
            // FIXME: this is suboptimal.
            // return *this = mr;
            vector_assign<scalar_assign<value_type, value_type> > () (*this, mr);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_row &operator = (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vector<value_type> (ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_row &assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_row &operator += (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vector<value_type> (*this + ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_row &plus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_plus_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_row &operator -= (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vector<value_type> (*this - ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_row &minus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_minus_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        matrix_row &operator *= (const AT &at) {
            vector_assign_scalar<scalar_multiplies_assign<value_type, AT> > () (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        matrix_row &operator /= (const AT &at) {
            vector_assign_scalar<scalar_divides_assign<value_type, AT> > () (*this, at);
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (matrix_row &mr) {
            // Too unusual semantic.
            // BOOST_UBLAS_CHECK (this != &mr, external_logic ());
            if (this != &mr) {
                BOOST_UBLAS_CHECK (size () == mr.size (), bad_size ());
                std::swap_ranges (begin (), end (), mr.begin ());
            }
        }
#ifdef BOOST_UBLAS_FRIEND_FUNCTION
        BOOST_UBLAS_INLINE
        friend void swap (matrix_row &mr1, matrix_row &mr2) {
            mr1.swap (mr2);
        }
#endif

#if defined (BOOST_UBLAS_USE_CANONICAL_ITERATOR) || defined (BOOST_UBLAS_USE_INDEXED_ITERATOR)
        typedef indexed_iterator<matrix_row<matrix_type>,
                                 BOOST_UBLAS_TYPENAME matrix_type::iterator2::iterator_category> iterator;
        typedef indexed_const_iterator<matrix_row<matrix_type>,
                                       BOOST_UBLAS_TYPENAME matrix_type::const_iterator2::iterator_category> const_iterator;
#else
        class const_iterator;
        class iterator;
#endif

        // Element lookup
        BOOST_UBLAS_INLINE
        const_iterator find_first (size_type j) const {
            const_iterator_type it2 (data ().find_first2 (1, i_, j));
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return const_iterator (*this, it2.index ());
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return const_iterator (*this, it2.index2 ());
#else
            return const_iterator (*this, it2);
#endif
#endif
        }
        BOOST_UBLAS_INLINE
        iterator find_first (size_type j) {
            iterator_type it2 (data ().find_first2 (1, i_, j));
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return iterator (*this, it2.index ());
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return iterator (*this, it2.index2 ());
#else
            return iterator (*this, it2);
#endif
#endif
        }
        BOOST_UBLAS_INLINE
        const_iterator find_last (size_type j) const {
            const_iterator_type it2 (data ().find_last2 (1, i_, j));
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return const_iterator (*this, it2.index ());
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return const_iterator (*this, it2.index2 ());
#else
            return const_iterator (*this, it2);
#endif
#endif
        }
        BOOST_UBLAS_INLINE
        iterator find_last (size_type j) {
            iterator_type it2 (data ().find_last2 (1, i_, j));
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return iterator (*this, it2.index ());
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return iterator (*this, it2.index2 ());
#else
            return iterator (*this, it2);
#endif
#endif
        }

        // Iterators simply are pointers.

#if ! defined (BOOST_UBLAS_USE_CANONICAL_ITERATOR) && ! defined (BOOST_UBLAS_USE_INDEXED_ITERATOR)
        class const_iterator:
            public container_const_reference<matrix_row>,
#ifdef BOOST_UBLAS_USE_ITERATOR_BASE_TRAITS
            public iterator_base_traits<typename M::const_iterator2::iterator_category>::template
                        iterator_base<const_iterator, value_type>::type {
#else
            public random_access_iterator_base<typename M::const_iterator2::iterator_category,
                                               const_iterator, value_type> {
#endif
        public:
            typedef typename M::const_iterator2::iterator_category iterator_category;
            typedef typename M::const_iterator2::difference_type difference_type;
            typedef typename M::const_iterator2::value_type value_type;
            typedef typename M::const_iterator2::reference reference;
            typedef typename M::const_iterator2::pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator ():
                container_const_reference<matrix_row> (), it_ () {}
            BOOST_UBLAS_INLINE
            const_iterator (const matrix_row &mr, const const_iterator_type &it):
                container_const_reference<matrix_row> (mr), it_ (it) {}
#ifndef BOOST_UBLAS_QUALIFIED_TYPENAME
            BOOST_UBLAS_INLINE
            const_iterator (const iterator &it):
                container_const_reference<matrix_row> (it ()), it_ (it.it_) {}
#else
            BOOST_UBLAS_INLINE
            const_iterator (const typename matrix_row::iterator &it):
                container_const_reference<matrix_row> (it ()), it_ (it.it_) {}
#endif

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator &operator ++ () {
                ++ it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -- () {
                -- it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator += (difference_type n) {
                it_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -= (difference_type n) {
                it_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const const_iterator &it) const {
                return it_ - it.it_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
                return *it_;
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                return it_.index2 ();
            }

            // Assignment
            BOOST_UBLAS_INLINE
            const_iterator &operator = (const const_iterator &it) {
                container_const_reference<matrix_row>::assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ == it.it_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const const_iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ < it.it_;
            }

        private:
            const_iterator_type it_;
        };
#endif

        BOOST_UBLAS_INLINE
        const_iterator begin () const {
            return find_first (0);
        }
        BOOST_UBLAS_INLINE
        const_iterator end () const {
            return find_last (size ());
        }

#if ! defined (BOOST_UBLAS_USE_CANONICAL_ITERATOR) && ! defined (BOOST_UBLAS_USE_INDEXED_ITERATOR)
        class iterator:
            public container_reference<matrix_row>,
#ifdef BOOST_UBLAS_USE_ITERATOR_BASE_TRAITS
            public iterator_base_traits<typename M::iterator2::iterator_category>::template
                        iterator_base<iterator, value_type>::type {
#else
            public random_access_iterator_base<typename M::iterator2::iterator_category,
                                               iterator, value_type> {
#endif                                               
        public:
            typedef typename M::iterator2::iterator_category iterator_category;
            typedef typename M::iterator2::difference_type difference_type;
            typedef typename M::iterator2::value_type value_type;
            typedef typename M::iterator2::reference reference;
            typedef typename M::iterator2::pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator ():
                container_reference<matrix_row> (), it_ () {}
            BOOST_UBLAS_INLINE
            iterator (matrix_row &mr, const iterator_type &it):
                container_reference<matrix_row> (mr), it_ (it) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            iterator &operator ++ () {
                ++ it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator &operator -- () {
                -- it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator &operator += (difference_type n) {
                it_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator &operator -= (difference_type n) {
                it_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const iterator &it) const {
                return it_ - it.it_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
                return *it_;
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                return it_.index2 ();
            }

            // Assignment 
            BOOST_UBLAS_INLINE
            iterator &operator = (const iterator &it) {
                container_reference<matrix_row>::assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ == it.it_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ < it.it_;
            }

        private:
            iterator_type it_;

            friend class const_iterator;
        };
#endif

        BOOST_UBLAS_INLINE
        iterator begin () {
            return find_first (0);
        }
        BOOST_UBLAS_INLINE
        iterator end () {
            return find_last (size ());
        }

        // Reverse iterator

#ifdef BOOST_MSVC_STD_ITERATOR
        typedef reverse_iterator_base<const_iterator, value_type, const_reference> const_reverse_iterator;
#else
        typedef reverse_iterator_base<const_iterator> const_reverse_iterator;
#endif

        BOOST_UBLAS_INLINE
        const_reverse_iterator rbegin () const {
            return const_reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator rend () const {
            return const_reverse_iterator (begin ());
        }

#ifdef BOOST_MSVC_STD_ITERATOR
        typedef reverse_iterator_base<iterator, value_type, reference> reverse_iterator;
#else
        typedef reverse_iterator_base<iterator> reverse_iterator;
#endif

        BOOST_UBLAS_INLINE
        reverse_iterator rbegin () {
            return reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator rend () {
            return reverse_iterator (begin ());
        }

    private:
        matrix_type &data_;
        size_type i_;
        static matrix_type nil_;
    };

    template<class M>
    typename matrix_row<M>::matrix_type matrix_row<M>::nil_;

    // Projections
    template<class M>
    BOOST_UBLAS_INLINE
    matrix_row<M> row (M &data, std::size_t i) {
        return matrix_row<M> (data, i);
    }
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
    template<class M>
    BOOST_UBLAS_INLINE
    const matrix_row<const M> row (const M &data, std::size_t i) {
        return matrix_row<const M> (data, i);
    }
#endif

    // Matrix row iterator
    template<class M, class I>
    class matrix_row_iterator:
        public container_reference<M>,
        public random_access_iterator_base<I,
                                           matrix_row_iterator<M, I>,
                                           matrix_row<M>,
                                           typename M::difference_type> {
    public:
        typedef M matrix_type;
        typedef I iterator_category;
        typedef typename matrix_type::size_type size_type;
        typedef typename matrix_type::difference_type difference_type;
        typedef matrix_row<matrix_type> value_type;
        typedef matrix_row<matrix_type> reference;
        typedef value_type *pointer;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        matrix_row_iterator ():
            container_reference<matrix_type> (), it_ () {}
        BOOST_UBLAS_INLINE
        matrix_row_iterator (matrix_type &m, size_type it):
            container_reference<matrix_type> (m), it_ (it) {}

        // Arithmetic
        BOOST_UBLAS_INLINE
        matrix_row_iterator &operator ++ () {
            ++ it_;
            return *this;
        }
        BOOST_UBLAS_INLINE
        matrix_row_iterator &operator -- () {
            -- it_;
            return *this;
        }
        BOOST_UBLAS_INLINE
        matrix_row_iterator &operator += (difference_type n) {
            it_ += n;
            return *this;
        }
        BOOST_UBLAS_INLINE
        matrix_row_iterator &operator -= (difference_type n) {
            it_ -= n;
            return *this;
        }
        BOOST_UBLAS_INLINE
        difference_type operator - (const matrix_row_iterator &it) const {
            return it_ - it.it_;
        }

        // Dereference
        BOOST_UBLAS_INLINE
        reference operator * () const {
            BOOST_UBLAS_CHECK (index () < (*this) ().size1 (), bad_index ());
            return row ((*this) (), it_);
        }

        // Index
        BOOST_UBLAS_INLINE
        size_type index () const {
            return it_;
        }

        // Assignment 
        BOOST_UBLAS_INLINE
        matrix_row_iterator &operator = (const matrix_row_iterator &it) {
            assign (&it ());
            it_ = it.it_;
            return *this;
        }

        // Comparison
        BOOST_UBLAS_INLINE
        bool operator == (const matrix_row_iterator &it) const {
            BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
            return it_ == it.it_;
        }
        BOOST_UBLAS_INLINE
        bool operator < (const matrix_row_iterator &it) const {
            BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
            return it_ < it.it_;
        }

    private:
        size_type it_;
    };

#ifdef BOOST_MSVC_STD_ITERATOR
    template<class M, class I>
    BOOST_UBLAS_INLINE
    matrix_row_iterator<M, I> operator ++ (const matrix_row_iterator<M, I> &it, int) {
        matrix_row_iterator<M, I> tmp (it);
        ++ tmp;
        return tmp;
    }
    template<class M, class I>
    BOOST_UBLAS_INLINE
    matrix_row_iterator<M, I> operator -- (const matrix_row_iterator<M, I> &it, int) {
        matrix_row_iterator<M, I> tmp (it);
        -- tmp;
        return tmp;
    }
    template<class M, class I>
    BOOST_UBLAS_INLINE
    matrix_row_iterator<M, I> operator + (const matrix_row_iterator<M, I> &it, std::ptrdiff_t n) {
        matrix_row_iterator<M, I> tmp (it);
        return tmp += n;
    }
    template<class M, class I>
    BOOST_UBLAS_INLINE
    matrix_row_iterator<M, I> operator - (const matrix_row_iterator<M, I> &it, std::ptrdiff_t n) {
        matrix_row_iterator<M, I> tmp (it);
        return tmp -= n;
    }
#endif

    template<class M, class I>
    class matrix_row_const_iterator:
        public container_const_reference<M>,
        public random_access_iterator_base<I,
                                           matrix_row_const_iterator<M, I>,
                                           matrix_row<M>,
                                           typename M::difference_type> {
    public:
        typedef M matrix_type;
        typedef I iterator_category;
        typedef typename matrix_type::size_type size_type;
        typedef typename matrix_type::difference_type difference_type;
        typedef matrix_row<matrix_type> value_type;
        typedef const matrix_row<const matrix_type> const_reference;
        typedef matrix_row<matrix_type> reference;
        typedef value_type *pointer;
        typedef matrix_row_iterator<matrix_type, iterator_category> iterator_type;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        matrix_row_const_iterator ():
            container_const_reference<matrix_type> (), it_ () {}
        BOOST_UBLAS_INLINE
        matrix_row_const_iterator (const matrix_type &c, size_type it):
            container_const_reference<matrix_type> (c), it_ (it) {}
        BOOST_UBLAS_INLINE
        matrix_row_const_iterator (const iterator_type &it):
            container_const_reference<matrix_type> (it ()), it_ (it.index ()) {}

        // Arithmetic
        BOOST_UBLAS_INLINE
        matrix_row_const_iterator &operator ++ () {
            ++ it_;
            return *this;
        }
        BOOST_UBLAS_INLINE
        matrix_row_const_iterator &operator -- () {
            -- it_;
            return *this;
        }
        BOOST_UBLAS_INLINE
        matrix_row_const_iterator &operator += (difference_type n) {
            it_ += n;
            return *this;
        }
        BOOST_UBLAS_INLINE
        matrix_row_const_iterator &operator -= (difference_type n) {
            it_ -= n;
            return *this;
        }
        BOOST_UBLAS_INLINE
        difference_type operator - (const matrix_row_const_iterator &it) const {
            return it_ - it.it_;
        }

        // Dereference
        BOOST_UBLAS_INLINE
        reference operator * () const {
            BOOST_UBLAS_CHECK (index () < (*this) ().size1 (), bad_index ());
            return row ((*this) (), it_);
        }

        // Index
        BOOST_UBLAS_INLINE
        size_type index () const {
            return it_;
        }

        // Assignment 
        BOOST_UBLAS_INLINE
        matrix_row_const_iterator &operator = (const matrix_row_const_iterator &it) {
            assign (&it ());
            it_ = it.it_;
            return *this;
        }

        // Comparison
        BOOST_UBLAS_INLINE
        bool operator == (const matrix_row_const_iterator &it) const {
            BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
            return it_ == it.it_;
        }
        BOOST_UBLAS_INLINE
        bool operator < (const matrix_row_const_iterator &it) const {
            BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
            return it_ < it.it_;
        }

    private:
        size_type it_;

        friend class matrix_row_iterator<matrix_type, iterator_category>;
    };

#ifdef BOOST_MSVC_STD_ITERATOR
    template<class M, class I>
    BOOST_UBLAS_INLINE
    matrix_row_const_iterator<M, I> operator ++ (const matrix_row_const_iterator<M, I> &it, int) {
        matrix_row_const_iterator<M, I> tmp (it);
        ++ tmp;
        return tmp;
    }
    template<class M, class I>
    BOOST_UBLAS_INLINE
    matrix_row_const_iterator<M, I> operator -- (const matrix_row_const_iterator<M, I> &it, int) {
        matrix_row_const_iterator<M, I> tmp (it);
        -- tmp;
        return tmp;
    }
    template<class M, class I>
    BOOST_UBLAS_INLINE
    matrix_row_const_iterator<M, I> operator + (const matrix_row_const_iterator<M, I> &it, std::ptrdiff_t n) {
        matrix_row_const_iterator<M, I> tmp (it);
        return tmp += n;
    }
    template<class M, class I>
    BOOST_UBLAS_INLINE
    matrix_row_const_iterator<M, I> operator - (const matrix_row_const_iterator<M, I> &it, std::ptrdiff_t n) {
        matrix_row_const_iterator<M, I> tmp (it);
        return tmp -= n;
    }
#endif

    // Matrix based column vector class
    template<class M>
    class matrix_column:
        public vector_expression<matrix_column<M> > {
    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        BOOST_UBLAS_USING vector_expression<matrix_column<M> >::operator ();
#endif
        typedef const M const_matrix_type;
        typedef M matrix_type;
        typedef typename M::size_type size_type;
        typedef typename M::difference_type difference_type;
        typedef typename M::value_type value_type;
        typedef typename M::const_reference const_reference;
        typedef typename M::reference reference;
        typedef typename M::const_pointer const_pointer;
        typedef typename M::pointer pointer;
#ifdef BOOST_UBLAS_ET_CLOSURE_REFERENCE
        typedef const vector_const_reference<const matrix_column<matrix_type> > const_closure_type;
        typedef vector_reference<matrix_column<matrix_type> > closure_type;
#endif
#ifdef BOOST_UBLAS_ET_CLOSURE_VALUE
        typedef const matrix_column<matrix_type> const_closure_type;
        typedef matrix_column<matrix_type> closure_type;
#endif
        typedef typename M::const_iterator1 const_iterator_type;
        typedef typename M::iterator1 iterator_type;
        typedef typename storage_restrict_traits<typename M::storage_category,
                                                 dense_proxy_tag>::storage_category storage_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        matrix_column (): 
            data_ (nil_), j_ () {}
        BOOST_UBLAS_INLINE
        matrix_column (matrix_type &data, size_type j): 
            data_ (data), j_ (j) {}

        // Accessors
        BOOST_UBLAS_INLINE
        size_type size () const { 
            return data_.size1 (); 
        }
        BOOST_UBLAS_INLINE
        const_matrix_type &data () const {
            return data_;
        }
        BOOST_UBLAS_INLINE
        matrix_type &data () {
            return data_;
        }

#ifdef BOOST_UBLAS_DEPRECATED
        // Resetting
        BOOST_UBLAS_INLINE
        void reset (matrix_type &data) {
            // data_ = data;
            data_.reset (data);
        }
        BOOST_UBLAS_INLINE
        void reset (matrix_type &data, size_type j) {
            // data_ = data;
            data_.reset (data);
            j_ = j;
        }
#endif

        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i) const {
            return data () (i, j_); 
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i) {
            return data () (i, j_); 
        }

        BOOST_UBLAS_INLINE
        const_reference operator [] (size_type i) const { 
            return (*this) (i); 
        }
        BOOST_UBLAS_INLINE
        reference operator [] (size_type i) { 
            return (*this) (i); 
        }

        // Assignment
        BOOST_UBLAS_INLINE
        matrix_column &operator = (const matrix_column &mc) { 
            // FIXME: the columns could be differently sized.
            // std::copy (mc.begin (), mc.end (), begin ());
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vector<value_type> (mc));
            return *this;
        }
        BOOST_UBLAS_INLINE
        matrix_column &assign_temporary (matrix_column &mc) {
            // FIXME: this is suboptimal.
            // return *this = mc;
            vector_assign<scalar_assign<value_type, value_type> > () (*this, mc);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_column &operator = (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vector<value_type> (ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_column &assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_column &operator += (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vector<value_type> (*this + ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_column &plus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_plus_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_column &operator -= (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vector<value_type> (*this - ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_column &minus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_minus_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        matrix_column &operator *= (const AT &at) {
            vector_assign_scalar<scalar_multiplies_assign<value_type, AT> > () (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        matrix_column &operator /= (const AT &at) {
            vector_assign_scalar<scalar_divides_assign<value_type, AT> > () (*this, at);
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (matrix_column &mc) {
            // Too unusual semantic.
            // BOOST_UBLAS_CHECK (this != &mc, external_logic ());
            if (this != &mc) {
                BOOST_UBLAS_CHECK (size () == mc.size (), bad_size ());
                std::swap_ranges (begin (), end (), mc.begin ());
            }
        }
#ifdef BOOST_UBLAS_FRIEND_FUNCTION
        BOOST_UBLAS_INLINE
        friend void swap (matrix_column &mc1, matrix_column &mc2) {
            mc1.swap (mc2);
        }
#endif

#if defined (BOOST_UBLAS_USE_CANONICAL_ITERATOR) || defined (BOOST_UBLAS_USE_INDEXED_ITERATOR)
        typedef indexed_iterator<matrix_column<matrix_type>,
                                 BOOST_UBLAS_TYPENAME matrix_type::iterator1::iterator_category> iterator;
        typedef indexed_const_iterator<matrix_column<matrix_type>,
                                       BOOST_UBLAS_TYPENAME matrix_type::const_iterator1::iterator_category> const_iterator;
#else
        class const_iterator;
        class iterator;
#endif

        // Element lookup
        BOOST_UBLAS_INLINE
        const_iterator find_first (size_type i) const {
            const_iterator_type it1 (data ().find_first1 (1, i, j_));
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return const_iterator (*this, it1.index ());
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return const_iterator (*this, it1.index1 ());
#else
            return const_iterator (*this, it1);
#endif
#endif
        }
        BOOST_UBLAS_INLINE
        iterator find_first (size_type i) {
            iterator_type it1 (data ().find_first1 (1, i, j_));
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return iterator (*this, it1.index ());
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return iterator (*this, it1.index1 ());
#else
            return iterator (*this, it1);
#endif
#endif
        }
        BOOST_UBLAS_INLINE
        const_iterator find_last (size_type i) const {
            const_iterator_type it1 (data ().find_last1 (1, i, j_));
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return const_iterator (*this, it1.index ());
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return const_iterator (*this, it1.index1 ());
#else
            return const_iterator (*this, it1);
#endif
#endif
        }
        BOOST_UBLAS_INLINE
        iterator find_last (size_type i) {
            iterator_type it1 (data ().find_last1 (1, i, j_));
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return iterator (*this, it1.index ());
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return iterator (*this, it1.index1 ());
#else
            return iterator (*this, it1);
#endif
#endif
        }

        // Iterators simply are pointers.

#if ! defined (BOOST_UBLAS_USE_CANONICAL_ITERATOR) && ! defined (BOOST_UBLAS_USE_INDEXED_ITERATOR)
        class const_iterator:
            public container_const_reference<matrix_column>,
#ifdef BOOST_UBLAS_USE_ITERATOR_BASE_TRAITS
            public iterator_base_traits<typename M::const_iterator1::iterator_category>::template
                        iterator_base<const_iterator, value_type>::type {
#else
            public random_access_iterator_base<typename M::const_iterator1::iterator_category,
                                               const_iterator, value_type> {
#endif                                               
        public:
            typedef typename M::const_iterator1::iterator_category iterator_category;
            typedef typename M::const_iterator1::difference_type difference_type;
            typedef typename M::const_iterator1::value_type value_type;
            typedef typename M::const_iterator1::reference reference;
            typedef typename M::const_iterator1::pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator ():
                container_const_reference<matrix_column> (), it_ () {}
            BOOST_UBLAS_INLINE
            const_iterator (const matrix_column &mc, const const_iterator_type &it):
                container_const_reference<matrix_column> (mc), it_ (it) {}
#ifndef BOOST_UBLAS_QUALIFIED_TYPENAME
            BOOST_UBLAS_INLINE
            const_iterator (const iterator &it):
                container_const_reference<matrix_column> (it ()), it_ (it.it_) {}
#else
            BOOST_UBLAS_INLINE
            const_iterator (const typename matrix_column::iterator &it):
                container_const_reference<matrix_column> (it ()), it_ (it.it_) {}
#endif

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator &operator ++ () {
                ++ it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -- () {
                -- it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator += (difference_type n) {
                it_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -= (difference_type n) {
                it_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const const_iterator &it) const {
                return it_ - it.it_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
                return *it_;
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                return it_.index1 ();
            }

            // Assignment 
            BOOST_UBLAS_INLINE
            const_iterator &operator = (const const_iterator &it) {
                container_const_reference<matrix_column>::assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ == it.it_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const const_iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ < it.it_;
            }

        private:
            const_iterator_type it_;
        };
#endif

        BOOST_UBLAS_INLINE
        const_iterator begin () const {
            return find_first (0);
        }
        BOOST_UBLAS_INLINE
        const_iterator end () const {
            return find_last (size ());
        }

#if ! defined (BOOST_UBLAS_USE_CANONICAL_ITERATOR) && ! defined (BOOST_UBLAS_USE_INDEXED_ITERATOR)
        class iterator:
            public container_reference<matrix_column>,
#ifdef BOOST_UBLAS_USE_ITERATOR_BASE_TRAITS
            public iterator_base_traits<typename M::iterator1::iterator_category>::template
                        iterator_base<iterator, value_type>::type {
#else
            public random_access_iterator_base<typename M::iterator1::iterator_category,
                                               iterator, value_type> {
#endif                                               
        public:
            typedef typename M::iterator1::iterator_category iterator_category;
            typedef typename M::iterator1::difference_type difference_type;
            typedef typename M::iterator1::value_type value_type;
            typedef typename M::iterator1::reference reference;
            typedef typename M::iterator1::pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator ():
                container_reference<matrix_column> (), it_ () {}
            BOOST_UBLAS_INLINE
            iterator (matrix_column &mc, const iterator_type &it):
                container_reference<matrix_column> (mc), it_ (it) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            iterator &operator ++ () {
                ++ it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator &operator -- () {
                -- it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator &operator += (difference_type n) {
                it_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator &operator -= (difference_type n) {
                it_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const iterator &it) const {
                return it_ - it.it_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
                return *it_;
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                return it_.index1 ();
            }

            // Assignment 
            BOOST_UBLAS_INLINE
            iterator &operator = (const iterator &it) {
                container_reference<matrix_column>::assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ == it.it_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ < it.it_;
            }

        private:
            iterator_type it_;

            friend class const_iterator;
        };
#endif

        BOOST_UBLAS_INLINE
        iterator begin () {
            return find_first (0);
        }
        BOOST_UBLAS_INLINE
        iterator end () {
            return find_last (size ());
        }

        // Reverse iterator

#ifdef BOOST_MSVC_STD_ITERATOR
        typedef reverse_iterator_base<const_iterator, value_type, const_reference> const_reverse_iterator;
#else
        typedef reverse_iterator_base<const_iterator> const_reverse_iterator;
#endif

        BOOST_UBLAS_INLINE
        const_reverse_iterator rbegin () const {
            return const_reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator rend () const {
            return const_reverse_iterator (begin ());
        }

#ifdef BOOST_MSVC_STD_ITERATOR
        typedef reverse_iterator_base<iterator, value_type, reference> reverse_iterator;
#else
        typedef reverse_iterator_base<iterator> reverse_iterator;
#endif

        BOOST_UBLAS_INLINE
        reverse_iterator rbegin () {
            return reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator rend () {
            return reverse_iterator (begin ());
        }

    private:
        matrix_type &data_;
        size_type j_;
        static matrix_type nil_;
    };

    template<class M>
    typename matrix_column<M>::matrix_type matrix_column<M>::nil_;

    // Projections
    template<class M>
    BOOST_UBLAS_INLINE
    matrix_column<M> column (M &data, std::size_t j) {
        return matrix_column<M> (data, j);
    }
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
    template<class M>
    BOOST_UBLAS_INLINE
    const matrix_column<const M> column (const M &data, std::size_t j) {
        return matrix_column<const M> (data, j);
    }
#endif

    // Matrix column iterator
    template<class M, class I>
    class matrix_column_iterator:
        public container_reference<M>,
        public random_access_iterator_base<I,
                                           matrix_column_iterator<M, I>,
                                           matrix_column<M>,
                                           typename M::difference_type> {
    public:
        typedef M matrix_type;
        typedef I iterator_category;
        typedef typename matrix_type::size_type size_type;
        typedef typename matrix_type::difference_type difference_type;
        typedef matrix_column<matrix_type> value_type;
        typedef matrix_column<matrix_type> reference;
        typedef value_type *pointer;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        matrix_column_iterator ():
            container_reference<matrix_type> (), it_ () {}
        BOOST_UBLAS_INLINE
        matrix_column_iterator (matrix_type &m, size_type it):
            container_reference<matrix_type> (m), it_ (it) {}

        // Arithmetic
        BOOST_UBLAS_INLINE
        matrix_column_iterator &operator ++ () {
            ++ it_;
            return *this;
        }
        BOOST_UBLAS_INLINE
        matrix_column_iterator &operator -- () {
            -- it_;
            return *this;
        }
        BOOST_UBLAS_INLINE
        matrix_column_iterator &operator += (difference_type n) {
            it_ += n;
            return *this;
        }
        BOOST_UBLAS_INLINE
        matrix_column_iterator &operator -= (difference_type n) {
            it_ -= n;
            return *this;
        }
        BOOST_UBLAS_INLINE
        difference_type operator - (const matrix_column_iterator &it) const {
            return it_ - it.it_;
        }

        // Dereference
        BOOST_UBLAS_INLINE
        reference operator * () const {
            BOOST_UBLAS_CHECK (index () < (*this) ().size2 (), bad_index ());
            return column ((*this) (), it_);
        }

        // Index
        BOOST_UBLAS_INLINE
        size_type index () const {
            return it_;
        }

        // Assignment 
        BOOST_UBLAS_INLINE
        matrix_column_iterator &operator = (const matrix_column_iterator &it) {
            assign (&it ());
            it_ = it.it_;
            return *this;
        }

        // Comparison
        BOOST_UBLAS_INLINE
        bool operator == (const matrix_column_iterator &it) const {
            BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
            return it_ == it.it_;
        }
        BOOST_UBLAS_INLINE
        bool operator < (const matrix_column_iterator &it) const {
            BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
            return it_ < it.it_;
        }

    private:
        size_type it_;
    };

#ifdef BOOST_MSVC_STD_ITERATOR
    template<class M, class I>
    BOOST_UBLAS_INLINE
    matrix_column_iterator<M, I> operator ++ (const matrix_column_iterator<M, I> &it, int) {
        matrix_column_iterator<M, I> tmp (it);
        ++ tmp;
        return tmp;
    }
    template<class M, class I>
    BOOST_UBLAS_INLINE
    matrix_column_iterator<M, I> operator -- (const matrix_column_iterator<M, I> &it, int) {
        matrix_column_iterator<M, I> tmp (it);
        -- tmp;
        return tmp;
    }
    template<class M, class I>
    BOOST_UBLAS_INLINE
    matrix_column_iterator<M, I> operator + (const matrix_column_iterator<M, I> &it, std::ptrdiff_t n) {
        matrix_column_iterator<M, I> tmp (it);
        return tmp += n;
    }
    template<class M, class I>
    BOOST_UBLAS_INLINE
    matrix_column_iterator<M, I> operator - (const matrix_column_iterator<M, I> &it, std::ptrdiff_t n) {
        matrix_column_iterator<M, I> tmp (it);
        return tmp -= n;
    }
#endif

    template<class M, class I>
    class matrix_column_const_iterator:
        public container_const_reference<M>,
        public random_access_iterator_base<I,
                                           matrix_column_const_iterator<M, I>,
                                           matrix_column<M>,
                                           typename M::difference_type> {
    public:
        typedef M matrix_type;
        typedef I iterator_category;
        typedef typename matrix_type::size_type size_type;
        typedef typename matrix_type::difference_type difference_type;
        typedef matrix_column<matrix_type> value_type;
        typedef const matrix_column<const matrix_type> const_reference;
        typedef matrix_column<matrix_type> reference;
        typedef value_type *pointer;
        typedef matrix_column_iterator<matrix_type, iterator_category> iterator_type;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        matrix_column_const_iterator ():
            container_const_reference<matrix_type> (), it_ () {}
        BOOST_UBLAS_INLINE
        matrix_column_const_iterator (const matrix_type &c, size_type it):
            container_const_reference<matrix_type> (c), it_ (it) {}
        BOOST_UBLAS_INLINE
        matrix_column_const_iterator (const iterator_type &it):
            container_const_reference<matrix_type> (it ()), it_ (it.index ()) {}

        // Arithmetic
        BOOST_UBLAS_INLINE
        matrix_column_const_iterator &operator ++ () {
            ++ it_;
            return *this;
        }
        BOOST_UBLAS_INLINE
        matrix_column_const_iterator &operator -- () {
            -- it_;
            return *this;
        }
        BOOST_UBLAS_INLINE
        matrix_column_const_iterator &operator += (difference_type n) {
            it_ += n;
            return *this;
        }
        BOOST_UBLAS_INLINE
        matrix_column_const_iterator &operator -= (difference_type n) {
            it_ -= n;
            return *this;
        }
        BOOST_UBLAS_INLINE
        difference_type operator - (const matrix_column_const_iterator &it) const {
            return it_ - it.it_;
        }

        // Dereference
        BOOST_UBLAS_INLINE
        reference operator * () const {
            BOOST_UBLAS_CHECK (index () < (*this) ().size2 (), bad_index ());
            return column ((*this) (), it_);
        }

        // Index
        BOOST_UBLAS_INLINE
        size_type index () const {
            return it_;
        }

        // Assignment 
        BOOST_UBLAS_INLINE
        matrix_column_const_iterator &operator = (const matrix_column_const_iterator &it) {
            assign (&it ());
            it_ = it.it_;
            return *this;
        }

        // Comparison
        BOOST_UBLAS_INLINE
        bool operator == (const matrix_column_const_iterator &it) const {
            BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
            return it_ == it.it_;
        }
        BOOST_UBLAS_INLINE
        bool operator < (const matrix_column_const_iterator &it) const {
            BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
            return it_ < it.it_;
        }

    private:
        size_type it_;

        friend class matrix_column_iterator<matrix_type, iterator_category>;
    };

#ifdef BOOST_MSVC_STD_ITERATOR
    template<class M, class I>
    BOOST_UBLAS_INLINE
    matrix_column_const_iterator<M, I> operator ++ (const matrix_column_const_iterator<M, I> &it, int) {
        matrix_column_const_iterator<M, I> tmp (it);
        ++ tmp;
        return tmp;
    }
    template<class M, class I>
    BOOST_UBLAS_INLINE
    matrix_column_const_iterator<M, I> operator -- (const matrix_column_const_iterator<M, I> &it, int) {
        matrix_column_const_iterator<M, I> tmp (it);
        -- tmp;
        return tmp;
    }
    template<class M, class I>
    BOOST_UBLAS_INLINE
    matrix_column_const_iterator<M, I> operator + (const matrix_column_const_iterator<M, I> &it, std::ptrdiff_t n) {
        matrix_column_const_iterator<M, I> tmp (it);
        return tmp += n;
    }
    template<class M, class I>
    BOOST_UBLAS_INLINE
    matrix_column_const_iterator<M, I> operator - (const matrix_column_const_iterator<M, I> &it, std::ptrdiff_t n) {
        matrix_column_const_iterator<M, I> tmp (it);
        return tmp -= n;
    }
#endif

    // Matrix based vector range class
    template<class M>
    class matrix_vector_range:
        public vector_expression<matrix_vector_range<M> > {
    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        BOOST_UBLAS_USING vector_expression<matrix_vector_range<M> >::operator ();
#endif
        typedef const M const_matrix_type;
        typedef M matrix_type;
        typedef typename M::size_type size_type;
        typedef typename M::difference_type difference_type;
        typedef typename M::value_type value_type;
        typedef typename M::const_reference const_reference;
        typedef typename M::reference reference;
        typedef typename M::const_pointer const_pointer;
        typedef typename M::pointer pointer;
#ifdef BOOST_UBLAS_ET_CLOSURE_REFERENCE
        typedef const vector_const_reference<const matrix_vector_range<matrix_type> > const_closure_type;
        typedef vector_reference<matrix_vector_range<matrix_type> > closure_type;
#endif
#ifdef BOOST_UBLAS_ET_CLOSURE_VALUE
        typedef const matrix_vector_range<matrix_type> const_closure_type;
        typedef matrix_vector_range<matrix_type> closure_type;
#endif
#ifdef BOOST_UBLAS_ENABLE_INDEX_SET_ALL
        typedef range<>::const_iterator const_iterator1_type;
        typedef range<>::const_iterator iterator1_type;
        typedef range<>::const_iterator const_iterator2_type;
        typedef range<>::const_iterator iterator2_type;
#else
        typedef range::const_iterator const_iterator1_type;
        typedef range::const_iterator iterator1_type;
        typedef range::const_iterator const_iterator2_type;
        typedef range::const_iterator iterator2_type;
#endif
        typedef typename storage_restrict_traits<typename M::storage_category,
                                                 dense_proxy_tag>::storage_category storage_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        matrix_vector_range (): 
            data_ (nil_), r1_ (), r2_ () {}
#ifdef BOOST_UBLAS_ENABLE_INDEX_SET_ALL
        BOOST_UBLAS_INLINE
        matrix_vector_range (matrix_type &data, const range<> &r1, const range<> &r2):
            data_ (data), r1_ (r1), r2_ (r2) {}
#else
        BOOST_UBLAS_INLINE
        matrix_vector_range (matrix_type &data, const range &r1, const range &r2):
            data_ (data), r1_ (r1), r2_ (r2) {}
#endif

        // Accessors
        BOOST_UBLAS_INLINE
        size_type size () const { 
            return BOOST_UBLAS_SAME (r1_.size (), r2_.size ()); 
        }
        BOOST_UBLAS_INLINE
        const_matrix_type &data () const {
            return data_;
        }
        BOOST_UBLAS_INLINE
        matrix_type &data () {
            return data_;
        }

#ifdef BOOST_UBLAS_DEPRECATED
        // Resetting
        BOOST_UBLAS_INLINE
        void reset (matrix_type &data) {
            // data_ = data;
            data_.reset (data);
        }
        BOOST_UBLAS_INLINE
        void reset (matrix_type &data, const range<> &r1, const range<> &r2) {
            // data_ = data;
            data_.reset (data);
            r1_ = r1;
            r2_ = r2;
        }
#endif

        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i) const {
            return data () (r1_ (i), r2_ (i)); 
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i) {
            return data () (r1_ (i), r2_ (i)); 
        }

        BOOST_UBLAS_INLINE
        const_reference operator [] (size_type i) const { 
            return (*this) (i); 
        }
        BOOST_UBLAS_INLINE
        reference operator [] (size_type i) { 
            return (*this) (i); 
        }

        // Assignment
        BOOST_UBLAS_INLINE
        matrix_vector_range &operator = (const matrix_vector_range &mvr) { 
            // FIXME: the ranges could be differently sized.
            // std::copy (mvr.begin (), mvr.end (), begin ());
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vector<value_type> (mvr));
            return *this;
        }
        BOOST_UBLAS_INLINE
        matrix_vector_range &assign_temporary (matrix_vector_range &mvr) {
            // FIXME: this is suboptimal.
            // return *this = mvr;
            vector_assign<scalar_assign<value_type, value_type> > () (*this, mvr);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_vector_range &operator = (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vector<value_type> (ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_vector_range &assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_vector_range &operator += (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vector<value_type> (*this + ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_vector_range &plus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_plus_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_vector_range &operator -= (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vector<value_type> (*this - ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_vector_range &minus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_minus_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        matrix_vector_range &operator *= (const AT &at) {
            vector_assign_scalar<scalar_multiplies_assign<value_type, AT> > () (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        matrix_vector_range &operator /= (const AT &at) {
            vector_assign_scalar<scalar_divides_assign<value_type, AT> > () (*this, at);
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (matrix_vector_range &mvr) {
            // Too unusual semantic.
            // BOOST_UBLAS_CHECK (this != &mvr, external_logic ());
            if (this != &mvr) {
                BOOST_UBLAS_CHECK (size () == mvr.size (), bad_size ());
                std::swap_ranges (begin (), end (), mvr.begin ());
            }
        }
#ifdef BOOST_UBLAS_FRIEND_FUNCTION
        BOOST_UBLAS_INLINE
        friend void swap (matrix_vector_range &mvr1, matrix_vector_range &mvr2) {
            mvr1.swap (mvr2);
        }
#endif

        class const_iterator;
        class iterator;

        // Element lookup
        BOOST_UBLAS_INLINE
        const_iterator find_first (size_type i) const {
            return const_iterator (*this, r1_.begin () + i, r2_.begin () + i);
        }
        BOOST_UBLAS_INLINE
        iterator find_first (size_type i) {
            return iterator (*this, r1_.begin () + i, r2_.begin () + i);
        }
        BOOST_UBLAS_INLINE
        const_iterator find_last (size_type i) const {
            return const_iterator (*this, r1_.begin () + i, r2_.begin () + i);
        }
        BOOST_UBLAS_INLINE
        iterator find_last (size_type i) {
            return iterator (*this, r1_.begin () + i, r2_.begin () + i);
        }

        // Iterators simply are indices.

        class const_iterator:
            public container_const_reference<matrix_vector_range>,
#ifdef BOOST_UBLAS_USE_ITERATOR_BASE_TRAITS
            public iterator_base_traits<typename iterator_restrict_traits<typename M::const_iterator1::iterator_category,
                                                                          typename M::const_iterator2::iterator_category>::iterator_category>::template
                        iterator_base<const_iterator, value_type>::type {
#else
            public random_access_iterator_base<typename iterator_restrict_traits<typename M::const_iterator1::iterator_category,
                                                                                 typename M::const_iterator2::iterator_category>::iterator_category,
                                               const_iterator, value_type> {
#endif
        public:
            typedef typename iterator_restrict_traits<typename M::const_iterator1::iterator_category,
                                                      typename M::const_iterator2::iterator_category>::iterator_category iterator_category;
#ifdef BOOST_MSVC_STD_ITERATOR
            typedef const_reference reference;
#else
            typedef typename matrix_vector_range::difference_type difference_type;
            typedef typename matrix_vector_range::value_type value_type;
            typedef typename matrix_vector_range::const_reference reference;
            typedef typename matrix_vector_range::const_pointer pointer;
#endif

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator ():
                container_const_reference<matrix_vector_range> (), it1_ (), it2_ () {}
            BOOST_UBLAS_INLINE
            const_iterator (const matrix_vector_range &mvr, const const_iterator1_type &it1, const const_iterator2_type &it2):
                container_const_reference<matrix_vector_range> (mvr), it1_ (it1), it2_ (it2) {}
#ifndef BOOST_UBLAS_QUALIFIED_TYPENAME
            BOOST_UBLAS_INLINE
            const_iterator (const iterator &it):
                container_const_reference<matrix_vector_range> (it ()), it1_ (it.it1_), it2_ (it.it2_) {}
#else
            BOOST_UBLAS_INLINE
            const_iterator (const typename matrix_vector_range::iterator &it):
                container_const_reference<matrix_vector_range> (it ()), it1_ (it.it1_), it2_ (it.it2_) {}
#endif

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator &operator ++ () {
                ++ it1_;
                ++ it2_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -- () {
                -- it1_;
                -- it2_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator += (difference_type n) {
                it1_ += n;
                it2_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -= (difference_type n) {
                it1_ -= n;
                it2_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const const_iterator &it) const {
                return BOOST_UBLAS_SAME (it1_ - it.it1_, it2_ - it.it2_);
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                return (*this) ().data () (*it1_, *it2_);
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type  index () const {
                return BOOST_UBLAS_SAME (it1_.index (), it2_.index ());
            }

            // Assignment 
            BOOST_UBLAS_INLINE
            const_iterator &operator = (const const_iterator &it) {
                container_const_reference<matrix_vector_range>::assign (&it ());
                it1_ = it.it1_;
                it2_ = it.it2_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ == it.it1_ && it2_ == it.it2_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const const_iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ < it.it1_ && it2_ < it.it2_;
            }

        private:
            const_iterator1_type it1_;
            const_iterator2_type it2_;
        };

        BOOST_UBLAS_INLINE
        const_iterator begin () const {
            return find_first (0); 
        }
        BOOST_UBLAS_INLINE
        const_iterator end () const {
            return find_last (size ()); 
        }

        class iterator:
            public container_reference<matrix_vector_range>,
#ifdef BOOST_UBLAS_USE_ITERATOR_BASE_TRAITS
            public iterator_base_traits<typename iterator_restrict_traits<typename M::iterator1::iterator_category,
                                                                          typename M::iterator2::iterator_category>::iterator_category>::template
                        iterator_base<iterator, value_type>::type {
#else
            public random_access_iterator_base<typename iterator_restrict_traits<typename M::iterator1::iterator_category,
                                                                                 typename M::iterator2::iterator_category>::iterator_category,
                                               iterator, value_type> {
#endif                                               
        public:
            typedef typename iterator_restrict_traits<typename M::iterator1::iterator_category,
                                                      typename M::iterator2::iterator_category>::iterator_category iterator_category;
#ifndef BOOST_MSVC_STD_ITERATOR
            typedef typename matrix_vector_range::difference_type difference_type;
            typedef typename matrix_vector_range::value_type value_type;
            typedef typename matrix_vector_range::reference reference;
            typedef typename matrix_vector_range::pointer pointer;
#endif

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator ():
                container_reference<matrix_vector_range> (), it1_ (), it2_ () {}
            BOOST_UBLAS_INLINE
            iterator (matrix_vector_range &mvr, const iterator1_type &it1, const iterator2_type &it2):
                container_reference<matrix_vector_range> (mvr), it1_ (it1), it2_ (it2) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            iterator &operator ++ () {
                ++ it1_;
                ++ it2_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator &operator -- () {
                -- it1_;
                -- it2_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator &operator += (difference_type n) {
                it1_ += n;
                it2_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator &operator -= (difference_type n) {
                it1_ -= n;
                it2_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const iterator &it) const {
                return BOOST_UBLAS_SAME (it1_ - it.it1_, it2_ - it.it2_);
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                return (*this) ().data () (*it1_, *it2_); 
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                return BOOST_UBLAS_SAME (it1_.index (), it2_.index ());
            }

            // Assignment 
            BOOST_UBLAS_INLINE
            iterator &operator = (const iterator &it) {
                container_reference<matrix_vector_range>::assign (&it ());
                it1_ = it.it1_;
                it2_ = it.it2_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ == it.it1_ && it2_ == it.it2_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ < it.it1_ && it2_ < it.it2_;
            }

        private:
            iterator1_type it1_;
            iterator2_type it2_;

            friend class const_iterator;
        };

        BOOST_UBLAS_INLINE
        iterator begin () {
            return find_first (0); 
        }
        BOOST_UBLAS_INLINE
        iterator end () {
            return find_last (size ()); 
        }

        // Reverse iterator

#ifdef BOOST_MSVC_STD_ITERATOR
        typedef reverse_iterator_base<const_iterator, value_type, const_reference> const_reverse_iterator;
#else
        typedef reverse_iterator_base<const_iterator> const_reverse_iterator;
#endif

        BOOST_UBLAS_INLINE
        const_reverse_iterator rbegin () const {
            return const_reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator rend () const {
            return const_reverse_iterator (begin ());
        }

#ifdef BOOST_MSVC_STD_ITERATOR
        typedef reverse_iterator_base<iterator, value_type, reference> reverse_iterator;
#else
        typedef reverse_iterator_base<iterator> reverse_iterator;
#endif

        BOOST_UBLAS_INLINE
        reverse_iterator rbegin () {
            return reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator rend () {
            return reverse_iterator (begin ());
        }

    private:
        matrix_type &data_;
#ifdef BOOST_UBLAS_ENABLE_INDEX_SET_ALL
        range<> r1_;
        range<> r2_;
#else
        range r1_;
        range r2_;
#endif
        static matrix_type nil_;
    };

    template<class M>
    typename matrix_vector_range<M>::matrix_type matrix_vector_range<M>::nil_;

    // Matrix based vector slice class
    template<class M>
    class matrix_vector_slice:
        public vector_expression<matrix_vector_slice<M> > {
    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        BOOST_UBLAS_USING vector_expression<matrix_vector_slice<M> >::operator ();
#endif
        typedef const M const_matrix_type;
        typedef M matrix_type;
        typedef typename M::size_type size_type;
        typedef typename M::difference_type difference_type;
        typedef typename M::value_type value_type;
        typedef typename M::const_reference const_reference;
        typedef typename M::reference reference;
        typedef typename M::const_pointer const_pointer;
        typedef typename M::pointer pointer;
#ifdef BOOST_UBLAS_ET_CLOSURE_REFERENCE
        typedef const vector_const_reference<const matrix_vector_slice<matrix_type> > const_closure_type;
        typedef vector_reference<matrix_vector_slice<matrix_type> > closure_type;
#endif
#ifdef BOOST_UBLAS_ET_CLOSURE_VALUE
        typedef const matrix_vector_slice<matrix_type> const_closure_type;
        typedef matrix_vector_slice<matrix_type> closure_type;
#endif
#ifdef BOOST_UBLAS_ENABLE_INDEX_SET_ALL
        typedef slice<>::const_iterator const_iterator1_type;
        typedef slice<>::const_iterator iterator1_type;
        typedef slice<>::const_iterator const_iterator2_type;
        typedef slice<>::const_iterator iterator2_type;
#else
        typedef slice::const_iterator const_iterator1_type;
        typedef slice::const_iterator iterator1_type;
        typedef slice::const_iterator const_iterator2_type;
        typedef slice::const_iterator iterator2_type;
#endif
        typedef typename storage_restrict_traits<typename M::storage_category,
                                                 dense_proxy_tag>::storage_category storage_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        matrix_vector_slice ():
            data_ (nil_), s1_ (), s2_ () {}
#ifdef BOOST_UBLAS_ENABLE_INDEX_SET_ALL
        BOOST_UBLAS_INLINE
        matrix_vector_slice (matrix_type &data, const slice<> &s1, const slice<> &s2):
            data_ (data), s1_ (s1), s2_ (s2) {}
#else
        BOOST_UBLAS_INLINE
        matrix_vector_slice (matrix_type &data, const slice &s1, const slice &s2):
            data_ (data), s1_ (s1), s2_ (s2) {}
#endif

        // Accessors
        BOOST_UBLAS_INLINE
        size_type size () const {
            return BOOST_UBLAS_SAME (s1_.size (), s2_.size ()); 
        }
        BOOST_UBLAS_INLINE
        const_matrix_type &data () const {
            return data_;
        }
        BOOST_UBLAS_INLINE
        matrix_type &data () {
            return data_;
        }

#ifdef BOOST_UBLAS_DEPRECATED
        // Resetting
        BOOST_UBLAS_INLINE
        void reset (matrix_type &data) {
            // data_ = data;
            data_.reset (data);
        }
        BOOST_UBLAS_INLINE
        void reset (matrix_type &data, const slice<> &s1, const slice<> &s2) {
            // data_ = data;
            data_.reset (data);
            s1_ = s1;
            s2_ = s2;
        }
#endif

        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i) const {
            return data () (s1_ (i), s2_ (i)); 
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i) {
            return data () (s1_ (i), s2_ (i)); 
        }

        BOOST_UBLAS_INLINE
        const_reference operator [] (size_type i) const { 
            return (*this) (i); 
        }
        BOOST_UBLAS_INLINE
        reference operator [] (size_type i) { 
            return (*this) (i); 
        }

        // Assignment
        BOOST_UBLAS_INLINE
        matrix_vector_slice &operator = (const matrix_vector_slice &mvs) { 
            // FIXME: the slices could be differently sized.
            // std::copy (mvs.begin (), mvs.end (), begin ());
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vector<value_type> (mvs));
            return *this;
        }
        BOOST_UBLAS_INLINE
        matrix_vector_slice &assign_temporary (matrix_vector_slice &mvs) {
            // FIXME: this is suboptimal.
            // return *this = mvs;
            vector_assign<scalar_assign<value_type, value_type> > () (*this, mvs);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_vector_slice &operator = (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vector<value_type> (ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_vector_slice &assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_vector_slice &operator += (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vector<value_type> (*this + ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_vector_slice &plus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_plus_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_vector_slice &operator -= (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vector<value_type> (*this - ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_vector_slice &minus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_minus_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        matrix_vector_slice &operator *= (const AT &at) {
            vector_assign_scalar<scalar_multiplies_assign<value_type, AT> > () (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        matrix_vector_slice &operator /= (const AT &at) {
            vector_assign_scalar<scalar_divides_assign<value_type, AT> > () (*this, at);
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (matrix_vector_slice &mvs) {
            // Too unusual semantic.
            // BOOST_UBLAS_CHECK (this != &mvs, external_logic ());
            if (this != &mvs) {
                BOOST_UBLAS_CHECK (size () == mvs.size (), bad_size ());
                std::swap_ranges (begin (), end (), mvs.begin ());
            }
        }
#ifdef BOOST_UBLAS_FRIEND_FUNCTION
        BOOST_UBLAS_INLINE
        friend void swap (matrix_vector_slice &mvs1, matrix_vector_slice &mvs2) {
            mvs1.swap (mvs2);
        }
#endif

        class const_iterator;
        class iterator;

        // Element lookup
        BOOST_UBLAS_INLINE
        const_iterator find_first (size_type i) const {
            return const_iterator (*this, s1_.begin () + i, s2_.begin () + i);
        }
        BOOST_UBLAS_INLINE
        iterator find_first (size_type i) {
            return iterator (*this, s1_.begin () + i, s2_.begin () + i);
        }
        BOOST_UBLAS_INLINE
        const_iterator find_last (size_type i) const {
            return const_iterator (*this, s1_.begin () + i, s2_.begin () + i);
        }
        BOOST_UBLAS_INLINE
        iterator find_last (size_type i) {
            return iterator (*this, s1_.begin () + i, s2_.begin () + i);
        }

        // Iterators simply are indices.

        class const_iterator:
            public container_const_reference<matrix_vector_slice>,
#ifdef BOOST_UBLAS_USE_ITERATOR_BASE_TRAITS
            public iterator_base_traits<typename iterator_restrict_traits<typename M::const_iterator1::iterator_category,
                                                                          typename M::const_iterator2::iterator_category>::iterator_category>::template
                        iterator_base<const_iterator, value_type>::type {
#else
            public random_access_iterator_base<typename iterator_restrict_traits<typename M::const_iterator1::iterator_category,
                                                                                 typename M::const_iterator2::iterator_category>::iterator_category,
                                               const_iterator, value_type> {
#endif
        public:
            typedef typename iterator_restrict_traits<typename M::const_iterator1::iterator_category,
                                                      typename M::const_iterator2::iterator_category>::iterator_category iterator_category;
#ifdef BOOST_MSVC_STD_ITERATOR
            typedef const_reference reference;
#else
            typedef typename matrix_vector_slice::difference_type difference_type;
            typedef typename matrix_vector_slice::value_type value_type;
            typedef typename matrix_vector_slice::const_reference reference;
            typedef typename matrix_vector_slice::const_pointer pointer;
#endif

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator ():
                container_const_reference<matrix_vector_slice> (), it1_ (), it2_ () {}
            BOOST_UBLAS_INLINE
            const_iterator (const matrix_vector_slice &mvs, const const_iterator1_type &it1, const const_iterator2_type &it2):
                container_const_reference<matrix_vector_slice> (mvs), it1_ (it1), it2_ (it2) {}
#ifndef BOOST_UBLAS_QUALIFIED_TYPENAME
            BOOST_UBLAS_INLINE
            const_iterator (const iterator &it):
                container_const_reference<matrix_vector_slice> (it ()), it1_ (it.it1_), it2_ (it.it2_) {}
#else
            BOOST_UBLAS_INLINE
            const_iterator (const typename matrix_vector_slice::iterator &it):
                container_const_reference<matrix_vector_slice> (it ()), it1_ (it.it1_), it2_ (it.it2_) {}
#endif

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator &operator ++ () {
                ++ it1_;
                ++ it2_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -- () {
                -- it1_;
                -- it2_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator += (difference_type n) {
                it1_ += n;
                it2_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -= (difference_type n) {
                it1_ -= n;
                it2_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const const_iterator &it) const {
                return BOOST_UBLAS_SAME (it1_ - it.it1_, it2_ - it.it2_);
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                return (*this) ().data () (*it1_, *it2_); 
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type  index () const {
                return BOOST_UBLAS_SAME (it1_.index (), it2_.index ());
            }

            // Assignment 
            BOOST_UBLAS_INLINE
            const_iterator &operator = (const const_iterator &it) {
                container_const_reference<matrix_vector_slice>::assign (&it ());
                it1_ = it.it1_;
                it2_ = it.it2_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ == it.it1_ && it2_ == it.it2_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const const_iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ < it.it1_ && it2_ < it.it2_;
            }

        private:
            const_iterator1_type it1_;
            const_iterator2_type it2_;
        };

        BOOST_UBLAS_INLINE
        const_iterator begin () const {
            return find_first (0); 
        }
        BOOST_UBLAS_INLINE
        const_iterator end () const {
            return find_last (size ()); 
        }

        class iterator:
            public container_reference<matrix_vector_slice>,
#ifdef BOOST_UBLAS_USE_ITERATOR_BASE_TRAITS
            public iterator_base_traits<typename iterator_restrict_traits<typename M::iterator1::iterator_category,
                                                                          typename M::iterator2::iterator_category>::iterator_category>::template
                        iterator_base<iterator, value_type>::type {
#else
            public random_access_iterator_base<typename iterator_restrict_traits<typename M::iterator1::iterator_category,
                                                                                 typename M::iterator2::iterator_category>::iterator_category,
                                               iterator, value_type> {
#endif                                               
        public:
            typedef typename iterator_restrict_traits<typename M::iterator1::iterator_category,
                                                      typename M::iterator2::iterator_category>::iterator_category iterator_category;
#ifndef BOOST_MSVC_STD_ITERATOR
            typedef typename matrix_vector_slice::difference_type difference_type;
            typedef typename matrix_vector_slice::value_type value_type;
            typedef typename matrix_vector_slice::reference reference;
            typedef typename matrix_vector_slice::pointer pointer;
#endif

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator ():
                container_reference<matrix_vector_slice> (), it1_ (), it2_ () {}
            BOOST_UBLAS_INLINE
            iterator (matrix_vector_slice &mvs, const iterator1_type &it1, const iterator2_type &it2):
                container_reference<matrix_vector_slice> (mvs), it1_ (it1), it2_ (it2) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            iterator &operator ++ () {
                ++ it1_;
                ++ it2_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator &operator -- () {
                -- it1_;
                -- it2_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator &operator += (difference_type n) {
                it1_ += n;
                it2_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator &operator -= (difference_type n) {
                it1_ -= n;
                it2_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const iterator &it) const {
                return BOOST_UBLAS_SAME (it1_ - it.it1_, it2_ - it.it2_);
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                return (*this) ().data () (*it1_, *it2_);
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                return BOOST_UBLAS_SAME (it1_.index (), it2_.index ());
            }

            // Assignment 
            BOOST_UBLAS_INLINE
            iterator &operator = (const iterator &it) {
                container_reference<matrix_vector_slice>::assign (&it ());
                it1_ = it.it1_;
                it2_ = it.it2_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ == it.it1_ && it2_ == it.it2_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ < it.it1_ && it2_ < it.it2_;
            }

        private:
            iterator1_type it1_;
            iterator2_type it2_;

            friend class const_iterator;
        };

        BOOST_UBLAS_INLINE
        iterator begin () {
            return find_first (0); 
        }
        BOOST_UBLAS_INLINE
        iterator end () {
            return find_last (size ()); 
        }

        // Reverse iterator

#ifdef BOOST_MSVC_STD_ITERATOR
        typedef reverse_iterator_base<const_iterator, value_type, const_reference> const_reverse_iterator;
#else
        typedef reverse_iterator_base<const_iterator> const_reverse_iterator;
#endif

        BOOST_UBLAS_INLINE
        const_reverse_iterator rbegin () const {
            return const_reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator rend () const {
            return const_reverse_iterator (begin ());
        }

#ifdef BOOST_MSVC_STD_ITERATOR
        typedef reverse_iterator_base<iterator, value_type, reference> reverse_iterator;
#else
        typedef reverse_iterator_base<iterator> reverse_iterator;
#endif

        BOOST_UBLAS_INLINE
        reverse_iterator rbegin () {
            return reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator rend () {
            return reverse_iterator (begin ());
        }

    private:
        matrix_type &data_;
#ifdef BOOST_UBLAS_ENABLE_INDEX_SET_ALL
        slice<> s1_;
        slice<> s2_;
#else
        slice s1_;
        slice s2_;
#endif
        static matrix_type nil_;
    };

    template<class M>
    typename matrix_vector_slice<M>::matrix_type matrix_vector_slice<M>::nil_;

    // Matrix based vector indirection class
    template<class M, class IA>
    class matrix_vector_indirect:
        public vector_expression<matrix_vector_indirect<M, IA> > {
    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        BOOST_UBLAS_USING vector_expression<matrix_vector_indirect<M, IA> >::operator ();
#endif
        typedef const M const_matrix_type;
        typedef M matrix_type;
        typedef const IA const_indirect_array_type;
        typedef IA indirect_array_type;
        typedef typename M::size_type size_type;
        typedef typename M::difference_type difference_type;
        typedef typename M::value_type value_type;
        typedef typename M::const_reference const_reference;
        typedef typename M::reference reference;
        typedef typename M::const_pointer const_pointer;
        typedef typename M::pointer pointer;
#ifdef BOOST_UBLAS_ET_CLOSURE_REFERENCE
        typedef const vector_const_reference<const matrix_vector_indirect<matrix_type, indirect_array_type> > const_closure_type;
        typedef vector_reference<matrix_vector_indirect<matrix_type, indirect_array_type> > closure_type;
#endif
#ifdef BOOST_UBLAS_ET_CLOSURE_VALUE
        typedef const matrix_vector_indirect<matrix_type, indirect_array_type> const_closure_type;
        typedef matrix_vector_indirect<matrix_type, indirect_array_type> closure_type;
#endif
        typedef typename IA::const_iterator const_iterator1_type;
        typedef typename IA::const_iterator iterator1_type;
        typedef typename IA::const_iterator const_iterator2_type;
        typedef typename IA::const_iterator iterator2_type;
        typedef typename storage_restrict_traits<typename M::storage_category,
                                                 dense_proxy_tag>::storage_category storage_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        matrix_vector_indirect ():
            data_ (nil_), ia1_ (), ia2_ () {}
        BOOST_UBLAS_INLINE
        matrix_vector_indirect (matrix_type &data, size_type size):
            data_ (data), ia1_ (size), ia2_ (size) {}
        BOOST_UBLAS_INLINE
        matrix_vector_indirect (matrix_type &data, const indirect_array_type &ia1, const indirect_array_type &ia2):
            data_ (data), ia1_ (ia1), ia2_ (ia2) {}

        // Accessors
        BOOST_UBLAS_INLINE
        size_type size () const {
            return BOOST_UBLAS_SAME (ia1_.size (), ia2_.size ());
        }
        BOOST_UBLAS_INLINE
        const_matrix_type &data () const {
            return data_;
        }
        BOOST_UBLAS_INLINE
        matrix_type &data () {
            return data_;
        }
        BOOST_UBLAS_INLINE
        const_indirect_array_type &indirect1 () const {
            return ia1_;
        }
        BOOST_UBLAS_INLINE
        indirect_array_type &indirect1 () {
            return ia1_;
        }
        BOOST_UBLAS_INLINE
        const_indirect_array_type &indirect2 () const {
            return ia2_;
        }
        BOOST_UBLAS_INLINE
        indirect_array_type &indirect2 () {
            return ia2_;
        }

#ifdef BOOST_UBLAS_DEPRECATED
        // Resetting
        BOOST_UBLAS_INLINE
        void reset (matrix_type &data) {
            // data_ = data;
            data_.reset (data);
        }
        BOOST_UBLAS_INLINE
        void reset (matrix_type &data, const indirect_array_type &ia1, const indirect_array_type &ia2) {
            // data_ = data;
            data_.reset (data);
            ia1_ = ia1;
            ia2_ = ia2;
        }
#endif

        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i) const {
            return data () (ia1_ (i), ia2_ (i));
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i) {
            return data () (ia1_ (i), ia2_ (i));
        }

        BOOST_UBLAS_INLINE
        const_reference operator [] (size_type i) const {
            return (*this) (i);
        }
        BOOST_UBLAS_INLINE
        reference operator [] (size_type i) {
            return (*this) (i);
        }

        // Assignment
        BOOST_UBLAS_INLINE
        matrix_vector_indirect &operator = (const matrix_vector_indirect &mvi) {
            // FIXME: the indirects could be differently sized.
            // std::copy (mvi.begin (), mvi.end (), begin ());
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vector<value_type> (mvi));
            return *this;
        }
        BOOST_UBLAS_INLINE
        matrix_vector_indirect &assign_temporary (matrix_vector_indirect &mvi) {
            // FIXME: this is suboptimal.
            // return *this = mvi;
            vector_assign<scalar_assign<value_type, value_type> > () (*this, mvi);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_vector_indirect &operator = (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vector<value_type> (ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_vector_indirect &assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_vector_indirect &operator += (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vector<value_type> (*this + ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_vector_indirect &plus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_plus_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_vector_indirect &operator -= (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign<value_type, value_type> > () (*this, vector<value_type> (*this - ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_vector_indirect &minus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_minus_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        matrix_vector_indirect &operator *= (const AT &at) {
            vector_assign_scalar<scalar_multiplies_assign<value_type, AT> > () (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        matrix_vector_indirect &operator /= (const AT &at) {
            vector_assign_scalar<scalar_divides_assign<value_type, AT> > () (*this, at);
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (matrix_vector_indirect &mvi) {
            // Too unusual semantic.
            // BOOST_UBLAS_CHECK (this != &mvi, external_logic ());
            if (this != &mvi) {
                BOOST_UBLAS_CHECK (size () == mvi.size (), bad_size ());
                std::swap_ranges (begin (), end (), mvi.begin ());
            }
        }
#ifdef BOOST_UBLAS_FRIEND_FUNCTION
        BOOST_UBLAS_INLINE
        friend void swap (matrix_vector_indirect &mvi1, matrix_vector_indirect &mvi2) {
            mvi1.swap (mvi2);
        }
#endif

        class const_iterator;
        class iterator;

        // Element lookup
        BOOST_UBLAS_INLINE
        const_iterator find_first (size_type i) const {
            return const_iterator (*this, ia1_.begin () + i, ia2_.begin () + i);
        }
        BOOST_UBLAS_INLINE
        iterator find_first (size_type i) {
            return iterator (*this, ia1_.begin () + i, ia2_.begin () + i);
        }
        BOOST_UBLAS_INLINE
        const_iterator find_last (size_type i) const {
            return const_iterator (*this, ia1_.begin () + i, ia2_.begin () + i);
        }
        BOOST_UBLAS_INLINE
        iterator find_last (size_type i) {
            return iterator (*this, ia1_.begin () + i, ia2_.begin () + i);
        }

        // Iterators simply are indices.

        class const_iterator:
            public container_const_reference<matrix_vector_indirect>,
#ifdef BOOST_UBLAS_USE_ITERATOR_BASE_TRAITS
            public iterator_base_traits<typename iterator_restrict_traits<typename M::const_iterator1::iterator_category,
                                                                          typename M::const_iterator2::iterator_category>::iterator_category>::template
                        iterator_base<const_iterator, value_type>::type {
#else
            public random_access_iterator_base<typename iterator_restrict_traits<typename M::const_iterator1::iterator_category,
                                                                                 typename M::const_iterator2::iterator_category>::iterator_category,
                                               const_iterator, value_type> {
#endif
        public:
            typedef typename iterator_restrict_traits<typename M::const_iterator1::iterator_category,
                                                      typename M::const_iterator2::iterator_category>::iterator_category iterator_category;
#ifdef BOOST_MSVC_STD_ITERATOR
            typedef const_reference reference;
#else
            typedef typename matrix_vector_indirect::difference_type difference_type;
            typedef typename matrix_vector_indirect::value_type value_type;
            typedef typename matrix_vector_indirect::const_reference reference;
            typedef typename matrix_vector_indirect::const_pointer pointer;
#endif

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator ():
                container_const_reference<matrix_vector_indirect> (), it1_ (), it2_ () {}
            BOOST_UBLAS_INLINE
            const_iterator (const matrix_vector_indirect &mvi, const const_iterator1_type &it1, const const_iterator2_type &it2):
                container_const_reference<matrix_vector_indirect> (mvi), it1_ (it1), it2_ (it2) {}
#ifndef BOOST_UBLAS_QUALIFIED_TYPENAME
            BOOST_UBLAS_INLINE
            const_iterator (const iterator &it):
                container_const_reference<matrix_vector_indirect> (it ()), it1_ (it.it1_), it2_ (it.it2_) {}
#else
            BOOST_UBLAS_INLINE
            const_iterator (const typename matrix_vector_indirect::iterator &it):
                container_const_reference<matrix_vector_indirect> (it ()), it1_ (it.it1_), it2_ (it.it2_) {}
#endif

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator &operator ++ () {
                ++ it1_;
                ++ it2_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -- () {
                -- it1_;
                -- it2_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator += (difference_type n) {
                it1_ += n;
                it2_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -= (difference_type n) {
                it1_ -= n;
                it2_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const const_iterator &it) const {
                return BOOST_UBLAS_SAME (it1_ - it.it1_, it2_ - it.it2_);
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                return (*this) ().data () (*it1_, *it2_);
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type  index () const {
                return BOOST_UBLAS_SAME (it1_.index (), it2_.index ());
            }

            // Assignment
            BOOST_UBLAS_INLINE
            const_iterator &operator = (const const_iterator &it) {
                container_const_reference<matrix_vector_indirect>::assign (&it ());
                it1_ = it.it1_;
                it2_ = it.it2_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ == it.it1_ && it2_ == it.it2_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const const_iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ < it.it1_ && it2_ < it.it2_;
            }

        private:
            const_iterator1_type it1_;
            const_iterator2_type it2_;
        };

        BOOST_UBLAS_INLINE
        const_iterator begin () const {
            return find_first (0);
        }
        BOOST_UBLAS_INLINE
        const_iterator end () const {
            return find_last (size ());
        }

        class iterator:
            public container_reference<matrix_vector_indirect>,
#ifdef BOOST_UBLAS_USE_ITERATOR_BASE_TRAITS
            public iterator_base_traits<typename iterator_restrict_traits<typename M::iterator1::iterator_category,
                                                                          typename M::iterator2::iterator_category>::iterator_category>::template
                        iterator_base<iterator, value_type>::type {
#else
            public random_access_iterator_base<typename iterator_restrict_traits<typename M::iterator1::iterator_category,
                                                                                 typename M::iterator2::iterator_category>::iterator_category,
                                               iterator, value_type> {
#endif
        public:
            typedef typename iterator_restrict_traits<typename M::iterator1::iterator_category,
                                                      typename M::iterator2::iterator_category>::iterator_category iterator_category;
#ifndef BOOST_MSVC_STD_ITERATOR
            typedef typename matrix_vector_indirect::difference_type difference_type;
            typedef typename matrix_vector_indirect::value_type value_type;
            typedef typename matrix_vector_indirect::reference reference;
            typedef typename matrix_vector_indirect::pointer pointer;
#endif

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator ():
                container_reference<matrix_vector_indirect> (), it1_ (), it2_ () {}
            BOOST_UBLAS_INLINE
            iterator (matrix_vector_indirect &mvi, const iterator1_type &it1, const iterator2_type &it2):
                container_reference<matrix_vector_indirect> (mvi), it1_ (it1), it2_ (it2) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            iterator &operator ++ () {
                ++ it1_;
                ++ it2_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator &operator -- () {
                -- it1_;
                -- it2_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator &operator += (difference_type n) {
                it1_ += n;
                it2_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator &operator -= (difference_type n) {
                it1_ -= n;
                it2_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const iterator &it) const {
                return BOOST_UBLAS_SAME (it1_ - it.it1_, it2_ - it.it2_);
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                return (*this) ().data () (*it1_, *it2_);
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                return BOOST_UBLAS_SAME (it1_.index (), it2_.index ());
            }

            // Assignment
            BOOST_UBLAS_INLINE
            iterator &operator = (const iterator &it) {
                container_reference<matrix_vector_indirect>::assign (&it ());
                it1_ = it.it1_;
                it2_ = it.it2_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ == it.it1_ && it2_ == it.it2_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ < it.it1_ && it2_ < it.it2_;
            }

        private:
            iterator1_type it1_;
            iterator2_type it2_;

            friend class const_iterator;
        };

        BOOST_UBLAS_INLINE
        iterator begin () {
            return find_first (0);
        }
        BOOST_UBLAS_INLINE
        iterator end () {
            return find_last (size ());
        }

        // Reverse iterator

#ifdef BOOST_MSVC_STD_ITERATOR
        typedef reverse_iterator_base<const_iterator, value_type, const_reference> const_reverse_iterator;
#else
        typedef reverse_iterator_base<const_iterator> const_reverse_iterator;
#endif

        BOOST_UBLAS_INLINE
        const_reverse_iterator rbegin () const {
            return const_reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator rend () const {
            return const_reverse_iterator (begin ());
        }

#ifdef BOOST_MSVC_STD_ITERATOR
        typedef reverse_iterator_base<iterator, value_type, reference> reverse_iterator;
#else
        typedef reverse_iterator_base<iterator> reverse_iterator;
#endif

        BOOST_UBLAS_INLINE
        reverse_iterator rbegin () {
            return reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator rend () {
            return reverse_iterator (begin ());
        }

    private:
        matrix_type &data_;
        indirect_array_type ia1_;
        indirect_array_type ia2_;
        static matrix_type nil_;
    };

    template<class M, class IA>
    typename matrix_vector_indirect<M, IA>::matrix_type matrix_vector_indirect<M, IA>::nil_;

    // Matrix based range class
    template<class M>
    class matrix_range:
        public matrix_expression<matrix_range<M> > {
    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        BOOST_UBLAS_USING matrix_expression<matrix_range<M> >::operator ();
#endif
        typedef const M const_matrix_type;
        typedef M matrix_type;
        typedef typename M::size_type size_type;
        typedef typename M::difference_type difference_type;
        typedef typename M::value_type value_type;
        typedef typename M::const_reference const_reference;
        typedef typename M::reference reference;
        typedef typename M::const_pointer const_pointer;
        typedef typename M::pointer pointer;
#ifdef BOOST_UBLAS_ET_CLOSURE_REFERENCE
        typedef const matrix_const_reference<const matrix_range<matrix_type> > const_closure_type;
        typedef matrix_reference<matrix_range<matrix_type> > closure_type;
#endif
#ifdef BOOST_UBLAS_ET_CLOSURE_VALUE
        typedef const matrix_range<matrix_type> const_closure_type;
        typedef matrix_range<matrix_type> closure_type;
#endif
        typedef typename M::const_iterator1 const_iterator1_type;
        typedef typename M::iterator1 iterator1_type;
        typedef typename M::const_iterator2 const_iterator2_type;
        typedef typename M::iterator2 iterator2_type;
        typedef typename storage_restrict_traits<typename M::storage_category,
                                                 dense_proxy_tag>::storage_category storage_category;
        typedef typename M::orientation_category orientation_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        matrix_range ():
            data_ (nil_), r1_ (), r2_ () {}
#ifdef BOOST_UBLAS_ENABLE_INDEX_SET_ALL
        BOOST_UBLAS_INLINE
        matrix_range (matrix_type &data, const range<> &r1, const range<> &r2):
            data_ (data), r1_ (r1.preprocess (data.size1 ())), r2_ (r2.preprocess (data.size2 ())) {}
#else
        BOOST_UBLAS_INLINE
        matrix_range (matrix_type &data, const range &r1, const range &r2):
            data_ (data), r1_ (r1), r2_ (r2) {}
#endif

        // Accessors
        BOOST_UBLAS_INLINE
        size_type start1 () const {
            return r1_.start (); 
        }
        BOOST_UBLAS_INLINE
        size_type size1 () const { 
            return r1_.size ();
        }
        BOOST_UBLAS_INLINE
        size_type start2() const { 
            return r2_.start (); 
        }
        BOOST_UBLAS_INLINE
        size_type size2 () const { 
            return r2_.size ();
        }
        BOOST_UBLAS_INLINE
        const_matrix_type &data () const {
            return data_;
        }
        BOOST_UBLAS_INLINE
        matrix_type &data () {
            return data_;
        }

#ifdef BOOST_UBLAS_DEPRECATED
        // Resetting
        BOOST_UBLAS_INLINE
        void reset (matrix_type &data) {
            // data_ = data;
            data_.reset (data);
        }
        BOOST_UBLAS_INLINE
        void reset (matrix_type &data, const range<> &r1, const range<> &r2) {
            // data_ = data;
            data_.reset (data);
            r1_ = r1;
            r2_ = r2;
        }
#endif

        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i, size_type j) const {
            return data () (r1_ (i), r2_ (j)); 
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i, size_type j) {
            return data () (r1_ (i), r2_ (j)); 
        }

#ifdef BOOST_UBLAS_ENABLE_INDEX_SET_ALL
        BOOST_UBLAS_INLINE
        matrix_range<matrix_type> project (const range<> &r1, const range<> &r2) const {
            return matrix_range<matrix_type>  (data_, r1_.compose (r1), r2_.compose (r2));
        }
#else
        BOOST_UBLAS_INLINE
        matrix_range<matrix_type> project (const range &r1, const range &r2) const {
            return matrix_range<matrix_type>  (data_, r1_.compose (r1), r2_.compose (r2));
        }
#endif

        // Assignment
        BOOST_UBLAS_INLINE
        matrix_range &operator = (const matrix_range &mr) { 
            matrix_assign<scalar_assign<value_type, value_type> > () (*this, mr); 
            return *this;
        }
        BOOST_UBLAS_INLINE
        matrix_range &assign_temporary (matrix_range &mr) { 
            return *this = mr;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_range &operator = (const matrix_expression<AE> &ae) { 
            matrix_assign<scalar_assign<value_type, value_type> > () (*this, matrix<value_type> (ae)); 
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_range &assign (const matrix_expression<AE> &ae) { 
            matrix_assign<scalar_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae); 
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_range& operator += (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_assign<value_type, value_type> > () (*this, matrix<value_type> (*this + ae)); 
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_range &plus_assign (const matrix_expression<AE> &ae) { 
            matrix_assign<scalar_plus_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae); 
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_range& operator -= (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_assign<value_type, value_type> > () (*this, matrix<value_type> (*this - ae)); 
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_range &minus_assign (const matrix_expression<AE> &ae) { 
            matrix_assign<scalar_minus_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae); 
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        matrix_range& operator *= (const AT &at) {
            matrix_assign_scalar<scalar_multiplies_assign<value_type, AT> > () (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        matrix_range& operator /= (const AT &at) {
            matrix_assign_scalar<scalar_divides_assign<value_type, AT> > () (*this, at);
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (matrix_range &mr) {
            // Too unusual semantic.
            // BOOST_UBLAS_CHECK (this != &mr, external_logic ());
            if (this != &mr) {
                BOOST_UBLAS_CHECK (size1 () == mr.size1 (), bad_size ());
                BOOST_UBLAS_CHECK (size2 () == mr.size2 (), bad_size ());
                matrix_swap<scalar_swap<value_type, value_type> > () (*this, mr);
            }
        }
#ifdef BOOST_UBLAS_FRIEND_FUNCTION
        BOOST_UBLAS_INLINE
        friend void swap (matrix_range &mr1, matrix_range &mr2) {
            mr1.swap (mr2);
        }
#endif

#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
        typedef matrix_row_iterator<matrix_range<matrix_type>,
                                    BOOST_UBLAS_TYPENAME matrix_type::iterator1::iterator_category> iterator1;
        typedef matrix_column_iterator<matrix_range<matrix_type>,
                                       BOOST_UBLAS_TYPENAME matrix_type::iterator2::iterator_category> iterator2;
        typedef matrix_row_const_iterator<matrix_range<matrix_type>,
                                          BOOST_UBLAS_TYPENAME matrix_type::const_iterator1::iterator_category> const_iterator1;
        typedef matrix_column_const_iterator<matrix_range<matrix_type>,
                                             BOOST_UBLAS_TYPENAME matrix_type::const_iterator2::iterator_category> const_iterator2;
#ifdef BOOST_MSVC_STD_ITERATOR
        typedef reverse_iterator_base<const_iterator1, typename matrix_row<matrix_range<matrix_type> >, typename matrix_row<matrix_range<const_matrix_type> > > const_reverse_iterator1;
        typedef reverse_iterator_base<iterator1, typename matrix_row<matrix_range<matrix_type> >, typename matrix_row<matrix_range<matrix_type> > > reverse_iterator1;
        typedef reverse_iterator_base<const_iterator2, typename matrix_column<matrix_range<matrix_type> >, typename matrix_column<matrix_range<const_matrix_type> > > const_reverse_iterator2;
        typedef reverse_iterator_base<iterator2, typename matrix_column<matrix_range<matrix_type> >, typename matrix_column<matrix_range<matrix_type> > > reverse_iterator2;
#else
        typedef reverse_iterator_base<const_iterator1> const_reverse_iterator1;
        typedef reverse_iterator_base<iterator1> reverse_iterator1;
        typedef reverse_iterator_base<const_iterator2> const_reverse_iterator2;
        typedef reverse_iterator_base<iterator2> reverse_iterator2;
#endif
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
        typedef indexed_iterator1<matrix_range<matrix_type>,
                                  BOOST_UBLAS_TYPENAME matrix_type::iterator1::iterator_category> iterator1;
        typedef indexed_iterator2<matrix_range<matrix_type>,
                                  BOOST_UBLAS_TYPENAME matrix_type::iterator2::iterator_category> iterator2;
        typedef indexed_const_iterator1<matrix_range<matrix_type>,
                                        BOOST_UBLAS_TYPENAME matrix_type::const_iterator1::iterator_category> const_iterator1;
        typedef indexed_const_iterator2<matrix_range<matrix_type>,
                                        BOOST_UBLAS_TYPENAME matrix_type::const_iterator2::iterator_category> const_iterator2;
#else
        class const_iterator1;
        class iterator1;
        class const_iterator2;
        class iterator2;
#endif
#ifdef BOOST_MSVC_STD_ITERATOR
        typedef reverse_iterator_base1<const_iterator1, value_type, const_reference> const_reverse_iterator1;
        typedef reverse_iterator_base1<iterator1, value_type, reference> reverse_iterator1;
        typedef reverse_iterator_base2<const_iterator2, value_type, const_reference> const_reverse_iterator2;
        typedef reverse_iterator_base2<iterator2, value_type, reference> reverse_iterator2;
#else
        typedef reverse_iterator_base1<const_iterator1> const_reverse_iterator1;
        typedef reverse_iterator_base1<iterator1> reverse_iterator1;
        typedef reverse_iterator_base2<const_iterator2> const_reverse_iterator2;
        typedef reverse_iterator_base2<iterator2> reverse_iterator2;
#endif
#endif

        // Element lookup
        BOOST_UBLAS_INLINE
        const_iterator1 find_first1 (int rank, size_type i, size_type j) const {
            const_iterator1_type it1 (data ().find_first1 (rank, start1 () + i, start2 () + j));
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return const_iterator1 (*this, it1.index ());
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return const_iterator1 (*this, it1.index1 (), it1.index2 ());
#else
            return const_iterator1 (*this, it1);
#endif
#endif
        }
        BOOST_UBLAS_INLINE
        iterator1 find_first1 (int rank, size_type i, size_type j) {
            iterator1_type it1 (data ().find_first1 (rank, start1 () + i, start2 () + j));
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return iterator1 (*this, it1.index ());
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return iterator1 (*this, it1.index1 (), it1.index2 ());
#else
            return iterator1 (*this, it1);
#endif
#endif
        }
        BOOST_UBLAS_INLINE
        const_iterator1 find_last1 (int rank, size_type i, size_type j) const {
            const_iterator1_type it1 (data ().find_last1 (rank, start1 () + i, start2 () + j));
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return const_iterator1 (*this, it1.index ());
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return const_iterator1 (*this, it1.index1 (), it1.index2 ());
#else
            return const_iterator1 (*this, it1);
#endif
#endif
        }
        BOOST_UBLAS_INLINE
        iterator1 find_last1 (int rank, size_type i, size_type j) {
            iterator1_type it1 (data ().find_last1 (rank, start1 () + i, start2 () + j));
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return iterator1 (*this, it1.index ());
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return iterator1 (*this, it1.index1 (), it1.index2 ());
#else
            return iterator1 (*this, it1);
#endif
#endif
        }
        BOOST_UBLAS_INLINE
        const_iterator2 find_first2 (int rank, size_type i, size_type j) const {
            const_iterator2_type it2 (data ().find_first2 (rank, start1 () + i, start2 () + j));
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return const_iterator2 (*this, it2.index ());
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return const_iterator2 (*this, it2.index1 (), it2.index2 ());
#else
            return const_iterator2 (*this, it2);
#endif
#endif
        }
        BOOST_UBLAS_INLINE
        iterator2 find_first2 (int rank, size_type i, size_type j) {
            iterator2_type it2 (data ().find_first2 (rank, start1 () + i, start2 () + j));
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return iterator2 (*this, it2.index ());
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return iterator2 (*this, it2.index1 (), it2.index2 ());
#else
            return iterator2 (*this, it2);
#endif
#endif
        }
        BOOST_UBLAS_INLINE
        const_iterator2 find_last2 (int rank, size_type i, size_type j) const {
            const_iterator2_type it2 (data ().find_last2 (rank, start1 () + i, start2 () + j));
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return const_iterator2 (*this, it2.index ());
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return const_iterator2 (*this, it2.index1 (), it2.index2 ());
#else
            return const_iterator2 (*this, it2);
#endif
#endif
        }
        BOOST_UBLAS_INLINE
        iterator2 find_last2 (int rank, size_type i, size_type j) {
            iterator2_type it2 (data ().find_last2 (rank, start1 () + i, start2 () + j));
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return iterator2 (*this, it2.index ());
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return iterator2 (*this, it2.index1 (), it2.index2 ());
#else
            return iterator2 (*this, it2);
#endif
#endif
        }

        // Iterators simply are pointers.

#if ! defined (BOOST_UBLAS_USE_CANONICAL_ITERATOR) && ! defined (BOOST_UBLAS_USE_INDEXED_ITERATOR)
        class const_iterator1:
            public container_const_reference<matrix_range>,
#ifdef BOOST_UBLAS_USE_ITERATOR_BASE_TRAITS
            public iterator_base_traits<typename M::const_iterator1::iterator_category>::template
                        iterator_base<const_iterator1, value_type>::type {
#else
            public random_access_iterator_base<typename M::const_iterator1::iterator_category,
                                               const_iterator1, value_type> {
#endif                                               
        public:
            typedef typename M::const_iterator1::iterator_category iterator_category;
            typedef typename M::const_iterator1::difference_type difference_type;
            typedef typename M::const_iterator1::value_type value_type;
            typedef typename M::const_iterator1::reference reference;
            typedef typename M::const_iterator1::pointer pointer;
            typedef const_iterator2 dual_iterator_type;
            typedef const_reverse_iterator2 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator1 ():
                container_const_reference<matrix_range> (), it_ () {}
            BOOST_UBLAS_INLINE
            const_iterator1 (const matrix_range &mr, const const_iterator1_type &it):
                container_const_reference<matrix_range> (mr), it_ (it) {}
            BOOST_UBLAS_INLINE
            const_iterator1 (const iterator1 &it):
                container_const_reference<matrix_range> (it ()), it_ (it.it_) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator1 &operator ++ () {
                ++ it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator1 &operator -- () {
                -- it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator1 &operator += (difference_type n) {
                it_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator1 &operator -= (difference_type n) {
                it_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const const_iterator1 &it) const {
                return it_ - it.it_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                return *it_; 
            }

            BOOST_UBLAS_INLINE
            const_iterator2 begin () const {
                const matrix_range &mr = (*this) ();
                return mr.find_first2 (1, index1 (), 0);
            }
            BOOST_UBLAS_INLINE
            const_iterator2 end () const {
                const matrix_range &mr = (*this) ();
                return mr.find_last2 (1, index1 (), mr.size2 ());
            }
            BOOST_UBLAS_INLINE
            const_reverse_iterator2 rbegin () const {
                return const_reverse_iterator2 (end ());
            }
            BOOST_UBLAS_INLINE
            const_reverse_iterator2 rend () const {
                return const_reverse_iterator2 (begin ());
            }

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                return it_.index1 () - (*this) ().start1 ();
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                return it_.index2 () - (*this) ().start2 ();
            }

            // Assignment 
            BOOST_UBLAS_INLINE
            const_iterator1 &operator = (const const_iterator1 &it) {
                container_const_reference<matrix_range>::assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ == it.it_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const const_iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ < it.it_;
            }

        private:
            const_iterator1_type it_;
        };
#endif

        BOOST_UBLAS_INLINE
        const_iterator1 begin1 () const {
            return find_first1 (0, 0, 0); 
        }
        BOOST_UBLAS_INLINE
        const_iterator1 end1 () const {
            return find_last1 (0, size1 (), 0); 
        }

#if ! defined (BOOST_UBLAS_USE_CANONICAL_ITERATOR) && ! defined (BOOST_UBLAS_USE_INDEXED_ITERATOR)
        class iterator1:
            public container_reference<matrix_range>,
#ifdef BOOST_UBLAS_USE_ITERATOR_BASE_TRAITS
            public iterator_base_traits<typename M::iterator1::iterator_category>::template
                        iterator_base<iterator1, value_type>::type {
#else
            public random_access_iterator_base<typename M::iterator1::iterator_category,
                                               iterator1, value_type> {
#endif                                               
        public:
            typedef typename M::iterator1::iterator_category iterator_category;
            typedef typename M::iterator1::difference_type difference_type;
            typedef typename M::iterator1::value_type value_type;
            typedef typename M::iterator1::reference reference;
            typedef typename M::iterator1::pointer pointer;
            typedef iterator2 dual_iterator_type;
            typedef reverse_iterator2 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator1 ():
                container_reference<matrix_range> (), it_ () {}
            BOOST_UBLAS_INLINE
            iterator1 (matrix_range &mr, const iterator1_type &it):
                container_reference<matrix_range> (mr), it_ (it) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            iterator1 &operator ++ () {
                ++ it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator1 &operator -- () {
                -- it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator1 &operator += (difference_type n) {
                it_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator1 &operator -= (difference_type n) {
                it_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const iterator1 &it) const {
                return it_ - it.it_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                return *it_; 
            }

            BOOST_UBLAS_INLINE
            iterator2 begin () const {
                matrix_range &mr = (*this) ();
                return mr.find_first2 (1, index1 (), 0);
            }
            BOOST_UBLAS_INLINE
            iterator2 end () const {
                matrix_range &mr = (*this) ();
                return mr.find_last2 (1, index1 (), mr.size2 ());
            }
            BOOST_UBLAS_INLINE
            reverse_iterator2 rbegin () const {
                return reverse_iterator2 (end ());
            }
            BOOST_UBLAS_INLINE
            reverse_iterator2 rend () const {
                return reverse_iterator2 (begin ());
            }

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                return it_.index1 () - (*this) ().start1 ();
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                return it_.index2 () - (*this) ().start2 ();
            }

            // Assignment 
            BOOST_UBLAS_INLINE
            iterator1 &operator = (const iterator1 &it) {
                container_reference<matrix_range>::assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ == it.it_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ < it.it_;
            }

        private:
            iterator1_type it_;

            friend class const_iterator1;
        };
#endif

        BOOST_UBLAS_INLINE
        iterator1 begin1 () {
            return find_first1 (0, 0, 0); 
        }
        BOOST_UBLAS_INLINE
        iterator1 end1 () {
            return find_last1 (0, size1 (), 0); 
        }

#if ! defined (BOOST_UBLAS_USE_CANONICAL_ITERATOR) && ! defined (BOOST_UBLAS_USE_INDEXED_ITERATOR)
        class const_iterator2:
            public container_const_reference<matrix_range>,
#ifdef BOOST_UBLAS_USE_ITERATOR_BASE_TRAITS
            public iterator_base_traits<typename M::const_iterator2::iterator_category>::template
                        iterator_base<const_iterator2, value_type>::type {
#else
            public random_access_iterator_base<typename M::const_iterator2::iterator_category,
                                               const_iterator2, value_type> {
#endif                                               
        public:
            typedef typename M::const_iterator2::iterator_category iterator_category;
            typedef typename M::const_iterator2::difference_type difference_type;
            typedef typename M::const_iterator2::value_type value_type;
            typedef typename M::const_iterator2::reference reference;
            typedef typename M::const_iterator2::pointer pointer;
            typedef const_iterator1 dual_iterator_type;
            typedef const_reverse_iterator1 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator2 ():
                container_const_reference<matrix_range> (), it_ () {}
            BOOST_UBLAS_INLINE
            const_iterator2 (const matrix_range &mr, const const_iterator2_type &it):
                container_const_reference<matrix_range> (mr), it_ (it) {}
            BOOST_UBLAS_INLINE
            const_iterator2 (const iterator2 &it):
                container_const_reference<matrix_range> (it ()), it_ (it.it_) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator2 &operator ++ () {
                ++ it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator2 &operator -- () {
                -- it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator2 &operator += (difference_type n) {
                it_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator2 &operator -= (difference_type n) {
                it_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const const_iterator2 &it) const {
                return it_ - it.it_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                return *it_; 
            }

            BOOST_UBLAS_INLINE
            const_iterator1 begin () const {
                const matrix_range &mr = (*this) ();
                return mr.find_first1 (1, 0, index2 ());
            }
            BOOST_UBLAS_INLINE
            const_iterator1 end () const {
                const matrix_range &mr = (*this) ();
                return mr.find_last1 (1, mr.size1 (), index2 ());
            }
            BOOST_UBLAS_INLINE
            const_reverse_iterator1 rbegin () const {
                return const_reverse_iterator1 (end ());
            }
            BOOST_UBLAS_INLINE
            const_reverse_iterator1 rend () const {
                return const_reverse_iterator1 (begin ());
            }

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                return it_.index1 () - (*this) ().start1 ();
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                return it_.index2 () - (*this) ().start2 ();
            }

            // Assignment 
            BOOST_UBLAS_INLINE
            const_iterator2 &operator = (const const_iterator2 &it) {
                container_const_reference<matrix_range>::assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ == it.it_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const const_iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ < it.it_;
            }

        private:
            const_iterator2_type it_;
        };
#endif

        BOOST_UBLAS_INLINE
        const_iterator2 begin2 () const {
            return find_first2 (0, 0, 0); 
        }
        BOOST_UBLAS_INLINE
        const_iterator2 end2 () const {
            return find_last2 (0, 0, size2 ()); 
        }

#if ! defined (BOOST_UBLAS_USE_CANONICAL_ITERATOR) && ! defined (BOOST_UBLAS_USE_INDEXED_ITERATOR)
        class iterator2:
            public container_reference<matrix_range>,
#ifdef BOOST_UBLAS_USE_ITERATOR_BASE_TRAITS
            public iterator_base_traits<typename M::iterator2::iterator_category>::template
                        iterator_base<iterator2, value_type>::type {
#else
            public random_access_iterator_base<typename M::iterator2::iterator_category,
                                               iterator2, value_type> {
#endif                                               
        public:
            typedef typename M::iterator2::iterator_category iterator_category;
            typedef typename M::iterator2::difference_type difference_type;
            typedef typename M::iterator2::value_type value_type;
            typedef typename M::iterator2::reference reference;
            typedef typename M::iterator2::pointer pointer;
            typedef iterator1 dual_iterator_type;
            typedef reverse_iterator1 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator2 ():
                container_reference<matrix_range> (), it_ () {}
            BOOST_UBLAS_INLINE
            iterator2 (matrix_range &mr, const iterator2_type &it):
                container_reference<matrix_range> (mr), it_ (it) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            iterator2 &operator ++ () {
                ++ it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator2 &operator -- () {
                -- it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator2 &operator += (difference_type n) {
                it_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator2 &operator -= (difference_type n) {
                it_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const iterator2 &it) const {
                return it_ - it.it_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                return *it_;
            }

            BOOST_UBLAS_INLINE
            iterator1 begin () const {
                matrix_range &mr = (*this) ();
                return mr.find_first1 (1, 0, index2 ());
            }
            BOOST_UBLAS_INLINE
            iterator1 end () const {
                matrix_range &mr = (*this) ();
                return mr.find_last1 (1, mr.size1 (), index2 ());
            }
            BOOST_UBLAS_INLINE
            reverse_iterator1 rbegin () const {
                return reverse_iterator1 (end ());
            }
            BOOST_UBLAS_INLINE
            reverse_iterator1 rend () const {
                return reverse_iterator1 (begin ());
            }

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                return it_.index1 () - (*this) ().start1 ();
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                return it_.index2 () - (*this) ().start2 ();
            }

            // Assignment 
            BOOST_UBLAS_INLINE
            iterator2 &operator = (const iterator2 &it) {
                container_reference<matrix_range>::assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ == it.it_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ < it.it_;
            }

        private:
            iterator2_type it_;

            friend class const_iterator2;
        };
#endif

        BOOST_UBLAS_INLINE
        iterator2 begin2 () {
            return find_first2 (0, 0, 0); 
        }
        BOOST_UBLAS_INLINE
        iterator2 end2 () {
            return find_last2 (0, 0, size2 ()); 
        }

        // Reverse iterators

        BOOST_UBLAS_INLINE
        const_reverse_iterator1 rbegin1 () const {
            return const_reverse_iterator1 (end1 ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator1 rend1 () const {
            return const_reverse_iterator1 (begin1 ());
        }

        BOOST_UBLAS_INLINE
        reverse_iterator1 rbegin1 () {
            return reverse_iterator1 (end1 ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator1 rend1 () {
            return reverse_iterator1 (begin1 ());
        }

        BOOST_UBLAS_INLINE
        const_reverse_iterator2 rbegin2 () const {
            return const_reverse_iterator2 (end2 ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator2 rend2 () const {
            return const_reverse_iterator2 (begin2 ());
        }

        BOOST_UBLAS_INLINE
        reverse_iterator2 rbegin2 () {
            return reverse_iterator2 (end2 ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator2 rend2 () {
            return reverse_iterator2 (begin2 ());
        }

    private:
        matrix_type &data_;
#ifdef BOOST_UBLAS_ENABLE_INDEX_SET_ALL
        range<> r1_;
        range<> r2_;
#else
        range r1_;
        range r2_;
#endif
        static matrix_type nil_;
    };

    template<class M>
    typename matrix_range<M>::matrix_type matrix_range<M>::nil_;

    // Projections
#ifdef BOOST_UBLAS_ENABLE_INDEX_SET_ALL
    template<class M>
    BOOST_UBLAS_INLINE
    matrix_range<M> project (M &data, const range<> &r1, const range<> &r2) {
        return matrix_range<M> (data, r1, r2);
    }
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
    template<class M>
    BOOST_UBLAS_INLINE
    const matrix_range<const M> project (const M &data, const range<> &r1, const range<> &r2) {
        return matrix_range<const M> (data, r1, r2);
    }
    template<class M>
    BOOST_UBLAS_INLINE
    matrix_range<M> project (const matrix_range<M> &data, const range<> &r1, const range<> &r2) {
        return data.project (r1, r2);
    }
#endif
#else
    template<class M>
    BOOST_UBLAS_INLINE
    matrix_range<M> project (M &data, const range &r1, const range &r2) {
        return matrix_range<M> (data, r1, r2);
    }
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
    template<class M>
    BOOST_UBLAS_INLINE
    const matrix_range<const M> project (const M &data, const range &r1, const range &r2) {
        return matrix_range<const M> (data, r1, r2);
    }
    template<class M>
    BOOST_UBLAS_INLINE
    matrix_range<M> project (const matrix_range<M> &data, const range &r1, const range &r2) {
        return data.project (r1, r2);
    }
#endif
#endif

    // Matrix based slice class
    template<class M>
    class matrix_slice:
        public matrix_expression<matrix_slice<M> > {
    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        BOOST_UBLAS_USING matrix_expression<matrix_slice<M> >::operator ();
#endif
        typedef const M const_matrix_type;
        typedef M matrix_type;
        typedef typename M::size_type size_type;
        typedef typename M::difference_type difference_type;
        typedef typename M::value_type value_type;
        typedef typename M::const_reference const_reference;
        typedef typename M::reference reference;
        typedef typename M::const_pointer const_pointer;
        typedef typename M::pointer pointer;
#ifdef BOOST_UBLAS_ET_CLOSURE_REFERENCE
        typedef const matrix_const_reference<const matrix_slice<matrix_type> > const_closure_type;
        typedef matrix_reference<matrix_slice<matrix_type> > closure_type;
#endif
#ifdef BOOST_UBLAS_ET_CLOSURE_VALUE
        typedef const matrix_slice<matrix_type> const_closure_type;
        typedef matrix_slice<matrix_type> closure_type;
#endif
#ifdef BOOST_UBLAS_ENABLE_INDEX_SET_ALL
        typedef slice<>::const_iterator const_iterator1_type;
        typedef slice<>::const_iterator iterator1_type;
        typedef slice<>::const_iterator const_iterator2_type;
        typedef slice<>::const_iterator iterator2_type;
#else
        typedef slice::const_iterator const_iterator1_type;
        typedef slice::const_iterator iterator1_type;
        typedef slice::const_iterator const_iterator2_type;
        typedef slice::const_iterator iterator2_type;
#endif
        typedef typename storage_restrict_traits<typename M::storage_category,
                                                 dense_proxy_tag>::storage_category storage_category;
        typedef typename M::orientation_category orientation_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        matrix_slice ():
            data_ (nil_), s1_ (), s2_ () {}
#ifdef BOOST_UBLAS_ENABLE_INDEX_SET_ALL
        BOOST_UBLAS_INLINE
        matrix_slice (matrix_type &data, const slice<> &s1, const slice<> &s2):
            data_ (data), s1_ (s1.preprocess (data.size1 ())), s2_ (s2.preprocess (data.size2 ())) {}
#else
        BOOST_UBLAS_INLINE
        matrix_slice (matrix_type &data, const slice &s1, const slice &s2):
            data_ (data), s1_ (s1), s2_ (s2) {}
#endif

        // Accessors
        BOOST_UBLAS_INLINE
        size_type size1 () const {
            return s1_.size ();
        }
        BOOST_UBLAS_INLINE
        size_type size2 () const { 
            return s2_.size ();
        }
        BOOST_UBLAS_INLINE
        const_matrix_type &data () const {
            return data_;
        }
        BOOST_UBLAS_INLINE
        matrix_type &data () {
            return data_;
        }

#ifdef BOOST_UBLAS_DEPRECATED
        // Resetting
        BOOST_UBLAS_INLINE
        void reset (matrix_type &data) {
            // data_ = data;
            data_.reset (data);
        }
        BOOST_UBLAS_INLINE
        void reset (matrix_type &data, const slice<> &s1, const slice<> &s2) {
            // data_ = data;
            data_.reset (data);
            s1_ = s1;
            s2_ = s2;
        }
#endif

        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i, size_type j) const {
            return data () (s1_ (i), s2_ (j)); 
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i, size_type j) {
            return data () (s1_ (i), s2_ (j));
        }

#ifdef BOOST_UBLAS_ENABLE_INDEX_SET_ALL
        BOOST_UBLAS_INLINE
        matrix_slice<matrix_type> project (const range<> &r1, const range<> &r2) const {
            return matrix_slice<matrix_type>  (data_, s1_.compose (r1), s2_.compose (r2));
        }
        BOOST_UBLAS_INLINE
        matrix_slice<matrix_type> project (const slice<> &s1, const slice<> &s2) const {
            return matrix_slice<matrix_type>  (data_, s1_.compose (s1), s2_.compose (s2));
        }
#else
        BOOST_UBLAS_INLINE
        matrix_slice<matrix_type> project (const range &r1, const range &r2) const {
            return matrix_slice<matrix_type>  (data_, s1_.compose (r1), s2_.compose (r2));
        }
        BOOST_UBLAS_INLINE
        matrix_slice<matrix_type> project (const slice &s1, const slice &s2) const {
            return matrix_slice<matrix_type>  (data_, s1_.compose (s1), s2_.compose (s2));
        }
#endif

        // Assignment
        BOOST_UBLAS_INLINE
        matrix_slice &operator = (const matrix_slice &ms) {
            matrix_assign<scalar_assign<value_type, value_type> > () (*this, ms); 
            return *this;
        }
        BOOST_UBLAS_INLINE
        matrix_slice &assign_temporary (matrix_slice &ms) { 
            return *this = ms;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_slice &operator = (const matrix_expression<AE> &ae) { 
            matrix_assign<scalar_assign<value_type, value_type> > () (*this, matrix<value_type> (ae)); 
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_slice &assign (const matrix_expression<AE> &ae) { 
            matrix_assign<scalar_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae); 
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_slice& operator += (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_assign<value_type, value_type> > () (*this, matrix<value_type> (*this + ae)); 
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_slice &plus_assign (const matrix_expression<AE> &ae) { 
            matrix_assign<scalar_plus_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae); 
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_slice& operator -= (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_assign<value_type, value_type> > () (*this, matrix<value_type> (*this - ae)); 
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_slice &minus_assign (const matrix_expression<AE> &ae) { 
            matrix_assign<scalar_minus_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae); 
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        matrix_slice& operator *= (const AT &at) {
            matrix_assign_scalar<scalar_multiplies_assign<value_type, AT> > () (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        matrix_slice& operator /= (const AT &at) {
            matrix_assign_scalar<scalar_divides_assign<value_type, AT> > () (*this, at);
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (matrix_slice &ms) {
            // Too unusual semantic.
            // BOOST_UBLAS_CHECK (this != &ms, external_logic ());
            if (this != &ms) {
                BOOST_UBLAS_CHECK (size1 () == ms.size1 (), bad_size ());
                BOOST_UBLAS_CHECK (size2 () == ms.size2 (), bad_size ());
                matrix_swap<scalar_swap<value_type, value_type> > () (*this, ms);
            }
        }
#ifdef BOOST_UBLAS_FRIEND_FUNCTION
        BOOST_UBLAS_INLINE
        friend void swap (matrix_slice &ms1, matrix_slice &ms2) {
            ms1.swap (ms2);
        }
#endif

#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
        typedef matrix_row_iterator<matrix_slice<matrix_type>,
                                    BOOST_UBLAS_TYPENAME matrix_type::iterator1::iterator_category> iterator1;
        typedef matrix_column_iterator<matrix_slice<matrix_type>,
                                       BOOST_UBLAS_TYPENAME matrix_type::iterator2::iterator_category> iterator2;
        typedef matrix_row_const_iterator<matrix_slice<matrix_type>,
                                          BOOST_UBLAS_TYPENAME matrix_type::const_iterator1::iterator_category> const_iterator1;
        typedef matrix_column_const_iterator<matrix_slice<matrix_type>,
                                             BOOST_UBLAS_TYPENAME matrix_type::const_iterator2::iterator_category> const_iterator2;
#ifdef BOOST_MSVC_STD_ITERATOR
        typedef reverse_iterator_base<const_iterator1, typename matrix_row<matrix_slice<matrix_type> >, typename matrix_row<matrix_slice<const_matrix_type> > > const_reverse_iterator1;
        typedef reverse_iterator_base<iterator1, typename matrix_row<matrix_slice<matrix_type> >, typename matrix_row<matrix_slice<matrix_type> > > reverse_iterator1;
        typedef reverse_iterator_base<const_iterator2, typename matrix_column<matrix_slice<matrix_type> >, typename matrix_column<matrix_slice<const_matrix_type> > > const_reverse_iterator2;
        typedef reverse_iterator_base<iterator2, typename matrix_column<matrix_slice<matrix_type> >, typename matrix_column<matrix_slice<matrix_type> > > reverse_iterator2;
#else
        typedef reverse_iterator_base<const_iterator1> const_reverse_iterator1;
        typedef reverse_iterator_base<iterator1> reverse_iterator1;
        typedef reverse_iterator_base<const_iterator2> const_reverse_iterator2;
        typedef reverse_iterator_base<iterator2> reverse_iterator2;
#endif
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
        typedef indexed_iterator1<matrix_slice<matrix_type>,
                                  BOOST_UBLAS_TYPENAME matrix_type::iterator1::iterator_category> iterator1;
        typedef indexed_iterator2<matrix_slice<matrix_type>,
                                  BOOST_UBLAS_TYPENAME matrix_type::iterator2::iterator_category> iterator2;
        typedef indexed_const_iterator1<matrix_slice<matrix_type>,
                                        BOOST_UBLAS_TYPENAME matrix_type::const_iterator1::iterator_category> const_iterator1;
        typedef indexed_const_iterator2<matrix_slice<matrix_type>,
                                        BOOST_UBLAS_TYPENAME matrix_type::const_iterator2::iterator_category> const_iterator2;
#else
        class const_iterator1;
        class iterator1;
        class const_iterator2;
        class iterator2;
#endif
#ifdef BOOST_MSVC_STD_ITERATOR
        typedef reverse_iterator_base1<const_iterator1, value_type, const_reference> const_reverse_iterator1;
        typedef reverse_iterator_base1<iterator1, value_type, reference> reverse_iterator1;
        typedef reverse_iterator_base2<const_iterator2, value_type, const_reference> const_reverse_iterator2;
        typedef reverse_iterator_base2<iterator2, value_type, reference> reverse_iterator2;
#else
        typedef reverse_iterator_base1<const_iterator1> const_reverse_iterator1;
        typedef reverse_iterator_base1<iterator1> reverse_iterator1;
        typedef reverse_iterator_base2<const_iterator2> const_reverse_iterator2;
        typedef reverse_iterator_base2<iterator2> reverse_iterator2;
#endif
#endif

        // Element lookup
        BOOST_UBLAS_INLINE
        const_iterator1 find_first1 (int rank, size_type i, size_type j) const {
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return const_iterator1 (*this, i);
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return const_iterator1 (*this, i, j);
#else
            return const_iterator1 (*this, s1_.begin () + i, s2_.begin () + j);
#endif
#endif
        }
        BOOST_UBLAS_INLINE
        iterator1 find_first1 (int rank, size_type i, size_type j) {
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return iterator1 (*this, i);
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return iterator1 (*this, i, j);
#else
            return iterator1 (*this, s1_.begin () + i, s2_.begin () + j);
#endif
#endif
        }
        BOOST_UBLAS_INLINE
        const_iterator1 find_last1 (int rank, size_type i, size_type j) const {
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return const_iterator1 (*this, i);
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return const_iterator1 (*this, i, j);
#else
            return const_iterator1 (*this, s1_.begin () + i, s2_.begin () + j);
#endif
#endif
        }
        BOOST_UBLAS_INLINE
        iterator1 find_last1 (int rank, size_type i, size_type j) {
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return iterator1 (*this, i);
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return iterator1 (*this, i, j);
#else
            return iterator1 (*this, s1_.begin () + i, s2_.begin () + j);
#endif
#endif
        }
        BOOST_UBLAS_INLINE
        const_iterator2 find_first2 (int rank, size_type i, size_type j) const {
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return const_iterator2 (*this, j);
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return const_iterator2 (*this, i, j);
#else
            return const_iterator2 (*this, s1_.begin () + i, s2_.begin () + j);
#endif
#endif
        }
        BOOST_UBLAS_INLINE
        iterator2 find_first2 (int rank, size_type i, size_type j) {
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return iterator2 (*this, j);
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return iterator2 (*this, i, j);
#else
            return iterator2 (*this, s1_.begin () + i, s2_.begin () + j);
#endif
#endif
        }
        BOOST_UBLAS_INLINE
        const_iterator2 find_last2 (int rank, size_type i, size_type j) const {
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return const_iterator2 (*this, j);
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return const_iterator2 (*this, i, j);
#else
            return const_iterator2 (*this, s1_.begin () + i, s2_.begin () + j);
#endif
#endif
        }
        BOOST_UBLAS_INLINE
        iterator2 find_last2 (int rank, size_type i, size_type j) {
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return iterator2 (*this, j);
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return iterator2 (*this, i, j);
#else
            return iterator2 (*this, s1_.begin () + i, s2_.begin () + j);
#endif
#endif
        }

        // Iterators simply are indices.

#if ! defined (BOOST_UBLAS_USE_CANONICAL_ITERATOR) && ! defined (BOOST_UBLAS_USE_INDEXED_ITERATOR)
        class const_iterator1:
            public container_const_reference<matrix_slice>,
#ifdef BOOST_UBLAS_USE_ITERATOR_BASE_TRAITS
            public iterator_base_traits<typename M::const_iterator1::iterator_category>::template
                        iterator_base<const_iterator1, value_type>::type {
#else
            public random_access_iterator_base<typename M::const_iterator1::iterator_category,
                                               const_iterator1, value_type> {
#endif
        public:
            typedef typename M::const_iterator1::iterator_category iterator_category;
            typedef typename M::const_iterator1::difference_type difference_type;
            typedef typename M::const_iterator1::value_type value_type;
            typedef typename M::const_iterator1::reference reference;
            typedef typename M::const_iterator1::pointer pointer;
            typedef const_iterator2 dual_iterator_type;
            typedef const_reverse_iterator2 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator1 ():
                container_const_reference<matrix_slice> (), it1_ (), it2_ () {}
            BOOST_UBLAS_INLINE
            const_iterator1 (const matrix_slice &ms, const const_iterator1_type &it1, const const_iterator2_type &it2):
                container_const_reference<matrix_slice> (ms), it1_ (it1), it2_ (it2) {}
            BOOST_UBLAS_INLINE
            const_iterator1 (const iterator1 &it):
                container_const_reference<matrix_slice> (it ()), it1_ (it.it1_), it2_ (it.it2_) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator1 &operator ++ () {
                ++ it1_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator1 &operator -- () {
                -- it1_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator1 &operator += (difference_type n) {
                it1_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator1 &operator -= (difference_type n) {
                it1_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const const_iterator1 &it) const {
                return it1_ - it.it1_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                return (*this) ().data () (*it1_, *it2_); 
            }

            BOOST_UBLAS_INLINE
            const_iterator2 begin () const {
                return const_iterator2 ((*this) (), it1_, it2_ ().begin ());
            }
            BOOST_UBLAS_INLINE
            const_iterator2 end () const {
                return const_iterator2 ((*this) (), it1_, it2_ ().end ()); 
            }
            BOOST_UBLAS_INLINE
            const_reverse_iterator2 rbegin () const {
                return const_reverse_iterator2 (end ());
            }
            BOOST_UBLAS_INLINE
            const_reverse_iterator2 rend () const {
                return const_reverse_iterator2 (begin ());
            }

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                return it1_.index ();
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                return it2_.index ();
            }

            // Assignment 
            BOOST_UBLAS_INLINE
            const_iterator1 &operator = (const const_iterator1 &it) {
                container_const_reference<matrix_slice>::assign (&it ());
                it1_ = it.it1_;
                it2_ = it.it2_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ == it.it1_ && it2_ == it.it2_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const const_iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ < it.it1_ && it2_ == it.it2_;
            }

        private:
            const_iterator1_type it1_;
            const_iterator2_type it2_;
        };
#endif

        BOOST_UBLAS_INLINE
        const_iterator1 begin1 () const {
            return find_first1 (0, 0, 0);
        }
        BOOST_UBLAS_INLINE
        const_iterator1 end1 () const {
            return find_last1 (0, size1 (), 0);
        }

#if ! defined (BOOST_UBLAS_USE_CANONICAL_ITERATOR) && ! defined (BOOST_UBLAS_USE_INDEXED_ITERATOR)
        class iterator1:
            public container_reference<matrix_slice>,
#ifdef BOOST_UBLAS_USE_ITERATOR_BASE_TRAITS
            public iterator_base_traits<typename M::iterator1::iterator_category>::template
                        iterator_base<iterator1, value_type>::type {
#else
            public random_access_iterator_base<typename M::iterator1::iterator_category,
                                               iterator1, value_type> {
#endif                                               
        public:
            typedef typename M::iterator1::iterator_category iterator_category;
            typedef typename M::iterator1::difference_type difference_type;
            typedef typename M::iterator1::value_type value_type;
            typedef typename M::iterator1::reference reference;
            typedef typename M::iterator1::pointer pointer;
            typedef iterator2 dual_iterator_type;
            typedef reverse_iterator2 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator1 ():
                container_reference<matrix_slice> (), it1_ (), it2_ () {}
            BOOST_UBLAS_INLINE
            iterator1 (matrix_slice &ms, const iterator1_type &it1, const iterator2_type &it2):
                container_reference<matrix_slice> (ms), it1_ (it1), it2_ (it2) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            iterator1 &operator ++ () {
                ++ it1_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator1 &operator -- () {
                -- it1_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator1 &operator += (difference_type n) {
                it1_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator1 &operator -= (difference_type n) {
                it1_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const iterator1 &it) const {
                return it1_ - it.it1_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                return (*this) ().data () (*it1_, *it2_); 
            }

            BOOST_UBLAS_INLINE
            iterator2 begin () const {
                return iterator2 ((*this) (), it1_, it2_ ().begin ());
            }
            BOOST_UBLAS_INLINE
            iterator2 end () const {
                return iterator2 ((*this) (), it1_, it2_ ().end ()); 
            }
            BOOST_UBLAS_INLINE
            reverse_iterator2 rbegin () const {
                return reverse_iterator2 (end ());
            }
            BOOST_UBLAS_INLINE
            reverse_iterator2 rend () const {
                return reverse_iterator2 (begin ());
            }

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                return it1_.index ();
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                return it2_.index ();
            }

            // Assignment 
            BOOST_UBLAS_INLINE
            iterator1 &operator = (const iterator1 &it) {
                container_reference<matrix_slice>::assign (&it ());
                it1_ = it.it1_;
                it2_ = it.it2_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ == it.it1_ && it2_ == it.it2_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ < it.it1_ && it2_ == it.it2_;
            }

        private:
            iterator1_type it1_;
            iterator2_type it2_;

            friend class const_iterator1;
        };
#endif

        BOOST_UBLAS_INLINE
        iterator1 begin1 () {
            return find_first1 (0, 0, 0);
        }
        BOOST_UBLAS_INLINE
        iterator1 end1 () {
            return find_last1 (0, size1 (), 0);
        }

#if ! defined (BOOST_UBLAS_USE_CANONICAL_ITERATOR) && ! defined (BOOST_UBLAS_USE_INDEXED_ITERATOR)
        class const_iterator2:
            public container_const_reference<matrix_slice>,
#ifdef BOOST_UBLAS_USE_ITERATOR_BASE_TRAITS
            public iterator_base_traits<typename M::const_iterator2::iterator_category>::template
                        iterator_base<const_iterator2, value_type>::type {
#else
            public random_access_iterator_base<typename M::const_iterator2::iterator_category,
                                               const_iterator2, value_type> {
#endif                                               
        public:
            typedef typename M::const_iterator2::iterator_category iterator_category;
            typedef typename M::const_iterator2::difference_type difference_type;
            typedef typename M::const_iterator2::value_type value_type;
            typedef typename M::const_iterator2::reference reference;
            typedef typename M::const_iterator2::pointer pointer;
            typedef const_iterator1 dual_iterator_type;
            typedef const_reverse_iterator1 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator2 ():
                container_const_reference<matrix_slice> (), it1_ (), it2_ () {}
            BOOST_UBLAS_INLINE
            const_iterator2 (const matrix_slice &ms, const const_iterator1_type &it1, const const_iterator2_type &it2):
                container_const_reference<matrix_slice> (ms), it1_ (it1), it2_ (it2) {}
            BOOST_UBLAS_INLINE
            const_iterator2 (const iterator2 &it):
                container_const_reference<matrix_slice> (it ()), it1_ (it.it1_), it2_ (it.it2_) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator2 &operator ++ () {
                ++ it2_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator2 &operator -- () {
                -- it2_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator2 &operator += (difference_type n) {
                it2_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator2 &operator -= (difference_type n) {
                it2_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const const_iterator2 &it) const {
                return it2_ - it.it2_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                return (*this) ().data () (*it1_, *it2_); 
            }

            BOOST_UBLAS_INLINE
            const_iterator1 begin () const {
                return const_iterator1 ((*this) (), it1_ ().begin (), it2_); 
            }
            BOOST_UBLAS_INLINE
            const_iterator1 end () const {
                return const_iterator1 ((*this) (), it1_ ().end (), it2_);
            }
            BOOST_UBLAS_INLINE
            const_reverse_iterator1 rbegin () const {
                return const_reverse_iterator1 (end ());
            }
            BOOST_UBLAS_INLINE
            const_reverse_iterator1 rend () const {
                return const_reverse_iterator1 (begin ());
            }

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                return it1_.index ();
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                return it2_.index ();
            }

            // Assignment 
            BOOST_UBLAS_INLINE
            const_iterator2 &operator = (const const_iterator2 &it) {
                container_const_reference<matrix_slice>::assign (&it ());
                it1_ = it.it1_;
                it2_ = it.it2_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ == it.it1_ && it2_ == it.it2_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const const_iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ == it.it1_ && it2_ < it.it2_;
            }

        private:
            const_iterator1_type it1_;
            const_iterator2_type it2_;
        };
#endif

        BOOST_UBLAS_INLINE
        const_iterator2 begin2 () const {
            return find_first2 (0, 0, 0);
        }
        BOOST_UBLAS_INLINE
        const_iterator2 end2 () const {
            return find_last2 (0, 0, size2 ());
        }

#if ! defined (BOOST_UBLAS_USE_CANONICAL_ITERATOR) && ! defined (BOOST_UBLAS_USE_INDEXED_ITERATOR)
        class iterator2:
            public container_reference<matrix_slice>,
#ifdef BOOST_UBLAS_USE_ITERATOR_BASE_TRAITS
            public iterator_base_traits<typename M::iterator2::iterator_category>::template
                        iterator_base<iterator2, value_type>::type {
#else
            public random_access_iterator_base<typename M::iterator2::iterator_category,
                                               iterator2, value_type> {
#endif                                               
        public:
            typedef typename M::iterator2::iterator_category iterator_category;
            typedef typename M::iterator2::difference_type difference_type;
            typedef typename M::iterator2::value_type value_type;
            typedef typename M::iterator2::reference reference;
            typedef typename M::iterator2::pointer pointer;
            typedef iterator1 dual_iterator_type;
            typedef reverse_iterator1 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator2 ():
                container_reference<matrix_slice> (), it1_ (), it2_ () {}
            BOOST_UBLAS_INLINE
            iterator2 (matrix_slice &ms, const iterator1_type &it1, const iterator2_type &it2):
                container_reference<matrix_slice> (ms), it1_ (it1), it2_ (it2) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            iterator2 &operator ++ () {
                ++ it2_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator2 &operator -- () {
                -- it2_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator2 &operator += (difference_type n) {
                it2_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator2 &operator -= (difference_type n) {
                it2_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const iterator2 &it) const {
                return it2_ - it.it2_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                return (*this) ().data () (*it1_, *it2_);
            }

            BOOST_UBLAS_INLINE
            iterator1 begin () const {
                return iterator1 ((*this) (), it1_ ().begin (), it2_); 
            }
            BOOST_UBLAS_INLINE
            iterator1 end () const {
                return iterator1 ((*this) (), it1_ ().end (), it2_); 
            }
            BOOST_UBLAS_INLINE
            reverse_iterator1 rbegin () const {
                return reverse_iterator1 (end ());
            }
            BOOST_UBLAS_INLINE
            reverse_iterator1 rend () const {
                return reverse_iterator1 (begin ());
            }

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                return it1_.index ();
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                return it2_.index ();
            }

            // Assignment 
            BOOST_UBLAS_INLINE
            iterator2 &operator = (const iterator2 &it) {
                container_reference<matrix_slice>::assign (&it ());
                it1_ = it.it1_;
                it2_ = it.it2_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ == it.it1_ && it2_ == it.it2_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ == it.it1_ && it2_ < it.it2_;
            }

        private:
            iterator1_type it1_;
            iterator2_type it2_;

            friend class const_iterator2;
        };
#endif

        BOOST_UBLAS_INLINE
        iterator2 begin2 () {
            return find_first2 (0, 0, 0);
        }
        BOOST_UBLAS_INLINE
        iterator2 end2 () {
            return find_last2 (0, 0, size2 ());
        }

        // Reverse iterators

        BOOST_UBLAS_INLINE
        const_reverse_iterator1 rbegin1 () const {
            return const_reverse_iterator1 (end1 ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator1 rend1 () const {
            return const_reverse_iterator1 (begin1 ());
        }

        BOOST_UBLAS_INLINE
        reverse_iterator1 rbegin1 () {
            return reverse_iterator1 (end1 ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator1 rend1 () {
            return reverse_iterator1 (begin1 ());
        }

        BOOST_UBLAS_INLINE
        const_reverse_iterator2 rbegin2 () const {
            return const_reverse_iterator2 (end2 ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator2 rend2 () const {
            return const_reverse_iterator2 (begin2 ());
        }

        BOOST_UBLAS_INLINE
        reverse_iterator2 rbegin2 () {
            return reverse_iterator2 (end2 ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator2 rend2 () {
            return reverse_iterator2 (begin2 ());
        }

    private:
        matrix_type &data_;
#ifdef BOOST_UBLAS_ENABLE_INDEX_SET_ALL
        slice<> s1_;
        slice<> s2_;
#else
        slice s1_;
        slice s2_;
#endif
        static matrix_type nil_;
    };

    template<class M>
    typename matrix_slice<M>::matrix_type matrix_slice<M>::nil_;

    // Projections
#ifdef BOOST_UBLAS_ENABLE_INDEX_SET_ALL
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
    template<class M>
    BOOST_UBLAS_INLINE
    matrix_slice<M> project (const matrix_slice<M> &data, const range<> &r1, const range<> &r2) {
        return data.project (r1, r2);
    }
#endif
    template<class M>
    BOOST_UBLAS_INLINE
    matrix_slice<M> project (M &data, const slice<> &s1, const slice<> &s2) {
        return matrix_slice<M> (data, s1, s2);
    }
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
    template<class M>
    BOOST_UBLAS_INLINE
    const matrix_slice<const M> project (const M &data, const slice<> &s1, const slice<> &s2) {
        return matrix_slice<const M> (data, s1, s2);
    }
    template<class M>
    BOOST_UBLAS_INLINE
    matrix_slice<M> project (const matrix_slice<M> &data, const slice<> &s1, const slice<> &s2) {
        return data.project (s1, s2);
    }
#endif
#else
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
    template<class M>
    BOOST_UBLAS_INLINE
    matrix_slice<M> project (const matrix_slice<M> &data, const range &r1, const range &r2) {
        return data.project (r1, r2);
    }
#endif
    template<class M>
    BOOST_UBLAS_INLINE
    matrix_slice<M> project (M &data, const slice &s1, const slice &s2) {
        return matrix_slice<M> (data, s1, s2);
    }
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
    template<class M>
    BOOST_UBLAS_INLINE
    const matrix_slice<const M> project (const M &data, const slice &s1, const slice &s2) {
        return matrix_slice<const M> (data, s1, s2);
    }
    template<class M>
    BOOST_UBLAS_INLINE
    matrix_slice<M> project (const matrix_slice<M> &data, const slice &s1, const slice &s2) {
        return data.project (s1, s2);
    }
#endif
#endif

    // Matrix based indirection class
    // Contributed by Toon Knapen.
    // Extended and optimized by Kresimir Fresl.
    template<class M, class IA>
    class matrix_indirect:
        public matrix_expression<matrix_indirect<M, IA> > {
    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        BOOST_UBLAS_USING matrix_expression<matrix_indirect<M, IA> >::operator ();
#endif
        typedef const M const_matrix_type;
        typedef M matrix_type;
        typedef const IA const_indirect_array_type;
        typedef IA indirect_array_type;
        typedef typename M::size_type size_type;
        typedef typename M::difference_type difference_type;
        typedef typename M::value_type value_type;
        typedef typename M::const_reference const_reference;
        typedef typename M::reference reference;
        typedef typename M::const_pointer const_pointer;
        typedef typename M::pointer pointer;
#ifdef BOOST_UBLAS_ET_CLOSURE_REFERENCE
        typedef const matrix_const_reference<const matrix_indirect<matrix_type, indirect_array_type> > const_closure_type;
        typedef matrix_reference<matrix_indirect<matrix_type, indirect_array_type> > closure_type;
#endif
#ifdef BOOST_UBLAS_ET_CLOSURE_VALUE
        typedef const matrix_indirect<matrix_type, indirect_array_type> const_closure_type;
        typedef matrix_indirect<matrix_type, indirect_array_type> closure_type;
#endif
        typedef typename IA::const_iterator const_iterator1_type;
        typedef typename IA::const_iterator iterator1_type;
        typedef typename IA::const_iterator const_iterator2_type;
        typedef typename IA::const_iterator iterator2_type;
        typedef typename storage_restrict_traits<typename M::storage_category,
                                                 dense_proxy_tag>::storage_category storage_category;
        typedef typename M::orientation_category orientation_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        matrix_indirect ():
            data_ (nil_), ia1_ (), ia2_ () {}
        BOOST_UBLAS_INLINE
        matrix_indirect (matrix_type &data, size_type size1, size_type size2):
            data_ (data), ia1_ (size1), ia2_ (size2) {}
#ifdef BOOST_UBLAS_ENABLE_INDEX_SET_ALL
        BOOST_UBLAS_INLINE
        matrix_indirect (matrix_type &data, const indirect_array_type &ia1, const indirect_array_type &ia2):
            data_ (data), ia1_ (ia1.preprocess (data.size1 ())), ia2_ (ia2.preprocess (data.size2 ())) {}
#else
        BOOST_UBLAS_INLINE
        matrix_indirect (matrix_type &data, const indirect_array_type &ia1, const indirect_array_type &ia2):
            data_ (data), ia1_ (ia1), ia2_ (ia2) {}
#endif

        // Accessors
        BOOST_UBLAS_INLINE
        size_type size1 () const {
            return ia1_.size ();
        }
        BOOST_UBLAS_INLINE
        size_type size2 () const {
            return ia2_.size ();
        }
        BOOST_UBLAS_INLINE
        const_matrix_type &data () const {
            return data_;
        }
        BOOST_UBLAS_INLINE
        matrix_type &data () {
            return data_;
        }
        BOOST_UBLAS_INLINE
        const_indirect_array_type &indirect1 () const {
            return ia1_;
        }
        BOOST_UBLAS_INLINE
        indirect_array_type &indirect1 () {
            return ia1_;
        }
        BOOST_UBLAS_INLINE
        const_indirect_array_type &indirect2 () const {
            return ia2_;
        }
        BOOST_UBLAS_INLINE
        indirect_array_type &indirect2 () {
            return ia2_;
        }

#ifdef BOOST_UBLAS_DEPRECATED
        // Resetting
        BOOST_UBLAS_INLINE
        void reset (matrix_type &data) {
            // data_ = data;
            data_.reset (data);
        }
        BOOST_UBLAS_INLINE
        void reset (matrix_type &data, const indirect_array_type &ia1, const indirect_array_type &ia2) {
            // data_ = data;
            data_.reset (data);
            ia1_ = ia1;
            ia2_ = ia2;
        }
#endif

        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i, size_type j) const {
            return data () (ia1_ (i), ia2_ (j));
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i, size_type j) {
            return data () (ia1_ (i), ia2_ (j));
        }

#ifdef BOOST_UBLAS_ENABLE_INDEX_SET_ALL
        BOOST_UBLAS_INLINE
        matrix_indirect<matrix_type, indirect_array_type> project (const range<> &r1, const range<> &r2) const {
            return matrix_indirect<matrix_type, indirect_array_type> (data_, ia1_.compose (r1), ia2_.compose (r2));
        }
        BOOST_UBLAS_INLINE
        matrix_indirect<matrix_type, indirect_array_type> project (const slice<> &s1, const slice<> &s2) const {
            return matrix_indirect<matrix_type, indirect_array_type> (data_, ia1_.compose (s1), ia2_.compose (s2));
        }
#else
        BOOST_UBLAS_INLINE
        matrix_indirect<matrix_type, indirect_array_type> project (const range &r1, const range &r2) const {
            return matrix_indirect<matrix_type, indirect_array_type> (data_, ia1_.compose (r1), ia2_.compose (r2));
        }
        BOOST_UBLAS_INLINE
        matrix_indirect<matrix_type, indirect_array_type> project (const slice &s1, const slice &s2) const {
            return matrix_indirect<matrix_type, indirect_array_type> (data_, ia1_.compose (s1), ia2_.compose (s2));
        }
#endif
        BOOST_UBLAS_INLINE
        matrix_indirect<matrix_type, indirect_array_type> project (const indirect_array_type &ia1, const indirect_array_type &ia2) const {
            return matrix_indirect<matrix_type, indirect_array_type> (data_, ia1_.compose (ia1), ia2_.compose (ia2));
        }

        // Assignment
        BOOST_UBLAS_INLINE
        matrix_indirect &operator = (const matrix_indirect &mi) {
            matrix_assign<scalar_assign<value_type, value_type> > () (*this, mi);
            return *this;
        }
        BOOST_UBLAS_INLINE
        matrix_indirect &assign_temporary (matrix_indirect &mi) {
            return *this = mi;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_indirect &operator = (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_assign<value_type, value_type> > () (*this, matrix<value_type> (ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_indirect &assign (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_indirect& operator += (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_assign<value_type, value_type> > () (*this, matrix<value_type> (*this + ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_indirect &plus_assign (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_plus_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_indirect& operator -= (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_assign<value_type, value_type> > () (*this, matrix<value_type> (*this - ae));
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        matrix_indirect &minus_assign (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_minus_assign<value_type, BOOST_UBLAS_TYPENAME AE::value_type> > () (*this, ae);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        matrix_indirect& operator *= (const AT &at) {
            matrix_assign_scalar<scalar_multiplies_assign<value_type, AT> > () (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        matrix_indirect& operator /= (const AT &at) {
            matrix_assign_scalar<scalar_divides_assign<value_type, AT> > () (*this, at);
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (matrix_indirect &mi) {
            // Too unusual semantic.
            // BOOST_UBLAS_CHECK (this != &mi, external_logic ());
            if (this != &mi) {
                BOOST_UBLAS_CHECK (size1 () == mi.size1 (), bad_size ());
                BOOST_UBLAS_CHECK (size2 () == mi.size2 (), bad_size ());
                matrix_swap<scalar_swap<value_type, value_type> > () (*this, mi);
            }
        }
#ifdef BOOST_UBLAS_FRIEND_FUNCTION
        BOOST_UBLAS_INLINE
        friend void swap (matrix_indirect &mi1, matrix_indirect &mi2) {
            mi1.swap (mi2);
        }
#endif

#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
        typedef matrix_row_iterator<matrix_indirect<matrix_type, indirect_array_type>,
                                    BOOST_UBLAS_TYPENAME matrix_type::iterator1::iterator_category> iterator1;
        typedef matrix_column_iterator<matrix_indirect<matrix_type, indirect_array_type>,
                                       BOOST_UBLAS_TYPENAME matrix_type::iterator2::iterator_category> iterator2;
        typedef matrix_row_const_iterator<matrix_indirect<matrix_type, indirect_array_type>,
                                          BOOST_UBLAS_TYPENAME matrix_type::const_iterator1::iterator_category> const_iterator1;
        typedef matrix_column_const_iterator<matrix_indirect<matrix_type, indirect_array_type>,
                                             BOOST_UBLAS_TYPENAME matrix_type::const_iterator2::iterator_category> const_iterator2;
#ifdef BOOST_MSVC_STD_ITERATOR
        typedef reverse_iterator_base<const_iterator1, typename matrix_row<matrix_indirect<matrix_type, indirect_array_type> >, typename matrix_row<matrix_indirect<const_matrix_type, const_indirect_array_type> > > const_reverse_iterator1;
        typedef reverse_iterator_base<iterator1, typename matrix_row<matrix_indirect<matrix_type, indirect_array_type> >, typename matrix_row<matrix_indirect<matrix_type, indirect_array_type> > > reverse_iterator1;
        typedef reverse_iterator_base<const_iterator2, typename matrix_column<matrix_indirect<matrix_type, indirect_array_type> >, typename matrix_column<matrix_indirect<const_matrix_type, const_indirect_array_type> > > const_reverse_iterator2;
        typedef reverse_iterator_base<iterator2, typename matrix_column<matrix_indirect<matrix_type, indirect_array_type> >, typename matrix_column<matrix_indirect<matrix_type, indirect_array_type> > > reverse_iterator2;
#else
        typedef reverse_iterator_base<const_iterator1> const_reverse_iterator1;
        typedef reverse_iterator_base<iterator1> reverse_iterator1;
        typedef reverse_iterator_base<const_iterator2> const_reverse_iterator2;
        typedef reverse_iterator_base<iterator2> reverse_iterator2;
#endif
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
        typedef indexed_iterator1<matrix_indirect<matrix_type, indirect_array_type>,
                                  BOOST_UBLAS_TYPENAME matrix_type::iterator1::iterator_category> iterator1;
        typedef indexed_iterator2<matrix_indirect<matrix_type, indirect_array_type>,
                                  BOOST_UBLAS_TYPENAME matrix_type::iterator2::iterator_category> iterator2;
        typedef indexed_const_iterator1<matrix_indirect<matrix_type, indirect_array_type>,
                                        BOOST_UBLAS_TYPENAME matrix_type::const_iterator1::iterator_category> const_iterator1;
        typedef indexed_const_iterator2<matrix_indirect<matrix_type, indirect_array_type>,
                                        BOOST_UBLAS_TYPENAME matrix_type::const_iterator2::iterator_category> const_iterator2;
#else
        class const_iterator1;
        class iterator1;
        class const_iterator2;
        class iterator2;
#endif
#ifdef BOOST_MSVC_STD_ITERATOR
        typedef reverse_iterator_base1<const_iterator1, value_type, const_reference> const_reverse_iterator1;
        typedef reverse_iterator_base1<iterator1, value_type, reference> reverse_iterator1;
        typedef reverse_iterator_base2<const_iterator2, value_type, const_reference> const_reverse_iterator2;
        typedef reverse_iterator_base2<iterator2, value_type, reference> reverse_iterator2;
#else
        typedef reverse_iterator_base1<const_iterator1> const_reverse_iterator1;
        typedef reverse_iterator_base1<iterator1> reverse_iterator1;
        typedef reverse_iterator_base2<const_iterator2> const_reverse_iterator2;
        typedef reverse_iterator_base2<iterator2> reverse_iterator2;
#endif
#endif

        // Element lookup
        BOOST_UBLAS_INLINE
        const_iterator1 find_first1 (int rank, size_type i, size_type j) const {
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return const_iterator1 (*this, i);
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return const_iterator1 (*this, i, j);
#else
            return const_iterator1 (*this, ia1_.begin () + i, ia2_.begin () + j);
#endif
#endif
        }
        BOOST_UBLAS_INLINE
        iterator1 find_first1 (int rank, size_type i, size_type j) {
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return iterator1 (*this, i);
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return iterator1 (*this, i, j);
#else
            return iterator1 (*this, ia1_.begin () + i, ia2_.begin () + j);
#endif
#endif
        }
        BOOST_UBLAS_INLINE
        const_iterator1 find_last1 (int rank, size_type i, size_type j) const {
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return const_iterator1 (*this, i);
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return const_iterator1 (*this, i, j);
#else
            return const_iterator1 (*this, ia1_.begin () + i, ia2_.begin () + j);
#endif
#endif
        }
        BOOST_UBLAS_INLINE
        iterator1 find_last1 (int rank, size_type i, size_type j) {
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return iterator1 (*this, i);
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return iterator1 (*this, i, j);
#else
            return iterator1 (*this, ia1_.begin () + i, ia2_.begin () + j);
#endif
#endif
        }
        BOOST_UBLAS_INLINE
        const_iterator2 find_first2 (int rank, size_type i, size_type j) const {
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return const_iterator2 (*this, j);
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return const_iterator2 (*this, i, j);
#else
            return const_iterator2 (*this, ia1_.begin () + i, ia2_.begin () + j);
#endif
#endif
        }
        BOOST_UBLAS_INLINE
        iterator2 find_first2 (int rank, size_type i, size_type j) {
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return iterator2 (*this, j);
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return iterator2 (*this, i, j);
#else
            return iterator2 (*this, ia1_.begin () + i, ia2_.begin () + j);
#endif
#endif
        }
        BOOST_UBLAS_INLINE
        const_iterator2 find_last2 (int rank, size_type i, size_type j) const {
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return const_iterator2 (*this, j);
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return const_iterator2 (*this, i, j);
#else
            return const_iterator2 (*this, ia1_.begin () + i, ia2_.begin () + j);
#endif
#endif
        }
        BOOST_UBLAS_INLINE
        iterator2 find_last2 (int rank, size_type i, size_type j) {
#ifdef BOOST_UBLAS_USE_CANONICAL_ITERATOR
            return iterator2 (*this, j);
#else
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
            return iterator2 (*this, i, j);
#else
            return iterator2 (*this, ia1_.begin () + i, ia2_.begin () + j);
#endif
#endif
        }

        // Iterators simply are indices.

#if ! defined (BOOST_UBLAS_USE_CANONICAL_ITERATOR) && ! defined (BOOST_UBLAS_USE_INDEXED_ITERATOR)
        class const_iterator1:
            public container_const_reference<matrix_indirect>,
#ifdef BOOST_UBLAS_USE_ITERATOR_BASE_TRAITS
            public iterator_base_traits<typename M::const_iterator1::iterator_category>::template
                        iterator_base<const_iterator1, value_type>::type {
#else
            public random_access_iterator_base<typename M::const_iterator1::iterator_category,
                                               const_iterator1, value_type> {
#endif
        public:
            typedef typename M::const_iterator1::iterator_category iterator_category;
            typedef typename M::const_iterator1::difference_type difference_type;
            typedef typename M::const_iterator1::value_type value_type;
            typedef typename M::const_iterator1::reference reference;
            typedef typename M::const_iterator1::pointer pointer;
            typedef const_iterator2 dual_iterator_type;
            typedef const_reverse_iterator2 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator1 ():
                container_const_reference<matrix_indirect> (), it1_ (), it2_ () {}
            BOOST_UBLAS_INLINE
            const_iterator1 (const matrix_indirect &mi, const const_iterator1_type &it1, const const_iterator2_type &it2):
                container_const_reference<matrix_indirect> (mi), it1_ (it1), it2_ (it2) {}
            BOOST_UBLAS_INLINE
            const_iterator1 (const iterator1 &it):
                container_const_reference<matrix_indirect> (it ()), it1_ (it.it1_), it2_ (it.it2_) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator1 &operator ++ () {
                ++ it1_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator1 &operator -- () {
                -- it1_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator1 &operator += (difference_type n) {
                it1_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator1 &operator -= (difference_type n) {
                it1_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const const_iterator1 &it) const {
                return it1_ - it.it1_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                return (*this) ().data () (*it1_, *it2_);
            }

            BOOST_UBLAS_INLINE
            const_iterator2 begin () const {
                return const_iterator2 ((*this) (), it1_, it2_ ().begin ());
            }
            BOOST_UBLAS_INLINE
            const_iterator2 end () const {
                return const_iterator2 ((*this) (), it1_, it2_ ().end ());
            }
            BOOST_UBLAS_INLINE
            const_reverse_iterator2 rbegin () const {
                return const_reverse_iterator2 (end ());
            }
            BOOST_UBLAS_INLINE
            const_reverse_iterator2 rend () const {
                return const_reverse_iterator2 (begin ());
            }

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                return it1_.index ();
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                return it2_.index ();
            }

            // Assignment
            BOOST_UBLAS_INLINE
            const_iterator1 &operator = (const const_iterator1 &it) {
                container_const_reference<matrix_indirect>::assign (&it ());
                it1_ = it.it1_;
                it2_ = it.it2_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ == it.it1_ && it2_ == it.it2_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const const_iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ < it.it1_ && it2_ == it.it2_;
            }

        private:
            const_iterator1_type it1_;
            const_iterator2_type it2_;
        };
#endif

        BOOST_UBLAS_INLINE
        const_iterator1 begin1 () const {
            return find_first1 (0, 0, 0);
        }
        BOOST_UBLAS_INLINE
        const_iterator1 end1 () const {
            return find_last1 (0, size1 (), 0);
        }

#if ! defined (BOOST_UBLAS_USE_CANONICAL_ITERATOR) && ! defined (BOOST_UBLAS_USE_INDEXED_ITERATOR)
        class iterator1:
            public container_reference<matrix_indirect>,
#ifdef BOOST_UBLAS_USE_ITERATOR_BASE_TRAITS
            public iterator_base_traits<typename M::iterator1::iterator_category>::template
                        iterator_base<iterator1, value_type>::type {
#else
            public random_access_iterator_base<typename M::iterator1::iterator_category,
                                               iterator1, value_type> {
#endif
        public:
            typedef typename M::iterator1::iterator_category iterator_category;
            typedef typename M::iterator1::difference_type difference_type;
            typedef typename M::iterator1::value_type value_type;
            typedef typename M::iterator1::reference reference;
            typedef typename M::iterator1::pointer pointer;
            typedef iterator2 dual_iterator_type;
            typedef reverse_iterator2 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator1 ():
                container_reference<matrix_indirect> (), it1_ (), it2_ () {}
            BOOST_UBLAS_INLINE
            iterator1 (matrix_indirect &mi, const iterator1_type &it1, const iterator2_type &it2):
                container_reference<matrix_indirect> (mi), it1_ (it1), it2_ (it2) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            iterator1 &operator ++ () {
                ++ it1_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator1 &operator -- () {
                -- it1_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator1 &operator += (difference_type n) {
                it1_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator1 &operator -= (difference_type n) {
                it1_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const iterator1 &it) const {
                return it1_ - it.it1_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                return (*this) ().data () (*it1_, *it2_);
            }

            BOOST_UBLAS_INLINE
            iterator2 begin () const {
                return iterator2 ((*this) (), it1_, it2_ ().begin ());
            }
            BOOST_UBLAS_INLINE
            iterator2 end () const {
                return iterator2 ((*this) (), it1_, it2_ ().end ());
            }
            BOOST_UBLAS_INLINE
            reverse_iterator2 rbegin () const {
                return reverse_iterator2 (end ());
            }
            BOOST_UBLAS_INLINE
            reverse_iterator2 rend () const {
                return reverse_iterator2 (begin ());
            }

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                return it1_.index ();
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                return it2_.index ();
            }

            // Assignment
            BOOST_UBLAS_INLINE
            iterator1 &operator = (const iterator1 &it) {
                container_reference<matrix_indirect>::assign (&it ());
                it1_ = it.it1_;
                it2_ = it.it2_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ == it.it1_ && it2_ == it.it2_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ < it.it1_ && it2_ == it.it2_;
            }

        private:
            iterator1_type it1_;
            iterator2_type it2_;

            friend class const_iterator1;
        };
#endif

        BOOST_UBLAS_INLINE
        iterator1 begin1 () {
            return find_first1 (0, 0, 0);
        }
        BOOST_UBLAS_INLINE
        iterator1 end1 () {
            return find_last1 (0, size1 (), 0);
        }

#if ! defined (BOOST_UBLAS_USE_CANONICAL_ITERATOR) && ! defined (BOOST_UBLAS_USE_INDEXED_ITERATOR)
        class const_iterator2:
            public container_const_reference<matrix_indirect>,
#ifdef BOOST_UBLAS_USE_ITERATOR_BASE_TRAITS
            public iterator_base_traits<typename M::const_iterator2::iterator_category>::template
                        iterator_base<const_iterator2, value_type>::type {
#else
            public random_access_iterator_base<typename M::const_iterator2::iterator_category,
                                               const_iterator2, value_type> {
#endif
        public:
            typedef typename M::const_iterator2::iterator_category iterator_category;
            typedef typename M::const_iterator2::difference_type difference_type;
            typedef typename M::const_iterator2::value_type value_type;
            typedef typename M::const_iterator2::reference reference;
            typedef typename M::const_iterator2::pointer pointer;
            typedef const_iterator1 dual_iterator_type;
            typedef const_reverse_iterator1 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator2 ():
                container_const_reference<matrix_indirect> (), it1_ (), it2_ () {}
            BOOST_UBLAS_INLINE
            const_iterator2 (const matrix_indirect &mi, const const_iterator1_type &it1, const const_iterator2_type &it2):
                container_const_reference<matrix_indirect> (mi), it1_ (it1), it2_ (it2) {}
            BOOST_UBLAS_INLINE
            const_iterator2 (const iterator2 &it):
                container_const_reference<matrix_indirect> (it ()), it1_ (it.it1_), it2_ (it.it2_) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator2 &operator ++ () {
                ++ it2_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator2 &operator -- () {
                -- it2_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator2 &operator += (difference_type n) {
                it2_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator2 &operator -= (difference_type n) {
                it2_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const const_iterator2 &it) const {
                return it2_ - it.it2_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                return (*this) ().data () (*it1_, *it2_);
            }

            BOOST_UBLAS_INLINE
            const_iterator1 begin () const {
                return const_iterator1 ((*this) (), it1_ ().begin (), it2_);
            }
            BOOST_UBLAS_INLINE
            const_iterator1 end () const {
                return const_iterator1 ((*this) (), it1_ ().end (), it2_);
            }
            BOOST_UBLAS_INLINE
            const_reverse_iterator1 rbegin () const {
                return const_reverse_iterator1 (end ());
            }
            BOOST_UBLAS_INLINE
            const_reverse_iterator1 rend () const {
                return const_reverse_iterator1 (begin ());
            }

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                return it1_.index ();
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                return it2_.index ();
            }

            // Assignment
            BOOST_UBLAS_INLINE
            const_iterator2 &operator = (const const_iterator2 &it) {
                container_const_reference<matrix_indirect>::assign (&it ());
                it1_ = it.it1_;
                it2_ = it.it2_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ == it.it1_ && it2_ == it.it2_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const const_iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ == it.it1_ && it2_ < it.it2_;
            }

        private:
            const_iterator1_type it1_;
            const_iterator2_type it2_;
        };
#endif

        BOOST_UBLAS_INLINE
        const_iterator2 begin2 () const {
            return find_first2 (0, 0, 0);
        }
        BOOST_UBLAS_INLINE
        const_iterator2 end2 () const {
            return find_last2 (0, 0, size2 ());
        }

#if ! defined (BOOST_UBLAS_USE_CANONICAL_ITERATOR) && ! defined (BOOST_UBLAS_USE_INDEXED_ITERATOR)
        class iterator2:
            public container_reference<matrix_indirect>,
#ifdef BOOST_UBLAS_USE_ITERATOR_BASE_TRAITS
            public iterator_base_traits<typename M::iterator2::iterator_category>::template
                        iterator_base<iterator2, value_type>::type {
#else
            public random_access_iterator_base<typename M::iterator2::iterator_category,
                                               iterator2, value_type> {
#endif
        public:
            typedef typename M::iterator2::iterator_category iterator_category;
            typedef typename M::iterator2::difference_type difference_type;
            typedef typename M::iterator2::value_type value_type;
            typedef typename M::iterator2::reference reference;
            typedef typename M::iterator2::pointer pointer;
            typedef iterator1 dual_iterator_type;
            typedef reverse_iterator1 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator2 ():
                container_reference<matrix_indirect> (), it1_ (), it2_ () {}
            BOOST_UBLAS_INLINE
            iterator2 (matrix_indirect &mi, const iterator1_type &it1, const iterator2_type &it2):
                container_reference<matrix_indirect> (mi), it1_ (it1), it2_ (it2) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            iterator2 &operator ++ () {
                ++ it2_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator2 &operator -- () {
                -- it2_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator2 &operator += (difference_type n) {
                it2_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator2 &operator -= (difference_type n) {
                it2_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const iterator2 &it) const {
                return it2_ - it.it2_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                return (*this) ().data () (*it1_, *it2_);
            }

            BOOST_UBLAS_INLINE
            iterator1 begin () const {
                return iterator1 ((*this) (), it1_ ().begin (), it2_);
            }
            BOOST_UBLAS_INLINE
            iterator1 end () const {
                return iterator1 ((*this) (), it1_ ().end (), it2_);
            }
            BOOST_UBLAS_INLINE
            reverse_iterator1 rbegin () const {
                return reverse_iterator1 (end ());
            }
            BOOST_UBLAS_INLINE
            reverse_iterator1 rend () const {
                return reverse_iterator1 (begin ());
            }

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                return it1_.index ();
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                return it2_.index ();
            }

            // Assignment
            BOOST_UBLAS_INLINE
            iterator2 &operator = (const iterator2 &it) {
                container_reference<matrix_indirect>::assign (&it ());
                it1_ = it.it1_;
                it2_ = it.it2_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ == it.it1_ && it2_ == it.it2_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it1_ == it.it1_ && it2_ < it.it2_;
            }

        private:
            iterator1_type it1_;
            iterator2_type it2_;

            friend class const_iterator2;
        };
#endif

        BOOST_UBLAS_INLINE
        iterator2 begin2 () {
            return find_first2 (0, 0, 0);
        }
        BOOST_UBLAS_INLINE
        iterator2 end2 () {
            return find_last2 (0, 0, size2 ());
        }

        // Reverse iterators

        BOOST_UBLAS_INLINE
        const_reverse_iterator1 rbegin1 () const {
            return const_reverse_iterator1 (end1 ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator1 rend1 () const {
            return const_reverse_iterator1 (begin1 ());
        }

        BOOST_UBLAS_INLINE
        reverse_iterator1 rbegin1 () {
            return reverse_iterator1 (end1 ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator1 rend1 () {
            return reverse_iterator1 (begin1 ());
        }

        BOOST_UBLAS_INLINE
        const_reverse_iterator2 rbegin2 () const {
            return const_reverse_iterator2 (end2 ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator2 rend2 () const {
            return const_reverse_iterator2 (begin2 ());
        }

        BOOST_UBLAS_INLINE
        reverse_iterator2 rbegin2 () {
            return reverse_iterator2 (end2 ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator2 rend2 () {
            return reverse_iterator2 (begin2 ());
        }

    private:
        matrix_type &data_;
        indirect_array_type ia1_;
        indirect_array_type ia2_;
        static matrix_type nil_;
    };

    template<class M, class IA>
    typename matrix_indirect<M, IA>::matrix_type matrix_indirect<M, IA>::nil_;

    // Projections
#ifdef BOOST_UBLAS_ENABLE_INDEX_SET_ALL
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
    template<class M, class IA>
    BOOST_UBLAS_INLINE
    matrix_indirect<M, IA> project (const matrix_indirect<M, IA> &data, const range<> &r1, const range<> &r2) {
        return data.project (r1, r2);
    }
    template<class M, class IA>
    BOOST_UBLAS_INLINE
    matrix_indirect<M, IA> project (const matrix_indirect<M, IA> &data, const slice<> &s1, const slice<> &s2) {
        return data.project (s1, s2);
    }
#endif
#else
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
    template<class M, class IA>
    BOOST_UBLAS_INLINE
    matrix_indirect<M, IA> project (const matrix_indirect<M, IA> &data, const range &r1, const range &r2) {
        return data.project (r1, r2);
    }
    template<class M, class IA>
    BOOST_UBLAS_INLINE
    matrix_indirect<M, IA> project (const matrix_indirect<M, IA> &data, const slice &s1, const slice &s2) {
        return data.project (s1, s2);
    }
#endif
#endif
    template<class M, class IA>
    BOOST_UBLAS_INLINE
    matrix_indirect<M, IA> project (M &data, const IA &ia1, const IA &ia2) {
        return matrix_indirect<M, IA> (data, ia1, ia2);
    }
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
    template<class M, class IA>
    BOOST_UBLAS_INLINE
    const matrix_indirect<const M, IA> project (const M &data, const IA &ia1, const IA &ia2) {
        return matrix_indirect<const M, IA> (data, ia1, ia2);
    }
    template<class M, class IA>
    BOOST_UBLAS_INLINE
    matrix_indirect<M, IA> project (const matrix_indirect<M, IA> &data, const IA &ia1, const IA &ia2) {
        return data.project (ia1, ia2);
    }
#endif

}}}

#endif







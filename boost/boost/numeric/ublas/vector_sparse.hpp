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

#ifndef _BOOST_UBLAS_VECTOR_SPARSE_
#define _BOOST_UBLAS_VECTOR_SPARSE_

#include <boost/numeric/ublas/storage_sparse.hpp>
#include <boost/numeric/ublas/vector_expression.hpp>
#include <boost/numeric/ublas/detail/vector_assign.hpp>

// Iterators based on ideas of Jeremy Siek

namespace boost { namespace numeric { namespace ublas {

#ifdef BOOST_UBLAS_STRICT_VECTOR_SPARSE

    template<class V>
    class sparse_vector_element:
       public container_reference<V> {
    public:
        typedef V vector_type;
        typedef typename V::size_type size_type;
        typedef typename V::value_type value_type;
        typedef const value_type &const_reference;
        typedef value_type *pointer;

    private:
        // Proxied element operations
        void get_d () const {
            pointer p = (*this) ().find_element (i_);
            if (p)
                d_ = *p;
            else
                d_ = value_type/*zero*/();
        }

        void set (const value_type &s) const {
            pointer p = (*this) ().find_element (i_);
            if (!p)
                (*this) ().insert_element (i_, s);
            else
                *p = s;
        }
        
    public:   
        // Construction and destruction
        sparse_vector_element (vector_type &v, size_type i):
            container_reference<vector_type> (v), i_ (i) {
        }
        BOOST_UBLAS_INLINE
        sparse_vector_element (const sparse_vector_element &p):
            container_reference<vector_type> (p), i_ (p.i_), d_ (p.d_) {}
        BOOST_UBLAS_INLINE
        ~sparse_vector_element () {
        }

        // Assignment
        BOOST_UBLAS_INLINE
        sparse_vector_element &operator = (const sparse_vector_element &p) {
            // Overide the implict copy assignment
            p.get_d ();
            set (p.d_);
            return *this;
        }
        template<class D>
        BOOST_UBLAS_INLINE
        sparse_vector_element &operator = (const D &d) {
            set (d);
            return *this;
        }
        template<class D>
        BOOST_UBLAS_INLINE
        sparse_vector_element &operator += (const D &d) {
            get_d ();
            d_ += d;
            set (d_);
            return *this;
        }
        template<class D>
        BOOST_UBLAS_INLINE
        sparse_vector_element &operator -= (const D &d) {
            get_d ();
            d_ -= d;
            set (d_);
            return *this;
        }
        template<class D>
        BOOST_UBLAS_INLINE
        sparse_vector_element &operator *= (const D &d) {
            get_d ();
            d_ *= d;
            set (d_);
            return *this;
        }
        template<class D>
        BOOST_UBLAS_INLINE
        sparse_vector_element &operator /= (const D &d) {
            get_d ();
            d_ /= d;
            set (d_);
            return *this;
        }

        // Comparison
        template<class D>
        BOOST_UBLAS_INLINE
        bool operator == (const D &d) const {
            get_d ();
            return d_ == d;
        }
        template<class D>
        BOOST_UBLAS_INLINE
        bool operator != (const D &d) const {
            get_d ();
            return d_ != d;
        }

        // Conversion - weak link in proxy as d_ is not a perfect alias for the element
        BOOST_UBLAS_INLINE
        operator const_reference () const {
            get_d ();
            return d_;
        }

        // Conversion to reference - may be invalidated
        BOOST_UBLAS_INLINE
        value_type& ref () const {
            pointer p = (*this) ().find_element (i_);
            if (!p)
                (*this) ().insert_element (i_, value_type/*zero*/());
            return *p;
        }

    private:
        size_type i_;
        mutable value_type d_;
    };

    /*
     * Generalise explicit reference access
     */
    namespace detail {
        template <class R>
        struct element_reference {
            typedef R& reference;
            static reference get_reference (reference r)
            {
                return r;
            }
        };
        template <class V>
        struct element_reference<sparse_vector_element<V> > {
            typedef typename V::value_type& reference;
            static reference get_reference (const sparse_vector_element<V>& sve)
            {
                return sve.ref ();
            }
        };
    }
    template <class VER>
    typename detail::element_reference<VER>::reference ref (VER& ver) {
        return detail::element_reference<VER>::get_reference (ver);
    }
    template <class VER>
    typename detail::element_reference<VER>::reference ref (const VER& ver) {
        return detail::element_reference<VER>::get_reference (ver);
    }


    template<class V>
    struct type_traits<sparse_vector_element<V> > {
        typedef typename V::value_type element_type;
        typedef type_traits<sparse_vector_element<V> > self_type;
        typedef typename type_traits<element_type>::value_type value_type;
        typedef typename type_traits<element_type>::const_reference const_reference;
        typedef sparse_vector_element<V> reference;
        typedef typename type_traits<element_type>::real_type real_type;
        typedef typename type_traits<element_type>::precision_type precision_type;

        static const unsigned plus_complexity = type_traits<element_type>::plus_complexity;
        static const unsigned multiplies_complexity = type_traits<element_type>::multiplies_complexity;

        static
        BOOST_UBLAS_INLINE
        real_type real (const_reference t) {
            return type_traits<element_type>::real (t);
        }
        static
        BOOST_UBLAS_INLINE
        real_type imag (const_reference t) {
            return type_traits<element_type>::imag (t);
        }
        static
        BOOST_UBLAS_INLINE
        value_type conj (const_reference t) {
            return type_traits<element_type>::conj (t);
        }

        static
        BOOST_UBLAS_INLINE
        real_type abs (const_reference t) {
            return type_traits<element_type>::abs (t);
        }
        static
        BOOST_UBLAS_INLINE
        value_type sqrt (const_reference t) {
            return type_traits<element_type>::sqrt (t);
        }

        static
        BOOST_UBLAS_INLINE
        real_type norm_1 (const_reference t) {
            return type_traits<element_type>::norm_1 (t);
        }
        static
        BOOST_UBLAS_INLINE
        real_type norm_2 (const_reference t) {
            return type_traits<element_type>::norm_2 (t);
        }
        static
        BOOST_UBLAS_INLINE
        real_type norm_inf (const_reference t) {
            return type_traits<element_type>::norm_inf (t);
        }

        static
        BOOST_UBLAS_INLINE
        bool equals (const_reference t1, const_reference t2) {
            return type_traits<element_type>::equals (t1, t2);
        }
    };

    template<class V1, class T2>
    struct promote_traits<sparse_vector_element<V1>, T2> {
        typedef typename promote_traits<typename sparse_vector_element<V1>::value_type, T2>::promote_type promote_type;
    };
    template<class T1, class V2>
    struct promote_traits<T1, sparse_vector_element<V2> > {
        typedef typename promote_traits<T1, typename sparse_vector_element<V2>::value_type>::promote_type promote_type;
    };
    template<class V1, class V2>
    struct promote_traits<sparse_vector_element<V1>, sparse_vector_element<V2> > {
        typedef typename promote_traits<typename sparse_vector_element<V1>::value_type,
                                        typename sparse_vector_element<V2>::value_type>::promote_type promote_type;
    };

#endif


    // Index map based sparse vector class
    template<class T, class A>
    class mapped_vector:
        public vector_expression<mapped_vector<T, A> > {

        typedef T &true_reference;
        typedef T *pointer;
        typedef const T *const_pointer;
        typedef mapped_vector<T, A> self_type;
    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        using vector_expression<self_type>::operator ();
#endif
        typedef typename A::size_type size_type;
        typedef typename A::difference_type difference_type;
        typedef T value_type;
        typedef A array_type;
        typedef const value_type &const_reference;
#ifndef BOOST_UBLAS_STRICT_VECTOR_SPARSE
        typedef typename detail::map_traits<A,T>::reference reference;
#else
        typedef sparse_vector_element<self_type> reference;
#endif
        typedef const vector_reference<const self_type> const_closure_type;
        typedef vector_reference<self_type> closure_type;
        typedef self_type vector_temporary_type;
        typedef sparse_tag storage_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        mapped_vector ():
            vector_expression<self_type> (),
            size_ (0), data_ () {}
        BOOST_UBLAS_INLINE
        mapped_vector (size_type size, size_type non_zeros = 0):
            vector_expression<self_type> (),
            size_ (size), data_ () {
            detail::map_reserve (data(), restrict_capacity (non_zeros));
        }
        BOOST_UBLAS_INLINE
        mapped_vector (const mapped_vector &v):
            vector_expression<self_type> (),
            size_ (v.size_), data_ (v.data_) {}
        template<class AE>
        BOOST_UBLAS_INLINE
        mapped_vector (const vector_expression<AE> &ae, size_type non_zeros = 0):
            vector_expression<self_type> (),
            size_ (ae ().size ()), data_ () {
            detail::map_reserve (data(), restrict_capacity (non_zeros));
            vector_assign<scalar_assign> (*this, ae);
        }

        // Accessors
        BOOST_UBLAS_INLINE
        size_type size () const {
            return size_;
        }
        BOOST_UBLAS_INLINE
        size_type nnz_capacity () const {
            return detail::map_capacity (data ());
        }
        BOOST_UBLAS_INLINE
        size_type nnz () const {
            return data (). size ();
        }

        // Storage accessors
        BOOST_UBLAS_INLINE
        const array_type &data () const {
            return data_;
        }
        BOOST_UBLAS_INLINE
        array_type &data () {
            return data_;
        }

        // Resizing
    private:
        BOOST_UBLAS_INLINE
        size_type restrict_capacity (size_type non_zeros) const {
            non_zeros = (std::min) (non_zeros, size_);
            return non_zeros;
        }
    public:
        BOOST_UBLAS_INLINE
        void resize (size_type size, bool preserve = true) {
            size_ = size;
            if (preserve) {
                data ().erase (data ().lower_bound(size_), data ().end());
            }
            else {
                data ().clear ();
            }
        }

        // Reserving
        BOOST_UBLAS_INLINE
        void reserve (size_type non_zeros = 0, bool preserve = true) {
            detail::map_reserve (data (), restrict_capacity (non_zeros));
        }

        // Element support
        BOOST_UBLAS_INLINE
        pointer find_element (size_type i) {
            return const_cast<pointer> (const_cast<const self_type&>(*this).find_element (i));
        }
        BOOST_UBLAS_INLINE
        const_pointer find_element (size_type i) const {
            const_subiterator_type it (data ().find (i));
            if (it == data ().end ())
                return 0;
            BOOST_UBLAS_CHECK ((*it).first == i, internal_logic ());   // broken map
            return &(*it).second;
        }

        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i) const {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            const_subiterator_type it (data ().find (i));
            if (it == data ().end ())
                return zero_;
            BOOST_UBLAS_CHECK ((*it).first == i, internal_logic ());   // broken map
            return (*it).second;
        }
        BOOST_UBLAS_INLINE
        true_reference ref (size_type i) {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            std::pair<subiterator_type, bool> ii (data ().insert (typename array_type::value_type (i, value_type/*zero*/())));
            BOOST_UBLAS_CHECK ((ii.first)->first == i, internal_logic ());   // broken map
            return (ii.first)->second;
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i) {
#ifndef BOOST_UBLAS_STRICT_VECTOR_SPARSE
            return ref (i);
#else
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            return reference (*this, i);
#endif
        }

        BOOST_UBLAS_INLINE
        const_reference operator [] (size_type i) const {
            return (*this) (i);
        }
        BOOST_UBLAS_INLINE
        reference operator [] (size_type i) {
            return (*this) (i);
        }

        // Element assignment
        BOOST_UBLAS_INLINE
        true_reference insert_element (size_type i, const_reference t) {
            std::pair<subiterator_type, bool> ii = data ().insert (typename array_type::value_type (i, t));
            BOOST_UBLAS_CHECK (ii.second, bad_index ());        // duplicate element
            BOOST_UBLAS_CHECK ((ii.first)->first == i, internal_logic ());   // broken map
            if (!ii.second)     // existing element
                (ii.first)->second = t;
            return (ii.first)->second;
        }
        BOOST_UBLAS_INLINE
        void erase_element (size_type i) {
            subiterator_type it = data ().find (i);
            if (it == data ().end ())
                return;
            data ().erase (it);
        }
        
        // Zeroing
        BOOST_UBLAS_INLINE
        void clear () {
            data ().clear ();
        }

        // Assignment
        BOOST_UBLAS_INLINE
        mapped_vector &operator = (const mapped_vector &v) {
            if (this != &v) {
                size_ = v.size_;
                data () = v.data ();
            }
            return *this;
        }
        BOOST_UBLAS_INLINE
        mapped_vector &assign_temporary (mapped_vector &v) {
            swap (v);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        mapped_vector &operator = (const vector_expression<AE> &ae) {
            self_type temporary (ae, detail::map_capacity (data()));
            return assign_temporary (temporary);
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        mapped_vector &assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        mapped_vector &operator += (const vector_expression<AE> &ae) {
            self_type temporary (*this + ae, detail::map_capacity (data()));
            return assign_temporary (temporary);
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        mapped_vector &plus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_plus_assign> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        mapped_vector &operator -= (const vector_expression<AE> &ae) {
            self_type temporary (*this - ae, detail::map_capacity (data()));
            return assign_temporary (temporary);
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        mapped_vector &minus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_minus_assign> (*this, ae);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        mapped_vector &operator *= (const AT &at) {
            vector_assign_scalar<scalar_multiplies_assign> (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        mapped_vector &operator /= (const AT &at) {
            vector_assign_scalar<scalar_divides_assign> (*this, at);
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (mapped_vector &v) {
            if (this != &v) {
                std::swap (size_, v.size_);
                data ().swap (v.data ());
            }
        }
        BOOST_UBLAS_INLINE
        friend void swap (mapped_vector &v1, mapped_vector &v2) {
            v1.swap (v2);
        }

        // Iterator types
    private:
        // Use storage iterator
        typedef typename A::const_iterator const_subiterator_type;
        typedef typename A::iterator subiterator_type;

        BOOST_UBLAS_INLINE
        true_reference at_element (size_type i) {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            subiterator_type it (data ().find (i));
            BOOST_UBLAS_CHECK (it != data ().end(), bad_index ());
            BOOST_UBLAS_CHECK ((*it).first == i, internal_logic ());   // broken map
            return it->second;
        }

    public:
        class const_iterator;
        class iterator;

        // Element lookup
        // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.    
        const_iterator find (size_type i) const {
            return const_iterator (*this, data ().lower_bound (i));
        }
        // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.    
        iterator find (size_type i) {
            return iterator (*this, data ().lower_bound (i));
        }


        class const_iterator:
            public container_const_reference<mapped_vector>,
            public bidirectional_iterator_base<sparse_bidirectional_iterator_tag,
                                               const_iterator, value_type> {
        public:
            typedef typename mapped_vector::value_type value_type;
            typedef typename mapped_vector::difference_type difference_type;
            typedef typename mapped_vector::const_reference reference;
            typedef const typename mapped_vector::pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator ():
                container_const_reference<self_type> (), it_ () {}
            BOOST_UBLAS_INLINE
            const_iterator (const self_type &v, const const_subiterator_type &it):
                container_const_reference<self_type> (v), it_ (it) {}
            BOOST_UBLAS_INLINE
            const_iterator (const iterator &it):
                container_const_reference<self_type> (it ()), it_ (it.it_) {}

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

            // Dereference
            BOOST_UBLAS_INLINE
            const_reference operator * () const {
                BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
                return (*it_).second;
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                BOOST_UBLAS_CHECK (*this != (*this) ().end (), bad_index ());
                BOOST_UBLAS_CHECK ((*it_).first < (*this) ().size (), bad_index ());
                return (*it_).first;
            }

            // Assignment
            BOOST_UBLAS_INLINE
            const_iterator &operator = (const const_iterator &it) {
                container_const_reference<self_type>::assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ == it.it_;
            }

        private:
            const_subiterator_type it_;
        };

        BOOST_UBLAS_INLINE
        const_iterator begin () const {
            return const_iterator (*this, data ().begin ());
        }
        BOOST_UBLAS_INLINE
        const_iterator end () const {
            return const_iterator (*this, data ().end ());
        }

        class iterator:
            public container_reference<mapped_vector>,
            public bidirectional_iterator_base<sparse_bidirectional_iterator_tag,
                                               iterator, value_type> {
        public:
            typedef typename mapped_vector::value_type value_type;
            typedef typename mapped_vector::difference_type difference_type;
            typedef typename mapped_vector::true_reference reference;
            typedef typename mapped_vector::pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator ():
                container_reference<self_type> (), it_ () {}
            BOOST_UBLAS_INLINE
            iterator (self_type &v, const subiterator_type &it):
                container_reference<self_type> (v), it_ (it) {}

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

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
                return (*it_).second;
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                BOOST_UBLAS_CHECK (*this != (*this) ().end (), bad_index ());
                BOOST_UBLAS_CHECK ((*it_).first < (*this) ().size (), bad_index ());
                return (*it_).first;
            }

            // Assignment
            BOOST_UBLAS_INLINE
            iterator &operator = (const iterator &it) {
                container_reference<self_type>::assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ == it.it_;
            }

        private:
            subiterator_type it_;

            friend class const_iterator;
        };

        BOOST_UBLAS_INLINE
        iterator begin () {
            return iterator (*this, data ().begin ());
        }
        BOOST_UBLAS_INLINE
        iterator end () {
            return iterator (*this, data ().end ());
        }

        // Reverse iterator
        typedef reverse_iterator_base<const_iterator> const_reverse_iterator;
        typedef reverse_iterator_base<iterator> reverse_iterator;

        BOOST_UBLAS_INLINE
        const_reverse_iterator rbegin () const {
            return const_reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator rend () const {
            return const_reverse_iterator (begin ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator rbegin () {
            return reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator rend () {
            return reverse_iterator (begin ());
        }

    private:
        size_type size_;
        array_type data_;
        static const value_type zero_;
    };

    template<class T, class A>
    const typename mapped_vector<T, A>::value_type mapped_vector<T, A>::zero_ (0);


    // Compressed array based sparse vector class
    // Thanks to Kresimir Fresl for extending this to cover different index bases.
    template<class T, std::size_t IB, class IA, class TA>
    class compressed_vector:
        public vector_expression<compressed_vector<T, IB, IA, TA> > {

        typedef T &true_reference;
        typedef T *pointer;
        typedef const T *const_pointer;
        typedef compressed_vector<T, IB, IA, TA> self_type;
    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        using vector_expression<self_type>::operator ();
#endif
        // ISSUE require type consistency check
        // is_convertable (IA::size_type, TA::size_type)
        typedef typename IA::value_type size_type;
        typedef typename IA::difference_type difference_type;
        typedef T value_type;
        typedef const T &const_reference;
#ifndef BOOST_UBLAS_STRICT_VECTOR_SPARSE
        typedef T &reference;
#else
        typedef sparse_vector_element<self_type> reference;
#endif
        typedef IA index_array_type;
        typedef TA value_array_type;
        typedef const vector_reference<const self_type> const_closure_type;
        typedef vector_reference<self_type> closure_type;
        typedef self_type vector_temporary_type;
        typedef sparse_tag storage_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        compressed_vector ():
            vector_expression<self_type> (),
            size_ (0), capacity_ (restrict_capacity (0)), filled_ (0),
            index_data_ (capacity_), value_data_ (capacity_) {
            storage_invariants ();
        }
        explicit BOOST_UBLAS_INLINE
        compressed_vector (size_type size, size_type non_zeros = 0):
            vector_expression<self_type> (),
            size_ (size), capacity_ (restrict_capacity (non_zeros)), filled_ (0),
            index_data_ (capacity_), value_data_ (capacity_) {
        storage_invariants ();
        }
        BOOST_UBLAS_INLINE
        compressed_vector (const compressed_vector &v):
            vector_expression<self_type> (),
            size_ (v.size_), capacity_ (v.capacity_), filled_ (v.filled_),
            index_data_ (v.index_data_), value_data_ (v.value_data_) {
            storage_invariants ();
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        compressed_vector (const vector_expression<AE> &ae, size_type non_zeros = 0):
            vector_expression<self_type> (),
            size_ (ae ().size ()), capacity_ (restrict_capacity (non_zeros)), filled_ (0),
            index_data_ (capacity_), value_data_ (capacity_) {
            storage_invariants ();
            vector_assign<scalar_assign> (*this, ae);
        }

        // Accessors
        BOOST_UBLAS_INLINE
        size_type size () const {
            return size_;
        }
        BOOST_UBLAS_INLINE
        size_type nnz_capacity () const {
            return capacity_;
        }
        BOOST_UBLAS_INLINE
        size_type nnz () const {
            return filled_;
        }

        // Storage accessors
        BOOST_UBLAS_INLINE
        static size_type index_base () {
            return IB;
        }
        BOOST_UBLAS_INLINE
        typename index_array_type::size_type filled () const {
            return filled_;
        }
        BOOST_UBLAS_INLINE
        const index_array_type &index_data () const {
            return index_data_;
        }
        BOOST_UBLAS_INLINE
        const value_array_type &value_data () const {
            return value_data_;
        }
        BOOST_UBLAS_INLINE
        void set_filled (const typename index_array_type::size_type & filled) {
            filled_ = filled;
            storage_invariants ();
        }
        BOOST_UBLAS_INLINE
        index_array_type &index_data () {
            return index_data_;
        }
        BOOST_UBLAS_INLINE
        value_array_type &value_data () {
            return value_data_;
        }

        // Resizing
    private:
        BOOST_UBLAS_INLINE
        size_type restrict_capacity (size_type non_zeros) const {
            non_zeros = (std::max) (non_zeros, size_type (1));
            non_zeros = (std::min) (non_zeros, size_);
            return non_zeros;
        }
    public:
        BOOST_UBLAS_INLINE
        void resize (size_type size, bool preserve = true) {
            // FIXME preserve unimplemented
            BOOST_UBLAS_CHECK (!preserve, internal_logic ());
            size_ = size;
            capacity_ = restrict_capacity (capacity_);
            index_data_. resize (capacity_);
            value_data_. resize (capacity_);
            filled_ = 0;
            storage_invariants ();
        }

        // Reserving
        BOOST_UBLAS_INLINE
        void reserve (size_type non_zeros, bool preserve = true) {
            capacity_ = restrict_capacity (non_zeros);
            if (preserve) {
                index_data_. resize (capacity_, size_type ());
                value_data_. resize (capacity_, value_type ());
                filled_ = (std::min) (capacity_, filled_);
            }
            else {
                index_data_. resize (capacity_);
                value_data_. resize (capacity_);
                filled_ = 0;
            }
            storage_invariants ();
        }

        // Element support
        BOOST_UBLAS_INLINE
        pointer find_element (size_type i) {
            return const_cast<pointer> (const_cast<const self_type&>(*this).find_element (i));
        }
        BOOST_UBLAS_INLINE
        const_pointer find_element (size_type i) const {
            const_subiterator_type it (detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
            if (it == index_data_.begin () + filled_ || *it != k_based (i))
                return 0;
            return &value_data_ [it - index_data_.begin ()];
        }

        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i) const {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            const_subiterator_type it (detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
            if (it == index_data_.begin () + filled_ || *it != k_based (i))
                return zero_;
            return value_data_ [it - index_data_.begin ()];
        }
        BOOST_UBLAS_INLINE
        true_reference ref (size_type i) {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            subiterator_type it (detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
            if (it == index_data_.begin () + filled_ || *it != k_based (i))
                return insert_element (i, value_type/*zero*/());
            else
                return value_data_ [it - index_data_.begin ()];
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i) {
#ifndef BOOST_UBLAS_STRICT_VECTOR_SPARSE
            return ref (i) ;
#else
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            return reference (*this, i);
#endif
        }

        BOOST_UBLAS_INLINE
        const_reference operator [] (size_type i) const {
            return (*this) (i);
        }
        BOOST_UBLAS_INLINE
        reference operator [] (size_type i) {
            return (*this) (i);
        }

        // Element assignment
        BOOST_UBLAS_INLINE
        true_reference insert_element (size_type i, const_reference t) {
            BOOST_UBLAS_CHECK (!find_element (i), bad_index ());        // duplicate element
            if (filled_ >= capacity_)
                reserve (2 * capacity_, true);
            subiterator_type it (detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
            // ISSUE max_capacity limit due to difference_type
            typename std::iterator_traits<subiterator_type>::difference_type n = it - index_data_.begin ();
            BOOST_UBLAS_CHECK (filled_ == 0 || filled_ == typename index_array_type::size_type (n) || *it != k_based (i), internal_logic ());   // duplicate found by lower_bound
            ++ filled_;
            it = index_data_.begin () + n;
            std::copy_backward (it, index_data_.begin () + filled_ - 1, index_data_.begin () + filled_);
            *it = k_based (i);
            typename value_array_type::iterator itt (value_data_.begin () + n);
            std::copy_backward (itt, value_data_.begin () + filled_ - 1, value_data_.begin () + filled_);
            *itt = t;
            storage_invariants ();
            return *itt;
        }
        BOOST_UBLAS_INLINE
        void erase_element (size_type i) {
            subiterator_type it (detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
            typename std::iterator_traits<subiterator_type>::difference_type  n = it - index_data_.begin ();
            if (filled_ > typename index_array_type::size_type (n) && *it == k_based (i)) {
                std::copy (it + 1, index_data_.begin () + filled_, it);
                typename value_array_type::iterator itt (value_data_.begin () + n);
                std::copy (itt + 1, value_data_.begin () + filled_, itt);
                -- filled_;
            }
            storage_invariants ();
        }
        
        // Zeroing
        BOOST_UBLAS_INLINE
        void clear () {
            filled_ = 0;
            storage_invariants ();
        }

        // Assignment
        BOOST_UBLAS_INLINE
        compressed_vector &operator = (const compressed_vector &v) {
            if (this != &v) {
                size_ = v.size_;
                capacity_ = v.capacity_;
                filled_ = v.filled_;
                index_data_ = v.index_data_;
                value_data_ = v.value_data_;
            }
            storage_invariants ();
            return *this;
        }
        BOOST_UBLAS_INLINE
        compressed_vector &assign_temporary (compressed_vector &v) {
            swap (v);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        compressed_vector &operator = (const vector_expression<AE> &ae) {
            self_type temporary (ae, capacity_);
            return assign_temporary (temporary);
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        compressed_vector &assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        compressed_vector &operator += (const vector_expression<AE> &ae) {
            self_type temporary (*this + ae, capacity_);
            return assign_temporary (temporary);
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        compressed_vector &plus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_plus_assign> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        compressed_vector &operator -= (const vector_expression<AE> &ae) {
            self_type temporary (*this - ae, capacity_);
            return assign_temporary (temporary);
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        compressed_vector &minus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_minus_assign> (*this, ae);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        compressed_vector &operator *= (const AT &at) {
            vector_assign_scalar<scalar_multiplies_assign> (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        compressed_vector &operator /= (const AT &at) {
            vector_assign_scalar<scalar_divides_assign> (*this, at);
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (compressed_vector &v) {
            if (this != &v) {
                std::swap (size_, v.size_);
                std::swap (capacity_, v.capacity_);
                std::swap (filled_, v.filled_);
                index_data_.swap (v.index_data_);
                value_data_.swap (v.value_data_);
            }
            storage_invariants ();
        }
        BOOST_UBLAS_INLINE
        friend void swap (compressed_vector &v1, compressed_vector &v2) {
            v1.swap (v2);
        }

        // Back element insertion and erasure
        BOOST_UBLAS_INLINE
        void push_back (size_type i, const_reference t) {
            BOOST_UBLAS_CHECK (filled_ == 0 || index_data_ [filled_ - 1] < k_based (i), external_logic ());
            if (filled_ >= capacity_)
                reserve (2 * capacity_, true);
            BOOST_UBLAS_CHECK (filled_ < capacity_, internal_logic ());
            index_data_ [filled_] = k_based (i);
            value_data_ [filled_] = t;
            ++ filled_;
            storage_invariants ();
        }
        BOOST_UBLAS_INLINE
        void pop_back () {
            BOOST_UBLAS_CHECK (filled_ > 0, external_logic ());
            -- filled_;
            storage_invariants ();
        }

        // Iterator types
    private:
        // Use index array iterator
        typedef typename IA::const_iterator const_subiterator_type;
        typedef typename IA::iterator subiterator_type;

        BOOST_UBLAS_INLINE
        true_reference at_element (size_type i) {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            subiterator_type it (detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
            BOOST_UBLAS_CHECK (it != index_data_.begin () + filled_ && *it == k_based (i), bad_index ());
            return value_data_ [it - index_data_.begin ()];
        }

    public:
        class const_iterator;
        class iterator;

        // Element lookup
        // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.    
        const_iterator find (size_type i) const {
            return const_iterator (*this, detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
        }
        // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.    
        iterator find (size_type i) {
            return iterator (*this, detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
        }


        class const_iterator:
            public container_const_reference<compressed_vector>,
            public bidirectional_iterator_base<sparse_bidirectional_iterator_tag,
                                               const_iterator, value_type> {
        public:
            typedef typename compressed_vector::value_type value_type;
            typedef typename compressed_vector::difference_type difference_type;
            typedef typename compressed_vector::const_reference reference;
            typedef const typename compressed_vector::pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator ():
                container_const_reference<self_type> (), it_ () {}
            BOOST_UBLAS_INLINE
            const_iterator (const self_type &v, const const_subiterator_type &it):
                container_const_reference<self_type> (v), it_ (it) {}
            BOOST_UBLAS_INLINE
            const_iterator (const iterator &it):
                container_const_reference<self_type> (it ()), it_ (it.it_) {}

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

            // Dereference
            BOOST_UBLAS_INLINE
            const_reference operator * () const {
                BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
                return (*this) ().value_data_ [it_ - (*this) ().index_data_.begin ()];
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                BOOST_UBLAS_CHECK (*this != (*this) ().end (), bad_index ());
                BOOST_UBLAS_CHECK ((*this) ().zero_based (*it_) < (*this) ().size (), bad_index ());
                return (*this) ().zero_based (*it_);
            }

            // Assignment
            BOOST_UBLAS_INLINE
            const_iterator &operator = (const const_iterator &it) {
                container_const_reference<self_type>::assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ == it.it_;
            }

        private:
            const_subiterator_type it_;
        };

        BOOST_UBLAS_INLINE
        const_iterator begin () const {
            return find (0);
        }
        BOOST_UBLAS_INLINE
        const_iterator end () const {
            return find (size_);
        }

        class iterator:
            public container_reference<compressed_vector>,
            public bidirectional_iterator_base<sparse_bidirectional_iterator_tag,
                                               iterator, value_type> {
        public:
            typedef typename compressed_vector::value_type value_type;
            typedef typename compressed_vector::difference_type difference_type;
            typedef typename compressed_vector::true_reference reference;
            typedef typename compressed_vector::pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator ():
                container_reference<self_type> (), it_ () {}
            BOOST_UBLAS_INLINE
            iterator (self_type &v, const subiterator_type &it):
                container_reference<self_type> (v), it_ (it) {}

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

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
                return (*this) ().value_data_ [it_ - (*this) ().index_data_.begin ()];
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                BOOST_UBLAS_CHECK (*this != (*this) ().end (), bad_index ());
                BOOST_UBLAS_CHECK ((*this) ().zero_based (*it_) < (*this) ().size (), bad_index ());
                return (*this) ().zero_based (*it_);
            }

            // Assignment
            BOOST_UBLAS_INLINE
            iterator &operator = (const iterator &it) {
                container_reference<self_type>::assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ == it.it_;
            }

        private:
            subiterator_type it_;

            friend class const_iterator;
        };

        BOOST_UBLAS_INLINE
        iterator begin () {
            return find (0);
        }
        BOOST_UBLAS_INLINE
        iterator end () {
            return find (size_);
        }

        // Reverse iterator
        typedef reverse_iterator_base<const_iterator> const_reverse_iterator;
        typedef reverse_iterator_base<iterator> reverse_iterator;

        BOOST_UBLAS_INLINE
        const_reverse_iterator rbegin () const {
            return const_reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator rend () const {
            return const_reverse_iterator (begin ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator rbegin () {
            return reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator rend () {
            return reverse_iterator (begin ());
        }

    private:
        void storage_invariants () const
        {
            BOOST_UBLAS_CHECK (capacity_ == index_data_.size (), internal_logic ());
            BOOST_UBLAS_CHECK (capacity_ == value_data_.size (), internal_logic ());
            BOOST_UBLAS_CHECK (filled_ <= capacity_, internal_logic ());
        }

        size_type size_;
        typename index_array_type::size_type capacity_;
        typename index_array_type::size_type filled_;
        index_array_type index_data_;
        value_array_type value_data_;
        static const value_type zero_;

        BOOST_UBLAS_INLINE
        static size_type zero_based (size_type k_based_index) {
            return k_based_index - IB;
        }
        BOOST_UBLAS_INLINE
        static size_type k_based (size_type zero_based_index) {
            return zero_based_index + IB;
        }

        friend class iterator;
        friend class const_iterator;
    };

    template<class T, std::size_t IB, class IA, class TA>
    const typename compressed_vector<T, IB, IA, TA>::value_type compressed_vector<T, IB, IA, TA>::zero_ (0);


    // Coordimate array based sparse vector class
    // Thanks to Kresimir Fresl for extending this to cover different index bases.
    template<class T, std::size_t IB, class IA, class TA>
    class coordinate_vector:
        public vector_expression<coordinate_vector<T, IB, IA, TA> > {

        typedef T &true_reference;
        typedef T *pointer;
        typedef const T *const_pointer;
        typedef coordinate_vector<T, IB, IA, TA> self_type;
    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        using vector_expression<self_type>::operator ();
#endif
        // ISSUE require type consistency check
        // is_convertable (IA::size_type, TA::size_type)
        typedef typename IA::value_type size_type;
        typedef typename IA::difference_type difference_type;
        typedef T value_type;
        typedef const T &const_reference;
#ifndef BOOST_UBLAS_STRICT_VECTOR_SPARSE
        typedef T &reference;
#else
        typedef sparse_vector_element<self_type> reference;
#endif
        typedef IA index_array_type;
        typedef TA value_array_type;
        typedef const vector_reference<const self_type> const_closure_type;
        typedef vector_reference<self_type> closure_type;
        typedef self_type vector_temporary_type;
        typedef sparse_tag storage_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        coordinate_vector ():
            vector_expression<self_type> (),
            size_ (0), capacity_ (restrict_capacity (0)),
            filled_ (0), sorted_filled_ (filled_), sorted_ (true),
            index_data_ (capacity_), value_data_ (capacity_) {
            storage_invariants ();
        }
        explicit BOOST_UBLAS_INLINE
        coordinate_vector (size_type size, size_type non_zeros = 0):
            vector_expression<self_type> (),
            size_ (size), capacity_ (restrict_capacity (non_zeros)),
            filled_ (0), sorted_filled_ (filled_), sorted_ (true),
            index_data_ (capacity_), value_data_ (capacity_) {
            storage_invariants ();
        }
        BOOST_UBLAS_INLINE
        coordinate_vector (const coordinate_vector &v):
            vector_expression<self_type> (),
            size_ (v.size_), capacity_ (v.capacity_),
            filled_ (v.filled_), sorted_filled_ (v.sorted_filled_), sorted_ (v.sorted_),
            index_data_ (v.index_data_), value_data_ (v.value_data_) {
            storage_invariants ();
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        coordinate_vector (const vector_expression<AE> &ae, size_type non_zeros = 0):
            vector_expression<self_type> (),
            size_ (ae ().size ()), capacity_ (restrict_capacity (non_zeros)),
            filled_ (0), sorted_filled_ (filled_), sorted_ (true),
            index_data_ (capacity_), value_data_ (capacity_) {
            storage_invariants ();
            vector_assign<scalar_assign> (*this, ae);
        }

        // Accessors
        BOOST_UBLAS_INLINE
        size_type size () const {
            return size_;
        }
        BOOST_UBLAS_INLINE
        size_type nnz_capacity () const {
            return capacity_;
        }
        BOOST_UBLAS_INLINE
        size_type nnz () const {
            return filled_;
        }

        // Storage accessors
        BOOST_UBLAS_INLINE
        static size_type index_base () {
            return IB;
        }
        BOOST_UBLAS_INLINE
        typename index_array_type::size_type filled () const {
            return filled_;
        }
        BOOST_UBLAS_INLINE
        const index_array_type &index_data () const {
            return index_data_;
        }
        BOOST_UBLAS_INLINE
        const value_array_type &value_data () const {
            return value_data_;
        }
        BOOST_UBLAS_INLINE
        void set_filled (const typename index_array_type::size_type &sorted, const typename index_array_type::size_type &filled) {
            sorted_filled_ = sorted;
            filled_ = filled;
            storage_invariants ();
            return filled_;
        }
        BOOST_UBLAS_INLINE
        index_array_type &index_data () {
            return index_data_;
        }
        BOOST_UBLAS_INLINE
        value_array_type &value_data () {
            return value_data_;
        }

        // Resizing
    private:
        BOOST_UBLAS_INLINE
        size_type restrict_capacity (size_type non_zeros) const {
             // minimum non_zeros
             non_zeros = (std::max) (non_zeros, size_type (1));
             // ISSUE no maximum as coordinate may contain inserted duplicates
             return non_zeros;
        }
    public:
        BOOST_UBLAS_INLINE
        void resize (size_type size, bool preserve = true) {
            if (preserve)
                sort ();    // remove duplicate elements.
            capacity_ = restrict_capacity (capacity_);
            if (preserve) {
                index_data_. resize (capacity_, size_type ());
                value_data_. resize (capacity_, value_type ());
                filled_ = (std::min) (capacity_, filled_);
            }
            else {
                index_data_. resize (capacity_);
                value_data_. resize (capacity_);
                filled_ = 0;
            }
            sorted_filled_ = filled_;
            size_ = size;
            storage_invariants ();
        }
        // Reserving
        BOOST_UBLAS_INLINE
        void reserve (size_type non_zeros, bool preserve = true) {
            if (preserve)
                sort ();    // remove duplicate elements.
            capacity_ = restrict_capacity (non_zeros);
            if (preserve) {
                index_data_. resize (capacity_, size_type ());
                value_data_. resize (capacity_, value_type ());
                filled_ = (std::min) (capacity_, filled_);
                }
            else {
                index_data_. resize (capacity_);
                value_data_. resize (capacity_);
                filled_ = 0;
            }
            sorted_filled_ = filled_;
            storage_invariants ();
        }

        // Element support
        BOOST_UBLAS_INLINE
        pointer find_element (size_type i) {
            return const_cast<pointer> (const_cast<const self_type&>(*this).find_element (i));
        }
        BOOST_UBLAS_INLINE
        const_pointer find_element (size_type i) const {
            sort ();
            const_subiterator_type it (detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
            if (it == index_data_.begin () + filled_ || *it != k_based (i))
                return 0;
            return &value_data_ [it - index_data_.begin ()];
        }

        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i) const {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            sort ();
            const_subiterator_type it (detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
            if (it == index_data_.begin () + filled_ || *it != k_based (i))
                return zero_;
            return value_data_ [it - index_data_.begin ()];
        }
        BOOST_UBLAS_INLINE
        true_reference ref (size_type i) {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            sort ();
            subiterator_type it (detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
            if (it == index_data_.begin () + filled_ || *it != k_based (i))
                return insert_element (i, value_type/*zero*/());
            else
                return value_data_ [it - index_data_.begin ()];
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i) {
#ifndef BOOST_UBLAS_STRICT_VECTOR_SPARSE
            return ref (i);
#else
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            return reference (*this, i);
#endif
        }

        BOOST_UBLAS_INLINE
        const_reference operator [] (size_type i) const {
            return (*this) (i);
        }
        BOOST_UBLAS_INLINE
        reference operator [] (size_type i) {
            return (*this) (i);
        }

        // Element assignment
        BOOST_UBLAS_INLINE
        void append_element (size_type i, const_reference t) {
            if (filled_ >= capacity_)
                reserve (2 * filled_, true);
            BOOST_UBLAS_CHECK (filled_ < capacity_, internal_logic ());
            index_data_ [filled_] = k_based (i);
            value_data_ [filled_] = t;
            ++ filled_;
            sorted_ = false;
            storage_invariants ();
        }
        BOOST_UBLAS_INLINE
        true_reference insert_element (size_type i, const_reference t) {
            BOOST_UBLAS_CHECK (!find_element (i), bad_index ());        // duplicate element
            append_element (i, t);
            return value_data_ [filled_ - 1];
        }
        BOOST_UBLAS_INLINE
        void erase_element (size_type i) {
            sort ();
            subiterator_type it (detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
            typename std::iterator_traits<subiterator_type>::difference_type n = it - index_data_.begin ();
            if (filled_ > typename index_array_type::size_type (n) && *it == k_based (i)) {
                std::copy (it + 1, index_data_.begin () + filled_, it);
                typename value_array_type::iterator itt (value_data_.begin () + n);
                std::copy (itt + 1, value_data_.begin () + filled_, itt);
                -- filled_;
                sorted_filled_ = filled_;
            }
            storage_invariants ();
        }
        
        // Zeroing
        BOOST_UBLAS_INLINE
        void clear () {
            filled_ = 0;
            sorted_filled_ = filled_;
            sorted_ = true;
            storage_invariants ();
        }
        
        // Assignment
        BOOST_UBLAS_INLINE
        coordinate_vector &operator = (const coordinate_vector &v) {
            if (this != &v) {
                size_ = v.size_;
                capacity_ = v.capacity_;
                filled_ = v.filled_;
                sorted_filled_ = v.sorted_filled_;
                sorted_ = v.sorted_;
                index_data_ = v.index_data_;
                value_data_ = v.value_data_;
            }
            storage_invariants ();
            return *this;
        }
        BOOST_UBLAS_INLINE
        coordinate_vector &assign_temporary (coordinate_vector &v) {
            swap (v);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        coordinate_vector &operator = (const vector_expression<AE> &ae) {
            self_type temporary (ae, capacity_);
            return assign_temporary (temporary);
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        coordinate_vector &assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_assign> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        coordinate_vector &operator += (const vector_expression<AE> &ae) {
            self_type temporary (*this + ae, capacity_);
            return assign_temporary (temporary);
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        coordinate_vector &plus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_plus_assign> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        coordinate_vector &operator -= (const vector_expression<AE> &ae) {
            self_type temporary (*this - ae, capacity_);
            return assign_temporary (temporary);
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        coordinate_vector &minus_assign (const vector_expression<AE> &ae) {
            vector_assign<scalar_minus_assign> (*this, ae);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        coordinate_vector &operator *= (const AT &at) {
            vector_assign_scalar<scalar_multiplies_assign> (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        coordinate_vector &operator /= (const AT &at) {
            vector_assign_scalar<scalar_divides_assign> (*this, at);
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (coordinate_vector &v) {
            if (this != &v) {
                std::swap (size_, v.size_);
                std::swap (capacity_, v.capacity_);
                std::swap (filled_, v.filled_);
                std::swap (sorted_filled_, v.sorted_filled_);
                std::swap (sorted_, v.sorted_);
                index_data_.swap (v.index_data_);
                value_data_.swap (v.value_data_);
            }
            storage_invariants ();
        }
        BOOST_UBLAS_INLINE
        friend void swap (coordinate_vector &v1, coordinate_vector &v2) {
            v1.swap (v2);
        }

        // Sorting and summation of duplicates
        BOOST_UBLAS_INLINE
        void sort () const {
            if (! sorted_ && filled_ > 0) {
                typedef index_pair_array<index_array_type, value_array_type> array_pair;
                array_pair ipa (filled_, index_data_, value_data_);
                const typename array_pair::iterator iunsorted = ipa.begin () + sorted_filled_;
                // sort new elements and merge
                std::sort (iunsorted, ipa.end ());
                std::inplace_merge (ipa.begin (), iunsorted, ipa.end ());
                
                // sum duplicates with += and remove
                size_type filled = 0;
                for (size_type i = 1; i < filled_; ++ i) {
                    if (index_data_ [filled] != index_data_ [i]) {
                        ++ filled;
                        if (filled != i) {
                            index_data_ [filled] = index_data_ [i];
                            value_data_ [filled] = value_data_ [i];
                        }
                    } else {
                        value_data_ [filled] += value_data_ [i];
                    }
                }
                filled_ = filled + 1;
                sorted_filled_ = filled_;
                sorted_ = true;
                storage_invariants ();
            }
        }

        // Back element insertion and erasure
        BOOST_UBLAS_INLINE
        void push_back (size_type i, const_reference t) {
            // must maintain sort order
            BOOST_UBLAS_CHECK (sorted_ && (filled_ == 0 || index_data_ [filled_ - 1] < k_based (i)), external_logic ());
            if (filled_ >= capacity_)
                reserve (2 * filled_, true);
            BOOST_UBLAS_CHECK (filled_ < capacity_, internal_logic ());
            index_data_ [filled_] = k_based (i);
            value_data_ [filled_] = t;
            ++ filled_;
            sorted_filled_ = filled_;
            storage_invariants ();
        }
        BOOST_UBLAS_INLINE
        void pop_back () {
            // ISSUE invariants could be simpilfied if sorted required as precondition
            BOOST_UBLAS_CHECK (filled_ > 0, external_logic ());
            -- filled_;
            sorted_filled_ = (std::min) (sorted_filled_, filled_);
            sorted_ = sorted_filled_ = filled;
            storage_invariants ();
        }

        // Iterator types
    private:
        // Use index array iterator
        typedef typename IA::const_iterator const_subiterator_type;
        typedef typename IA::iterator subiterator_type;

        BOOST_UBLAS_INLINE
        true_reference at_element (size_type i) {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            sort ();
            subiterator_type it (detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
            BOOST_UBLAS_CHECK (it != index_data_.begin () + filled_ && *it == k_based (i), bad_index ());
            return value_data_ [it - index_data_.begin ()];
        }

    public:
        class const_iterator;
        class iterator;

        // Element lookup
        // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.    
        const_iterator find (size_type i) const {
            sort ();
            return const_iterator (*this, detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
        }
        // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.    
        iterator find (size_type i) {
            sort ();
            return iterator (*this, detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
        }


        class const_iterator:
            public container_const_reference<coordinate_vector>,
            public bidirectional_iterator_base<sparse_bidirectional_iterator_tag,
                                               const_iterator, value_type> {
        public:
            typedef typename coordinate_vector::value_type value_type;
            typedef typename coordinate_vector::difference_type difference_type;
            typedef typename coordinate_vector::const_reference reference;
            typedef const typename coordinate_vector::pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator ():
                container_const_reference<self_type> (), it_ () {}
            BOOST_UBLAS_INLINE
            const_iterator (const self_type &v, const const_subiterator_type &it):
                container_const_reference<self_type> (v), it_ (it) {}
            BOOST_UBLAS_INLINE
            const_iterator (const iterator &it):
                container_const_reference<self_type> (it ()), it_ (it.it_) {}

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

            // Dereference
            BOOST_UBLAS_INLINE
            const_reference operator * () const {
                BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
                return (*this) ().value_data_ [it_ - (*this) ().index_data_.begin ()];
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                BOOST_UBLAS_CHECK (*this != (*this) ().end (), bad_index ());
                BOOST_UBLAS_CHECK ((*this) ().zero_based (*it_) < (*this) ().size (), bad_index ());
                return (*this) ().zero_based (*it_);
            }

            // Assignment
            BOOST_UBLAS_INLINE
            const_iterator &operator = (const const_iterator &it) {
                container_const_reference<self_type>::assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ == it.it_;
            }

        private:
            const_subiterator_type it_;
        };

        BOOST_UBLAS_INLINE
        const_iterator begin () const {
            return find (0);
        }
        BOOST_UBLAS_INLINE
        const_iterator end () const {
            return find (size_);
        }

        class iterator:
            public container_reference<coordinate_vector>,
            public bidirectional_iterator_base<sparse_bidirectional_iterator_tag,
                                               iterator, value_type> {
        public:
            typedef typename coordinate_vector::value_type value_type;
            typedef typename coordinate_vector::difference_type difference_type;
            typedef typename coordinate_vector::true_reference reference;
            typedef typename coordinate_vector::pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator ():
                container_reference<self_type> (), it_ () {}
            BOOST_UBLAS_INLINE
            iterator (self_type &v, const subiterator_type &it):
                container_reference<self_type> (v), it_ (it) {}

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

            // Dereference
            BOOST_UBLAS_INLINE
            reference operator * () const {
                BOOST_UBLAS_CHECK (index () < (*this) ().size (), bad_index ());
                return (*this) ().value_data_ [it_ - (*this) ().index_data_.begin ()];
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                BOOST_UBLAS_CHECK (*this != (*this) ().end (), bad_index ());
                BOOST_UBLAS_CHECK ((*this) ().zero_based (*it_) < (*this) ().size (), bad_index ());
                return (*this) ().zero_based (*it_);
            }

            // Assignment
            BOOST_UBLAS_INLINE
            iterator &operator = (const iterator &it) {
                container_reference<self_type>::assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                return it_ == it.it_;
            }

        private:
            subiterator_type it_;

            friend class const_iterator;
        };

        BOOST_UBLAS_INLINE
        iterator begin () {
            return find (0);
        }
        BOOST_UBLAS_INLINE
        iterator end () {
            return find (size_);
        }

        // Reverse iterator
        typedef reverse_iterator_base<const_iterator> const_reverse_iterator;
        typedef reverse_iterator_base<iterator> reverse_iterator;

        BOOST_UBLAS_INLINE
        const_reverse_iterator rbegin () const {
            return const_reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator rend () const {
            return const_reverse_iterator (begin ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator rbegin () {
            return reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator rend () {
            return reverse_iterator (begin ());
        }

    private:
        void storage_invariants () const
        {
            BOOST_UBLAS_CHECK (capacity_ == index_data_.size (), internal_logic ());
            BOOST_UBLAS_CHECK (capacity_ == value_data_.size (), internal_logic ());
            BOOST_UBLAS_CHECK (filled_ <= capacity_, internal_logic ());
            BOOST_UBLAS_CHECK (sorted_filled_ <= filled_, internal_logic ());
            BOOST_UBLAS_CHECK (sorted_ == (sorted_filled_ == filled_), internal_logic ());
        }

        size_type size_;
        size_type capacity_;
        mutable typename index_array_type::size_type filled_;
        mutable typename index_array_type::size_type sorted_filled_; 
        mutable bool sorted_;
        mutable index_array_type index_data_;
        mutable value_array_type value_data_;
        static const value_type zero_;

        BOOST_UBLAS_INLINE
        static size_type zero_based (size_type k_based_index) {
            return k_based_index - IB;
        }
        BOOST_UBLAS_INLINE
        static size_type k_based (size_type zero_based_index) {
            return zero_based_index + IB;
        }

        friend class iterator;
        friend class const_iterator;
    };

    template<class T, std::size_t IB, class IA, class TA>
    const typename coordinate_vector<T, IB, IA, TA>::value_type coordinate_vector<T, IB, IA, TA>::zero_ (0);

}}}

#endif

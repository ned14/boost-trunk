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

#ifndef BOOST_UBLAS_VECTOR_ASSIGN_H
#define BOOST_UBLAS_VECTOR_ASSIGN_H

#include <boost/numeric/ublas/config.hpp>
#include <boost/numeric/ublas/vector_expression.hpp>

// Iterators based on ideas of Jeremy Siek

namespace boost { namespace numeric { namespace ublas {

    template<class E1, class E2>
    static
    BOOST_UBLAS_INLINE
    bool equals (const vector_expression<E1> &e1, const vector_expression<E2> &e2) {
        typedef BOOST_UBLAS_TYPENAME type_traits<BOOST_UBLAS_TYPENAME promote_traits<BOOST_UBLAS_TYPENAME E1::value_type,
                                                                                     BOOST_UBLAS_TYPENAME E2::value_type>::promote_type>::real_type real_type;
        // Check, that the values match at least half.
        static real_type sqrt_epsilon (type_traits<real_type>::sqrt (std::numeric_limits<real_type>::epsilon ()));
        return norm_inf (e1 - e2) < sqrt_epsilon *
               std::max<real_type> (std::max<real_type> (norm_inf (e1),
                                                         norm_inf (e2)),
                                    std::numeric_limits<real_type>::min ());
    }

#ifdef BOOST_UBLAS_ENABLE_SPECIALIZED_ASSIGN
    // Iterating case
    template<class F, class V, class T>
    // This function seems to be big. So we do not let the compiler inline it.
    // BOOST_UBLAS_INLINE
    void iterating_vector_assign_scalar (const F &f, V &v, const T &t) {
        typedef F functor_type;
        typedef typename V::difference_type difference_type;
        difference_type size (v.size ());
        typename V::iterator it (v.begin ());
        BOOST_UBLAS_CHECK (v.end () - it == size, bad_size ());
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
        while (-- size >= 0)
            functor_type () (*it, t), ++ it;
#else
        DD (size, 4, r, (functor_type () (*it, t), ++ it));
#endif
    }
    // Indexing case
    template<class F, class V, class T>
    // This function seems to be big. So we do not let the compiler inline it.
    // BOOST_UBLAS_INLINE
    void indexing_vector_assign_scalar (const F &f, V &v, const T &t) {
        typedef F functor_type;
        typedef typename V::difference_type difference_type;
        difference_type size (v.size ());
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
        for (difference_type i = 0; i < size; ++ i)
            functor_type () (v (i), t);
#else
        difference_type i (0);
        DD (size, 4, r, (functor_type () (v (i), t), ++ i));
#endif
    }

    // Dense (proxy) case
    template<class F, class V, class T>
    // This function seems to be big. So we do not let the compiler inline it.
    // BOOST_UBLAS_INLINE
    void evaluate_vector_assign_scalar (const F &f, V &v, const T &t, dense_proxy_tag) {
        typedef F functor_type;
        typedef typename V::difference_type difference_type;
        difference_type size (v.size ());
        if (size >= BOOST_UBLAS_ITERATOR_THRESHOLD)
            iterating_vector_assign_scalar (functor_type (), v, t);
        else
            indexing_vector_assign_scalar (functor_type (), v, t);
    }
    // Packed (proxy) case
    template<class F, class V, class T>
    // This function seems to be big. So we do not let the compiler inline it.
    // BOOST_UBLAS_INLINE
    void evaluate_vector_assign_scalar (const F &f, V &v, const T &t, packed_proxy_tag) {
        typedef F functor_type;
        typedef typename V::difference_type difference_type;
        typename V::iterator it (v.begin ());
        difference_type size (v.end () - it);
        while (-- size >= 0)
            functor_type () (*it, t), ++ it;
    }
    // Sparse (proxy) case
    template<class F, class V, class T>
    // This function seems to be big. So we do not let the compiler inline it.
    // BOOST_UBLAS_INLINE
    void evaluate_vector_assign_scalar (const F &f, V &v, const T &t, sparse_proxy_tag) {
        typedef F functor_type;
        typename V::iterator it (v.begin ());
        typename V::iterator it_end (v.end ());
        while (it != it_end)
            functor_type () (*it, t), ++ it;
    }
#endif

    // vector assignment_operation scalar
    template<class F>
    struct vector_assign_scalar {
        typedef F functor_type;
        typedef typename F::assign_category assign_category;

#ifndef BOOST_UBLAS_ENABLE_SPECIALIZED_ASSIGN
        // Iterating case
        template<class V, class T>
        // This function seems to be big. So we do not let the compiler inline it.
        // BOOST_UBLAS_INLINE
        void iterating_assign (V &v, const T &t) {
            typedef typename V::difference_type difference_type;
            difference_type size (v.size ());
            typename V::iterator it (v.begin ());
            BOOST_UBLAS_CHECK (v.end () - it == size, bad_size ());
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
            while (-- size >= 0)
                functor_type () (*it, t), ++ it;
#else
            DD (size, 4, r, (functor_type () (*it, t), ++ it));
#endif
        }
        // Indexing case
        template<class V, class T>
        // This function seems to be big. So we do not let the compiler inline it.
        // BOOST_UBLAS_INLINE
        void indexing_assign (V &v, const T &t) {
            typedef typename V::difference_type difference_type;
            difference_type size (v.size ());
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
            for (difference_type i = 0; i < size; ++ i)
                functor_type () (v (i), t);
#else
            difference_type i (0);
            DD (size, 4, r, (functor_type () (v (i), t), ++ i));
#endif
        }

        // Dense (proxy) case
        template<class V, class T>
        // This function seems to be big. So we do not let the compiler inline it.
        // BOOST_UBLAS_INLINE
        void operator () (V &v, const T &t, dense_proxy_tag) {
            typedef typename V::difference_type difference_type;
            difference_type size (v.size ());
            if (size >= BOOST_UBLAS_ITERATOR_THRESHOLD)
                iterating_assign (v, t);
            else
                indexing_assign (v, t);
        }
        // Packed (proxy) case
        template<class V, class T>
        // This function seems to be big. So we do not let the compiler inline it.
        // BOOST_UBLAS_INLINE
        void operator () (V &v, const T &t, packed_proxy_tag) {
            typedef typename V::difference_type difference_type;
            typename V::iterator it (v.begin ());
            difference_type size (v.end () - it);
            while (-- size >= 0)
                functor_type () (*it, t), ++ it;
        }
        // Sparse (proxy) case
        template<class V, class T>
        // This function seems to be big. So we do not let the compiler inline it.
        // BOOST_UBLAS_INLINE
        void operator () (V &v, const T &t, sparse_proxy_tag) {
            typename V::iterator it (v.begin ());
            typename V::iterator it_end (v.end ());
            while (it != it_end)
                functor_type () (*it, t), ++ it;
        }
#endif

        // Dispatcher
        template<class V, class T>
        BOOST_UBLAS_INLINE
        void operator () (V &v, const T &t) {
            typedef typename V::storage_category storage_category;
#ifndef BOOST_UBLAS_ENABLE_SPECIALIZED_ASSIGN
            operator () (v, t, storage_category ());
#else
            evaluate_vector_assign_scalar (functor_type (), v, t, storage_category ());
#endif
        }
    };

    template<class LS, class A, class RI>
    struct vector_assign_traits {
        typedef LS storage_category;
    };

    template<>
    struct vector_assign_traits<dense_tag, assign_tag, packed_random_access_iterator_tag> {
        typedef packed_tag storage_category;
    };
    template<>
    struct vector_assign_traits<dense_tag, computed_assign_tag, packed_random_access_iterator_tag> {
        typedef packed_tag storage_category;
    };
    template<>
    struct vector_assign_traits<dense_tag, assign_tag, sparse_bidirectional_iterator_tag> {
        typedef sparse_tag storage_category;
    };
    template<>
    struct vector_assign_traits<dense_tag, computed_assign_tag, sparse_bidirectional_iterator_tag> {
        typedef sparse_tag storage_category;
    };

    template<>
    struct vector_assign_traits<dense_proxy_tag, assign_tag, packed_random_access_iterator_tag> {
        typedef packed_proxy_tag storage_category;
    };
    template<>
    struct vector_assign_traits<dense_proxy_tag, computed_assign_tag, packed_random_access_iterator_tag> {
        typedef packed_proxy_tag storage_category;
    };
    template<>
    struct vector_assign_traits<dense_proxy_tag, assign_tag, sparse_bidirectional_iterator_tag> {
        typedef sparse_proxy_tag storage_category;
    };
    template<>
    struct vector_assign_traits<dense_proxy_tag, computed_assign_tag, sparse_bidirectional_iterator_tag> {
        typedef sparse_proxy_tag storage_category;
    };

    template<>
    struct vector_assign_traits<packed_tag, assign_tag, sparse_bidirectional_iterator_tag> {
        typedef sparse_tag storage_category;
    };
    template<>
    struct vector_assign_traits<packed_tag, computed_assign_tag, sparse_bidirectional_iterator_tag> {
        typedef sparse_tag storage_category;
    };

    template<>
    struct vector_assign_traits<packed_proxy_tag, assign_tag, sparse_bidirectional_iterator_tag> {
        typedef sparse_proxy_tag storage_category;
    };
    template<>
    struct vector_assign_traits<packed_proxy_tag, computed_assign_tag, sparse_bidirectional_iterator_tag> {
        typedef sparse_proxy_tag storage_category;
    };

    template<>
    struct vector_assign_traits<sparse_tag, computed_assign_tag, dense_random_access_iterator_tag> {
        typedef sparse_proxy_tag storage_category;
    };
    template<>
    struct vector_assign_traits<sparse_tag, computed_assign_tag, packed_random_access_iterator_tag> {
        typedef sparse_proxy_tag storage_category;
    };
    template<>
    struct vector_assign_traits<sparse_tag, computed_assign_tag, sparse_bidirectional_iterator_tag> {
        typedef sparse_proxy_tag storage_category;
    };

#ifdef BOOST_UBLAS_ENABLE_SPECIALIZED_ASSIGN
    // Iterating case
    template<class F, class V, class E>
    // This function seems to be big. So we do not let the compiler inline it.
    // BOOST_UBLAS_INLINE
    void iterating_vector_assign (const F &f, V &v, const vector_expression<E> &e) {
        typedef F functor_type;
        typedef typename V::difference_type difference_type;
        difference_type size (BOOST_UBLAS_SAME (v.size (), e ().size ()));
        typename V::iterator it (v.begin ());
        BOOST_UBLAS_CHECK (v.end () - it == size, bad_size ());
        typename E::const_iterator ite (e ().begin ());
        BOOST_UBLAS_CHECK (e ().end () - ite == size, bad_size ());
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
        while (-- size >= 0)
            functor_type () (*it, *ite), ++ it, ++ ite;
#else
        DD (size, 2, r, (functor_type () (*it, *ite), ++ it, ++ ite));
#endif
    }
    // Indexing case
    template<class F, class V, class E>
    // This function seems to be big. So we do not let the compiler inline it.
    // BOOST_UBLAS_INLINE
    void indexing_vector_assign (const F &f, V &v, const vector_expression<E> &e) {
        typedef F functor_type;
        typedef typename V::difference_type difference_type;
        difference_type size (BOOST_UBLAS_SAME (v.size (), e ().size ()));
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
        for (difference_type i = 0; i < size; ++ i)
            functor_type () (v (i), e () (i));
#else
        difference_type i (0);
        DD (size, 2, r, (functor_type () (v (i), e () (i)), ++ i));
#endif
    }

    // Dense (proxy) case
    template<class F, class V, class E>
    // This function seems to be big. So we do not let the compiler inline it.
    // BOOST_UBLAS_INLINE
    void evaluate_vector_assign (const F &f, V &v, const vector_expression<E> &e, dense_proxy_tag) {
        typedef F functor_type;
        typedef typename V::size_type size_type;
        typedef typename V::difference_type difference_type;
        difference_type size (BOOST_UBLAS_SAME (v.size (), e ().size ()));
        if (size >= BOOST_UBLAS_ITERATOR_THRESHOLD)
            iterating_vector_assign (functor_type (), v, e);
        else
            indexing_vector_assign (functor_type (), v, e);
    }
    // Packed (proxy) case
    template<class F, class V, class E>
    // This function seems to be big. So we do not let the compiler inline it.
    // BOOST_UBLAS_INLINE
    void evaluate_vector_assign (const F &f, V &v, const vector_expression<E> &e, packed_proxy_tag) {
        BOOST_UBLAS_CHECK (v.size () == e ().size (), bad_size ());
        typedef F functor_type;
        typedef typename V::size_type size_type;
        typedef typename V::value_type value_type;
#ifdef BOOST_UBLAS_TYPE_CHECK
        vector<value_type> cv (v.size ());
        indexing_vector_assign (scalar_assign<value_type, value_type> (), cv, v);
        indexing_vector_assign (functor_type (), cv, e);
#endif
        typename V::iterator it (v.begin ());
        typename V::iterator it_end (v.end ());
        typename E::const_iterator ite (e ().begin ());
        typename E::const_iterator ite_end (e ().end ());
        if (ite != ite_end && ite.index () < it.index ())
            ite += std::min (it.index () - ite.index (), size_type (ite_end - ite));
        while (it != it_end && ite != ite_end && it.index () < ite.index ()) {
            functor_type () (*it, value_type ());
            ++ it;
        }
        while (it != it_end && ite != ite_end) {
            functor_type () (*it, *ite);
            ++ it, ++ ite;
        }
        while (it != it_end) {
            functor_type () (*it, value_type ());
            ++ it;
        }
#ifdef BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (equals (v, cv), external_logic ());
#endif
    }
    // Sparse case
    template<class F, class V, class E>
    // This function seems to be big. So we do not let the compiler inline it.
    // BOOST_UBLAS_INLINE
    void evaluate_vector_assign (const F &f, V &v, const vector_expression<E> &e, sparse_tag) {
        BOOST_UBLAS_CHECK (v.size () == e ().size (), bad_size ());
        v.clear ();
        typename E::const_iterator ite (e ().begin ());
        typename E::const_iterator ite_end (e ().end ());
        while (ite != ite_end)
            v.insert (ite.index (), *ite), ++ ite;
    }
    // Sparse proxy case
    template<class F, class V, class E>
    // This function seems to be big. So we do not let the compiler inline it.
    // BOOST_UBLAS_INLINE
    void evaluate_vector_assign (const F &f, V &v, const vector_expression<E> &e, sparse_proxy_tag) {
        BOOST_UBLAS_CHECK (v.size () == e ().size (), bad_size ());
        typedef F functor_type;
        typedef typename V::value_type value_type;
#ifdef BOOST_UBLAS_TYPE_CHECK
        vector<value_type> cv (v.size ());
        indexing_vector_assign (scalar_assign<value_type, value_type> (), cv, v);
        indexing_vector_assign (functor_type (), cv, e);
#endif
        typename V::iterator it (v.begin ());
        typename V::iterator it_end (v.end ());
        typename E::const_iterator ite (e ().begin ());
        typename E::const_iterator ite_end (e ().end ());
        while (it != it_end && ite != ite_end) {
            int compare = it.index () - ite.index ();
            if (compare == 0) {
                functor_type () (*it, *ite);
                ++ it, ++ ite;
            } else if (compare < 0) {
                functor_type () (*it, value_type ());
                ++ it;
            } else if (compare > 0) {
                ++ ite;
            }
        }
        while (it != it_end) {
            functor_type () (*it, value_type ());
            ++ it;
        }
#ifdef BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (equals (v, cv), external_logic ());
#endif
    }
#endif

    // vector assignment_operation vector_expression
    template<class F>
    struct vector_assign {
        typedef F functor_type;
        typedef typename F::assign_category assign_category;

#ifndef BOOST_UBLAS_ENABLE_SPECIALIZED_ASSIGN
        // Iterating case
        template<class V, class E>
        // This function seems to be big. So we do not let the compiler inline it.
        // BOOST_UBLAS_INLINE
        void iterating_assign (V &v, const vector_expression<E> &e) {
            typedef typename V::difference_type difference_type;
            difference_type size (BOOST_UBLAS_SAME (v.size (), e ().size ()));
            typename V::iterator it (v.begin ());
            BOOST_UBLAS_CHECK (v.end () - it == size, bad_size ());
            typename E::const_iterator ite (e ().begin ());
            BOOST_UBLAS_CHECK (e ().end () - ite == size, bad_size ());
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
            while (-- size >= 0)
                functor_type () (*it, *ite), ++ it, ++ ite;
#else
            DD (size, 2, r, (functor_type () (*it, *ite), ++ it, ++ ite));
#endif
        }
        // Indexing case
        template<class V, class E>
        // This function seems to be big. So we do not let the compiler inline it.
        // BOOST_UBLAS_INLINE
        void indexing_assign (V &v, const vector_expression<E> &e) {
            typedef typename V::difference_type difference_type;
            difference_type size (BOOST_UBLAS_SAME (v.size (), e ().size ()));
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
            for (difference_type i = 0; i < size; ++ i)
                functor_type () (v (i), e () (i));
#else
            difference_type i (0);
            DD (size, 2, r, (functor_type () (v (i), e () (i)), ++ i));
#endif
        }

        // Dense (proxy) case
        template<class V, class E>
        // This function seems to be big. So we do not let the compiler inline it.
        // BOOST_UBLAS_INLINE
        void operator () (V &v, const vector_expression<E> &e, dense_proxy_tag) {
            typedef typename V::size_type size_type;
            typedef typename V::difference_type difference_type;
            difference_type size (BOOST_UBLAS_SAME (v.size (), e ().size ()));
            if (size >= BOOST_UBLAS_ITERATOR_THRESHOLD)
                iterating_assign (v, e);
            else
                indexing_assign (v, e);
        }
        // Packed (proxy) case
        template<class V, class E>
        // This function seems to be big. So we do not let the compiler inline it.
        // BOOST_UBLAS_INLINE
        void operator () (V &v, const vector_expression<E> &e, packed_proxy_tag) {
            BOOST_UBLAS_CHECK (v.size () == e ().size (), bad_size ());
            typedef typename V::size_type size_type;
            typedef typename V::value_type value_type;
#ifdef BOOST_UBLAS_TYPE_CHECK
            vector<value_type> cv (v.size ());
            vector_assign<scalar_assign<value_type, value_type> > ().indexing_assign (cv, v);
            vector_assign<functor_type> ().indexing_assign  (cv, e);
#endif
            typename V::iterator it (v.begin ());
            typename V::iterator it_end (v.end ());
            typename E::const_iterator ite (e ().begin ());
            typename E::const_iterator ite_end (e ().end ());
            if (ite != ite_end && ite.index () < it.index ())
                ite += std::min (it.index () - ite.index (), size_type (ite_end - ite));
            while (it != it_end && ite != ite_end && it.index () < ite.index ()) {
                functor_type () (*it, value_type ());
                ++ it;
            }
            while (it != it_end && ite != ite_end) {
                functor_type () (*it, *ite);
                ++ it, ++ ite;
            }
            while (it != it_end) {
                functor_type () (*it, value_type ());
                ++ it;
            }
#ifdef BOOST_UBLAS_TYPE_CHECK
            BOOST_UBLAS_CHECK (equals (v, cv), external_logic ());
#endif
        }
        // Sparse case
        template<class V, class E>
        // This function seems to be big. So we do not let the compiler inline it.
        // BOOST_UBLAS_INLINE
        void operator () (V &v, const vector_expression<E> &e, sparse_tag) {
            BOOST_UBLAS_CHECK (v.size () == e ().size (), bad_size ());
            v.clear ();
            typename E::const_iterator ite (e ().begin ());
            typename E::const_iterator ite_end (e ().end ());
            while (ite != ite_end)
                v.insert (ite.index (), *ite), ++ ite;
        }
        // Sparse proxy case
        template<class V, class E>
        // This function seems to be big. So we do not let the compiler inline it.
        // BOOST_UBLAS_INLINE
        void operator () (V &v, const vector_expression<E> &e, sparse_proxy_tag) {
            BOOST_UBLAS_CHECK (v.size () == e ().size (), bad_size ());
            typedef typename V::value_type value_type;
#ifdef BOOST_UBLAS_TYPE_CHECK
            vector<value_type> cv (v.size ());
            vector_assign<scalar_assign<value_type, value_type> > ().indexing_assign (cv, v);
            vector_assign<functor_type> ().indexing_assign  (cv, e);
#endif
            typename V::iterator it (v.begin ());
            typename V::iterator it_end (v.end ());
            typename E::const_iterator ite (e ().begin ());
            typename E::const_iterator ite_end (e ().end ());
            while (it != it_end && ite != ite_end) {
                int compare = it.index () - ite.index ();
                if (compare == 0) {
                    functor_type () (*it, *ite);
                    ++ it, ++ ite;
                } else if (compare < 0) {
                    functor_type () (*it, value_type ());
                    ++ it;
                } else if (compare > 0) {
                    ++ ite;
                }
            }
            while (it != it_end) {
                functor_type () (*it, value_type ());
                ++ it;
            }
#ifdef BOOST_UBLAS_TYPE_CHECK
            BOOST_UBLAS_CHECK (equals (v, cv), external_logic ());
#endif
        }
#endif

        // Dispatcher
        template<class V, class E>
        BOOST_UBLAS_INLINE
        void operator () (V &v, const vector_expression<E> &e) {
            typedef typename vector_assign_traits<BOOST_UBLAS_TYPENAME V::storage_category,
                                                  assign_category,
                                                  BOOST_UBLAS_TYPENAME E::const_iterator::iterator_category>::storage_category storage_category;
#ifndef BOOST_UBLAS_ENABLE_SPECIALIZED_ASSIGN
            operator () (v, e, storage_category ());
#else
            evaluate_vector_assign (functor_type (), v, e, storage_category ());
#endif
        }
    };

}}}

#endif




















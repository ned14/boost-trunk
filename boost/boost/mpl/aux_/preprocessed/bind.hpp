// preprocessed part of 'boost/mpl/bind.hpp' header
// see the original for copyright information

namespace boost {
namespace mpl {

namespace aux {
template<bool>
struct resolve_argument_impl
{
    template
        <
            typename T, typename U1, typename U2, typename U3, typename U4,
                typename U5
        >
    struct result_
    {
        typedef T type;
    };
};

template<>
struct resolve_argument_impl<true>
{
    template
        <
            typename T, typename U1, typename U2, typename U3, typename U4,
                typename U5
        >
    struct result_
    {
        typedef typename apply5<T, U1, U2, U3, U4, U5>::type type;
    };
};

template<typename T>
struct is_bind_template;

template<typename T>
struct resolve_bind_argument
{
    template<typename U1, typename U2, typename U3, typename U4, typename U5>
    struct result_
    {
        typedef typename resolve_argument_impl<is_bind_template<T>::value>::template
            result_<T, U1, U2, U3, U4, U5>::type type;
    };
};
}

template
    <
        typename F, typename T1, typename T2, typename T3, typename T4, typename
            T5
    >
struct bind;

template<typename F, typename T>
struct bind1st;

template<typename F, typename T>
struct bind2nd;


namespace aux {
template<int>
struct bind_impl_chooser;

template<typename T>
struct is_bind_template
{
    static const bool value = false;
};

template
    <
        typename F, typename T1, typename T2, typename T3, typename T4, typename
            T5
    >
struct is_bind_template<bind<F, T1, T2, T3, T4, T5> >
{
    static const bool value = true;
};

template<typename F, typename T>
struct is_bind_template<bind1st<F, T> >
{
    static const bool value = true;
};

template<typename F, typename T>
struct is_bind_template<bind2nd<F, T> >
{
    static const bool value = true;
};

}

template<typename F>
struct bind0
{
    template<typename U1, typename U2, typename U3, typename U4, typename U5>
    struct apply_
    {
        typedef typename aux::resolve_bind_argument<F>
            ::template result_<U1, U2, U3, U4, U5>::type f_;

        typedef apply0<f_> type;
    };

    template
        <
            typename U1 = aux::none, typename U2 = aux::none, typename U3 =
                aux::none, typename U4 = aux::none, typename U5 = aux::none
        >
    struct apply : apply_< U1, U2, U3, U4, U5 >::type
    {
    };
};

namespace aux {
template<typename F>
struct is_bind_template<bind0<F> >
{
    static const bool value = true;
};
}

namespace aux {
template<>
struct bind_impl_chooser<0>
{
    template
        <
            typename F, typename T1, typename T2, typename T3, typename T4,
                typename T5
        >
    struct result_
    {
        typedef bind0<F> type;
    };
};
}

namespace aux {
template<>
struct resolve_bind_argument<arg<1> >
{
    template<typename U1, typename U2, typename U3, typename U4, typename U5>
    struct result_
    {
        typedef U1 type;

        typedef char arity_constraint[sizeof(aux::reject_if_none< type > )];
    };
};
}

template<typename F, typename T1>
struct bind1
{
    template<typename U1, typename U2, typename U3, typename U4, typename U5>
    struct apply_
    {
        typedef typename aux::resolve_bind_argument<F>
            ::template result_<U1, U2, U3, U4, U5>::type f_;

        typedef typename aux::resolve_bind_argument<T1>
            ::template result_<U1, U2, U3, U4, U5>::type t1;

        typedef apply1<f_, t1> type;
    };

    template
        <
            typename U1 = aux::none, typename U2 = aux::none, typename U3 =
                aux::none, typename U4 = aux::none, typename U5 = aux::none
        >
    struct apply : apply_< U1, U2, U3, U4, U5 >::type
    {
    };
};

namespace aux {
template<typename F, typename T1>
struct is_bind_template<bind1<F, T1> >
{
    static const bool value = true;
};
}

namespace aux {
template<>
struct bind_impl_chooser<1>
{
    template
        <
            typename F, typename T1, typename T2, typename T3, typename T4,
                typename T5
        >
    struct result_
    {
        typedef bind1<F, T1> type;
    };
};
}

namespace aux {
template<>
struct resolve_bind_argument<arg<2> >
{
    template<typename U1, typename U2, typename U3, typename U4, typename U5>
    struct result_
    {
        typedef U2 type;

        typedef char arity_constraint[sizeof(aux::reject_if_none< type > )];
    };
};
}

template<typename F, typename T1, typename T2>
struct bind2
{
    template<typename U1, typename U2, typename U3, typename U4, typename U5>
    struct apply_
    {
        typedef typename aux::resolve_bind_argument<F>
            ::template result_<U1, U2, U3, U4, U5>::type f_;

        typedef typename aux::resolve_bind_argument<T1>
            ::template result_<U1, U2, U3, U4, U5>::type t1;

        typedef typename aux::resolve_bind_argument<T2>
            ::template result_<U1, U2, U3, U4, U5>::type t2;

        typedef apply2<f_, t1, t2> type;
    };

    template
        <
            typename U1 = aux::none, typename U2 = aux::none, typename U3 =
                aux::none, typename U4 = aux::none, typename U5 = aux::none
        >
    struct apply : apply_< U1, U2, U3, U4, U5 >::type
    {
    };
};

namespace aux {
template<typename F, typename T1, typename T2>
struct is_bind_template<bind2<F, T1, T2> >
{
    static const bool value = true;
};
}

namespace aux {
template<>
struct bind_impl_chooser<2>
{
    template
        <
            typename F, typename T1, typename T2, typename T3, typename T4,
                typename T5
        >
    struct result_
    {
        typedef bind2<F, T1, T2> type;
    };
};
}

namespace aux {
template<>
struct resolve_bind_argument<arg<3> >
{
    template<typename U1, typename U2, typename U3, typename U4, typename U5>
    struct result_
    {
        typedef U3 type;

        typedef char arity_constraint[sizeof(aux::reject_if_none< type > )];
    };
};
}

template<typename F, typename T1, typename T2, typename T3>
struct bind3
{
    template<typename U1, typename U2, typename U3, typename U4, typename U5>
    struct apply_
    {
        typedef typename aux::resolve_bind_argument<F>
            ::template result_<U1, U2, U3, U4, U5>::type f_;

        typedef typename aux::resolve_bind_argument<T1>
            ::template result_<U1, U2, U3, U4, U5>::type t1;

        typedef typename aux::resolve_bind_argument<T2>
            ::template result_<U1, U2, U3, U4, U5>::type t2;

        typedef typename aux::resolve_bind_argument<T3>
            ::template result_<U1, U2, U3, U4, U5>::type t3;

        typedef apply3<f_, t1, t2, t3> type;
    };

    template
        <
            typename U1 = aux::none, typename U2 = aux::none, typename U3 =
                aux::none, typename U4 = aux::none, typename U5 = aux::none
        >
    struct apply : apply_< U1, U2, U3, U4, U5 >::type
    {
    };
};

namespace aux {
template<typename F, typename T1, typename T2, typename T3>
struct is_bind_template<bind3<F, T1, T2, T3> >
{
    static const bool value = true;
};
}

namespace aux {
template<>
struct bind_impl_chooser<3>
{
    template
        <
            typename F, typename T1, typename T2, typename T3, typename T4,
                typename T5
        >
    struct result_
    {
        typedef bind3<F, T1, T2, T3> type;
    };
};
}

namespace aux {
template<>
struct resolve_bind_argument<arg<4> >
{
    template<typename U1, typename U2, typename U3, typename U4, typename U5>
    struct result_
    {
        typedef U4 type;

        typedef char arity_constraint[sizeof(aux::reject_if_none< type > )];
    };
};
}

template<typename F, typename T1, typename T2, typename T3, typename T4>
struct bind4
{
    template<typename U1, typename U2, typename U3, typename U4, typename U5>
    struct apply_
    {
        typedef typename aux::resolve_bind_argument<F>
            ::template result_<U1, U2, U3, U4, U5>::type f_;

        typedef typename aux::resolve_bind_argument<T1>
            ::template result_<U1, U2, U3, U4, U5>::type t1;

        typedef typename aux::resolve_bind_argument<T2>
            ::template result_<U1, U2, U3, U4, U5>::type t2;

        typedef typename aux::resolve_bind_argument<T3>
            ::template result_<U1, U2, U3, U4, U5>::type t3;

        typedef typename aux::resolve_bind_argument<T4>
            ::template result_<U1, U2, U3, U4, U5>::type t4;

        typedef apply4<f_, t1, t2, t3, t4> type;
    };

    template
        <
            typename U1 = aux::none, typename U2 = aux::none, typename U3 =
                aux::none, typename U4 = aux::none, typename U5 = aux::none
        >
    struct apply : apply_< U1, U2, U3, U4, U5 >::type
    {
    };
};

namespace aux {
template<typename F, typename T1, typename T2, typename T3, typename T4>
struct is_bind_template<bind4<F, T1, T2, T3, T4> >
{
    static const bool value = true;
};
}

namespace aux {
template<>
struct bind_impl_chooser<4>
{
    template
        <
            typename F, typename T1, typename T2, typename T3, typename T4,
                typename T5
        >
    struct result_
    {
        typedef bind4<F, T1, T2, T3, T4> type;
    };
};
}

namespace aux {
template<>
struct resolve_bind_argument<arg<5> >
{
    template<typename U1, typename U2, typename U3, typename U4, typename U5>
    struct result_
    {
        typedef U5 type;

        typedef char arity_constraint[sizeof(aux::reject_if_none< type > )];
    };
};
}

template
    <
        typename F, typename T1, typename T2, typename T3, typename T4, typename
            T5
    >
struct bind5
{
    template<typename U1, typename U2, typename U3, typename U4, typename U5>
    struct apply_
    {
        typedef typename aux::resolve_bind_argument<F>
            ::template result_<U1, U2, U3, U4, U5>::type f_;

        typedef typename aux::resolve_bind_argument<T1>
            ::template result_<U1, U2, U3, U4, U5>::type t1;

        typedef typename aux::resolve_bind_argument<T2>
            ::template result_<U1, U2, U3, U4, U5>::type t2;

        typedef typename aux::resolve_bind_argument<T3>
            ::template result_<U1, U2, U3, U4, U5>::type t3;

        typedef typename aux::resolve_bind_argument<T4>
            ::template result_<U1, U2, U3, U4, U5>::type t4;

        typedef typename aux::resolve_bind_argument<T5>
            ::template result_<U1, U2, U3, U4, U5>::type t5;

        typedef apply5<f_, t1, t2, t3, t4, t5> type;
    };

    template
        <
            typename U1 = aux::none, typename U2 = aux::none, typename U3 =
                aux::none, typename U4 = aux::none, typename U5 = aux::none
        >
    struct apply : apply_< U1, U2, U3, U4, U5 >::type
    {
    };
};

namespace aux {
template
    <
        typename F, typename T1, typename T2, typename T3, typename T4, typename
            T5
    >
struct is_bind_template<bind5<F, T1, T2, T3, T4, T5> >
{
    static const bool value = true;
};
}

namespace aux {
template<>
struct bind_impl_chooser<5>
{
    template
        <
            typename F, typename T1, typename T2, typename T3, typename T4,
                typename T5
        >
    struct result_
    {
        typedef bind5<F, T1, T2, T3, T4, T5> type;
    };
};
}

namespace aux {
template
    <
        typename T, typename U0 = T, typename U1 = T, typename U2 = T, typename
            U3 = T, typename U4 = T
    >
struct bind_count_if_not
{
    static const long value = !::boost::is_same< T, U0 >::value + !::boost::
        is_same< T, U1 >::value + !::boost::is_same< T, U2 >::value + !::boost::
            is_same< T, U3 >::value + !::boost::is_same< T, U4 >::value;
};
}

template
    <
        typename F, typename T1 = aux::none, typename T2 = aux::none, typename
            T3 = aux::none, typename T4 = aux::none, typename T5 = aux::none
    >
struct bind :
    aux::bind_impl_chooser<aux::bind_count_if_not< aux::none, T1, T2, T3, T4, T5 >::value>
        ::template result_<F, T1, T2, T3, T4, T5>::type
{
};

template<typename F, typename T>
struct bind1st
{
    template
        <
            typename U, typename U1 = aux::none, typename U2 = aux::none, typename
                U3 = aux::none, typename U4 = aux::none
        >
    struct apply : apply2< F, T, U >
    {
    };
};

template<typename F, typename T>
struct bind2nd
{
    template
        <
            typename U, typename U1 = aux::none, typename U2 = aux::none, typename
                U3 = aux::none, typename U4 = aux::none
        >
    struct apply : apply2< F, U, T >
    {
    };
};
}
}

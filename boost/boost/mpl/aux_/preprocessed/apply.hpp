// preprocessed part of 'boost/mpl/apply.hpp' header
// see the original for copyright information

namespace boost {
namespace mpl {

namespace aux {
template<long>
struct apply_impl_chooser;
}

template<typename F>
struct apply0 :
    F
{
};

template<>
struct apply0< _ >
{
    template<typename F>
    struct apply : F
    {
    };
};

namespace aux {
template<>
struct apply_impl_chooser< 0 >
{
    template
        <
            typename F, typename T1, typename T2, typename T3, typename T4,
                typename T5
        >
    struct result_
    {
        typedef apply0<F> type;
    };
};
}

template<typename F, typename T1>
struct apply1 :
    F::template apply<T1>
{
};

template<>
struct apply1<_, _>
{
    template<typename F, typename T1>
    struct apply : F::template apply< T1 >
    {
    };
};

namespace aux {
template<>
struct apply_impl_chooser< 1 >
{
    template
        <
            typename F, typename T1, typename T2, typename T3, typename T4,
                typename T5
        >
    struct result_
    {
        typedef apply1<F, T1> type;
    };
};
}

template<typename F, typename T1, typename T2>
struct apply2 :
    F::template apply<T1, T2>
{
};

template<>
struct apply2<_, _, _>
{
    template<typename F, typename T1, typename T2>
    struct apply : F::template apply<T1, T2>
    {
    };
};

namespace aux {
template<>
struct apply_impl_chooser< 2 >
{
    template
        <
            typename F, typename T1, typename T2, typename T3, typename T4,
                typename T5
        >
    struct result_
    {
        typedef apply2<F, T1, T2> type;
    };
};
}

template<typename F, typename T1, typename T2, typename T3>
struct apply3 :
    F::template apply<T1, T2, T3>
{
};

template<>
struct apply3<_, _, _, _>
{
    template<typename F, typename T1, typename T2, typename T3>
    struct apply : F::template apply<T1, T2, T3>
    {
    };
};

namespace aux {
template<>
struct apply_impl_chooser< 3 >
{
    template
        <
            typename F, typename T1, typename T2, typename T3, typename T4,
                typename T5
        >
    struct result_
    {
        typedef apply3<F, T1, T2, T3> type;
    };
};
}

template<typename F, typename T1, typename T2, typename T3, typename T4>
struct apply4 :
    F::template apply<T1, T2, T3, T4>
{
};

template<>
struct apply4<_, _, _, _, _>
{
    template<typename F, typename T1, typename T2, typename T3, typename T4>
    struct apply : F::template apply<T1, T2, T3, T4>
    {
    };
};

namespace aux {
template<>
struct apply_impl_chooser< 4 >
{
    template
        <
            typename F, typename T1, typename T2, typename T3, typename T4,
                typename T5
        >
    struct result_
    {
        typedef apply4<F, T1, T2, T3, T4> type;
    };
};
}

template
    <
        typename F, typename T1, typename T2, typename T3, typename T4, typename
            T5
    >
struct apply5 :
    F::template apply<T1, T2, T3, T4, T5>
{
};

template<>
struct apply5<_, _, _, _, _, _>
{
    template
        <
            typename F, typename T1, typename T2, typename T3, typename T4,
                typename T5
        >
    struct apply : F::template apply<T1, T2, T3, T4, T5>
    {
    };
};

namespace aux {
template<>
struct apply_impl_chooser< 5 >
{
    template
        <
            typename F, typename T1, typename T2, typename T3, typename T4,
                typename T5
        >
    struct result_
    {
        typedef apply5<F, T1, T2, T3, T4, T5> type;
    };
};
}

namespace aux {
template
    <
        typename T, typename U0 = T, typename U1 = T, typename U2 = T, typename
            U3 = T, typename U4 = T
    >
struct apply_count_if_not
{
    static const long   value = !::boost::is_same< T, U0 >::value + !::boost::
        is_same< T, U1 >::value + !::boost::is_same< T, U2 >::value + !::boost::
            is_same< T, U3 >::value + !::boost::is_same< T, U4 >::value;
};
}

template
    <
        typename F, typename T1 = aux::none, typename T2 = aux::none, typename
            T3 = aux::none, typename T4 = aux::none, typename T5 = aux::none
    >
struct apply :
    aux::apply_impl_chooser<aux::apply_count_if_not< aux::none, T1, T2, T3, T4, T5 >::value>
        ::template result_<F, T1, T2, T3, T4, T5>::type
{
};

}
}

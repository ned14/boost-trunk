// preprocessed part of 'boost/mpl/aux_/impl.hpp' header
// see the original for copyright information

namespace boost {
namespace mpl {

namespace aux {
template<long>
struct list_impl_chooser;
}

namespace aux {
template<>
struct list_impl_chooser< 0 >
{
    template
        <
            typename T0, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename T6, typename T7, typename T8, typename T9
        >
    struct result_
    {
        typedef list0 type;
    };
};
}

namespace aux {
template<>
struct list_impl_chooser< 1 >
{
    template
        <
            typename T0, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename T6, typename T7, typename T8, typename T9
        >
    struct result_
    {
        typedef list1<T0> type;
    };
};
}

namespace aux {
template<>
struct list_impl_chooser< 2 >
{
    template
        <
            typename T0, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename T6, typename T7, typename T8, typename T9
        >
    struct result_
    {
        typedef list2<T0, T1> type;
    };
};
}

namespace aux {
template<>
struct list_impl_chooser< 3 >
{
    template
        <
            typename T0, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename T6, typename T7, typename T8, typename T9
        >
    struct result_
    {
        typedef list3<T0, T1, T2> type;
    };
};
}

namespace aux {
template<>
struct list_impl_chooser< 4 >
{
    template
        <
            typename T0, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename T6, typename T7, typename T8, typename T9
        >
    struct result_
    {
        typedef list4<T0, T1, T2, T3> type;
    };
};
}

namespace aux {
template<>
struct list_impl_chooser< 5 >
{
    template
        <
            typename T0, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename T6, typename T7, typename T8, typename T9
        >
    struct result_
    {
        typedef list5<T0, T1, T2, T3, T4> type;
    };
};
}

namespace aux {
template<>
struct list_impl_chooser< 6 >
{
    template
        <
            typename T0, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename T6, typename T7, typename T8, typename T9
        >
    struct result_
    {
        typedef list6<T0, T1, T2, T3, T4, T5> type;
    };
};
}

namespace aux {
template<>
struct list_impl_chooser< 7 >
{
    template
        <
            typename T0, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename T6, typename T7, typename T8, typename T9
        >
    struct result_
    {
        typedef list7<T0, T1, T2, T3, T4, T5, T6> type;
    };
};
}

namespace aux {
template<>
struct list_impl_chooser< 8 >
{
    template
        <
            typename T0, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename T6, typename T7, typename T8, typename T9
        >
    struct result_
    {
        typedef list8<T0, T1, T2, T3, T4, T5, T6, T7> type;
    };
};
}

namespace aux {
template<>
struct list_impl_chooser< 9 >
{
    template
        <
            typename T0, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename T6, typename T7, typename T8, typename T9
        >
    struct result_
    {
        typedef list9<T0, T1, T2, T3, T4, T5, T6, T7, T8> type;
    };
};
}

namespace aux {
template
    <
        typename T, typename U0 = T, typename U1 = T, typename U2 = T, typename
            U3 = T, typename U4 = T, typename U5 = T, typename U6 = T, typename
                U7 = T, typename U8 = T, typename U9 = T
    >
struct list_count_if_not
{
    static const long   value = !::boost::is_same< T, U0 >::value + !::boost::
        is_same< T, U1 >::value + !::boost::is_same< T, U2 >::value + !::boost::
            is_same< T, U3 >::value + !::boost::is_same< T, U4 >::value + !::
                boost::is_same< T, U5 >::value + !::boost::is_same< T, U6 >::
                    value + !::boost::is_same< T, U7 >::value + !::boost::
                        is_same< T, U8 >::value + !::boost::is_same< T, U9 >::
                            value;
};
}
}
}

// preprocessed part of 'boost/mpl/list.hpp' header
// see the original for copyright information

namespace boost {
namespace mpl {

namespace aux {
template
    <
        typename T0, typename T1, typename T2, typename T3, typename T4,
            typename T5, typename T6, typename T7, typename T8, typename T9
    >
struct list_impl
{
    typedef aux::list_count_if_not
        <
            aux::none, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9
        > arg_num_;
    typedef typename aux::list_impl_chooser<arg_num_::value>
        ::template result_<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::type type;

};
}

template
    <
        typename T0 = aux::none, typename T1 = aux::none, typename T2 = aux::
            none, typename T3 = aux::none, typename T4 = aux::none, typename
                T5 = aux::none, typename T6 = aux::none, typename T7 = aux::
                    none, typename T8 = aux::none, typename T9 = aux::none
    >
struct list :
    aux::list_impl<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::type
{
    typedef typename aux::list_impl<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::type
        type;
};
}
}

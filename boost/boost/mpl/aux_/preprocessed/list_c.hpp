// preprocessed part of 'boost/mpl/list_c.hpp' header
// see the original for copyright information

namespace boost {
namespace mpl {

namespace aux {
template<typename T>
struct list_c_param
{
    typedef long type;

    static const long   value = 2147483647L;
};

template<>
struct list_c_param< unsigned char >
{
    typedef unsigned long type;

    static const unsigned long  value = 0xffffffffUL;
};

template<>
struct list_c_param< unsigned short >
{
    typedef unsigned long type;

    static const unsigned long  value = 0xffffffffUL;
};

template<>
struct list_c_param< unsigned int >
{
    typedef unsigned long type;

    static const unsigned long  value = 0xffffffffUL;
};

template<>
struct list_c_param< unsigned long >
{
    typedef unsigned long type;

    static const unsigned long  value = 0xffffffffUL;
};

template
    <
        typename T, typename list_c_param<T>::type C0, typename list_c_param<T>::type
            C1, typename list_c_param<T>::type C2, typename list_c_param<T>::type
                C3, typename list_c_param<T>::type C4, typename list_c_param<T>::type
                    C5, typename list_c_param<T>::type C6, typename list_c_param
                        <
                            T
                        >::type C7, typename list_c_param<T>::type C8, typename list_c_param
                        <
                            T
                        >::type C9
    >
struct list_c_impl
{
    typedef typename list_c_param<T>::type param_type_;

    typedef aux::list_count_if_not
        <
            integral_c<param_type_, list_c_param<T>::value> , integral_c
                <
                    param_type_, C0
                > , integral_c<param_type_, C1> , integral_c<param_type_, C2> , integral_c
                <
                    param_type_, C3
                > , integral_c<param_type_, C4> , integral_c<param_type_, C5> , integral_c
                <
                    param_type_, C6
                > , integral_c<param_type_, C7> , integral_c<param_type_, C8> , integral_c
                <
                    param_type_, C9
                >
        > arg_num_;

    typedef typename aux::list_impl_chooser<arg_num_::value>::template result_
        <
            integral_c<T, (T) C0> , integral_c<T, (T) C1> , integral_c
                <T, (T) C2
                > , integral_c<T, (T) C3> , integral_c<T, (T) C4> , integral_c
                <T, (T) C5
                > , integral_c<T, (T) C6> , integral_c<T, (T) C7> , integral_c
                <T, (T) C8
                > , integral_c<T, (T) C9>
        >::type type;
};
}

template
    <
        typename T, typename aux::list_c_param<T>::type C0 = aux::list_c_param
            <
                T
            >::value, typename aux::list_c_param<T>::type C1 = aux::list_c_param
            <
                T
            >::value, typename aux::list_c_param<T>::type C2 = aux::list_c_param
            <
                T
            >::value, typename aux::list_c_param<T>::type C3 = aux::list_c_param
            <
                T
            >::value, typename aux::list_c_param<T>::type C4 = aux::list_c_param
            <
                T
            >::value, typename aux::list_c_param<T>::type C5 = aux::list_c_param
            <
                T
            >::value, typename aux::list_c_param<T>::type C6 = aux::list_c_param
            <
                T
            >::value, typename aux::list_c_param<T>::type C7 = aux::list_c_param
            <
                T
            >::value, typename aux::list_c_param<T>::type C8 = aux::list_c_param
            <
                T
            >::value, typename aux::list_c_param<T>::type C9 = aux::list_c_param
            <
                T
            >::value
    >
struct list_c :
    aux::list_c_impl<T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9>::type
{
    typedef typename aux::list_c_impl<T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9>::type
        type;
};
}
}

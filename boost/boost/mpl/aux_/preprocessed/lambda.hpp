// preprocessed part of 'boost/mpl/lambda.hpp' header
// see the original for copyright information

namespace boost {
namespace mpl {
template<typename T>
struct lambda
{
    typedef T type;
};

template<typename F>
struct lambda<bind0<F> >
{
    typedef bind0<F> type;
};

template<template<typename P1>
class F, typename T1>
struct lambda<F<T1> >
{
    typedef bind1<typename make_f1<F>::type, typename lambda<T1>::type> type;
};

template<template<typename P1>
class F>
struct lambda<F<_> >
{
    typedef F<_> type;
};

template<typename F, typename T1>
struct lambda<bind1<F, T1> >
{
    typedef bind1<F, T1> type;
};

template<template<typename P1, typename P2>
class F, typename T1, typename T2>
struct lambda<F<T1, T2> >
{
    typedef bind2
        <
            typename make_f2<F>::type, typename lambda<T1>::type, typename lambda
                <
                    T2
                >::type
        > type;
};

template<template<typename P1, typename P2>
class F>
struct lambda<F<_, _> >
{
    typedef F<_, _> type;
};

template<typename F, typename T1, typename T2>
struct lambda<bind2<F, T1, T2> >
{
    typedef bind2<F, T1, T2> type;
};

template<template<typename P1, typename P2, typename P3>
class F, typename T1, typename T2, typename T3>
struct lambda<F<T1, T2, T3> >
{
    typedef bind3
        <
            typename make_f3<F>::type, typename lambda<T1>::type, typename lambda
                <
                    T2
                >::type, typename lambda<T3>::type
        > type;
};

template<template<typename P1, typename P2, typename P3>
class F>
struct lambda<F<_, _, _> >
{
    typedef F<_, _, _> type;
};

template<typename F, typename T1, typename T2, typename T3>
struct lambda<bind3<F, T1, T2, T3> >
{
    typedef bind3<F, T1, T2, T3> type;
};

template<template<typename P1, typename P2, typename P3, typename P4>
class F, typename T1, typename T2, typename T3, typename T4>
struct lambda<F<T1, T2, T3, T4> >
{
    typedef bind4
        <
            typename make_f4<F>::type, typename lambda<T1>::type, typename lambda
                <
                    T2
                >::type, typename lambda<T3>::type, typename lambda<T4>::type
        > type;
};

template<template<typename P1, typename P2, typename P3, typename P4>
class F>
struct lambda<F<_, _, _, _> >
{
    typedef F<_, _, _, _> type;
};

template<typename F, typename T1, typename T2, typename T3, typename T4>
struct lambda<bind4<F, T1, T2, T3, T4> >
{
    typedef bind4<F, T1, T2, T3, T4> type;
};

template
    <
        template
            <
                typename P1, typename P2, typename P3, typename P4, typename P5
            >
        class F, typename T1, typename T2, typename T3, typename T4, typename T5
    >
struct lambda<F<T1, T2, T3, T4, T5> >
{
    typedef bind5
        <
            typename make_f5<F>::type, typename lambda<T1>::type, typename lambda
                <
                    T2
                >::type, typename lambda<T3>::type, typename lambda<T4>::type, typename lambda
                <
                    T5
                >::type
        > type;
};

template
    <
        template
            <
                typename P1, typename P2, typename P3, typename P4, typename P5
            >
        class F
    >
struct lambda<F<_, _, _, _, _> >
{
    typedef F<_, _, _, _, _> type;
};

template
    <
        typename F, typename T1, typename T2, typename T3, typename T4, typename
            T5
    >
struct lambda<bind5<F, T1, T2, T3, T4, T5> >
{
    typedef bind5<F, T1, T2, T3, T4, T5> type;
};

template<typename T>
struct lambda<protect<T> >
{
    typedef protect<T> type;
};

template
    <
        typename F, typename T1, typename T2, typename T3, typename T4, typename
            T5
    >
struct lambda<bind<F, T1, T2, T3, T4, T5> >
{
    typedef bind<F, T1, T2, T3, T4, T5> type;
};

template<typename F, typename T>
struct lambda<bind1st<F, T> >
{
    typedef bind1st<F, T> type;
};

template<typename F, typename T>
struct lambda<bind2nd<F, T> >
{
    typedef bind2nd<F, T> type;
};

}
}

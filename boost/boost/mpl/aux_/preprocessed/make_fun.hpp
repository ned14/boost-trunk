// preprocessed part of 'boost/mpl/make_fun.hpp' header
// see the original for copyright information

namespace boost {
namespace mpl {
template<template<typename P1>
class F>
struct make_f1
{
    typedef make_f1 type;

    template<typename U1>
    struct apply : F< U1 >
    {
    };
};

template<template<typename P1, typename P2>
class F>
struct make_f2
{
    typedef make_f2 type;

    template<typename U1, typename U2>
    struct apply : F<U1, U2>
    {
    };
};

template<template<typename P1, typename P2, typename P3>
class F>
struct make_f3
{
    typedef make_f3 type;

    template<typename U1, typename U2, typename U3>
    struct apply : F<U1, U2, U3>
    {
    };
};

template<template<typename P1, typename P2, typename P3, typename P4>
class F>
struct make_f4
{
    typedef make_f4 type;

    template<typename U1, typename U2, typename U3, typename U4>
    struct apply : F<U1, U2, U3, U4>
    {
    };
};

template
    <
        template
            <
                typename P1, typename P2, typename P3, typename P4, typename P5
            >
        class F
    >
struct make_f5
{
    typedef make_f5 type;

    template<typename U1, typename U2, typename U3, typename U4, typename U5>
    struct apply : F<U1, U2, U3, U4, U5>
    {
    };
};

template<template<typename>
class F>
struct make_f_x
{
    template<typename U>
    struct apply : F< U >
    {
    };
};

template<template<typename, typename>
class F>
struct make_f_xy
{
    template<typename U1, typename U2>
    struct apply : F<U1, U2>
    {
    };
};

template<template<typename, typename>
class F>
struct make_f_yx
{
    template<typename U1, typename U2>
    struct apply : F<U2, U1>
    {
    };
};

}
}

// preprocessed version of '/boost/mpl/aux_/Attic/apply_wrap.hpp' header
// see the original for copyright information

namespace boost { namespace mpl { namespace aux {

template< typename F >
struct apply_wrap0 : F
{
};

template< typename F>
struct msvc_apply1
{
    template< bool > struct f_ : F {};
    template<> struct f_<true>
    {
        template< typename P1 > struct apply
        {
        };
    };

    template< typename T1 > struct result_
        : f_< aux::msvc_never_true<F>::value >
            ::template apply<T1>
    {
    };
};

template<
      typename F, typename T1
    >
struct apply_wrap1
{
    typedef typename msvc_apply1<F>::template result_<
          T1
        >::type type;
};

template< typename F>
struct msvc_apply2
{
    template< bool > struct f_ : F {};
    template<> struct f_<true>
    {
        template< typename P1, typename P2 > struct apply
        {
        };
    };

    template< typename T1, typename T2 > struct result_
        : f_< aux::msvc_never_true<F>::value >
            ::template apply< T1,T2 >
    {
    };
};

template<
      typename F, typename T1, typename T2
    >
struct apply_wrap2
{
    typedef typename msvc_apply2<F>::template result_<
          T1, T2
        >::type type;
};

template< typename F>
struct msvc_apply3
{
    template< bool > struct f_ : F {};
    template<> struct f_<true>
    {
        template< typename P1, typename P2, typename P3 > struct apply
        {
        };
    };

    template< typename T1, typename T2, typename T3 > struct result_
        : f_< aux::msvc_never_true<F>::value >
            ::template apply< T1,T2,T3 >
    {
    };
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply_wrap3
{
    typedef typename msvc_apply3<F>::template result_<
          T1, T2, T3
        >::type type;
};

template< typename F>
struct msvc_apply4
{
    template< bool > struct f_ : F {};
    template<> struct f_<true>
    {
        template<
              typename P1, typename P2, typename P3, typename P4
            >
        struct apply
        {
        };
    };

    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : f_< aux::msvc_never_true<F>::value >
            ::template apply< T1,T2,T3,T4 >
    {
    };
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply_wrap4
{
    typedef typename msvc_apply4<F>::template result_<
          T1, T2, T3, T4
        >::type type;
};

template< typename F>
struct msvc_apply5
{
    template< bool > struct f_ : F {};
    template<> struct f_<true>
    {
        template<
              typename P1, typename P2, typename P3, typename P4
            , typename P5
            >
        struct apply
        {
        };
    };

    template<
          typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
        : f_< aux::msvc_never_true<F>::value >
            ::template apply< T1,T2,T3,T4,T5 >
    {
    };
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply_wrap5
{
    typedef typename msvc_apply5<F>::template result_<
          T1, T2, T3, T4, T5
        >::type type;
};

}}}


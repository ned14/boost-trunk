// preprocessed version of '/boost/mpl/aux_/Attic/apply_wrap.hpp' header
// see the original for copyright information

namespace boost { namespace mpl { namespace aux {

template< typename F >
struct apply_wrap0 : F
{
};

template<
      typename F, typename T1
    >
struct apply_wrap1
{
    typedef typename F::template apply<
         T1
        >::type type;
};

template<
      typename F, typename T1, typename T2
    >
struct apply_wrap2
{
    typedef typename F::template apply<
         T1, T2
        >::type type;
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply_wrap3
{
    typedef typename F::template apply<
         T1, T2, T3
        >::type type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply_wrap4
{
    typedef typename F::template apply<
         T1, T2, T3, T4
        >::type type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply_wrap5
{
    typedef typename F::template apply<
         T1, T2, T3, T4, T5
        >::type type;
};

}}}


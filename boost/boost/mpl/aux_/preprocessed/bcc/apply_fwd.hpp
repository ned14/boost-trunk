namespace boost { namespace mpl {

template<
      typename F, typename T1 = na, typename T2 = na, typename T3 = na
    , typename T4 = na, typename T5 = na
    >
struct apply;

template<
      typename F
    >
struct apply0;

template<
      typename F, typename T1
    >
struct apply1;

template<
      typename F, typename T1, typename T2
    >
struct apply2;

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply3;

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply4;

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply5;

}}

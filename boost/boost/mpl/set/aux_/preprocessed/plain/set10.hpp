namespace boost { namespace mpl {

template<
      typename T0
    >
struct set1
    : s_item<
          T0
        , set0<  >
        >
{
};

template<
      typename T0, typename T1
    >
struct set2
    : s_item<
          T1
        , set1<T0>
        >
{
};

template<
      typename T0, typename T1, typename T2
    >
struct set3
    : s_item<
          T2
        , set2< T0,T1 >
        >
{
};

template<
      typename T0, typename T1, typename T2, typename T3
    >
struct set4
    : s_item<
          T3
        , set3< T0,T1,T2 >
        >
{
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    >
struct set5
    : s_item<
          T4
        , set4< T0,T1,T2,T3 >
        >
{
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct set6
    : s_item<
          T5
        , set5< T0,T1,T2,T3,T4 >
        >
{
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6
    >
struct set7
    : s_item<
          T6
        , set6< T0,T1,T2,T3,T4,T5 >
        >
{
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7
    >
struct set8
    : s_item<
          T7
        , set7< T0,T1,T2,T3,T4,T5,T6 >
        >
{
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8
    >
struct set9
    : s_item<
          T8
        , set8< T0,T1,T2,T3,T4,T5,T6,T7 >
        >
{
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    >
struct set10
    : s_item<
          T9
        , set9< T0,T1,T2,T3,T4,T5,T6,T7,T8 >
        >
{
};

}}

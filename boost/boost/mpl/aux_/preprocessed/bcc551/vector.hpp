namespace boost { namespace mpl {

template<
      typename T0 = na, typename T1 = na, typename T2 = na, typename T3 = na
    , typename T4 = na, typename T5 = na, typename T6 = na, typename T7 = na
    , typename T8 = na, typename T9 = na
    >
struct vector;

template<
    >
struct vector< na,na,na,na,na,na,na,na,na,na >
    : vector0<  >
{
    typedef vector0<  > type;
};

template<
      typename T0
    >
struct vector< T0,na,na,na,na,na,na,na,na,na >
    : vector1<T0>
{
    typedef vector1<T0> type;
};

template<
      typename T0, typename T1
    >
struct vector< T0,T1,na,na,na,na,na,na,na,na >
    : vector2< T0,T1 >
{
    typedef vector2< T0,T1 > type;
};

template<
      typename T0, typename T1, typename T2
    >
struct vector< T0,T1,T2,na,na,na,na,na,na,na >
    : vector3< T0,T1,T2 >
{
    typedef vector3< T0,T1,T2 > type;
};

template<
      typename T0, typename T1, typename T2, typename T3
    >
struct vector< T0,T1,T2,T3,na,na,na,na,na,na >
    : vector4< T0,T1,T2,T3 >
{
    typedef vector4< T0,T1,T2,T3 > type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    >
struct vector< T0,T1,T2,T3,T4,na,na,na,na,na >
    : vector5< T0,T1,T2,T3,T4 >
{
    typedef vector5< T0,T1,T2,T3,T4 > type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct vector< T0,T1,T2,T3,T4,T5,na,na,na,na >
    : vector6< T0,T1,T2,T3,T4,T5 >
{
    typedef vector6< T0,T1,T2,T3,T4,T5 > type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6
    >
struct vector< T0,T1,T2,T3,T4,T5,T6,na,na,na >
    : vector7< T0,T1,T2,T3,T4,T5,T6 >
{
    typedef vector7< T0,T1,T2,T3,T4,T5,T6 > type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7
    >
struct vector< T0,T1,T2,T3,T4,T5,T6,T7,na,na >
    : vector8< T0,T1,T2,T3,T4,T5,T6,T7 >
{
    typedef vector8< T0,T1,T2,T3,T4,T5,T6,T7 > type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8
    >
struct vector< T0,T1,T2,T3,T4,T5,T6,T7,T8,na >
    : vector9< T0,T1,T2,T3,T4,T5,T6,T7,T8 >
{
    typedef vector9< T0,T1,T2,T3,T4,T5,T6,T7,T8 > type;
};

// primary template (not a specialization!)

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    >
struct vector
    : vector10< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9 >
{
    typedef vector10< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9 > type;
};

}}

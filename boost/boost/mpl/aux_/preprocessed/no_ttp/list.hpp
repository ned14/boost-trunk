namespace boost { namespace mpl {

template<
      typename T0 = na, typename T1 = na, typename T2 = na, typename T3 = na
    , typename T4 = na, typename T5 = na, typename T6 = na, typename T7 = na
    , typename T8 = na, typename T9 = na
    >
struct list;

template<
    >
struct list< na,na,na,na,na,na,na,na,na,na >
    : list0<  >
{
    typedef list0<  > type;
};

template<
      typename T0
    >
struct list< T0,na,na,na,na,na,na,na,na,na >
    : list1<T0>
{
    typedef list1<T0> type;
};

template<
      typename T0, typename T1
    >
struct list< T0,T1,na,na,na,na,na,na,na,na >
    : list2< T0,T1 >
{
    typedef list2< T0,T1 > type;
};

template<
      typename T0, typename T1, typename T2
    >
struct list< T0,T1,T2,na,na,na,na,na,na,na >
    : list3< T0,T1,T2 >
{
    typedef list3< T0,T1,T2 > type;
};

template<
      typename T0, typename T1, typename T2, typename T3
    >
struct list< T0,T1,T2,T3,na,na,na,na,na,na >
    : list4< T0,T1,T2,T3 >
{
    typedef list4< T0,T1,T2,T3 > type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    >
struct list< T0,T1,T2,T3,T4,na,na,na,na,na >
    : list5< T0,T1,T2,T3,T4 >
{
    typedef list5< T0,T1,T2,T3,T4 > type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct list< T0,T1,T2,T3,T4,T5,na,na,na,na >
    : list6< T0,T1,T2,T3,T4,T5 >
{
    typedef list6< T0,T1,T2,T3,T4,T5 > type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6
    >
struct list< T0,T1,T2,T3,T4,T5,T6,na,na,na >
    : list7< T0,T1,T2,T3,T4,T5,T6 >
{
    typedef list7< T0,T1,T2,T3,T4,T5,T6 > type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7
    >
struct list< T0,T1,T2,T3,T4,T5,T6,T7,na,na >
    : list8< T0,T1,T2,T3,T4,T5,T6,T7 >
{
    typedef list8< T0,T1,T2,T3,T4,T5,T6,T7 > type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8
    >
struct list< T0,T1,T2,T3,T4,T5,T6,T7,T8,na >
    : list9< T0,T1,T2,T3,T4,T5,T6,T7,T8 >
{
    typedef list9< T0,T1,T2,T3,T4,T5,T6,T7,T8 > type;
};

// primary template (not a specialization!)

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    >
struct list
    : list10< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9 >
{
    typedef list10< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9 > type;
};

}}

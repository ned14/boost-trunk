// preprocessed version of 'boost/mpl/list_c.hpp' header
// see the original for copyright information

namespace boost {
namespace mpl {

template<
      typename T
    , long C0 = LONG_MAX, long C1 = LONG_MAX, long C2 = LONG_MAX
    , long C3 = LONG_MAX, long C4 = LONG_MAX, long C5 = LONG_MAX
    , long C6 = LONG_MAX, long C7 = LONG_MAX, long C8 = LONG_MAX
    , long C9 = LONG_MAX
    >
struct list_c;

template<
      typename T
     
    >
struct list_c<
          T, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : list0_c<T>
{
    typedef list0_c<T> type;
};

template<
      typename T
    , long C0
    >
struct list_c<
          T, C0, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX
        >
    : list1_c< T,C0 >
{
    typedef list1_c< T,C0 > type;
};

template<
      typename T
    , long C0, long C1
    >
struct list_c<
          T, C0, C1, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX
        >
    : list2_c< T,C0,C1 >
{
    typedef list2_c< T,C0,C1 > type;
};

template<
      typename T
    , long C0, long C1, long C2
    >
struct list_c<
          T, C0, C1, C2, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX
        >
    : list3_c< T,C0,C1,C2 >
{
    typedef list3_c< T,C0,C1,C2 > type;
};

template<
      typename T
    , long C0, long C1, long C2, long C3
    >
struct list_c<
          T, C0, C1, C2, C3, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX
        >
    : list4_c< T,C0,C1,C2,C3 >
{
    typedef list4_c< T,C0,C1,C2,C3 > type;
};

template<
      typename T
    , long C0, long C1, long C2, long C3, long C4
    >
struct list_c<
          T, C0, C1, C2, C3, C4, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX
        >
    : list5_c< T,C0,C1,C2,C3,C4 >
{
    typedef list5_c< T,C0,C1,C2,C3,C4 > type;
};

template<
      typename T
    , long C0, long C1, long C2, long C3, long C4, long C5
    >
struct list_c<
          T, C0, C1, C2, C3, C4, C5, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : list6_c< T,C0,C1,C2,C3,C4,C5 >
{
    typedef list6_c< T,C0,C1,C2,C3,C4,C5 > type;
};

template<
      typename T
    , long C0, long C1, long C2, long C3, long C4, long C5, long C6
    >
struct list_c< T,C0,C1,C2,C3,C4,C5,C6,LONG_MAX,LONG_MAX,LONG_MAX >
    : list7_c< T,C0,C1,C2,C3,C4,C5,C6 >
{
    typedef list7_c< T,C0,C1,C2,C3,C4,C5,C6 > type;
};

template<
      typename T
    , long C0, long C1, long C2, long C3, long C4, long C5, long C6, long C7
    >
struct list_c< T,C0,C1,C2,C3,C4,C5,C6,C7,LONG_MAX,LONG_MAX >
    : list8_c< T,C0,C1,C2,C3,C4,C5,C6,C7 >
{
    typedef list8_c< T,C0,C1,C2,C3,C4,C5,C6,C7 > type;
};

template<
      typename T
    , long C0, long C1, long C2, long C3, long C4, long C5, long C6, long C7
    , long C8
    >
struct list_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,LONG_MAX >
    : list9_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8 >
{
    typedef list9_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8 > type;
};

// primary template (not a specialization!)
template<
      typename T
    , long C0, long C1, long C2, long C3, long C4, long C5, long C6, long C7
    , long C8, long C9
    >
struct list_c
    : list10_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9 >
{
    typedef list10_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9 > type;
};

} // namespace mpl
} // namespace boost


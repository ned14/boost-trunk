// preprocessed version of 'boost/mpl/vector/vector40.hpp' header
// see the original for copyright information

namespace boost {
namespace mpl {

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    , typename T20, typename T21, typename T22, typename T23, typename T24
    , typename T25, typename T26, typename T27, typename T28, typename T29
    , typename T30
    >
struct vector31
{
    typedef aux::vector_tag<31> tag;
    typedef vector31 type;
    typedef T0 item0;
    typedef T1 item1;
    typedef T2 item2;
    typedef T3 item3;
    typedef T4 item4;
    typedef T5 item5;
    typedef T6 item6;
    typedef T7 item7;
    typedef T8 item8;
    typedef T9 item9;
    typedef T10 item10;
    typedef T11 item11;
    typedef T12 item12;
    typedef T13 item13;
    typedef T14 item14;
    typedef T15 item15;
    typedef T16 item16;
    typedef T17 item17;
    typedef T18 item18;
    typedef T19 item19;
    typedef T20 item20;
    typedef T21 item21;
    typedef T22 item22;
    typedef T23 item23;
    typedef T24 item24;
    typedef T25 item25;
    typedef T26 item26;
    typedef T27 item27;
    typedef T28 item28;
    typedef T29 item29;
    typedef T30 item30;
    
    typedef void_ item31;
    typedef T30 back;
    typedef vector_iterator< type,integral_c<long,0> > begin;
    typedef vector_iterator< type,integral_c<long,31> > end;
};

template<>
struct push_back_traits< aux::vector_tag< 30> >
{
    template< typename Vector, typename T > struct algorithm
    {
        typedef vector31<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , T
            > type;
    };
};

template<>
struct pop_back_traits< aux::vector_tag< 31> >
{
    template< typename Vector > struct algorithm
    {
        typedef vector30<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            > type;
    };
};

namespace aux {
template<> struct vector_item_impl<31>
{
    template< typename V > struct result_
    {
        typedef typename V::item31 type;
    };
};
}

template<>
struct front_traits< aux::vector_tag< 31> >
{
    template< typename Vector > struct algorithm
    {
        typedef typename Vector::front type;
    };
};

template<>
struct back_traits< aux::vector_tag< 31> >
{
    template< typename Vector > struct algorithm
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_traits< aux::vector_tag< 31> >
{
    template< typename Vector > struct algorithm
        : false_c
    {
    };
};

template<>
struct size_traits< aux::vector_tag< 31> >
{
    template< typename Vector > struct algorithm
        : integral_c< int,31 >
    {
    };
};

template<>
struct O1_size_traits< aux::vector_tag< 31> >
    : size_traits< aux::vector_tag< 31> >
{
};

template<>
struct clear_traits< aux::vector_tag< 31> >
{
    template< typename Vector > struct algorithm
    {
        typedef vector0<> type;
    };
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    , typename T20, typename T21, typename T22, typename T23, typename T24
    , typename T25, typename T26, typename T27, typename T28, typename T29
    , typename T30, typename T31
    >
struct vector32
{
    typedef aux::vector_tag<32> tag;
    typedef vector32 type;
    typedef T0 item0;
    typedef T1 item1;
    typedef T2 item2;
    typedef T3 item3;
    typedef T4 item4;
    typedef T5 item5;
    typedef T6 item6;
    typedef T7 item7;
    typedef T8 item8;
    typedef T9 item9;
    typedef T10 item10;
    typedef T11 item11;
    typedef T12 item12;
    typedef T13 item13;
    typedef T14 item14;
    typedef T15 item15;
    typedef T16 item16;
    typedef T17 item17;
    typedef T18 item18;
    typedef T19 item19;
    typedef T20 item20;
    typedef T21 item21;
    typedef T22 item22;
    typedef T23 item23;
    typedef T24 item24;
    typedef T25 item25;
    typedef T26 item26;
    typedef T27 item27;
    typedef T28 item28;
    typedef T29 item29;
    typedef T30 item30;
    typedef T31 item31;
    
    typedef void_ item32;
    typedef T31 back;
    typedef vector_iterator< type,integral_c<long,0> > begin;
    typedef vector_iterator< type,integral_c<long,32> > end;
};

template<>
struct push_back_traits< aux::vector_tag< 31> >
{
    template< typename Vector, typename T > struct algorithm
    {
        typedef vector32<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30
            , T
            > type;
    };
};

template<>
struct pop_back_traits< aux::vector_tag< 32> >
{
    template< typename Vector > struct algorithm
    {
        typedef vector31<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30
            > type;
    };
};

namespace aux {
template<> struct vector_item_impl<32>
{
    template< typename V > struct result_
    {
        typedef typename V::item32 type;
    };
};
}

template<>
struct front_traits< aux::vector_tag< 32> >
{
    template< typename Vector > struct algorithm
    {
        typedef typename Vector::front type;
    };
};

template<>
struct back_traits< aux::vector_tag< 32> >
{
    template< typename Vector > struct algorithm
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_traits< aux::vector_tag< 32> >
{
    template< typename Vector > struct algorithm
        : false_c
    {
    };
};

template<>
struct size_traits< aux::vector_tag< 32> >
{
    template< typename Vector > struct algorithm
        : integral_c< int,32 >
    {
    };
};

template<>
struct O1_size_traits< aux::vector_tag< 32> >
    : size_traits< aux::vector_tag< 32> >
{
};

template<>
struct clear_traits< aux::vector_tag< 32> >
{
    template< typename Vector > struct algorithm
    {
        typedef vector0<> type;
    };
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    , typename T20, typename T21, typename T22, typename T23, typename T24
    , typename T25, typename T26, typename T27, typename T28, typename T29
    , typename T30, typename T31, typename T32
    >
struct vector33
{
    typedef aux::vector_tag<33> tag;
    typedef vector33 type;
    typedef T0 item0;
    typedef T1 item1;
    typedef T2 item2;
    typedef T3 item3;
    typedef T4 item4;
    typedef T5 item5;
    typedef T6 item6;
    typedef T7 item7;
    typedef T8 item8;
    typedef T9 item9;
    typedef T10 item10;
    typedef T11 item11;
    typedef T12 item12;
    typedef T13 item13;
    typedef T14 item14;
    typedef T15 item15;
    typedef T16 item16;
    typedef T17 item17;
    typedef T18 item18;
    typedef T19 item19;
    typedef T20 item20;
    typedef T21 item21;
    typedef T22 item22;
    typedef T23 item23;
    typedef T24 item24;
    typedef T25 item25;
    typedef T26 item26;
    typedef T27 item27;
    typedef T28 item28;
    typedef T29 item29;
    typedef T30 item30;
    typedef T31 item31;
    typedef T32 item32;
    
    typedef void_ item33;
    typedef T32 back;
    typedef vector_iterator< type,integral_c<long,0> > begin;
    typedef vector_iterator< type,integral_c<long,33> > end;
};

template<>
struct push_back_traits< aux::vector_tag< 32> >
{
    template< typename Vector, typename T > struct algorithm
    {
        typedef vector33<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , T
            > type;
    };
};

template<>
struct pop_back_traits< aux::vector_tag< 33> >
{
    template< typename Vector > struct algorithm
    {
        typedef vector32<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            > type;
    };
};

namespace aux {
template<> struct vector_item_impl<33>
{
    template< typename V > struct result_
    {
        typedef typename V::item33 type;
    };
};
}

template<>
struct front_traits< aux::vector_tag< 33> >
{
    template< typename Vector > struct algorithm
    {
        typedef typename Vector::front type;
    };
};

template<>
struct back_traits< aux::vector_tag< 33> >
{
    template< typename Vector > struct algorithm
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_traits< aux::vector_tag< 33> >
{
    template< typename Vector > struct algorithm
        : false_c
    {
    };
};

template<>
struct size_traits< aux::vector_tag< 33> >
{
    template< typename Vector > struct algorithm
        : integral_c< int,33 >
    {
    };
};

template<>
struct O1_size_traits< aux::vector_tag< 33> >
    : size_traits< aux::vector_tag< 33> >
{
};

template<>
struct clear_traits< aux::vector_tag< 33> >
{
    template< typename Vector > struct algorithm
    {
        typedef vector0<> type;
    };
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    , typename T20, typename T21, typename T22, typename T23, typename T24
    , typename T25, typename T26, typename T27, typename T28, typename T29
    , typename T30, typename T31, typename T32, typename T33
    >
struct vector34
{
    typedef aux::vector_tag<34> tag;
    typedef vector34 type;
    typedef T0 item0;
    typedef T1 item1;
    typedef T2 item2;
    typedef T3 item3;
    typedef T4 item4;
    typedef T5 item5;
    typedef T6 item6;
    typedef T7 item7;
    typedef T8 item8;
    typedef T9 item9;
    typedef T10 item10;
    typedef T11 item11;
    typedef T12 item12;
    typedef T13 item13;
    typedef T14 item14;
    typedef T15 item15;
    typedef T16 item16;
    typedef T17 item17;
    typedef T18 item18;
    typedef T19 item19;
    typedef T20 item20;
    typedef T21 item21;
    typedef T22 item22;
    typedef T23 item23;
    typedef T24 item24;
    typedef T25 item25;
    typedef T26 item26;
    typedef T27 item27;
    typedef T28 item28;
    typedef T29 item29;
    typedef T30 item30;
    typedef T31 item31;
    typedef T32 item32;
    typedef T33 item33;
    
    typedef void_ item34;
    typedef T33 back;
    typedef vector_iterator< type,integral_c<long,0> > begin;
    typedef vector_iterator< type,integral_c<long,34> > end;
};

template<>
struct push_back_traits< aux::vector_tag< 33> >
{
    template< typename Vector, typename T > struct algorithm
    {
        typedef vector34<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32
            , T
            > type;
    };
};

template<>
struct pop_back_traits< aux::vector_tag< 34> >
{
    template< typename Vector > struct algorithm
    {
        typedef vector33<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32
            > type;
    };
};

namespace aux {
template<> struct vector_item_impl<34>
{
    template< typename V > struct result_
    {
        typedef typename V::item34 type;
    };
};
}

template<>
struct front_traits< aux::vector_tag< 34> >
{
    template< typename Vector > struct algorithm
    {
        typedef typename Vector::front type;
    };
};

template<>
struct back_traits< aux::vector_tag< 34> >
{
    template< typename Vector > struct algorithm
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_traits< aux::vector_tag< 34> >
{
    template< typename Vector > struct algorithm
        : false_c
    {
    };
};

template<>
struct size_traits< aux::vector_tag< 34> >
{
    template< typename Vector > struct algorithm
        : integral_c< int,34 >
    {
    };
};

template<>
struct O1_size_traits< aux::vector_tag< 34> >
    : size_traits< aux::vector_tag< 34> >
{
};

template<>
struct clear_traits< aux::vector_tag< 34> >
{
    template< typename Vector > struct algorithm
    {
        typedef vector0<> type;
    };
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    , typename T20, typename T21, typename T22, typename T23, typename T24
    , typename T25, typename T26, typename T27, typename T28, typename T29
    , typename T30, typename T31, typename T32, typename T33, typename T34
    >
struct vector35
{
    typedef aux::vector_tag<35> tag;
    typedef vector35 type;
    typedef T0 item0;
    typedef T1 item1;
    typedef T2 item2;
    typedef T3 item3;
    typedef T4 item4;
    typedef T5 item5;
    typedef T6 item6;
    typedef T7 item7;
    typedef T8 item8;
    typedef T9 item9;
    typedef T10 item10;
    typedef T11 item11;
    typedef T12 item12;
    typedef T13 item13;
    typedef T14 item14;
    typedef T15 item15;
    typedef T16 item16;
    typedef T17 item17;
    typedef T18 item18;
    typedef T19 item19;
    typedef T20 item20;
    typedef T21 item21;
    typedef T22 item22;
    typedef T23 item23;
    typedef T24 item24;
    typedef T25 item25;
    typedef T26 item26;
    typedef T27 item27;
    typedef T28 item28;
    typedef T29 item29;
    typedef T30 item30;
    typedef T31 item31;
    typedef T32 item32;
    typedef T33 item33;
    typedef T34 item34;
    
    typedef void_ item35;
    typedef T34 back;
    typedef vector_iterator< type,integral_c<long,0> > begin;
    typedef vector_iterator< type,integral_c<long,35> > end;
};

template<>
struct push_back_traits< aux::vector_tag< 34> >
{
    template< typename Vector, typename T > struct algorithm
    {
        typedef vector35<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32, typename Vector::item33
            , T
            > type;
    };
};

template<>
struct pop_back_traits< aux::vector_tag< 35> >
{
    template< typename Vector > struct algorithm
    {
        typedef vector34<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32, typename Vector::item33
            > type;
    };
};

namespace aux {
template<> struct vector_item_impl<35>
{
    template< typename V > struct result_
    {
        typedef typename V::item35 type;
    };
};
}

template<>
struct front_traits< aux::vector_tag< 35> >
{
    template< typename Vector > struct algorithm
    {
        typedef typename Vector::front type;
    };
};

template<>
struct back_traits< aux::vector_tag< 35> >
{
    template< typename Vector > struct algorithm
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_traits< aux::vector_tag< 35> >
{
    template< typename Vector > struct algorithm
        : false_c
    {
    };
};

template<>
struct size_traits< aux::vector_tag< 35> >
{
    template< typename Vector > struct algorithm
        : integral_c< int,35 >
    {
    };
};

template<>
struct O1_size_traits< aux::vector_tag< 35> >
    : size_traits< aux::vector_tag< 35> >
{
};

template<>
struct clear_traits< aux::vector_tag< 35> >
{
    template< typename Vector > struct algorithm
    {
        typedef vector0<> type;
    };
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    , typename T20, typename T21, typename T22, typename T23, typename T24
    , typename T25, typename T26, typename T27, typename T28, typename T29
    , typename T30, typename T31, typename T32, typename T33, typename T34
    , typename T35
    >
struct vector36
{
    typedef aux::vector_tag<36> tag;
    typedef vector36 type;
    typedef T0 item0;
    typedef T1 item1;
    typedef T2 item2;
    typedef T3 item3;
    typedef T4 item4;
    typedef T5 item5;
    typedef T6 item6;
    typedef T7 item7;
    typedef T8 item8;
    typedef T9 item9;
    typedef T10 item10;
    typedef T11 item11;
    typedef T12 item12;
    typedef T13 item13;
    typedef T14 item14;
    typedef T15 item15;
    typedef T16 item16;
    typedef T17 item17;
    typedef T18 item18;
    typedef T19 item19;
    typedef T20 item20;
    typedef T21 item21;
    typedef T22 item22;
    typedef T23 item23;
    typedef T24 item24;
    typedef T25 item25;
    typedef T26 item26;
    typedef T27 item27;
    typedef T28 item28;
    typedef T29 item29;
    typedef T30 item30;
    typedef T31 item31;
    typedef T32 item32;
    typedef T33 item33;
    typedef T34 item34;
    typedef T35 item35;
    
    typedef void_ item36;
    typedef T35 back;
    typedef vector_iterator< type,integral_c<long,0> > begin;
    typedef vector_iterator< type,integral_c<long,36> > end;
};

template<>
struct push_back_traits< aux::vector_tag< 35> >
{
    template< typename Vector, typename T > struct algorithm
    {
        typedef vector36<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32, typename Vector::item33
            , typename Vector::item34
            , T
            > type;
    };
};

template<>
struct pop_back_traits< aux::vector_tag< 36> >
{
    template< typename Vector > struct algorithm
    {
        typedef vector35<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32, typename Vector::item33
            , typename Vector::item34
            > type;
    };
};

namespace aux {
template<> struct vector_item_impl<36>
{
    template< typename V > struct result_
    {
        typedef typename V::item36 type;
    };
};
}

template<>
struct front_traits< aux::vector_tag< 36> >
{
    template< typename Vector > struct algorithm
    {
        typedef typename Vector::front type;
    };
};

template<>
struct back_traits< aux::vector_tag< 36> >
{
    template< typename Vector > struct algorithm
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_traits< aux::vector_tag< 36> >
{
    template< typename Vector > struct algorithm
        : false_c
    {
    };
};

template<>
struct size_traits< aux::vector_tag< 36> >
{
    template< typename Vector > struct algorithm
        : integral_c< int,36 >
    {
    };
};

template<>
struct O1_size_traits< aux::vector_tag< 36> >
    : size_traits< aux::vector_tag< 36> >
{
};

template<>
struct clear_traits< aux::vector_tag< 36> >
{
    template< typename Vector > struct algorithm
    {
        typedef vector0<> type;
    };
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    , typename T20, typename T21, typename T22, typename T23, typename T24
    , typename T25, typename T26, typename T27, typename T28, typename T29
    , typename T30, typename T31, typename T32, typename T33, typename T34
    , typename T35, typename T36
    >
struct vector37
{
    typedef aux::vector_tag<37> tag;
    typedef vector37 type;
    typedef T0 item0;
    typedef T1 item1;
    typedef T2 item2;
    typedef T3 item3;
    typedef T4 item4;
    typedef T5 item5;
    typedef T6 item6;
    typedef T7 item7;
    typedef T8 item8;
    typedef T9 item9;
    typedef T10 item10;
    typedef T11 item11;
    typedef T12 item12;
    typedef T13 item13;
    typedef T14 item14;
    typedef T15 item15;
    typedef T16 item16;
    typedef T17 item17;
    typedef T18 item18;
    typedef T19 item19;
    typedef T20 item20;
    typedef T21 item21;
    typedef T22 item22;
    typedef T23 item23;
    typedef T24 item24;
    typedef T25 item25;
    typedef T26 item26;
    typedef T27 item27;
    typedef T28 item28;
    typedef T29 item29;
    typedef T30 item30;
    typedef T31 item31;
    typedef T32 item32;
    typedef T33 item33;
    typedef T34 item34;
    typedef T35 item35;
    typedef T36 item36;
    
    typedef void_ item37;
    typedef T36 back;
    typedef vector_iterator< type,integral_c<long,0> > begin;
    typedef vector_iterator< type,integral_c<long,37> > end;
};

template<>
struct push_back_traits< aux::vector_tag< 36> >
{
    template< typename Vector, typename T > struct algorithm
    {
        typedef vector37<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32, typename Vector::item33
            , typename Vector::item34, typename Vector::item35
            , T
            > type;
    };
};

template<>
struct pop_back_traits< aux::vector_tag< 37> >
{
    template< typename Vector > struct algorithm
    {
        typedef vector36<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32, typename Vector::item33
            , typename Vector::item34, typename Vector::item35
            > type;
    };
};

namespace aux {
template<> struct vector_item_impl<37>
{
    template< typename V > struct result_
    {
        typedef typename V::item37 type;
    };
};
}

template<>
struct front_traits< aux::vector_tag< 37> >
{
    template< typename Vector > struct algorithm
    {
        typedef typename Vector::front type;
    };
};

template<>
struct back_traits< aux::vector_tag< 37> >
{
    template< typename Vector > struct algorithm
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_traits< aux::vector_tag< 37> >
{
    template< typename Vector > struct algorithm
        : false_c
    {
    };
};

template<>
struct size_traits< aux::vector_tag< 37> >
{
    template< typename Vector > struct algorithm
        : integral_c< int,37 >
    {
    };
};

template<>
struct O1_size_traits< aux::vector_tag< 37> >
    : size_traits< aux::vector_tag< 37> >
{
};

template<>
struct clear_traits< aux::vector_tag< 37> >
{
    template< typename Vector > struct algorithm
    {
        typedef vector0<> type;
    };
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    , typename T20, typename T21, typename T22, typename T23, typename T24
    , typename T25, typename T26, typename T27, typename T28, typename T29
    , typename T30, typename T31, typename T32, typename T33, typename T34
    , typename T35, typename T36, typename T37
    >
struct vector38
{
    typedef aux::vector_tag<38> tag;
    typedef vector38 type;
    typedef T0 item0;
    typedef T1 item1;
    typedef T2 item2;
    typedef T3 item3;
    typedef T4 item4;
    typedef T5 item5;
    typedef T6 item6;
    typedef T7 item7;
    typedef T8 item8;
    typedef T9 item9;
    typedef T10 item10;
    typedef T11 item11;
    typedef T12 item12;
    typedef T13 item13;
    typedef T14 item14;
    typedef T15 item15;
    typedef T16 item16;
    typedef T17 item17;
    typedef T18 item18;
    typedef T19 item19;
    typedef T20 item20;
    typedef T21 item21;
    typedef T22 item22;
    typedef T23 item23;
    typedef T24 item24;
    typedef T25 item25;
    typedef T26 item26;
    typedef T27 item27;
    typedef T28 item28;
    typedef T29 item29;
    typedef T30 item30;
    typedef T31 item31;
    typedef T32 item32;
    typedef T33 item33;
    typedef T34 item34;
    typedef T35 item35;
    typedef T36 item36;
    typedef T37 item37;
    
    typedef void_ item38;
    typedef T37 back;
    typedef vector_iterator< type,integral_c<long,0> > begin;
    typedef vector_iterator< type,integral_c<long,38> > end;
};

template<>
struct push_back_traits< aux::vector_tag< 37> >
{
    template< typename Vector, typename T > struct algorithm
    {
        typedef vector38<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32, typename Vector::item33
            , typename Vector::item34, typename Vector::item35
            , typename Vector::item36
            , T
            > type;
    };
};

template<>
struct pop_back_traits< aux::vector_tag< 38> >
{
    template< typename Vector > struct algorithm
    {
        typedef vector37<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32, typename Vector::item33
            , typename Vector::item34, typename Vector::item35
            , typename Vector::item36
            > type;
    };
};

namespace aux {
template<> struct vector_item_impl<38>
{
    template< typename V > struct result_
    {
        typedef typename V::item38 type;
    };
};
}

template<>
struct front_traits< aux::vector_tag< 38> >
{
    template< typename Vector > struct algorithm
    {
        typedef typename Vector::front type;
    };
};

template<>
struct back_traits< aux::vector_tag< 38> >
{
    template< typename Vector > struct algorithm
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_traits< aux::vector_tag< 38> >
{
    template< typename Vector > struct algorithm
        : false_c
    {
    };
};

template<>
struct size_traits< aux::vector_tag< 38> >
{
    template< typename Vector > struct algorithm
        : integral_c< int,38 >
    {
    };
};

template<>
struct O1_size_traits< aux::vector_tag< 38> >
    : size_traits< aux::vector_tag< 38> >
{
};

template<>
struct clear_traits< aux::vector_tag< 38> >
{
    template< typename Vector > struct algorithm
    {
        typedef vector0<> type;
    };
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    , typename T20, typename T21, typename T22, typename T23, typename T24
    , typename T25, typename T26, typename T27, typename T28, typename T29
    , typename T30, typename T31, typename T32, typename T33, typename T34
    , typename T35, typename T36, typename T37, typename T38
    >
struct vector39
{
    typedef aux::vector_tag<39> tag;
    typedef vector39 type;
    typedef T0 item0;
    typedef T1 item1;
    typedef T2 item2;
    typedef T3 item3;
    typedef T4 item4;
    typedef T5 item5;
    typedef T6 item6;
    typedef T7 item7;
    typedef T8 item8;
    typedef T9 item9;
    typedef T10 item10;
    typedef T11 item11;
    typedef T12 item12;
    typedef T13 item13;
    typedef T14 item14;
    typedef T15 item15;
    typedef T16 item16;
    typedef T17 item17;
    typedef T18 item18;
    typedef T19 item19;
    typedef T20 item20;
    typedef T21 item21;
    typedef T22 item22;
    typedef T23 item23;
    typedef T24 item24;
    typedef T25 item25;
    typedef T26 item26;
    typedef T27 item27;
    typedef T28 item28;
    typedef T29 item29;
    typedef T30 item30;
    typedef T31 item31;
    typedef T32 item32;
    typedef T33 item33;
    typedef T34 item34;
    typedef T35 item35;
    typedef T36 item36;
    typedef T37 item37;
    typedef T38 item38;
    
    typedef void_ item39;
    typedef T38 back;
    typedef vector_iterator< type,integral_c<long,0> > begin;
    typedef vector_iterator< type,integral_c<long,39> > end;
};

template<>
struct push_back_traits< aux::vector_tag< 38> >
{
    template< typename Vector, typename T > struct algorithm
    {
        typedef vector39<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32, typename Vector::item33
            , typename Vector::item34, typename Vector::item35
            , typename Vector::item36, typename Vector::item37
            , T
            > type;
    };
};

template<>
struct pop_back_traits< aux::vector_tag< 39> >
{
    template< typename Vector > struct algorithm
    {
        typedef vector38<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32, typename Vector::item33
            , typename Vector::item34, typename Vector::item35
            , typename Vector::item36, typename Vector::item37
            > type;
    };
};

namespace aux {
template<> struct vector_item_impl<39>
{
    template< typename V > struct result_
    {
        typedef typename V::item39 type;
    };
};
}

template<>
struct front_traits< aux::vector_tag< 39> >
{
    template< typename Vector > struct algorithm
    {
        typedef typename Vector::front type;
    };
};

template<>
struct back_traits< aux::vector_tag< 39> >
{
    template< typename Vector > struct algorithm
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_traits< aux::vector_tag< 39> >
{
    template< typename Vector > struct algorithm
        : false_c
    {
    };
};

template<>
struct size_traits< aux::vector_tag< 39> >
{
    template< typename Vector > struct algorithm
        : integral_c< int,39 >
    {
    };
};

template<>
struct O1_size_traits< aux::vector_tag< 39> >
    : size_traits< aux::vector_tag< 39> >
{
};

template<>
struct clear_traits< aux::vector_tag< 39> >
{
    template< typename Vector > struct algorithm
    {
        typedef vector0<> type;
    };
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    , typename T20, typename T21, typename T22, typename T23, typename T24
    , typename T25, typename T26, typename T27, typename T28, typename T29
    , typename T30, typename T31, typename T32, typename T33, typename T34
    , typename T35, typename T36, typename T37, typename T38, typename T39
    >
struct vector40
{
    typedef aux::vector_tag<40> tag;
    typedef vector40 type;
    typedef T0 item0;
    typedef T1 item1;
    typedef T2 item2;
    typedef T3 item3;
    typedef T4 item4;
    typedef T5 item5;
    typedef T6 item6;
    typedef T7 item7;
    typedef T8 item8;
    typedef T9 item9;
    typedef T10 item10;
    typedef T11 item11;
    typedef T12 item12;
    typedef T13 item13;
    typedef T14 item14;
    typedef T15 item15;
    typedef T16 item16;
    typedef T17 item17;
    typedef T18 item18;
    typedef T19 item19;
    typedef T20 item20;
    typedef T21 item21;
    typedef T22 item22;
    typedef T23 item23;
    typedef T24 item24;
    typedef T25 item25;
    typedef T26 item26;
    typedef T27 item27;
    typedef T28 item28;
    typedef T29 item29;
    typedef T30 item30;
    typedef T31 item31;
    typedef T32 item32;
    typedef T33 item33;
    typedef T34 item34;
    typedef T35 item35;
    typedef T36 item36;
    typedef T37 item37;
    typedef T38 item38;
    typedef T39 item39;
    
    typedef void_ item40;
    typedef T39 back;
    typedef vector_iterator< type,integral_c<long,0> > begin;
    typedef vector_iterator< type,integral_c<long,40> > end;
};

template<>
struct push_back_traits< aux::vector_tag< 39> >
{
    template< typename Vector, typename T > struct algorithm
    {
        typedef vector40<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32, typename Vector::item33
            , typename Vector::item34, typename Vector::item35
            , typename Vector::item36, typename Vector::item37
            , typename Vector::item38
            , T
            > type;
    };
};

template<>
struct pop_back_traits< aux::vector_tag< 40> >
{
    template< typename Vector > struct algorithm
    {
        typedef vector39<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32, typename Vector::item33
            , typename Vector::item34, typename Vector::item35
            , typename Vector::item36, typename Vector::item37
            , typename Vector::item38
            > type;
    };
};

namespace aux {
template<> struct vector_item_impl<40>
{
    template< typename V > struct result_
    {
        typedef typename V::item40 type;
    };
};
}

template<>
struct front_traits< aux::vector_tag< 40> >
{
    template< typename Vector > struct algorithm
    {
        typedef typename Vector::front type;
    };
};

template<>
struct back_traits< aux::vector_tag< 40> >
{
    template< typename Vector > struct algorithm
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_traits< aux::vector_tag< 40> >
{
    template< typename Vector > struct algorithm
        : false_c
    {
    };
};

template<>
struct size_traits< aux::vector_tag< 40> >
{
    template< typename Vector > struct algorithm
        : integral_c< int,40 >
    {
    };
};

template<>
struct O1_size_traits< aux::vector_tag< 40> >
    : size_traits< aux::vector_tag< 40> >
{
};

template<>
struct clear_traits< aux::vector_tag< 40> >
{
    template< typename Vector > struct algorithm
    {
        typedef vector0<> type;
    };
};

} // namespace mpl
} // namespace boost


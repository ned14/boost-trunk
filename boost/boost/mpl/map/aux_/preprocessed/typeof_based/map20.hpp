namespace boost { namespace mpl {

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10
    >
struct map11
    : m_item<
          typename P10::first
        , typename P10::second
        , map10< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9 >
        >
{
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11
    >
struct map12
    : m_item<
          typename P11::first
        , typename P11::second
        , map11< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10 >
        >
{
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12
    >
struct map13
    : m_item<
          typename P12::first
        , typename P12::second
        , map12< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11 >
        >
{
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13
    >
struct map14
    : m_item<
          typename P13::first
        , typename P13::second
        , map13< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12 >
        >
{
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    >
struct map15
    : m_item<
          typename P14::first
        , typename P14::second
        , map14< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13 >
        >
{
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    , typename P15
    >
struct map16
    : m_item<
          typename P15::first
        , typename P15::second
        , map15< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14 >
        >
{
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    , typename P15, typename P16
    >
struct map17
    : m_item<
          typename P16::first
        , typename P16::second
        , map16< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15 >
        >
{
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    , typename P15, typename P16, typename P17
    >
struct map18
    : m_item<
          typename P17::first
        , typename P17::second
        , map17< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16 >
        >
{
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    , typename P15, typename P16, typename P17, typename P18
    >
struct map19
    : m_item<
          typename P18::first
        , typename P18::second
        , map18< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17 >
        >
{
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    , typename P15, typename P16, typename P17, typename P18, typename P19
    >
struct map20
    : m_item<
          typename P19::first
        , typename P19::second
        , map19< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18 >
        >
{
};

}}

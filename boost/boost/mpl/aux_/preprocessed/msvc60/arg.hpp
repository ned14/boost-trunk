namespace boost { namespace mpl {
template<> struct arg<-1>
{
    enum { value = -1 };
    BOOST_MPL_AUX_ARG_TYPEDEF(void_, tag)
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U1 type;

     private:
        enum { nv = !is_na<type>::value };
        BOOST_STATIC_ASSERT(nv);
    };
};

template<> struct arg<1>
{
    enum { value = 1 };
    typedef arg<2> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(void_, tag)
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U1 type;

     private:
        enum { nv = !is_na<type>::value };
        BOOST_STATIC_ASSERT(nv);
    };
};

template<> struct arg<2>
{
    enum { value = 2 };
    typedef arg<3> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(void_, tag)
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U2 type;

     private:
        enum { nv = !is_na<type>::value };
        BOOST_STATIC_ASSERT(nv);
    };
};

template<> struct arg<3>
{
    enum { value = 3 };
    typedef arg<4> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(void_, tag)
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U3 type;

     private:
        enum { nv = !is_na<type>::value };
        BOOST_STATIC_ASSERT(nv);
    };
};

template<> struct arg<4>
{
    enum { value = 4 };
    typedef arg<5> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(void_, tag)
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U4 type;

     private:
        enum { nv = !is_na<type>::value };
        BOOST_STATIC_ASSERT(nv);
    };
};

template<> struct arg<5>
{
    enum { value = 5 };
    typedef arg<6> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(void_, tag)
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U5 type;

     private:
        enum { nv = !is_na<type>::value };
        BOOST_STATIC_ASSERT(nv);
    };
};

BOOST_MPL_AUX_NONTYPE_ARITY_SPEC(1, int, arg)
}}

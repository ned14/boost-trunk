// preprocessed version of 'boost/mpl/lambda_no_ctps.hpp' header
// see the original for copyright information

namespace boost {
namespace mpl {

namespace aux {

template< int arity > struct lambda_impl
{
    template< typename T > struct result_
    {
        typedef T type;
    };
};

template<> struct lambda_impl<1>
{
    template< typename F > struct result_
    {
        typedef typename F::rebind f_;
        typedef bind1<
              f_
            , typename lambda< typename f_::arg1 >::type
            > type;
    };
};

template<> struct lambda_impl<2>
{
    template< typename F > struct result_
    {
        typedef typename F::rebind f_;
        typedef bind2<
              f_
            
            ,typename lambda< typename f_::arg1 >::type, typename lambda< typename f_::arg2 >::type
            > type;
    };
};

template<> struct lambda_impl<3>
{
    template< typename F > struct result_
    {
        typedef typename F::rebind f_;
        typedef bind3<
              f_
            
            ,typename lambda< typename f_::arg1 >::type, typename lambda< typename f_::arg2 >::type, typename lambda< typename f_::arg3 >::type
            > type;
    };
};

template<> struct lambda_impl<4>
{
    template< typename F > struct result_
    {
        typedef typename F::rebind f_;
        typedef bind4<
              f_
            
            ,typename lambda< typename f_::arg1 >::type, typename lambda< typename f_::arg2 >::type, typename lambda< typename f_::arg3 >::type, typename lambda< typename f_::arg4 >::type
            > type;
    };
};

template<> struct lambda_impl<5>
{
    template< typename F > struct result_
    {
        typedef typename F::rebind f_;
        typedef bind5<
              f_
            
            ,typename lambda< typename f_::arg1 >::type, typename lambda< typename f_::arg2 >::type, typename lambda< typename f_::arg3 >::type, typename lambda< typename f_::arg4 >::type, typename lambda< typename f_::arg5 >::type
            > type;
    };
};

} // namespace aux

template< typename T >
struct lambda
    : aux::lambda_impl< ::boost::mpl::aux::template_arity<T>::value >
        ::template result_<T>
{
};

} // namespace mpl
} // namespace boost


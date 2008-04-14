//   Boost pow.hpp header file
//   Computes a power with exponent known at compile-time

//  (C) Copyright Bruno Lalande 2008.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.


#ifndef BOOST_MATH_POW_HPP
#define BOOST_MATH_POW_HPP


#include <boost/math/policies/policy.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/tools/promotion.hpp>
#include <boost/mpl/greater_equal.hpp>


namespace boost {
namespace math {


namespace detail {


template <int N>
struct positive_power;

template <>
struct positive_power<0>
{
    template <typename T>
    static typename tools::promote_args<T>::type result(T)
    { return 1; }
};

template <>
struct positive_power<2>
{
    template <typename T>
    static typename tools::promote_args<T>::type result(T base)
    { return base*base; }
};

template <int N>
struct positive_power
{
    template <typename T>
    static typename tools::promote_args<T>::type result(T base)
    {
        return (N%2) ? base*positive_power<N-1>::result(base)
                     : positive_power<2>::result(
                           positive_power<N/2>::result(base)
                       );
    }
};


template <int N, bool>
struct power_if_positive
{
    template <typename T, class Policy>
    static typename tools::promote_args<T>::type result(T base, const Policy&)
    { return positive_power<N>::result(base); }
};

template <int N>
struct power_if_positive<N, false>
{
    template <typename T, class Policy>
    static typename tools::promote_args<T>::type
    result(T base, const Policy& policy)
    {
        if (base == 0)
        {
            return policies::raise_overflow_error<T>(
                       "boost::math::pow(%1%)",
                       "Attempted to compute a negative power of 0",
                       policy
                   );
        }

        return T(1) / positive_power<-N>::result(base);
    }
};


template <int N>
struct select_power_if_positive
{
    typedef typename mpl::greater_equal<
                         mpl::int_<N>,
                         mpl::int_<0>
                     >::type is_positive;

    typedef power_if_positive<N, is_positive::value> type;
};


}  // namespace detail


template <int N, typename T, class Policy>
inline typename tools::promote_args<T>::type pow(T base, const Policy& policy)
{ return detail::select_power_if_positive<N>::type::result(base, policy); }


template <int N, typename T>
inline typename tools::promote_args<T>::type pow(T base)
{ return pow<N>(base, policies::policy<>()); }


}  // namespace math
}  // namespace boost


#endif

// test file for special_functions.hpp

//  (C) Copyright Hubert Holin 2001. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.


#define    BOOST_SPECIAL_FUNCTIONS_TEST_VERBOSE    0


#include <algorithm>
#include <iostream>
#include <iomanip>
#include <complex>

#include <boost/math/special_functions/atanh.hpp>
#include <boost/math/special_functions/asinh.hpp>
#include <boost/math/special_functions/acosh.hpp>
#include <boost/math/special_functions/sinc.hpp>
#include <boost/math/special_functions/sinhc.hpp>


#define BOOST_INCLUDE_MAIN  // for testing, include rather than link
#include <boost/test/test_tools.hpp>


template<typename T>
T    atanh_error_evaluator(T x)
{
    using    ::std::abs;
    using    ::std::tanh;
    using    ::std::cosh;
        
    using    ::std::numeric_limits;
    
    using    ::boost::math::atanh;
    
    
    static T const    epsilon = numeric_limits<float>::epsilon();
    
    T                y = tanh(x);
    T                z = atanh(y);
    
    T                absolute_error = abs(z-x);
    T                relative_error = absolute_error/(cosh(x)*cosh(x));
    T                scaled_error = relative_error/epsilon;
    
    return(scaled_error);
}


template<typename T>
T    asinh_error_evaluator(T x)
{
    using    ::std::abs;
    using    ::std::sinh;
    using    ::std::cosh;
        
    using    ::std::numeric_limits;
    
    using    ::boost::math::asinh;
    
    
    static T const    epsilon = numeric_limits<float>::epsilon();
    
    T                y = sinh(x);
    T                z = asinh(y);
    
    T                absolute_error = abs(z-x);
    T                relative_error = absolute_error*cosh(x);
    T                scaled_error = relative_error/epsilon;
    
    return(scaled_error);
}


template<typename T>
T    acosh_error_evaluator(T x)
{
    using    ::std::abs;
    using    ::std::sinh;
    using    ::std::cosh;
        
    using    ::std::numeric_limits;
    
    using    ::boost::math::acosh;
    
    
    static T const    epsilon = numeric_limits<float>::epsilon();
    
    T                y = cosh(x);
    T                z = acosh(y);
    
    T                absolute_error = abs(z-abs(x));
    T                relative_error = absolute_error*abs(sinh(x));
    T                scaled_error = relative_error/epsilon;
    
    return(scaled_error);
}


int    test_main(int, char *[])

{
    using    ::std::abs;
    using    ::std::sin;
    using    ::std::log;
    using    ::std::tanh;
    using    ::std::sinh;
    using    ::std::cosh;
        
    using    ::std::numeric_limits;
    
    using    ::boost::math::atanh;
    using    ::boost::math::asinh;
    using    ::boost::math::acosh;
    using    ::boost::math::sinc_pi;
    using    ::boost::math::sinhc_pi;
    
    
    // tests for evaluation by humans
    
#if    BOOST_SPECIAL_FUNCTIONS_TEST_VERBOSE
    ::std::cout << "epsilon" << ::std::endl;
    
    ::std::cout << ::std::setw(15) << numeric_limits<float>::epsilon()
                << ::std::setw(15) << numeric_limits<double>::epsilon()
                << ::std::setw(15) << numeric_limits<long double>::epsilon()
                << ::std::endl;
    
    ::std::cout << ::std::endl << ::std::endl;
    
    ::std::cout << "atanh" << ::std::endl;
    
    for    (int i = 0; i <= 100; i++)
    {
        float          xf = static_cast<float>(i-50)/static_cast<float>(5);
        double         xd = static_cast<double>(i-50)/static_cast<double>(5);
        long double    xl = static_cast<long double>(i-50)/static_cast<long double>(5);
        
        float          yf = tanh(xf);
        double         yd = tanh(xd);
        long double    yl = tanh(xl);
        
        if    (
                std::numeric_limits<float>::has_infinity &&
                std::numeric_limits<double>::has_infinity &&
                std::numeric_limits<long double>::has_infinity
            )
        {
            ::std:: cout << ::std::setw(15)
                         << atanh_error_evaluator(xf)
                         << ::std::setw(15)
                         << atanh_error_evaluator(xd)
                         << ::std::setw(15)
                         << atanh_error_evaluator(xl)
                         << ::std::endl;
        }
        else
        {
            if    (
                    (abs(yf-static_cast<float>(1)) <
                        numeric_limits<float>::epsilon())||
                    (abs(yf+static_cast<float>(1)) <
                        numeric_limits<float>::epsilon())||
                    (abs(yf-static_cast<double>(1)) <
                        numeric_limits<double>::epsilon())||
                    (abs(yf+static_cast<double>(1)) <
                        numeric_limits<double>::epsilon())||
                    (abs(yf-static_cast<long double>(1)) <
                        numeric_limits<long double>::epsilon())||
                    (abs(yf+static_cast<long double>(1)) <
                        numeric_limits<long double>::epsilon())
                )
            {
                ::std::cout << "Platform's numerics may lack precision."
                            << ::std::endl;
            }
            else
            {
                ::std:: cout << ::std::setw(15)
                             << atanh_error_evaluator(xf)
                             << ::std::setw(15)
                             << atanh_error_evaluator(xd)
                             << ::std::setw(15)
                             << atanh_error_evaluator(xl)
                             << ::std::endl;
            }
        }
    }
    
    ::std::cout << ::std::endl << ::std::endl;
    
    ::std::cout << "asinh" << ::std::endl;
    
    for    (int i = 0; i <= 100; i++)
    {
        float          xf = static_cast<float>(i-50)/static_cast<float>(5);
        double         xd = static_cast<double>(i-50)/static_cast<double>(5);
        long double    xl = static_cast<long double>(i-50)/static_cast<long double>(5);
        
        ::std:: cout << ::std::setw(15)
                     << asinh_error_evaluator(xf)
                     << ::std::setw(15)
                     << asinh_error_evaluator(xd)
                     << ::std::setw(15)
                     << asinh_error_evaluator(xl)
                     << ::std::endl;
    }
    
    ::std::cout << ::std::endl << ::std::endl;
    
    ::std::cout << "acosh" << ::std::endl;
    
    for    (int i = 0; i <= 100; i++)
    {
        float          xf = static_cast<float>(i-50)/static_cast<float>(5);
        double         xd = static_cast<double>(i-50)/static_cast<double>(5);
        long double    xl = static_cast<long double>(i-50)/static_cast<long double>(5);
        
        ::std:: cout << ::std::setw(15)
                     << acosh_error_evaluator(xf)
                     << ::std::setw(15)
                     << acosh_error_evaluator(xd)
                     << ::std::setw(15)
                     << acosh_error_evaluator(xl)
                     << ::std::endl;
    }
    
    ::std::cout << ::std::endl << ::std::endl;
    
    ::std::cout << "sinc_pi" << ::std::endl;
    
    for    (int i = 0; i <= 100; i++)
    {
        ::std::cout << ::std::setw(15)
                    << sinc_pi<float>(static_cast<float>(i-50)/
                                                static_cast<float>(50))
                    << ::std::setw(15)
                    << sinc_pi<double>(static_cast<double>(i-50)/
                                                static_cast<double>(50))
                    << ::std::setw(15)
                    << sinc_pi<long double>(static_cast<long double>(i-50)/
                                                static_cast<long double>(50))
                    << ::std::endl;
    }
    
    ::std::cout << ::std::endl << ::std::endl;
    
    ::std::cout << "sinhc_pi" << ::std::endl;
    
    for    (int i = 0; i <= 100; i++)
    {
        ::std::cout << ::std::setw(15)
                    << sinhc_pi<float>(static_cast<float>(i-50)/
                                                static_cast<float>(50))
                    << ::std::setw(15)
                    << sinhc_pi<double>(static_cast<double>(i-50)/
                                                static_cast<double>(50))
                    << ::std::setw(15)
                    << sinhc_pi<long double>(static_cast<long double>(i-50)/
                                                static_cast<long double>(50))
                    << ::std::endl;
    }
    
    ::std::cout << ::std::endl << ::std::endl;
#endif    /* BOOST_SPECIAL_FUNCTIONS_TEST_VERBOSE */
    
    
    // tests for evaluation by scripts
    
#define    BOOST_SPECIAL_FUNCTIONS_TEST_ATANH(type)                         \
                                                                            \
    ::std::cout << "Testing atanh in the real domain." << ::std::endl;      \
                                                                            \
    BOOST_TEST(abs(atanh<type>(static_cast<type>(0))) <=                    \
        numeric_limits<type>::epsilon());                                   \
                                                                            \
    BOOST_TEST(abs(atanh<type>(static_cast<type>(3)/5)-                     \
        log(static_cast<type>(2))) <=                                       \
        numeric_limits<type>::epsilon());                                   \
                                                                            \
    BOOST_TEST(abs(atanh<type>(static_cast<type>(-3)/5)+                    \
        log(static_cast<type>(2))) <=                                       \
        numeric_limits<type>::epsilon());                                   \
                                                                            \
    for    (int i = 0; i <= 100; i++)                                       \
    {                                                                       \
        type        x = static_cast<type>(i-50)/static_cast<type>(5);       \
        type        y = tanh(x);                                            \
                                                                            \
        if    (                                                             \
                (abs(y-static_cast<type>(1)) >=                             \
                    numeric_limits<type>::epsilon())&&                      \
                (abs(y+static_cast<type>(1)) >=                             \
                    numeric_limits<type>::epsilon())                        \
            )                                                               \
        {                                                                   \
            BOOST_TEST(atanh_error_evaluator(x) <= static_cast<type>(4));   \
        }                                                                   \
    }
        


#define    BOOST_SPECIAL_FUNCTIONS_TEST_ASINH(type)                     \
                                                                        \
    ::std::cout << "Testing asinh in the real domain." << ::std::endl;  \
                                                                        \
    for    (int i = 0; i <= 100; i++)                                   \
    {                                                                   \
        type    x = static_cast<type>(i-50)/static_cast<type>(5);       \
                                                                        \
        BOOST_TEST(asinh_error_evaluator(x) <= static_cast<type>(4));   \
    }


#define    BOOST_SPECIAL_FUNCTIONS_TEST_ACOSH(type)                     \
                                                                        \
    ::std::cout << "Testing acosh in the real domain." << ::std::endl;  \
                                                                        \
    for    (int i = 0; i <= 100; i++)                                   \
    {                                                                   \
        type    x = static_cast<type>(i-50)/static_cast<type>(5);       \
                                                                        \
        BOOST_TEST(acosh_error_evaluator(x) <= static_cast<type>(4));   \
    }
    
    
#define    BOOST_SPECIAL_FUNCTIONS_TEST_SINC_PI(type)                       \
                                                                            \
    ::std::cout << "Testing sinc_pi in the real domain." << ::std::endl;    \
                                                                            \
    BOOST_TEST(abs(sinc_pi<type>(static_cast<type>(0))-                     \
        static_cast<type>(1)) <=                                            \
        numeric_limits<type>::epsilon());
    
#define    BOOST_SPECIAL_FUNCTIONS_TEST_SINC_PI_FOR_C(type)                 \
                                                                            \
    ::std::cout << "Testing sinc_pi in the complex domain." << ::std::endl; \
                                                                            \
    BOOST_TEST(abs(sinc_pi<type>(::std::complex<type>(0, 1))-               \
        ::std::complex<type>(sinh(static_cast<type>(1)))) <=                \
        numeric_limits<type>::epsilon());
    
    
#define    BOOST_SPECIAL_FUNCTIONS_TEST_SINHC_PI(type)                      \
                                                                            \
    ::std::cout << "Testing sinhc_pi in the real domain." << ::std::endl;   \
                                                                            \
    BOOST_TEST(abs(sinhc_pi<type>(static_cast<type>(0))-                    \
        static_cast<type>(1)) <=                                            \
        numeric_limits<type>::epsilon());
    
#define    BOOST_SPECIAL_FUNCTIONS_TEST_SINHC_PI_FOR_C(type)                \
                                                                            \
    ::std::cout << "Testing sinhc_pi in the complex domain." << ::std::endl;\
                                                                            \
    BOOST_TEST(abs(sinhc_pi<type>(::std::complex<type>(0, 1))-              \
        ::std::complex<type>(sin(static_cast<type>(1)))) <=                 \
        numeric_limits<type>::epsilon());
    
    
#ifdef    BOOST_NO_TEMPLATE_TEMPLATES
#define    BOOST_SPECIAL_FUNCTIONS_TEST(type)                       \
    ::std::cout << "Testing " << #type << "." << std::endl;         \
    BOOST_SPECIAL_FUNCTIONS_TEST_ATANH(type)                        \
    BOOST_SPECIAL_FUNCTIONS_TEST_ASINH(type)                        \
    BOOST_SPECIAL_FUNCTIONS_TEST_ACOSH(type)                        \
    BOOST_SPECIAL_FUNCTIONS_TEST_SINC_PI(type)                      \
    BOOST_SPECIAL_FUNCTIONS_TEST_SINHC_PI(type)                     \
    ::std::cout <<                                                  \
    "Warning: no template templates; curtailed functionality." <<   \
    ::std::endl;
#else    /* BOOST_NO_TEMPLATE_TEMPLATES */
#define    BOOST_SPECIAL_FUNCTIONS_TEST(type)               \
    ::std::cout << "Testing " << #type << "." << std::endl; \
    BOOST_SPECIAL_FUNCTIONS_TEST_ATANH(type)                \
    BOOST_SPECIAL_FUNCTIONS_TEST_ASINH(type)                \
    BOOST_SPECIAL_FUNCTIONS_TEST_ACOSH(type)                \
    BOOST_SPECIAL_FUNCTIONS_TEST_SINC_PI(type)              \
    BOOST_SPECIAL_FUNCTIONS_TEST_SINHC_PI(type)             \
    BOOST_SPECIAL_FUNCTIONS_TEST_SINC_PI_FOR_C(type)        \
    BOOST_SPECIAL_FUNCTIONS_TEST_SINHC_PI_FOR_C(type)
#endif    /* BOOST_NO_TEMPLATE_TEMPLATES */
    
    
    BOOST_SPECIAL_FUNCTIONS_TEST(float)
    BOOST_SPECIAL_FUNCTIONS_TEST(double)
    BOOST_SPECIAL_FUNCTIONS_TEST(long double)
    
    
#undef    BOOST_SPECIAL_FUNCTIONS_TEST

#undef    BOOST_SPECIAL_FUNCTIONS_TEST_ATANH
#undef    BOOST_SPECIAL_FUNCTIONS_TEST_ASINH
#undef    BOOST_SPECIAL_FUNCTIONS_TEST_ACOSH
#undef    BOOST_SPECIAL_FUNCTIONS_TEST_SINC_PI
#undef    BOOST_SPECIAL_FUNCTIONS_TEST_SINC_PI_FOR_C
#undef    BOOST_SPECIAL_FUNCTIONS_TEST_SINHC_PI
#undef    BOOST_SPECIAL_FUNCTIONS_TEST_SINHC_PI_FOR_C
    
    return(::boost::exit_success);
}

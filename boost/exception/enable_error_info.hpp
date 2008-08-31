//Copyright (c) 2006-2008 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_0C5D492E909711DCB658AD4556D89593
#define UUID_0C5D492E909711DCB658AD4556D89593

#include <boost/exception/exception.hpp>

namespace
boost
    {
    namespace
    exception_detail
        {
        template <class T>
        struct
        error_info_injector:
            public T,
            public exception
            {
            explicit
            error_info_injector( T const & x ):
                T(x)
                {
                }

            ~error_info_injector() throw()
                {
                }
            };

        struct large_size { char c[256]; };
        large_size dispatch( exception * );

        struct small_size { };
        small_size dispatch( void * );

        template <class,int>
        struct enable_error_info_helper;

        template <class T>
        struct
        enable_error_info_helper<T,sizeof(large_size)>
            {
            typedef T type;
            };

        template <class T>
        struct
        enable_error_info_helper<T,sizeof(small_size)>
            {
            typedef error_info_injector<T> type;
            };

        template <class T>
        struct
        enable_error_info_return_type
            {
            typedef typename enable_error_info_helper<T,sizeof(dispatch((T*)0))>::type type;
            };
        }

    template <class T>
    inline
    typename
    exception_detail::enable_error_info_return_type<T>::type
    enable_error_info( T const & x )
        {
        return typename exception_detail::enable_error_info_return_type<T>::type(x);
        }
    }

#endif

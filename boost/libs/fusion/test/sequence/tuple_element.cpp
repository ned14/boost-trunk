/*=============================================================================
    Copyright (c) 1999-2003 Jaakko J�rvi
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#include <boost/fusion/tuple.hpp>

#define FUSION_SEQUENCE tuple
#define FUSION_AT get
#define FUSION_VALUE_AT(S, N) tuple_element<N, S>
#include "value_at.hpp"

int
main()
{
    test();
    return boost::report_errors();
}


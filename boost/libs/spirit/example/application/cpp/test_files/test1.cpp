/*=============================================================================
    A Standard compliant C++ preprocessor

    Copyright (c) 2001-2003 Hartmut Kaiser
    Copyright (c) 2003 Paul Mensonides
    http://spirit.sourceforge.net/

    Permission to copy, use, modify, sell and distribute this software
    is granted provided this copyright notice appears in all copies.
    This software is provided "as is" without express or implied
    warranty, and with no claim as to its suitability for any purpose.

    See Copyright.txt for full copyright notices and acknowledgements.
=============================================================================*/

// Tests macro expansion order

#define A(x, y) x, y
#define B(x, y) [x][y]
#define C(x) B(x)

C( A(2, 3) )	        // should expand to [2][3]

#include <iostream>
#include <cassert>

#define PHOENIX_LIMIT 15
#include "boost/spirit/phoenix/primitives.hpp"

using namespace phoenix;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
int
main()
{
    char c1 = '1';
    int i1 = 1, i2 = 2, i = 4;
    const char* s2 = "2";

///////////////////////////////////////////////////////////////////////////////
//
//  Values, variables and arguments
//
///////////////////////////////////////////////////////////////////////////////
    cout << val("Hello")() << val(' ')() << val("World")() << endl;

    assert(arg1(c1) == c1);
    assert(arg1(i1, i2) == i1);
    assert(arg2(i1, s2) == s2);

    assert(val(3)() == 3);
    assert(var(i)() == 4);
    assert(var(++i)() == 5);

    cout << "///////////////////////////////////////////////////////////////////////////////\n";
    cout << "\t\tTests concluded\n";
    cout << "\t\tSUCCESS!!!\n";
    cout << "///////////////////////////////////////////////////////////////////////////////\n";
}

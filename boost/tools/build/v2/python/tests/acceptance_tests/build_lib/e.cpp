#include <stdio.h>
#include "x.h"

int main (int, char**)
{
    printf ("Yellow, World!\n");
    printf ("Lib call: %d\n", dummy ());
    return 0;
}


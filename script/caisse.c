#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>
#include "banking.h"
#include "cashstore.h"


int main() 
{
    struct CashStore reg;
    srand (time(NULL));          // Rand seeding
    init_array(&reg, 30);         // Initialise to 5 elements

    menu(&reg);

    free_array(&reg);            // free memory to avoid memory leaks
    return 0;
}


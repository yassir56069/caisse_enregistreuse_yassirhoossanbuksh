#ifndef BANKING_H_
#define BANKING_H_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>

#pragma region Banking Functions
// Functions explicitely used to generate and manipulate currency values as appropriate

    /* Function: gen_cash( double min, double max )
        *
        * Generates a random amount of cash for manipulation using rand().
        * 
        * Parameters:
        * min - minimum value that can be generated
        * max - maximum value that can be generated
        * 
        * Returns:
        * Generated cash value
        */
    int gen_cash( int min, int max );

    /* Function: gen_cents( int iter, int bool_s ) )
        *
        * Generates a random amount of cents.
        * 
        * This function's necessity may not be obvious, but essentially, generating double values with rand comes with various problems, notably, rand is likely to give cent values that are unorthodox for typical prices. This is why we instead generate the cents seperate a number of times to create a sense of randomness to the cent value without it being too random for it to be a logical value. The higher the iter value, the more likely it is for the cent value to be unorthodox, as we stray further away from more typical cent value. 
        * 
        * Parameters:
        * iter - number of iterations ( < 4 recommended)
        * s - acts as the function safeguard, when on it will sometimes disregard precise cent values. use this when iter is large
        * 
        * Returns:
        * Generated cent value
        */
    double gen_cents( int iter, int bool_s );

#pragma endregion 

#endif
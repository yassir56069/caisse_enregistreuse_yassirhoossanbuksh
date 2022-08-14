#include "banking.h"


#pragma region Banking Functions

    int gen_cash( int min, int max )
    {
        return ((rand() %(max - min + 1)) + min) ;
    }

    double gen_cents( int iter, int bool_s ) 
    {
        double n = 0.00;

        for (int i = 0; i < iter; i++) 
        {
            int det = rand() % 30;

            if ( det > 20) 
            {
                n += .50;
            }
            else if ( det > 10)
            {
                n += .20;
            }
            else 
            {
                n += .05;
            }
        }

        if ( bool_s == 1 )
        {
            int guard = rand() %30;
            if (guard > 20)
            {
                return n;
            }
            else if (guard > 10)
            {
                
                int det = rand() % 30;

                if ( det > 20) 
                {
                    n = .50;
                }
                else if ( det > 10)
                {
                    n = .20;
                }
                else 
                {
                    n = .05;
                }

                return n;
            }
            else 
            {
                return 0;
            }
        }
        else if (bool_s == 0)
        {
            return n;
        }
        else 
        {
            printf("bool_s should be either 0 or 1, rand function did not run..");
            return 0;
        }
    }

#pragma endregion
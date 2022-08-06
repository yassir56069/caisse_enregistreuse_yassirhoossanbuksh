#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>

#pragma region Prototypes

    #pragma region Banking Enums
    // Enums containing all value types we'll be dealing with are created, we seperate cents from the rest perform calculations later

        /* Enum: bank_notes
         *
         * Each note and it's respective value is displayed here
         */
        typedef enum 
        {
            Rs2k = 2000,
            Rs1k = 1000,
            Rs500 = 500,
            Rs200 = 200,
            Rs100 = 100,
            Rs50 = 50,
            Rs25 = 25,
            Rs20 = 20,
            Rs10 = 10,
            Rs5 = 5,
            Rs1 = 1
        } bank_notes;

        /* Enum: bank_cent
         *
         * Each cent and it's respective value is displayed here
         */
        typedef enum 
        {
            c50 = 50,
            c20 = 20,
            c5 = 5

        } bank_cents;

    #pragma endregion 

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

    #pragma region Cashstore Structure
    // Contains all methods and struct init for the CashStore Structure

        /* Struct: CashStore{}
         *
         * This structure stores all types of notes and cents in arrays with their appropriate names according to their value.
         * 
         * parts
         * *notes - the dynamic notes array
         * *cents - the dynamic cents array
         * 
         * used[2] - this is a size_t variable that stores the number of array slots used up by our 2 respective arrays.
         * size[2] - this is a size_t variable that stores the size of our 2 respective arrays.
         */
        struct CashStore 
        {
            bank_notes *notes;
            bank_cents *cents;

            /* Explanation: size_t used[2]; size_t size[2]
             * 
             * The size_t type is used to obtain a unsigned integer. This is used to store sizes of objects because they cannot be negative. Since we have 2 different dynamic arrays with varying lengths (for efficiency) 
             * these parameters are arrays themselves, where;
             * 
             * used[0] and size[0] concern the values of the *notes dynamic array 
             * 
             * and, 
             * 
             * used[1] and size[1] concern the values of the *cents dnymic array
             *
             */
            size_t used[2];
            size_t size[2];
        };
        
        #pragma region CashStore Public Methods
        //Public methods that are meant to be used with the CashStore structure.

            #pragma region Dynamic Array Methods
            // All functions manipulating the dynamic array are found here, these are used extensively to control and manage the CashStore Structure

                /* Function: init_array( struct CashStore *reg, int l )
                *
                * Sets up the dnyamic array with the minimum amount of l integers
                * 
                * Parameters:
                * *reg- points to the CashStore object, the cash register.
                * l - number of integers to store
                */
                void init_array( struct CashStore *reg, int l );

                /* Function: free_array( struct CashStore *reg )
                *
                * Frees allocated memory in the given CashStore object
                * 
                * Parameters: 
                * *reg- points to the CashStore object, the cash register.
                */
                void free_array( struct CashStore *reg );

                /* Function: ins_notes_array( bank_notes data ,struct CashStore *reg)
                * increments the size of the notes dynamic array (if needed) and adds the data given
                *
                * Parameters: 
                * data- the corresponding bank note to add to the register
                * *reg- points to the CashStore object, the cash register.
                */
                void ins_notes_array( bank_notes data , struct CashStore *reg);

                /* Function: ins_cents_array( bank_cents data ,struct CashStore *reg)
                * increments the size of the cents dynamic array (if needed) and adds the data given
                *
                * Parameters: 
                * data- the corresponding bank note to add to the register
                * *reg- points to the CashStore object, the cash register.
                */
                void ins_cents_array( bank_cents data , struct CashStore *reg);

                /* Function: PrintReg( struct CashStore *reg )
                * Displays the contents of the register structure
                *
                * Parameters: 
                * *reg- points to the CashStore object, the cash register.
                */
                void PrintReg( struct CashStore *reg );

            #pragma endregion
        
            #pragma region Cash Manipulation Methods        
            // CashStore structure methods that manipulate cash inputs and cash outputs using the notes and cents dynamic array

                /* Function: prompt_pay( double price )
                 *
                 * recursive function that prompts user to pay an amount of cash, given the price and the notes they have available
                 * 
                 * Parameters:
                 * price - the price the user has to pay
                 * *reg- points to the CashStore object, the cash register.
                 * Returns:
                 * the remainder of the calculation. if it has reached it's recursion limit condition, it'll return the change.
                 */
                double prompt_pay( double price );

                /* Function: cash_adder( double n, struct CashStore *reg )
                 *
                 * adds given cash value to the appropriate arrays.
                 * 
                 * Parameters:
                 * n - value to add to our function.
                 * *reg- points to the CashStore object, the cash register.
                 * 
                 * Returns:
                 * Remainder after subtraction from value, on end of loop, will return cents.
                 */
                double cash_adder( double n, struct CashStore *reg );

            #pragma endregion

        #pragma endregion

    #pragma endregion

#pragma endregion

int main() 
{
    struct CashStore reg;
    srand (time(NULL));          // Rand seeding

    init_array(&reg, 5);         // Initialise to 5 elements

    double change = prompt_pay((gen_cash(1,2000) + gen_cents(2, 1)));
    printf("\n\nChange: %.2f \n", change);

    cash_adder(change, &reg);

    PrintReg(&reg);              // print out cash register contents

    free_array(&reg);            // free memory to avoid memory leaks
    return 0;
}

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

#pragma region CashStore Public Methods

    #pragma region Dynamic Array Methods

        void init_array( struct CashStore *reg, int l ) 
        {
            reg->notes = malloc(l * sizeof(int));
            reg->cents = malloc(l * sizeof(int));

            for (int i = 0 ; i < 2; i++) 
            {
                reg->used[i] = 0;
                reg->size[i] = l;
            }
        }

        void ins_notes_array( bank_notes data , struct CashStore *reg) 
        {
            if (reg->used[0] == reg->size[0]) 
            {
                reg->size[0] *= 2;
                reg->notes = realloc(reg->notes, reg->size[0] * sizeof(int));
            }

            /* Explanation of reg->notes[reg->used[0]++]= data
            *
            * reg->notes is our notes dynamic array, we are trying to access the last element of it that has not been taken up. our array must then access the element at reg->used[0] ++. This is because used keeps track of
            * the latest element that has been used in memory already. Keep in mind that this calculation will also automatically increment the value of our used size_t variable. 
            */
            reg->notes[reg->used[0]++] = data;
        }

        void ins_cents_array( bank_cents data , struct CashStore *reg) 
        {
            if (reg->used[1] == reg->size[1]) 
            {
                reg->size[1] *= 2;
                reg->cents = realloc(reg->cents, reg->size[1] * sizeof(int));
            }

            reg->cents[reg->used[1]++] = data;
        }

        void free_array( struct CashStore *reg )
        {
            free(reg->notes);
            free(reg->cents);

            reg->notes = NULL;
            reg->cents = NULL;

            for (int i =0 ; i < 2; i++) 
            {
                reg->used[i] = reg->size[i] = 0;
            }
        
        }

        void PrintReg( struct CashStore *reg )
        { 
            printf("Notes/Coins in array: ");
            for( int i = 0; i < reg->used[0] ; i++) 
            {
                printf(": %d\n", reg->notes[i]);
            }

            printf("Cents in array: ");
            for( int i = 0; i < reg->used[1] ; i++) 
            {
                printf(": %d\n", reg->cents[i]);
            }
        }

    #pragma endregion

    #pragma region Cash Manipulation Methods

    double prompt_pay( double price ) 
    {
        int c;
        double give = 0, disp = 0;
        while (  give < price)
        {
            c = 0;
            disp = price - give;
            printf("\n Current Sum: %.2f", disp);
            printf("\nEnter a montery to pay with: ");
            printf("\n1) Rs 2000");
            printf("\n2) Rs 1000");
            printf("\n3) Rs 500");
            printf("\n4) Rs 200");
            printf("\n5) Rs 100");
            printf("\n6) Rs 50");
            printf("\n7) Rs 25");
            printf("\n8) Rs 20");
            printf("\n9) Rs 10");
            printf("\n10) Rs 5");
            printf("\n11) Rs 1");
            printf("\n12) Cn 50");
            printf("\n13) Cn 20");
            printf("\n14) Cn 5");

            printf("\nChoice: ");

            scanf("%d", &c);

            switch(c) 
            {
                case 1:
                    give += Rs2k;
                    break;

                case 2:
                    give += Rs1k;
                    break;
                case 3:
                    give += Rs500;
                    break;
                case 4:
                    give += Rs200;
                    break;
                case 5:
                    give += Rs100;
                    break;
                case 6:
                    give += Rs50;
                    break;
                case 7:
                    give += Rs25;
                    break;
                case 8:
                    give += Rs20;
                    break;
                case 9:
                    give += Rs10;
                    break;
                case 10:
                    give += Rs5;
                    break;
                case 11:
                    give += Rs1;
                    break;
                case 12:
                    give += (c50/100.00);
                    break;
                case 13:
                    give += (c20/100.00);
                    break;
                case 14:
                    give += (c5/100.00);
                    break;

                default:
                    printf("\nPlease enter a valid value..\n\n");

                printf("%lf", give);
            }
        }

        return (give - price);
    }

    double cash_adder( double n, struct CashStore *reg) 
    {
       while ( n > 0.04 ) // while n >= 5 cents
        {

            if ( n >= 2000 ) 
            {
                ins_notes_array(Rs2k, reg);
                n -= (Rs2k + .0);
            }
            else if (n >= 1000)
            {
                ins_notes_array(Rs1k, reg);
                n -= (Rs1k + .0);
            }
            else if (n >= 500)
            {
                ins_notes_array(Rs500, reg);
                n -= (Rs500  + .0);
            }
            else if (n >= 200)
            {
                ins_notes_array(Rs200, reg);
                n -= (Rs200 + .0);
            }
            else if (n >= 100)
            {
                ins_notes_array(Rs100, reg);
                n -= (Rs100 + .0);
            }
            else if (n >= 50)
            {
                ins_notes_array(Rs50, reg);
                n -= (Rs50 + .0);
            }
            else if (n >= 25)
            {
                ins_notes_array(Rs25, reg);
                n -= (Rs25 + .0);
            }
            else if (n >= 20)
            {
                ins_notes_array(Rs20, reg);
                n -= (Rs20 + .0);
            }
            else if (n >= 10)
            {
                ins_notes_array(Rs10, reg);
                n -= (Rs10 + .0);
            }
            else if (n >= 5)
            {
                ins_notes_array(Rs5, reg);
                n -= (Rs5 + .0);
            } 
            else if (n >= 1)
            {
                ins_notes_array(Rs1, reg);
                n -= (Rs1 + .0);
            }
            else if (n >= 0.5) 
            {
                ins_cents_array(c50, reg);
                n -= 0.50;
            }
            else if (n >= 0.2)
            {
                ins_cents_array(c20, reg);
                n -= 0.20;
            }
            else 
            {
                ins_cents_array(c5, reg);
                n -= 0.05;
            }
        }
        return n;
    }
    
#pragma endregion

#pragma endregion

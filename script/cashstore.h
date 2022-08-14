#ifndef CASHSTORE_H_
#define CASHSTORE_H_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h> 

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

            /* Function: rem_notes_array(int search, struct CashStore *reg)
            * decrement the size of the notes dynamic array upon finding the value searched inside of it, incase the value is not found, returns 0
            *
            * Parameters: 
            * search- the value to search for in the notes array
            * *reg- points to the CashStore object, the cash register.
            */
            int rem_notes_array(bank_notes search, struct CashStore *reg);

            /* Function: rem_cents_array(int search, struct CashStore *reg)
            * decrement the size of the cents dynamic array upon finding the value searched inside of it, incase the value is not found, returns 0
            *
            * Parameters: 
            * search- the value to search for in the cents array
            * *reg- points to the CashStore object, the cash register.
            */
            double rem_cents_array(bank_cents search, struct CashStore *reg);

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

            /* Function: prompt_pay( double price, struct CashStore *reg  )
            *
            * recursive function that prompts user to pay an amount of cash, given the price and the notes they have available
            * 
            * Parameters:
            * price - the price the user has to pay
            * *reg- points to the CashStore object, the cash register.
            * 
            * Returns:
            * the remainder of the calculation. if it has reached it's recursion limit condition, it'll return the change.
            */
            double prompt_pay( double price, struct CashStore *reg );

            /* Function: cash_subber( double n, struct CashStore *reg )
            *
            * subs given cash value to the appropriate arrays.
            * 
            * Parameters:
            * n - value to subtract from our function.
            * *reg- points to the CashStore object, the cash register.
            * 
            * Returns:
            * Remainder after subtraction from value, on end of loop, will return cents.
            */
            double cash_subber( double n, struct CashStore *reg );

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

            /* Function: prompt_cash(struct CashStore *reg)
            *
            * prompts user to add cash to register
            * 
            * Parameters:
            * *reg- points to the CashStore object, the cash register.
            */                
            void prompt_cash(struct CashStore *reg);
            
            /* Function: out_of_cash(int repay, struct CashStore *reg)
            *
            * runs whenever register runs out of a bill that is needed. proves 2 choices (close program or re-fill money)
            * 
            * Parameters:
            * repay - amount that still needs to be paid to the customer
            * *reg- points to the CashStore object, the cash register.
            */                
            double out_of_cash(double repay, struct CashStore *reg);

        #pragma endregion

    #pragma endregion


    #pragma region menus

        /* Function: menu()
        *
        * This function acts as the menu for the register, letting the user decide where to proceed (add to register, conduct transaction or exit)
        * 
        * Parameters:
        * *reg- points to the CashStore object, the cash register.
        */
        void menu(struct CashStore *reg);


        /* Function: transaction(struct CashStore *reg) 
        *
        * This function commits a single transaction before feeding back into the menu
        * 
        * Parameters:
        * *reg- points to the CashStore object, the cash register.
        */
        void transaction(struct CashStore *reg);

    #pragma endregion

#pragma endregion

#endif
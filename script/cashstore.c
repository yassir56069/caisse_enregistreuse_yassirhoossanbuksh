#include "cashstore.h"
#include "banking.h"


#pragma region Menus
    
    void menu(struct CashStore *reg) 
    {
        int c = 0;
        while ( c != 4) // exit condition
        {
            printf("Welcome to your cash register! what actions would you like to perform?");
            printf("\n1] add cash to register");
            printf("\n2] conduct transaction");
            printf("\n3] view register contents");
            printf("\n4] exit");
            printf("\nChoice: ");
            scanf("%d", &c);

            switch(c) 
            {
                case 1:
                    prompt_cash(reg);
                    break;

                case 2:
                    transaction(reg);
                    break;

                case 3:
                    PrintReg(reg);

                case 4:
                    exit(1);
                    break;

                default:
                    printf("\n Please enter a valid value.. \n\n");
            }

        }

    }

    void transaction(struct CashStore *reg) 
    {
        double change = prompt_pay((gen_cash(1,2000) + gen_cents(2, 1)), reg);
        
        printf("\n\nChange: %.2f \n", change);

        cash_subber(change, reg);


        PrintReg(reg);              // print out cash register contents
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
                reg->notes = realloc(reg->notes, reg->size[0] * sizeof(reg->notes[0]));
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
                reg->cents = realloc(reg->cents, reg->size[1] * sizeof(reg->cents[0]));
            }

            reg->cents[reg->used[1]++] = data;
        }

        int rem_notes_array(bank_notes search, struct CashStore *reg)
        {
            int index = -1, flag = 0; // flag = 1 -> found
            for (int i = 0; i < reg->size[0]; i++) 
            {
                if ( reg->notes[i] == search) 
                {
                    index = i;
                    flag = 1;
                    break;
                }
            }

            if (flag == 1) 
            {
                int elements_to_move = reg->size[0] - index - 1;
                memmove( &reg->notes[index], &reg->notes[index+1], elements_to_move * sizeof(reg->notes[0]));
                reg->size[0]--;
                reg->used[0]--;
                return flag;
            }
            else 
            {
                return search;
            }
        }

        double rem_cents_array(bank_cents search, struct CashStore *reg)
        {
            int index = -1, flag = 0; // flag = -1 -> found
            for (int i = 0; i < reg->size[1]; i++) 
            {
                if ( reg->cents[i] == search) 
                {
                    index = i;
                    flag = -1;
                    break;
                }
            }

            if (flag == 1)
            {
                int elements_to_move = reg->size[1] - index - 1;
                memmove( &reg->cents[index], &reg->cents[index+1], elements_to_move * sizeof(reg->cents[0]));
                reg->size[1]--;
                reg->used[1]--;
                return flag;
            }
            else 
            {
                return (search / 100.0);
            }
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
            printf("Notes/Coins in array: \n");
            for( int i = 0; i < reg->used[0] ; i++) 
            {
                printf(": %d\n", reg->notes[i]);
            }

            printf("Cents in array: \n");
            for( int i = 0; i < reg->used[1] ; i++) 
            {
                printf(": %d\n", reg->cents[i]);
            }
            printf("\n\n");
        }

    #pragma endregion

    #pragma region Cash Manipulation Methods

    double prompt_pay( double price, struct CashStore *reg ) 
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
                    ins_notes_array(Rs2k, reg);
                    give += Rs2k;
                    break;

                case 2:
                    ins_notes_array(Rs1k, reg);
                    give += Rs1k;
                    break;
                case 3:
                    ins_notes_array(Rs500, reg);
                    give += Rs500;
                    break;
                case 4:
                    ins_notes_array(Rs200, reg);
                    give += Rs200;
                    break;
                case 5:
                    ins_notes_array(Rs100, reg);
                    give += Rs100;
                    break;
                case 6:
                    ins_notes_array(Rs50, reg);
                    give += Rs50;
                    break;
                case 7:
                    ins_notes_array(Rs25, reg);
                    give += Rs25;
                    break;
                case 8:
                    ins_notes_array(Rs20, reg);
                    give += Rs20;
                    break;
                case 9:
                    ins_notes_array(Rs10, reg);
                    give += Rs10;
                    break;
                case 10:
                    ins_notes_array(Rs5, reg);
                    give += Rs5;
                    break;
                case 11:
                    ins_notes_array(Rs1, reg);
                    give += Rs1;
                    break;
                case 12:
                    ins_cents_array(c50, reg);
                    give += (c50/100.00);
                    break;
                case 13:
                    ins_cents_array(c20, reg);
                    give += (c20/100.00);
                    break;
                case 14:
                    ins_cents_array(c5, reg);
                    give += (c5/100.00);
                    break;

                default:
                    printf("\nPlease enter a valid value..\n\n");

                printf("%lf", give);
            }
        }

        return (give - price);
    }

    double cash_subber( double n, struct CashStore *reg) 
    {
        double have_flag = -1; // have_flag = -1 --> we still have the specified bill
        
        while ( n > 0.04 ) // while n >= 5 cents
        {

            if ( n >= 2000 ) 
            {
                have_flag = rem_notes_array(Rs2k, reg);
                n -= (Rs2k + .0);
            }
            else if (n >= 1000)
            {
                have_flag = rem_notes_array(Rs1k, reg);
                n -= (Rs1k + .0);
            }
            else if (n >= 500)
            {
                have_flag = rem_notes_array(Rs500, reg);
                n -= (Rs500  + .0);
            }
            else if (n >= 200)
            {
                have_flag = rem_notes_array(Rs200, reg);
                n -= (Rs200 + .0);
            }
            else if (n >= 100)
            {
                have_flag = rem_notes_array(Rs100, reg);
                n -= (Rs100 + .0);
            }
            else if (n >= 50)
            {
                have_flag = rem_notes_array(Rs50, reg);
                n -= (Rs50 + .0);
            }
            else if (n >= 25)
            {
                have_flag = rem_notes_array(Rs25, reg);
                n -= (Rs25 + .0);
            }
            else if (n >= 20)
            {
                have_flag = rem_notes_array(Rs20, reg);
                n -= (Rs20 + .0);
            }
            else if (n >= 10)
            {
                have_flag = rem_notes_array(Rs10, reg);
                n -= (Rs10 + .0);
            }
            else if (n >= 5)
            {
                have_flag = rem_notes_array(Rs5, reg);
                n -= (Rs5 + .0);
            } 
            else if (n >= 1)
            {
                have_flag = rem_notes_array(Rs1, reg);
                n -= (Rs1 + .0);
            }
            else if (n >= 0.5) 
            {
                have_flag = rem_cents_array(c50, reg);
                n -= 0.50;
            }
            else if (n >= 0.2)
            {
                have_flag = rem_cents_array(c20, reg);
                n -= 0.20;
            }
            else 
            {
                have_flag = rem_cents_array(c5, reg);
                n -= 0.05;
            }

            if (have_flag != -1) 
            {
                printf("have_flag value: %lf", have_flag);
                printf("n value: %lf", n);

                out_of_cash(have_flag, reg);
            }
        }
        return 0.0;
    }

    double cash_adder( double n, struct CashStore *reg) 
    {
        while ( n > 0.04 ) // while n >= 5 cents
        {

            if ( n >= 2000 ) 
            {
                ins_notes_array(Rs2k, reg);
                n -= (Rs2k);
            }
            else if (n >= 1000)
            {
                ins_notes_array(Rs1k, reg);
                n -= (Rs1k);
            }
            else if (n >= 500)
            {
                ins_notes_array(Rs500, reg);
                n -= (Rs500);
            }
            else if (n >= 200)
            {
                ins_notes_array(Rs200, reg);
                n -= (Rs200);
            }
            else if (n >= 100)
            {
                ins_notes_array(Rs100, reg);
                n -= (Rs100);
            }
            else if (n >= 50)
            {
                ins_notes_array(Rs50, reg);
                n -= (Rs50);
            }
            else if (n >= 25)
            {
                ins_notes_array(Rs25, reg);
                n -= (Rs25);
            }
            else if (n >= 20)
            {
                ins_notes_array(Rs20, reg);
                n -= (Rs20);
            }
            else if (n >= 10)
            {
                ins_notes_array(Rs10, reg);
                n -= (Rs10);
            }
            else if (n >= 5)
            {
                ins_notes_array(Rs5, reg);
                n -= (Rs5);
            } 
            else if (n >= 1)
            {
                ins_notes_array(Rs1, reg);
                n -= (Rs1);
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

    void prompt_cash(struct CashStore *reg)
    {
        double n;
        printf("\n\n");
        printf("How much money would you like to add to the register? : ");
        scanf("%lf", &n);

        cash_adder(n, reg);
        
        printf("\n Amount successfully added!\n");
    }

    double out_of_cash(double repay, struct CashStore *reg)
    {
        int c = -1;
        printf("\nyou have run out of funds to complete the transaction [NEED %lf], what would you like to do?", repay);
        printf("\n1 ] Add needed cash amount to register.");
        printf("\n2 ] Close to menu. (cancels transaction)");
        printf("\n3 ] Exit program.");
        printf("\n Choice: ");

        scanf("%d", &c);

        switch (c)
        {
            case 1:
            {
                break;
            }
            case 2:
            {
                menu(reg);
                break;
            }


            default:
            {
                exit(1);
                break;
            }
        }
    }

#pragma endregion

#pragma endregion
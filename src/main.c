#include <stdio.h>

#include "account.h"

#define MAX_ACCOUNTS 100

int main()
{
    Account accounts[MAX_ACCOUNTS];
    int count = 0;

    int choice;

    while (1)
    {
        printf("\n=== BANK SYSTEM ===\n");
        printf("1. Create account\n");
        printf("2. Display account\n");
        printf("3. Deposit\n");
        printf("4. Withdraw\n");
        printf("5. Transfer\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 0)
        {
            printf("Bye!\n");
            break;
        }

        if (choice == 1)
        {
            int id;
            char name[200];
            char password[128];

            printf("ID: ");
            scanf("%d", &id);

            printf("Name: ");
            scanf("%s", name);

            printf("Password: ");
            scanf("%s", password);

            accounts[count] = create_account(id, name, password);
            count++;

            printf("Account created!\n");
        }

        else if (choice == 2)
        {
            int id;
            printf("ID: ");
            scanf("%d", &id);

            Account *acc = find_account(accounts, count, id);

            if (acc)
                print_account(*acc);
            else
                printf("Account not found\n");
        }

        else if (choice == 3)
        {
            int id;
            float amount;

            printf("ID: ");
            scanf("%d", &id);

            Account *acc = find_account(accounts, count, id);

            if (!acc)
            {
                printf("Account not found\n");
            }
            else
            {
                printf("Amount: ");
                scanf("%f", &amount);

                deposit(acc, amount);
                printf("Deposit done!\n");
            }
        }

        else if (choice == 4)
        {
            int id;
            float amount;

            printf("ID: ");
            scanf("%d", &id);

            Account *acc = find_account(accounts, count, id);

            if (!acc)
            {
                printf("Account not found\n");
            }
            else
            {
                printf("Amount: ");
                scanf("%f", &amount);

                if (withdraw(acc, amount))
                    printf("Withdraw done!\n");
                else
                    printf("Not enough money\n");
            }
        }

        else if (choice == 5)
        {
            int from_id, to_id;
            float amount;

            printf("From ID: ");
            scanf("%d", &from_id);

            printf("To ID: ");
            scanf("%d", &to_id);

            Account *from = find_account(accounts, count, from_id);
            Account *to = find_account(accounts, count, to_id);

            if (!from || !to)
            {
                printf("Account not found\n");
            }
            else
            {
                printf("Amount: ");
                scanf("%f", &amount);

                if (transfer(from, to, amount))
                    printf("Transfer successful!\n");
                else
                    printf("Not enough money\n");
            }
        }

        else
        {
            printf("Invalid choice\n");
        }
    }

    return 0;
}
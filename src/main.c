#include <stdio.h>

#include "account.h"
#include "database.h"

#define MAX_ACCOUNTS 1000

int main()
{
    Account accounts[MAX_ACCOUNTS];
    int count = load_accounts(accounts, MAX_ACCOUNTS);
    int choice;

    while (1)
    {
        printf("\n=== BANK SYSTEM ===\n");
        printf("1. Create account\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("> ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            int id;
            char name[200], password[128];
            printf("ID: ");
            scanf("%d", &id);
            printf("Name: ");
            scanf("%s", name);
            printf("Password: ");
            scanf("%s", password);
            accounts[count++] = create_account(id, name, password);
            save_all(accounts, count);
            printf("Account created!\n");
        }
        else if (choice == 2)
        {
            int id;
            char password[128];
            printf("ID: ");
            scanf("%d", &id);
            printf("Password: ");
            scanf("%s", password);
            Account *user = login(accounts, count, id, password);
            if (!user)
            {
                printf("Login failed\n");
                continue;
            }
            int sub;
            while (1)
            {
                printf("\n1. Balance\n2. Deposit\n3. Withdraw\n4. Logout\n> ");
                scanf("%d", &sub);
                if (sub == 1)
                {
                    print_account(*user);
                }
                else if (sub == 2)
                {
                    float amount;
                    printf("Amount: ");
                    scanf("%f", &amount);
                    deposit(user, amount);
                    log_transaction("DEPOSIT", user->id, amount);
                }
                else if (sub == 3)
                {
                    float amount;
                    printf("Amount: ");
                    scanf("%f", &amount);
                    if (withdraw(user, amount))
                    {
                        log_transaction("WITHDRAW", user->id, amount);
                    }
                    else
                    {
                        printf("Not enough money\n");
                    }
                }
                else if (sub == 4)
                {
                    break;
                }

                save_all(accounts, count);
            }
        }
        else if (choice == 3)
        {
            break;
        }
    }

    return 0;
}
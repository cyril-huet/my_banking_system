#include <stdio.h>
#include <string.h>
#include "account.h"
#include "database.h"

#define MAX_ACCOUNTS 100

int main() {
    Account accounts[MAX_ACCOUNTS];
    int count = load_accounts(accounts, MAX_ACCOUNTS);

    printf("Loaded %d accounts\n", count);

    int id;
    char password[128];

    // 🔐 LOGIN
    printf("Login ID: ");
    scanf("%d", &id);

    Account *acc = find_account(accounts, count, id);

    if (!acc) {
        printf("Account not found\n");
        return 1;
    }

    printf("Password: ");
    scanf("%s", password);

    if (strcmp(acc->password, password) != 0) {
        printf("Wrong password\n");
        return 1;
    }

    printf("Login successful!\n");

    // 📱 MENU
    int choice;
    float amount;

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Deposit\n");
        printf("2. Withdraw\n");
        printf("3. Show balance\n");
        printf("4. Exit\n");
        printf("Choice: ");

        scanf("%d", &choice);

        if (choice == 1) {
            printf("Amount: ");
            scanf("%f", &amount);
            deposit(acc, amount);
            save_all(accounts, count);
            printf("Money added!\n");

        } else if (choice == 2) {
            printf("Amount: ");
            scanf("%f", &amount);
            if (!withdraw(acc, amount)) {
                printf("Not enough money\n");
            } else {
                save_all(accounts, count);
                printf("Money withdrawn!\n");
            }

        } else if (choice == 3) {
            print_account(*acc);

        } else if (choice == 4) {
            printf("Goodbye!\n");
            break;

        } else {
            printf("Invalid choice\n");
        }
    }

    return 0;
}
#include <stdio.h>
#include "account.h"
#include "database.h"

#define MAX_ACCOUNTS 100

int main() {
    Account accounts[MAX_ACCOUNTS];
    int count = load_accounts(accounts, MAX_ACCOUNTS);

    printf("Loaded %d accounts\n", count);

    int id;
    char name[200];
    char password[128];

    printf("New account ID: ");
    scanf("%d", &id);

    printf("Name: ");
    scanf("%s", name);

    printf("Password: ");
    scanf("%s", password);

    Account new_acc = create_account(id, name, password);

    save_account(new_acc);

    printf("Account saved!\n");

    return 0;
}
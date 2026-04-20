#include <stdio.h>
#include "account.h"

int main() {
    int id;
    char name[200];
    char password[128];

    printf("Enter ID: ");
    scanf("%d", &id);

    printf("Enter name: ");
    scanf("%s", name);

    printf("Enter password: ");
    scanf("%s", password);

    Account acc = create_account(id, name, password);

    float amount;

    printf("Deposit amount: ");
    scanf("%f", &amount);
    deposit(&acc, amount);

    printf("Withdraw amount: ");
    scanf("%f", &amount);
    withdraw(&acc, amount);

    print_account(acc);

    return 0;
}
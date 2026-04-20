#include <stdio.h>
#include "account.h"

void print_account(Account acc) {
    printf("ID: %d\n", acc.id);
    printf("Name: %s\n", acc.name);
    printf("Balance: %.2f\n", acc.balance);
}

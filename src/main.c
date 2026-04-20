#include <stdio.h>
#include <string.h>
#include "account.h"

int main() {
    Account acc;

    acc.id = 1;
    strcpy(acc.name, "Cyril");
    strcpy(acc.password, "1234");
    acc.balance = 100.0;

    print_account(acc);

    return 0;
}

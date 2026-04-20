#include <stdio.h>

#include "account.h"

int main()
{
    Account acc = create_account(1, "Cyril", "1234");

    deposit(&acc, 1000);
    withdraw(&acc, 200);

    print_account(acc);

    return 0;
}
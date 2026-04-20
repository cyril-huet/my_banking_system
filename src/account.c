#include "account.h"

#include <stdio.h>
#include <string.h>

Account create_account(int id, char name[], char password[])
{
    Account account;
    account.id = id;
    strcpy(account.name, name);
    strcpy(account.password, password);
    account.balance = 0.0;
    return account;
}

void deposit(Account *account, float amount)
{
    account->balance += amount;
}

int withdraw(Account *account, float amount)
{
    if (account->balance >= amount)
    {
        account->balance -= amount;
        return 1; // succès
    }
    return 0; // échec
}

void print_account(Account account)
{
    printf("ID: %d\nName: %s\nBalance: %.2f\n", account.id, account.name,
           account.balance);
}
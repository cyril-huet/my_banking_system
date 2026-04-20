#include "account.h"

#include <stdio.h>
#include <string.h>

Account create_account(int id, char *name, char *password)
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

int transfer(Account *src, Account *dst, float amount)
{
    if (src->balance < amount)
    {
        return 0;
    }

    src->balance -= amount;
    dst->balance += amount;
    return 1;
}

void save_accounts(Account accounts[], int count)
{
    FILE *file = fopen("accounts.txt", "w");

    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%d %s %s %f\n", accounts[i].id, accounts[i].name,
                accounts[i].password, accounts[i].balance);
    }

    fclose(file);
}

int load_accounts(Account accounts[])
{
    FILE *file = fopen("accounts.txt", "r");
    int count = 0;

    if (!file)
    {
        return 0;
    }

    while (fscanf(file, "%d %s %s %f", &accounts[count].id,
                  accounts[count].name, accounts[count].password,
                  &accounts[count].balance)
           != EOF)
    {
        count++;
    }

    fclose(file);
    return count;
}
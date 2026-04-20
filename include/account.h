#ifndef ACCOUNT_H
#define ACCOUNT_H

struct Account
{
    int id;
    char name[200];
    char password[128];
    float balance;
};

typedef struct Account Account;

void print_account(Account acc);
Account create_account(int id, char name[], char password[]);
void deposit(Account *acc, float amount);
int withdraw(Account *acc, float amount);

#endif
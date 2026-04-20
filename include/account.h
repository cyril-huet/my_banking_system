#ifndef ACCOUNT_H
#define ACCOUNT_H

typedef struct Account
{
    int id;
    char name[200];
    char password[128];
    float balance;
} Account;

Account create_account(int id, char *name, char *password);
void deposit(Account *account, float amount);
int withdraw(Account *account, float amount);
int transfer(Account *src, Account *dst, float amount);
void print_account(Account account);
Account *login(Account accounts[], int count, int id, char *password);

#endif
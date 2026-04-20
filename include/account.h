#ifndef ACCOUNT_H
#define ACCOUNT_H

typedef struct {
    int id;
    char name[200];
    char password[128];
    float balance;
} Account;

void print_account(Account acc);

#endif
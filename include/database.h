#ifndef DATABASE_H
#define DATABASE_H

#include "account.h"

void save_account(Account account);
int load_accounts(Account accounts[], int max);
Account *find_account(Account accounts[], int count, int id);
void save_all(Account accounts[], int count);
void log_transaction(char *type, int id, float amount);

#endif
#ifndef DATABASE_H
#define DATABASE_H

#include "account.h"

void save_account(Account acc);
int load_accounts(Account accounts[], int max);
void save_all(Account accounts[], int count);

#endif

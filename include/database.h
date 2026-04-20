#ifndef DATABASE_H
#define DATABASE_H

#include "account.h"
#include <libpq-fe.h>

void save_account(Account account);
int load_accounts(Account accounts[], int max);
Account *find_account(Account accounts[], int count, int id);
void save_all(Account accounts[], int count);
void log_transaction(char *type, int id, float amount);
PGconn *connect_db();
void db_withdraw(PGconn *conn, int id, float amount);
void db_deposit(PGconn *conn, int id, float amount);
int db_login(PGconn *conn, int id, char *password);
void db_create_account(PGconn *conn, int id, char *name, char *password);
float db_get_balance(PGconn *conn, int id);
void db_transfer(PGconn *conn, int from, int to, float amount);

#endif
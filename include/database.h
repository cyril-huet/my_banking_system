#ifndef DATABASE_H
#define DATABASE_H

#include <libpq-fe.h>

PGconn *connect_db();

int db_login(PGconn *conn, int id, char *password);
float db_get_balance(PGconn *conn, int id);
void db_deposit(PGconn *conn, int id, float amount);
int db_withdraw(PGconn *conn, int id, float amount);
void db_create_account(PGconn *conn, int id, char *name, char *password);

#endif
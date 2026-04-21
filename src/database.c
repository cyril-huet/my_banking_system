#include "database.h"
#include <stdio.h>
#include <stdlib.h>

PGconn *connect_db()
{
    PGconn *conn = PQconnectdb(
        "postgresql://postgres:xymvof-kaRhu6-rozhic@db.kdngofzabwfptjbxtnym.supabase.co:6543/postgres"
    );

    if (PQstatus(conn) != CONNECTION_OK)
    {
        printf("DB error: %s\n", PQerrorMessage(conn));
        return NULL;
    }

    return conn;
}

int db_login(PGconn *conn, int id, char *password)
{
    char query[256];
    sprintf(query,
        "SELECT * FROM accounts WHERE id=%d AND password='%s';",
        id, password);

    PGresult *res = PQexec(conn, query);
    int ok = (PQntuples(res) == 1);
    PQclear(res);
    return ok;
}

float db_get_balance(PGconn *conn, int id)
{
    char query[256];
    sprintf(query, "SELECT balance FROM accounts WHERE id=%d;", id);

    PGresult *res = PQexec(conn, query);

    if (PQntuples(res) == 1)
    {
        float b = atof(PQgetvalue(res, 0, 0));
        PQclear(res);
        return b;
    }

    PQclear(res);
    return -1;
}

void db_deposit(PGconn *conn, int id, float amount)
{
    char query[256];
    sprintf(query,
        "UPDATE accounts SET balance = balance + %f WHERE id=%d;",
        amount, id);

    PQclear(PQexec(conn, query));
}

int db_withdraw(PGconn *conn, int id, float amount)
{
    char query[256];

    sprintf(query,
        "UPDATE accounts SET balance = balance - %f WHERE id = %d AND balance >= %f;",
        amount, id, amount);

    PGresult *res = PQexec(conn, query);

    int success = PQcmdTuples(res)[0] != '0'; // si 0 lignes modifiées = échec

    PQclear(res);
    return success;
}
void db_create_account(PGconn *conn, int id, char *name, char *password)
{
    char query[512];
    sprintf(query,
        "INSERT INTO accounts (id, name, password, balance) VALUES (%d, '%s', '%s', 0);",
        id, name, password);

    PQclear(PQexec(conn, query));
}
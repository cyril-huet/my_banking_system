#include "database.h"

#include <libpq-fe.h>
#include <stdio.h>

void save_account(Account account)
{
    FILE *file = fopen("accounts.db", "ab");
    if (!file)
    {
        return;
    }

    fwrite(&account, sizeof(Account), 1, file);
    fclose(file);
}

int load_accounts(Account accounts[], int max)
{
    FILE *file = fopen("accounts.db", "rb");
    if (!file)
    {
        return 0;
    }

    int count = 0;
    while (fread(&accounts[count], sizeof(Account), 1, file) && count < max)
    {
        count++;
    }

    fclose(file);
    return count;
}

Account *find_account(Account accounts[], int count, int id)
{
    for (int i = 0; i < count; i++)
    {
        if (accounts[i].id == id)
        {
            return &accounts[i];
        }
    }
    return NULL;
}

void save_all(Account accounts[], int count)
{
    FILE *file = fopen("accounts.db", "wb");
    if (!file)
    {
        return;
    }

    fwrite(accounts, sizeof(Account), count, file);
    fclose(file);
}

void log_transaction(char *type, int id, float amount)
{
    FILE *file = fopen("transactions.log", "a");
    if (!file)
    {
        return;
    }

    fprintf(file, "%s | ID:%d | Amount: %.2f\n", type, id, amount);
    fclose(file);
}



PGconn *connect_db()
{
    PGconn *res = PQconnectdb(
        "postgresql://postgres:xymvof-kaRhu6-rozhic@db.kdngofzabwfptjbxtnym.supabase.co:5432/postgres?sslmode=require"
    );

    if (PQstatus(res) != CONNECTION_OK)
    {
        printf("Connection failed: %s\n", PQerrorMessage(res));
        PQfinish(res);
        return NULL;
    }

    printf("Connected to Supabase!\n");
    return res;
}


void db_create_account(PGconn *conn, int id, char *name, char *password)
{
    char query[512];

    sprintf(query,"INSERT INTO accounts (id, name, password, balance) VALUES (%d, '%s', '%s', 0);", id, name, password);

    PGresult *res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        printf("Insert failed: %s\n", PQerrorMessage(conn));
    }
    else
    {
        printf("Account created in DB!\n");
    }

    PQclear(res);
}

int db_login(PGconn *conn, int id, char *password)
{
    char query[512];

    sprintf(query,"SELECT * FROM accounts WHERE id=%d AND password='%s';",id, password);

    PGresult *res = PQexec(conn, query);
    if (PQntuples(res) == 1)
    {
        PQclear(res);
        return 1; // succès
    }

    PQclear(res);
    return 0; // fail
}

void db_deposit(PGconn *conn, int id, float amount)
{
    char query[512];
    sprintf(query,"UPDATE accounts SET balance = balance + %f WHERE id=%d;",amount, id);

    PGresult *res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        printf("Deposit failed\n");
    }

    PQclear(res);
}

void db_withdraw(PGconn *conn, int id, float amount)
{
    char query[512];

    sprintf(query,"UPDATE accounts SET balance = balance - %f WHERE id=%d AND balance >= %f;",amount, id, amount);
    PGresult *res = PQexec(conn, query);

    if (PQcmdTuples(res)[0] == '0')
    {
        printf("Not enough money\n");
    }

    PQclear(res);
}

float db_get_balance(PGconn *conn, int id)
{
    char query[256];
    sprintf(query, "SELECT balance FROM accounts WHERE id=%d;", id);

    PGresult *res = PQexec(conn, query);

    if (PQntuples(res) == 1)
    {
        float balance = atof(PQgetvalue(res, 0, 0));
        PQclear(res);
        return balance;
    }

    PQclear(res);
    return -1;
}


void db_transfer(PGconn *conn, int from, int to, float amount)
{
    char query[512];

    sprintf(query,
        "UPDATE accounts SET balance = balance - %f WHERE id=%d AND balance >= %f;"
        "UPDATE accounts SET balance = balance + %f WHERE id=%d;",
        amount, from, amount, amount, to);

    PGresult *res = PQexec(conn, query);

    PQclear(res);
}
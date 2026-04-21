#include <stdio.h>
#include "database.h"

int main()
{
    PGconn *conn = connect_db();

    if (!conn)
        return 1;

    db_create_account(conn, 1, "cyril", "1234");

    if (db_login(conn, 1, "1234"))
        printf("Login OK\n");

    db_deposit(conn, 1, 100);
    printf("Balance: %.2f\n", db_get_balance(conn, 1));

    PQfinish(conn);
    return 0;
}
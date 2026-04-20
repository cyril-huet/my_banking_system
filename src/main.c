#include <stdio.h>
#include <libpq-fe.h>
#include "database.h"
int main()
{
    PGconn *conn = connect_db();

    if (!conn)
        return 1;

    db_create_account(conn, 1, "cyril", "1234");

    if (db_login(conn, 1, "1234"))
        printf("Login OK\n");
    else
        printf("Login failed\n");

    db_deposit(conn, 1, 100);
    db_withdraw(conn, 1, 50);

    PQfinish(conn);
    printf("Balance: %.2f\n", db_get_balance(conn, 1));

    db_create_account(conn, 2, "bob", "1234");

    db_transfer(conn, 1, 2, 20);

    printf("Balance 1: %.2f\n", db_get_balance(conn, 1));
    printf("Balance 2: %.2f\n", db_get_balance(conn, 2));
    return 0;
}
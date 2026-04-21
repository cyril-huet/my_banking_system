#include <arpa/inet.h>
#include <libpq-fe.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "database.h"

#define PORT 8080

void send_response(int client, char *body)
{
    char response[2048];

    sprintf(response,
            "HTTP/1.1 200 OK\r\n"
            "Access-Control-Allow-Origin: *\r\n"
            "Access-Control-Allow-Methods: GET\r\n"
            "Access-Control-Allow-Headers: *\r\n"
            "Content-Type: text/plain\r\n\r\n%s",
            body);
    write(client, response, strlen(response));
}

void handle_request(int client_socket)
{
    char buffer[2048] = { 0 };
    read(client_socket, buffer, sizeof(buffer));
    int id, to;
    float amount;
    char password[100];

    PGconn *conn = connect_db();
    if (!conn)
    {
        send_response(client_socket, "DB error");
        close(client_socket);
        return;
    }

    // LOGIN
    if (sscanf(buffer, "GET /login?id=%d&password=%s", &id, password) == 2)
    {
        char *space = strchr(password, ' ');
        if (space)
        {
            *space = '\0';
        }

        if (db_login(conn, id, password))
        {
            send_response(client_socket, "Login OK");
        }
        else
        {
            send_response(client_socket, "Login FAIL");
        }
    }

    // BALANCE
    else if (sscanf(buffer, "GET /balance?id=%d", &id) == 1)
    {
        float b = db_get_balance(conn, id);
        char msg[100];
        sprintf(msg, "Balance: %.2f", b);
        send_response(client_socket, msg);
    }

    // DEPOSIT
    else if (sscanf(buffer, "GET /deposit?id=%d&amount=%f", &id, &amount) == 2)
    {
        db_deposit(conn, id, amount);
        send_response(client_socket, "Deposit OK");
    }

    // WITHDRAW
    else if (sscanf(buffer, "GET /withdraw?id=%d&amount=%f", &id, &amount) == 2)
    {
        int success = db_withdraw(conn, id, amount);

        if (success)
        {
            send_response(client_socket, "Withdraw OK");
        }
        else
        {
            send_response(client_socket, "Not enough money");
        }
    }

    // TRANSFER
    else if (sscanf(buffer, "GET /transfer?from=%d&to=%d&amount=%f", &id, &to,
                    &amount)
             == 3)
    {
        db_withdraw(conn, id, amount);
        db_deposit(conn, to, amount);
        send_response(client_socket, "Transfer OK");
    }
    // CREATE ACCOUNT
    else if (sscanf(buffer, "GET /create?id=%d&password=%s", &id, password)
             == 2)
    {
        char *space = strchr(password, ' ');
        if (space)
        {
            *space = '\0';
        }

        db_create_account(conn, id, "user", password);
        send_response(client_socket, "Account created");
    }
    else
    {
        send_response(client_socket, "Bank API C 🚀");
    }

    PQfinish(conn);
    close(client_socket);
}

int main()
{
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 10);
    printf("Server running on http://localhost:8080\n");

    while (1)
    {
        client_socket = accept(server_fd, (struct sockaddr *)&address,
                               (socklen_t *)&addrlen);
        handle_request(client_socket);
    }

    return 0;
}
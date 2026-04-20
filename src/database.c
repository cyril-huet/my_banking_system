#include <stdio.h>
#include "database.h"

void save_account(Account account) {
    FILE *file = fopen("accounts.db", "ab");
    if (!file) {return;}

    fwrite(&account, sizeof(Account), 1, file);
    fclose(file);
}

int load_accounts(Account accounts[], int max) {
    FILE *file = fopen("accounts.db", "rb");
    if (!file) {return 0;}

    int count = 0;
    while (fread(&accounts[count], sizeof(Account), 1, file) && count < max) {
        count++;
    }

    fclose(file);
    return count;
}

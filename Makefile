CC=gcc
CFLAGS=-Wall -Wextra -Werror -Iinclude

SRC=src/main.c src/account.c
TARGET=bank

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

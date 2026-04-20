CC=gcc
CFLAGS=-Wall -Wextra -Werror -Iinclude

SRC=src/main.c src/account.c src/database.c
TARGET=bank

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)


format:
	clang-format -i src/*.c include/*.h
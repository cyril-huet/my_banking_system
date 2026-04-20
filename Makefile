CC=gcc
CFLAGS=-Wall -Wextra -Werror -Iinclude

SRC=src/main.c src/account.c
OUT=bank

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)

format:
	clang-format -i src/*.c include/*.h
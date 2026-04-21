CC = gcc

CFLAGS = -Wall -Wextra -Werror \
-Iinclude \
-I/opt/homebrew/opt/libpq/include

LDFLAGS = -L/opt/homebrew/opt/libpq/lib -lpq -lcivetweb

all:
	$(CC) src/server.c src/database.c -o server $(CFLAGS) $(LDFLAGS)

test:
	$(CC) src/main.c src/database.c -o test $(CFLAGS) $(LDFLAGS)

clean:
	rm -f server test
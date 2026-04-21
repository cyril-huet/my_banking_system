CC = gcc

UNAME_S := $(shell uname -s)

# Flags communs
CFLAGS = -Wall -Wextra -Werror -Iinclude
LDFLAGS = -lpq

# Config selon OS (homebrew si MacOS)
ifeq ($(UNAME_S),Darwin)
	CFLAGS += -I/opt/homebrew/opt/libpq/include
	LDFLAGS += -L/opt/homebrew/opt/libpq/lib
endif

ifeq ($(UNAME_S),Linux)
	CFLAGS += -I/usr/include/postgresql
	LDFLAGS += -L/usr/lib -lpq
endif

SRC = src/server.c src/database.c
TARGET = server

all:
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

format:
	find . -name "*.c" -o -name "*.h" | xargs clang-format -i

clean:
	rm -f $(TARGET)

# .DEFAULT_GOAL=all

CC=gcc
CFLAGS=-fsanitize=signed-integer-overflow -fsanitize=undefined -g -std=gnu99 -O2 -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow

FRONTEND=a1_frontend
BACKEND=a1_backend

all: backend frontend
.PHONY: all

backend: a1_lib.c backend.c
	$(CC) -o $(BACKEND) $(CFLAGS) backend.c a1_lib.c
	./a1_backend

frontend: a1_lib.c frontend.c
	$(CC) -o $(FRONTEND) $(CFLAGS) frontend.c a1_lib.c
	./a1_frontend

clean:
	rm -rf $(FRONTEND) $(BACKEND)


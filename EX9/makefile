# Makefile for compiling loader, A, and B

CC = gcc
CFLAGS = -Wall
TARGETS = loader A B

all: $(TARGETS)

loader: loader.c
	$(CC) $(CFLAGS) -o loader loader.c

A: A.c
	$(CC) $(CFLAGS) -o A A.c

B: B.c
	$(CC) $(CFLAGS) -o B B.c

clean:
	rm -f $(TARGETS)


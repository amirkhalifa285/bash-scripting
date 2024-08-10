CC = gcc
CFLAGS = -Wall -g

all: loader A B

loader: loader.c
	$(CC) $(CFLAGS) -o loader loader.c

A: A.c
	$(CC) $(CFLAGS) -o A A.c

B: B.c
	$(CC) $(CFLAGS) -o B B.c

clean:
	rm -f loader A B file_B.txt *.o

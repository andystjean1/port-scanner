
CC = gcc
CFLAGS = -O4 -Wall -g


all: scanner

scan: scanner.o
	$(CC) $(CFLAGS) -o scan scanner.o

scanner.o: scanner.c
	$(CC) $(CFLAGS) -c scanner.c

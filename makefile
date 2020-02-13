CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c11
NAME = gameoflife

all: gameoflife.c libgol.so
	$(CC) $(CFLAGS) -o $(NAME) gameoflife.c -L. -lgol -Wl,-rpath=.

libgol.so: gol.o
	$(CC) $(CFLAGS) -shared gol.o -o libgol.so

gol.o: gol.c gol.h
	$(CC) $(CFLAGS) -c gol.c -fPIC

.PHONY: clean

clean:
	rm -f ./*.o ./*.so ./$(NAME) *~ core ./*~
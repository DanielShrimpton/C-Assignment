CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c11 -I.
DEPS = gol.h
OBJ = gameoflife.o gol.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

gameoflife2: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f ./*.o *~ core ./*~
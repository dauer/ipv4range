CC=gcc
CFLAGS=-std=c99 -ansi -g -Wextra -Wall -pedantic -I.
DEPS=iprange.h interface.h
OBJ=main.o interface.o iprange.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ipv4range: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -rf *.o ipv4range

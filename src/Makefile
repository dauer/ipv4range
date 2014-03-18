CC=gcc

ifeq ($(mode), release)
	CFLAGS=-std=c99 -O2 -ansi -Wextra -Wall -pedantic -Wconversion -I.
else
	CFLAGS=-std=c99 -O0 -ansi -g -Wextra -Wall -pedantic -Wconversion -I.
endif

DEPS=iprange.h interface.h
OBJ=main.o interface.o iprange.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ipv4range: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -rf *.o ipv4range

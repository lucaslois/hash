EXEC = pruebas
CC = gcc
CFLAGS = -Werror -pedantic -std=c99 -g

all: pruebas

pruebas: pruebas_catedra.c main.c testing.c hash.o
	$(CC) $(CFLAGS) pruebas_catedra.c main.c testing.c hash.o -o $(EXEC)

hash.o: hash.c hash.h
	$(CC) $(CFLAGS) hash.c -c

run: pruebas
	./pruebas

reset: hash.o pruebas
	rm hash.o pruebas .hash.c.swp vgcore.*

remove_vgcore:
	rm vgcore.*

valgrind: pruebas
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pruebas

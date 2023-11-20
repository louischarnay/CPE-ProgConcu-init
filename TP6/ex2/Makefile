CC = gcc
C_FLAGS = -Wall -Wextra -Wpedantic -g

CONSO = dijkstra.c conso.c 
PROD = dijkstra.c prod.c
INIT = dijkstra.c init.c
CLEAN = dijkstra.c clean.c


all:
	$(CC) $(C_FLAGS) -o conso.out $(CONSO)
	$(CC) $(C_FLAGS) -o prod.out $(PROD)
	$(CC) $(C_FLAGS) -o init.out $(INIT)
	$(CC) $(C_FLAGS) -o clean.out $(CLEAN)

clean:
	rm -rf *.out
	rm -rf *.dSYM

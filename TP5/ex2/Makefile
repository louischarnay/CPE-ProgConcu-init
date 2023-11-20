CC = gcc
C_FLAGS = -Wall -Wextra -g

FIRST = dijkstra.c first.c 
SECOND = dijkstra.c second.c
INIT = dijkstra.c init.c
CLEAN = dijkstra.c clean.c


all:
	$(CC) $(C_FLAGS) -o first.out $(FIRST)
	$(CC) $(C_FLAGS) -o second.out $(SECOND)
	$(CC) $(C_FLAGS) -o init.out $(INIT)
	$(CC) $(C_FLAGS) -o clean.out $(CLEAN)

clean:
	rm -rf *.out
	rm -rf *.dSYM
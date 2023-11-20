CC = gcc
C_FLAGS = -Wall -Wextra -Wpedantic -g

READER = dijkstra.c reader.c 
WRITER = dijkstra.c writer.c
INIT = dijkstra.c init.c
CLEAN = dijkstra.c clean.c


all:
	$(CC) $(C_FLAGS) -o reader.out $(READER)
	$(CC) $(C_FLAGS) -o writer.out $(WRITER)
	$(CC) $(C_FLAGS) -o init.out $(INIT)
	$(CC) $(C_FLAGS) -o clean.out $(CLEAN)

clean:
	rm -rf *.out
	rm -rf *.dSYM

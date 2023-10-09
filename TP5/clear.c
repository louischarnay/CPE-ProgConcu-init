#include "dijkstra/dijkstra.c"

int main(int argc, char *argv[]) {
    sem_delete(atoi(argv[argc - 1]));
    return 0;
}
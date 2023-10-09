#include "./dijkstra/dijkstra.c"

#define CLE 1

int main(int argc, char *argv[]) {
    int sem;
    sem = sem_create(CLE, atoi(argv[argc - 1]));
    printf("Semaphore %d created\n", sem);
    return sem;
}
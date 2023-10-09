#include "./dijkstra/dijkstra.c"

int main(int argc, char *argv[]) {
    int sem;
    sem = sem_create(atoi(argv[1]), atoi(argv[2]));
    printf("Semaphore %d created\n", sem);
    return sem;
}
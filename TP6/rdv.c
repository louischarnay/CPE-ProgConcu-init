#include <sys/shm.h>

#include "./dijkstra/dijkstra.c"

#define NUM 4
#define KEY 5942
#define KEY_2 5943

int main() {
    int semid1 = sem_create(KEY, 0);
    int semid2 = sem_create(KEY_2, 0);

    int* mutex = shmat(semid1, NULL, 0); //nombre de processus en attente

    printf("Start rendez-vous\n");

    P(semid1);
    if(*mutex + 1 != NUM){
        *mutex = *mutex + 1;
        printf("mutex = %d\n", *mutex);
        V(semid1);
        P(semid2);
        V(semid2);
    } else {
        printf("Last processus\n");
        V(semid1);
        V(semid2);
    }

    shmdt(mutex);

    printf("End rendez-vous\n");

    return 0;
}
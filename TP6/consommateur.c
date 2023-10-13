#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "./dijkstra/dijkstra.c"

#define NUM 4
#define KEY 5942
#define KEY_2 5943
#define KEY_3 5944

int main() {
    srand(getpid());

    int semid1 = sem_create(KEY, 0);
    int semid2 = sem_create(KEY_2, 0);
    int semid3 = sem_create(KEY_3, 0);

    int* mutex = shmat(semid1, NULL, 0); //nombre de processus en attente

    int IL = mutex[NUM];
    
    P(semid3);
    P(semid1);
    printf("Consommateur %d : %d\n", IL, mutex[IL]);
    mutex[NUM] = (IL + 1) % NUM;
    V(semid1);
    V(semid2);

    shmdt(mutex);

    return 0;
}
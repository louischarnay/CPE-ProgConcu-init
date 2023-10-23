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

int max(int i1, int i2){
    if(i1 > i2){
        return i1;
    }
    return i2;
}

int main() {
    srand(getpid());

    int semid1 = sem_create(KEY, 0);
    int semid2 = sem_create(KEY_2, 0);
    int semid3 = sem_create(KEY_3, 0);

    int* mutex = shmat(semid1, NULL, 0); //nombre de processus en attente

    int result = 0;

    int i1, i2, maxValue;

    while(result != -1){
        P(semid2);
        P(semid1);
        i1 = mutex[0];
        i2 = mutex[1];
        V(semid1);
        P(semid3);
        P(semid1);
        maxValue = max(i1, i2);
        if (maxValue == i1) {
            result = -1;
        }
        mutex[2] = result;
        V(semid1);
        V(semid2);
    }

    shmdt(mutex);

    return 0;
}
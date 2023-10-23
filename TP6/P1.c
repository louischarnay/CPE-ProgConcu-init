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

int index;

int max(int tab[]){
    int max = tab[0];
    for(int i = 1; i < NUM; i++){
        if(tab[i] > max){
            max = tab[i];
            index = i;
        }
    }
    return max;
}

int main() {
    int tab[NUM] = {0, 1, 2, 3};
    srand(getpid());

    int semid1 = sem_create(KEY, 0);
    int semid2 = sem_create(KEY_2, 0);
    int semid3 = sem_create(KEY_3, 0);

    int* mutex = shmat(semid1, NULL, 0); //nombre de processus en attente

    int result = 0;

    while(result != -1){
        P(semid2);
        P(semid1);
        mutex[0] = max(tab);
        V(semid1);
        P(semid3);
        P(semid1);
        result = mutex[2];
        tab[index] = mutex[0];
        V(semid1);
        V(semid2);
    }
    printf("Resultat tab1 : ");
    for(int i = 0; i < NUM; i++){
        printf("%d ", tab[i]);
    }
    printf("\n");

    shmdt(mutex);

    return 0;
}
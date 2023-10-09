#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "./dijkstra/dijkstra.c"

#define CLE 1

int main() {
    printf("Coucou c'est Sandro\n");

    int semid1 = sem_create(CLE, 0);
    int semid2 = sem_create(CLE+1, 0);
    
    srand(time(NULL));
    int random = (rand() % 10);

    sleep(random);

    printf("Sandro se réveille\n");

    V(semid1);
    P(semid1);

    printf("Sandro est au rdv");

    V(semid1);
    V(semid2); 
       
    return 0;
}
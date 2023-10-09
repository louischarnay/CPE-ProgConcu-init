#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "./dijkstra/dijkstra.c"

#define CLE 2

int main() {
    printf("Coucou c'est Seb\n");

    int semid1 = sem_create(CLE, 0);
    int semid2 = sem_create(CLE+1, 0);
    
    srand(time(NULL));
    int random = (rand() % 10);

    sleep(random);

    printf("Seb se réveille\n");

    P(semid1);
    V(semid2);
    
    printf("Seb est au rdv");

    V(semid1);
    V(semid2); 
    
    return 0;
}
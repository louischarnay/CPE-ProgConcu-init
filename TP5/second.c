#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "dijkstra/dijkstra.c"

#define CLE 1

int main(){
    printf("Hello World it's second\n");

    int semid = sem_create(CLE, 0);

    P(semid);
    
    srand(time(NULL));
    int random = (rand() % 4);

    while (random <= 1 || random >= 4)
    {
        random = (rand() % 4);
    }

    sleep(random);

    V(semid);

    printf("Second is done\n");
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "./dijkstra/dijkstra.c"

#define CLE 1

int main(){
    printf("Hello World it's first\n");

    int semid = sem_create(CLE, 0);
    
    srand(time(NULL));
    int random = (rand() % 5);

    while (random <= 3 || random >= 5)
    {
        random = (rand() % 5);
    }

    sleep(random);

    V(semid);

    printf("First is done\n");
    
    return 0;
}
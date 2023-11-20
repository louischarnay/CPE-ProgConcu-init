#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/sem.h>
#include <sys/types.h>
#include "dijkstra.h"

#define SNAME "sem"

int main(void){
	srand(time(NULL));
	puts("Waiting for sem");
	int semid = semget(1, 1, SEM_A | SEM_R);
	P(semid);
	int r = (rand() % (4 - 1 + 1)) + 1;
	printf("Sleeping %d\n", r);
	sleep(r);
	
	puts("woke up");
	return 0;
}

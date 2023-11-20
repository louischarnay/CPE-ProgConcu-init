#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "dijkstra.h"
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>

#define SNAME "sem"

int main(void){
	srand(time(NULL));
	puts("Message first");
	int r = (rand() % (5 - 3 + 1)) + 3;
	printf("Sleeping %d\n", r);
	int semid = semget(1, 1, SEM_A | SEM_R);
	//printf("SemdID %d\n", semid);
	sleep(r);
	V(semid);
	puts("Woke up");
	return 0;
}

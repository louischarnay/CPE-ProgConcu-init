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
	puts("Arrived");
	int semid = semget(1, 1, SEM_A | SEM_R);
	P(semid);
	puts("start rdv");
	return 0;
}